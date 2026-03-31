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

/*
 * (C) Copyright 2016
 * Marvell Semiconductor <www.marvell.com>
 * Written-by: Xiaoming Lu <xmlu@marvell.com>
 */

#include <common.h>
#include <malloc.h>
#include <fdtdec.h>
#include <asm/armv8/mmu.h>
#include <lmb.h>
#include "mem_init.h"

DECLARE_GLOBAL_DATA_PTR;

#define FDT_REG_SIZE  sizeof(u32)
struct dram_bank {
	phys_addr_t start;
	phys_size_t size;
};

__section(".data") static int bank_nr;

#define MAX_MM_REGION	4
__section(".data") static struct mm_region berlin_mem_map[MAX_MM_REGION];
struct mm_region *mem_map = berlin_mem_map;

int dram_init_banksize(void)
{
	int b;

	for (b = 0; b < bank_nr; b++) {
		gd->bd->bi_dram[b].start = mem_map[b].virt;
		gd->bd->bi_dram[b].size = mem_map[b].size;
		debug("Bank #%d: start %llx\n", b,
		      (unsigned long long)gd->bd->bi_dram[b].start);
		debug("Bank #%d: size %llx\n", b,
		      (unsigned long long)gd->bd->bi_dram[b].size);
	}

	return 0;
}

