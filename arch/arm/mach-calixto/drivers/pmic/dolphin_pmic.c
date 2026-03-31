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

#include "pmic.h"

static struct leakage_table table_vcpu_h_step5000uv[] = {
	{	600,  990000},
	{	860,  950000},
	{	1120, 925000},
	{	1380, 915000},
	{	1640, 915000},
	{	1900, 900000},
	{	2160, 890000},
	{	2420, 875000},
	{	2680, 865000},
	{	3000, 865000},
	{	0xffff, 865000},
};

static struct leakage_table table_vcpu_l_step5000uv[] = {
	{	600,  890000},
	{	860,  850000},
	{	1120, 825000},
	{	1380, 815000},
	{	1640, 815000},
	{	1900, 800000},
	{	2160, 790000},
	{	2420, 775000},
	{	2680, 765000},
	{	3000, 765000},
	{	0xffff, 765000},
};

static struct freq_leakage_table l_table_vcpu_step5000uv[] = {
	//vl is at front and vh follows vl
	{1800, table_vcpu_l_step5000uv},
	{2100, table_vcpu_h_step5000uv},
	{0, NULL},
};

static struct leakage_table table_vcore_l_step5000uv[] = {
	{	600,  890000},
	{	860,  865000},
	{	1120, 850000},
	{	1380, 840000},
	{	1640, 825000},
	{	1900, 815000},
	{	2160, 815000},
	{	2420, 800000},
	{	2680, 790000},
	{	3000, 775000},
	{	0xffff, 775000},
};

static struct leakage_table table_vcore_h_step5000uv[] = {
	{	600,  915000},
	{	860,  900000},
	{	1120, 875000},
	{	1380, 865000},
	{	1640, 850000},
	{	1900, 850000},
	{	2160, 840000},
	{	2420, 825000},
	{	2680, 815000},
	{	3000, 800000},
	{	0xffff, 800000},
};

static struct freq_leakage_table l_table_vcore_step5000uv[] = {
	{900, table_vcore_l_step5000uv},
	{1100, table_vcore_h_step5000uv},
	{0, NULL},
};

struct freq_leakage_table *get_vcpu_leakage_table(void)
{
	return l_table_vcpu_step5000uv;
}

struct freq_leakage_table *get_vcore_leakage_table(void)
{
	return l_table_vcore_step5000uv;
}
