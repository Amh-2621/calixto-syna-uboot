// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2016~2023 Synaptics Incorporated. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 or
 * later as published by the Free Software Foundation.
 *
 * INFORMATION CONTAINED IN THIS DOCUMENT IS PROVIDED "AS-IS," AND
 * SYNAPTICS EXPRESSLY DISCLAIMS ALL EXPRESS AND IMPLIED WARRANTIES,
 * INCLUDING ANY IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE, AND ANY WARRANTIES OF NON-INFRINGEMENT OF ANY
 * INTELLECTUAL PROPERTY RIGHTS. IN NO EVENT SHALL SYNAPTICS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, PUNITIVE, OR
 * CONSEQUENTIAL DAMAGES ARISING OUT OF OR IN CONNECTION WITH THE USE
 * OF THE INFORMATION CONTAINED IN THIS DOCUMENT, HOWEVER CAUSED AND
 * BASED ON ANY THEORY OF LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, AND EVEN IF SYNAPTICS WAS
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. IF A TRIBUNAL OF
 * COMPETENT JURISDICTION DOES NOT PERMIT THE DISCLAIMER OF DIRECT
 * DAMAGES OR ANY OTHER DAMAGES, SYNAPTICS' TOTAL CUMULATIVE LIABILITY
 * TO ANY PARTY SHALL NOT EXCEED ONE HUNDRED U.S. DOLLARS.
 */

#include <config.h>
#include <common.h>
#include <div64.h>
#include <malloc.h>
#include "misc_syna.h"
#include "fastboot_syna.h"
#include <dm/device.h>
#include <dm/device-internal.h>

#ifdef CONFIG_MMC
#include "mmc.h"
#define CONFIG_MISC_IN_MMC 1
#endif

#ifdef CONFIG_SPI_FLASH_MTD
#include <linux/mtd/mtd.h>
#include <spi.h>
#include <spi_flash.h>
#undef CONFIG_MISC_IN_MMC
#define CONFIG_MISC_IN_SPI 1
#endif

#define BOOTCTRL_MAGIC				0x42424100
#define BOOT_CONTROL_VERSION		1
#define ANDROID_AB_COMMAND_KEY		"bootctrl.metadata"
#define BOOTCTRL_HAL_FTS_LENGH		0x20
#define MISC_BOOT_CONTROL_VERSION  2
#define MAX_GPT_ENTRY 64

typedef struct syna_slot_metadata {
	uint8_t priority : 4;
	uint8_t tries_remaining : 3;
	uint8_t successful_boot : 1;
} syna_slot_metadata_t;

typedef struct boot_ctrl {
	u32 magic;		// Magic for identification - '\0ABB' (Boot Contrl Magic)
	u8 version;		// boot ctrl version, 1
	 syna_slot_metadata_t slot_info[2];	// Information about each slot
	u8 reserved;		// reserved
} boot_ctrl_t;

typedef struct misc_slot_metadata {
	u8 priority;
	u8 tries_remaining;
	// 1 if this slot has booted successfully, 0 otherwise.
	u8 successful_boot;
	// 1 if this slot is corrupted from a dm-verity corruption, 0 otherwise.
	u8 verity_corrupted;
	u8 reserved;
} misc_slot_metadata_t;

typedef struct misc_boot_ctrl {
	u32 magic;
	u8 version;
	u8 recovery_tries_remaining;
	misc_slot_metadata_t slot_info[2];
	u8 reserved[16];
} misc_boot_ctrl_t;

struct emmc_part {
	unsigned char	hwpart; /* UDA or GPPn */
	unsigned char	part;	/* part index inside GPT */
	disk_partition_t info;
};

#ifdef CONFIG_MMC
static struct emmc_part *emmc_part_table;
#endif

static bool is_valid_bootctrl(void *p_bootctrl)
{
	misc_boot_ctrl_t *pbctrl = (misc_boot_ctrl_t *)p_bootctrl;

	return ((pbctrl->magic == BOOTCTRL_MAGIC) && (pbctrl->version == MISC_BOOT_CONTROL_VERSION));
}

static bool slot_is_bootable(misc_slot_metadata_t *p_slot)
{
	return p_slot->priority > 0 && (p_slot->successful_boot || (p_slot->tries_remaining > 0));
}

