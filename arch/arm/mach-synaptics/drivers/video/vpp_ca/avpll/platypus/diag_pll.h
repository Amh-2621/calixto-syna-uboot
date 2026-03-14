/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Copyright (C) 2016~2024 Synaptics Incorporated. All rights reserved.
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

#ifndef DIAG_PLL_H
#define DIAG_PLL_H

#include <common.h>
#include <asm/io.h>
#include "Galois_memmap.h"
#include "global.h"
#include "cpu_wrp.h"
#include "mc_wrap.h"
#include "avioGbl.h"
#include "avio_memmap.h"

#define SYNA_CLK_READ32(addr, ptr_val) do {*ptr_val = readl((long)(addr));} while(0)
#define SYNA_CLK_WRITE32(addr, val) do {writel((val), (long)(addr));} while(0)

#define DOWN            1
#define UP              0

#define ENABLE          1
#define DISABLE         0

#define ABYPASS          1
#define DEABYPASS        0

#define BYPASS          1
#define UNBYPASS        0
#define ARESET          1
#define DEARESET        0

#define INT             0
#define FRACTION        1

#define DPONLY          1
#define ALL             0

// REF CLOCK divider, recommended value from ASIC Vinson as 1.
// FREF=25Mhz, FREF/Mint [1:100], FREF/Mfrac [10:100] ==> M [1:2]
// 1 is recommended by ASIC.
#define M1              1
#define M2              2
#define M4		4
#define M5		5
#define M6		6
#define FREF            25

#define VPLLWRAP0BASE_ADDR    	(MEMMAP_AVIO_REG_BASE+AVIO_MEMMAP_AVIO_GBL_BASE+RA_avioGbl_VPLL_WRAP0)
//#define VPLLWRAP1BASE_ADDR    	(MEMMAP_AVIO_REG_BASE+AVIO_MEMMAP_AVIO_GBL_BASE+RA_avioGbl_VPLL_WRAP1)
#define APLLWRAP0BASE_ADDR    	(MEMMAP_AVIO_REG_BASE+AVIO_MEMMAP_AVIO_GBL_BASE+RA_avioGbl_APLL_WRAP0)
#define APLLWRAP1BASE_ADDR    	(MEMMAP_AVIO_REG_BASE+AVIO_MEMMAP_AVIO_GBL_BASE+RA_avioGbl_APLL_WRAP1)

#define APLLWRAP0APLLCTRL     	APLLWRAP0BASE_ADDR + RA_APLL_WRAP_APLL_CTRL
#define APLLWRAP1APLLCTRL     	APLLWRAP1BASE_ADDR + RA_APLL_WRAP_APLL_CTRL
#define APLLWRAP0APLL     	APLLWRAP0BASE_ADDR + RA_APLL_WRAP_APLL
#define APLLWRAP1APLL     	APLLWRAP1BASE_ADDR + RA_APLL_WRAP_APLL

#define VPLLWRAP0VPLLCTRL     	VPLLWRAP0BASE_ADDR + RA_VPLL_WRAP_VPLL_CTRL
//#define VPLLWRAP1VPLLCTRL     	VPLLWRAP1BASE_ADDR + RA_VPLL_WRAP_VPLL_CTRL
#define VPLLWRAP0VPLL     	VPLLWRAP0BASE_ADDR + RA_VPLL_WRAP_VPLL
//#define VPLLWRAP1VPLL     	VPLLWRAP1BASE_ADDR + RA_VPLL_WRAP_VPLL


//#define APLL_CLKEN_ADDR   (MEMMAP_AVIO_REG_BASE+AVIO_MEMMAP_AVIO_GBL_BASE+RA_avioGbl_AVPLLA_CLK_EN)
//#define APLL_SWRST_ADDR   (MEMMAP_AVIO_REG_BASE+AVIO_MEMMAP_AVIO_GBL_BASE+RA_avioGbl_SWRST_CTRL)
#define AVPLL_SWPD_ADDR    (MEMMAP_AVIO_REG_BASE+AVIO_MEMMAP_AVIO_GBL_BASE+RA_avioGbl_AVPLL_CTRL0)

enum PLLMODE {
	INT_MODE=0,
	FRAC_MODE,
	SSC_MODE,
	RSVD
};

#define PLL_REG_SET(tmpstr, field123, val123)     tmpstr.uctrl##field123 = val123
#define PLL_REG_GET(tmpstr, field123, val123)     val123 = tmpstr.uctrl##field123

#define PLL_REG_READ(baseaddr, offset, val123)                                          \
	do{ 															\
		val123 = readl((long)(baseaddr+offset*4));			\
	}while(0)

#define PLL_REG_WRITE(baseaddr, offset, val123)                                         \
	do{ 															\
		writel(val123, (long)(baseaddr+offset*4));			\
	}while(0)

#define PLL_REG_PRINT(baseaddr, offset)                                                 \
	do{ 															\
		volatile unsigned int val123;								\
		val123 = readl((long)(baseaddr+offset*4));		  \
		debug("0x%08x: 0x%08x\n",							  \
				(baseaddr+offset*4),								\
				val123);											\
	}while(0)
#define SSC_DIV_MAX		15

typedef enum {
	DIAG_SYSPLL0=0,
	DIAG_SYSPLL1,
	DIAG_SYSPLL2,
	DIAG_MEMPLL,
	DIAG_CPUPLL,
	DIAG_VPLL0,
	DIAG_APLL0,
	DIAG_APLL1,
	DIAG_SIPLL,
	DIAG_AVPLL,
	DIAG_SYSPLL
} E_PLL_SRC;

enum divider_index
{
	DIVIDED_BY_2 = 1,
	DIVIDED_BY_4,
	DIVIDED_BY_6,
	DIVIDED_BY_8,
	DIVIDED_BY_12
};

typedef struct {
	int clocko;
	int clocko1;
} CLOCKO_t;

typedef struct {
	unsigned int dm;
	unsigned int dn;
	unsigned int frac;
	unsigned int dp;
	unsigned int dp1;
} APLLCFG_t;

typedef struct {
	unsigned int ssc;
	unsigned int freq;
	unsigned int amp;
} SSC_t;

typedef struct {
	int div;
	int val;
} ssc_div_t;

int diag_change_avpll(unsigned int apll_index, unsigned int freq,
		      unsigned int ssc, unsigned int ssc_freq,
		      unsigned int ssc_amp, unsigned int ssc_mode,
		      unsigned int calc, APLLCFG_t pll_cfg);

#endif
