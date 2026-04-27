/// SPDX-License-Identifier: GPL-2.0+
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

#include "avioDhub.h"
#include "Galois_memmap.h"
#include "avio_memmap.h"
#include "avio_dhub_cfg_prv.h"
#include "hal_dhub.h"

#define CPUINDEX    0

typedef enum DHUB_128bBCM_TYPE_s {
	DHUB_128bBCM_TYPE_64b,
	DHUB_128bBCM_TYPE_128b,
} DHUB_128bBCM_TYPE;

typedef enum _DHUB_TYPE_ {
	DHUB_TYPE_64BIT,
	DHUB_TYPE_128BIT,
} DHUB_TYPE;

typedef enum _DHUB_ID_ {
	DHUB_ID_AG_DHUB,
	DHUB_ID_VPP_DHUB,
	DHUB_ID_VIP_DHUB,
	DHUB_ID_AIP_DHUB,
	DHUB_ID_MAX,
} DHUB_ID;

HDL_dhub2d AG_dhubHandle;
HDL_dhub2d VPP_dhubHandle;

/*Total size vpp128bDhub_BANK0_SIZE 0x5A00 = 23040*/
#define AVIO_DHUB_MV_R0_SIZE       (10752)
#define AVIO_DHUB_MV_R1_SIZE       (10752)

#define AVIO_DHUB_MV_R0_BASE       (VPP_DHUB_BANK0_START_ADDR)
#define AVIO_DHUB_MV_R1_BASE       (VPP_DHUB_BANK0_START_ADDR + AVIO_DHUB_MV_R0_SIZE)

DHUB_channel_config  LCDC_config[VPP_NUM_OF_CHANNELS] = {
    {avioDhubChMap_vpp128b_LCDC1_R, AVIO_DHUB_MV_R0_BASE,
		AVIO_DHUB_MV_R0_BASE+64, 64, (AVIO_DHUB_MV_R0_SIZE-64),
		dHubChannel_CFG_MTU_256byte, 1, 0, 1, 0xF, 0xF},

    {avioDhubChMap_vpp128b_LCDC2_R, AVIO_DHUB_MV_R1_BASE,
		AVIO_DHUB_MV_R1_BASE+64, 64, (AVIO_DHUB_MV_R1_SIZE-64),
		dHubChannel_CFG_MTU_256byte, 1, 0, 1, 0xF, 0xF},
};