static int write_bootctrl_metadata(void *p_bootctrl)
{
#ifdef CONFIG_MISC_IN_MMC
	if (!p_bootctrl) {
		printf("ERROR: invalid bootctrl metadata for write !\n");
		return -1;
	}

	struct blk_desc *dev_desc;
	disk_partition_t info;
	lbaint_t strat_blk, size_blk;
	int mmc_dev = get_mmc_boot_dev();
	struct mmc *mmc = find_mmc_device(mmc_dev);
	char *partition_name = "misc";

	if (!mmc) {
		printf("invalid mmc device\n");
		return -1;
	}

	dev_desc = blk_get_dev("mmc", mmc_dev);
	if (!dev_desc || dev_desc->type == DEV_TYPE_UNKNOWN) {
		printf("invalid mmc device\n");
		return -1;
	}

	blk_dselect_hwpart(dev_desc, get_mmc_part_by_name(mmc_dev, partition_name));

	if (part_get_info_by_name(dev_desc, partition_name, &info) == -1) {
		printf("cannot find partition: '%s'\n", partition_name);
		return -1;
	}
	strat_blk = info.start + 4096 / dev_desc->blksz;
	size_blk = (sizeof(misc_boot_ctrl_t) + dev_desc->blksz) / dev_desc->blksz;
	blk_dwrite(dev_desc, strat_blk, size_blk, p_bootctrl);

	return 0;
#else
	disk_partition_t info;
	loff_t start;
	size_t write_len;
	size_t write;
	int ret = -1;
	struct erase_info erase_op = {};
	struct mtd_info *mtd = get_mtd_device(NULL, 0);

	if (IS_ERR_OR_NULL(mtd)) {
		puts("\nno devices available\n");
		goto out;
	}

	char *partition_name = "misc";

	if (syna_mtdparts_get_info_by_name(mtd, partition_name, &info) == -1) {
		printf("cannot find partition: '%s'\n", partition_name);
		goto out;
	}
	start = (info.start * info.blksz) + 4096;
	write_len = sizeof(misc_boot_ctrl_t);

	erase_op.mtd = mtd;
	erase_op.addr = (start & (~(mtd->erasesize - 1)));
	erase_op.len = mtd->erasesize;
	erase_op.scrub = 0;

	ret = mtd_erase(mtd, &erase_op);
	if (ret) {
		printf("%s: erase() failed for block at 0x%llx: %d\n",
		       mtd->name, erase_op.addr, ret);
		goto out;
	}

	ret = mtd_write(mtd, start, write_len, &write, p_bootctrl);
	if (ret || write != write_len) {
		printf("%s: write() failed for block at 0x%llx: %d\n",
		       mtd->name, start, ret);
		goto out;
	}
	ret = 0;

out:
	if (!IS_ERR_OR_NULL(mtd))
		put_mtd_device(mtd);

	return ret;
#endif
}

static int get_bootctrl_metadata(void *p_bootctrl)
{
#ifdef CONFIG_MISC_IN_MMC
	if (!p_bootctrl) {
		printf("Error: invalid parameter p_bootctrl !\n");
		return -1;
	}

	struct blk_desc *dev_desc;
	disk_partition_t info;
	lbaint_t strat_blk;
	int mmc_dev = get_mmc_boot_dev();
	struct mmc *mmc = find_mmc_device(mmc_dev);
	char *misc_bootctrl;
	char *partition_name = "misc";

	if (!mmc) {
		printf("invalid mmc device\n");
		return -1;
	}

	dev_desc = blk_get_dev("mmc", mmc_dev);
	if (!dev_desc || dev_desc->type == DEV_TYPE_UNKNOWN) {
		printf("invalid mmc device\n");
		return -1;
	}

	blk_dselect_hwpart(dev_desc, get_mmc_part_by_name(mmc_dev, partition_name));

	if (part_get_info_by_name(dev_desc, partition_name, &info) == -1) {
		printf("cannot find partition: '%s'\n", partition_name);
		return -1;
	}

	misc_bootctrl = (void *)malloc(dev_desc->blksz);
	strat_blk = info.start + 4096 / dev_desc->blksz;
	blk_dread(dev_desc, strat_blk, 1, misc_bootctrl);
	memcpy(p_bootctrl, (void *)misc_bootctrl, sizeof(misc_boot_ctrl_t));

	free(misc_bootctrl);

	return 0;
#else
	disk_partition_t info;
	loff_t start;
	int ret = -1;
	struct mtd_info *mtd = get_mtd_device(NULL, 0);
	size_t read;

	if (IS_ERR_OR_NULL(mtd)) {
		puts("\nno devices available\n");
		return 1;
	}

	char *partition_name = "misc";

	if (syna_mtdparts_get_info_by_name(mtd, partition_name, &info) == -1) {
		printf("cannot find partition: '%s'\n", partition_name);
		goto out;
	}

	start = (info.start * info.blksz) + 4096;
	ret = mtd_read(mtd, start, sizeof(misc_boot_ctrl_t), &read, p_bootctrl);

	if ((ret && ret != -EUCLEAN) || read != sizeof(misc_boot_ctrl_t)) {
		printf("%s: read() failed for block at 0x%llx: %d\n",
		       mtd->name, start, ret);
		goto out;
	}

	ret = 0;

out:
	if (!IS_ERR_OR_NULL(mtd))
		put_mtd_device(mtd);

	return ret;
#endif
}

