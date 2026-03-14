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
#include "mem_region_userdata.h"
#include "mem_init.h"
#include "mmgr.h"
#include "tee_client.h"

static struct mem_region mem[MAX_REGION_COUNT] __aligned(4096);
static int region_count;
static u32 cma_pool_start;
static u32 cma_pool_size;

#define CACHEABLE_MEM_POOL_SIZE (128 * 1024 * 1024)
void init_ion_cacheable_mempool(void)
{
	int i = 0;
	unsigned long mstart = 0;
	u32 size = 0;

	for (i = 0; i < region_count; i++) {
		if (TEE_MR_ION_FOR_NONSECURE(&mem[i]) && TEE_MR_ION_FOR_CACHEABLE(&mem[i])) {
			mstart = (unsigned long)(mem[i].base);
			size = mem[i].size;

			/* ION_CMA must be one of Non-secure and Cacheable pool, Usually it is the same pool */
			if (TEE_MR_ION_IS_CMA(&mem[i]) && TEE_MR_USER_IS_ION(&mem[i]) && size) {
				cma_pool_start = mem[i].base;
				cma_pool_size = mem[i].size;
			}

			debug("nonsecure cacheable memory region base = 0x%08lx\n", mstart);
			init_mmgr_by_type(MEM_ION_CACHEABLE, mstart, CACHEABLE_MEM_POOL_SIZE);
			if (size < CACHEABLE_MEM_POOL_SIZE)
				printf("nonsecure cacheable memory region size = 0x%08x\n", size);

			return;
		}
	}
	printf("cann't find non-secure ION cacheable memory!\n");
}

void init_ion_noncacheable_mempool(void)
{
	int i = 0;
	unsigned long mstart = 0;
	u32 size = 0;

	for (i = 0; i < region_count; i++) {
		if (TEE_MR_ION_FOR_NONSECURE(&mem[i]) && TEE_MR_ION_FOR_NONCACHEABLE(&mem[i])) {
			mstart = (unsigned long)(mem[i].base);
			size = mem[i].size;

			debug("nonsecure noncacheable memory region base = 0x%08lx\n", mstart);
			init_mmgr_by_type(MEM_ION_NONCACHEABLE, mstart, size);
			return;
		}
	}
	printf("cann't find non-secure ION noncacheable memory!\n");
}

struct mem_region *get_mem_region_list_from_tz(void)
{
	int i;
	struct mem_region *mem_r = (struct mem_region *)0x04600000;

	if (region_count > 0)
		return mem;

	region_count = tee_get_mem_region_list(mem_r, MAX_REGION_COUNT, 0, 0);

	memcpy(mem, mem_r, sizeof(struct mem_region) * region_count);

	for (i = 0; i < region_count; i++)
		debug("pool[%d]: name: %s, base =0x%08x, size = 0x%08x, attr = 0x%08x, userdata0 = 0x%08x\n",
		      i, mem[i].name, mem[i].base, mem[i].size, mem[i].attr, mem[i].userdata[0]);

	init_ion_cacheable_mempool();
	init_ion_noncacheable_mempool();

	if (region_count > 0)
		return mem;

	return NULL;
}

int get_mem_region_count(void)
{
	return region_count;
}

int get_mem_region_by_name(u64 *start, u64 *size, char *zone_name)
{
	u64 mem_base = 0, mem_size = 0;
	int region_count = 0;
	struct mem_region *mem_r = (struct mem_region *)0x04600000;

	region_count = tee_get_mem_region_list(mem_r, MAX_REGION_COUNT, 0, 0);
	for (int i = 0; i < region_count; i++) {
		if (!memcmp(mem_r[i].name, zone_name, strlen(zone_name))) {
			mem_base = mem_r[i].base;
			mem_size = mem_r[i].size;
			break;
		}
	}
	if (mem_size == 0) {
		printf("Error: %s (%s) fail\n", __func__, zone_name);
		return -1;
	}

	*start = mem_base;
	*size  = mem_size;

	return 0;
}

