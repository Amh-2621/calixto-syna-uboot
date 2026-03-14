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
#include <dm.h>
#include <asm/io.h>
#include <dm/pinctrl.h>
#include <dm/fdtaddr.h>
#include "pinctrl_syna.h"

#ifdef CONFIG_TARGET_PLATYPUS
#include "pinctrl_syna_platypus.h"
#endif

#ifdef CONFIG_TARGET_DOLPHIN
#include "pinctrl_syna_dolphin.h"
#endif

#ifdef CONFIG_TARGET_MYNA2
#include "pinctrl_syna_myna2.h"
#endif

static int syna_pinctrl_get_groups_count(struct udevice *dev)
{
	struct syna_pinctrl *pctrl = dev_get_priv(dev);

	return pctrl->desc->ngroups;
}

static const char *syna_pinctrl_get_group_name(struct udevice *dev,
					       u32 selector)
{
	struct syna_pinctrl *pctrl = dev_get_priv(dev);

	return pctrl->desc->groups[selector].name;
}

static int synaptics_pinmux_get_functions_count(struct udevice *dev)
{
	struct syna_pinctrl *pctrl = dev_get_priv(dev);

	return pctrl->nfuncs;
}

static const char *synaptics_pinmux_get_function_name(struct udevice *dev,
						      u32 selector)
{
	struct syna_pinctrl *pctrl = dev_get_priv(dev);

	return pctrl->funcs[selector].name;
}

static struct syna_desc_func *
syna_pinctrl_find_function_by_name(struct syna_pinctrl *pctrl,
				   const struct syna_desc_group *group,
				     const char *fname)
{
	struct syna_desc_func *function = group->funcs;

	while (function->name) {
		if (!strcmp(function->name, fname))
			return function;

		function++;
	}

	return NULL;
}

static int synaptics_pinmux_group_set(struct udevice *dev,
				      u32 group_selector,
				   u32 func_selector)
{
	struct syna_pinctrl *pctrl = dev_get_priv(dev);
	const struct syna_desc_group *group_desc = pctrl->desc->groups + group_selector;
	struct syna_pinctrl_func *func = pctrl->funcs + func_selector;
	struct syna_desc_func *function_desc =
		syna_pinctrl_find_function_by_name(pctrl, group_desc,
						   func->name);

	u32 mask, val;

	if (!function_desc)
		return -EINVAL;

	debug("%s: group=%d  func=%d\n", __func__, group_selector, func_selector);
	mask = GENMASK(group_desc->lsb + group_desc->bit_width - 1,
		       group_desc->lsb);
	val = function_desc->muxval << group_desc->lsb;

	fdt_addr_t addr = pctrl->base + group_desc->offset;

	debug("%s: base=%016llx  offset=%08x\n", __func__, pctrl->base, group_desc->offset);
	u32 data = readl(addr);

	debug("%s: readl  %016llx  %08x\n", __func__, addr, data);
	debug("%s: mask=%08x, val=%08x\n", __func__, mask, val);
	data &= ~mask;
	data |= val & mask;
	writel(data, addr);
	debug("%s: writel %016llx  %08x\n", __func__, addr, data);

	return 0;
}

static const struct pinctrl_ops syna_pinctrl_ops = {
	.get_groups_count = syna_pinctrl_get_groups_count,
	.get_group_name = syna_pinctrl_get_group_name,
	.get_functions_count = synaptics_pinmux_get_functions_count,
	.get_function_name = synaptics_pinmux_get_function_name,
	.pinmux_group_set = synaptics_pinmux_group_set,
	.set_state = pinctrl_generic_set_state,
};

static int syna_pinctrl_add_function(struct syna_pinctrl *pctrl,
				     const char *name)
{
	struct syna_pinctrl_func *function = pctrl->funcs;

	while (function->name) {
		if (!strcmp(function->name, name)) {
			function->ngroups++;
			return -EEXIST;
		}
		function++;
	}

	function->name = name;
	function->ngroups = 1;

	pctrl->nfuncs++;

	return 0;
}

