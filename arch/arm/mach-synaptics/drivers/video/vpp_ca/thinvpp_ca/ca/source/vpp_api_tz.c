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

////////////////////////////////////////////////////////////////////////////////
//! \file vpp_api_tz.c
//!
//! \brief VPP API wrapper for trust zone.
//!
////////////////////////////////////////////////////////////////////////////////

#include "common.h"
#include "vpp_api.h"
#include "tee_ca_vpp.h"
#include "vbuf.h"
#include "vdec_com.h"
#include "OSAL_api.h"

//Memory shared with TA, should be 4K aligned
#define PAGE_SIZE	0x1000

//VPP API SHM internal control data structure
typedef struct {
    AMP_SHM_HANDLE            hShm;       /* shm handle */
    UINT32                    *phy_addr;  /* shm physical addr */
    UINT32                    *vir_addr;  /* shm virtul addr */
    MV_OSAL_HANDLE_MUTEX_t     hLock;     /* Lock for shm */
} vpp_shm_t;

/***********************************************************
 * FUNCTION: initialize VPP module
 * PARAMS: none
 * RETURN: MV_VPP_OK - succeed
 *         MV_VPP_EBADCALL - function called previously
 **********************************************************/
INT MV_VPPOBJ_Init(VPP_INIT_PARM *vpp_init_parm)
{
#if defined (VPP_ENABLE_INTERNAL_MEM_MGR)

	AMP_SHM_HANDLE shmHandle;
	int result;
	u64 start, size;

	VppInitialize();

	//Pass the vpp/vpp_rsv region to TA for its exclusive use
	if (!VPP_GET_RSV_MEM_REGION(&start, &size)) {
		vpp_init_parm->uiShmPA = (UINT32)start;
		vpp_init_parm->uiShmSize = SHM_SHARE_SZ;
	} else {
		//vpp/vpp_rsv carveout does not exist, Then allocate from other carve-out
		shmHandle = VPP_ALLOC_ALLIGNED(SHM_SHARE_SZ, PAGE_SIZE);
		if (!shmHandle) {
			return MV_VPP_ENOMEM;
		}
		vpp_init_parm->uiShmPA = (UINT32)shmHandle;
		vpp_init_parm->uiShmSize = SHM_SHARE_SZ;
	}

#ifdef VPP_ENABLE_FLUSH_CACHE
	vpp_init_parm->iHDMIEnable = 1;
	vpp_init_parm->iVdacEnable = 1;
#endif //VPP_ENABLE_FLUSH_CACHE
#endif
	result = VppInit(vpp_init_parm);
	if (result != 0) {
		printf("vpp init fialed\n");
		return -ENODEV;
	}

	return (MV_VPP_OK);
}

/***********************************************
 * FUNCTION: create a VPP object
 * RETURN: MV_VPP_OK - succeed
 *         MV_VPP_EUNCONFIG - not initialized
 *         MV_VPP_ENODEV - no device
 *         MV_VPP_ENOMEM - no memory
 ***********************************************/
INT MV_VPPOBJ_Create(void)
{
    VppCreate();
    return MV_VPP_OK;
}

/***************************************
 * FUNCTION: VPP profile configuration
 * INPUT: NONE
 * RETURN: NONE
 **************************************/
INT MV_VPPOBJ_Config(INT handle,
                     const INT *pvinport_cfg,
                     const INT *pdv_cfg,
                     const INT *pzorder_cfg,
                     const INT *pvoutport_cfg,
                     const INT *pfeature_cfg)
{
	return VppConfig(handle, pvinport_cfg, pdv_cfg, pzorder_cfg, pvoutport_cfg, pfeature_cfg);
}

/*******************************************************************
 * FUNCTION: set CPCB or DV output resolution
 * INPUT: cpcbID - CPCB(for Berlin) or DV(for Galois) id
 *        resID - id of output resolution
 *        bit_depth - HDMI deep color bit depth
 * RETURN: MV_VPP_OK - SUCCEED
 *         MV_EBADPARAM - invalid parameters
 *         MV_EUNCONFIG - VPP not configured or plane not active
 *         MV_EFRAMEQFULL - frame queue is full
 * Note: this function has to be called before enabling a plane
 *       which belongs to that CPCB or DV.
 *******************************************************************/
