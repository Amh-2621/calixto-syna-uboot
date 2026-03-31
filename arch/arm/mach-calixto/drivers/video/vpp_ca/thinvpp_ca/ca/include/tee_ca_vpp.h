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

#ifndef _TEE_VPP_CA_H_
#define _TEE_VPP_CA_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "tee_ca_common.h"
#include "vpp_cmd.h"
#include "vpp_api.h"

int VppRegisterShm(unsigned int *PhyAddr, unsigned int Size);
int VppUnregisterShm(unsigned int *PhyAddr, unsigned int Size);
int VppInitialize(void);
void VppFinalize(void);

TAVPPPassShm *VppSelectPassShm(void);
int VppPassShm(unsigned int *PhyAddr, VPP_SHM_ID AddrId, unsigned int Size);
int VppPassVbufInfo(unsigned int *Vbuf, unsigned int VbufSize,
                         unsigned int *Clut, unsigned int ClutSize,
                         int PlaneID, int ClutValid, VPP_SHM_ID ShmID);
int VppInit(VPP_INIT_PARM *vpp_init_parm);
int VppCreate(void);
int VppReset(void);
int VppConfig(INT handle, const INT *pvinport_cfg, const INT *pdv_cfg,
		const INT *pzorder_cfg, const INT *pvoutport_cfg, const INT *pfeature_cfg);
int VppSetOutRes(int CpcbId, int ResId, int BitDepth);
int VppSetRefWin(int PlaneId, int WinX, int WinY, int WinW, int WinH);
int VppOpenDispWin(int PlaneId, int WinX, int WinY, int WinW, int WinH, int BgClr, int Alpha, int GlobalAlpha);
int VppChangeDispWin(int PlaneId, int WinX, int WinY, int WinW, int WinH, int BgClr, int Alpha, int GlobalAlpha);
int VppChangeDispWinFromISR(int PlaneId, int WinX, int WinY, int WinW, int WinH, int BgClr, int Alpha, int GlobalAlpha);
int VppSetDispMode(int PlaneId, int Mode);
int VppHdmiSetVidFmt(int ColorFmt, int BitDepth, int PixelRep);
int VppSetPlaneMute(int planeID, int mute);
int VppSetHdmiTxControl(int enable);
int VppPassVbufInfoPar(unsigned int *Vbuf, unsigned int VbufSize,
                         unsigned int *Clut, unsigned int ClutSize,
                         int PlaneID, int ClutValid, VPP_SHM_ID ShmID);
int VppRecycleFrame(int PlaneId);
int VppSetFormat(int handle, int cpcbID, VPP_DISP_OUT_PARAMS *pDispParams);
int VppInvokePassShm_Helper(void *pBuffer, VPP_SHM_ID shmCmdId, UINT32 sBufferSize);
int Vppstop(void);
int VppDestroy(void);
int VppIsrHandler(unsigned int MsgId, unsigned int IntSts);

int MV_VPPOBJ_Stop(int handle);
#ifdef __cplusplus
}
#endif

#endif /* _TEE_VPP_CA_H_ */
