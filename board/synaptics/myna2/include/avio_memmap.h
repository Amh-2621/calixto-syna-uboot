/* SPDX-License-Identifier: GPL-2.0+ */
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

#ifndef avio_memmap_h
#define avio_memmap_h () {}

#include "ctypes.h"

#pragma pack(1)
#ifdef __cplusplus
  extern "C" {
#endif

#ifndef _DOCC_H_BITOPS_
#define _DOCC_H_BITOPS_ () {}

    #define _bSETMASK_(b)                                      ((b) < 32 ? (1 << ((b) & 31)) : 0)
    #define _NSETMASK_(msb, lsb)                                (_bSETMASK_((msb) + 1) - _bSETMASK_(lsb))
    #define _bCLRMASK_(b)                                      (~_bSETMASK_(b))
    #define _NCLRMASK_(msb, lsb)                                (~_NSETMASK_(msb, lsb))
    #define _BFGET_(r, msb, lsb)                                 (_NSETMASK_((msb) - (lsb), 0) & ((r) >> (lsb)))
    #define _BFSET_(r, msb, lsb, v)                               do { (r) &= _NCLRMASK_(msb, lsb); (r) |= _NSETMASK_(msb, lsb) & ((v) << (lsb)); } while (0)

#endif

//////
///
/// $INTERFACE AVIO_MEMMAP                              (4,4)
///     # # ----------------------------------------------------------
///               : AIO64B_DHUB_REG_BASE 0x0
///                            ###
///                            * Base address of AIO 64bit DHUB control Registers
///                            * 128 KB
///                            ###
///               : AIO64B_DHUB_REG_SIZE 0x20000
///                            ###
///                            * Size of AIO 64bit DHUB Registers memory mapping
///                            ###
///               : AIO64B_DHUB_REG_DEC_BIT 0x11
///                            ###
///                            * 128 KB has a 17 bits offset
///                            ###
///               : AVIO_RESERVED0_REG_BASE 0x20000
///                            ###
///                            * 128 KB AVIO reserved space
///                            * 128 KB
///                            ###
///               : AVIO_RESERVED0_REG_SIZE 0x20000
///                            ###
///                            * Size of reserved0 registers
///                            ###
///               : AVIO_RESERVED0_REG_DEC_BIT 0x11
///                            ###
///                            * 128 KB has a 17 bits offset
///                            ###
///               : AVIO_RESERVED1_REG_BASE 0x40000
///                            ###
///                            * 32 KB space reserved
///                            * 32 KB
///                            ###
///               : AVIO_RESERVED1_REG_SIZE 0x8000
///                            ###
///                            * Size of reserved1 registers
///                            ###
///               : AVIO_RESERVED1_REG_DEC_BIT 0xF
///                            ###
///                            * 32 KB has a 15 bits offset
///                            ###
///               : AVIO_I2S_REG_BASE  0x48000
///                            ###
///                            * Base address for I2S Registers
///                            * 1 KB
///                            ###
///               : AVIO_I2S_REG_SIZE  0x400
///                            ###
///                            * Size of I2S Registers memory mapping
///                            ###
///               : AVIO_I2S_REG_DEC_BIT 0xA
///                            ###
///                            * 1 KB has a 10 bits offset
///                            ###
///               : AVIO_BCM_REG_BASE  0x48400
///                            ###
///                            * AVIO BCM Registers
///                            * 512 B
///                            ###
///               : AVIO_BCM_REG_SIZE  0x200
///                            ###
///                            * Size of AVIO BCM Registers
///                            ###
///               : AVIO_BCM_REG_DEC_BIT 0x9
///                            ###
///                            * 512 B has 9-bit offset
///                            ###
///               : AVIO_GBL_BASE      0x48600
///                            ###
///                            * Base address for AVIO Global Registers
///                            * 128 B
///                            ###
///               : AVIO_GBL_SIZE      0x80
///                            ###
///                            * Size of AVIO Global Registers
///                            ###
///               : AVIO_GBL_DEC_BIT   0x7
///                            ###
///                            * 128 B has a 7-bit offset
///                            ###
///     # # ----------------------------------------------------------
/// $ENDOFINTERFACE  # size:       0B, bits:       0b, padding:     0B
////////////////////////////////////////////////////////////
#ifndef h_AVIO_MEMMAP
#define h_AVIO_MEMMAP () {}

    #define        AVIO_MEMMAP_VPP128B_DHUB_REG_BASE           0x0
    #define        AVIO_MEMMAP_VPP128B_DHUB_REG_SIZE           0x10000
    #define        AVIO_MEMMAP_VPP128B_DHUB_REG_DEC_BIT        0x10
    #define        AVIO_MEMMAP_AIO64B_DHUB_REG_BASE            0x10000
    #define        AVIO_MEMMAP_AIO64B_DHUB_REG_SIZE            0x10000
    #define        AVIO_MEMMAP_AIO64B_DHUB_REG_DEC_BIT         0x10
    #define        AVIO_MEMMAP_AVIO_LCDC1_REG_BASE             0x20000
    #define        AVIO_MEMMAP_AVIO_LCDC1_REG_SIZE             0x10000
    #define        AVIO_MEMMAP_AVIO_LCDC1_REG_DEC_BIT          0x10
    #define        AVIO_MEMMAP_AVIO_LCDC2_REG_BASE             0x40000
    #define        AVIO_MEMMAP_AVIO_LCDC2_REG_SIZE             0x10000
    #define        AVIO_MEMMAP_AVIO_LCDC2_REG_DEC_BIT          0x10
    #define        AVIO_MEMMAP_AVIO_GBL_BASE                   0x60000
    #define        AVIO_MEMMAP_AVIO_GBL_SIZE                   0x4000
    #define        AVIO_MEMMAP_AVIO_GBL_DEC_BIT                0xE
    #define        AVIO_MEMMAP_AVIO_DAIF_REG_BASE              0x64000
    #define        AVIO_MEMMAP_AVIO_DAIF_REG_SIZE              0x800
    #define        AVIO_MEMMAP_AVIO_DAIF_REG_DEC_BIT           0xB
    #define        AVIO_MEMMAP_AVIO_DRT_REG_BASE               0x64800
    #define        AVIO_MEMMAP_AVIO_DRT_REG_SIZE               0x200
    #define        AVIO_MEMMAP_AVIO_DRT_REG_DEC_BIT            0x9
    #define        AVIO_MEMMAP_AVIO_DCLS_REG_BASE              0x64C00
    #define        AVIO_MEMMAP_AVIO_DCLS_REG_SIZE              0x80
    #define        AVIO_MEMMAP_AVIO_DCLS_REG_DEC_BIT           0x7
    #define        AVIO_MEMMAP_AVIO_BCM_REG_BASE               0x65000
    #define        AVIO_MEMMAP_AVIO_BCM_REG_SIZE               0x200
    #define        AVIO_MEMMAP_AVIO_BCM_REG_DEC_BIT            0x9
    #define        AVIO_MEMMAP_AVIO_PTRACK1_REG_BASE           0x65400
    #define        AVIO_MEMMAP_AVIO_PTRACK1_REG_SIZE           0x100
    #define        AVIO_MEMMAP_AVIO_PTRACK1_REG_DEC_BIT        0x8
    #define        AVIO_MEMMAP_AVIO_PTRACK2_REG_BASE           0x65800
    #define        AVIO_MEMMAP_AVIO_PTRACK2_REG_SIZE           0x100
    #define        AVIO_MEMMAP_AVIO_PTRACK2_REG_DEC_BIT        0x8
    #define        AVIO_MEMMAP_AVIO_I2S_REG_BASE               0x65C00
    #define        AVIO_MEMMAP_AVIO_I2S_REG_SIZE               0x400
    #define        AVIO_MEMMAP_AVIO_I2S_REG_DEC_BIT            0xA
    #define        AVIO_MEMMAP_AVIO_RESERVED0_REG_BASE         0x80000
    #define        AVIO_MEMMAP_AVIO_RESERVED0_REG_SIZE         0x80000
    #define        AVIO_MEMMAP_AVIO_RESERVED0_REG_DEC_BIT      0x13
    #define        AVIO_MEMMAP_AVIO_RESERVED1_REG_BASE         0x100000
    #define        AVIO_MEMMAP_AVIO_RESERVED1_REG_SIZE         0x100000
    #define        AVIO_MEMMAP_AVIO_RESERVED1_REG_DEC_BIT      0x14
    ///////////////////////////////////////////////////////////

#endif
//////
/// ENDOFINTERFACE: AVIO_MEMMAP
////////////////////////////////////////////////////////////

#ifdef __cplusplus
  }
#endif
#pragma  pack()

#endif
//////
/// ENDOFFILE: avio_memmap.h
////////////////////////////////////////////////////////////