INT MV_VPPOBJ_SetCPCBOutputResolution(INT handle,
                                      INT cpcbID,
                                      INT resID,
                                      INT bit_depth)
{
    HRESULT Ret = MV_VPP_OK;

    Ret = VppSetOutRes(cpcbID, resID, bit_depth);

    return (Ret);
}

/********************************************************************************
 * FUNCTION: Set Hdmi Video format
 * INPUT: color_fmt - color format (RGB, YCbCr 444, 422)
 *      : bit_depth - 8/10/12 bit color
 *      : pixel_rept - 1/2/4 repetitions of pixel
 * RETURN: MV_VPP_OK - SUCCEED
 *         MV_EBADPARAM - invalid parameters
 *         MV_EUNCONFIG - VPP not configured
 *         MV_VPP_ENODEV - no device
 *         MV_EUNSUPPORT - channel not connected in configuration
 *         MV_VPP_EBADCALL - channel not connected to DV1
 *         MV_ECMDQFULL - command queue is full
 ********************************************************************************/
INT MV_VPPOBJ_SetHdmiVideoFmt(INT handle, INT color_fmt, INT bit_depth, INT pixel_rept)
{
    return VppHdmiSetVidFmt(color_fmt, bit_depth, pixel_rept);
}

/********************************************************************************
 * FUNCTION: Set Hdmi Tx control
 * RETURN: MV_VPP_OK - SUCCEED
 *         MV_EBADPARAM - invalid parameters
 *         MV_EUNCONFIG - VPP not configured
 *         MV_VPP_ENODEV - no device
 *         MV_EUNSUPPORT - channel not connected in configuration
 *         MV_VPP_EBADCALL - channel not connected to DV1
 *         MV_ECMDQFULL - command queue is full
 ********************************************************************************/
INT MV_VPPOBJ_SetHdmiTxControl(VOID)
{
    return VppSetHdmiTxControl(1);
}

/******************************************************************************
 * FUNCTION: open a window of a video/graphics plane for display.
 *           the window is defined in end display resolution
 * INPUT: planeID - id of a video/grahpics plane
 *        *win - pointer to a vpp window struct
 *        *attr - pointer to a vpp window attribute struct
 * RETURN: MV_VPP_OK - SUCCEED
 *         MV_EBADPARAM - invalid parameters
 *         MV_EUNCONFIG - VPP not configured
 *         MV_EUNSUPPORT - plane not connected in configuration
 *         MV_ECMDQFULL - command queue is full
 ******************************************************************************/
INT MV_VPPOBJ_OpenDispWindow(INT handle,
                             INT planeID,
                             VPP_WIN *win,
                             VPP_WIN_ATTR *attr)
{
    HRESULT Ret = MV_VPP_OK;
    int params[8];

    if (!win)
        return (MV_VPP_EBADPARAM);

    if ((win->width<=0) || (win->height<=0))
        return (MV_VPP_EBADPARAM);

    params[0] = planeID;
    params[1] = win->x;
    params[2] = win->y;
    params[3] = win->width;
    params[4] = win->height;

    /* set video plane background window */
    if (attr) {
        params[5] = attr->bgcolor;
        params[6] = attr->alpha;
        params[7] = attr->globalAlphaFlag;
    } else {
        params[5] = -1;
        params[6] = -1;
        params[7] = -1;
    }

    Ret = VppOpenDispWin(params[0],
                   params[1],
                   params[2],
                   params[3],
                   params[4],
                   params[5],
                   params[6],
                   params[7]);

    return (Ret);
}

