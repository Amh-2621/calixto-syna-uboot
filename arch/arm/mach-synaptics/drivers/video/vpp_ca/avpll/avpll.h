// SPDX-License-Identifier: GPL-2.0+
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

#ifndef AVPLL_H
#define AVPLL_H

typedef struct __VPLL_CONFIG__ {
	float field_rate;
	int frame_rate_enum;
	int h_active;
	int v_active;
	int isInterlaced;
	int h_total;
	int v_total;
	float video_freq;
	float pixel_freq;
	int Dm;
	int Dn;
	float dummy;
	double frac;
	float vco_freq;
	int Dp;
	float vpll_freq;
	int vclk_div;
	float vclk;
} VPLL_CONFIG;

void AVPLL_SetClockFreqForResID(int resID);
int AVPLL_SetClockFreq(int avpllGroupId, int vco_freq_index,
		       unsigned int target_freq, int chId);
void AVPLL_Load_ResConfig(VPLL_CONFIG* vpllcfg);
int AVPLL_GetClkgenparams (int freq, int *Dm, int *Dn, double *Frac, int *Dp);
void AVPLL_SetClockGenericFreq(int src, unsigned int freq);

#endif