static int init_bootctrl(misc_boot_ctrl_t *p_bootctrl, int default_slot)
{
	if (default_slot > 1) {
		printf("invalid default slot number for bootctrl !\n");
		return -1;
	}

	memset((void *)p_bootctrl, 0, sizeof(misc_boot_ctrl_t));

	p_bootctrl->slot_info[default_slot].priority		    = 8;
	p_bootctrl->slot_info[default_slot].tries_remaining	= 2;
	p_bootctrl->slot_info[default_slot].successful_boot	= 0;

	p_bootctrl->slot_info[1 - default_slot].priority		    = 3;
	p_bootctrl->slot_info[1 - default_slot].tries_remaining	= 2;
	p_bootctrl->slot_info[1 - default_slot].successful_boot	= 0;

	p_bootctrl->version	= MISC_BOOT_CONTROL_VERSION;
	p_bootctrl->magic	= BOOTCTRL_MAGIC;

	if (write_bootctrl_metadata(p_bootctrl)) {
		printf("Error: fail to write misc bootctrl metadata !\n");
		return -1;
	}

	return 0;
}

int get_current_slot(void)
{
	int bootab_sel = BOOTSEL_INVALID;
	misc_boot_ctrl_t bctrl;

	if (get_bootctrl_metadata((void *)&bctrl)) {
		printf("Error: fail to get bootctrl.metadata !\n");
		return get_boot_slot();
	}

	if (is_valid_bootctrl((void *)&bctrl)) {
		if (slot_is_bootable((void *)&bctrl.slot_info[0]) &&
		    slot_is_bootable((void *)&bctrl.slot_info[1])) {
		    if (bctrl.slot_info[0].priority != bctrl.slot_info[1].priority)
				bootab_sel = (bctrl.slot_info[0].priority - bctrl.slot_info[1].priority) > 0 ? BOOTSEL_A : BOOTSEL_B;
			else if(bctrl.slot_info[0].successful_boot != bctrl.slot_info[1].successful_boot)
				bootab_sel = (bctrl.slot_info[0].successful_boot - bctrl.slot_info[1].successful_boot) > 0 ? BOOTSEL_A : BOOTSEL_B;
			else if(bctrl.slot_info[0].tries_remaining != bctrl.slot_info[1].tries_remaining)
				bootab_sel = (bctrl.slot_info[0].tries_remaining - bctrl.slot_info[1].tries_remaining) > 0 ? BOOTSEL_A : BOOTSEL_B;
			else
				bootab_sel = BOOTSEL_DEFAULT;
		} else if (slot_is_bootable((void *)&bctrl.slot_info[0])) {
			bootab_sel = BOOTSEL_A;
		} else if (slot_is_bootable((void *)&bctrl.slot_info[1])) {
			bootab_sel = BOOTSEL_B;
		} else {
			/* No bootable slots! */
			printf("No bootable slots found !!!\n");
			bootab_sel = BOOTSEL_INVALID;
			goto out;
		}
	} else {
		printf("invalid bootctrl, Magic:0x%x,Ver:0x%x.\n", bctrl.magic, bctrl.version);
		if (!init_bootctrl((void *)&bctrl, BOOTSEL_DEFAULT)) {
			printf("No valid metadata for bootctrl, initialize to default slot %d !\n", BOOTSEL_DEFAULT);
			bootab_sel = BOOTSEL_DEFAULT;
		}
	}

	debug("Slot index=%d got !\n", bootab_sel);

out:
	return bootab_sel;
}

