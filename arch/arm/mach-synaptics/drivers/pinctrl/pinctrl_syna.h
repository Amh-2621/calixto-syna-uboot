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

#ifndef __PINCTRL_SYNA_H
#define __PINCTRL_SYNA_H

struct syna_desc_func {
	const char	*name;
	u8		muxval;
};

struct syna_desc_group {
	const char			*name;
	u8				offset;
	u8				bit_width;
	u8				lsb;
	struct syna_desc_func	*funcs;
};

struct syna_pinctrl_desc {
	const struct syna_desc_group	*groups;
	u32				ngroups;
};

struct syna_pinctrl_func {
	const char	*name;
	const char	**groups;
	u32		ngroups;
};

#define SYNA_PINCTRL_GROUP(_name, _offset, _width, _lsb, ...)		\
	{								\
		.name = _name,						\
		.offset = _offset,					\
		.bit_width = _width,					\
		.lsb = _lsb,						\
		.funcs = (struct syna_desc_func[]){		\
			__VA_ARGS__, { } },				\
	}

#define SYNA_PINCTRL_FUNC(_muxval, _name)		\
	{						\
		.name = _name,				\
		.muxval = _muxval,			\
	}

#define SYNA_PINCTRL_FUNC_UNKNOWN		{}

struct syna_pinctrl {
	fdt_addr_t base;
	struct udevice *dev;
	const struct syna_pinctrl_desc *desc;
	struct syna_pinctrl_func *funcs;
	u32 nfuncs;
};

#endif /* __PINCTRL_SYNA_H */