int get_system_mem(struct mem_region *system_mem, int *system_num)
{
	int i, num = 0;
	struct mem_region *mem = get_mem_region_list_from_tz();

	if (!mem)
		return -1;

	for (i = 0; i < region_count && num < MAX_SYSTEM_POOL_NUM; i++) {
		if (TEE_MR_USER_IS_SYSTEM(mem + i))
			memcpy(system_mem + num++, mem + i, sizeof(struct mem_region));
	}

	*system_num = num;
	return 0;
}

int get_bl_mem(struct mem_region *bl_mem, int *bl_num)
{
	int i, num = 0;
	struct mem_region *mem = get_mem_region_list_from_tz();

	if (!mem)
		return -1;

	for (i = 0; i < region_count; i++) {
		if (TEE_MR_USER_IS_BL(mem + i)) {
			memcpy(bl_mem + num++, mem + i, sizeof(struct mem_region));
			break;
		}
	}

	*bl_num = num;
	return 0;
}

int get_ion_mem(struct mem_region *ion_mem, int *ion_num)
{
	int i, num = 0;
	struct mem_region *mem = get_mem_region_list_from_tz();

	if (!mem)
		return -1;

	for (i = 0; i < region_count; i++) {
		if (TEE_MR_USER_IS_ION(mem + i) && !TEE_MR_ION_IS_CMA(mem + i))
			memcpy(ion_mem + num++, mem + i, sizeof(struct mem_region));
	}

	*ion_num = num;
	return 0;
}

int get_reserved_mem(struct mem_region *reserved_mem, int *reserved_num)
{
	int i, num = 0, system_num = 0;
	struct mem_region system_mem[MAX_SYSTEM_POOL_NUM];
	u32 sys_start = 0, sys_end = 0;

	*reserved_num = 0;
	memset(system_mem, 0x0, sizeof(system_mem));
	get_system_mem(system_mem, &system_num);
	if (system_num == 0)
		return 0;

	sys_start = system_mem[0].base;
	sys_end = system_mem[0].base + system_mem[0].size;

	struct mem_region *mem = get_mem_region_list_from_tz();

	if (!mem)
		return -1;

	for (i = 0; i < region_count; i++) {
		if (TEE_MR_ION_IS_CMA(mem + i) && TEE_MR_USER_IS_ION(mem + i))
			continue;

		/* Continue below reserve memory check for Non-CMA ION */
		/* Notice:
		 *     1. Only the first system is the case we handle.
		 *     2. ION regions should not have overlay with each other.
		 */
		if (TEE_MR_USER_IS_ION(mem + i)) {
			//ion is overlap with system, then set the reserved memory
			if (mem[i].base >= sys_start && mem[i].base < sys_end) {
				debug("memory layout find overlap, 0x%x, 0x%x, (0x%x:0x%x)\n",
					mem[i].base, mem[i].size, sys_start, sys_end);
				if (mem[i].size <= (sys_end - mem[i].base)) {
					reserved_mem[num].base = mem[i].base;
					reserved_mem[num].size = mem[i].size;
					num++;
				} else {
					printf("memory layout configuration error!!!\n");
				}
			}
		}
	}
	*reserved_num = num;

	return 0;
}

u32 get_cma_addr(void)
{
	return cma_pool_start;
}

u32 get_cma_size(void)
{
	return cma_pool_size;
}

void *malloc_ion_cacheable(int size)
{
	return mmgr_alloc_by_type(MEM_ION_CACHEABLE, size);
}

void free_ion_cacheable(void *m)
{
	mmgr_free_by_type(MEM_ION_CACHEABLE, m);
}

void *malloc_ion_noncacheable(int size)
{
	return mmgr_alloc_by_type(MEM_ION_NONCACHEABLE, size);
}

void free_ion_noncacheable(void *m)
{
	mmgr_free_by_type(MEM_ION_NONCACHEABLE, m);
}