bool set_active_slot(int slot_index)
{
	misc_boot_ctrl_t bctrl;
	misc_slot_metadata_t *slotp = NULL;

	if((unsigned int)slot_index > 0x1) {
		printf("invalid slot number for bootctrl !\n");
		goto error;
	}

	if(get_bootctrl_metadata((void *)&bctrl)) {
		printf("Error: fail to get bootctrl.metadata !\n");
		goto error;
	}

	if(is_valid_bootctrl((void *)&bctrl)) {
		slotp = &bctrl.slot_info[slot_index];
		slotp->successful_boot = 0;
		slotp->priority = 15;
		slotp->tries_remaining = 2;

		slotp = &bctrl.slot_info[1-slot_index];
		if(slotp->priority >= 15)
			slotp->priority = 14;
		if(write_bootctrl_metadata((void *)&bctrl)) {
			printf("Fail to write bootctrl metadata !\n");
			goto error;
		}
	} else {
		printf("invalid bootctrl, Magic:0x%x,Ver:0x%x.\n", bctrl.magic, bctrl.version);
		printf("No valid metadata for bootctrl, initialize to default slot %d !\n", slot_index);
		if(init_bootctrl((void *)&bctrl, slot_index))
			goto error;
	}

	return (bool)1;

error:
	printf("Fail to set slot %d active !\n", slot_index);
	return (bool)0;
}

int try_abmode(int abmode_sel)
{
	/* ... and decrement tries remaining, if applicable. */
	misc_boot_ctrl_t bctrl;

	memset((void *)&bctrl, 0, sizeof(misc_boot_ctrl_t));
	if (get_bootctrl_metadata((void *)&bctrl)) {
		printf("Error: fail to get bootctrl.metadata !\n");
		return 1;
	}

	if (is_valid_bootctrl((void *)&bctrl) && bctrl.slot_info[abmode_sel].tries_remaining > 0) {
		bctrl.slot_info[abmode_sel].tries_remaining -= 1;
		write_bootctrl_metadata((void *)&bctrl);
		return 0;
	} else if (is_valid_bootctrl((void *)&bctrl)) {
		bctrl.slot_info[abmode_sel].priority -= 2;
		write_bootctrl_metadata((void *)&bctrl);
		return -1;
	}

	return 1;
}

#ifdef CONFIG_MMC
static struct part_driver *f_part_driver_lookup_type(struct blk_desc *dev_desc)
{
	struct part_driver *drv =
		ll_entry_start(struct part_driver, part_driver);
	const int n_ents = ll_entry_count(struct part_driver, part_driver);
	struct part_driver *entry;

	if (dev_desc->part_type == PART_TYPE_UNKNOWN) {
		for (entry = drv; entry != drv + n_ents; entry++) {
			int ret;

			ret = entry->test(dev_desc);
			if (!ret) {
				dev_desc->part_type = entry->part_type;
				return entry;
			}
		}
	} else {
		for (entry = drv; entry != drv + n_ents; entry++) {
			if (dev_desc->part_type == entry->part_type)
				return entry;
		}
	}

	/* Not found */
	return NULL;
}

static int f_part_get_info_by_name(struct blk_desc *dev_desc, const char *name,
				   disk_partition_t *info)
{
	struct part_driver *part_drv;
	int ret;
	int i;

	part_drv = f_part_driver_lookup_type(dev_desc);
	if (!part_drv)
		return -1;
	for (i = 1; i < part_drv->max_entries; i++) {
		ret = part_drv->get_info(dev_desc, i, info);
		if (ret != 0) {
			/* no more entries in table */
			break;
		}
		if (strcmp(name, (const char *)info->name) == 0) {
			/* matched */
			return i;
		}
	}

	return -1;
}

