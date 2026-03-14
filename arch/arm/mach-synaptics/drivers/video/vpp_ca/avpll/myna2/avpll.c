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

#include "avpll.h"
#include "diag_pll.h"

#define FRAC_BITS           24
#define FRAC_MASK           ((1<<FRAC_BITS) - 1)

#define FREQ_FACTOR         (1000)

#define VCO_HIGH_LIMIT      ((6000 * 1000 * 1000UL) / FREQ_FACTOR)
#define VCO_LOW_LIMIT       ((1200 * 1000 * 1000UL) / FREQ_FACTOR)
#define FRAC_MIN_FPFD       ((5 * 1000 * 1000UL) / FREQ_FACTOR)
#define FRAC_MAX_FPFD       ((7500 * 1000UL) / FREQ_FACTOR)

#define MAX_DP0             ((1 << 5) * 2)
#define MIN_DP0             2
#define MAX_DP0_S           (MAX_DP0 / 2)
#define MIN_DP0_S           (MIN_DP0 / 2)
#define MAX_DP1             7
#define MIN_DP1             1

#define MAX_DM              (1 << 6)
#define MAX_DN              (1 << 7)
#define DIVF_DEF_MULT       4
#define PARENT_RATE_KHZ     25000

extern int gcd(int a, int b);

#define dbg_printf      printf

int AVPLL_GetClkgenparams (int freq, int *Dm, int *Dn, double *Frac, int *Dp)
{
	int	dp0;
	unsigned int	dn, dm, gcdv;
	unsigned long	frac;
	unsigned long	vco;
	unsigned long	rate0 = freq * 2;
	unsigned long	parent_rate = PARENT_RATE_KHZ;

	dp0 = VCO_HIGH_LIMIT / rate0;
	if (dp0 > MAX_DP0_S)
		dp0 = MAX_DP0_S;

	vco = rate0 * dp0;
	dp0 = vco / rate0;

	if ((dp0 > MAX_DP0_S)) {
		dbg_printf("dp0 invalid \n");
		return -1;
	}

	/* try to let vco near the high limit */
	while ((dp0 <= (MAX_DP0_S / 2))
		&& (vco <= VCO_HIGH_LIMIT /2)) {
		vco *= 2;
	}

	/* caculate the dn, dm */
	gcdv = gcd(vco, parent_rate);
	dn = vco / gcdv;
	dm = parent_rate / gcdv * DIVF_DEF_MULT;
	frac = 0;

	/* If dn and dm are valid values, we don't use frac mode. */
	if ((dm > MAX_DM) || (dn > MAX_DN)) {
		/*
			* For frac mode, the FPFD is limited from 5M to 7.5M.
			* For 25M input, dm is only valid for 5 or 4, here we got
			* dm = parent / FRAC_MIN_FPFD.
			*/
		dm = parent_rate / FRAC_MIN_FPFD;
		if (((parent_rate / dm) >= FRAC_MAX_FPFD)
			|| (dm > MAX_DM)) {
			dbg_printf("dm invalid \n");
			return -1;
		}

		frac = (vco << FRAC_BITS) * dm / (DIVF_DEF_MULT * parent_rate);
		dn = frac >> FRAC_BITS;
		frac = frac & FRAC_MASK;
	}

	*Dm = dm-1;
	*Dn = dn-1;
	*Frac = frac;
	*Dp = dp0-1;

	return 0;
}

void AVPLL_SetClockGenericFreq(int src, unsigned int freq)
{
	APLLCFG_t apll_cfg;

	AVPLL_GetClkgenparams(freq,
						&apll_cfg.dm,
						&apll_cfg.dn,
						&apll_cfg.frac,
						&apll_cfg.dp);
	apll_cfg.dp1 = 0;

	diag_change_avpll(src, 0, 0, 0, 0, 0, 0, apll_cfg);
}