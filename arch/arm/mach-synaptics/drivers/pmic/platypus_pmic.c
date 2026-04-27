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
	{	200,  975000},
	{	400,  950000},
	{	600,  900000},
	{	800,  875000},
	{	1000, 850000},
	{	1200, 825000},
	{	1400, 815000},
	{	0xffff, 815000},
};

static struct leakage_table table_vcpu_l_step5000uv[] = {
	{	200,  900000},
	{	400,  865000},
	{	600,  840000},
	{	800,  815000},
	{	1000, 800000},
	{	1200, 775000},
	{	1400, 765000},
	{	0xffff, 765000},
};

static struct freq_leakage_table l_table_vcpu_step5000uv[] = {
	//vl is at front and vh follows vl
	{1800, table_vcpu_l_step5000uv},
	{2000, table_vcpu_h_step5000uv},
	{0, NULL},
};

static struct leakage_table table_vcore_h_step5000uv[] = {
	{	200,  900000},
	{	400,  875000},
	{	600,  850000},
	{	800,  825000},
	{	1000, 800000},
	{	1200, 775000},
	{	1400, 765000},
	{	0xffff, 765000},
};

static struct leakage_table table_vcore_l_step5000uv[] = {
	{	200,  890000},
	{	400,  865000},
	{	600,  815000},
	{	800,  790000},
	{	1000, 765000},
	{	1200, 750000},
	{	1400, 740000},
	{	0xffff, 740000},
};

static struct freq_leakage_table l_table_vcore_step5000uv[] = {
	{700, table_vcore_l_step5000uv},
	{800, table_vcore_h_step5000uv},
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