DHUB_channel_config  AG_config[AG_NUM_OF_CHANNELS] = {
	// Bank0
	{avioDhubChMap_aio64b_I2S1_R, AIO_DHUB_I2S1_R_BASE,
		AIO_DHUB_I2S1_R_BASE+32, 32, (AIO_DHUB_I2S1_R_SIZE-32),
		dHubChannel_CFG_MTU_128byte, 0, 0, 1, 0xF, 0xF},

	{avioDhubChMap_aio64b_I2S1_W, AIO_DHUB_I2S1_W_BASE,
		AIO_DHUB_I2S1_W_BASE+64, 64, (AIO_DHUB_I2S1_W_SIZE-64),
		dHubChannel_CFG_MTU_128byte, 1, 0, 1, 0xF, 0xF},

	{avioDhubChMap_aio64b_I2S2_R, AIO_DHUB_I2S2_R_BASE,
		AIO_DHUB_I2S2_R_BASE+32, 32, (AIO_DHUB_I2S2_R_SIZE-32),
		dHubChannel_CFG_MTU_128byte, 0, 0, 1, 0xF, 0xF},

	{avioDhubChMap_aio64b_I2S2_W, AIO_DHUB_I2S2_W_BASE,
		AIO_DHUB_I2S2_W_BASE+32, 32, (AIO_DHUB_I2S2_W_SIZE-32),
		dHubChannel_CFG_MTU_128byte, 0, 0, 1, 0xF, 0xF},

	{avioDhubChMap_aio64b_I2S3_R, AIO_DHUB_I2S3_R_BASE,
		AIO_DHUB_I2S3_R_BASE+32, 32, (AIO_DHUB_I2S3_R_SIZE-32),
		dHubChannel_CFG_MTU_128byte, 0, 0, 1, 0xF, 0xF},

	{avioDhubChMap_aio64b_I2S3_W, AIO_DHUB_I2S3_W_BASE,
		AIO_DHUB_I2S3_W_BASE+32, 32, (AIO_DHUB_I2S3_W_SIZE-32),
		dHubChannel_CFG_MTU_128byte, 0, 0, 1, 0xF, 0xF},

	{avioDhubChMap_aio64b_I2S4_R, AIO_DHUB_I2S4_R_BASE,
		AIO_DHUB_I2S4_R_BASE+32, 32, (AIO_DHUB_I2S4_R_SIZE-32),
		dHubChannel_CFG_MTU_128byte, 0, 0, 1, 0xF, 0xF},

	{avioDhubChMap_aio64b_I2S4_W, AIO_DHUB_I2S4_W_BASE,
		AIO_DHUB_I2S4_W_BASE+32, 32, (AIO_DHUB_I2S4_W_SIZE-32),
		dHubChannel_CFG_MTU_128byte, 0, 0, 1, 0xF, 0xF},

	{avioDhubChMap_aio64b_BCM_R, AIO_DHUB_BCM_R_BASE,
		AIO_DHUB_BCM_R_BASE+128,  128, (AIO_DHUB_BCM_R_SIZE-128),
		dHubChannel_CFG_MTU_256byte, 0, 0, 1, 0xF, 0xF},

	{avioDhubChMap_aio64b_I2S5_R, AIO_DHUB_I2S5_R_BASE,
		AIO_DHUB_I2S5_R_BASE+32, 32, (AIO_DHUB_I2S5_R_SIZE-32),
		dHubChannel_CFG_MTU_128byte, 0, 0, 1, 0xF, 0xF},

	{avioDhubChMap_aio64b_I2S5_W, AIO_DHUB_I2S5_W_BASE,
		AIO_DHUB_I2S5_W_BASE+32, 32, (AIO_DHUB_I2S5_W_SIZE-32),
		dHubChannel_CFG_MTU_128byte, 0, 0, 1, 0xF, 0xF},

	{avioDhubChMap_aio64b_PDM_W, AIO_DHUB_PDM_W_BASE,
		AIO_DHUB_PDM_W_BASE+32,    32, (AIO_DHUB_PDM_W_SIZE-32),
		dHubChannel_CFG_MTU_128byte, 0, 0, 1, 0xF, 0xF},

	{avioDhubChMap_aio64b_PDM_R, AIO_DHUB_PDM_R_BASE,
		AIO_DHUB_PDM_R_BASE+32,  32, (AIO_DHUB_PDM_R_SIZE-32),
		dHubChannel_CFG_MTU_128byte, 0, 0, 1, 0xF, 0xF},

	{avioDhubChMap_aio64b_DCLASS_R, AIO_DHUB_DCLASS_R_BASE,
		AIO_DHUB_DCLASS_R_BASE+32, 32, (AIO_DHUB_DCLASS_R_SIZE-32),
		dHubChannel_CFG_MTU_128byte, 0, 0, 1, 0xF, 0xF},

	{avioDhubChMap_aio64b_DRT_R, AIO_DHUB_DRT_R_BASE,
		AIO_DHUB_DRT_R_BASE+32,    32, (AIO_DHUB_DRT_R_SIZE-32),
		dHubChannel_CFG_MTU_128byte, 0, 0, 1, 0xF, 0xF},

	{avioDhubChMap_aio64b_DRT_W, AIO_DHUB_DRT_W_BASE,
		AIO_DHUB_DRT_W_BASE+32,    32, (AIO_DHUB_DRT_W_SIZE-32),
		dHubChannel_CFG_MTU_128byte, 0, 0, 1, 0xF, 0xF},
};

