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

#include <common.h>
#include <command.h>
#include <image.h>
#include <genimg.h>
#include <android_image.h>
#include "fastboot_syna.h"
#include "mem_init.h"
#include "tee_client.h"

#include <linux/mtd/mtd.h>

#define GENX_IMAGE_HEADER_LINUX_SIZE 336
#define IMAGE_TYPE_LINUX_KERNEL 0x21
#define LINUX_KERNEL_ADDR 0x7c00000
#define CODETYPE_KERNEL 5

#define MIN_ANDROID_IMG_SIZE (1 * 1024 * 1024)
#define MAX_ANDROID_IMG_SIZE (30 * 1024 * 1024)

#define KERNEL_A_NAME           "boot_a"
#define KERNEL_B_NAME           "boot_b"

#define	MAX_PAGESIZE 8192
#define CUSTKEY_SIZE		(5 << 10)

#define SYNA_SPI_BASE 0xF0000000
#define SYNA_SPI_RANGE 0x1000000

#define DEFAULT_SPI_ADDR 0x200000

enum boot_type_t {
	BOOT_TYPE_MMC,
	BOOT_TYPE_SPI,
	BOOT_TYPE_RAM,
	BOOT_TYPE_INVALID = -1,
};

static int read_image(enum boot_type_t boot_type, const char *pt_name,
	u32 offset, unsigned char *buff, unsigned int read_bytes)
{
	struct mtd_info *mtd = NULL;
	size_t read;
	loff_t start;
	int ret = -1;

	switch (boot_type) {
#ifdef CONFIG_MMC
	case BOOT_TYPE_MMC:
		fb_mmc_flash_read(pt_name, buff, read_bytes);
		ret = 0;
		break;
#endif

#ifdef CONFIG_SPI_FLASH_MTD
	case BOOT_TYPE_SPI:
		mtd = get_mtd_device(NULL, 0);
		if (IS_ERR_OR_NULL(mtd)) {
			puts("\nno devices available\n");
			goto spi_out;
		}

		if (pt_name) {
			disk_partition_t info;

			if (syna_mtdparts_get_info_by_name(mtd, pt_name, &info) == -1) {
				printf("cannot find partition: '%s'\n", pt_name);
				goto spi_out;
			}
			start = info.start * info.blksz;
		} else {
			start = offset;
		}
		ret = mtd_read(mtd, start, read_bytes, &read, buff);
		if ((ret && ret != -EUCLEAN) || read != read_bytes) {
			printf("%s: read() failed for block at 0x%llx: %d\n",
			       mtd->name, start, ret);
			goto spi_out;
		}

spi_out:
		if (!IS_ERR_OR_NULL(mtd))
			put_mtd_device(mtd);

		break;
#endif

	case BOOT_TYPE_RAM:
		memcpy((void *)buff, (void *)(uintptr_t)offset, read_bytes);
		ret = 0;
		break;
	default:
		;
	}

	return ret;
}

static void *load_android_image(enum boot_type_t boot_type, const char *pt_name,
	u32 offset, unsigned char *buff)
{
	struct img_info *img_info;
	struct img_header *img_hdr;
	unsigned char *img_buff = buff + CUSTKEY_SIZE;
	u32 read_size, img_size;
	int ret = -1;

	read_image(boot_type, pt_name, offset, img_buff, MAX_PAGESIZE);

	img_info = (struct img_info *)img_buff;
	if (img_info->magic != IMG_INFO_MAGIC) {
		printf("ERROR: incorrect magic in image info  0x%08x\n", img_info->magic);
		return NULL;
	}

	/* find out boot image read size */
	img_size = img_info->image_size;
	img_size = ALIGN(img_size, 16);
	read_size = img_size + PREPEND_IMAGE_INFO_SIZE;

	/* check read size  */
	if (read_size > MAX_ANDROID_IMG_SIZE || read_size < MIN_ANDROID_IMG_SIZE) {
		printf("ERROR: img_size %u is invalid\n", read_size);
		return NULL;
	}

	read_image(boot_type, pt_name, offset, img_buff, read_size);
	img_hdr = (void *)(img_buff + PREPEND_IMAGE_INFO_SIZE);

	/* verify image */
	ret = tee_verify_image(5, (void *)img_hdr, img_size,
				(void *)img_hdr, img_size, IMAGE_TYPE_LINUX_KERNEL);
	if (ret <= 0) {
		printf("ERROR: Verify Linux Kernel image failed! ret=0x%x\n", ret);
		return NULL;
	}

	return (void *)img_hdr + GENX_IMAGE_HEADER_LINUX_SIZE;
}

static int boot_android_image(unsigned char *buff)
{
	int result = 0;
	u32 mkbootimg_page;
	andr_img_hdr *bootimg_hdr = (void *)buff;
	char cmd[32];

	if (strncmp((const char *)bootimg_hdr->magic, ANDR_BOOT_MAGIC, 8)) {
		printf("ERROR: Invalid mkbootimg header!\n");
		return -1;
	}

	/* update kernel address */
	bootimg_hdr->kernel_addr = LINUX_KERNEL_ADDR;

	mkbootimg_page = bootimg_hdr->page_size;
	struct img_header *gih = (struct img_header *)(buff + mkbootimg_page);

	/* find DTB and copy to dst memory */
	result = find_chunk(IMAGE_CHUNK_ID_LINUX_DTB, gih);
	if (result < 0) {
		printf("didn't find dtb!!!\n");
		return -1;
	}
	bootimg_hdr->second_addr = (u32)((uintptr_t)buff + mkbootimg_page + gih->chunk[result].offset);
	bootimg_hdr->second_size = gih->chunk[result].size;

	sprintf(cmd, "bootm %p", buff);
	run_command(cmd, 0);
	return 0;
}

