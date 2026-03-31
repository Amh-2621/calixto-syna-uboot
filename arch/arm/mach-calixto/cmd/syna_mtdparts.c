// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (C) 2016~2024 Synaptics Incorporated. All rights reserved.
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
#include <linux/mtd/mtd.h>
#include <version_table.h>
#include "fastboot_syna.h"

#define CMD_MTD_PARTS_LEN 512
#define MTD_PART_LEN 64
#define KB 0x400
#define MB 0x100000
#define GB 0x40000000

#define MAX_VERSION_TABLE 32
#define CLEAR_VT_SIZE 2048
#define MAGIC_NUMBER           (0xD2ADA3F1)
#define CRC32_SIZE      (4)

#define SPI_VT_OFFSET 0x7F800
#define SPI_BOOT_PART_NUM 2
#define SPI_BOOT_PART_SIZE 0x200000

struct ver_table_t {
	int num;
	struct ver_table_entry_t vt[MAX_VERSION_TABLE];
	unsigned int dev_ids[MAX_VERSION_TABLE];
};

static struct ver_table_t vts;

static void dump_version_entry(struct ver_table_entry_t *vte)
{
	debug("%s: part1(start=%d, blks=%d, version=%08u%04u), part2(start=%d, blks=%d, version=%08u%04u)\n",
	      vte->name,
		vte->part1_start_blkind, vte->part1_blks,
		vte->part1_version.major_version, vte->part1_version.minor_version,
#ifdef CONFIG_EMMC_WRITE_PROTECT
		vte->part1_start_blkind, vte->part1_blks,
		vte->part1_version.major_version, vte->part1_version.minor_version);
#else
		vte->part2_start_blkind, vte->part2_blks,
		vte->part2_version.major_version, vte->part2_version.minor_version);
#endif
}

void dump_version_table(void)
{
	int i = 0;

	for (i = 0; i < vts.num; i++) {
		debug("[%02d,sd%02d] ", i, vts.dev_ids[i]);
		dump_version_entry(&vts.vt[i]);
	}
}

int parse_version_table(u8 *buff)
{
	unsigned int i;
	unsigned int dev_id = 0;

	unsigned int vt_size = 0;

	struct ver_table_entry_t *vt_entry;
	struct version_table_t *vt = (struct version_table_t *)(buff);

	vt_size = sizeof(struct version_table_t) +
		vt->num_entries * sizeof(struct ver_table_entry_t);

	/* check calculated version table size*/
	if (vt_size >= 2048) {
		debug("ERROR: vt_size is too big %d!!!\n", vt_size);
		return -2;
	}

	if (vt->magic != MAGIC_NUMBER ||
	    crc32(0, (unsigned char *)buff, vt_size + CRC32_SIZE) != 0xffffffff) {
		printf("MAGIC NUMBER or CRC error. %d\n", vt_size);
		return -2;
	}

	dev_id = 0;
	vts.num = 0;
	for (i = 0; i < vt->num_entries; i++) {
		vt_entry = &vt->table[i];

		memcpy(&vts.vt[i], vt_entry, sizeof(struct ver_table_entry_t));
		vts.dev_ids[i] = dev_id;
		vts.num++;
		dev_id++;
#ifdef CONFIG_EMMC_WRITE_PROTECT

#else
		if (vt_entry->part1_start_blkind != vt_entry->part2_start_blkind) {
			/* double copy of the partition */
			dev_id++;
		}
#endif
	}
	return 0;
}

static int get_partition_info(struct mtd_info *mtd)
{
	size_t read;
	int ret = -1, i = 0;
	u8 *buff = malloc(CLEAR_VT_SIZE);

	if (!buff)
		goto out;

	for (i = 0; i < SPI_BOOT_PART_NUM; i++) {
		ret = mtd_read(mtd, i * SPI_BOOT_PART_SIZE + SPI_VT_OFFSET, CLEAR_VT_SIZE, &read, buff);
		if (ret) {
			debug("read partition info error\n");
			continue;
		}

		ret = parse_version_table(buff);
		if (ret) {
			debug("parse partition info error\n");
			continue;
		}
		break;
	}

out:
	if (buff)
		free(buff);

	return ret;
}

static int get_mtd_parts(struct mtd_info *mtd)
{
	char cmd[CMD_MTD_PARTS_LEN];
	char part[64];
	u32 left = CMD_MTD_PARTS_LEN;
	u32 len = 0;
	u32 size;
	struct ver_table_entry_t *vte;
	int i;

	len = snprintf(cmd, left, "setenv mtdparts %s:", mtd->name);
	if (len < 0)
		return -1;
	left -= len;

	for (i = 0; i < vts.num; i++) {
		vte = &vts.vt[i];
		size = vte->part1_blks * mtd->erasesize;

		if (size >= GB && (size % GB == 0))
			len = snprintf(part, MTD_PART_LEN, "%dg(%s),", size / GB, vte->name);
		else if (size >= MB && (size % MB == 0))
			len = snprintf(part, MTD_PART_LEN, "%dm(%s),", size / MB, vte->name);
		else if (size >= KB && (size % KB == 0))
			len = snprintf(part, MTD_PART_LEN, "%dk(%s),", size / KB, vte->name);
		else
			return -1;

		if (len < 0)
			return -1;

		if (left > len)
			strcat(cmd, part);
		else
			return -1;

		left -= len;
	}

	return run_command(cmd, 0);
}

int syna_mtdparts_get_info_by_name(struct mtd_info *mtd, const char *name,
				   disk_partition_t *info)
{
	int i = 0;

	for (i = 0; i < vts.num; i++) {
		if (strcmp(name, vts.vt[i].name))
			continue;

		info->blksz = mtd->erasesize;
		info->start = vts.vt[i].part1_start_blkind;
		info->size = vts.vt[i].part1_blks;
		snprintf((char *)info->name, sizeof(info->name), "%s", vts.vt[i].name);
		strcpy((char *)info->type, "U-Boot");
		return 0;
	}

	return -1;
}

int syna_init_mtdparts(void)
{
	struct mtd_info *mtd = NULL;
	int ret = -1;

#ifdef CONFIG_SPI_FLASH_MTD
	/* setup spi device */
	fb_spi_setup_mtd_dev();

	mtd = get_mtd_device(NULL, 0);
#endif
	if (IS_ERR_OR_NULL(mtd))
		goto out;

	if (get_partition_info(mtd))
		goto out;

	if (get_mtd_parts(mtd))
		goto out;

	ret = 0;

out:
	if (!IS_ERR_OR_NULL(mtd))
		put_mtd_device(mtd);

	return ret;
}

static int do_syna_mtdparts(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	return syna_init_mtdparts();
}

U_BOOT_CMD(
		syna_mtdparts, 1, 0, do_syna_mtdparts,
		"Load MTD partition from flash",
		NULL
);
