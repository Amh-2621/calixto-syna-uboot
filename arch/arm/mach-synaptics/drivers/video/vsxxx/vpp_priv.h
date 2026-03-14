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

#ifndef _VPP_PRIV_H
#define _VPP_PRIV_H

#include "common.h"
#include <dm.h>
#include "vpp_api.h"

#define	VPP_SUPPORT_SCALAR		1

typedef enum {
	DISPLAY_1,
	DISPLAY_2,
	MAX_NUM_DISPLAY
} ENUM_DISPLAY_ID;

int syna_get_display_modeinfo(struct berlin_fb_priv *priv, int *width,
			      int *height, int display, avio_fastlogo_info *dispinfo);

int MV_VPPOBJ_SetFormat(struct vpp_config_params *vpp_config_param);
int MV_VPPOBJ_Config_Display(struct vpp_config_params *vpp_config_param);
int MV_VPP_pushframe(VBUF_INFO *pVppBuf, INT planeID, int width, int height);
void MV_VPP_Enable_IRQ(void);
void MV_VPP_Disable_IRQ(void);
int MV_VPPOBJ_Mipi_LoadInfoTable(struct vpp_config_params *vpp_config_param);
void MV_VPPOBJ_DestroyDisplay(void);
void MV_VPP_Disable_IRQ(void);

#endif