/*******************************************************************
 * FUNCTION: set display mode for a plane
 * INPUT: planeID - id of the plane
 *        mode - DISP_STILL_PIC: still picture, DISP_FRAME: frame
 * RETURN: MV_VPP_OK - SUCCEED
 *         MV_EBADPARAM - invalid parameters
 *         MV_EUNCONFIG - VPP not configured or plane not active
 *         MV_EFRAMEQFULL - frame queue is full
 *******************************************************************/
INT MV_VPPOBJ_SetDisplayMode(INT handle, INT planeID, INT mode)
{
    return VppSetDispMode(planeID, mode);
}

/*******************************************************************
 * FUNCTION: display a frame for a plane
 * INPUT: planeID - id of the plane
 *        *frame - frame descriptor
 * RETURN: MV_VPP_OK - SUCCEED
 *         MV_EBADPARAM - invalid parameters
 *         MV_EUNCONFIG - VPP not configured or plane not active
 *         MV_EFRAMEQFULL - frame queue is full
 *******************************************************************/
INT MV_VPPOBJ_DisplayFrame(INT handle, INT planeID, VOID *frame)
{
	VBUF_INFO *pVBufInfo,*pElInfo = NULL;
	INT ret, DolbyValid = 0;
	pVBufInfo = (VBUF_INFO *)frame;

#if CONFIG_MV_AMP_TEE_ENABLE
	pVBufInfo->m_hDesc = (intptr_t)frame;
#endif

	debug("%s:%d: m_is_compressed:%p, m_primaries:%p m_iDisplayOETF:%p m_vitmyuvRangeIn:%p"
		"m_thdr_present_mode:%p, m_dv_status:%p, m_sar_height:%p, m_pbuf_start = 0x%p\n",
		__func__, __LINE__, &(pVBufInfo->m_is_compressed),
		&(pVBufInfo->m_primaries), &(pVBufInfo->m_iDisplayOETF),
		&(pVBufInfo->m_vitmyuvRangeIn), &(pVBufInfo->m_thdr_present_mode),
		&(pVBufInfo->m_dv_status), &(pVBufInfo->m_sar_height),
		(pVBufInfo->m_pbuf_start));

	/* pass frame info */
	ret = VppPassVbufInfo((UINT32 *)pVBufInfo, sizeof(VBUF_INFO),
			(UINT32 *)pElInfo,sizeof(VBUF_INFO),
			planeID, DolbyValid, DISPLAY_FRAME);
	if (ret != 0) {
		debug("VppPassVbufInfo failed\n");
		return ret;
	}

	return (MV_VPP_OK);
}

/***************************************************************
 * FUNCTION: set the reference window for a plane
 * INPUT: planeID - id of the plane
 *        *win - pointer to the reference window struct
 * RETURN: MV_VPP_OK - SUCCEED
 *         MV_EBADPARAM - invalid parameters
 *         MV_EUNCONFIG - VPP not configured
 *         MV_EUNSUPPORT - plane not connected in configuration
 *         MV_ECMDQFULL - command queue is full
 **************************************************************/
INT MV_VPPOBJ_SetRefWindow(INT handle, INT planeID, VPP_WIN *win)
{
	HRESULT Ret;

	Ret = VppSetRefWin(planeID, win->x, win->y, win->width, win->height);

	return (Ret);
}

/******************************************************************************
 * FUNCTION: change a window of a video/graphics plane.
 *           the window is defined in end display resolution
 * INPUT: planeID - id of a video/grahpics plane
 *        *win - pointer to a vpp window struct
 *        *attr - pointer to a vpp window attribute struct
 * RETURN: MV_VPP_OK - SUCCEED
 *         MV_EBADPARAM - invalid parameters
 *         MV_EUNCONFIG - VPP not configured
 *         MV_EUNSUPPORT - plane not connected in configuration
 *         MV_ECMDQFULL - command queue is full
 ******************************************************************************/