#if defined(CONFIG_SYNA_FASTBOOT) || defined(CONFIG_SYNA_SUBOOT)
void get_mem_from_tzk(void)
{
	u64 sys_base = 0, sys_size = 0;
	u64 ns_nc_base = 0, ns_nc_size = 0;
	u64 map_size = 0;
	u64 bl_base = 0, bl_size = 0;

	get_mem_region_by_name(&bl_base, &bl_size, "bootloader");
	get_mem_region_by_name(&sys_base, &sys_size, "system");
	get_mem_region_by_name(&ns_nc_base, &ns_nc_size, "NonSecure-NC");
	if (ns_nc_base == sys_base + sys_size) {
		map_size = sys_size + ns_nc_size;
	} else {
		map_size = sys_size;
		printf("NonSecure-NC memory pool doesn't next to system memory pool\n");
	}

	if (sys_size) {
		gd->ram_top = sys_base;
		gd->ram_base = sys_base;
		gd->ram_size = sys_size;
		bank_nr = 2;

		mem_map[0].virt = bl_base;
		mem_map[0].phys = bl_base;
		mem_map[0].size = bl_size;
		mem_map[0].attrs = PTE_BLOCK_MEMTYPE(MT_NORMAL) |
				   PTE_BLOCK_INNER_SHARE;

		mem_map[1].virt = sys_base;
		mem_map[1].phys = sys_base;
		mem_map[1].size = map_size;
		mem_map[1].attrs = PTE_BLOCK_MEMTYPE(MT_NORMAL) |
				   PTE_BLOCK_INNER_SHARE;

		mem_map[bank_nr].virt = 0xF0000000UL;
		mem_map[bank_nr].phys = 0xF0000000UL;
		mem_map[bank_nr].size = 0x10000000UL;
		mem_map[bank_nr].attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
					 PTE_BLOCK_NON_SHARE |
					 PTE_BLOCK_PXN | PTE_BLOCK_UXN;

		memset(&mem_map[bank_nr + 1], 0, sizeof(struct mm_region));
	} else {
		printf("Error: Doesn't get memory region from TZK!!\n");
	}
}
#else
int get_mem_from_fdt(void)
{
	int node, len;
	const void *blob = gd->fdt_blob;
	const u32 *cell;
	int i = 0, b, na, ns;
	u64 val;

	na = fdt_address_cells(blob, 0);
	ns = fdt_size_cells(blob, 0);

	/* find or create "/memory" node. */
	node = fdt_subnode_offset(blob, 0, "memory");
	if (node < 0) {
		printf("%s: Can't get memory node\n", __func__);
		return node;
	}

	/* Get pointer to cells and length of it */
	cell = fdt_getprop(blob, node, "reg", &len);
	if (!cell) {
		printf("%s: Can't get reg property\n", __func__);
		return -1;
	}

	bank_nr = len / FDT_REG_SIZE / (na + ns);

	if (bank_nr > MAX_MM_REGION - 2) {
		printf("bank_nr=%d is too large, please redefine MAX_MM_REGION\n", bank_nr);
		hang();
	}

	debug("%s: bank_nr=%d\n", __func__, bank_nr);

	for (b = 0; b < bank_nr; b++) {
		debug("%s: Bank #%d:\n", __func__, b);
		if (na == 2) {
			val = cell[i + 1];
			val <<= 32;
			val |= cell[i];
			val = fdt64_to_cpu(val);
			debug("%s: addr64=%llx, cell=%p\n",
			      __func__, val, &cell[i]);
			mem_map[b].phys = val;
		} else {
			debug("%s: addr32=%x\n",
			      __func__, fdt32_to_cpu(cell[i]));
			mem_map[b].phys = fdt32_to_cpu(cell[i]);
		}
		mem_map[b].virt = mem_map[b].phys;
		i += na;

		debug("%s: i=%x, size=%zu\n", __func__, i,
		      sizeof(phys_addr_t));

		if (ns == 2) {
			val = cell[i + 1];
			val <<= 32;
			val |= cell[i];
			val = fdt64_to_cpu(val);

			debug("%s: size64=%llx, cell=%p\n",
			      __func__, val, &cell[i]);
			mem_map[b].size = val;
		} else {
			debug("%s: size32=%x\n",
			      __func__, fdt32_to_cpu(cell[i]));
			mem_map[b].size = fdt32_to_cpu(cell[i]);
		}
		i += ns;
		mem_map[b].attrs = PTE_BLOCK_MEMTYPE(MT_NORMAL) |
				   PTE_BLOCK_INNER_SHARE;
		debug("%s: i=%x, size=%zu\n",
		      __func__, i, sizeof(phys_size_t));
	}

	mem_map[bank_nr].virt = 0xF0000000UL;
	mem_map[bank_nr].phys = 0xF0000000UL;
	mem_map[bank_nr].size = 0x10000000UL;
	mem_map[bank_nr].attrs = PTE_BLOCK_MEMTYPE(MT_DEVICE_NGNRNE) |
				 PTE_BLOCK_NON_SHARE |
				 PTE_BLOCK_PXN | PTE_BLOCK_UXN;

	memset(&mem_map[bank_nr + 1], 0, sizeof(struct mm_region));

	gd->ram_top = mem_map[0].virt;
	gd->ram_base = mem_map[0].phys;
	gd->ram_size = mem_map[bank_nr - 1].virt + mem_map[bank_nr - 1].size
		       - mem_map[0].virt;

	for (b = 0; b < bank_nr + 2; b++) {
		debug("BANK#%d:\n", b);
		debug("    virt = %016llx\n", mem_map[b].virt);
		debug("    phys = %016llx\n", mem_map[b].phys);
		debug("    size = %016llx\n", mem_map[b].size);
		debug("   attrs = %016llx\n", mem_map[b].attrs);
	}

	return 0;
}
#endif

int dram_init(void)
{
#if defined(CONFIG_SYNA_FASTBOOT) || defined(CONFIG_SYNA_SUBOOT)
	get_mem_from_tzk();
#else
	get_mem_from_fdt();
#endif

	debug("%s: Initial DRAM size %llx\n", __func__, (u64)gd->ram_size);

	return 0;
}

#ifdef CONFIG_LMB
void board_lmb_reserve(struct lmb *lmb)
{
	int i = 0;
	/* make none reserved region for we don't need this one */
	for (i = 0; i < lmb->reserved.cnt; i++)
		lmb_free(lmb, lmb->reserved.region[i].base, lmb->reserved.region[i].size);
}
#endif
