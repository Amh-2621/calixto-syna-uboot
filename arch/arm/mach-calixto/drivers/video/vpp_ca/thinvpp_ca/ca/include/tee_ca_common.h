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

#ifndef _TEE_COMMON_CA_H_
#define _TEE_COMMON_CA_H_

#include "tee_client_type.h"
#include "OSAL_api.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define TAVPP_PASS_SHMSIZE (1024*4)

#define VPP_PASS_SHM_LOCK(hLock)      do {                        \
        HRESULT ret;                                    \
        ret = MV_OSAL_Mutex_Lock(hLock);   \
        ASSERT(ret == SUCCESS);                         \
        (void)ret; \
    } while (0)

#define VPP_PASS_SHM_UNLOCK(hLock)    do {                      \
        HRESULT ret;                                    \
        ret = MV_OSAL_Mutex_Unlock(hLock); \
        ASSERT(ret == SUCCESS);                         \
        (void)ret; \
    } while (0)

#define VPP_TEEC_LOGIFERROR(result) \
        do { \
            if (result != TEEC_SUCCESS) \
                printf("TEEC Error ret=0x%08x\n", result); \
        } while (0)

typedef struct TAVPPPassShm_T{
    AMP_SHM_HANDLE              shm_handle;     /* shm handle */
    unsigned int                *phy_addr;      /* shm physical addr */
    unsigned int                *vir_addr;      /* shm virtul addr */
    MV_OSAL_HANDLE_MUTEX_t      lock_handle;    /* Lock for shm */
} TAVPPPassShm;

typedef struct TAVPPContext_T {
    bool                        initialized;
    TAVPPPassShm                shmContext;
    TEEC_Session                session;
} TAVPPContext;

enum{
    TAVPP_API_INSTANCE = 0,
    MAX_TAVPP_INSTANCE_NUM,
};

//TEEC_Session session;

#ifdef __cplusplus
}
#endif

#endif /* _TEE_VPP_CA_H_ */
