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

#ifndef _OSAL_API_H_
#define _OSAL_API_H_

#include "com_type.h"
#include "string.h"
#include <linux/types.h>

#define GaloisMemSet            memset
#define GaloisFree(x)            (void)0
#define GaloisMemcpy            memcpy
#define GaloisMemClear(buf, n)	memset((buf), 0, (n))
#define GaloisMemComp
#define MV_ASSERT(n)
#define ASSERT(x)
#define devmem_phy_to_virt(a) (a)

typedef UINT32    VPP_MEM_HANDLE;
typedef signed int HRESULT;
typedef void *MV_OSAL_HANDLE;
typedef MV_OSAL_HANDLE  *pMV_OSAL_HANDLE_MUTEX_t;
typedef MV_OSAL_HANDLE  MV_OSAL_HANDLE_MUTEX_t;
typedef UINT32                  AMP_SHM_HANDLE;
//typedef void *  VDEC_VID_BUF_DESC;
typedef char    CHAR;

void GaloisInit(void);
void * GaloisMalloc(unsigned int size);
void * VPP_ALLOC(unsigned int  uiSize);
void *VPP_ALLOC_ALLIGNED(unsigned int size, unsigned int alignment);
void * VPP_TZ_ALLOC(unsigned int  uiSize);

int VPP_GET_RSV_MEM_REGION(u64 *start, u64 *size);

#define MV_OSAL_Mutex_Create(...)      SUCCESS
#define AMP_SHM_GetVirtualAddress(...) SUCCESS
#define AMP_SHM_Release(...)
#define TEEC_RegisterSharedMemory(...)
#define TEEC_ReleaseSharedMemory(...)

#define TEEC_FinalizeContext(...)

#endif /* _OSAL_API_H_ */