INT MV_VPPOBJ_ChangeDispWindow(INT handle,
        INT planeID,
        VPP_WIN *win,
        VPP_WIN_ATTR *attr)
{
	HRESULT Ret = MV_VPP_OK;
	int params[8];

	if((!win)&&(!attr))
		return MV_VPP_EBADPARAM;

	params[0] = planeID;

	if (win) {
		if ((win->width<=2) || (win->height<=2))
			return (MV_VPP_EBADPARAM);

		params[1] = win->x;
		params[2] = win->y;
		params[3] = win->width;
		params[4] = win->height;
	} else {
		params[1] = -1; /* no change */
		params[2] = -1;
		params[3] = -1;
		params[4] = -1;
	}
	if (attr) {
		params[5] = attr->bgcolor;
		params[6] = attr->alpha;
		params[7] = attr->globalAlphaFlag;
	} else {
		params[5] = -1; /* no change */
		params[6] = -1;
		params[7] = -1;
	}

	Ret = VppChangeDispWin(params[0],
			params[1],
			params[2],
			params[3],
			params[4],
			params[5],
			params[6],
			params[7]);

	return (Ret);
}

/***************************************************
 * FUNCTION: mute/un-mute a plane
 * PARAMS:  planeID - plane to mute/un-mute
 *          mute - 1: mute, 0: un-mute
 * RETURN: MV_VPP_OK - succeed
 *         MV_VPP_ENODEV - no device
 *         MV_EBADPARAM - invalid parameters
 *         MV_EUNCONFIG - VPP not configured
 ***********************************************/
INT MV_VPPOBJ_SetPlaneMute(INT handle, INT planeID, INT mute)
{
    return VppSetPlaneMute(planeID, mute);
}

/************************************************************************
 * FUNCTION: recycle plane frame descriptors
 * INPUT: planeID - id of the plane
 * RETURN: NULL - no frame descriptor for recycle
 *         other - pointer to frame descriptor being recycled
 ************************************************************************/
uintptr_t MV_VPPOBJ_RecycleFrames(int handle, int planeID)
{
    return (uintptr_t)VppRecycleFrame(planeID);
}

int MV_VPPOBJ_Stop(int handle)
{
    return Vppstop();
}

int MV_VPPOBJ_LoadMipiConfig(VPP_MIPI_LOAD_CONFIG *pConfigParams)
{
	if (!pConfigParams)
		return MV_VPP_EBADPARAM;

	return VppInvokePassShm_Helper(pConfigParams, VPP_MIPI_CONFIG,
					sizeof(VPP_MIPI_LOAD_CONFIG));
}

/***************************************
 * FUNCTION: VPP reset
 * INPUT: NONE
 * RETURN: NONE
 **************************************/
INT MV_VPPOBJ_Reset(void)
{
    return VppReset();
}

/***********************************************
 * FUNCTION: destroy a VPP object
 * PARAMS: handle - VPP object handle
 * RETURN: MV_VPP_OK - succeed
 *         MV_VPP_EUNCONFIG - not initialized
 *         MV_VPP_ENODEV - no device
 *         MV_VPP_ENOMEM - no memory
 ***********************************************/
INT MV_VPPOBJ_Destroy(INT handle)
{
    VppDestroy();

    return (MV_VPP_OK);
}

/***************************************************
 * FUNCTION: Get HDMI Sink Feature Map
 * PARAMS: handle - VPP object handle
 *         pSinkFeatureMap - pointer to HDMI sink capabilities structure
 * RETURN: MV_VPP_OK - succeed
 *         MV_VPP_ENODEV - no device
 *         MV_EBADPARAM - invalid parameters
 *         MV_EUNCONFIG - VPP not configured
 ***************************************************/
 INT MV_VPPOBJ_GetHDMISinkFeatureMap(INT handle, VPP_HDMI_SINK_CAPS *pSinkFeatureMap)
 {
	 if (!pSinkFeatureMap)
		 return MV_VPP_EBADPARAM;

	 return VppInvokePassShm_Helper(pSinkFeatureMap, GET_HDMI_SINKCAPS,
					 sizeof(VPP_HDMI_SINK_CAPS));
 }