static int syna_pinctrl_build_state(struct udevice *dev)
{
	struct syna_pinctrl *pctrl = dev_get_priv(dev);
	struct syna_desc_group const *desc_group;
	struct syna_desc_func const *desc_function;
	int i, max_funcs = 0;

	pctrl->nfuncs = 0;

	for (i = 0; i < pctrl->desc->ngroups; i++) {
		desc_group = pctrl->desc->groups + i;
		/* compute the maxiumum number of functions a group can have */
		max_funcs += 1 << (desc_group->bit_width + 1);
	}

	/* we will reallocate later */
	pctrl->funcs = malloc(max_funcs * sizeof(*pctrl->funcs));
	if (!pctrl->funcs)
		return -ENOMEM;
	memset(pctrl->funcs, 0, max_funcs * sizeof(*pctrl->funcs));

	/* register all functions */
	for (i = 0; i < pctrl->desc->ngroups; i++) {
		desc_group = pctrl->desc->groups + i;
		desc_function = desc_group->funcs;

		while (desc_function->name) {
			syna_pinctrl_add_function(pctrl, desc_function->name);
			desc_function++;
		}
	}

	/* map functions to theirs groups */
	for (i = 0; i < pctrl->desc->ngroups; i++) {
		desc_group = pctrl->desc->groups + i;
		desc_function = desc_group->funcs;

		while (desc_function->name) {
			struct syna_pinctrl_func
				*function = pctrl->funcs;
			const char **groups;
			bool found = false;

			while (function->name) {
				if (!strcmp(desc_function->name, function->name)) {
					found = true;
					break;
				}
				function++;
			}

			if (!found)
				return -EINVAL;

			if (!function->groups) {
				function->groups =
					malloc(function->ngroups * sizeof(char *));
				if (!function->groups)
					return -ENOMEM;
				memset(function->groups, 0, function->ngroups * sizeof(char *));
			}

			groups = function->groups;
			while (*groups)
				groups++;
			*groups = desc_group->name;

			desc_function++;
		}
	}

	return 0;
}

static int syna_pinctrl_probe(struct udevice *dev)
{
	struct syna_pinctrl *pctrl = dev_get_priv(dev);
	int ret;

	pctrl->base = devfdt_get_addr(dev);
	if (pctrl->base == FDT_ADDR_T_NONE)
		return -EINVAL;

	pctrl->dev = dev;
	pctrl->desc = (struct syna_pinctrl_desc *)dev_get_driver_data(dev);
	debug("%s:%s base=%016llx, desc=%p\n", __func__, dev->name, pctrl->base, pctrl->desc);
	ret = syna_pinctrl_build_state(dev);
	if (ret) {
		dev_err(dev, "cannot build driver state: %d\n", ret);
		return ret;
	}

	return 0;
}

static const struct udevice_id syna_pinctrl_match[] = {
#ifdef CONFIG_TARGET_PLATYPUS
	{	.compatible = "syna,platypus-soc-pinctrl",	.data = (ulong)&platypus_soc_pinctrl_data,},
	{	.compatible = "syna,platypus-avio-pinctrl", .data = (ulong)&platypus_avio_pinctrl_data,},
	{	.compatible = "syna,platypus-sysmgr-pinctrl", .data = (ulong)&platypus_sysmgr_pinctrl_data,},
#endif

#ifdef CONFIG_TARGET_DOLPHIN
	{	.compatible = "syna,dolphin-soc-pinctrl",	.data = (ulong)&dolphin_soc_pinctrl_data,},
	{	.compatible = "syna,dolphin-avio-pinctrl", .data = (ulong)&dolphin_avio_pinctrl_data,},
	{	.compatible = "syna,dolphin-sysmgr-pinctrl", .data = (ulong)&dolphin_sysmgr_pinctrl_data,},
#endif

#ifdef CONFIG_TARGET_MYNA2
	{	.compatible = "syna,myna2-soc-pinctrl", .data = (ulong)&myna2_soc_pinctrl_data,},
#endif
	{}
};

U_BOOT_DRIVER(syna_pinctrl) = {
	.name		= "syna-pinctrl",
	.id		= UCLASS_PINCTRL,
	.of_match	= syna_pinctrl_match,
	.ops		= &syna_pinctrl_ops,
	.probe		= syna_pinctrl_probe,
	.priv_auto_alloc_size = sizeof(struct syna_pinctrl),
};