int drv_dhub_initialize_dhub(void *h_dhub_ctx)
{
	DhubInitialization(CPUINDEX, VPP_DHUB_BASE, VPP_HBO_SRAM_BASE,
					&VPP_dhubHandle, LCDC_config,
					VPP_NUM_OF_CHANNELS, DHUB_TYPE_128BIT);

	DhubInitialization(CPUINDEX, AG_DHUB_BASE, AG_HBO_SRAM_BASE,
					&AG_dhubHandle, AG_config, AG_NUM_OF_CHANNELS,
					DHUB_TYPE_64BIT);

	return 0;
}

/******************************************************************************************************************
 *    Function: DhubInitialization
 *    Description: Initialize DHUB .
 *    Parameter : cpuId ------------- cpu ID
 *             dHubBaseAddr -------------  dHub Base address.
 *             hboSramAddr ----- Sram Address for HBO.
 *             pdhubHandle ----- pointer to 2D dhubHandle
 *             dhub_config ----- configuration of AG
 *             numOfChans     ----- number of channels
 *    Return:        void
******************************************************************************************************************/
void DhubInitialization(SIGN32 cpuId,
						UNSG32 dHubBaseAddr,
						UNSG32 hboSramAddr,
						HDL_dhub2d *pdhubHandle,
						DHUB_channel_config *dhub_config,
						SIGN32 numOfChans,
						DHUB_TYPE dHubType)
{
	HDL_semaphore *pSemHandle;
	SIGN32 i;
	SIGN32 chanId;
	SIGN32 cmdDiv = 8;

	if(dHubType==DHUB_TYPE_128BIT)
		cmdDiv = 16;
	else
		cmdDiv = 8;

	//Initialize HDL_dhub with a $dHub BIU instance.
	dhub2d_hdl(	hboSramAddr,			/*!	Base address of dHub.HBO SRAM !*/
				 dHubBaseAddr,			/*!	Base address of a BIU instance of $dHub !*/
				 pdhubHandle				/*!	Handle to HDL_dhub2d !*/
			);
	//set up semaphore to trigger cmd done interrupt
	//note that this set of semaphores are different from the HBO semaphores
	//the ID must match the dhub ID because they are hardwired.
	pSemHandle = dhub_semaphore(&pdhubHandle->dhub);

	for (i = 0; i< numOfChans; i++) {
		//Configurate a dHub channel
		//note that in this function, it also configured right HBO channels(cmdQ and dataQ) and semaphores
		chanId = dhub_config[i].chanId;
		{
			dhub_channel_cfg(
						&pdhubHandle->dhub,					/*!	Handle to HDL_dhub !*/
						chanId,						/*!	Channel ID in $dHubReg !*/
						dhub_config[i].chanCmdBase,		//UNSG32 baseCmd,	/*!	Channel FIFO base address (byte address) for cmdQ !*/
						dhub_config[i].chanDataBase,		//UNSG32 baseData,	/*!	Channel FIFO base address (byte address) for dataQ !*/
						dhub_config[i].chanCmdSize/cmdDiv,	//SIGN32		depthCmd,			/*!	Channel FIFO depth for cmdQ, in 64b word !*/
						dhub_config[i].chanDataSize/cmdDiv,	//SIGN32		depthData,			/*!	Channel FIFO depth for dataQ, in 64b word !*/
						dhub_config[i].chanMtuSize,						/*!	See 'dHubChannel.CFG.MTU', 0/1/2 for 8/32/128 bytes !*/
						dhub_config[i].chanQos,								/*!	See 'dHubChannel.CFG.QoS' !*/
						dhub_config[i].chanSelfLoop,								/*!	See 'dHubChannel.CFG.selfLoop' !*/
						dhub_config[i].chanEnable,								/*!	0 to disable, 1 to enable !*/
						0								/*!	Pass NULL to directly init dHub, or
															Pass non-zero to receive programming sequence
															in (adr,data) pairs
															!*/
						);
			// setup interrupt for channel chanId
			//configure the semaphore depth to be 1
			semaphore_cfg(pSemHandle, chanId, 1, 0);
		}
	}
}
