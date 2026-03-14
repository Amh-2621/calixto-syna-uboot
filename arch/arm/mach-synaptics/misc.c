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
#include <asm/io.h>
#include <mmc.h>
#include "Galois_memmap.h"
#include "global.h"
#include "misc_syna.h"
#include "fastboot_syna.h"

int get_mmc_boot_dev(void)
{
#ifdef CONFIG_SYNA_MMC_SUBOOT
	static int mmc_flash_dev = -1;
	u32 boot_strap, boot_source;

	if (mmc_flash_dev != -1)
		return mmc_flash_dev;

	boot_strap = __raw_readl(MEMMAP_CHIP_CTRL_REG_BASE + RA_Gbl_bootStrap);
	boot_source = (boot_strap & MSK32Gbl_bootStrap_bootSrc) >> LSb32Gbl_bootStrap_bootSrc;

	debug("\tboot_source: %d\n", boot_source);

	if (boot_source == Gbl_bootStrap_bootSrc_ROM_SPI_BOOT)
		mmc_flash_dev = DEV_SD; /* SPI-SD */
	else
		mmc_flash_dev = DEV_EMMC; /* eMMC */

	return mmc_flash_dev;
#else
	return DEV_EMMC;
#endif
}

int get_mmc_active_dev(void)
{
	char *s;
	int mmc_dev;

	s = env_get("mmc_dev");
	if (s)
		mmc_dev = !!((int)simple_strtol(s, NULL, 10));
	else
		mmc_dev = get_mmc_boot_dev();

	return mmc_dev;
}

uint32_t get_mmc_erased_mem_cont(int mmc_dev)
{
	struct mmc *mmc = NULL;

	if (mmc_dev == DEV_EMMC) {
		mmc = find_mmc_device(mmc_dev);
		if (!mmc)
			return 0xFFFFFFFF;

		if (mmc->ext_csd && mmc->ext_csd[181] == 0)
			return 0;
	}

	return 0xFFFFFFFF;
}

static int emmc_partition_type = -1;

int get_mmc_partition_type(int mmc_dev)
{
	struct blk_desc *dev_desc = NULL;
	char dev_hwpart_str[4];

	if (mmc_dev == DEV_EMMC) {
		if (emmc_partition_type >= 0)
			return emmc_partition_type;

		snprintf(dev_hwpart_str, 4, "%d.%d", mmc_dev, 4);
		blk_get_device_by_str("mmc", dev_hwpart_str, &dev_desc);
		if (dev_desc && dev_desc->type != DEV_TYPE_UNKNOWN) {
			f_mmc_save_part_table(mmc_dev);
			emmc_partition_type = EMMC_GPP_PARTITION;
		} else {
			emmc_partition_type = DEFAULT_PARTITION;
		}

		return emmc_partition_type;
	}

	return DEFAULT_PARTITION;
}

int get_mmc_part_by_name(int mmc_dev, const char *name)
{
	int ret = 0;

	if (name == NULL)
		return 0;

	if(strcmp(name, "bootloader") ==0 ||
		strcmp(name, "bootloader1") ==0)
		return 1;

	if(strcmp(name, "bootloader2") ==0)
		return 2;

	if (get_mmc_partition_type(mmc_dev) == DEFAULT_PARTITION)
		return 0;

	ret = f_mmc_get_hwpart_from_table(name);
	if (ret >= 0)
		return ret;

	return 0;
}

unsigned int get_max_malloc_size(void)
{
	unsigned int max_size = CONFIG_SYS_MALLOC_LEN;
	// depends on the heap size defined in config
	if (max_size > (1 << 30)) // > 1GB
		return (max_size - (100 << 20));
	if (max_size > (400 << 20)) // > 400MB
		return (max_size - (40 << 20));

	//don't hope to come here
	return (max_size - (10 << 20));
}
