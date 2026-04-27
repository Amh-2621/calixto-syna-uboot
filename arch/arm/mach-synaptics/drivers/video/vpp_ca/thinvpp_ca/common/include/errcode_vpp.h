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

///////////////////////////////////////////////////////////////////////////////
//! \file errcode_vpp.h
//! \brief Header file for VPP error codes
///////////////////////////////////////////////////////////////////////////////

#ifndef _ERRCODE_VPP_H_
#define _ERRCODE_VPP_H_

#include "ErrorCode.h"

#define S_VPP( code ) ( E_SUC | E_VPP_BASE | ( (code) & 0xFFFF ) )
#define E_VPP( code ) ( E_ERR | E_VPP_BASE | ( (code) & 0xFFFF ) )

#define S_VPP_OK            (S_OK)

/* error code */
#define VPP_E_NODEV         E_VPP(1)
#define VPP_E_BADPARAM      E_VPP(2)
#define VPP_E_BADCALL       E_VPP(3)
#define VPP_E_UNSUPPORT     E_VPP(4)
#define VPP_E_IOFAIL        E_VPP(5)
#define VPP_E_UNCONFIG      E_VPP(6)
#define VPP_E_CMDQFULL      E_VPP(7)
#define VPP_E_FRAMEQFULL    E_VPP(8)
#define VPP_E_BCMBUFFULL    E_VPP(9)
#define VPP_E_NOMEM         E_VPP(10)
#define VPP_EVBIBUFFULL     E_VPP(11)
#define VPP_EHARDWAREBUSY   E_VPP(12)
#define VPP_ENOSINKCNCTED   E_VPP(13)
#define VPP_ENOHDCPENABLED  E_VPP(14)

#endif //!< #ifndef _ERRCODE_VPP_H_
