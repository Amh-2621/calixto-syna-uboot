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
#include <console.h>
#include <dm.h>
#include <flash_ts.h>
#include <mmc.h>
#include <net.h>
#include "misc_syna.h"

DECLARE_GLOBAL_DATA_PTR;

#define BL_ARG_MAGIC 0xdeadbeaf
struct bl_boot_arg {
	unsigned long param[8];		// the first param is set to the address of bl_boot_arg.
	unsigned int flash_param[3];	// the original param
	unsigned int leakage;		// leakage id
	unsigned int chip_id[2];	// unique chip id
	unsigned int soc_tsen_id;	// soc tsen_id
	unsigned int cpu_tsen_id;	// cpu tsen_id
	unsigned int chip_revision;	// chip revision: Z1/A0/A1/A2
	u8 mac_addr[ARP_HLEN]; // MAC address
	int boot_slot;
};

static unsigned long param2_save = 0xFFFFFFFF;

int arch_misc_init(void)
{
	return 0;
}

void save_boot_params(unsigned long param1, unsigned long param2, unsigned long param3)
{
	if (param1 == BL_ARG_MAGIC)
		param2_save = param2;

	save_boot_params_ret();
}

int get_leakage(void)
{
	if (param2_save != 0xFFFFFFFF)
		return ((struct bl_boot_arg *)param2_save)->leakage;

	return -1;
}

int get_fe_bgs(void)
{
	if (param2_save != 0xFFFFFFFF)
		return ((struct bl_boot_arg *)param2_save)->param[0];

	return -1;
}

int get_mac(u8 *enetaddr)
{
	if (enetaddr != NULL && param2_save != 0xFFFFFFFF)
		memcpy(enetaddr, ((struct bl_boot_arg *)param2_save)->mac_addr, ARP_HLEN);

	return 0;
}

int get_boot_slot(void)
{
	if (param2_save != 0xFFFFFFFF)
		return ((struct bl_boot_arg *)param2_save)->boot_slot & 0x1;

	return -1;
}