static int f_part_get_info_by_name_or_alias(struct blk_desc *dev_desc,
					    const char *name, disk_partition_t *info)
{
	int ret;

	ret = f_part_get_info_by_name(dev_desc, name, info);
	if (ret < 0) {
		/* strlen("fastboot_partition_alias_") + 32(part_name) + 1 */
		char env_alias_name[25 + 32 + 1];
		char *aliased_part_name;

		/* check for alias */
		strcpy(env_alias_name, "fastboot_partition_alias_");
		strncat(env_alias_name, name, 32);
		aliased_part_name = env_get(env_alias_name);
		if (aliased_part_name)
			ret = f_part_get_info_by_name(dev_desc,
						      aliased_part_name, info);
	}
	return ret;
}

static void read_raw_image_from_offset(struct blk_desc *dev_desc, disk_partition_t *info,
				       const char *part_name, void *buffer,
		unsigned int read_bytes, unsigned int offset)
{
	lbaint_t blkcnt;
	lbaint_t blks;
	lbaint_t start;

	/* determine number of blocks to write */
	blkcnt = ((read_bytes + (info->blksz - 1)) & ~(info->blksz - 1));
	blkcnt = lldiv(blkcnt, info->blksz);

	start = info->start;

	if (offset % info->blksz) {
		printf("offset should be aligned with block size\n");
		return;
	}

	start += (offset / (info->blksz));

	if (blkcnt > info->size) {
		printf("too large for partition: '%s'\n", part_name);
		return;
	}

	blks = blk_dread(dev_desc, start, blkcnt, buffer);
	if (blks != blkcnt) {
		printf("failed reading to device %d\n", dev_desc->devnum);
		return;
	}
}

int f_mmc_get_part_info(int mmc_dev, const char *part_name,
			disk_partition_t *part_info)
{
	struct blk_desc *dev_desc = blk_get_dev("mmc", mmc_dev);
	int part = 0;

	if (!dev_desc) {
		printf("block device not found");
		return -ENOENT;
	}

	if (!part_name || !part_info) {
		printf("parameter error");
		return -ENOENT;
	}

	part = get_mmc_part_by_name(mmc_dev, part_name);
	blk_dselect_hwpart(dev_desc, part);

	if (part == 1 || part == 2) {
		part_info->start = 0;
		part_info->size = dev_desc->lba;
		part_info->blksz = dev_desc->blksz;
		return 0;
	} else {
		return f_part_get_info_by_name_or_alias(dev_desc, part_name, part_info);
	}
}

int f_mmc_get_part_index(int mmc_dev, const char *part_name)
{
	disk_partition_t part_info;

	return f_mmc_get_part_info(mmc_dev, part_name, &part_info);
}

int f_mmc_save_part_table(int mmc_dev)
{
	struct part_driver *part_drv = NULL;
	int i = 0, j = 0, k = 0, ret = 0;
	struct blk_desc *dev_desc = blk_get_dev("mmc", mmc_dev);

	if (!dev_desc) {
		printf("block device not found");
		return -ENOENT;
	}

	part_drv = f_part_driver_lookup_type(dev_desc);
	if (!part_drv)
		return -1;

	emmc_part_table = (void *)malloc(MAX_GPT_ENTRY * sizeof(struct emmc_part));
	if (!emmc_part_table)
		return -ENOMEM;

	if (blk_dselect_hwpart(dev_desc, 0)) /* UDA */
		return -ENOENT;

	for (j = 1; j < part_drv->max_entries && i < MAX_GPT_ENTRY; i++, j++) {
		emmc_part_table[i].hwpart = 0;
		emmc_part_table[i].part = j;
		ret = part_drv->get_info(dev_desc, j, &emmc_part_table[i].info);
		if (ret != 0) {
			/* no more entries in table */
			break;
		}
	}

	for (k = 4; k < 8; k++) {
		if (blk_dselect_hwpart(dev_desc, k)) /* GPPn */
			break;

		for (j = 1; j < part_drv->max_entries && i < MAX_GPT_ENTRY; i++, j++) {
			emmc_part_table[i].hwpart = k;
			emmc_part_table[i].part = j;
			ret = part_drv->get_info(dev_desc, j, &emmc_part_table[i].info);
			if (ret != 0) {
				/* no more entries in table */
				break;
			}
		}
	}

	if (i == MAX_GPT_ENTRY)
		return -EINVAL;

	return 0;
}

