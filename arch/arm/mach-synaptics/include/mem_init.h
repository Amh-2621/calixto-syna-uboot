/* SPDX-License-Identifier: GPL-2.0+ */
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

#ifndef __MEM_INIT_H__
#define __MEM_INIT_H__

#define MAX_REGION_COUNT 16
#define MAX_SYSTEM_POOL_NUM 2

/* memory region */
struct mem_region {
	char			name[32];
	u32		base;	/* base address */
	u32		size;
	u32		attr;	/* attributes */
	u32		reserved;

	/* bellow fields are user defined data.
	 * it's to support multiple platforms by unified structure.
	 * different platform can use them for different purpose.
	 */
	u32		userdata[4];
};

struct mem_region *get_mem_region_list_from_tz(void);
int get_mem_region_count(void);
int get_mem_region_by_name(u64 *start, u64 *size, char *zone_name);
int get_system_mem(struct mem_region *system_mem, int *system_num);
int get_bl_mem(struct mem_region *bl_mem, int *bl_num);
int get_ion_mem(struct mem_region *ion_mem, int *ion_num);
int get_reserved_mem(struct mem_region *reserved_mem, int *reserved_num);
u32 get_cma_addr(void);
u32 get_cma_size(void);

void *malloc_ion_cacheable(int size);
void free_ion_cacheable(void *m);
void *malloc_ion_noncacheable(int size);
void free_ion_noncacheable(void *m);

#endif