static enum boot_type_t get_boot_type(const char *name)
{
	enum boot_type_t type = BOOT_TYPE_INVALID;

	if (!type)
		return BOOT_TYPE_INVALID;

	if (strcmp(name, "mmc") == 0)
		return BOOT_TYPE_MMC;

	if (strcmp(name, "spi") == 0)
		return BOOT_TYPE_SPI;

	if (strcmp(name, "ram") == 0)
		return BOOT_TYPE_RAM;

	return BOOT_TYPE_INVALID;
}

static int do_syna_boot(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	int ret = CMD_RET_USAGE;
	enum boot_type_t boot_type = BOOT_TYPE_INVALID;
	unsigned char *buff =  NULL;
	unsigned char *bootimg_hdr =  NULL;
	int ab_mode = BOOTSEL_INVALID;
	const char *pt_name = NULL;
	u32 try_ab = 0;
	u32 offset = 0;

	if (argc < 2)
		goto out;

	boot_type = get_boot_type(argv[1]);
	if (boot_type == BOOT_TYPE_INVALID)
		goto out;

	switch (boot_type) {
	case BOOT_TYPE_MMC:
		ab_mode = get_current_slot();
		if (ab_mode != BOOTSEL_A && ab_mode != BOOTSEL_B) {
			printf("No bootable slots found for image loading, spinning...!!\n");
			run_command("reset", 0);
		}
		pt_name = (ab_mode == BOOTSEL_A) ?  KERNEL_A_NAME : KERNEL_B_NAME;
		try_ab = 1;
		break;

	case BOOT_TYPE_SPI:
		if (argc == 2) {
			ab_mode = get_current_slot();
			if (ab_mode != BOOTSEL_A && ab_mode != BOOTSEL_B) {
				printf("No bootable slots found for image loading, spinning...!!\n");
				run_command("reset", 0);
			}
			pt_name = (ab_mode == BOOTSEL_A) ?  KERNEL_A_NAME : KERNEL_B_NAME;
			try_ab = 1;
		} else if (argc == 3) {
			offset = simple_strtoul(argv[2], NULL, 16);
		} else {
			goto out;
		}
		break;

	case BOOT_TYPE_RAM:
		if (argc != 3)
			goto out;

		offset = simple_strtoul(argv[2], NULL, 16);
		break;

	default:
		goto out;
	}

	/* reserve 1M for key */
	buff = malloc_ion_cacheable(MAX_ANDROID_IMG_SIZE + 0x100000);
	if (!buff)
		goto out;

retry_image_load:
	bootimg_hdr = load_android_image(boot_type, pt_name, offset, buff);
	if (!bootimg_hdr && try_ab) {
		if (try_abmode(ab_mode)) {
			printf("Invalid slot_%s boot image! reset to backup image...\n", ab_mode ? "b" : "a");
			run_command("reset", 0);
		} else {
			printf("Failed to load slot_%s boot image! Retry again...\n", ab_mode ? "b" : "a");
			goto retry_image_load;
		}
	}

	boot_android_image(bootimg_hdr);
	ret = 0;

out:
	if (buff)
		free_ion_cacheable(buff);

	return ret;
}

#ifdef CONFIG_CMD_SYNA_BOOTMMC
static int do_bootmmc(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	return run_command("syna_boot mmc", 0);
}
#endif

#ifdef CONFIG_CMD_SYNA_BOOTSPI
static int do_bootspi(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	char cmd[32];
	u32 spi_addr = DEFAULT_SPI_ADDR;

	if (argc == 2) {
		spi_addr = simple_strtoul(argv[1], NULL, 16);
		snprintf(cmd, sizeof(cmd), "syna_boot spi 0x%x", spi_addr ? spi_addr : DEFAULT_SPI_ADDR);
	} else {
		snprintf(cmd, sizeof(cmd), "syna_boot spi");
	}

	return run_command(cmd, 0);
}
#endif

static int do_bootram(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	char cmd[32];
	u32 ram_addr = CONFIG_SYS_LOAD_ADDR;

	if (argc == 2)
		ram_addr = simple_strtoul(argv[1], NULL, 16);

	snprintf(cmd, sizeof(cmd), "syna_boot ram 0x%x", ram_addr ? ram_addr : CONFIG_SYS_LOAD_ADDR);
	return run_command(cmd, 0);
}

#ifdef CONFIG_CMD_SYNA_BOOTMMC
U_BOOT_CMD(
	bootmmc, 1, 0, do_bootmmc,
	"u-boot boot linux from mmc\n",
	""
);
#endif

#ifdef CONFIG_CMD_SYNA_BOOTSPI
U_BOOT_CMD(
	bootspi, 1, 0, do_bootspi,
	"u-boot boot linux from SPI\n",
	""
);
#endif

U_BOOT_CMD(
	bootram, 2, 0, do_bootram,
	"u-boot boot linux from RAM\n",
	""
);

U_BOOT_CMD(
	syna_boot, 3, 0, do_syna_boot,
	"Syna u-boot boot linux\n",
	"mmc\n"
	"syna_boot spi/ram offset\n"
);