int f_mmc_get_hwpart_from_table(const char *part_name)
{
	int i;

	if (!emmc_part_table)
		return -EINVAL;

	for (i = 0; i < MAX_GPT_ENTRY; i++)
		if (strcmp(part_name, (const char *)&emmc_part_table[i].info.name) == 0)
			return emmc_part_table[i].hwpart;

	return -EINVAL;
}

int f_mmc_get_part_from_table(const char *part_name)
{
	int i;

	if (!emmc_part_table)
		return -EINVAL;

	for (i = 0; i < MAX_GPT_ENTRY; i++)
		if (strcmp(part_name, (const char *)&emmc_part_table[i].info.name) == 0)
			return emmc_part_table[i].part;

	return -EINVAL;
}

void fb_mmc_flash_read_from_offset(const char *cmd, void *read_buffer,
				   unsigned int read_bytes, unsigned int offset)
{
	struct blk_desc *dev_desc;
	disk_partition_t info;
	int mmc_dev = get_mmc_active_dev();
	struct mmc *mmc = find_mmc_device(mmc_dev);

	if (!mmc) {
		printf("invalid mmc device\n");
		return;
	}

	dev_desc = blk_get_dev("mmc", mmc_dev);
	if (!dev_desc || dev_desc->type == DEV_TYPE_UNKNOWN) {
		printf("invalid mmc device\n");
		return;
	}
	if (f_mmc_get_part_info(mmc_dev, cmd, &info) < 0) {
		printf("cannot find partition: '%s'\n", cmd);
		return;
	}

	read_raw_image_from_offset(dev_desc, &info, cmd, read_buffer, read_bytes, offset);
}

void fb_mmc_flash_read(const char *cmd, void *read_buffer,
		       unsigned int read_bytes)
{
	fb_mmc_flash_read_from_offset(cmd, read_buffer, read_bytes, 0);
}
#endif

#ifdef CONFIG_SPI_FLASH_MTD

static struct spi_flash *flash;

struct mtd_info *fb_spi_setup_mtd_dev(void)
{
	struct udevice *new, *bus_dev;
	int ret;

	if (flash)
		return &flash->mtd;

	ret = spi_find_bus_and_cs(CONFIG_SF_DEFAULT_BUS, CONFIG_SF_DEFAULT_CS, &bus_dev, &new);
	if (!ret)
		device_remove(new, DM_REMOVE_NORMAL);

	ret = spi_flash_probe_bus_cs(CONFIG_SF_DEFAULT_BUS, CONFIG_SF_DEFAULT_CS,
				     CONFIG_SF_DEFAULT_SPEED, CONFIG_SF_DEFAULT_MODE, &new);
	if (ret) {
		printf("Failed to initialize SPI flash at %u:%u (error %d)\n",
		       CONFIG_SF_DEFAULT_BUS, CONFIG_SF_DEFAULT_CS, ret);
		return NULL;
	}

	flash = dev_get_uclass_priv(new);

	if (flash)
		return &flash->mtd;

	return NULL;
}
#endif

static int do_bootslot(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int ab_mode;

	if (argc == 1)
		return -1;

	if(strcmp(argv[1], "get") == 0) {
		ab_mode = get_current_slot();
		if (ab_mode != BOOTSEL_A && ab_mode != BOOTSEL_B)
			printf("No bootable slots found\n");
		else
			printf("Active boot slot is %s\n", ab_mode ? "b" : "a");

		return 0;
	}

	if(strcmp(argv[1], "set") == 0) {
		if (argv[2][0] == 'a')
			ab_mode = BOOTSEL_A;
		else if (argv[2][0] == 'b')
			ab_mode = BOOTSEL_B;
		else
			return -1;

		set_active_slot(ab_mode);
		return 0;
	}

	return -1;
}

U_BOOT_CMD(
	bootslot, 3, 0, do_bootslot,
	"get/set active Linux boot slot(a/b) in emmc\n",
	"Examples:\n"
	"\tbootslot get\n"
	"\tbootslot set a\n"
);

