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

static struct leakage_table table_vcore_h[] = {
	{	200,  955000},
	{	300,  905000},
	{	400,  875000},
	{	500, 855000},
	{	600, 840000},
	{	0xffff, 825000},
};

static struct leakage_table table_vcore_l[] = {
	{	200,  880000},
	{	300,  830000},
	{	400,  800000},
	{	500, 780000},
	{	600, 765000},
	{	0xffff, 750000},
};

static struct freq_leakage_table l_table_vcore[] = {
	/* vl is at front */
	{1700, table_vcore_l},
	{1900, table_vcore_h},
	{0, NULL},
};

static struct freq_leakage_table *l_table_vcpu = l_table_vcore;

struct freq_leakage_table *get_vcpu_leakage_table(void)
{
	return l_table_vcpu;
}

struct freq_leakage_table *get_vcore_leakage_table(void)
{
	return l_table_vcore;
}
