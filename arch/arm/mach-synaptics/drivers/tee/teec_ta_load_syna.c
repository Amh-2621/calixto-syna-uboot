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
#include <malloc.h>
#include <log.h>
#include "mmc.h"
#include "part.h"
#include "tee.h"
#include "genimg.h"
#include "misc_syna.h"
#include "fastboot_syna.h"

#define MISC_PT_NAME		"misc"
#define BOOTLOADERA_PT_NAME	"bl_a"
#define BOOTLOADERB_PT_NAME	"bl_b"

#define PRELOAD_TA_ALIGNMENT	(512)

static char *ta_buff;
static int ta_num;

static void read_preload_ta(void)
{
	struct blk_desc *dev_desc = NULL;
	disk_partition_t blinfo;
	int slot = -1;
	const char *slotname = NULL;

	void *buf = NULL;
	lbaint_t ta_start = 0;
	unsigned int ta_totalsize = 0;
	lbaint_t ta_rblk = 0;
	struct img_info *img_info = NULL;
	struct img_header *img_hdr = NULL;
	int mmc_dev = 0;

	if (ta_buff && (ta_num > 0))
		return;

	if (get_mmc_num() <= 0) {
		printf("No MMC device available %d\n", get_mmc_num());
		return;
	}

	mmc_dev = get_mmc_boot_dev();
	dev_desc = blk_get_dev("mmc", mmc_dev);
	if (!dev_desc) {
		printf("No MMC device available\n");
		return;
	}

	slot = get_current_slot();
	if (slot == BOOTSEL_INVALID) {
		printf("There is no available boot partition!\n");
		return;
	}

	slotname = slot ? BOOTLOADERB_PT_NAME : BOOTLOADERA_PT_NAME;

	if (blk_dselect_hwpart(dev_desc, get_mmc_part_by_name(mmc_dev, slotname))) {
		printf("Switch part fail\n");
		return;
	}

	if (!part_get_info_by_name(dev_desc, slotname, &blinfo)) {
		printf("Can't find bootloader partition!\n");
		return;
	}

	buf = malloc(dev_desc->blksz);
	if (!buf) {
		printf("no enough memory\n");
		return;
	}

	if (1 != blk_dread(dev_desc, blinfo.start, 1, buf)) {
		printf("fail to read image info!\n");
		free(buf);
		return;
	}

	img_info = (struct img_info *)buf;
	if (img_info->magic != IMG_INFO_MAGIC) {
		printf("is booltoader programmed?\n");
		free(buf);
		return;
	}

	ta_start = blinfo.start;
	ta_start += (img_info->image_offset + img_info->image_size
				+ PRELOAD_TA_ALIGNMENT - 1) / PRELOAD_TA_ALIGNMENT;

	if (1 != blk_dread(dev_desc, ta_start, 1, buf)) {
		printf("fail to read image header!\n");
		free(buf);
		return;
	}

	img_hdr = (struct img_header *)buf;
	if (img_hdr->header_magic_num != 0x482A4D49 || img_hdr->chunk_num <= 0) {
		printf("There is no preload TA.\n");
		free(buf);
		return;
	}

	ta_num = img_hdr->chunk_num;
	ta_totalsize = img_hdr->chunk[ta_num - 1].offset + img_hdr->chunk[ta_num - 1].size;
	ta_totalsize = (ta_totalsize + dev_desc->blksz - 1) & (~(dev_desc->blksz - 1));

	ta_rblk = ta_totalsize / dev_desc->blksz;

	/* the buf is not needed anymore */
	free(buf);

	ta_buff = malloc(ta_totalsize);
	if (!ta_buff) {
		printf("no enough memory\n");
		return;
	}

	if (ta_rblk != blk_dread(dev_desc, ta_start, ta_rblk, ta_buff)) {
		printf("fail to read TAs.\n");
		free(ta_buff);
		return;
	}
}

static unsigned int gen_id_from_uuid(const struct tee_optee_ta_uuid *destination)
{
	unsigned int id = 0;
	const char hex_asc[] = "0123456789ABCDEF";

	id = hex_asc[(destination->clock_seq_and_node[6] & 0xf0) >> 4];
	id |= hex_asc[(destination->clock_seq_and_node[6] & 0x0f)] << 8;
	id |= hex_asc[(destination->clock_seq_and_node[7] & 0xf0) >> 4] << 16;
	id |= hex_asc[(destination->clock_seq_and_node[7] & 0x0f)] << 24;

	return id;
}

int teeci_loadsecuremodule(const struct tee_optee_ta_uuid *destination, void *ta,
			   size_t *ta_size)
{
	int res = -1;
	struct img_header *img_hdr = NULL;
	unsigned int id = 0;
	int i = 0;

	read_preload_ta();

	if (ta_num <= 0 || !ta_buff)
		return res;

	/* All preload TAs are loaded. Let's find the called TA. */
	id = gen_id_from_uuid(destination);
	img_hdr = (struct img_header *)ta_buff;

	for (i = 0; i < ta_num; i++) {
		if (img_hdr->chunk[i].id == id) {
			*ta_size = img_hdr->chunk[i].size;
			if (ta) {
				memcpy(ta, (void *)(ta_buff + img_hdr->chunk[i].offset), img_hdr->chunk[i].size);
			}
			return 0;
		}
	}

	return res;
}
