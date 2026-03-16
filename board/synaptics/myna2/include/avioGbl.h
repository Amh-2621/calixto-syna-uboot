/* SPDX-License-Identifier: GPL-2.0+ */
/*
Â * Copyright (C) 2016~2023 Synaptics Incorporated. All rights reserved.
Â *
Â * This program is free software; you can redistribute it and/or modify
Â * it under the terms of the GNU General Public License version 2 or
Â * later as published by the Free Software Foundation.
Â *
Â * INFORMATION CONTAINED IN THIS DOCUMENT IS PROVIDED "AS-IS," AND
Â * SYNAPTICS EXPRESSLY DISCLAIMS ALL EXPRESS AND IMPLIED WARRANTIES,
Â * INCLUDING ANY IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
Â * A PARTICULAR PURPOSE, AND ANY WARRANTIES OF NON-INFRINGEMENT OF ANY
Â * INTELLECTUAL PROPERTY RIGHTS. IN NO EVENT SHALL SYNAPTICS BE LIABLE
Â * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, PUNITIVE, OR
Â * CONSEQUENTIAL DAMAGES ARISING OUT OF OR IN CONNECTION WITH THE USE
Â * OF THE INFORMATION CONTAINED IN THIS DOCUMENT, HOWEVER CAUSED AND
Â * BASED ON ANY THEORY OF LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
Â * NEGLIGENCE OR OTHER TORTIOUS ACTION, AND EVEN IF SYNAPTICS WAS
Â * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. IF A TRIBUNAL OF
Â * COMPETENT JURISDICTION DOES NOT PERMIT THE DISCLAIMER OF DIRECT
Â * DAMAGES OR ANY OTHER DAMAGES, SYNAPTICS' TOTAL CUMULATIVE LIABILITY
Â * TO ANY PARTY SHALL NOT EXCEED ONE HUNDRED U.S. DOLLARS.
Â */

#ifndef avioGbl_h
#define avioGbl_h () {}

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
/// $INTERFACE abipll                  biu              (4,4)
///     # # ----------------------------------------------------------
///     @ 0x00000 ctrlA                (P-)
///               ###
///               * PLL Control
///               ###
///               %unsigned 1  RESET                     0x0
///                                    ###
///                                    * PLL Internal Reset Active High
///                                    ###
///               %unsigned 1  BYPASS                    0x0
///                                    ###
///                                    * PLL Bypass Enable Active High
///                                    ###
///               %unsigned 1  NEWDIV                    0x0
///                                    ###
///                                    * Fractional Divide Input Control
///                                    ###
///               %unsigned 3  RANGE                     0x2
///                                    ###
///                                    * PLL Filter Range
///                                    ###
///               %%        26         # Stuffing bits...
///     @ 0x00004 ctrlB                (P-)
///               %unsigned 4  SSMF                      0x0
///                                    ###
///                                    * Spread Spectrum Modulation Frequency
///                                    ###
///               %unsigned 3  SSMD                      0x0
///                                    ###
///                                    * Spread Spectrum Modulation Depth
///                                    ###
///               %unsigned 1  SSE_RSVD                  0x0
///                                    ###
///                                    * Spread Spectrum Reserve Bit
///                                    ###
///               %unsigned 1  SSE                       0x0
///                                    ###
///                                    * Enables Spread Spectrum Mode Active High
///                                    ###
///               %unsigned 1  SSDS                      0x0
///                                    ###
///                                    * Spread Spectrum Down Spread Center Spread
///                                    ###
///               %%        22         # Stuffing bits...
///     @ 0x00008 ctrlC                (P-)
///               %unsigned 6  DIVR                      0x1
///                                    ###
///                                    * Reference Divider
///                                    ###
///               %%        26         # Stuffing bits...
///     @ 0x0000C ctrlD                (P-)
///               %unsigned 9  DIVFI                     0x1F
///                                    ###
///                                    * Integer Divider
///                                    ###
///               %%        23         # Stuffing bits...
///     @ 0x00010 ctrlE                (P-)
///               %unsigned 24 DIVFF                     0x0
///                                    ###
///                                    * Fractional Divider Control
///                                    ###
///               %%        8          # Stuffing bits...
///     @ 0x00014 ctrlF                (P-)
///               %unsigned 5  DIVQ                      0x1
///                                    ###
///                                    * Output Divider Control for PLLOUT
///                                    ###
///               %%        27         # Stuffing bits...
///     @ 0x00018 ctrlG                (P-)
///               %unsigned 3  DIVQF                     0x3
///                                    ###
///                                    * Output Divider Control for PLLOUTF
///                                    ###
///               %%        29         # Stuffing bits...
///     @ 0x0001C status               (R-)
///               ###
///               * PLL status register
///               ###
///               %unsigned 1  LOCK
///                                    ###
///                                    * Output. Lock detection
///                                    ###
///               %unsigned 1  DIVACK
///                                    ###
///                                    * Fractional Divide Hand-shake signal
///                                    ###
///               %%        30         # Stuffing bits...
///     # # ----------------------------------------------------------
/// $ENDOFINTERFACE  # size:      32B, bits:      65b, padding:     0B
////////////////////////////////////////////////////////////
#ifndef h_abipll
#define h_abipll () {}

    #define     RA_abipll_ctrlA                                0x0000

    #define     BA_abipll_ctrlA_RESET                          0x0000
    #define     B16abipll_ctrlA_RESET                          0x0000
    #define   LSb32abipll_ctrlA_RESET                             0
    #define   LSb16abipll_ctrlA_RESET                             0
    #define       babipll_ctrlA_RESET                          1
    #define   MSK32abipll_ctrlA_RESET                             0x00000001

    #define     BA_abipll_ctrlA_BYPASS                         0x0000
    #define     B16abipll_ctrlA_BYPASS                         0x0000
    #define   LSb32abipll_ctrlA_BYPASS                            1
    #define   LSb16abipll_ctrlA_BYPASS                            1
    #define       babipll_ctrlA_BYPASS                         1
    #define   MSK32abipll_ctrlA_BYPASS                            0x00000002

    #define     BA_abipll_ctrlA_NEWDIV                         0x0000
    #define     B16abipll_ctrlA_NEWDIV                         0x0000
    #define   LSb32abipll_ctrlA_NEWDIV                            2
    #define   LSb16abipll_ctrlA_NEWDIV                            2
    #define       babipll_ctrlA_NEWDIV                         1
    #define   MSK32abipll_ctrlA_NEWDIV                            0x00000004

    #define     BA_abipll_ctrlA_RANGE                          0x0000
    #define     B16abipll_ctrlA_RANGE                          0x0000
    #define   LSb32abipll_ctrlA_RANGE                             3
    #define   LSb16abipll_ctrlA_RANGE                             3
    #define       babipll_ctrlA_RANGE                          3
    #define   MSK32abipll_ctrlA_RANGE                             0x00000038
    ///////////////////////////////////////////////////////////
    #define     RA_abipll_ctrlB                                0x0004

    #define     BA_abipll_ctrlB_SSMF                           0x0004
    #define     B16abipll_ctrlB_SSMF                           0x0004
    #define   LSb32abipll_ctrlB_SSMF                              0
    #define   LSb16abipll_ctrlB_SSMF                              0
    #define       babipll_ctrlB_SSMF                           4
    #define   MSK32abipll_ctrlB_SSMF                              0x0000000F

    #define     BA_abipll_ctrlB_SSMD                           0x0004
    #define     B16abipll_ctrlB_SSMD                           0x0004
    #define   LSb32abipll_ctrlB_SSMD                              4
    #define   LSb16abipll_ctrlB_SSMD                              4
    #define       babipll_ctrlB_SSMD                           3
    #define   MSK32abipll_ctrlB_SSMD                              0x00000070

    #define     BA_abipll_ctrlB_SSE_RSVD                       0x0004
    #define     B16abipll_ctrlB_SSE_RSVD                       0x0004
    #define   LSb32abipll_ctrlB_SSE_RSVD                          7
    #define   LSb16abipll_ctrlB_SSE_RSVD                          7
    #define       babipll_ctrlB_SSE_RSVD                       1
    #define   MSK32abipll_ctrlB_SSE_RSVD                          0x00000080

    #define     BA_abipll_ctrlB_SSE                            0x0005
    #define     B16abipll_ctrlB_SSE                            0x0004
    #define   LSb32abipll_ctrlB_SSE                               8
    #define   LSb16abipll_ctrlB_SSE                               8
    #define       babipll_ctrlB_SSE                            1
    #define   MSK32abipll_ctrlB_SSE                               0x00000100

    #define     BA_abipll_ctrlB_SSDS                           0x0005
    #define     B16abipll_ctrlB_SSDS                           0x0004
    #define   LSb32abipll_ctrlB_SSDS                              9
    #define   LSb16abipll_ctrlB_SSDS                              9
    #define       babipll_ctrlB_SSDS                           1
    #define   MSK32abipll_ctrlB_SSDS                              0x00000200
    ///////////////////////////////////////////////////////////
    #define     RA_abipll_ctrlC                                0x0008

    #define     BA_abipll_ctrlC_DIVR                           0x0008
    #define     B16abipll_ctrlC_DIVR                           0x0008
    #define   LSb32abipll_ctrlC_DIVR                              0
    #define   LSb16abipll_ctrlC_DIVR                              0
    #define       babipll_ctrlC_DIVR                           6
    #define   MSK32abipll_ctrlC_DIVR                              0x0000003F
    ///////////////////////////////////////////////////////////
    #define     RA_abipll_ctrlD                                0x000C

    #define     BA_abipll_ctrlD_DIVFI                          0x000C
    #define     B16abipll_ctrlD_DIVFI                          0x000C
    #define   LSb32abipll_ctrlD_DIVFI                             0
    #define   LSb16abipll_ctrlD_DIVFI                             0
    #define       babipll_ctrlD_DIVFI                          9
    #define   MSK32abipll_ctrlD_DIVFI                             0x000001FF
    ///////////////////////////////////////////////////////////
    #define     RA_abipll_ctrlE                                0x0010

    #define     BA_abipll_ctrlE_DIVFF                          0x0010
    #define     B16abipll_ctrlE_DIVFF                          0x0010
    #define   LSb32abipll_ctrlE_DIVFF                             0
    #define   LSb16abipll_ctrlE_DIVFF                             0
    #define       babipll_ctrlE_DIVFF                          24
    #define   MSK32abipll_ctrlE_DIVFF                             0x00FFFFFF
    ///////////////////////////////////////////////////////////
    #define     RA_abipll_ctrlF                                0x0014

    #define     BA_abipll_ctrlF_DIVQ                           0x0014
    #define     B16abipll_ctrlF_DIVQ                           0x0014
    #define   LSb32abipll_ctrlF_DIVQ                              0
    #define   LSb16abipll_ctrlF_DIVQ                              0
    #define       babipll_ctrlF_DIVQ                           5
    #define   MSK32abipll_ctrlF_DIVQ                              0x0000001F
    ///////////////////////////////////////////////////////////
    #define     RA_abipll_ctrlG                                0x0018

    #define     BA_abipll_ctrlG_DIVQF                          0x0018
    #define     B16abipll_ctrlG_DIVQF                          0x0018
    #define   LSb32abipll_ctrlG_DIVQF                             0
    #define   LSb16abipll_ctrlG_DIVQF                             0
    #define       babipll_ctrlG_DIVQF                          3
    #define   MSK32abipll_ctrlG_DIVQF                             0x00000007
    ///////////////////////////////////////////////////////////
    #define     RA_abipll_status                               0x001C

    #define     BA_abipll_status_LOCK                          0x001C
    #define     B16abipll_status_LOCK                          0x001C
    #define   LSb32abipll_status_LOCK                             0
    #define   LSb16abipll_status_LOCK                             0
    #define       babipll_status_LOCK                          1
    #define   MSK32abipll_status_LOCK                             0x00000001

    #define     BA_abipll_status_DIVACK                        0x001C
    #define     B16abipll_status_DIVACK                        0x001C
    #define   LSb32abipll_status_DIVACK                           1
    #define   LSb16abipll_status_DIVACK                           1
    #define       babipll_status_DIVACK                        1
    #define   MSK32abipll_status_DIVACK                           0x00000002
    ///////////////////////////////////////////////////////////

    typedef struct SIE_abipll {
    ///////////////////////////////////////////////////////////
    #define   GET32abipll_ctrlA_RESET(r32)                     _BFGET_(r32, 0, 0)
    #define   SET32abipll_ctrlA_RESET(r32, v)                   _BFSET_(r32, 0, 0, v)
    #define   GET16abipll_ctrlA_RESET(r16)                     _BFGET_(r16, 0, 0)
    #define   SET16abipll_ctrlA_RESET(r16, v)                   _BFSET_(r16, 0, 0, v)

    #define   GET32abipll_ctrlA_BYPASS(r32)                    _BFGET_(r32, 1, 1)
    #define   SET32abipll_ctrlA_BYPASS(r32, v)                  _BFSET_(r32, 1, 1, v)
    #define   GET16abipll_ctrlA_BYPASS(r16)                    _BFGET_(r16, 1, 1)
    #define   SET16abipll_ctrlA_BYPASS(r16, v)                  _BFSET_(r16, 1, 1, v)

    #define   GET32abipll_ctrlA_NEWDIV(r32)                    _BFGET_(r32, 2, 2)
    #define   SET32abipll_ctrlA_NEWDIV(r32, v)                  _BFSET_(r32, 2, 2, v)
    #define   GET16abipll_ctrlA_NEWDIV(r16)                    _BFGET_(r16, 2, 2)
    #define   SET16abipll_ctrlA_NEWDIV(r16, v)                  _BFSET_(r16, 2, 2, v)

    #define   GET32abipll_ctrlA_RANGE(r32)                     _BFGET_(r32, 5, 3)
    #define   SET32abipll_ctrlA_RANGE(r32, v)                   _BFSET_(r32, 5, 3, v)
    #define   GET16abipll_ctrlA_RANGE(r16)                     _BFGET_(r16, 5, 3)
    #define   SET16abipll_ctrlA_RANGE(r16, v)                   _BFSET_(r16, 5, 3, v)

    #define     w32abipll_ctrlA                                {\
	    UNSG32 uctrlA_RESET                                :  1;\
	    UNSG32 uctrlA_BYPASS                               :  1;\
	    UNSG32 uctrlA_NEWDIV                               :  1;\
	    UNSG32 uctrlA_RANGE                                :  3;\
	    UNSG32 RSVDx0_b6                                   : 26;\
	}
    union { UNSG32 u32abipll_ctrlA;
	    struct w32abipll_ctrlA;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32abipll_ctrlB_SSMF(r32)                      _BFGET_(r32, 3, 0)
    #define   SET32abipll_ctrlB_SSMF(r32, v)                    _BFSET_(r32, 3, 0, v)
    #define   GET16abipll_ctrlB_SSMF(r16)                      _BFGET_(r16, 3, 0)
    #define   SET16abipll_ctrlB_SSMF(r16, v)                    _BFSET_(r16, 3, 0, v)

    #define   GET32abipll_ctrlB_SSMD(r32)                      _BFGET_(r32, 6, 4)
    #define   SET32abipll_ctrlB_SSMD(r32, v)                    _BFSET_(r32, 6, 4, v)
    #define   GET16abipll_ctrlB_SSMD(r16)                      _BFGET_(r16, 6, 4)
    #define   SET16abipll_ctrlB_SSMD(r16, v)                    _BFSET_(r16, 6, 4, v)

    #define   GET32abipll_ctrlB_SSE_RSVD(r32)                  _BFGET_(r32, 7, 7)
    #define   SET32abipll_ctrlB_SSE_RSVD(r32, v)                _BFSET_(r32, 7, 7, v)
    #define   GET16abipll_ctrlB_SSE_RSVD(r16)                  _BFGET_(r16, 7, 7)
    #define   SET16abipll_ctrlB_SSE_RSVD(r16, v)                _BFSET_(r16, 7, 7, v)

    #define   GET32abipll_ctrlB_SSE(r32)                       _BFGET_(r32, 8, 8)
    #define   SET32abipll_ctrlB_SSE(r32, v)                     _BFSET_(r32, 8, 8, v)
    #define   GET16abipll_ctrlB_SSE(r16)                       _BFGET_(r16, 8, 8)
    #define   SET16abipll_ctrlB_SSE(r16, v)                     _BFSET_(r16, 8, 8, v)

    #define   GET32abipll_ctrlB_SSDS(r32)                      _BFGET_(r32, 9, 9)
    #define   SET32abipll_ctrlB_SSDS(r32, v)                    _BFSET_(r32, 9, 9, v)
    #define   GET16abipll_ctrlB_SSDS(r16)                      _BFGET_(r16, 9, 9)
    #define   SET16abipll_ctrlB_SSDS(r16, v)                    _BFSET_(r16, 9, 9, v)

    #define     w32abipll_ctrlB                                {\
	    UNSG32 uctrlB_SSMF                                 :  4;\
	    UNSG32 uctrlB_SSMD                                 :  3;\
	    UNSG32 uctrlB_SSE_RSVD                             :  1;\
	    UNSG32 uctrlB_SSE                                  :  1;\
	    UNSG32 uctrlB_SSDS                                 :  1;\
	    UNSG32 RSVDx4_b10                                  : 22;\
	}
    union { UNSG32 u32abipll_ctrlB;
	    struct w32abipll_ctrlB;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32abipll_ctrlC_DIVR(r32)                      _BFGET_(r32, 5, 0)
    #define   SET32abipll_ctrlC_DIVR(r32, v)                    _BFSET_(r32, 5, 0, v)
    #define   GET16abipll_ctrlC_DIVR(r16)                      _BFGET_(r16, 5, 0)
    #define   SET16abipll_ctrlC_DIVR(r16, v)                    _BFSET_(r16, 5, 0, v)

    #define     w32abipll_ctrlC                                {\
	    UNSG32 uctrlC_DIVR                                 :  6;\
	    UNSG32 RSVDx8_b6                                   : 26;\
	}
    union { UNSG32 u32abipll_ctrlC;
	    struct w32abipll_ctrlC;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32abipll_ctrlD_DIVFI(r32)                     _BFGET_(r32, 8, 0)
    #define   SET32abipll_ctrlD_DIVFI(r32, v)                   _BFSET_(r32, 8, 0, v)
    #define   GET16abipll_ctrlD_DIVFI(r16)                     _BFGET_(r16, 8, 0)
    #define   SET16abipll_ctrlD_DIVFI(r16, v)                   _BFSET_(r16, 8, 0, v)

    #define     w32abipll_ctrlD                                {\
	    UNSG32 uctrlD_DIVFI                                :  9;\
	    UNSG32 RSVDxC_b9                                   : 23;\
	}
    union { UNSG32 u32abipll_ctrlD;
	    struct w32abipll_ctrlD;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32abipll_ctrlE_DIVFF(r32)                     _BFGET_(r32, 23, 0)
    #define   SET32abipll_ctrlE_DIVFF(r32, v)                   _BFSET_(r32, 23, 0, v)

    #define     w32abipll_ctrlE                                {\
	    UNSG32 uctrlE_DIVFF                                : 24;\
	    UNSG32 RSVDx10_b24                                 :  8;\
	}
    union { UNSG32 u32abipll_ctrlE;
	    struct w32abipll_ctrlE;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32abipll_ctrlF_DIVQ(r32)                      _BFGET_(r32, 4, 0)
    #define   SET32abipll_ctrlF_DIVQ(r32, v)                    _BFSET_(r32, 4, 0, v)
    #define   GET16abipll_ctrlF_DIVQ(r16)                      _BFGET_(r16, 4, 0)
    #define   SET16abipll_ctrlF_DIVQ(r16, v)                    _BFSET_(r16, 4, 0, v)

    #define     w32abipll_ctrlF                                {\
	    UNSG32 uctrlF_DIVQ                                 :  5;\
	    UNSG32 RSVDx14_b5                                  : 27;\
	}
    union { UNSG32 u32abipll_ctrlF;
	    struct w32abipll_ctrlF;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32abipll_ctrlG_DIVQF(r32)                     _BFGET_(r32, 2, 0)
    #define   SET32abipll_ctrlG_DIVQF(r32, v)                   _BFSET_(r32, 2, 0, v)
    #define   GET16abipll_ctrlG_DIVQF(r16)                     _BFGET_(r16, 2, 0)
    #define   SET16abipll_ctrlG_DIVQF(r16, v)                   _BFSET_(r16, 2, 0, v)

    #define     w32abipll_ctrlG                                {\
	    UNSG32 uctrlG_DIVQF                                :  3;\
	    UNSG32 RSVDx18_b3                                  : 29;\
	}
    union { UNSG32 u32abipll_ctrlG;
	    struct w32abipll_ctrlG;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32abipll_status_LOCK(r32)                     _BFGET_(r32, 0, 0)
    #define   SET32abipll_status_LOCK(r32, v)                   _BFSET_(r32, 0, 0, v)
    #define   GET16abipll_status_LOCK(r16)                     _BFGET_(r16, 0, 0)
    #define   SET16abipll_status_LOCK(r16, v)                   _BFSET_(r16, 0, 0, v)

    #define   GET32abipll_status_DIVACK(r32)                   _BFGET_(r32, 1, 1)
    #define   SET32abipll_status_DIVACK(r32, v)                 _BFSET_(r32, 1, 1, v)
    #define   GET16abipll_status_DIVACK(r16)                   _BFGET_(r16, 1, 1)
    #define   SET16abipll_status_DIVACK(r16, v)                 _BFSET_(r16, 1, 1, v)

    #define     w32abipll_status                               {\
	    UNSG32 ustatus_LOCK                                :  1;\
	    UNSG32 ustatus_DIVACK                              :  1;\
	    UNSG32 RSVDx1C_b2                                  : 30;\
	}
    union { UNSG32 u32abipll_status;
	    struct w32abipll_status;
	  };
    ///////////////////////////////////////////////////////////
    } SIE_abipll;

    typedef union  T32abipll_ctrlA {
		UNSG32 u32;
	    struct w32abipll_ctrlA;
		 } T32abipll_ctrlA;
    typedef union  T32abipll_ctrlB {
		UNSG32 u32;
	    struct w32abipll_ctrlB;
		 } T32abipll_ctrlB;
    typedef union  T32abipll_ctrlC {
		UNSG32 u32;
	    struct w32abipll_ctrlC;
		 } T32abipll_ctrlC;
    typedef union  T32abipll_ctrlD {
		UNSG32 u32;
	    struct w32abipll_ctrlD;
		 } T32abipll_ctrlD;
    typedef union  T32abipll_ctrlE {
		UNSG32 u32;
	    struct w32abipll_ctrlE;
		 } T32abipll_ctrlE;
    typedef union  T32abipll_ctrlF {
		UNSG32 u32;
	    struct w32abipll_ctrlF;
		 } T32abipll_ctrlF;
    typedef union  T32abipll_ctrlG {
		UNSG32 u32;
	    struct w32abipll_ctrlG;
		 } T32abipll_ctrlG;
    typedef union  T32abipll_status {
		UNSG32 u32;
	    struct w32abipll_status;
		 } T32abipll_status;
    ///////////////////////////////////////////////////////////

    typedef union  Tabipll_ctrlA {
		UNSG32 u32[1];
	    struct {
	    struct w32abipll_ctrlA;
		   };
		 } Tabipll_ctrlA;
    typedef union  Tabipll_ctrlB {
		UNSG32 u32[1];
	    struct {
	    struct w32abipll_ctrlB;
		   };
		 } Tabipll_ctrlB;
    typedef union  Tabipll_ctrlC {
		UNSG32 u32[1];
	    struct {
	    struct w32abipll_ctrlC;
		   };
		 } Tabipll_ctrlC;
    typedef union  Tabipll_ctrlD {
		UNSG32 u32[1];
	    struct {
	    struct w32abipll_ctrlD;
		   };
		 } Tabipll_ctrlD;
    typedef union  Tabipll_ctrlE {
		UNSG32 u32[1];
	    struct {
	    struct w32abipll_ctrlE;
		   };
		 } Tabipll_ctrlE;
    typedef union  Tabipll_ctrlF {
		UNSG32 u32[1];
	    struct {
	    struct w32abipll_ctrlF;
		   };
		 } Tabipll_ctrlF;
    typedef union  Tabipll_ctrlG {
		UNSG32 u32[1];
	    struct {
	    struct w32abipll_ctrlG;
		   };
		 } Tabipll_ctrlG;
    typedef union  Tabipll_status {
		UNSG32 u32[1];
	    struct {
	    struct w32abipll_status;
		   };
		 } Tabipll_status;

    ///////////////////////////////////////////////////////////
     SIGN32 abipll_drvrd(SIE_abipll *p, UNSG32 base, SIGN32 mem, SIGN32 tst);
     SIGN32 abipll_drvwr(SIE_abipll *p, UNSG32 base, SIGN32 mem, SIGN32 tst, UNSG32 *pcmd);
       void abipll_reset(SIE_abipll *p);
     SIGN32 abipll_cmp(SIE_abipll *p, SIE_abipll *pie, char *pfx, void *hLOG, SIGN32 mem, SIGN32 tst);
    #define abipll_check(p, pie, pfx, hLOG) abipll_cmp(p, pie, pfx, (void *)(hLOG), 0, 0)
    #define abipll_print(p,    pfx, hLOG) abipll_cmp(p, 0,  pfx, (void *)(hLOG), 0, 0)

#endif
//////
/// ENDOFINTERFACE: abipll
////////////////////////////////////////////////////////////

//////
///
/// $INTERFACE DPHYTX                  biu              (4,4)
///     # # ----------------------------------------------------------
///     @ 0x00000 DPHY_CTL0            (P)
///               %unsigned 1  BiuCtrlPhyEn              0x0
///                                    ###
///                                    * Enable Biu Control DPHY register.
///                                    ###
///               %%        31         # Stuffing bits...
///     @ 0x00004 DPHY_CTL1            (P)
///               %unsigned 1  shutdownz                 0x0
///                                    ###
///                                    * Shutdown InputThis line is used to place the PHY in shutdown. All analog blocks are in shutdown mode and the digital logic is reset.Active state: Low
///                                    ###
///               %unsigned 1  rstz                      0x0
///                                    ###
///                                    * Reset InputThis line is used to place the digital section of the PHY in reset state.Active state: Low
///                                    ###
///               %unsigned 1  forcepll                  0x0
///                                    ###
///                                    * By default, the PLL clock multiplier is switched off during shutdown and ULP operation if all lanes are in ULPS. If the PLL functionality is required from system perspective in any of these conditions, forcepll can be kept asserted maintaining the PLL active at all times, regardless of other configurations or states.
///                                    * forcepll signal cannot be used to power-up the PLL independent of the PHY state.
///                                    ###
///               %unsigned 1  txrequesthsclk            0x0
///                                    ###
///                                    * High-Speed Transmit Clock Request SignalThis signal causes the clock lane to start transmitting DDR clock on the lane interconnect. A TX HS request is not allowed if the add-on PLL is not enabled and locked.
///                                    ###
///               %unsigned 1  enableclkBIU              0x0
///                                    ###
///                                    * Enable Clock Lane ModuleAll lane drivers and terminations are turned off when enableclk is low. In addition, all other lane PPI inputs are ignored and all lane PPI outputs are driven to the default values. enableclk is level sensitive and asynchronous.It is not allowed for this signal to be changed during operation. It should be set with PHY in power-down.
///                                    ###
///               %unsigned 1  turndisable_0             0x0
///                                    ###
///                                    * Disable Turn AroundThis signal is used to prevent the bi-directional lane from processing a turn-around request in the lane interconnection.Note: This is useful to prevent a potential “lock-up” situation when a unidirectional lane module is connected to a bi-directional lane module.
///                                    ###
///               %unsigned 1  forcerxmode_0             0x0
///                                    ###
///                                    * Force Lane Module into Receive Mode/Wait for Stop State This signal allows the protocol layer to initialize a lane module or force a bi-directional lane module into receive mode. This signal is used to solve a contention situation. When this signal is high, the lane module immediately transitions into receive control mode and waits for a Stop state to appear on the Lane interconnect.
///                                    ###
///               %unsigned 1  basedir_0                 0x0
///                                    ###
///                                    * Function: Configures the Base Direction for Lane¦ basedir_0 = 1: Configures lane as RX upon startup of the PHY¦ basedir_0 = 0: Configures lane as TX
///                                    ###
///               %unsigned 1  forcetxstopmode_0         0x0
///                                    ###
///                                    * Force Lane Module into Transmit Mode and Generate Stop StateThis signal allows the protocol layer to force a bi-directional lane module into transmit mode and Stop state following an error indication (for example, Expired Timeout). When this signal is high, the lane module immediately transitions into transmit mode and the module state machine is forced into the Stop state.
///                                    ###
///               %unsigned 1  forcetxstopmode_1         0x0
///                                    ###
///                                    * Force Lane Module into Transmit Mode and Generate Stop StateThis signal allows the protocol layer to force a bi-directional lane module into transmit mode and Stop state following an error indication (for example, Expired Timeout). When this signal is high, the lane module immediately transitions into transmit mode and the module state machine is forced into the Stop state.
///                                    ###
///               %unsigned 1  forcetxstopmode_2         0x0
///                                    ###
///                                    * Force Lane Module into Transmit Mode and Generate Stop StateThis signal allows the protocol layer to force a bi-directional lane module into transmit mode and Stop state following an error indication (for example, Expired Timeout). When this signal is high, the lane module immediately transitions into transmit mode and the module state machine is forced into the Stop state.
///                                    ###
///               %unsigned 1  forcetxstopmode_3         0x0
///                                    ###
///                                    * Force Lane Module into Transmit Mode and Generate Stop StateThis signal allows the protocol layer to force a bi-directional lane module into transmit mode and Stop state following an error indication (for example, Expired Timeout). When this signal is high, the lane module immediately transitions into transmit mode and the module state machine is forced into the Stop state.
///                                    ###
///               %unsigned 1  enable_0                  0x0
///                                    ###
///                                    * Enable Lane 0All lane drivers, receivers, terminations, and contention detectors are turned off when enable_0 is low. In addition, all other lane PPI inputs are ignored and all lane PPI outputs are driven to the default values.enable_0 is level sensitive and asynchronous. It is not allowed for this signal to be changed during operation. It should be set with PHY in power-down.
///                                    ###
///               %unsigned 1  enable_1                  0x0
///                                    ###
///                                    * Enable Lane 1All lane drivers, receivers, terminations, and contention detectors are turned off when enable_1 is low. In addition, all other lane PPI inputs are ignored and all lane PPI outputs are driven to the default values.enable_1 is level sensitive and asynchronous. It is not allowed for this signal to be changed during operation. It should be set with PHY in power-down.
///                                    ###
///               %unsigned 1  enable_2                  0x0
///                                    ###
///                                    * Enable Lane 2All lane drivers, receivers, terminations, and contention detectors are turned off when enable_2 is low. In addition, all other lane PPI inputs are ignored and all lane PPI outputs are driven to the default values.enable_2 is level sensitive and asynchronous. It is not allowed for this signal to be changed during operation. It should be set with PHY in power-down.
///                                    ###
///               %unsigned 1  enable_3                  0x0
///                                    ###
///                                    * Enable Lane 3All lane drivers, receivers, terminations, and contention detectors are turned off when enable_3 is low. In addition, all other lane PPI inputs are ignored and all lane PPI outputs are driven to the default values.enable_3 is level sensitive and asynchronous. It is not allowed for this signal to be changed during operation. It should be set with PHY in power-down.
///                                    ###
///               %unsigned 7  hsfreqrange               0x49
///                                    ###
///                                    * High-speed Frequency Range Selection. Refer to Table 5-6 on page 123 for Operating Frequency Range selection and default values. This signal should be set with the D-PHY in power-down and must not change during operation.This signal can be overridden through D-PHY test control registers.
///                                    ###
///               %unsigned 1  cont_en                   0x0
///                                    ###
///                                    * This signal places the macro in IO continuity test mode. All other interface signals should be placed in their default values.Active state: high
///                                    ###
///               %unsigned 6  cfgclkfreqrange           0x20
///                                    ###
///                                    * System clock frequency configuration preset. Should beset according to the following equation:cfgclkfreqrange[5:0] = round[ (Fcfg_clk(MHz)-17)*4]
///                                    ###
///               %unsigned 1  biston                    0x0
///                                    ###
///                                    * Starts the pattern generator.
///                                    ###
///               %%        1          # Stuffing bits...
///     @ 0x00008 DPHY_CTL2            (P)
///               %unsigned 1  txulpsclkBIU              0x0
///                                    ###
///                                    * Transmit Ultra Low Power on Clock LaneThis signal is asserted to cause the clock lane module to enter the Ultra Low Power state. The lane module remains in this mode until the txulpsexitclk signal is asserted. This signal is clocked by txclkesc.
///                                    ###
///               %unsigned 1  txulpsexitclk             0x0
///                                    ###
///                                    * This signal is asserted to cause the clock lane module totransmit the Ultra Low Power (ULP) exit sequence and return to the Stop state. This signal is clocked by txclkesc. While txclkesc can be gated during ULP state, it must be reactivated so that the txulpsexitclk command can be processed.Between the assertion of txulpsexitclk andulpsactivenotclk there is a latency not higher than 55us for the default configurations.
///                                    ###
///               %unsigned 1  turnrequest_0             0x0
///                                    ###
///                                    * Turn around RequestThis signal is used to indicate that the protocol layer needs to turn the lane around, allowing for the other side to start transmitting the data.turnrequest_0 is valid on the rising edges of txclkesc.Note: turnrequest_0 is only meaningful for a lane that is currently transmitting data (direction_0 = 0). If the data lane module is in receive mode (direction_0 =1), this signal is ignored.
///                                    ###
///               %%        29         # Stuffing bits...
///     @ 0x0000C DPHY_CTL3            (P)
///               %unsigned 8  txdataesc_0               0x0
///                                    ###
///                                    * Escape Mode Transmit Data BusThis is the 8-bit bus data input to be transmitted in low-power data transmission mode. The LSB is transmitted first. txdataesc_0 is synchronous with the rising edge of txclkesc.
///                                    ###
///               %unsigned 4  txtriggeresc_0            0x0
///                                    ###
///                                    * Escape Mode Transmit Trigger 0-3One of these signals is asserted with txrequestesc_0 to cause the lane module to send the associated trigger across the lane interconnection.txtriggeresc_0 is synchronous with the rising edge of txclkesc_0.Note: Only one of the txtriggeresc_0 is asserted at any given time, and only when txlpdtesc_0 and txulpsesc_0 are both at low level.¦ txtriggeresc_0[0] corresponds to Reset-Trigger.¦ txtriggeresc_0[1] corresponds to Unknown-3 Trigger.¦ txtriggeresc_0[2] corresponds to Unknown-4 Trigger.¦ txtriggeresc_0[3] corresponds to Unknown-5 Trigger.
///                                    ###
///               %unsigned 1  txrequestesc_0            0x0
///                                    ###
///                                    * Escape Mode Transmit RequestThis signal together with txlpdtesc_0, txulpsesc_0, andtxtriggeresc_0[3:0] is used to request the entry into any Escape mode.Once in Escape mode, the lane stays in Escape mode untiltxrequestesc_0 is un-asserted.Note: It can only be asserted by the protocol layer whiletxrequestdatahs_0 is at low level.
///                                    ###
///               %unsigned 1  txlpdtesc_0               0x0
///                                    ###
///                                    * Escape Mode Transmit Low-Power DataThis signal is asserted with txrequestesc_0 to cause the lane module to enter low-power data transmission mode. The lane module remains in this mode until txrequestesc_0 is de-asserted.Note: txulpsesc_0 and all the bits of txtriggeresc_0 must be at low level when txlpdtesc_0 is at high level.
///                                    ###
///               %unsigned 1  txulpsesc_0               0x0
///                                    ###
///                                    * Escape Mode Transmit ULPThis signal is asserted with txrequestesc_0 to cause the lane module to enter the ULP State. The lane module remains in this state until txulpsexit_0 is asserted and txrequestesc_0 is de-asserted.Note: txlpdtesc_0 and all bits of txtriggeresc_0 must be at low level when txulpsesc_0 is at high level.
///                                    ###
///               %unsigned 1  txulpsexit_0              0x0
///                                    ###
///                                    * Initiate the transmission of the ULP exit sequence.If this signal is asserted while the lane is in ULP state, the PHY leaves the ULP state and begins driving a Mark-1 symbol on the line interconnect.Afterwards, upon de-assertion of txrequestesc_0, the PHY drives the LP-11 Stop state. Between the assertion of txulpsexit_0 and ulpsactivenotclk there is a latency not higher than 55us for the default configurationsNote: This signal is ignored when the PHY is not in the ULP state.
///                                    ###
///               %unsigned 1  txvalidesc_0              0x0
///                                    ###
///                                    * Escape Mode Transmit Data ValidThis signal indicates that the protocol layer is driving valid data on txdataesc_0 bus, to be transmitted.Note: The lane module accepts the data when txrequestesc_0, txvalidesc_0, and txreadyesc_0 are all active on the same rising edge of txclkesc.
///                                    ###
///               %%        15         # Stuffing bits...
///     @ 0x00010 DPHY_CTL4            (P)
///               %unsigned 8  txdataesc_1               0x0
///                                    ###
///                                    * Escape Mode Transmit Data BusThis is the 8-bit bus data input to be transmitted in low-power data transmission mode. The LSB is transmitted first. txdataesc_1 is synchronous with the rising edge of txclkesc.
///                                    ###
///               %unsigned 4  txtriggeresc_1            0x0
///                                    ###
///                                    * Escape Mode Transmit Trigger 0-3One of these signals is asserted with txrequestesc_1 to cause the lane module to send the associated trigger across the lane interconnection.txtriggeresc_1 is synchronous with the rising edge of txclkesc_1.Note: Only one of the txtriggeresc_1 is asserted at any given time, and only when txlpdtesc_1 and txulpsesc_1 are both at low level.¦ txtriggeresc_1[0] corresponds to Reset-Trigger.¦ txtriggeresc_1[1] corresponds to Unknown-3 Trigger.¦ txtriggeresc_1[2] corresponds to Unknown-4 Trigger.¦ txtriggeresc_1[3] corresponds to Unknown-5 Trigger.
///                                    ###
///               %unsigned 1  txrequestesc_1            0x0
///                                    ###
///                                    * Escape Mode Transmit RequestThis signal together with txlpdtesc_1, txulpsesc_1, andtxtriggeresc_1[3:0] is used to request the entry into any Escape mode.Once in Escape mode, the lane stays in Escape mode untiltxrequestesc_1 is un-asserted.Note: It can only be asserted by the protocol layer whiletxrequestdatahs_1 is at low level.
///                                    ###
///               %unsigned 1  txlpdtesc_1               0x0
///                                    ###
///                                    * Escape Mode Transmit Low-Power DataThis signal is asserted with txrequestesc_1 to cause the lane module to enter low-power data transmission mode. The lane module remains in this mode until txrequestesc_1 is de-asserted.Note: txulpsesc_1 and all the bits of txtriggeresc_1 must be at low level when txlpdtesc_1 is at high level.
///                                    ###
///               %unsigned 1  txulpsesc_1               0x0
///                                    ###
///                                    * Escape Mode Transmit ULPThis signal is asserted with txrequestesc_1 to cause the lane module to enter the ULP State. The lane module remains in this state until txulpsexit_1 is asserted and txrequestesc_1 is de-asserted.Note: txlpdtesc_1 and all bits of txtriggeresc_1 must be at low level when txulpsesc_1 is at high level.
///                                    ###
///               %unsigned 1  txulpsexit_1              0x0
///                                    ###
///                                    * Initiate the transmission of the ULP exit sequence.If this signal is asserted while the lane is in ULP state, the PHY leaves the ULP state and begins driving a Mark-1 symbol on the line interconnect.Afterwards, upon de-assertion of txrequestesc_1, the PHY drives the LP-11 Stop state. Between the assertion of txulpsexit_1 and ulpsactivenotclk there is a latency not higher than 55us for the default configurationsNote: This signal is ignored when the PHY is not in the ULP state.
///                                    ###
///               %unsigned 1  txvalidesc_1              0x0
///                                    ###
///                                    * Escape Mode Transmit Data ValidThis signal indicates that the protocol layer is driving valid data on txdataesc_1 bus, to be transmitted.Note: The lane module accepts the data when txrequestesc_1, txvalidesc_1, and txreadyesc_1 are all active on the same rising edge of txclkesc.
///                                    ###
///               %%        15         # Stuffing bits...
///     @ 0x00014 DPHY_CTL5            (P)
///               %unsigned 8  txdataesc_2               0x0
///                                    ###
///                                    * Escape Mode Transmit Data BusThis is the 8-bit bus data input to be transmitted in low-power data transmission mode. The LSB is transmitted first. txdataesc_2 is synchronous with the rising edge of txclkesc.
///                                    ###
///               %unsigned 4  txtriggeresc_2            0x0
///                                    ###
///                                    * Escape Mode Transmit Trigger 0-3One of these signals is asserted with txrequestesc_2 to cause the lane module to send the associated trigger across the lane interconnection.txtriggeresc_2 is synchronous with the rising edge of txclkesc_2.Note: Only one of the txtriggeresc_2 is asserted at any given time, and only when txlpdtesc_2 and txulpsesc_2 are both at low level.¦ txtriggeresc_2[0] corresponds to Reset-Trigger.¦ txtriggeresc_2[1] corresponds to Unknown-3 Trigger.¦ txtriggeresc_2[2] corresponds to Unknown-4 Trigger.¦ txtriggeresc_2[3] corresponds to Unknown-5 Trigger.
///                                    ###
///               %unsigned 1  txrequestesc_2            0x0
///                                    ###
///                                    * Escape Mode Transmit RequestThis signal together with txlpdtesc_2, txulpsesc_2, andtxtriggeresc_2[3:0] is used to request the entry into any Escape mode.Once in Escape mode, the lane stays in Escape mode untiltxrequestesc_2 is un-asserted.Note: It can only be asserted by the protocol layer whiletxrequestdatahs_2 is at low level.
///                                    ###
///               %unsigned 1  txlpdtesc_2               0x0
///                                    ###
///                                    * Escape Mode Transmit Low-Power DataThis signal is asserted with txrequestesc_2 to cause the lane module to enter low-power data transmission mode. The lane module remains in this mode until txrequestesc_2 is de-asserted.Note: txulpsesc_2 and all the bits of txtriggeresc_2 must be at low level when txlpdtesc_2 is at high level.
///                                    ###
///               %unsigned 1  txulpsesc_2               0x0
///                                    ###
///                                    * Escape Mode Transmit ULPThis signal is asserted with txrequestesc_2 to cause the lane module to enter the ULP State. The lane module remains in this state until txulpsexit_2 is asserted and txrequestesc_2 is de-asserted.Note: txlpdtesc_2 and all bits of txtriggeresc_2 must be at low level when txulpsesc_2 is at high level.
///                                    ###
///               %unsigned 1  txulpsexit_2              0x0
///                                    ###
///                                    * Initiate the transmission of the ULP exit sequence.If this signal is asserted while the lane is in ULP state, the PHY leaves the ULP state and begins driving a Mark-1 symbol on the line interconnect.Afterwards, upon de-assertion of txrequestesc_2, the PHY drives the LP-11 Stop state. Between the assertion of txulpsexit_2 and ulpsactivenotclk there is a latency not higher than 55us for the default configurationsNote: This signal is ignored when the PHY is not in the ULP state.
///                                    ###
///               %unsigned 1  txvalidesc_2              0x0
///                                    ###
///                                    * Escape Mode Transmit Data ValidThis signal indicates that the protocol layer is driving valid data on txdataesc_2 bus, to be transmitted.Note: The lane module accepts the data when txrequestesc_2, txvalidesc_2, and txreadyesc_2 are all active on the same rising edge of txclkesc.
///                                    ###
///               %%        15         # Stuffing bits...
///     @ 0x00018 DPHY_CTL6            (P)
///               %unsigned 8  txdataesc_3               0x0
///                                    ###
///                                    * Escape Mode Transmit Data BusThis is the 8-bit bus data input to be transmitted in low-power data transmission mode. The LSB is transmitted first. txdataesc_3 is synchronous with the rising edge of txclkesc.
///                                    ###
///               %unsigned 4  txtriggeresc_3            0x0
///                                    ###
///                                    * Escape Mode Transmit Trigger 0-3One of these signals is asserted with txrequestesc_3 to cause the lane module to send the associated trigger across the lane interconnection.txtriggeresc_3 is synchronous with the rising edge of txclkesc_3.Note: Only one of the txtriggeresc_3 is asserted at any given time, and only when txlpdtesc_3 and txulpsesc_3 are both at low level.¦ txtriggeresc_3[0] corresponds to Reset-Trigger.¦ txtriggeresc_3[1] corresponds to Unknown-3 Trigger.¦ txtriggeresc_3[2] corresponds to Unknown-4 Trigger.¦ txtriggeresc_3[3] corresponds to Unknown-5 Trigger.
///                                    ###
///               %unsigned 1  txrequestesc_3            0x0
///                                    ###
///                                    * Escape Mode Transmit RequestThis signal together with txlpdtesc_3, txulpsesc_3, andtxtriggeresc_3[3:0] is used to request the entry into any Escape mode.Once in Escape mode, the lane stays in Escape mode untiltxrequestesc_3 is un-asserted.Note: It can only be asserted by the protocol layer whiletxrequestdatahs_3 is at low level.
///                                    ###
///               %unsigned 1  txlpdtesc_3               0x0
///                                    ###
///                                    * Escape Mode Transmit Low-Power DataThis signal is asserted with txrequestesc_3 to cause the lane module to enter low-power data transmission mode. The lane module remains in this mode until txrequestesc_3 is de-asserted.Note: txulpsesc_3 and all the bits of txtriggeresc_3 must be at low level when txlpdtesc_3 is at high level.
///                                    ###
///               %unsigned 1  txulpsesc_3               0x0
///                                    ###
///                                    * Escape Mode Transmit ULPThis signal is asserted with txrequestesc_3 to cause the lane module to enter the ULP State. The lane module remains in this state until txulpsexit_3 is asserted and txrequestesc_3 is de-asserted.Note: txlpdtesc_3 and all bits of txtriggeresc_3 must be at low level when txulpsesc_3 is at high level.
///                                    ###
///               %unsigned 1  txulpsexit_3              0x0
///                                    ###
///                                    * Initiate the transmission of the ULP exit sequence.If this signal is asserted while the lane is in ULP state, the PHY leaves the ULP state and begins driving a Mark-1 symbol on the line interconnect.Afterwards, upon de-assertion of txrequestesc_3, the PHY drives the LP-11 Stop state. Between the assertion of txulpsexit_3 and ulpsactivenotclk there is a latency not higher than 55us for the default configurationsNote: This signal is ignored when the PHY is not in the ULP state.
///                                    ###
///               %unsigned 1  txvalidesc_3              0x0
///                                    ###
///                                    * Escape Mode Transmit Data ValidThis signal indicates that the protocol layer is driving valid data on txdataesc_3 bus, to be transmitted.Note: The lane module accepts the data when txrequestesc_3, txvalidesc_3, and txreadyesc_3 are all active on the same rising edge of txclkesc.
///                                    ###
///               %%        15         # Stuffing bits...
///     @ 0x0001C DPHY_CTL7            (P)
///               %unsigned 1  txblaneclkSel             0x0
///               %unsigned 1  txskewcalhsBIU            0x0
///                                    ###
///                                    * High-Speed Transmit Deskew Calibration.When txskewcalhs is sampled high by txbyteclkhs, the lane module initiates a deskew sequence. When txskewcalhs is de-asserted data lanes stops sending deskew pattern, and the lane modules initiates an End-of-Transmission (EOT) sequence.
///                                    ###
///               %unsigned 1  txrequestdatahs_0         0x0
///                                    ###
///                                    * High-Speed Transmit Request And Data Valid SignalWhen txrequesths_0 is sampled high by txbyteclkhs, the lane module initiates a Start-of-Transmission (SOT) sequence. When txrequesths_0 is sampled low while txreadyhs_0 is asserted, the lane module initiates an End-of-Transmission (EOT) sequence. A TX HS request is not allowed if the add-on PLL is not enabled and locked.
///                                    ###
///               %unsigned 1  txrequestdatahs_1         0x0
///                                    ###
///                                    * High-Speed Transmit Request And Data Valid SignalWhen txrequesths_1 is sampled high by txbyteclkhs, the lane module initiates a Start-of-Transmission (SOT) sequence. When txrequesths_1 is sampled low while txreadyhs_1 is asserted, the lane module initiates an End-of-Transmission (EOT) sequence. A TX HS request is not allowed if the add-on PLL is not enabled and locked.
///                                    ###
///               %unsigned 1  txrequestdatahs_2         0x0
///                                    ###
///                                    * High-Speed Transmit Request And Data Valid SignalWhen txrequesths_2 is sampled high by txbyteclkhs, the lane module initiates a Start-of-Transmission (SOT) sequence. When txrequesths_2 is sampled low while txreadyhs_2 is asserted, the lane module initiates an End-of-Transmission (EOT) sequence. A TX HS request is not allowed if the add-on PLL is not enabled and locked.
///                                    ###
///               %unsigned 1  txrequestdatahs_3         0x0
///                                    ###
///                                    * High-Speed Transmit Request And Data Valid SignalWhen txrequesths_3 is sampled high by txbyteclkhs, the lane module initiates a Start-of-Transmission (SOT) sequence. When txrequesths_3 is sampled low while txreadyhs_3 is asserted, the lane module initiates an End-of-Transmission (EOT) sequence. A TX HS request is not allowed if the add-on PLL is not enabled and locked.
///                                    ###
///               %%        26         # Stuffing bits...
///     @ 0x00020 DPHY_CTL8            (P)
///               %unsigned 8  txdatahs_0                0x0
///                                    ###
///                                    * High-Speed Transmit DataThis is an 8-bit data bus input that receives data to be transmitted.txdatahs_0[0] is transmitted first. The txdatahs_0 signal is synchronous to the rising edge of txbyteclkhs.
///                                    ###
///               %unsigned 8  txdatahs_1                0x0
///                                    ###
///                                    * High-Speed Transmit DataThis is an 8-bit data bus input that receives data to be transmitted.txdatahs_1[0] is transmitted first. The txdatahs_1 signal is synchronous to the rising edge of txbyteclkhs.
///                                    ###
///               %unsigned 8  txdatahs_2                0x0
///                                    ###
///                                    * High-Speed Transmit DataThis is an 8-bit data bus input that receives data to be transmitted.txdatahs_2[0] is transmitted first. The txdatahs_2 signal is synchronous to the rising edge of txbyteclkhs.
///                                    ###
///               %unsigned 8  txdatahs_3                0x0
///                                    ###
///                                    * High-Speed Transmit DataThis is an 8-bit data bus input that receives data to be transmitted.txdatahs_3[0] is transmitted first. The txdatahs_3 signal is synchronous to the rising edge of txbyteclkhs.
///                                    ###
///     @ 0x00024 DPHY_RB0             (R-)
///               %unsigned 11 cont_data
///                                    ###
///                                    * Each pin of this output bus is used to verify the continuityfrom the chips pin all the way to the PHY’s analog ports (package, bonding, die, etc). Please refer to the test modes section for more information.¦ cont_data[0]: rext¦ cont_data[1]: clkn¦ cont_data[2]: clkp¦ cont_data[3]: datan0¦ cont_data[4]: datap0¦ cont_data[5]: datan1¦ cont_data[6]: datap1¦ cont_data[7]: datan2¦ cont_data[8]: datap2¦ cont_data[9]: datan3¦ cont_data[10]: datap3
///                                    ###
///               %unsigned 1  lock
///                                    ###
///                                    * PLL Lock SignalWhen set, it signals that the PLL acquired lock with input refclk.This signal can be overridden through D-PHY test control registers.
///                                    ###
///               %unsigned 1  stopstateclk
///                                    ###
///                                    * Clock Lane in Stop StateThis signal indicates that the clock lane module is in Stop state.
///                                    ###
///               %unsigned 1  ulpsactivenotclk
///                                    ###
///                                    * This signal is asserted to cause the clock lane module totransmit the Ultra Low Power (ULP) exit sequence and return to the Stop state. This signal is clocked by txclkesc. While txclkesc can be gated during ULP state, it must be reactivated so that the txulpsexitclk command can be processed.Between the assertion of txulpsexitclk andulpsactivenotclk there is a latency not higher than 55us for the default configurations.
///                                    ###
///               %unsigned 1  stopstatedata_0
///                                    ###
///                                    * Data Lane in Stop StateThis signal indicates that the lane module is in Stop state. This is valid for both TX and RX applications. This signal is asynchronous to any clock in the PPI.Note: If the application requires multi-lane synchronization, the lanes must be kept in the Stop state during 67-byte clock cycles; this occurs after the stopstate_0 signals are observed in the PPI. Only then is a new burst request issued in the lanes. If dead time between packets is a bottleneck, see table “High-Speed Transition Times”, column High-SpeedExit“HS->LP” on page 397
///                                    ###
///               %unsigned 1  stopstatedata_1
///                                    ###
///                                    * Data Lane in Stop StateThis signal indicates that the lane module is in Stop state. This is valid for both TX and RX applications. This signal is asynchronous to any clock in the PPI.Note: If the application requires multi-lane synchronization, the lanes must be kept in the Stop state during 67-byte clock cycles; this occurs after the stopstate_1 signals are observed in the PPI. Only then is a new burst request issued in the lanes. If dead time between packets is a bottleneck, see table “High-Speed Transition Times”, column High-SpeedExit“HS->LP” on page 397
///                                    ###
///               %unsigned 1  stopstatedata_2
///                                    ###
///                                    * Data Lane in Stop StateThis signal indicates that the lane module is in Stop state. This is valid for both TX and RX applications. This signal is asynchronous to any clock in the PPI.Note: If the application requires multi-lane synchronization, the lanes must be kept in the Stop state during 67-byte clock cycles; this occurs after the stopstate_2 signals are observed in the PPI. Only then is a new burst request issued in the lanes. If dead time between packets is a bottleneck, see table “High-Speed Transition Times”, column High-SpeedExit“HS->LP” on page 397
///                                    ###
///               %unsigned 1  stopstatedata_3
///                                    ###
///                                    * Data Lane in Stop StateThis signal indicates that the lane module is in Stop state. This is valid for both TX and RX applications. This signal is asynchronous to any clock in the PPI.Note: If the application requires multi-lane synchronization, the lanes must be kept in the Stop state during 67-byte clock cycles; this occurs after the stopstate_3 signals are observed in the PPI. Only then is a new burst request issued in the lanes. If dead time between packets is a bottleneck, see table “High-Speed Transition Times”, column High-SpeedExit“HS->LP” on page 397
///                                    ###
///               %unsigned 1  ulpsactivenot_0
///                                    ###
///                                    * This signal indicates that the lane is in the Ultra Low Power (ULP) state. For a TX lane, this signal is asserted (driven low) some time after txulpsesc_0 and txrequestesc_0 are asserted. txclkesc must be supplied to the PHY until ulpsactivenot_0 is asserted. In order to leave the ULP state, the transmitter first drives txulpsexit_0 high, then waits for ulpsactivenot_0 to become high (inactive). At that point, the PHY is active and transmits a Mark-1 on the Lines. The protocol waits for a time Twakeup and then drives txrequestesc_0 inactive to return the lane to Stop state.For a RX lane, this signal indicates that the lane is in the ULP state. At the beginning of ULP state, ulpsactivenot_0 is asserted (driven low); at the end of the ULP state, this signal becomes inactive to indicate that the Mark-1 state has been observed. Later, after a period of time Twakeup, the rxulpsesc_0 signal is de-asserted (driven high).
///                                    ###
///               %unsigned 1  ulpsactivenot_1
///                                    ###
///                                    * This signal indicates that the lane is in the Ultra Low Power (ULP) state. For a TX lane, this signal is asserted (driven low) some time after txulpsesc_1 and txrequestesc_1 are asserted. txclkesc must be supplied to the PHY until ulpsactivenot_1 is asserted. In order to leave the ULP state, the transmitter first drives txulpsexit_1 high, then waits for ulpsactivenot_1 to become high (inactive). At that point, the PHY is active and transmits a Mark-1 on the Lines. The protocol waits for a time Twakeup and then drives txrequestesc_1 inactive to return the lane to Stop state.For a RX lane, this signal indicates that the lane is in the ULP state. At the beginning of ULP state, ulpsactivenot_1 is asserted (driven low); at the end of the ULP state, this signal becomes inactive to indicate that the Mark-1 state has been observed. Later, after a period of time Twakeup, the rxulpsesc_1 signal is de-asserted (driven high).
///                                    ###
///               %unsigned 1  ulpsactivenot_2
///                                    ###
///                                    * This signal indicates that the lane is in the Ultra Low Power (ULP) state. For a TX lane, this signal is asserted (driven low) some time after txulpsesc_2 and txrequestesc_2 are asserted. txclkesc must be supplied to the PHY until ulpsactivenot_2 is asserted. In order to leave the ULP state, the transmitter first drives txulpsexit_2 high, then waits for ulpsactivenot_2 to become high (inactive). At that point, the PHY is active and transmits a Mark-1 on the Lines. The protocol waits for a time Twakeup and then drives txrequestesc_2 inactive to return the lane to Stop state.For a RX lane, this signal indicates that the lane is in the ULP state. At the beginning of ULP state, ulpsactivenot_2 is asserted (driven low); at the end of the ULP state, this signal becomes inactive to indicate that the Mark-1 state has been observed. Later, after a period of time Twakeup, the rxulpsesc_2 signal is de-asserted (driven high).
///                                    ###
///               %unsigned 1  ulpsactivenot_3
///                                    ###
///                                    * This signal indicates that the lane is in the Ultra Low Power (ULP) state. For a TX lane, this signal is asserted (driven low) some time after txulpsesc_3 and txrequestesc_3 are asserted. txclkesc must be supplied to the PHY until ulpsactivenot_3 is asserted. In order to leave the ULP state, the transmitter first drives txulpsexit_3 high, then waits for ulpsactivenot_3 to become high (inactive). At that point, the PHY is active and transmits a Mark-1 on the Lines. The protocol waits for a time Twakeup and then drives txrequestesc_3 inactive to return the lane to Stop state.For a RX lane, this signal indicates that the lane is in the ULP state. At the beginning of ULP state, ulpsactivenot_3 is asserted (driven low); at the end of the ULP state, this signal becomes inactive to indicate that the Mark-1 state has been observed. Later, after a period of time Twakeup, the rxulpsesc_3 signal is de-asserted (driven high).
///                                    ###
///               %%        10         # Stuffing bits...
///     @ 0x00028 DPHY_RB1             (R-)
///               %unsigned 1  txreadyhs_0
///                                    ###
///                                    * High-Speed Transmit ReadyThis signal indicates that txdatahs_0 is accepted by the lane module to be serially transmitted. txreadyhs_0 and the other PPI high-speed data TX signals are synchronous with the rising edge of txbyteclkhs.
///                                    ###
///               %unsigned 1  txreadyhs_1
///                                    ###
///                                    * High-Speed Transmit ReadyThis signal indicates that txdatahs_1 is accepted by the lane module to be serially transmitted. txreadyhs_1 and the other PPI high-speed data TX signals are synchronous with the rising edge of txbyteclkhs.
///                                    ###
///               %unsigned 1  txreadyhs_2
///                                    ###
///                                    * High-Speed Transmit ReadyThis signal indicates that txdatahs_2 is accepted by the lane module to be serially transmitted. txreadyhs_2 and the other PPI high-speed data TX signals are synchronous with the rising edge of txbyteclkhs.
///                                    ###
///               %unsigned 1  txreadyhs_3
///                                    ###
///                                    * High-Speed Transmit ReadyThis signal indicates that txdatahs_3 is accepted by the lane module to be serially transmitted. txreadyhs_3 and the other PPI high-speed data TX signals are synchronous with the rising edge of txbyteclkhs.
///                                    ###
///               %%        28         # Stuffing bits...
///     @ 0x0002C DPHY_RB2             (R-)
///               %unsigned 1  txreadyesc_0
///                                    ###
///                                    * Escape Mode Transmit Ready This signal indicates that the data is accepted by the lane module to be serially transmitted.txreadyesc_0 is synchronous with the rising edge of txclkesc.
///                                    ###
///               %unsigned 1  txreadyesc_1
///                                    ###
///                                    * Escape Mode Transmit Ready This signal indicates that the data is accepted by the lane module to be serially transmitted.txreadyesc_1 is synchronous with the rising edge of txclkesc.
///                                    ###
///               %unsigned 1  txreadyesc_2
///                                    ###
///                                    * Escape Mode Transmit Ready This signal indicates that the data is accepted by the lane module to be serially transmitted.txreadyesc_2 is synchronous with the rising edge of txclkesc.
///                                    ###
///               %unsigned 1  txreadyesc_3
///                                    ###
///                                    * Escape Mode Transmit Ready This signal indicates that the data is accepted by the lane module to be serially transmitted.txreadyesc_3 is synchronous with the rising edge of txclkesc.
///                                    ###
///               %unsigned 1  errcontrol_0
///                                    ###
///                                    * Control ErrorThis signal is asserted when an incorrect line state sequence is detected (for example, if a turnaround request or Escape mode request is immediately followed by a Stop state instead of the required Bridge state, this signal is asserted and remains high until the line returns to Stop state).
///                                    ###
///               %unsigned 1  errcontentionlp0_0
///                                    ###
///                                    * LP0 Contention ErrorThis signal is asserted when a lane module functioning as TX, while its base direction is RX detects a contention situation on a line while trying to drive the line low.
///                                    ###
///               %unsigned 1  errcontentionlp1_0
///                                    ###
///                                    * LP1 Contention ErrorThis signal is asserted when a lane module functioning as TX, while its base direction is RX detects a contention situation on a line while trying to drive the line high.
///                                    ###
///               %%        25         # Stuffing bits...
///     @ 0x00030 DPHY_RB3             (R-)
///               %unsigned 8  rxdataesc_0
///                                    ###
///                                    * Escape Mode Receive Data BusThis is the 8-bit bus data output received by the lane interconnect. The signal rxdataesc_0[0] is received first. Data is transferred on the rising edges of rxclkesc_0.
///                                    ###
///               %unsigned 4  rxtriggeresc_0
///                                    ###
///                                    * Escape Mode Receive Trigger 0-3This signal indicates that a trigger event has been received in the lane interconnect. The asserted rxtriggeresc_0 signal remains active until a Stop state is detected on the lane interconnect.¦ rxtriggeresc_0[0] corresponds to Reset-Trigger.¦ rxtriggeresc_0[1] corresponds to Unknown-3 Trigger.¦ rxtriggeresc_0[2] corresponds to Unknown-4 Trigger.¦ rxtriggeresc_0[3] corresponds to Unknown-5 Trigger
///                                    ###
///               %unsigned 1  rxlpdtesc_0
///                                    ###
///                                    * Escape Low-Power Data Receive ModeThis signal is asserted to indicate that the lane module is in low-power data receive mode. While in this mode, received data is driven onto rxdataesc_0 output bus when rxvalidesc 0 is active. rxlpdtesc_0 remains asserted until a Stop state is detected on the lane interconnect.
///                                    ###
///               %unsigned 1  rxulpsesc_0
///                                    ###
///                                    * Escape ULP Receive ModeThis signal is asserted to indicate that the lane module has entered the ULP State. The lane module remains in this mode with rxulpsesc_0 asserted until a Stop state is detected on the lane interconnect.
///                                    ###
///               %unsigned 1  rxvalidesc_0
///                                    ###
///                                    * Escape Mode Receive Data ValidThis signal indicates that the lane module is driving valid data to the protocol layer on the rxdataesc_0 bus.Note: There is no separate signal to indicate that the data is ready for process. The protocol layer is expected to process the received data on every rising edge of the rxclkesc_0 where rxvalidesc_0 is asserted.There is no provision in the PHY to slow down or throttle the received data.
///                                    ###
///               %unsigned 1  direction_0
///                                    ###
///                                    * Transmit/Receive DirectionThis signal is used to indicate the current direction of the lane interconnect. When direction_0 is low, the lane interconnect is in transmit mode. When direction_0 is high, the lane interconnect is in receive mode.
///                                    ###
///               %unsigned 1  erresc_0
///                                    ###
///                                    * Escape Entry ErrorIf an unrecognized escape entry command is received, this signal is asserted and remains high until the line returns to Stop state.
///                                    ###
///               %unsigned 1  errsyncesc_0
///                                    ###
///                                    * Low-Power Data Transmission Synchronization ErrorIf the number of bits received during low-power data transmission mode is not a multiple of eight when the transmission ends, this signal is asserted and remains high until the line returns to Stop state.
///                                    ###
///               %%        14         # Stuffing bits...
///     @ 0x00034 DPHY_PLL0            (P)
///               %unsigned 1  updatepll                 0x0
///                                    ###
///                                    * Control for PLL operation frequency updated. Whenexercised, PLL SoC control signals are latched to PLLshadow_registers to set PLL operating frequency.
///                                    ###
///               %%        31         # Stuffing bits...
///     @ 0x00038 DPHY_PLL1            (P)
///               %unsigned 4  n                         0x3
///                                    ###
///                                    * Control of the input frequency division ratio N (1 to 16) for SoC direct PLL control. This signal can control the PLL if pll_shadow_control = 1'b0
///                                    ###
///               %unsigned 10 m                         0xC6
///                                    ###
///                                    * Control of the feedback multiplication ratio M (40 to 625)for SoC direct PLL control. This signal can control the PLL if pll_shadow_control = 1'b0
///                                    ###
///               %unsigned 6  vco_cntrl                 0x1
///                                    ###
///                                    * VCO operating range for SoC direct PLL control, needsto be set appropriately to frequency of operation:For detailed information regarding the VCO ranges see table “VCO Ranges” on page 85This signal can control the PLL if pll_shadow_control = 1'b0
///                                    ###
///               %unsigned 6  prop_cntrl                0xC
///                                    ###
///                                    * Proportional Charge Pump control for SoC direct PLLcontrol. This signal can control the PLL if pll_shadow_control = 1'b0 Power down value=”000000
///                                    ###
///               %unsigned 6  int_cntrl                 0x0
///                                    ###
///                                    * Integral Charge Pump control for SoC direct PLL control.This signal can control the PLL if pll_shadow_control = 1'b0 Power down value=”000000”
///                                    ###
///     @ 0x0003C DPHY_PLL2            (P)
///               %unsigned 2  gmp_cntrl                 0x1
///                                    ###
///                                    * Controls the effective loop-filter resistance (=1/gmp) toincrease/decrease MPLL bandwidth and compensate for change in divider modulus (n_cntrl). For SoC direct PLL control. This signal can control the PLL if pll_shadow_control = 1'b0
///                                    ###
///               %unsigned 7  cpbias_cntrl              0x10
///                                    ###
///                                    * Charge Pump bias control, for SoC direct PLL control.This signal can control the PLL if pll_shadow_control = 1'b0
///                                    ###
///               %unsigned 2  clksel                    0x0
///                                    ###
///                                    * Control of PLL clock output selection.¦ 00 - Clocks stopped¦ 01 - Clock generation¦ 10 - Buffered clkext¦ 11 - ForbiddenFor more information see table “PLL Bypass Settings” on page 62
///                                    ###
///               %unsigned 1  force_lock                0x0
///                                    ###
///                                    * Force lock to SOC¦ 0 – according to lock detector-default¦ 1 – lock indication forced,
///                                    ###
///               %unsigned 1  pll_shadow_control        0x0
///                                    ###
///                                    * Selection of PLL configuration mechanism. PLL can beconfigured through D-PHY or through SoC control and shadow control registers¦ 0: SoC control and shadow registers¦ 1: D-PHY control
///                                    ###
///               %unsigned 1  shadow_clear              0x0
///                                    ###
///                                    * Shadow registers clear. Rise edge sensitive
///                                    ###
///               %unsigned 1  gp_clk_en                 0x0
///                                    ###
///                                    * Enable signal for clkout_gp clock
///                                    ###
///               %%        17         # Stuffing bits...
///     @ 0x00040 DPHY_PLLRB0          (R-)
///               %unsigned 4  n_obs
///                                    ###
///                                    * Output of multiplexer controlled by pll_shadow_controlsignal. This output signal represents the control signal provided by PHY test control registers or SoC control depending on pll_shadow_control selection. Used for SOC observability.
///                                    ###
///               %unsigned 10 m_obs
///                                    ###
///                                    * Output of multiplexer controlled by pll_shadow_controlsignal. This output signal represents the control signal provided by PHY test control registers or SoC control depending on pll_shadow_control selection. Used for SOC observability.
///                                    ###
///               %unsigned 6  vco_cntrl_obs
///                                    ###
///                                    * Output of multiplexer controlled by pll_shadow_controlsignal. This output signal represents the control signal provided by PHY test control registers or SoC control depending on pll_shadow_control selection. Used for SOC observability
///                                    ###
///               %unsigned 6  prop_cntrl_obs
///                                    ###
///                                    * Output of multiplexer controlled by pll_shadow_controlsignal. This output signal represents the control signal provided by PHY test control registers or SoC control depending on pll_shadow_control selection. Used for SOC observability.
///                                    ###
///               %unsigned 6  int_cntrl_obs
///                                    ###
///                                    * Output of multiplexer controlled by pll_shadow_controlsignal. This output signal represents the control signal provided by PHY test control registers or SoC control depending on pll_shadow_control selection. Used for SOC observability
///                                    ###
///     @ 0x00044 DPHY_PLLRB1          (R-)
///               %unsigned 2  gmp_cntrl_obs
///                                    ###
///                                    * Output of multiplexer controlled by pll_shadow_controlsignal. This output signal represents the control signal provided by PHY test control registers or SoC control depending on pll_shadow_control selection. Used for SOC observability.
///                                    ###
///               %unsigned 7  cpbias_cntrl_obs
///                                    ###
///                                    * Output of multiplexer controlled by pll_shadow_controlsignal. This output signal represents the control signal provided by PHY test control registers or SoC control depending on pll_shadow_control selection. Used for SOC observability
///                                    ###
///               %unsigned 1  pll_shadow_control_obs
///                                    ###
///                                    * Output of multiplexer controlled by pll_shadow_controlsignal. This output signal represents the control signal provided by PHY test control registers or SoC control depending on pll_shadow_control selection. Used for SOC observability
///                                    ###
///               %unsigned 1  lock_pll
///                                    ###
///                                    * Lock state signaling (0: PLL is not locked, 1: PLL islocked)
///                                    ###
///               %%        21         # Stuffing bits...
///     # # ----------------------------------------------------------
/// $ENDOFINTERFACE  # size:      72B, bits:     283b, padding:     0B
////////////////////////////////////////////////////////////
#ifndef h_DPHYTX
#define h_DPHYTX () {}

    #define     RA_DPHYTX_DPHY_CTL0                            0x0000

    #define     BA_DPHYTX_DPHY_CTL0_BiuCtrlPhyEn               0x0000
    #define     B16DPHYTX_DPHY_CTL0_BiuCtrlPhyEn               0x0000
    #define   LSb32DPHYTX_DPHY_CTL0_BiuCtrlPhyEn                  0
    #define   LSb16DPHYTX_DPHY_CTL0_BiuCtrlPhyEn                  0
    #define       bDPHYTX_DPHY_CTL0_BiuCtrlPhyEn               1
    #define   MSK32DPHYTX_DPHY_CTL0_BiuCtrlPhyEn                  0x00000001
    ///////////////////////////////////////////////////////////
    #define     RA_DPHYTX_DPHY_CTL1                            0x0004

    #define     BA_DPHYTX_DPHY_CTL1_shutdownz                  0x0004
    #define     B16DPHYTX_DPHY_CTL1_shutdownz                  0x0004
    #define   LSb32DPHYTX_DPHY_CTL1_shutdownz                     0
    #define   LSb16DPHYTX_DPHY_CTL1_shutdownz                     0
    #define       bDPHYTX_DPHY_CTL1_shutdownz                  1
    #define   MSK32DPHYTX_DPHY_CTL1_shutdownz                     0x00000001

    #define     BA_DPHYTX_DPHY_CTL1_rstz                       0x0004
    #define     B16DPHYTX_DPHY_CTL1_rstz                       0x0004
    #define   LSb32DPHYTX_DPHY_CTL1_rstz                          1
    #define   LSb16DPHYTX_DPHY_CTL1_rstz                          1
    #define       bDPHYTX_DPHY_CTL1_rstz                       1
    #define   MSK32DPHYTX_DPHY_CTL1_rstz                          0x00000002

    #define     BA_DPHYTX_DPHY_CTL1_forcepll                   0x0004
    #define     B16DPHYTX_DPHY_CTL1_forcepll                   0x0004
    #define   LSb32DPHYTX_DPHY_CTL1_forcepll                      2
    #define   LSb16DPHYTX_DPHY_CTL1_forcepll                      2
    #define       bDPHYTX_DPHY_CTL1_forcepll                   1
    #define   MSK32DPHYTX_DPHY_CTL1_forcepll                      0x00000004

    #define     BA_DPHYTX_DPHY_CTL1_txrequesthsclk             0x0004
    #define     B16DPHYTX_DPHY_CTL1_txrequesthsclk             0x0004
    #define   LSb32DPHYTX_DPHY_CTL1_txrequesthsclk                3
    #define   LSb16DPHYTX_DPHY_CTL1_txrequesthsclk                3
    #define       bDPHYTX_DPHY_CTL1_txrequesthsclk             1
    #define   MSK32DPHYTX_DPHY_CTL1_txrequesthsclk                0x00000008

    #define     BA_DPHYTX_DPHY_CTL1_enableclkBIU               0x0004
    #define     B16DPHYTX_DPHY_CTL1_enableclkBIU               0x0004
    #define   LSb32DPHYTX_DPHY_CTL1_enableclkBIU                  4
    #define   LSb16DPHYTX_DPHY_CTL1_enableclkBIU                  4
    #define       bDPHYTX_DPHY_CTL1_enableclkBIU               1
    #define   MSK32DPHYTX_DPHY_CTL1_enableclkBIU                  0x00000010

    #define     BA_DPHYTX_DPHY_CTL1_turndisable_0              0x0004
    #define     B16DPHYTX_DPHY_CTL1_turndisable_0              0x0004
    #define   LSb32DPHYTX_DPHY_CTL1_turndisable_0                 5
    #define   LSb16DPHYTX_DPHY_CTL1_turndisable_0                 5
    #define       bDPHYTX_DPHY_CTL1_turndisable_0              1
    #define   MSK32DPHYTX_DPHY_CTL1_turndisable_0                 0x00000020

    #define     BA_DPHYTX_DPHY_CTL1_forcerxmode_0              0x0004
    #define     B16DPHYTX_DPHY_CTL1_forcerxmode_0              0x0004
    #define   LSb32DPHYTX_DPHY_CTL1_forcerxmode_0                 6
    #define   LSb16DPHYTX_DPHY_CTL1_forcerxmode_0                 6
    #define       bDPHYTX_DPHY_CTL1_forcerxmode_0              1
    #define   MSK32DPHYTX_DPHY_CTL1_forcerxmode_0                 0x00000040

    #define     BA_DPHYTX_DPHY_CTL1_basedir_0                  0x0004
    #define     B16DPHYTX_DPHY_CTL1_basedir_0                  0x0004
    #define   LSb32DPHYTX_DPHY_CTL1_basedir_0                     7
    #define   LSb16DPHYTX_DPHY_CTL1_basedir_0                     7
    #define       bDPHYTX_DPHY_CTL1_basedir_0                  1
    #define   MSK32DPHYTX_DPHY_CTL1_basedir_0                     0x00000080

    #define     BA_DPHYTX_DPHY_CTL1_forcetxstopmode_0          0x0005
    #define     B16DPHYTX_DPHY_CTL1_forcetxstopmode_0          0x0004
    #define   LSb32DPHYTX_DPHY_CTL1_forcetxstopmode_0             8
    #define   LSb16DPHYTX_DPHY_CTL1_forcetxstopmode_0             8
    #define       bDPHYTX_DPHY_CTL1_forcetxstopmode_0          1
    #define   MSK32DPHYTX_DPHY_CTL1_forcetxstopmode_0             0x00000100

    #define     BA_DPHYTX_DPHY_CTL1_forcetxstopmode_1          0x0005
    #define     B16DPHYTX_DPHY_CTL1_forcetxstopmode_1          0x0004
    #define   LSb32DPHYTX_DPHY_CTL1_forcetxstopmode_1             9
    #define   LSb16DPHYTX_DPHY_CTL1_forcetxstopmode_1             9
    #define       bDPHYTX_DPHY_CTL1_forcetxstopmode_1          1
    #define   MSK32DPHYTX_DPHY_CTL1_forcetxstopmode_1             0x00000200

    #define     BA_DPHYTX_DPHY_CTL1_forcetxstopmode_2          0x0005
    #define     B16DPHYTX_DPHY_CTL1_forcetxstopmode_2          0x0004
    #define   LSb32DPHYTX_DPHY_CTL1_forcetxstopmode_2             10
    #define   LSb16DPHYTX_DPHY_CTL1_forcetxstopmode_2             10
    #define       bDPHYTX_DPHY_CTL1_forcetxstopmode_2          1
    #define   MSK32DPHYTX_DPHY_CTL1_forcetxstopmode_2             0x00000400

    #define     BA_DPHYTX_DPHY_CTL1_forcetxstopmode_3          0x0005
    #define     B16DPHYTX_DPHY_CTL1_forcetxstopmode_3          0x0004
    #define   LSb32DPHYTX_DPHY_CTL1_forcetxstopmode_3             11
    #define   LSb16DPHYTX_DPHY_CTL1_forcetxstopmode_3             11
    #define       bDPHYTX_DPHY_CTL1_forcetxstopmode_3          1
    #define   MSK32DPHYTX_DPHY_CTL1_forcetxstopmode_3             0x00000800

    #define     BA_DPHYTX_DPHY_CTL1_enable_0                   0x0005
    #define     B16DPHYTX_DPHY_CTL1_enable_0                   0x0004
    #define   LSb32DPHYTX_DPHY_CTL1_enable_0                      12
    #define   LSb16DPHYTX_DPHY_CTL1_enable_0                      12
    #define       bDPHYTX_DPHY_CTL1_enable_0                   1
    #define   MSK32DPHYTX_DPHY_CTL1_enable_0                      0x00001000

    #define     BA_DPHYTX_DPHY_CTL1_enable_1                   0x0005
    #define     B16DPHYTX_DPHY_CTL1_enable_1                   0x0004
    #define   LSb32DPHYTX_DPHY_CTL1_enable_1                      13
    #define   LSb16DPHYTX_DPHY_CTL1_enable_1                      13
    #define       bDPHYTX_DPHY_CTL1_enable_1                   1
    #define   MSK32DPHYTX_DPHY_CTL1_enable_1                      0x00002000

    #define     BA_DPHYTX_DPHY_CTL1_enable_2                   0x0005
    #define     B16DPHYTX_DPHY_CTL1_enable_2                   0x0004
    #define   LSb32DPHYTX_DPHY_CTL1_enable_2                      14
    #define   LSb16DPHYTX_DPHY_CTL1_enable_2                      14
    #define       bDPHYTX_DPHY_CTL1_enable_2                   1
    #define   MSK32DPHYTX_DPHY_CTL1_enable_2                      0x00004000

    #define     BA_DPHYTX_DPHY_CTL1_enable_3                   0x0005
    #define     B16DPHYTX_DPHY_CTL1_enable_3                   0x0004
    #define   LSb32DPHYTX_DPHY_CTL1_enable_3                      15
    #define   LSb16DPHYTX_DPHY_CTL1_enable_3                      15
    #define       bDPHYTX_DPHY_CTL1_enable_3                   1
    #define   MSK32DPHYTX_DPHY_CTL1_enable_3                      0x00008000

    #define     BA_DPHYTX_DPHY_CTL1_hsfreqrange                0x0006
    #define     B16DPHYTX_DPHY_CTL1_hsfreqrange                0x0006
    #define   LSb32DPHYTX_DPHY_CTL1_hsfreqrange                   16
    #define   LSb16DPHYTX_DPHY_CTL1_hsfreqrange                   0
    #define       bDPHYTX_DPHY_CTL1_hsfreqrange                7
    #define   MSK32DPHYTX_DPHY_CTL1_hsfreqrange                   0x007F0000

    #define     BA_DPHYTX_DPHY_CTL1_cont_en                    0x0006
    #define     B16DPHYTX_DPHY_CTL1_cont_en                    0x0006
    #define   LSb32DPHYTX_DPHY_CTL1_cont_en                       23
    #define   LSb16DPHYTX_DPHY_CTL1_cont_en                       7
    #define       bDPHYTX_DPHY_CTL1_cont_en                    1
    #define   MSK32DPHYTX_DPHY_CTL1_cont_en                       0x00800000

    #define     BA_DPHYTX_DPHY_CTL1_cfgclkfreqrange            0x0007
    #define     B16DPHYTX_DPHY_CTL1_cfgclkfreqrange            0x0006
    #define   LSb32DPHYTX_DPHY_CTL1_cfgclkfreqrange               24
    #define   LSb16DPHYTX_DPHY_CTL1_cfgclkfreqrange               8
    #define       bDPHYTX_DPHY_CTL1_cfgclkfreqrange            6
    #define   MSK32DPHYTX_DPHY_CTL1_cfgclkfreqrange               0x3F000000

    #define     BA_DPHYTX_DPHY_CTL1_biston                     0x0007
    #define     B16DPHYTX_DPHY_CTL1_biston                     0x0006
    #define   LSb32DPHYTX_DPHY_CTL1_biston                        30
    #define   LSb16DPHYTX_DPHY_CTL1_biston                        14
    #define       bDPHYTX_DPHY_CTL1_biston                     1
    #define   MSK32DPHYTX_DPHY_CTL1_biston                        0x40000000
    ///////////////////////////////////////////////////////////
    #define     RA_DPHYTX_DPHY_CTL2                            0x0008

    #define     BA_DPHYTX_DPHY_CTL2_txulpsclkBIU               0x0008
    #define     B16DPHYTX_DPHY_CTL2_txulpsclkBIU               0x0008
    #define   LSb32DPHYTX_DPHY_CTL2_txulpsclkBIU                  0
    #define   LSb16DPHYTX_DPHY_CTL2_txulpsclkBIU                  0
    #define       bDPHYTX_DPHY_CTL2_txulpsclkBIU               1
    #define   MSK32DPHYTX_DPHY_CTL2_txulpsclkBIU                  0x00000001

    #define     BA_DPHYTX_DPHY_CTL2_txulpsexitclk              0x0008
    #define     B16DPHYTX_DPHY_CTL2_txulpsexitclk              0x0008
    #define   LSb32DPHYTX_DPHY_CTL2_txulpsexitclk                 1
    #define   LSb16DPHYTX_DPHY_CTL2_txulpsexitclk                 1
    #define       bDPHYTX_DPHY_CTL2_txulpsexitclk              1
    #define   MSK32DPHYTX_DPHY_CTL2_txulpsexitclk                 0x00000002

    #define     BA_DPHYTX_DPHY_CTL2_turnrequest_0              0x0008
    #define     B16DPHYTX_DPHY_CTL2_turnrequest_0              0x0008
    #define   LSb32DPHYTX_DPHY_CTL2_turnrequest_0                 2
    #define   LSb16DPHYTX_DPHY_CTL2_turnrequest_0                 2
    #define       bDPHYTX_DPHY_CTL2_turnrequest_0              1
    #define   MSK32DPHYTX_DPHY_CTL2_turnrequest_0                 0x00000004
    ///////////////////////////////////////////////////////////
    #define     RA_DPHYTX_DPHY_CTL3                            0x000C

    #define     BA_DPHYTX_DPHY_CTL3_txdataesc_0                0x000C
    #define     B16DPHYTX_DPHY_CTL3_txdataesc_0                0x000C
    #define   LSb32DPHYTX_DPHY_CTL3_txdataesc_0                   0
    #define   LSb16DPHYTX_DPHY_CTL3_txdataesc_0                   0
    #define       bDPHYTX_DPHY_CTL3_txdataesc_0                8
    #define   MSK32DPHYTX_DPHY_CTL3_txdataesc_0                   0x000000FF

    #define     BA_DPHYTX_DPHY_CTL3_txtriggeresc_0             0x000D
    #define     B16DPHYTX_DPHY_CTL3_txtriggeresc_0             0x000C
    #define   LSb32DPHYTX_DPHY_CTL3_txtriggeresc_0                8
    #define   LSb16DPHYTX_DPHY_CTL3_txtriggeresc_0                8
    #define       bDPHYTX_DPHY_CTL3_txtriggeresc_0             4
    #define   MSK32DPHYTX_DPHY_CTL3_txtriggeresc_0                0x00000F00

    #define     BA_DPHYTX_DPHY_CTL3_txrequestesc_0             0x000D
    #define     B16DPHYTX_DPHY_CTL3_txrequestesc_0             0x000C
    #define   LSb32DPHYTX_DPHY_CTL3_txrequestesc_0                12
    #define   LSb16DPHYTX_DPHY_CTL3_txrequestesc_0                12
    #define       bDPHYTX_DPHY_CTL3_txrequestesc_0             1
    #define   MSK32DPHYTX_DPHY_CTL3_txrequestesc_0                0x00001000

    #define     BA_DPHYTX_DPHY_CTL3_txlpdtesc_0                0x000D
    #define     B16DPHYTX_DPHY_CTL3_txlpdtesc_0                0x000C
    #define   LSb32DPHYTX_DPHY_CTL3_txlpdtesc_0                   13
    #define   LSb16DPHYTX_DPHY_CTL3_txlpdtesc_0                   13
    #define       bDPHYTX_DPHY_CTL3_txlpdtesc_0                1
    #define   MSK32DPHYTX_DPHY_CTL3_txlpdtesc_0                   0x00002000

    #define     BA_DPHYTX_DPHY_CTL3_txulpsesc_0                0x000D
    #define     B16DPHYTX_DPHY_CTL3_txulpsesc_0                0x000C
    #define   LSb32DPHYTX_DPHY_CTL3_txulpsesc_0                   14
    #define   LSb16DPHYTX_DPHY_CTL3_txulpsesc_0                   14
    #define       bDPHYTX_DPHY_CTL3_txulpsesc_0                1
    #define   MSK32DPHYTX_DPHY_CTL3_txulpsesc_0                   0x00004000

    #define     BA_DPHYTX_DPHY_CTL3_txulpsexit_0               0x000D
    #define     B16DPHYTX_DPHY_CTL3_txulpsexit_0               0x000C
    #define   LSb32DPHYTX_DPHY_CTL3_txulpsexit_0                  15
    #define   LSb16DPHYTX_DPHY_CTL3_txulpsexit_0                  15
    #define       bDPHYTX_DPHY_CTL3_txulpsexit_0               1
    #define   MSK32DPHYTX_DPHY_CTL3_txulpsexit_0                  0x00008000

    #define     BA_DPHYTX_DPHY_CTL3_txvalidesc_0               0x000E
    #define     B16DPHYTX_DPHY_CTL3_txvalidesc_0               0x000E
    #define   LSb32DPHYTX_DPHY_CTL3_txvalidesc_0                  16
    #define   LSb16DPHYTX_DPHY_CTL3_txvalidesc_0                  0
    #define       bDPHYTX_DPHY_CTL3_txvalidesc_0               1
    #define   MSK32DPHYTX_DPHY_CTL3_txvalidesc_0                  0x00010000
    ///////////////////////////////////////////////////////////
    #define     RA_DPHYTX_DPHY_CTL4                            0x0010

    #define     BA_DPHYTX_DPHY_CTL4_txdataesc_1                0x0010
    #define     B16DPHYTX_DPHY_CTL4_txdataesc_1                0x0010
    #define   LSb32DPHYTX_DPHY_CTL4_txdataesc_1                   0
    #define   LSb16DPHYTX_DPHY_CTL4_txdataesc_1                   0
    #define       bDPHYTX_DPHY_CTL4_txdataesc_1                8
    #define   MSK32DPHYTX_DPHY_CTL4_txdataesc_1                   0x000000FF

    #define     BA_DPHYTX_DPHY_CTL4_txtriggeresc_1             0x0011
    #define     B16DPHYTX_DPHY_CTL4_txtriggeresc_1             0x0010
    #define   LSb32DPHYTX_DPHY_CTL4_txtriggeresc_1                8
    #define   LSb16DPHYTX_DPHY_CTL4_txtriggeresc_1                8
    #define       bDPHYTX_DPHY_CTL4_txtriggeresc_1             4
    #define   MSK32DPHYTX_DPHY_CTL4_txtriggeresc_1                0x00000F00

    #define     BA_DPHYTX_DPHY_CTL4_txrequestesc_1             0x0011
    #define     B16DPHYTX_DPHY_CTL4_txrequestesc_1             0x0010
    #define   LSb32DPHYTX_DPHY_CTL4_txrequestesc_1                12
    #define   LSb16DPHYTX_DPHY_CTL4_txrequestesc_1                12
    #define       bDPHYTX_DPHY_CTL4_txrequestesc_1             1
    #define   MSK32DPHYTX_DPHY_CTL4_txrequestesc_1                0x00001000

    #define     BA_DPHYTX_DPHY_CTL4_txlpdtesc_1                0x0011
    #define     B16DPHYTX_DPHY_CTL4_txlpdtesc_1                0x0010
    #define   LSb32DPHYTX_DPHY_CTL4_txlpdtesc_1                   13
    #define   LSb16DPHYTX_DPHY_CTL4_txlpdtesc_1                   13
    #define       bDPHYTX_DPHY_CTL4_txlpdtesc_1                1
    #define   MSK32DPHYTX_DPHY_CTL4_txlpdtesc_1                   0x00002000

    #define     BA_DPHYTX_DPHY_CTL4_txulpsesc_1                0x0011
    #define     B16DPHYTX_DPHY_CTL4_txulpsesc_1                0x0010
    #define   LSb32DPHYTX_DPHY_CTL4_txulpsesc_1                   14
    #define   LSb16DPHYTX_DPHY_CTL4_txulpsesc_1                   14
    #define       bDPHYTX_DPHY_CTL4_txulpsesc_1                1
    #define   MSK32DPHYTX_DPHY_CTL4_txulpsesc_1                   0x00004000

    #define     BA_DPHYTX_DPHY_CTL4_txulpsexit_1               0x0011
    #define     B16DPHYTX_DPHY_CTL4_txulpsexit_1               0x0010
    #define   LSb32DPHYTX_DPHY_CTL4_txulpsexit_1                  15
    #define   LSb16DPHYTX_DPHY_CTL4_txulpsexit_1                  15
    #define       bDPHYTX_DPHY_CTL4_txulpsexit_1               1
    #define   MSK32DPHYTX_DPHY_CTL4_txulpsexit_1                  0x00008000

    #define     BA_DPHYTX_DPHY_CTL4_txvalidesc_1               0x0012
    #define     B16DPHYTX_DPHY_CTL4_txvalidesc_1               0x0012
    #define   LSb32DPHYTX_DPHY_CTL4_txvalidesc_1                  16
    #define   LSb16DPHYTX_DPHY_CTL4_txvalidesc_1                  0
    #define       bDPHYTX_DPHY_CTL4_txvalidesc_1               1
    #define   MSK32DPHYTX_DPHY_CTL4_txvalidesc_1                  0x00010000
    ///////////////////////////////////////////////////////////
    #define     RA_DPHYTX_DPHY_CTL5                            0x0014

    #define     BA_DPHYTX_DPHY_CTL5_txdataesc_2                0x0014
    #define     B16DPHYTX_DPHY_CTL5_txdataesc_2                0x0014
    #define   LSb32DPHYTX_DPHY_CTL5_txdataesc_2                   0
    #define   LSb16DPHYTX_DPHY_CTL5_txdataesc_2                   0
    #define       bDPHYTX_DPHY_CTL5_txdataesc_2                8
    #define   MSK32DPHYTX_DPHY_CTL5_txdataesc_2                   0x000000FF

    #define     BA_DPHYTX_DPHY_CTL5_txtriggeresc_2             0x0015
    #define     B16DPHYTX_DPHY_CTL5_txtriggeresc_2             0x0014
    #define   LSb32DPHYTX_DPHY_CTL5_txtriggeresc_2                8
    #define   LSb16DPHYTX_DPHY_CTL5_txtriggeresc_2                8
    #define       bDPHYTX_DPHY_CTL5_txtriggeresc_2             4
    #define   MSK32DPHYTX_DPHY_CTL5_txtriggeresc_2                0x00000F00

    #define     BA_DPHYTX_DPHY_CTL5_txrequestesc_2             0x0015
    #define     B16DPHYTX_DPHY_CTL5_txrequestesc_2             0x0014
    #define   LSb32DPHYTX_DPHY_CTL5_txrequestesc_2                12
    #define   LSb16DPHYTX_DPHY_CTL5_txrequestesc_2                12
    #define       bDPHYTX_DPHY_CTL5_txrequestesc_2             1
    #define   MSK32DPHYTX_DPHY_CTL5_txrequestesc_2                0x00001000

    #define     BA_DPHYTX_DPHY_CTL5_txlpdtesc_2                0x0015
    #define     B16DPHYTX_DPHY_CTL5_txlpdtesc_2                0x0014
    #define   LSb32DPHYTX_DPHY_CTL5_txlpdtesc_2                   13
    #define   LSb16DPHYTX_DPHY_CTL5_txlpdtesc_2                   13
    #define       bDPHYTX_DPHY_CTL5_txlpdtesc_2                1
    #define   MSK32DPHYTX_DPHY_CTL5_txlpdtesc_2                   0x00002000

    #define     BA_DPHYTX_DPHY_CTL5_txulpsesc_2                0x0015
    #define     B16DPHYTX_DPHY_CTL5_txulpsesc_2                0x0014
    #define   LSb32DPHYTX_DPHY_CTL5_txulpsesc_2                   14
    #define   LSb16DPHYTX_DPHY_CTL5_txulpsesc_2                   14
    #define       bDPHYTX_DPHY_CTL5_txulpsesc_2                1
    #define   MSK32DPHYTX_DPHY_CTL5_txulpsesc_2                   0x00004000

    #define     BA_DPHYTX_DPHY_CTL5_txulpsexit_2               0x0015
    #define     B16DPHYTX_DPHY_CTL5_txulpsexit_2               0x0014
    #define   LSb32DPHYTX_DPHY_CTL5_txulpsexit_2                  15
    #define   LSb16DPHYTX_DPHY_CTL5_txulpsexit_2                  15
    #define       bDPHYTX_DPHY_CTL5_txulpsexit_2               1
    #define   MSK32DPHYTX_DPHY_CTL5_txulpsexit_2                  0x00008000

    #define     BA_DPHYTX_DPHY_CTL5_txvalidesc_2               0x0016
    #define     B16DPHYTX_DPHY_CTL5_txvalidesc_2               0x0016
    #define   LSb32DPHYTX_DPHY_CTL5_txvalidesc_2                  16
    #define   LSb16DPHYTX_DPHY_CTL5_txvalidesc_2                  0
    #define       bDPHYTX_DPHY_CTL5_txvalidesc_2               1
    #define   MSK32DPHYTX_DPHY_CTL5_txvalidesc_2                  0x00010000
    ///////////////////////////////////////////////////////////
    #define     RA_DPHYTX_DPHY_CTL6                            0x0018

    #define     BA_DPHYTX_DPHY_CTL6_txdataesc_3                0x0018
    #define     B16DPHYTX_DPHY_CTL6_txdataesc_3                0x0018
    #define   LSb32DPHYTX_DPHY_CTL6_txdataesc_3                   0
    #define   LSb16DPHYTX_DPHY_CTL6_txdataesc_3                   0
    #define       bDPHYTX_DPHY_CTL6_txdataesc_3                8
    #define   MSK32DPHYTX_DPHY_CTL6_txdataesc_3                   0x000000FF

    #define     BA_DPHYTX_DPHY_CTL6_txtriggeresc_3             0x0019
    #define     B16DPHYTX_DPHY_CTL6_txtriggeresc_3             0x0018
    #define   LSb32DPHYTX_DPHY_CTL6_txtriggeresc_3                8
    #define   LSb16DPHYTX_DPHY_CTL6_txtriggeresc_3                8
    #define       bDPHYTX_DPHY_CTL6_txtriggeresc_3             4
    #define   MSK32DPHYTX_DPHY_CTL6_txtriggeresc_3                0x00000F00

    #define     BA_DPHYTX_DPHY_CTL6_txrequestesc_3             0x0019
    #define     B16DPHYTX_DPHY_CTL6_txrequestesc_3             0x0018
    #define   LSb32DPHYTX_DPHY_CTL6_txrequestesc_3                12
    #define   LSb16DPHYTX_DPHY_CTL6_txrequestesc_3                12
    #define       bDPHYTX_DPHY_CTL6_txrequestesc_3             1
    #define   MSK32DPHYTX_DPHY_CTL6_txrequestesc_3                0x00001000

    #define     BA_DPHYTX_DPHY_CTL6_txlpdtesc_3                0x0019
    #define     B16DPHYTX_DPHY_CTL6_txlpdtesc_3                0x0018
    #define   LSb32DPHYTX_DPHY_CTL6_txlpdtesc_3                   13
    #define   LSb16DPHYTX_DPHY_CTL6_txlpdtesc_3                   13
    #define       bDPHYTX_DPHY_CTL6_txlpdtesc_3                1
    #define   MSK32DPHYTX_DPHY_CTL6_txlpdtesc_3                   0x00002000

    #define     BA_DPHYTX_DPHY_CTL6_txulpsesc_3                0x0019
    #define     B16DPHYTX_DPHY_CTL6_txulpsesc_3                0x0018
    #define   LSb32DPHYTX_DPHY_CTL6_txulpsesc_3                   14
    #define   LSb16DPHYTX_DPHY_CTL6_txulpsesc_3                   14
    #define       bDPHYTX_DPHY_CTL6_txulpsesc_3                1
    #define   MSK32DPHYTX_DPHY_CTL6_txulpsesc_3                   0x00004000

    #define     BA_DPHYTX_DPHY_CTL6_txulpsexit_3               0x0019
    #define     B16DPHYTX_DPHY_CTL6_txulpsexit_3               0x0018
    #define   LSb32DPHYTX_DPHY_CTL6_txulpsexit_3                  15
    #define   LSb16DPHYTX_DPHY_CTL6_txulpsexit_3                  15
    #define       bDPHYTX_DPHY_CTL6_txulpsexit_3               1
    #define   MSK32DPHYTX_DPHY_CTL6_txulpsexit_3                  0x00008000

    #define     BA_DPHYTX_DPHY_CTL6_txvalidesc_3               0x001A
    #define     B16DPHYTX_DPHY_CTL6_txvalidesc_3               0x001A
    #define   LSb32DPHYTX_DPHY_CTL6_txvalidesc_3                  16
    #define   LSb16DPHYTX_DPHY_CTL6_txvalidesc_3                  0
    #define       bDPHYTX_DPHY_CTL6_txvalidesc_3               1
    #define   MSK32DPHYTX_DPHY_CTL6_txvalidesc_3                  0x00010000
    ///////////////////////////////////////////////////////////
    #define     RA_DPHYTX_DPHY_CTL7                            0x001C

    #define     BA_DPHYTX_DPHY_CTL7_txblaneclkSel              0x001C
    #define     B16DPHYTX_DPHY_CTL7_txblaneclkSel              0x001C
    #define   LSb32DPHYTX_DPHY_CTL7_txblaneclkSel                 0
    #define   LSb16DPHYTX_DPHY_CTL7_txblaneclkSel                 0
    #define       bDPHYTX_DPHY_CTL7_txblaneclkSel              1
    #define   MSK32DPHYTX_DPHY_CTL7_txblaneclkSel                 0x00000001

    #define     BA_DPHYTX_DPHY_CTL7_txskewcalhsBIU             0x001C
    #define     B16DPHYTX_DPHY_CTL7_txskewcalhsBIU             0x001C
    #define   LSb32DPHYTX_DPHY_CTL7_txskewcalhsBIU                1
    #define   LSb16DPHYTX_DPHY_CTL7_txskewcalhsBIU                1
    #define       bDPHYTX_DPHY_CTL7_txskewcalhsBIU             1
    #define   MSK32DPHYTX_DPHY_CTL7_txskewcalhsBIU                0x00000002

    #define     BA_DPHYTX_DPHY_CTL7_txrequestdatahs_0          0x001C
    #define     B16DPHYTX_DPHY_CTL7_txrequestdatahs_0          0x001C
    #define   LSb32DPHYTX_DPHY_CTL7_txrequestdatahs_0             2
    #define   LSb16DPHYTX_DPHY_CTL7_txrequestdatahs_0             2
    #define       bDPHYTX_DPHY_CTL7_txrequestdatahs_0          1
    #define   MSK32DPHYTX_DPHY_CTL7_txrequestdatahs_0             0x00000004

    #define     BA_DPHYTX_DPHY_CTL7_txrequestdatahs_1          0x001C
    #define     B16DPHYTX_DPHY_CTL7_txrequestdatahs_1          0x001C
    #define   LSb32DPHYTX_DPHY_CTL7_txrequestdatahs_1             3
    #define   LSb16DPHYTX_DPHY_CTL7_txrequestdatahs_1             3
    #define       bDPHYTX_DPHY_CTL7_txrequestdatahs_1          1
    #define   MSK32DPHYTX_DPHY_CTL7_txrequestdatahs_1             0x00000008

    #define     BA_DPHYTX_DPHY_CTL7_txrequestdatahs_2          0x001C
    #define     B16DPHYTX_DPHY_CTL7_txrequestdatahs_2          0x001C
    #define   LSb32DPHYTX_DPHY_CTL7_txrequestdatahs_2             4
    #define   LSb16DPHYTX_DPHY_CTL7_txrequestdatahs_2             4
    #define       bDPHYTX_DPHY_CTL7_txrequestdatahs_2          1
    #define   MSK32DPHYTX_DPHY_CTL7_txrequestdatahs_2             0x00000010

    #define     BA_DPHYTX_DPHY_CTL7_txrequestdatahs_3          0x001C
    #define     B16DPHYTX_DPHY_CTL7_txrequestdatahs_3          0x001C
    #define   LSb32DPHYTX_DPHY_CTL7_txrequestdatahs_3             5
    #define   LSb16DPHYTX_DPHY_CTL7_txrequestdatahs_3             5
    #define       bDPHYTX_DPHY_CTL7_txrequestdatahs_3          1
    #define   MSK32DPHYTX_DPHY_CTL7_txrequestdatahs_3             0x00000020
    ///////////////////////////////////////////////////////////
    #define     RA_DPHYTX_DPHY_CTL8                            0x0020

    #define     BA_DPHYTX_DPHY_CTL8_txdatahs_0                 0x0020
    #define     B16DPHYTX_DPHY_CTL8_txdatahs_0                 0x0020
    #define   LSb32DPHYTX_DPHY_CTL8_txdatahs_0                    0
    #define   LSb16DPHYTX_DPHY_CTL8_txdatahs_0                    0
    #define       bDPHYTX_DPHY_CTL8_txdatahs_0                 8
    #define   MSK32DPHYTX_DPHY_CTL8_txdatahs_0                    0x000000FF

    #define     BA_DPHYTX_DPHY_CTL8_txdatahs_1                 0x0021
    #define     B16DPHYTX_DPHY_CTL8_txdatahs_1                 0x0020
    #define   LSb32DPHYTX_DPHY_CTL8_txdatahs_1                    8
    #define   LSb16DPHYTX_DPHY_CTL8_txdatahs_1                    8
    #define       bDPHYTX_DPHY_CTL8_txdatahs_1                 8
    #define   MSK32DPHYTX_DPHY_CTL8_txdatahs_1                    0x0000FF00

    #define     BA_DPHYTX_DPHY_CTL8_txdatahs_2                 0x0022
    #define     B16DPHYTX_DPHY_CTL8_txdatahs_2                 0x0022
    #define   LSb32DPHYTX_DPHY_CTL8_txdatahs_2                    16
    #define   LSb16DPHYTX_DPHY_CTL8_txdatahs_2                    0
    #define       bDPHYTX_DPHY_CTL8_txdatahs_2                 8
    #define   MSK32DPHYTX_DPHY_CTL8_txdatahs_2                    0x00FF0000

    #define     BA_DPHYTX_DPHY_CTL8_txdatahs_3                 0x0023
    #define     B16DPHYTX_DPHY_CTL8_txdatahs_3                 0x0022
    #define   LSb32DPHYTX_DPHY_CTL8_txdatahs_3                    24
    #define   LSb16DPHYTX_DPHY_CTL8_txdatahs_3                    8
    #define       bDPHYTX_DPHY_CTL8_txdatahs_3                 8
    #define   MSK32DPHYTX_DPHY_CTL8_txdatahs_3                    0xFF000000
    ///////////////////////////////////////////////////////////
    #define     RA_DPHYTX_DPHY_RB0                             0x0024

    #define     BA_DPHYTX_DPHY_RB0_cont_data                   0x0024
    #define     B16DPHYTX_DPHY_RB0_cont_data                   0x0024
    #define   LSb32DPHYTX_DPHY_RB0_cont_data                      0
    #define   LSb16DPHYTX_DPHY_RB0_cont_data                      0
    #define       bDPHYTX_DPHY_RB0_cont_data                   11
    #define   MSK32DPHYTX_DPHY_RB0_cont_data                      0x000007FF

    #define     BA_DPHYTX_DPHY_RB0_lock                        0x0025
    #define     B16DPHYTX_DPHY_RB0_lock                        0x0024
    #define   LSb32DPHYTX_DPHY_RB0_lock                           11
    #define   LSb16DPHYTX_DPHY_RB0_lock                           11
    #define       bDPHYTX_DPHY_RB0_lock                        1
    #define   MSK32DPHYTX_DPHY_RB0_lock                           0x00000800

    #define     BA_DPHYTX_DPHY_RB0_stopstateclk                0x0025
    #define     B16DPHYTX_DPHY_RB0_stopstateclk                0x0024
    #define   LSb32DPHYTX_DPHY_RB0_stopstateclk                   12
    #define   LSb16DPHYTX_DPHY_RB0_stopstateclk                   12
    #define       bDPHYTX_DPHY_RB0_stopstateclk                1
    #define   MSK32DPHYTX_DPHY_RB0_stopstateclk                   0x00001000

    #define     BA_DPHYTX_DPHY_RB0_ulpsactivenotclk            0x0025
    #define     B16DPHYTX_DPHY_RB0_ulpsactivenotclk            0x0024
    #define   LSb32DPHYTX_DPHY_RB0_ulpsactivenotclk               13
    #define   LSb16DPHYTX_DPHY_RB0_ulpsactivenotclk               13
    #define       bDPHYTX_DPHY_RB0_ulpsactivenotclk            1
    #define   MSK32DPHYTX_DPHY_RB0_ulpsactivenotclk               0x00002000

    #define     BA_DPHYTX_DPHY_RB0_stopstatedata_0             0x0025
    #define     B16DPHYTX_DPHY_RB0_stopstatedata_0             0x0024
    #define   LSb32DPHYTX_DPHY_RB0_stopstatedata_0                14
    #define   LSb16DPHYTX_DPHY_RB0_stopstatedata_0                14
    #define       bDPHYTX_DPHY_RB0_stopstatedata_0             1
    #define   MSK32DPHYTX_DPHY_RB0_stopstatedata_0                0x00004000

    #define     BA_DPHYTX_DPHY_RB0_stopstatedata_1             0x0025
    #define     B16DPHYTX_DPHY_RB0_stopstatedata_1             0x0024
    #define   LSb32DPHYTX_DPHY_RB0_stopstatedata_1                15
    #define   LSb16DPHYTX_DPHY_RB0_stopstatedata_1                15
    #define       bDPHYTX_DPHY_RB0_stopstatedata_1             1
    #define   MSK32DPHYTX_DPHY_RB0_stopstatedata_1                0x00008000

    #define     BA_DPHYTX_DPHY_RB0_stopstatedata_2             0x0026
    #define     B16DPHYTX_DPHY_RB0_stopstatedata_2             0x0026
    #define   LSb32DPHYTX_DPHY_RB0_stopstatedata_2                16
    #define   LSb16DPHYTX_DPHY_RB0_stopstatedata_2                0
    #define       bDPHYTX_DPHY_RB0_stopstatedata_2             1
    #define   MSK32DPHYTX_DPHY_RB0_stopstatedata_2                0x00010000

    #define     BA_DPHYTX_DPHY_RB0_stopstatedata_3             0x0026
    #define     B16DPHYTX_DPHY_RB0_stopstatedata_3             0x0026
    #define   LSb32DPHYTX_DPHY_RB0_stopstatedata_3                17
    #define   LSb16DPHYTX_DPHY_RB0_stopstatedata_3                1
    #define       bDPHYTX_DPHY_RB0_stopstatedata_3             1
    #define   MSK32DPHYTX_DPHY_RB0_stopstatedata_3                0x00020000

    #define     BA_DPHYTX_DPHY_RB0_ulpsactivenot_0             0x0026
    #define     B16DPHYTX_DPHY_RB0_ulpsactivenot_0             0x0026
    #define   LSb32DPHYTX_DPHY_RB0_ulpsactivenot_0                18
    #define   LSb16DPHYTX_DPHY_RB0_ulpsactivenot_0                2
    #define       bDPHYTX_DPHY_RB0_ulpsactivenot_0             1
    #define   MSK32DPHYTX_DPHY_RB0_ulpsactivenot_0                0x00040000

    #define     BA_DPHYTX_DPHY_RB0_ulpsactivenot_1             0x0026
    #define     B16DPHYTX_DPHY_RB0_ulpsactivenot_1             0x0026
    #define   LSb32DPHYTX_DPHY_RB0_ulpsactivenot_1                19
    #define   LSb16DPHYTX_DPHY_RB0_ulpsactivenot_1                3
    #define       bDPHYTX_DPHY_RB0_ulpsactivenot_1             1
    #define   MSK32DPHYTX_DPHY_RB0_ulpsactivenot_1                0x00080000

    #define     BA_DPHYTX_DPHY_RB0_ulpsactivenot_2             0x0026
    #define     B16DPHYTX_DPHY_RB0_ulpsactivenot_2             0x0026
    #define   LSb32DPHYTX_DPHY_RB0_ulpsactivenot_2                20
    #define   LSb16DPHYTX_DPHY_RB0_ulpsactivenot_2                4
    #define       bDPHYTX_DPHY_RB0_ulpsactivenot_2             1
    #define   MSK32DPHYTX_DPHY_RB0_ulpsactivenot_2                0x00100000

    #define     BA_DPHYTX_DPHY_RB0_ulpsactivenot_3             0x0026
    #define     B16DPHYTX_DPHY_RB0_ulpsactivenot_3             0x0026
    #define   LSb32DPHYTX_DPHY_RB0_ulpsactivenot_3                21
    #define   LSb16DPHYTX_DPHY_RB0_ulpsactivenot_3                5
    #define       bDPHYTX_DPHY_RB0_ulpsactivenot_3             1
    #define   MSK32DPHYTX_DPHY_RB0_ulpsactivenot_3                0x00200000
    ///////////////////////////////////////////////////////////
    #define     RA_DPHYTX_DPHY_RB1                             0x0028

    #define     BA_DPHYTX_DPHY_RB1_txreadyhs_0                 0x0028
    #define     B16DPHYTX_DPHY_RB1_txreadyhs_0                 0x0028
    #define   LSb32DPHYTX_DPHY_RB1_txreadyhs_0                    0
    #define   LSb16DPHYTX_DPHY_RB1_txreadyhs_0                    0
    #define       bDPHYTX_DPHY_RB1_txreadyhs_0                 1
    #define   MSK32DPHYTX_DPHY_RB1_txreadyhs_0                    0x00000001

    #define     BA_DPHYTX_DPHY_RB1_txreadyhs_1                 0x0028
    #define     B16DPHYTX_DPHY_RB1_txreadyhs_1                 0x0028
    #define   LSb32DPHYTX_DPHY_RB1_txreadyhs_1                    1
    #define   LSb16DPHYTX_DPHY_RB1_txreadyhs_1                    1
    #define       bDPHYTX_DPHY_RB1_txreadyhs_1                 1
    #define   MSK32DPHYTX_DPHY_RB1_txreadyhs_1                    0x00000002

    #define     BA_DPHYTX_DPHY_RB1_txreadyhs_2                 0x0028
    #define     B16DPHYTX_DPHY_RB1_txreadyhs_2                 0x0028
    #define   LSb32DPHYTX_DPHY_RB1_txreadyhs_2                    2
    #define   LSb16DPHYTX_DPHY_RB1_txreadyhs_2                    2
    #define       bDPHYTX_DPHY_RB1_txreadyhs_2                 1
    #define   MSK32DPHYTX_DPHY_RB1_txreadyhs_2                    0x00000004

    #define     BA_DPHYTX_DPHY_RB1_txreadyhs_3                 0x0028
    #define     B16DPHYTX_DPHY_RB1_txreadyhs_3                 0x0028
    #define   LSb32DPHYTX_DPHY_RB1_txreadyhs_3                    3
    #define   LSb16DPHYTX_DPHY_RB1_txreadyhs_3                    3
    #define       bDPHYTX_DPHY_RB1_txreadyhs_3                 1
    #define   MSK32DPHYTX_DPHY_RB1_txreadyhs_3                    0x00000008
    ///////////////////////////////////////////////////////////
    #define     RA_DPHYTX_DPHY_RB2                             0x002C

    #define     BA_DPHYTX_DPHY_RB2_txreadyesc_0                0x002C
    #define     B16DPHYTX_DPHY_RB2_txreadyesc_0                0x002C
    #define   LSb32DPHYTX_DPHY_RB2_txreadyesc_0                   0
    #define   LSb16DPHYTX_DPHY_RB2_txreadyesc_0                   0
    #define       bDPHYTX_DPHY_RB2_txreadyesc_0                1
    #define   MSK32DPHYTX_DPHY_RB2_txreadyesc_0                   0x00000001

    #define     BA_DPHYTX_DPHY_RB2_txreadyesc_1                0x002C
    #define     B16DPHYTX_DPHY_RB2_txreadyesc_1                0x002C
    #define   LSb32DPHYTX_DPHY_RB2_txreadyesc_1                   1
    #define   LSb16DPHYTX_DPHY_RB2_txreadyesc_1                   1
    #define       bDPHYTX_DPHY_RB2_txreadyesc_1                1
    #define   MSK32DPHYTX_DPHY_RB2_txreadyesc_1                   0x00000002

    #define     BA_DPHYTX_DPHY_RB2_txreadyesc_2                0x002C
    #define     B16DPHYTX_DPHY_RB2_txreadyesc_2                0x002C
    #define   LSb32DPHYTX_DPHY_RB2_txreadyesc_2                   2
    #define   LSb16DPHYTX_DPHY_RB2_txreadyesc_2                   2
    #define       bDPHYTX_DPHY_RB2_txreadyesc_2                1
    #define   MSK32DPHYTX_DPHY_RB2_txreadyesc_2                   0x00000004

    #define     BA_DPHYTX_DPHY_RB2_txreadyesc_3                0x002C
    #define     B16DPHYTX_DPHY_RB2_txreadyesc_3                0x002C
    #define   LSb32DPHYTX_DPHY_RB2_txreadyesc_3                   3
    #define   LSb16DPHYTX_DPHY_RB2_txreadyesc_3                   3
    #define       bDPHYTX_DPHY_RB2_txreadyesc_3                1
    #define   MSK32DPHYTX_DPHY_RB2_txreadyesc_3                   0x00000008

    #define     BA_DPHYTX_DPHY_RB2_errcontrol_0                0x002C
    #define     B16DPHYTX_DPHY_RB2_errcontrol_0                0x002C
    #define   LSb32DPHYTX_DPHY_RB2_errcontrol_0                   4
    #define   LSb16DPHYTX_DPHY_RB2_errcontrol_0                   4
    #define       bDPHYTX_DPHY_RB2_errcontrol_0                1
    #define   MSK32DPHYTX_DPHY_RB2_errcontrol_0                   0x00000010

    #define     BA_DPHYTX_DPHY_RB2_errcontentionlp0_0          0x002C
    #define     B16DPHYTX_DPHY_RB2_errcontentionlp0_0          0x002C
    #define   LSb32DPHYTX_DPHY_RB2_errcontentionlp0_0             5
    #define   LSb16DPHYTX_DPHY_RB2_errcontentionlp0_0             5
    #define       bDPHYTX_DPHY_RB2_errcontentionlp0_0          1
    #define   MSK32DPHYTX_DPHY_RB2_errcontentionlp0_0             0x00000020

    #define     BA_DPHYTX_DPHY_RB2_errcontentionlp1_0          0x002C
    #define     B16DPHYTX_DPHY_RB2_errcontentionlp1_0          0x002C
    #define   LSb32DPHYTX_DPHY_RB2_errcontentionlp1_0             6
    #define   LSb16DPHYTX_DPHY_RB2_errcontentionlp1_0             6
    #define       bDPHYTX_DPHY_RB2_errcontentionlp1_0          1
    #define   MSK32DPHYTX_DPHY_RB2_errcontentionlp1_0             0x00000040
    ///////////////////////////////////////////////////////////
    #define     RA_DPHYTX_DPHY_RB3                             0x0030

    #define     BA_DPHYTX_DPHY_RB3_rxdataesc_0                 0x0030
    #define     B16DPHYTX_DPHY_RB3_rxdataesc_0                 0x0030
    #define   LSb32DPHYTX_DPHY_RB3_rxdataesc_0                    0
    #define   LSb16DPHYTX_DPHY_RB3_rxdataesc_0                    0
    #define       bDPHYTX_DPHY_RB3_rxdataesc_0                 8
    #define   MSK32DPHYTX_DPHY_RB3_rxdataesc_0                    0x000000FF

    #define     BA_DPHYTX_DPHY_RB3_rxtriggeresc_0              0x0031
    #define     B16DPHYTX_DPHY_RB3_rxtriggeresc_0              0x0030
    #define   LSb32DPHYTX_DPHY_RB3_rxtriggeresc_0                 8
    #define   LSb16DPHYTX_DPHY_RB3_rxtriggeresc_0                 8
    #define       bDPHYTX_DPHY_RB3_rxtriggeresc_0              4
    #define   MSK32DPHYTX_DPHY_RB3_rxtriggeresc_0                 0x00000F00

    #define     BA_DPHYTX_DPHY_RB3_rxlpdtesc_0                 0x0031
    #define     B16DPHYTX_DPHY_RB3_rxlpdtesc_0                 0x0030
    #define   LSb32DPHYTX_DPHY_RB3_rxlpdtesc_0                    12
    #define   LSb16DPHYTX_DPHY_RB3_rxlpdtesc_0                    12
    #define       bDPHYTX_DPHY_RB3_rxlpdtesc_0                 1
    #define   MSK32DPHYTX_DPHY_RB3_rxlpdtesc_0                    0x00001000

    #define     BA_DPHYTX_DPHY_RB3_rxulpsesc_0                 0x0031
    #define     B16DPHYTX_DPHY_RB3_rxulpsesc_0                 0x0030
    #define   LSb32DPHYTX_DPHY_RB3_rxulpsesc_0                    13
    #define   LSb16DPHYTX_DPHY_RB3_rxulpsesc_0                    13
    #define       bDPHYTX_DPHY_RB3_rxulpsesc_0                 1
    #define   MSK32DPHYTX_DPHY_RB3_rxulpsesc_0                    0x00002000

    #define     BA_DPHYTX_DPHY_RB3_rxvalidesc_0                0x0031
    #define     B16DPHYTX_DPHY_RB3_rxvalidesc_0                0x0030
    #define   LSb32DPHYTX_DPHY_RB3_rxvalidesc_0                   14
    #define   LSb16DPHYTX_DPHY_RB3_rxvalidesc_0                   14
    #define       bDPHYTX_DPHY_RB3_rxvalidesc_0                1
    #define   MSK32DPHYTX_DPHY_RB3_rxvalidesc_0                   0x00004000

    #define     BA_DPHYTX_DPHY_RB3_direction_0                 0x0031
    #define     B16DPHYTX_DPHY_RB3_direction_0                 0x0030
    #define   LSb32DPHYTX_DPHY_RB3_direction_0                    15
    #define   LSb16DPHYTX_DPHY_RB3_direction_0                    15
    #define       bDPHYTX_DPHY_RB3_direction_0                 1
    #define   MSK32DPHYTX_DPHY_RB3_direction_0                    0x00008000

    #define     BA_DPHYTX_DPHY_RB3_erresc_0                    0x0032
    #define     B16DPHYTX_DPHY_RB3_erresc_0                    0x0032
    #define   LSb32DPHYTX_DPHY_RB3_erresc_0                       16
    #define   LSb16DPHYTX_DPHY_RB3_erresc_0                       0
    #define       bDPHYTX_DPHY_RB3_erresc_0                    1
    #define   MSK32DPHYTX_DPHY_RB3_erresc_0                       0x00010000

    #define     BA_DPHYTX_DPHY_RB3_errsyncesc_0                0x0032
    #define     B16DPHYTX_DPHY_RB3_errsyncesc_0                0x0032
    #define   LSb32DPHYTX_DPHY_RB3_errsyncesc_0                   17
    #define   LSb16DPHYTX_DPHY_RB3_errsyncesc_0                   1
    #define       bDPHYTX_DPHY_RB3_errsyncesc_0                1
    #define   MSK32DPHYTX_DPHY_RB3_errsyncesc_0                   0x00020000
    ///////////////////////////////////////////////////////////
    #define     RA_DPHYTX_DPHY_PLL0                            0x0034

    #define     BA_DPHYTX_DPHY_PLL0_updatepll                  0x0034
    #define     B16DPHYTX_DPHY_PLL0_updatepll                  0x0034
    #define   LSb32DPHYTX_DPHY_PLL0_updatepll                     0
    #define   LSb16DPHYTX_DPHY_PLL0_updatepll                     0
    #define       bDPHYTX_DPHY_PLL0_updatepll                  1
    #define   MSK32DPHYTX_DPHY_PLL0_updatepll                     0x00000001
    ///////////////////////////////////////////////////////////
    #define     RA_DPHYTX_DPHY_PLL1                            0x0038

    #define     BA_DPHYTX_DPHY_PLL1_n                          0x0038
    #define     B16DPHYTX_DPHY_PLL1_n                          0x0038
    #define   LSb32DPHYTX_DPHY_PLL1_n                             0
    #define   LSb16DPHYTX_DPHY_PLL1_n                             0
    #define       bDPHYTX_DPHY_PLL1_n                          4
    #define   MSK32DPHYTX_DPHY_PLL1_n                             0x0000000F

    #define     BA_DPHYTX_DPHY_PLL1_m                          0x0038
    #define     B16DPHYTX_DPHY_PLL1_m                          0x0038
    #define   LSb32DPHYTX_DPHY_PLL1_m                             4
    #define   LSb16DPHYTX_DPHY_PLL1_m                             4
    #define       bDPHYTX_DPHY_PLL1_m                          10
    #define   MSK32DPHYTX_DPHY_PLL1_m                             0x00003FF0

    #define     BA_DPHYTX_DPHY_PLL1_vco_cntrl                  0x0039
    #define     B16DPHYTX_DPHY_PLL1_vco_cntrl                  0x0038
    #define   LSb32DPHYTX_DPHY_PLL1_vco_cntrl                     14
    #define   LSb16DPHYTX_DPHY_PLL1_vco_cntrl                     14
    #define       bDPHYTX_DPHY_PLL1_vco_cntrl                  6
    #define   MSK32DPHYTX_DPHY_PLL1_vco_cntrl                     0x000FC000

    #define     BA_DPHYTX_DPHY_PLL1_prop_cntrl                 0x003A
    #define     B16DPHYTX_DPHY_PLL1_prop_cntrl                 0x003A
    #define   LSb32DPHYTX_DPHY_PLL1_prop_cntrl                    20
    #define   LSb16DPHYTX_DPHY_PLL1_prop_cntrl                    4
    #define       bDPHYTX_DPHY_PLL1_prop_cntrl                 6
    #define   MSK32DPHYTX_DPHY_PLL1_prop_cntrl                    0x03F00000

    #define     BA_DPHYTX_DPHY_PLL1_int_cntrl                  0x003B
    #define     B16DPHYTX_DPHY_PLL1_int_cntrl                  0x003A
    #define   LSb32DPHYTX_DPHY_PLL1_int_cntrl                     26
    #define   LSb16DPHYTX_DPHY_PLL1_int_cntrl                     10
    #define       bDPHYTX_DPHY_PLL1_int_cntrl                  6
    #define   MSK32DPHYTX_DPHY_PLL1_int_cntrl                     0xFC000000
    ///////////////////////////////////////////////////////////
    #define     RA_DPHYTX_DPHY_PLL2                            0x003C

    #define     BA_DPHYTX_DPHY_PLL2_gmp_cntrl                  0x003C
    #define     B16DPHYTX_DPHY_PLL2_gmp_cntrl                  0x003C
    #define   LSb32DPHYTX_DPHY_PLL2_gmp_cntrl                     0
    #define   LSb16DPHYTX_DPHY_PLL2_gmp_cntrl                     0
    #define       bDPHYTX_DPHY_PLL2_gmp_cntrl                  2
    #define   MSK32DPHYTX_DPHY_PLL2_gmp_cntrl                     0x00000003

    #define     BA_DPHYTX_DPHY_PLL2_cpbias_cntrl               0x003C
    #define     B16DPHYTX_DPHY_PLL2_cpbias_cntrl               0x003C
    #define   LSb32DPHYTX_DPHY_PLL2_cpbias_cntrl                  2
    #define   LSb16DPHYTX_DPHY_PLL2_cpbias_cntrl                  2
    #define       bDPHYTX_DPHY_PLL2_cpbias_cntrl               7
    #define   MSK32DPHYTX_DPHY_PLL2_cpbias_cntrl                  0x000001FC

    #define     BA_DPHYTX_DPHY_PLL2_clksel                     0x003D
    #define     B16DPHYTX_DPHY_PLL2_clksel                     0x003C
    #define   LSb32DPHYTX_DPHY_PLL2_clksel                        9
    #define   LSb16DPHYTX_DPHY_PLL2_clksel                        9
    #define       bDPHYTX_DPHY_PLL2_clksel                     2
    #define   MSK32DPHYTX_DPHY_PLL2_clksel                        0x00000600

    #define     BA_DPHYTX_DPHY_PLL2_force_lock                 0x003D
    #define     B16DPHYTX_DPHY_PLL2_force_lock                 0x003C
    #define   LSb32DPHYTX_DPHY_PLL2_force_lock                    11
    #define   LSb16DPHYTX_DPHY_PLL2_force_lock                    11
    #define       bDPHYTX_DPHY_PLL2_force_lock                 1
    #define   MSK32DPHYTX_DPHY_PLL2_force_lock                    0x00000800

    #define     BA_DPHYTX_DPHY_PLL2_pll_shadow_control         0x003D
    #define     B16DPHYTX_DPHY_PLL2_pll_shadow_control         0x003C
    #define   LSb32DPHYTX_DPHY_PLL2_pll_shadow_control            12
    #define   LSb16DPHYTX_DPHY_PLL2_pll_shadow_control            12
    #define       bDPHYTX_DPHY_PLL2_pll_shadow_control         1
    #define   MSK32DPHYTX_DPHY_PLL2_pll_shadow_control            0x00001000

    #define     BA_DPHYTX_DPHY_PLL2_shadow_clear               0x003D
    #define     B16DPHYTX_DPHY_PLL2_shadow_clear               0x003C
    #define   LSb32DPHYTX_DPHY_PLL2_shadow_clear                  13
    #define   LSb16DPHYTX_DPHY_PLL2_shadow_clear                  13
    #define       bDPHYTX_DPHY_PLL2_shadow_clear               1
    #define   MSK32DPHYTX_DPHY_PLL2_shadow_clear                  0x00002000

    #define     BA_DPHYTX_DPHY_PLL2_gp_clk_en                  0x003D
    #define     B16DPHYTX_DPHY_PLL2_gp_clk_en                  0x003C
    #define   LSb32DPHYTX_DPHY_PLL2_gp_clk_en                     14
    #define   LSb16DPHYTX_DPHY_PLL2_gp_clk_en                     14
    #define       bDPHYTX_DPHY_PLL2_gp_clk_en                  1
    #define   MSK32DPHYTX_DPHY_PLL2_gp_clk_en                     0x00004000
    ///////////////////////////////////////////////////////////
    #define     RA_DPHYTX_DPHY_PLLRB0                          0x0040

    #define     BA_DPHYTX_DPHY_PLLRB0_n_obs                    0x0040
    #define     B16DPHYTX_DPHY_PLLRB0_n_obs                    0x0040
    #define   LSb32DPHYTX_DPHY_PLLRB0_n_obs                       0
    #define   LSb16DPHYTX_DPHY_PLLRB0_n_obs                       0
    #define       bDPHYTX_DPHY_PLLRB0_n_obs                    4
    #define   MSK32DPHYTX_DPHY_PLLRB0_n_obs                       0x0000000F

    #define     BA_DPHYTX_DPHY_PLLRB0_m_obs                    0x0040
    #define     B16DPHYTX_DPHY_PLLRB0_m_obs                    0x0040
    #define   LSb32DPHYTX_DPHY_PLLRB0_m_obs                       4
    #define   LSb16DPHYTX_DPHY_PLLRB0_m_obs                       4
    #define       bDPHYTX_DPHY_PLLRB0_m_obs                    10
    #define   MSK32DPHYTX_DPHY_PLLRB0_m_obs                       0x00003FF0

    #define     BA_DPHYTX_DPHY_PLLRB0_vco_cntrl_obs            0x0041
    #define     B16DPHYTX_DPHY_PLLRB0_vco_cntrl_obs            0x0040
    #define   LSb32DPHYTX_DPHY_PLLRB0_vco_cntrl_obs               14
    #define   LSb16DPHYTX_DPHY_PLLRB0_vco_cntrl_obs               14
    #define       bDPHYTX_DPHY_PLLRB0_vco_cntrl_obs            6
    #define   MSK32DPHYTX_DPHY_PLLRB0_vco_cntrl_obs               0x000FC000

    #define     BA_DPHYTX_DPHY_PLLRB0_prop_cntrl_obs           0x0042
    #define     B16DPHYTX_DPHY_PLLRB0_prop_cntrl_obs           0x0042
    #define   LSb32DPHYTX_DPHY_PLLRB0_prop_cntrl_obs              20
    #define   LSb16DPHYTX_DPHY_PLLRB0_prop_cntrl_obs              4
    #define       bDPHYTX_DPHY_PLLRB0_prop_cntrl_obs           6
    #define   MSK32DPHYTX_DPHY_PLLRB0_prop_cntrl_obs              0x03F00000

    #define     BA_DPHYTX_DPHY_PLLRB0_int_cntrl_obs            0x0043
    #define     B16DPHYTX_DPHY_PLLRB0_int_cntrl_obs            0x0042
    #define   LSb32DPHYTX_DPHY_PLLRB0_int_cntrl_obs               26
    #define   LSb16DPHYTX_DPHY_PLLRB0_int_cntrl_obs               10
    #define       bDPHYTX_DPHY_PLLRB0_int_cntrl_obs            6
    #define   MSK32DPHYTX_DPHY_PLLRB0_int_cntrl_obs               0xFC000000
    ///////////////////////////////////////////////////////////
    #define     RA_DPHYTX_DPHY_PLLRB1                          0x0044

    #define     BA_DPHYTX_DPHY_PLLRB1_gmp_cntrl_obs            0x0044
    #define     B16DPHYTX_DPHY_PLLRB1_gmp_cntrl_obs            0x0044
    #define   LSb32DPHYTX_DPHY_PLLRB1_gmp_cntrl_obs               0
    #define   LSb16DPHYTX_DPHY_PLLRB1_gmp_cntrl_obs               0
    #define       bDPHYTX_DPHY_PLLRB1_gmp_cntrl_obs            2
    #define   MSK32DPHYTX_DPHY_PLLRB1_gmp_cntrl_obs               0x00000003

    #define     BA_DPHYTX_DPHY_PLLRB1_cpbias_cntrl_obs         0x0044
    #define     B16DPHYTX_DPHY_PLLRB1_cpbias_cntrl_obs         0x0044
    #define   LSb32DPHYTX_DPHY_PLLRB1_cpbias_cntrl_obs            2
    #define   LSb16DPHYTX_DPHY_PLLRB1_cpbias_cntrl_obs            2
    #define       bDPHYTX_DPHY_PLLRB1_cpbias_cntrl_obs         7
    #define   MSK32DPHYTX_DPHY_PLLRB1_cpbias_cntrl_obs            0x000001FC

    #define     BA_DPHYTX_DPHY_PLLRB1_pll_shadow_control_obs   0x0045
    #define     B16DPHYTX_DPHY_PLLRB1_pll_shadow_control_obs   0x0044
    #define   LSb32DPHYTX_DPHY_PLLRB1_pll_shadow_control_obs      9
    #define   LSb16DPHYTX_DPHY_PLLRB1_pll_shadow_control_obs      9
    #define       bDPHYTX_DPHY_PLLRB1_pll_shadow_control_obs   1
    #define   MSK32DPHYTX_DPHY_PLLRB1_pll_shadow_control_obs      0x00000200

    #define     BA_DPHYTX_DPHY_PLLRB1_lock_pll                 0x0045
    #define     B16DPHYTX_DPHY_PLLRB1_lock_pll                 0x0044
    #define   LSb32DPHYTX_DPHY_PLLRB1_lock_pll                    10
    #define   LSb16DPHYTX_DPHY_PLLRB1_lock_pll                    10
    #define       bDPHYTX_DPHY_PLLRB1_lock_pll                 1
    #define   MSK32DPHYTX_DPHY_PLLRB1_lock_pll                    0x00000400
    ///////////////////////////////////////////////////////////

    typedef struct SIE_DPHYTX {
    ///////////////////////////////////////////////////////////
    #define   GET32DPHYTX_DPHY_CTL0_BiuCtrlPhyEn(r32)          _BFGET_(r32, 0, 0)
    #define   SET32DPHYTX_DPHY_CTL0_BiuCtrlPhyEn(r32, v)        _BFSET_(r32, 0, 0, v)
    #define   GET16DPHYTX_DPHY_CTL0_BiuCtrlPhyEn(r16)          _BFGET_(r16, 0, 0)
    #define   SET16DPHYTX_DPHY_CTL0_BiuCtrlPhyEn(r16, v)        _BFSET_(r16, 0, 0, v)

    #define     w32DPHYTX_DPHY_CTL0                            {\
	    UNSG32 uDPHY_CTL0_BiuCtrlPhyEn                     :  1;\
	    UNSG32 RSVDx0_b1                                   : 31;\
	}
    union { UNSG32 u32DPHYTX_DPHY_CTL0;
	    struct w32DPHYTX_DPHY_CTL0;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32DPHYTX_DPHY_CTL1_shutdownz(r32)             _BFGET_(r32, 0, 0)
    #define   SET32DPHYTX_DPHY_CTL1_shutdownz(r32, v)           _BFSET_(r32, 0, 0, v)
    #define   GET16DPHYTX_DPHY_CTL1_shutdownz(r16)             _BFGET_(r16, 0, 0)
    #define   SET16DPHYTX_DPHY_CTL1_shutdownz(r16, v)           _BFSET_(r16, 0, 0, v)

    #define   GET32DPHYTX_DPHY_CTL1_rstz(r32)                  _BFGET_(r32, 1, 1)
    #define   SET32DPHYTX_DPHY_CTL1_rstz(r32, v)                _BFSET_(r32, 1, 1, v)
    #define   GET16DPHYTX_DPHY_CTL1_rstz(r16)                  _BFGET_(r16, 1, 1)
    #define   SET16DPHYTX_DPHY_CTL1_rstz(r16, v)                _BFSET_(r16, 1, 1, v)

    #define   GET32DPHYTX_DPHY_CTL1_forcepll(r32)              _BFGET_(r32, 2, 2)
    #define   SET32DPHYTX_DPHY_CTL1_forcepll(r32, v)            _BFSET_(r32, 2, 2, v)
    #define   GET16DPHYTX_DPHY_CTL1_forcepll(r16)              _BFGET_(r16, 2, 2)
    #define   SET16DPHYTX_DPHY_CTL1_forcepll(r16, v)            _BFSET_(r16, 2, 2, v)

    #define   GET32DPHYTX_DPHY_CTL1_txrequesthsclk(r32)        _BFGET_(r32, 3, 3)
    #define   SET32DPHYTX_DPHY_CTL1_txrequesthsclk(r32, v)      _BFSET_(r32, 3, 3, v)
    #define   GET16DPHYTX_DPHY_CTL1_txrequesthsclk(r16)        _BFGET_(r16, 3, 3)
    #define   SET16DPHYTX_DPHY_CTL1_txrequesthsclk(r16, v)      _BFSET_(r16, 3, 3, v)

    #define   GET32DPHYTX_DPHY_CTL1_enableclkBIU(r32)          _BFGET_(r32, 4, 4)
    #define   SET32DPHYTX_DPHY_CTL1_enableclkBIU(r32, v)        _BFSET_(r32, 4, 4, v)
    #define   GET16DPHYTX_DPHY_CTL1_enableclkBIU(r16)          _BFGET_(r16, 4, 4)
    #define   SET16DPHYTX_DPHY_CTL1_enableclkBIU(r16, v)        _BFSET_(r16, 4, 4, v)

    #define   GET32DPHYTX_DPHY_CTL1_turndisable_0(r32)         _BFGET_(r32, 5, 5)
    #define   SET32DPHYTX_DPHY_CTL1_turndisable_0(r32, v)       _BFSET_(r32, 5, 5, v)
    #define   GET16DPHYTX_DPHY_CTL1_turndisable_0(r16)         _BFGET_(r16, 5, 5)
    #define   SET16DPHYTX_DPHY_CTL1_turndisable_0(r16, v)       _BFSET_(r16, 5, 5, v)

    #define   GET32DPHYTX_DPHY_CTL1_forcerxmode_0(r32)         _BFGET_(r32, 6, 6)
    #define   SET32DPHYTX_DPHY_CTL1_forcerxmode_0(r32, v)       _BFSET_(r32, 6, 6, v)
    #define   GET16DPHYTX_DPHY_CTL1_forcerxmode_0(r16)         _BFGET_(r16, 6, 6)
    #define   SET16DPHYTX_DPHY_CTL1_forcerxmode_0(r16, v)       _BFSET_(r16, 6, 6, v)

    #define   GET32DPHYTX_DPHY_CTL1_basedir_0(r32)             _BFGET_(r32, 7, 7)
    #define   SET32DPHYTX_DPHY_CTL1_basedir_0(r32, v)           _BFSET_(r32, 7, 7, v)
    #define   GET16DPHYTX_DPHY_CTL1_basedir_0(r16)             _BFGET_(r16, 7, 7)
    #define   SET16DPHYTX_DPHY_CTL1_basedir_0(r16, v)           _BFSET_(r16, 7, 7, v)

    #define   GET32DPHYTX_DPHY_CTL1_forcetxstopmode_0(r32)     _BFGET_(r32, 8, 8)
    #define   SET32DPHYTX_DPHY_CTL1_forcetxstopmode_0(r32, v)   _BFSET_(r32, 8, 8, v)
    #define   GET16DPHYTX_DPHY_CTL1_forcetxstopmode_0(r16)     _BFGET_(r16, 8, 8)
    #define   SET16DPHYTX_DPHY_CTL1_forcetxstopmode_0(r16, v)   _BFSET_(r16, 8, 8, v)

    #define   GET32DPHYTX_DPHY_CTL1_forcetxstopmode_1(r32)     _BFGET_(r32, 9, 9)
    #define   SET32DPHYTX_DPHY_CTL1_forcetxstopmode_1(r32, v)   _BFSET_(r32, 9, 9, v)
    #define   GET16DPHYTX_DPHY_CTL1_forcetxstopmode_1(r16)     _BFGET_(r16, 9, 9)
    #define   SET16DPHYTX_DPHY_CTL1_forcetxstopmode_1(r16, v)   _BFSET_(r16, 9, 9, v)

    #define   GET32DPHYTX_DPHY_CTL1_forcetxstopmode_2(r32)     _BFGET_(r32, 10, 10)
    #define   SET32DPHYTX_DPHY_CTL1_forcetxstopmode_2(r32, v)   _BFSET_(r32, 10, 10, v)
    #define   GET16DPHYTX_DPHY_CTL1_forcetxstopmode_2(r16)     _BFGET_(r16, 10, 10)
    #define   SET16DPHYTX_DPHY_CTL1_forcetxstopmode_2(r16, v)   _BFSET_(r16, 10, 10, v)

    #define   GET32DPHYTX_DPHY_CTL1_forcetxstopmode_3(r32)     _BFGET_(r32, 11, 11)
    #define   SET32DPHYTX_DPHY_CTL1_forcetxstopmode_3(r32, v)   _BFSET_(r32, 11, 11, v)
    #define   GET16DPHYTX_DPHY_CTL1_forcetxstopmode_3(r16)     _BFGET_(r16, 11, 11)
    #define   SET16DPHYTX_DPHY_CTL1_forcetxstopmode_3(r16, v)   _BFSET_(r16, 11, 11, v)

    #define   GET32DPHYTX_DPHY_CTL1_enable_0(r32)              _BFGET_(r32, 12, 12)
    #define   SET32DPHYTX_DPHY_CTL1_enable_0(r32, v)            _BFSET_(r32, 12, 12, v)
    #define   GET16DPHYTX_DPHY_CTL1_enable_0(r16)              _BFGET_(r16, 12, 12)
    #define   SET16DPHYTX_DPHY_CTL1_enable_0(r16, v)            _BFSET_(r16, 12, 12, v)

    #define   GET32DPHYTX_DPHY_CTL1_enable_1(r32)              _BFGET_(r32, 13, 13)
    #define   SET32DPHYTX_DPHY_CTL1_enable_1(r32, v)            _BFSET_(r32, 13, 13, v)
    #define   GET16DPHYTX_DPHY_CTL1_enable_1(r16)              _BFGET_(r16, 13, 13)
    #define   SET16DPHYTX_DPHY_CTL1_enable_1(r16, v)            _BFSET_(r16, 13, 13, v)

    #define   GET32DPHYTX_DPHY_CTL1_enable_2(r32)              _BFGET_(r32, 14, 14)
    #define   SET32DPHYTX_DPHY_CTL1_enable_2(r32, v)            _BFSET_(r32, 14, 14, v)
    #define   GET16DPHYTX_DPHY_CTL1_enable_2(r16)              _BFGET_(r16, 14, 14)
    #define   SET16DPHYTX_DPHY_CTL1_enable_2(r16, v)            _BFSET_(r16, 14, 14, v)

    #define   GET32DPHYTX_DPHY_CTL1_enable_3(r32)              _BFGET_(r32, 15, 15)
    #define   SET32DPHYTX_DPHY_CTL1_enable_3(r32, v)            _BFSET_(r32, 15, 15, v)
    #define   GET16DPHYTX_DPHY_CTL1_enable_3(r16)              _BFGET_(r16, 15, 15)
    #define   SET16DPHYTX_DPHY_CTL1_enable_3(r16, v)            _BFSET_(r16, 15, 15, v)

    #define   GET32DPHYTX_DPHY_CTL1_hsfreqrange(r32)           _BFGET_(r32, 22, 16)
    #define   SET32DPHYTX_DPHY_CTL1_hsfreqrange(r32, v)         _BFSET_(r32, 22, 16, v)
    #define   GET16DPHYTX_DPHY_CTL1_hsfreqrange(r16)           _BFGET_(r16, 6, 0)
    #define   SET16DPHYTX_DPHY_CTL1_hsfreqrange(r16, v)         _BFSET_(r16, 6, 0, v)

    #define   GET32DPHYTX_DPHY_CTL1_cont_en(r32)               _BFGET_(r32, 23, 23)
    #define   SET32DPHYTX_DPHY_CTL1_cont_en(r32, v)             _BFSET_(r32, 23, 23, v)
    #define   GET16DPHYTX_DPHY_CTL1_cont_en(r16)               _BFGET_(r16, 7, 7)
    #define   SET16DPHYTX_DPHY_CTL1_cont_en(r16, v)             _BFSET_(r16, 7, 7, v)

    #define   GET32DPHYTX_DPHY_CTL1_cfgclkfreqrange(r32)       _BFGET_(r32, 29, 24)
    #define   SET32DPHYTX_DPHY_CTL1_cfgclkfreqrange(r32, v)     _BFSET_(r32, 29, 24, v)
    #define   GET16DPHYTX_DPHY_CTL1_cfgclkfreqrange(r16)       _BFGET_(r16, 13, 8)
    #define   SET16DPHYTX_DPHY_CTL1_cfgclkfreqrange(r16, v)     _BFSET_(r16, 13, 8, v)

    #define   GET32DPHYTX_DPHY_CTL1_biston(r32)                _BFGET_(r32, 30, 30)
    #define   SET32DPHYTX_DPHY_CTL1_biston(r32, v)              _BFSET_(r32, 30, 30, v)
    #define   GET16DPHYTX_DPHY_CTL1_biston(r16)                _BFGET_(r16, 14, 14)
    #define   SET16DPHYTX_DPHY_CTL1_biston(r16, v)              _BFSET_(r16, 14, 14, v)

    #define     w32DPHYTX_DPHY_CTL1                            {\
	    UNSG32 uDPHY_CTL1_shutdownz                        :  1;\
	    UNSG32 uDPHY_CTL1_rstz                             :  1;\
	    UNSG32 uDPHY_CTL1_forcepll                         :  1;\
	    UNSG32 uDPHY_CTL1_txrequesthsclk                   :  1;\
	    UNSG32 uDPHY_CTL1_enableclkBIU                     :  1;\
	    UNSG32 uDPHY_CTL1_turndisable_0                    :  1;\
	    UNSG32 uDPHY_CTL1_forcerxmode_0                    :  1;\
	    UNSG32 uDPHY_CTL1_basedir_0                        :  1;\
	    UNSG32 uDPHY_CTL1_forcetxstopmode_0                :  1;\
	    UNSG32 uDPHY_CTL1_forcetxstopmode_1                :  1;\
	    UNSG32 uDPHY_CTL1_forcetxstopmode_2                :  1;\
	    UNSG32 uDPHY_CTL1_forcetxstopmode_3                :  1;\
	    UNSG32 uDPHY_CTL1_enable_0                         :  1;\
	    UNSG32 uDPHY_CTL1_enable_1                         :  1;\
	    UNSG32 uDPHY_CTL1_enable_2                         :  1;\
	    UNSG32 uDPHY_CTL1_enable_3                         :  1;\
	    UNSG32 uDPHY_CTL1_hsfreqrange                      :  7;\
	    UNSG32 uDPHY_CTL1_cont_en                          :  1;\
	    UNSG32 uDPHY_CTL1_cfgclkfreqrange                  :  6;\
	    UNSG32 uDPHY_CTL1_biston                           :  1;\
	    UNSG32 RSVDx4_b31                                  :  1;\
	}
    union { UNSG32 u32DPHYTX_DPHY_CTL1;
	    struct w32DPHYTX_DPHY_CTL1;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32DPHYTX_DPHY_CTL2_txulpsclkBIU(r32)          _BFGET_(r32, 0, 0)
    #define   SET32DPHYTX_DPHY_CTL2_txulpsclkBIU(r32, v)        _BFSET_(r32, 0, 0, v)
    #define   GET16DPHYTX_DPHY_CTL2_txulpsclkBIU(r16)          _BFGET_(r16, 0, 0)
    #define   SET16DPHYTX_DPHY_CTL2_txulpsclkBIU(r16, v)        _BFSET_(r16, 0, 0, v)

    #define   GET32DPHYTX_DPHY_CTL2_txulpsexitclk(r32)         _BFGET_(r32, 1, 1)
    #define   SET32DPHYTX_DPHY_CTL2_txulpsexitclk(r32, v)       _BFSET_(r32, 1, 1, v)
    #define   GET16DPHYTX_DPHY_CTL2_txulpsexitclk(r16)         _BFGET_(r16, 1, 1)
    #define   SET16DPHYTX_DPHY_CTL2_txulpsexitclk(r16, v)       _BFSET_(r16, 1, 1, v)

    #define   GET32DPHYTX_DPHY_CTL2_turnrequest_0(r32)         _BFGET_(r32, 2, 2)
    #define   SET32DPHYTX_DPHY_CTL2_turnrequest_0(r32, v)       _BFSET_(r32, 2, 2, v)
    #define   GET16DPHYTX_DPHY_CTL2_turnrequest_0(r16)         _BFGET_(r16, 2, 2)
    #define   SET16DPHYTX_DPHY_CTL2_turnrequest_0(r16, v)       _BFSET_(r16, 2, 2, v)

    #define     w32DPHYTX_DPHY_CTL2                            {\
	    UNSG32 uDPHY_CTL2_txulpsclkBIU                     :  1;\
	    UNSG32 uDPHY_CTL2_txulpsexitclk                    :  1;\
	    UNSG32 uDPHY_CTL2_turnrequest_0                    :  1;\
	    UNSG32 RSVDx8_b3                                   : 29;\
	}
    union { UNSG32 u32DPHYTX_DPHY_CTL2;
	    struct w32DPHYTX_DPHY_CTL2;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32DPHYTX_DPHY_CTL3_txdataesc_0(r32)           _BFGET_(r32, 7, 0)
    #define   SET32DPHYTX_DPHY_CTL3_txdataesc_0(r32, v)         _BFSET_(r32, 7, 0, v)
    #define   GET16DPHYTX_DPHY_CTL3_txdataesc_0(r16)           _BFGET_(r16, 7, 0)
    #define   SET16DPHYTX_DPHY_CTL3_txdataesc_0(r16, v)         _BFSET_(r16, 7, 0, v)

    #define   GET32DPHYTX_DPHY_CTL3_txtriggeresc_0(r32)        _BFGET_(r32, 11, 8)
    #define   SET32DPHYTX_DPHY_CTL3_txtriggeresc_0(r32, v)      _BFSET_(r32, 11, 8, v)
    #define   GET16DPHYTX_DPHY_CTL3_txtriggeresc_0(r16)        _BFGET_(r16, 11, 8)
    #define   SET16DPHYTX_DPHY_CTL3_txtriggeresc_0(r16, v)      _BFSET_(r16, 11, 8, v)

    #define   GET32DPHYTX_DPHY_CTL3_txrequestesc_0(r32)        _BFGET_(r32, 12, 12)
    #define   SET32DPHYTX_DPHY_CTL3_txrequestesc_0(r32, v)      _BFSET_(r32, 12, 12, v)
    #define   GET16DPHYTX_DPHY_CTL3_txrequestesc_0(r16)        _BFGET_(r16, 12, 12)
    #define   SET16DPHYTX_DPHY_CTL3_txrequestesc_0(r16, v)      _BFSET_(r16, 12, 12, v)

    #define   GET32DPHYTX_DPHY_CTL3_txlpdtesc_0(r32)           _BFGET_(r32, 13, 13)
    #define   SET32DPHYTX_DPHY_CTL3_txlpdtesc_0(r32, v)         _BFSET_(r32, 13, 13, v)
    #define   GET16DPHYTX_DPHY_CTL3_txlpdtesc_0(r16)           _BFGET_(r16, 13, 13)
    #define   SET16DPHYTX_DPHY_CTL3_txlpdtesc_0(r16, v)         _BFSET_(r16, 13, 13, v)

    #define   GET32DPHYTX_DPHY_CTL3_txulpsesc_0(r32)           _BFGET_(r32, 14, 14)
    #define   SET32DPHYTX_DPHY_CTL3_txulpsesc_0(r32, v)         _BFSET_(r32, 14, 14, v)
    #define   GET16DPHYTX_DPHY_CTL3_txulpsesc_0(r16)           _BFGET_(r16, 14, 14)
    #define   SET16DPHYTX_DPHY_CTL3_txulpsesc_0(r16, v)         _BFSET_(r16, 14, 14, v)

    #define   GET32DPHYTX_DPHY_CTL3_txulpsexit_0(r32)          _BFGET_(r32, 15, 15)
    #define   SET32DPHYTX_DPHY_CTL3_txulpsexit_0(r32, v)        _BFSET_(r32, 15, 15, v)
    #define   GET16DPHYTX_DPHY_CTL3_txulpsexit_0(r16)          _BFGET_(r16, 15, 15)
    #define   SET16DPHYTX_DPHY_CTL3_txulpsexit_0(r16, v)        _BFSET_(r16, 15, 15, v)

    #define   GET32DPHYTX_DPHY_CTL3_txvalidesc_0(r32)          _BFGET_(r32, 16, 16)
    #define   SET32DPHYTX_DPHY_CTL3_txvalidesc_0(r32, v)        _BFSET_(r32, 16, 16, v)
    #define   GET16DPHYTX_DPHY_CTL3_txvalidesc_0(r16)          _BFGET_(r16, 0, 0)
    #define   SET16DPHYTX_DPHY_CTL3_txvalidesc_0(r16, v)        _BFSET_(r16, 0, 0, v)

    #define     w32DPHYTX_DPHY_CTL3                            {\
	    UNSG32 uDPHY_CTL3_txdataesc_0                      :  8;\
	    UNSG32 uDPHY_CTL3_txtriggeresc_0                   :  4;\
	    UNSG32 uDPHY_CTL3_txrequestesc_0                   :  1;\
	    UNSG32 uDPHY_CTL3_txlpdtesc_0                      :  1;\
	    UNSG32 uDPHY_CTL3_txulpsesc_0                      :  1;\
	    UNSG32 uDPHY_CTL3_txulpsexit_0                     :  1;\
	    UNSG32 uDPHY_CTL3_txvalidesc_0                     :  1;\
	    UNSG32 RSVDxC_b17                                  : 15;\
	}
    union { UNSG32 u32DPHYTX_DPHY_CTL3;
	    struct w32DPHYTX_DPHY_CTL3;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32DPHYTX_DPHY_CTL4_txdataesc_1(r32)           _BFGET_(r32, 7, 0)
    #define   SET32DPHYTX_DPHY_CTL4_txdataesc_1(r32, v)         _BFSET_(r32, 7, 0, v)
    #define   GET16DPHYTX_DPHY_CTL4_txdataesc_1(r16)           _BFGET_(r16, 7, 0)
    #define   SET16DPHYTX_DPHY_CTL4_txdataesc_1(r16, v)         _BFSET_(r16, 7, 0, v)

    #define   GET32DPHYTX_DPHY_CTL4_txtriggeresc_1(r32)        _BFGET_(r32, 11, 8)
    #define   SET32DPHYTX_DPHY_CTL4_txtriggeresc_1(r32, v)      _BFSET_(r32, 11, 8, v)
    #define   GET16DPHYTX_DPHY_CTL4_txtriggeresc_1(r16)        _BFGET_(r16, 11, 8)
    #define   SET16DPHYTX_DPHY_CTL4_txtriggeresc_1(r16, v)      _BFSET_(r16, 11, 8, v)

    #define   GET32DPHYTX_DPHY_CTL4_txrequestesc_1(r32)        _BFGET_(r32, 12, 12)
    #define   SET32DPHYTX_DPHY_CTL4_txrequestesc_1(r32, v)      _BFSET_(r32, 12, 12, v)
    #define   GET16DPHYTX_DPHY_CTL4_txrequestesc_1(r16)        _BFGET_(r16, 12, 12)
    #define   SET16DPHYTX_DPHY_CTL4_txrequestesc_1(r16, v)      _BFSET_(r16, 12, 12, v)

    #define   GET32DPHYTX_DPHY_CTL4_txlpdtesc_1(r32)           _BFGET_(r32, 13, 13)
    #define   SET32DPHYTX_DPHY_CTL4_txlpdtesc_1(r32, v)         _BFSET_(r32, 13, 13, v)
    #define   GET16DPHYTX_DPHY_CTL4_txlpdtesc_1(r16)           _BFGET_(r16, 13, 13)
    #define   SET16DPHYTX_DPHY_CTL4_txlpdtesc_1(r16, v)         _BFSET_(r16, 13, 13, v)

    #define   GET32DPHYTX_DPHY_CTL4_txulpsesc_1(r32)           _BFGET_(r32, 14, 14)
    #define   SET32DPHYTX_DPHY_CTL4_txulpsesc_1(r32, v)         _BFSET_(r32, 14, 14, v)
    #define   GET16DPHYTX_DPHY_CTL4_txulpsesc_1(r16)           _BFGET_(r16, 14, 14)
    #define   SET16DPHYTX_DPHY_CTL4_txulpsesc_1(r16, v)         _BFSET_(r16, 14, 14, v)

    #define   GET32DPHYTX_DPHY_CTL4_txulpsexit_1(r32)          _BFGET_(r32, 15, 15)
    #define   SET32DPHYTX_DPHY_CTL4_txulpsexit_1(r32, v)        _BFSET_(r32, 15, 15, v)
    #define   GET16DPHYTX_DPHY_CTL4_txulpsexit_1(r16)          _BFGET_(r16, 15, 15)
    #define   SET16DPHYTX_DPHY_CTL4_txulpsexit_1(r16, v)        _BFSET_(r16, 15, 15, v)

    #define   GET32DPHYTX_DPHY_CTL4_txvalidesc_1(r32)          _BFGET_(r32, 16, 16)
    #define   SET32DPHYTX_DPHY_CTL4_txvalidesc_1(r32, v)        _BFSET_(r32, 16, 16, v)
    #define   GET16DPHYTX_DPHY_CTL4_txvalidesc_1(r16)          _BFGET_(r16, 0, 0)
    #define   SET16DPHYTX_DPHY_CTL4_txvalidesc_1(r16, v)        _BFSET_(r16, 0, 0, v)

    #define     w32DPHYTX_DPHY_CTL4                            {\
	    UNSG32 uDPHY_CTL4_txdataesc_1                      :  8;\
	    UNSG32 uDPHY_CTL4_txtriggeresc_1                   :  4;\
	    UNSG32 uDPHY_CTL4_txrequestesc_1                   :  1;\
	    UNSG32 uDPHY_CTL4_txlpdtesc_1                      :  1;\
	    UNSG32 uDPHY_CTL4_txulpsesc_1                      :  1;\
	    UNSG32 uDPHY_CTL4_txulpsexit_1                     :  1;\
	    UNSG32 uDPHY_CTL4_txvalidesc_1                     :  1;\
	    UNSG32 RSVDx10_b17                                 : 15;\
	}
    union { UNSG32 u32DPHYTX_DPHY_CTL4;
	    struct w32DPHYTX_DPHY_CTL4;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32DPHYTX_DPHY_CTL5_txdataesc_2(r32)           _BFGET_(r32, 7, 0)
    #define   SET32DPHYTX_DPHY_CTL5_txdataesc_2(r32, v)         _BFSET_(r32, 7, 0, v)
    #define   GET16DPHYTX_DPHY_CTL5_txdataesc_2(r16)           _BFGET_(r16, 7, 0)
    #define   SET16DPHYTX_DPHY_CTL5_txdataesc_2(r16, v)         _BFSET_(r16, 7, 0, v)

    #define   GET32DPHYTX_DPHY_CTL5_txtriggeresc_2(r32)        _BFGET_(r32, 11, 8)
    #define   SET32DPHYTX_DPHY_CTL5_txtriggeresc_2(r32, v)      _BFSET_(r32, 11, 8, v)
    #define   GET16DPHYTX_DPHY_CTL5_txtriggeresc_2(r16)        _BFGET_(r16, 11, 8)
    #define   SET16DPHYTX_DPHY_CTL5_txtriggeresc_2(r16, v)      _BFSET_(r16, 11, 8, v)

    #define   GET32DPHYTX_DPHY_CTL5_txrequestesc_2(r32)        _BFGET_(r32, 12, 12)
    #define   SET32DPHYTX_DPHY_CTL5_txrequestesc_2(r32, v)      _BFSET_(r32, 12, 12, v)
    #define   GET16DPHYTX_DPHY_CTL5_txrequestesc_2(r16)        _BFGET_(r16, 12, 12)
    #define   SET16DPHYTX_DPHY_CTL5_txrequestesc_2(r16, v)      _BFSET_(r16, 12, 12, v)

    #define   GET32DPHYTX_DPHY_CTL5_txlpdtesc_2(r32)           _BFGET_(r32, 13, 13)
    #define   SET32DPHYTX_DPHY_CTL5_txlpdtesc_2(r32, v)         _BFSET_(r32, 13, 13, v)
    #define   GET16DPHYTX_DPHY_CTL5_txlpdtesc_2(r16)           _BFGET_(r16, 13, 13)
    #define   SET16DPHYTX_DPHY_CTL5_txlpdtesc_2(r16, v)         _BFSET_(r16, 13, 13, v)

    #define   GET32DPHYTX_DPHY_CTL5_txulpsesc_2(r32)           _BFGET_(r32, 14, 14)
    #define   SET32DPHYTX_DPHY_CTL5_txulpsesc_2(r32, v)         _BFSET_(r32, 14, 14, v)
    #define   GET16DPHYTX_DPHY_CTL5_txulpsesc_2(r16)           _BFGET_(r16, 14, 14)
    #define   SET16DPHYTX_DPHY_CTL5_txulpsesc_2(r16, v)         _BFSET_(r16, 14, 14, v)

    #define   GET32DPHYTX_DPHY_CTL5_txulpsexit_2(r32)          _BFGET_(r32, 15, 15)
    #define   SET32DPHYTX_DPHY_CTL5_txulpsexit_2(r32, v)        _BFSET_(r32, 15, 15, v)
    #define   GET16DPHYTX_DPHY_CTL5_txulpsexit_2(r16)          _BFGET_(r16, 15, 15)
    #define   SET16DPHYTX_DPHY_CTL5_txulpsexit_2(r16, v)        _BFSET_(r16, 15, 15, v)

    #define   GET32DPHYTX_DPHY_CTL5_txvalidesc_2(r32)          _BFGET_(r32, 16, 16)
    #define   SET32DPHYTX_DPHY_CTL5_txvalidesc_2(r32, v)        _BFSET_(r32, 16, 16, v)
    #define   GET16DPHYTX_DPHY_CTL5_txvalidesc_2(r16)          _BFGET_(r16, 0, 0)
    #define   SET16DPHYTX_DPHY_CTL5_txvalidesc_2(r16, v)        _BFSET_(r16, 0, 0, v)

    #define     w32DPHYTX_DPHY_CTL5                            {\
	    UNSG32 uDPHY_CTL5_txdataesc_2                      :  8;\
	    UNSG32 uDPHY_CTL5_txtriggeresc_2                   :  4;\
	    UNSG32 uDPHY_CTL5_txrequestesc_2                   :  1;\
	    UNSG32 uDPHY_CTL5_txlpdtesc_2                      :  1;\
	    UNSG32 uDPHY_CTL5_txulpsesc_2                      :  1;\
	    UNSG32 uDPHY_CTL5_txulpsexit_2                     :  1;\
	    UNSG32 uDPHY_CTL5_txvalidesc_2                     :  1;\
	    UNSG32 RSVDx14_b17                                 : 15;\
	}
    union { UNSG32 u32DPHYTX_DPHY_CTL5;
	    struct w32DPHYTX_DPHY_CTL5;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32DPHYTX_DPHY_CTL6_txdataesc_3(r32)           _BFGET_(r32, 7, 0)
    #define   SET32DPHYTX_DPHY_CTL6_txdataesc_3(r32, v)         _BFSET_(r32, 7, 0, v)
    #define   GET16DPHYTX_DPHY_CTL6_txdataesc_3(r16)           _BFGET_(r16, 7, 0)
    #define   SET16DPHYTX_DPHY_CTL6_txdataesc_3(r16, v)         _BFSET_(r16, 7, 0, v)

    #define   GET32DPHYTX_DPHY_CTL6_txtriggeresc_3(r32)        _BFGET_(r32, 11, 8)
    #define   SET32DPHYTX_DPHY_CTL6_txtriggeresc_3(r32, v)      _BFSET_(r32, 11, 8, v)
    #define   GET16DPHYTX_DPHY_CTL6_txtriggeresc_3(r16)        _BFGET_(r16, 11, 8)
    #define   SET16DPHYTX_DPHY_CTL6_txtriggeresc_3(r16, v)      _BFSET_(r16, 11, 8, v)

    #define   GET32DPHYTX_DPHY_CTL6_txrequestesc_3(r32)        _BFGET_(r32, 12, 12)
    #define   SET32DPHYTX_DPHY_CTL6_txrequestesc_3(r32, v)      _BFSET_(r32, 12, 12, v)
    #define   GET16DPHYTX_DPHY_CTL6_txrequestesc_3(r16)        _BFGET_(r16, 12, 12)
    #define   SET16DPHYTX_DPHY_CTL6_txrequestesc_3(r16, v)      _BFSET_(r16, 12, 12, v)

    #define   GET32DPHYTX_DPHY_CTL6_txlpdtesc_3(r32)           _BFGET_(r32, 13, 13)
    #define   SET32DPHYTX_DPHY_CTL6_txlpdtesc_3(r32, v)         _BFSET_(r32, 13, 13, v)
    #define   GET16DPHYTX_DPHY_CTL6_txlpdtesc_3(r16)           _BFGET_(r16, 13, 13)
    #define   SET16DPHYTX_DPHY_CTL6_txlpdtesc_3(r16, v)         _BFSET_(r16, 13, 13, v)

    #define   GET32DPHYTX_DPHY_CTL6_txulpsesc_3(r32)           _BFGET_(r32, 14, 14)
    #define   SET32DPHYTX_DPHY_CTL6_txulpsesc_3(r32, v)         _BFSET_(r32, 14, 14, v)
    #define   GET16DPHYTX_DPHY_CTL6_txulpsesc_3(r16)           _BFGET_(r16, 14, 14)
    #define   SET16DPHYTX_DPHY_CTL6_txulpsesc_3(r16, v)         _BFSET_(r16, 14, 14, v)

    #define   GET32DPHYTX_DPHY_CTL6_txulpsexit_3(r32)          _BFGET_(r32, 15, 15)
    #define   SET32DPHYTX_DPHY_CTL6_txulpsexit_3(r32, v)        _BFSET_(r32, 15, 15, v)
    #define   GET16DPHYTX_DPHY_CTL6_txulpsexit_3(r16)          _BFGET_(r16, 15, 15)
    #define   SET16DPHYTX_DPHY_CTL6_txulpsexit_3(r16, v)        _BFSET_(r16, 15, 15, v)

    #define   GET32DPHYTX_DPHY_CTL6_txvalidesc_3(r32)          _BFGET_(r32, 16, 16)
    #define   SET32DPHYTX_DPHY_CTL6_txvalidesc_3(r32, v)        _BFSET_(r32, 16, 16, v)
    #define   GET16DPHYTX_DPHY_CTL6_txvalidesc_3(r16)          _BFGET_(r16, 0, 0)
    #define   SET16DPHYTX_DPHY_CTL6_txvalidesc_3(r16, v)        _BFSET_(r16, 0, 0, v)

    #define     w32DPHYTX_DPHY_CTL6                            {\
	    UNSG32 uDPHY_CTL6_txdataesc_3                      :  8;\
	    UNSG32 uDPHY_CTL6_txtriggeresc_3                   :  4;\
	    UNSG32 uDPHY_CTL6_txrequestesc_3                   :  1;\
	    UNSG32 uDPHY_CTL6_txlpdtesc_3                      :  1;\
	    UNSG32 uDPHY_CTL6_txulpsesc_3                      :  1;\
	    UNSG32 uDPHY_CTL6_txulpsexit_3                     :  1;\
	    UNSG32 uDPHY_CTL6_txvalidesc_3                     :  1;\
	    UNSG32 RSVDx18_b17                                 : 15;\
	}
    union { UNSG32 u32DPHYTX_DPHY_CTL6;
	    struct w32DPHYTX_DPHY_CTL6;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32DPHYTX_DPHY_CTL7_txblaneclkSel(r32)         _BFGET_(r32, 0, 0)
    #define   SET32DPHYTX_DPHY_CTL7_txblaneclkSel(r32, v)       _BFSET_(r32, 0, 0, v)
    #define   GET16DPHYTX_DPHY_CTL7_txblaneclkSel(r16)         _BFGET_(r16, 0, 0)
    #define   SET16DPHYTX_DPHY_CTL7_txblaneclkSel(r16, v)       _BFSET_(r16, 0, 0, v)

    #define   GET32DPHYTX_DPHY_CTL7_txskewcalhsBIU(r32)        _BFGET_(r32, 1, 1)
    #define   SET32DPHYTX_DPHY_CTL7_txskewcalhsBIU(r32, v)      _BFSET_(r32, 1, 1, v)
    #define   GET16DPHYTX_DPHY_CTL7_txskewcalhsBIU(r16)        _BFGET_(r16, 1, 1)
    #define   SET16DPHYTX_DPHY_CTL7_txskewcalhsBIU(r16, v)      _BFSET_(r16, 1, 1, v)

    #define   GET32DPHYTX_DPHY_CTL7_txrequestdatahs_0(r32)     _BFGET_(r32, 2, 2)
    #define   SET32DPHYTX_DPHY_CTL7_txrequestdatahs_0(r32, v)   _BFSET_(r32, 2, 2, v)
    #define   GET16DPHYTX_DPHY_CTL7_txrequestdatahs_0(r16)     _BFGET_(r16, 2, 2)
    #define   SET16DPHYTX_DPHY_CTL7_txrequestdatahs_0(r16, v)   _BFSET_(r16, 2, 2, v)

    #define   GET32DPHYTX_DPHY_CTL7_txrequestdatahs_1(r32)     _BFGET_(r32, 3, 3)
    #define   SET32DPHYTX_DPHY_CTL7_txrequestdatahs_1(r32, v)   _BFSET_(r32, 3, 3, v)
    #define   GET16DPHYTX_DPHY_CTL7_txrequestdatahs_1(r16)     _BFGET_(r16, 3, 3)
    #define   SET16DPHYTX_DPHY_CTL7_txrequestdatahs_1(r16, v)   _BFSET_(r16, 3, 3, v)

    #define   GET32DPHYTX_DPHY_CTL7_txrequestdatahs_2(r32)     _BFGET_(r32, 4, 4)
    #define   SET32DPHYTX_DPHY_CTL7_txrequestdatahs_2(r32, v)   _BFSET_(r32, 4, 4, v)
    #define   GET16DPHYTX_DPHY_CTL7_txrequestdatahs_2(r16)     _BFGET_(r16, 4, 4)
    #define   SET16DPHYTX_DPHY_CTL7_txrequestdatahs_2(r16, v)   _BFSET_(r16, 4, 4, v)

    #define   GET32DPHYTX_DPHY_CTL7_txrequestdatahs_3(r32)     _BFGET_(r32, 5, 5)
    #define   SET32DPHYTX_DPHY_CTL7_txrequestdatahs_3(r32, v)   _BFSET_(r32, 5, 5, v)
    #define   GET16DPHYTX_DPHY_CTL7_txrequestdatahs_3(r16)     _BFGET_(r16, 5, 5)
    #define   SET16DPHYTX_DPHY_CTL7_txrequestdatahs_3(r16, v)   _BFSET_(r16, 5, 5, v)

    #define     w32DPHYTX_DPHY_CTL7                            {\
	    UNSG32 uDPHY_CTL7_txblaneclkSel                    :  1;\
	    UNSG32 uDPHY_CTL7_txskewcalhsBIU                   :  1;\
	    UNSG32 uDPHY_CTL7_txrequestdatahs_0                :  1;\
	    UNSG32 uDPHY_CTL7_txrequestdatahs_1                :  1;\
	    UNSG32 uDPHY_CTL7_txrequestdatahs_2                :  1;\
	    UNSG32 uDPHY_CTL7_txrequestdatahs_3                :  1;\
	    UNSG32 RSVDx1C_b6                                  : 26;\
	}
    union { UNSG32 u32DPHYTX_DPHY_CTL7;
	    struct w32DPHYTX_DPHY_CTL7;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32DPHYTX_DPHY_CTL8_txdatahs_0(r32)            _BFGET_(r32, 7, 0)
    #define   SET32DPHYTX_DPHY_CTL8_txdatahs_0(r32, v)          _BFSET_(r32, 7, 0, v)
    #define   GET16DPHYTX_DPHY_CTL8_txdatahs_0(r16)            _BFGET_(r16, 7, 0)
    #define   SET16DPHYTX_DPHY_CTL8_txdatahs_0(r16, v)          _BFSET_(r16, 7, 0, v)

    #define   GET32DPHYTX_DPHY_CTL8_txdatahs_1(r32)            _BFGET_(r32, 15, 8)
    #define   SET32DPHYTX_DPHY_CTL8_txdatahs_1(r32, v)          _BFSET_(r32, 15, 8, v)
    #define   GET16DPHYTX_DPHY_CTL8_txdatahs_1(r16)            _BFGET_(r16, 15, 8)
    #define   SET16DPHYTX_DPHY_CTL8_txdatahs_1(r16, v)          _BFSET_(r16, 15, 8, v)

    #define   GET32DPHYTX_DPHY_CTL8_txdatahs_2(r32)            _BFGET_(r32, 23, 16)
    #define   SET32DPHYTX_DPHY_CTL8_txdatahs_2(r32, v)          _BFSET_(r32, 23, 16, v)
    #define   GET16DPHYTX_DPHY_CTL8_txdatahs_2(r16)            _BFGET_(r16, 7, 0)
    #define   SET16DPHYTX_DPHY_CTL8_txdatahs_2(r16, v)          _BFSET_(r16, 7, 0, v)

    #define   GET32DPHYTX_DPHY_CTL8_txdatahs_3(r32)            _BFGET_(r32, 31, 24)
    #define   SET32DPHYTX_DPHY_CTL8_txdatahs_3(r32, v)          _BFSET_(r32, 31, 24, v)
    #define   GET16DPHYTX_DPHY_CTL8_txdatahs_3(r16)            _BFGET_(r16, 15, 8)
    #define   SET16DPHYTX_DPHY_CTL8_txdatahs_3(r16, v)          _BFSET_(r16, 15, 8, v)

    #define     w32DPHYTX_DPHY_CTL8                            {\
	    UNSG32 uDPHY_CTL8_txdatahs_0                       :  8;\
	    UNSG32 uDPHY_CTL8_txdatahs_1                       :  8;\
	    UNSG32 uDPHY_CTL8_txdatahs_2                       :  8;\
	    UNSG32 uDPHY_CTL8_txdatahs_3                       :  8;\
	}
    union { UNSG32 u32DPHYTX_DPHY_CTL8;
	    struct w32DPHYTX_DPHY_CTL8;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32DPHYTX_DPHY_RB0_cont_data(r32)              _BFGET_(r32, 10, 0)
    #define   SET32DPHYTX_DPHY_RB0_cont_data(r32, v)            _BFSET_(r32, 10, 0, v)
    #define   GET16DPHYTX_DPHY_RB0_cont_data(r16)              _BFGET_(r16, 10, 0)
    #define   SET16DPHYTX_DPHY_RB0_cont_data(r16, v)            _BFSET_(r16, 10, 0, v)

    #define   GET32DPHYTX_DPHY_RB0_lock(r32)                   _BFGET_(r32, 11, 11)
    #define   SET32DPHYTX_DPHY_RB0_lock(r32, v)                 _BFSET_(r32, 11, 11, v)
    #define   GET16DPHYTX_DPHY_RB0_lock(r16)                   _BFGET_(r16, 11, 11)
    #define   SET16DPHYTX_DPHY_RB0_lock(r16, v)                 _BFSET_(r16, 11, 11, v)

    #define   GET32DPHYTX_DPHY_RB0_stopstateclk(r32)           _BFGET_(r32, 12, 12)
    #define   SET32DPHYTX_DPHY_RB0_stopstateclk(r32, v)         _BFSET_(r32, 12, 12, v)
    #define   GET16DPHYTX_DPHY_RB0_stopstateclk(r16)           _BFGET_(r16, 12, 12)
    #define   SET16DPHYTX_DPHY_RB0_stopstateclk(r16, v)         _BFSET_(r16, 12, 12, v)

    #define   GET32DPHYTX_DPHY_RB0_ulpsactivenotclk(r32)       _BFGET_(r32, 13, 13)
    #define   SET32DPHYTX_DPHY_RB0_ulpsactivenotclk(r32, v)     _BFSET_(r32, 13, 13, v)
    #define   GET16DPHYTX_DPHY_RB0_ulpsactivenotclk(r16)       _BFGET_(r16, 13, 13)
    #define   SET16DPHYTX_DPHY_RB0_ulpsactivenotclk(r16, v)     _BFSET_(r16, 13, 13, v)

    #define   GET32DPHYTX_DPHY_RB0_stopstatedata_0(r32)        _BFGET_(r32, 14, 14)
    #define   SET32DPHYTX_DPHY_RB0_stopstatedata_0(r32, v)      _BFSET_(r32, 14, 14, v)
    #define   GET16DPHYTX_DPHY_RB0_stopstatedata_0(r16)        _BFGET_(r16, 14, 14)
    #define   SET16DPHYTX_DPHY_RB0_stopstatedata_0(r16, v)      _BFSET_(r16, 14, 14, v)

    #define   GET32DPHYTX_DPHY_RB0_stopstatedata_1(r32)        _BFGET_(r32, 15, 15)
    #define   SET32DPHYTX_DPHY_RB0_stopstatedata_1(r32, v)      _BFSET_(r32, 15, 15, v)
    #define   GET16DPHYTX_DPHY_RB0_stopstatedata_1(r16)        _BFGET_(r16, 15, 15)
    #define   SET16DPHYTX_DPHY_RB0_stopstatedata_1(r16, v)      _BFSET_(r16, 15, 15, v)

    #define   GET32DPHYTX_DPHY_RB0_stopstatedata_2(r32)        _BFGET_(r32, 16, 16)
    #define   SET32DPHYTX_DPHY_RB0_stopstatedata_2(r32, v)      _BFSET_(r32, 16, 16, v)
    #define   GET16DPHYTX_DPHY_RB0_stopstatedata_2(r16)        _BFGET_(r16, 0, 0)
    #define   SET16DPHYTX_DPHY_RB0_stopstatedata_2(r16, v)      _BFSET_(r16, 0, 0, v)

    #define   GET32DPHYTX_DPHY_RB0_stopstatedata_3(r32)        _BFGET_(r32, 17, 17)
    #define   SET32DPHYTX_DPHY_RB0_stopstatedata_3(r32, v)      _BFSET_(r32, 17, 17, v)
    #define   GET16DPHYTX_DPHY_RB0_stopstatedata_3(r16)        _BFGET_(r16, 1, 1)
    #define   SET16DPHYTX_DPHY_RB0_stopstatedata_3(r16, v)      _BFSET_(r16, 1, 1, v)

    #define   GET32DPHYTX_DPHY_RB0_ulpsactivenot_0(r32)        _BFGET_(r32, 18, 18)
    #define   SET32DPHYTX_DPHY_RB0_ulpsactivenot_0(r32, v)      _BFSET_(r32, 18, 18, v)
    #define   GET16DPHYTX_DPHY_RB0_ulpsactivenot_0(r16)        _BFGET_(r16, 2, 2)
    #define   SET16DPHYTX_DPHY_RB0_ulpsactivenot_0(r16, v)      _BFSET_(r16, 2, 2, v)

    #define   GET32DPHYTX_DPHY_RB0_ulpsactivenot_1(r32)        _BFGET_(r32, 19, 19)
    #define   SET32DPHYTX_DPHY_RB0_ulpsactivenot_1(r32, v)      _BFSET_(r32, 19, 19, v)
    #define   GET16DPHYTX_DPHY_RB0_ulpsactivenot_1(r16)        _BFGET_(r16, 3, 3)
    #define   SET16DPHYTX_DPHY_RB0_ulpsactivenot_1(r16, v)      _BFSET_(r16, 3, 3, v)

    #define   GET32DPHYTX_DPHY_RB0_ulpsactivenot_2(r32)        _BFGET_(r32, 20, 20)
    #define   SET32DPHYTX_DPHY_RB0_ulpsactivenot_2(r32, v)      _BFSET_(r32, 20, 20, v)
    #define   GET16DPHYTX_DPHY_RB0_ulpsactivenot_2(r16)        _BFGET_(r16, 4, 4)
    #define   SET16DPHYTX_DPHY_RB0_ulpsactivenot_2(r16, v)      _BFSET_(r16, 4, 4, v)

    #define   GET32DPHYTX_DPHY_RB0_ulpsactivenot_3(r32)        _BFGET_(r32, 21, 21)
    #define   SET32DPHYTX_DPHY_RB0_ulpsactivenot_3(r32, v)      _BFSET_(r32, 21, 21, v)
    #define   GET16DPHYTX_DPHY_RB0_ulpsactivenot_3(r16)        _BFGET_(r16, 5, 5)
    #define   SET16DPHYTX_DPHY_RB0_ulpsactivenot_3(r16, v)      _BFSET_(r16, 5, 5, v)

    #define     w32DPHYTX_DPHY_RB0                             {\
	    UNSG32 uDPHY_RB0_cont_data                         : 11;\
	    UNSG32 uDPHY_RB0_lock                              :  1;\
	    UNSG32 uDPHY_RB0_stopstateclk                      :  1;\
	    UNSG32 uDPHY_RB0_ulpsactivenotclk                  :  1;\
	    UNSG32 uDPHY_RB0_stopstatedata_0                   :  1;\
	    UNSG32 uDPHY_RB0_stopstatedata_1                   :  1;\
	    UNSG32 uDPHY_RB0_stopstatedata_2                   :  1;\
	    UNSG32 uDPHY_RB0_stopstatedata_3                   :  1;\
	    UNSG32 uDPHY_RB0_ulpsactivenot_0                   :  1;\
	    UNSG32 uDPHY_RB0_ulpsactivenot_1                   :  1;\
	    UNSG32 uDPHY_RB0_ulpsactivenot_2                   :  1;\
	    UNSG32 uDPHY_RB0_ulpsactivenot_3                   :  1;\
	    UNSG32 RSVDx24_b22                                 : 10;\
	}
    union { UNSG32 u32DPHYTX_DPHY_RB0;
	    struct w32DPHYTX_DPHY_RB0;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32DPHYTX_DPHY_RB1_txreadyhs_0(r32)            _BFGET_(r32, 0, 0)
    #define   SET32DPHYTX_DPHY_RB1_txreadyhs_0(r32, v)          _BFSET_(r32, 0, 0, v)
    #define   GET16DPHYTX_DPHY_RB1_txreadyhs_0(r16)            _BFGET_(r16, 0, 0)
    #define   SET16DPHYTX_DPHY_RB1_txreadyhs_0(r16, v)          _BFSET_(r16, 0, 0, v)

    #define   GET32DPHYTX_DPHY_RB1_txreadyhs_1(r32)            _BFGET_(r32, 1, 1)
    #define   SET32DPHYTX_DPHY_RB1_txreadyhs_1(r32, v)          _BFSET_(r32, 1, 1, v)
    #define   GET16DPHYTX_DPHY_RB1_txreadyhs_1(r16)            _BFGET_(r16, 1, 1)
    #define   SET16DPHYTX_DPHY_RB1_txreadyhs_1(r16, v)          _BFSET_(r16, 1, 1, v)

    #define   GET32DPHYTX_DPHY_RB1_txreadyhs_2(r32)            _BFGET_(r32, 2, 2)
    #define   SET32DPHYTX_DPHY_RB1_txreadyhs_2(r32, v)          _BFSET_(r32, 2, 2, v)
    #define   GET16DPHYTX_DPHY_RB1_txreadyhs_2(r16)            _BFGET_(r16, 2, 2)
    #define   SET16DPHYTX_DPHY_RB1_txreadyhs_2(r16, v)          _BFSET_(r16, 2, 2, v)

    #define   GET32DPHYTX_DPHY_RB1_txreadyhs_3(r32)            _BFGET_(r32, 3, 3)
    #define   SET32DPHYTX_DPHY_RB1_txreadyhs_3(r32, v)          _BFSET_(r32, 3, 3, v)
    #define   GET16DPHYTX_DPHY_RB1_txreadyhs_3(r16)            _BFGET_(r16, 3, 3)
    #define   SET16DPHYTX_DPHY_RB1_txreadyhs_3(r16, v)          _BFSET_(r16, 3, 3, v)

    #define     w32DPHYTX_DPHY_RB1                             {\
	    UNSG32 uDPHY_RB1_txreadyhs_0                       :  1;\
	    UNSG32 uDPHY_RB1_txreadyhs_1                       :  1;\
	    UNSG32 uDPHY_RB1_txreadyhs_2                       :  1;\
	    UNSG32 uDPHY_RB1_txreadyhs_3                       :  1;\
	    UNSG32 RSVDx28_b4                                  : 28;\
	}
    union { UNSG32 u32DPHYTX_DPHY_RB1;
	    struct w32DPHYTX_DPHY_RB1;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32DPHYTX_DPHY_RB2_txreadyesc_0(r32)           _BFGET_(r32, 0, 0)
    #define   SET32DPHYTX_DPHY_RB2_txreadyesc_0(r32, v)         _BFSET_(r32, 0, 0, v)
    #define   GET16DPHYTX_DPHY_RB2_txreadyesc_0(r16)           _BFGET_(r16, 0, 0)
    #define   SET16DPHYTX_DPHY_RB2_txreadyesc_0(r16, v)         _BFSET_(r16, 0, 0, v)

    #define   GET32DPHYTX_DPHY_RB2_txreadyesc_1(r32)           _BFGET_(r32, 1, 1)
    #define   SET32DPHYTX_DPHY_RB2_txreadyesc_1(r32, v)         _BFSET_(r32, 1, 1, v)
    #define   GET16DPHYTX_DPHY_RB2_txreadyesc_1(r16)           _BFGET_(r16, 1, 1)
    #define   SET16DPHYTX_DPHY_RB2_txreadyesc_1(r16, v)         _BFSET_(r16, 1, 1, v)

    #define   GET32DPHYTX_DPHY_RB2_txreadyesc_2(r32)           _BFGET_(r32, 2, 2)
    #define   SET32DPHYTX_DPHY_RB2_txreadyesc_2(r32, v)         _BFSET_(r32, 2, 2, v)
    #define   GET16DPHYTX_DPHY_RB2_txreadyesc_2(r16)           _BFGET_(r16, 2, 2)
    #define   SET16DPHYTX_DPHY_RB2_txreadyesc_2(r16, v)         _BFSET_(r16, 2, 2, v)

    #define   GET32DPHYTX_DPHY_RB2_txreadyesc_3(r32)           _BFGET_(r32, 3, 3)
    #define   SET32DPHYTX_DPHY_RB2_txreadyesc_3(r32, v)         _BFSET_(r32, 3, 3, v)
    #define   GET16DPHYTX_DPHY_RB2_txreadyesc_3(r16)           _BFGET_(r16, 3, 3)
    #define   SET16DPHYTX_DPHY_RB2_txreadyesc_3(r16, v)         _BFSET_(r16, 3, 3, v)

    #define   GET32DPHYTX_DPHY_RB2_errcontrol_0(r32)           _BFGET_(r32, 4, 4)
    #define   SET32DPHYTX_DPHY_RB2_errcontrol_0(r32, v)         _BFSET_(r32, 4, 4, v)
    #define   GET16DPHYTX_DPHY_RB2_errcontrol_0(r16)           _BFGET_(r16, 4, 4)
    #define   SET16DPHYTX_DPHY_RB2_errcontrol_0(r16, v)         _BFSET_(r16, 4, 4, v)

    #define   GET32DPHYTX_DPHY_RB2_errcontentionlp0_0(r32)     _BFGET_(r32, 5, 5)
    #define   SET32DPHYTX_DPHY_RB2_errcontentionlp0_0(r32, v)   _BFSET_(r32, 5, 5, v)
    #define   GET16DPHYTX_DPHY_RB2_errcontentionlp0_0(r16)     _BFGET_(r16, 5, 5)
    #define   SET16DPHYTX_DPHY_RB2_errcontentionlp0_0(r16, v)   _BFSET_(r16, 5, 5, v)

    #define   GET32DPHYTX_DPHY_RB2_errcontentionlp1_0(r32)     _BFGET_(r32, 6, 6)
    #define   SET32DPHYTX_DPHY_RB2_errcontentionlp1_0(r32, v)   _BFSET_(r32, 6, 6, v)
    #define   GET16DPHYTX_DPHY_RB2_errcontentionlp1_0(r16)     _BFGET_(r16, 6, 6)
    #define   SET16DPHYTX_DPHY_RB2_errcontentionlp1_0(r16, v)   _BFSET_(r16, 6, 6, v)

    #define     w32DPHYTX_DPHY_RB2                             {\
	    UNSG32 uDPHY_RB2_txreadyesc_0                      :  1;\
	    UNSG32 uDPHY_RB2_txreadyesc_1                      :  1;\
	    UNSG32 uDPHY_RB2_txreadyesc_2                      :  1;\
	    UNSG32 uDPHY_RB2_txreadyesc_3                      :  1;\
	    UNSG32 uDPHY_RB2_errcontrol_0                      :  1;\
	    UNSG32 uDPHY_RB2_errcontentionlp0_0                :  1;\
	    UNSG32 uDPHY_RB2_errcontentionlp1_0                :  1;\
	    UNSG32 RSVDx2C_b7                                  : 25;\
	}
    union { UNSG32 u32DPHYTX_DPHY_RB2;
	    struct w32DPHYTX_DPHY_RB2;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32DPHYTX_DPHY_RB3_rxdataesc_0(r32)            _BFGET_(r32, 7, 0)
    #define   SET32DPHYTX_DPHY_RB3_rxdataesc_0(r32, v)          _BFSET_(r32, 7, 0, v)
    #define   GET16DPHYTX_DPHY_RB3_rxdataesc_0(r16)            _BFGET_(r16, 7, 0)
    #define   SET16DPHYTX_DPHY_RB3_rxdataesc_0(r16, v)          _BFSET_(r16, 7, 0, v)

    #define   GET32DPHYTX_DPHY_RB3_rxtriggeresc_0(r32)         _BFGET_(r32, 11, 8)
    #define   SET32DPHYTX_DPHY_RB3_rxtriggeresc_0(r32, v)       _BFSET_(r32, 11, 8, v)
    #define   GET16DPHYTX_DPHY_RB3_rxtriggeresc_0(r16)         _BFGET_(r16, 11, 8)
    #define   SET16DPHYTX_DPHY_RB3_rxtriggeresc_0(r16, v)       _BFSET_(r16, 11, 8, v)

    #define   GET32DPHYTX_DPHY_RB3_rxlpdtesc_0(r32)            _BFGET_(r32, 12, 12)
    #define   SET32DPHYTX_DPHY_RB3_rxlpdtesc_0(r32, v)          _BFSET_(r32, 12, 12, v)
    #define   GET16DPHYTX_DPHY_RB3_rxlpdtesc_0(r16)            _BFGET_(r16, 12, 12)
    #define   SET16DPHYTX_DPHY_RB3_rxlpdtesc_0(r16, v)          _BFSET_(r16, 12, 12, v)

    #define   GET32DPHYTX_DPHY_RB3_rxulpsesc_0(r32)            _BFGET_(r32, 13, 13)
    #define   SET32DPHYTX_DPHY_RB3_rxulpsesc_0(r32, v)          _BFSET_(r32, 13, 13, v)
    #define   GET16DPHYTX_DPHY_RB3_rxulpsesc_0(r16)            _BFGET_(r16, 13, 13)
    #define   SET16DPHYTX_DPHY_RB3_rxulpsesc_0(r16, v)          _BFSET_(r16, 13, 13, v)

    #define   GET32DPHYTX_DPHY_RB3_rxvalidesc_0(r32)           _BFGET_(r32, 14, 14)
    #define   SET32DPHYTX_DPHY_RB3_rxvalidesc_0(r32, v)         _BFSET_(r32, 14, 14, v)
    #define   GET16DPHYTX_DPHY_RB3_rxvalidesc_0(r16)           _BFGET_(r16, 14, 14)
    #define   SET16DPHYTX_DPHY_RB3_rxvalidesc_0(r16, v)         _BFSET_(r16, 14, 14, v)

    #define   GET32DPHYTX_DPHY_RB3_direction_0(r32)            _BFGET_(r32, 15, 15)
    #define   SET32DPHYTX_DPHY_RB3_direction_0(r32, v)          _BFSET_(r32, 15, 15, v)
    #define   GET16DPHYTX_DPHY_RB3_direction_0(r16)            _BFGET_(r16, 15, 15)
    #define   SET16DPHYTX_DPHY_RB3_direction_0(r16, v)          _BFSET_(r16, 15, 15, v)

    #define   GET32DPHYTX_DPHY_RB3_erresc_0(r32)               _BFGET_(r32, 16, 16)
    #define   SET32DPHYTX_DPHY_RB3_erresc_0(r32, v)             _BFSET_(r32, 16, 16, v)
    #define   GET16DPHYTX_DPHY_RB3_erresc_0(r16)               _BFGET_(r16, 0, 0)
    #define   SET16DPHYTX_DPHY_RB3_erresc_0(r16, v)             _BFSET_(r16, 0, 0, v)

    #define   GET32DPHYTX_DPHY_RB3_errsyncesc_0(r32)           _BFGET_(r32, 17, 17)
    #define   SET32DPHYTX_DPHY_RB3_errsyncesc_0(r32, v)         _BFSET_(r32, 17, 17, v)
    #define   GET16DPHYTX_DPHY_RB3_errsyncesc_0(r16)           _BFGET_(r16, 1, 1)
    #define   SET16DPHYTX_DPHY_RB3_errsyncesc_0(r16, v)         _BFSET_(r16, 1, 1, v)

    #define     w32DPHYTX_DPHY_RB3                             {\
	    UNSG32 uDPHY_RB3_rxdataesc_0                       :  8;\
	    UNSG32 uDPHY_RB3_rxtriggeresc_0                    :  4;\
	    UNSG32 uDPHY_RB3_rxlpdtesc_0                       :  1;\
	    UNSG32 uDPHY_RB3_rxulpsesc_0                       :  1;\
	    UNSG32 uDPHY_RB3_rxvalidesc_0                      :  1;\
	    UNSG32 uDPHY_RB3_direction_0                       :  1;\
	    UNSG32 uDPHY_RB3_erresc_0                          :  1;\
	    UNSG32 uDPHY_RB3_errsyncesc_0                      :  1;\
	    UNSG32 RSVDx30_b18                                 : 14;\
	}
    union { UNSG32 u32DPHYTX_DPHY_RB3;
	    struct w32DPHYTX_DPHY_RB3;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32DPHYTX_DPHY_PLL0_updatepll(r32)             _BFGET_(r32, 0, 0)
    #define   SET32DPHYTX_DPHY_PLL0_updatepll(r32, v)           _BFSET_(r32, 0, 0, v)
    #define   GET16DPHYTX_DPHY_PLL0_updatepll(r16)             _BFGET_(r16, 0, 0)
    #define   SET16DPHYTX_DPHY_PLL0_updatepll(r16, v)           _BFSET_(r16, 0, 0, v)

    #define     w32DPHYTX_DPHY_PLL0                            {\
	    UNSG32 uDPHY_PLL0_updatepll                        :  1;\
	    UNSG32 RSVDx34_b1                                  : 31;\
	}
    union { UNSG32 u32DPHYTX_DPHY_PLL0;
	    struct w32DPHYTX_DPHY_PLL0;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32DPHYTX_DPHY_PLL1_n(r32)                     _BFGET_(r32, 3, 0)
    #define   SET32DPHYTX_DPHY_PLL1_n(r32, v)                   _BFSET_(r32, 3, 0, v)
    #define   GET16DPHYTX_DPHY_PLL1_n(r16)                     _BFGET_(r16, 3, 0)
    #define   SET16DPHYTX_DPHY_PLL1_n(r16, v)                   _BFSET_(r16, 3, 0, v)

    #define   GET32DPHYTX_DPHY_PLL1_m(r32)                     _BFGET_(r32, 13, 4)
    #define   SET32DPHYTX_DPHY_PLL1_m(r32, v)                   _BFSET_(r32, 13, 4, v)
    #define   GET16DPHYTX_DPHY_PLL1_m(r16)                     _BFGET_(r16, 13, 4)
    #define   SET16DPHYTX_DPHY_PLL1_m(r16, v)                   _BFSET_(r16, 13, 4, v)

    #define   GET32DPHYTX_DPHY_PLL1_vco_cntrl(r32)             _BFGET_(r32, 19, 14)
    #define   SET32DPHYTX_DPHY_PLL1_vco_cntrl(r32, v)           _BFSET_(r32, 19, 14, v)

    #define   GET32DPHYTX_DPHY_PLL1_prop_cntrl(r32)            _BFGET_(r32, 25, 20)
    #define   SET32DPHYTX_DPHY_PLL1_prop_cntrl(r32, v)          _BFSET_(r32, 25, 20, v)
    #define   GET16DPHYTX_DPHY_PLL1_prop_cntrl(r16)            _BFGET_(r16, 9, 4)
    #define   SET16DPHYTX_DPHY_PLL1_prop_cntrl(r16, v)          _BFSET_(r16, 9, 4, v)

    #define   GET32DPHYTX_DPHY_PLL1_int_cntrl(r32)             _BFGET_(r32, 31, 26)
    #define   SET32DPHYTX_DPHY_PLL1_int_cntrl(r32, v)           _BFSET_(r32, 31, 26, v)
    #define   GET16DPHYTX_DPHY_PLL1_int_cntrl(r16)             _BFGET_(r16, 15, 10)
    #define   SET16DPHYTX_DPHY_PLL1_int_cntrl(r16, v)           _BFSET_(r16, 15, 10, v)

    #define     w32DPHYTX_DPHY_PLL1                            {\
	    UNSG32 uDPHY_PLL1_n                                :  4;\
	    UNSG32 uDPHY_PLL1_m                                : 10;\
	    UNSG32 uDPHY_PLL1_vco_cntrl                        :  6;\
	    UNSG32 uDPHY_PLL1_prop_cntrl                       :  6;\
	    UNSG32 uDPHY_PLL1_int_cntrl                        :  6;\
	}
    union { UNSG32 u32DPHYTX_DPHY_PLL1;
	    struct w32DPHYTX_DPHY_PLL1;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32DPHYTX_DPHY_PLL2_gmp_cntrl(r32)             _BFGET_(r32, 1, 0)
    #define   SET32DPHYTX_DPHY_PLL2_gmp_cntrl(r32, v)           _BFSET_(r32, 1, 0, v)
    #define   GET16DPHYTX_DPHY_PLL2_gmp_cntrl(r16)             _BFGET_(r16, 1, 0)
    #define   SET16DPHYTX_DPHY_PLL2_gmp_cntrl(r16, v)           _BFSET_(r16, 1, 0, v)

    #define   GET32DPHYTX_DPHY_PLL2_cpbias_cntrl(r32)          _BFGET_(r32, 8, 2)
    #define   SET32DPHYTX_DPHY_PLL2_cpbias_cntrl(r32, v)        _BFSET_(r32, 8, 2, v)
    #define   GET16DPHYTX_DPHY_PLL2_cpbias_cntrl(r16)          _BFGET_(r16, 8, 2)
    #define   SET16DPHYTX_DPHY_PLL2_cpbias_cntrl(r16, v)        _BFSET_(r16, 8, 2, v)

    #define   GET32DPHYTX_DPHY_PLL2_clksel(r32)                _BFGET_(r32, 10, 9)
    #define   SET32DPHYTX_DPHY_PLL2_clksel(r32, v)              _BFSET_(r32, 10, 9, v)
    #define   GET16DPHYTX_DPHY_PLL2_clksel(r16)                _BFGET_(r16, 10, 9)
    #define   SET16DPHYTX_DPHY_PLL2_clksel(r16, v)              _BFSET_(r16, 10, 9, v)

    #define   GET32DPHYTX_DPHY_PLL2_force_lock(r32)            _BFGET_(r32, 11, 11)
    #define   SET32DPHYTX_DPHY_PLL2_force_lock(r32, v)          _BFSET_(r32, 11, 11, v)
    #define   GET16DPHYTX_DPHY_PLL2_force_lock(r16)            _BFGET_(r16, 11, 11)
    #define   SET16DPHYTX_DPHY_PLL2_force_lock(r16, v)          _BFSET_(r16, 11, 11, v)

    #define   GET32DPHYTX_DPHY_PLL2_pll_shadow_control(r32)    _BFGET_(r32, 12, 12)
    #define   SET32DPHYTX_DPHY_PLL2_pll_shadow_control(r32, v)  _BFSET_(r32, 12, 12, v)
    #define   GET16DPHYTX_DPHY_PLL2_pll_shadow_control(r16)    _BFGET_(r16, 12, 12)
    #define   SET16DPHYTX_DPHY_PLL2_pll_shadow_control(r16, v)  _BFSET_(r16, 12, 12, v)

    #define   GET32DPHYTX_DPHY_PLL2_shadow_clear(r32)          _BFGET_(r32, 13, 13)
    #define   SET32DPHYTX_DPHY_PLL2_shadow_clear(r32, v)        _BFSET_(r32, 13, 13, v)
    #define   GET16DPHYTX_DPHY_PLL2_shadow_clear(r16)          _BFGET_(r16, 13, 13)
    #define   SET16DPHYTX_DPHY_PLL2_shadow_clear(r16, v)        _BFSET_(r16, 13, 13, v)

    #define   GET32DPHYTX_DPHY_PLL2_gp_clk_en(r32)             _BFGET_(r32, 14, 14)
    #define   SET32DPHYTX_DPHY_PLL2_gp_clk_en(r32, v)           _BFSET_(r32, 14, 14, v)
    #define   GET16DPHYTX_DPHY_PLL2_gp_clk_en(r16)             _BFGET_(r16, 14, 14)
    #define   SET16DPHYTX_DPHY_PLL2_gp_clk_en(r16, v)           _BFSET_(r16, 14, 14, v)

    #define     w32DPHYTX_DPHY_PLL2                            {\
	    UNSG32 uDPHY_PLL2_gmp_cntrl                        :  2;\
	    UNSG32 uDPHY_PLL2_cpbias_cntrl                     :  7;\
	    UNSG32 uDPHY_PLL2_clksel                           :  2;\
	    UNSG32 uDPHY_PLL2_force_lock                       :  1;\
	    UNSG32 uDPHY_PLL2_pll_shadow_control               :  1;\
	    UNSG32 uDPHY_PLL2_shadow_clear                     :  1;\
	    UNSG32 uDPHY_PLL2_gp_clk_en                        :  1;\
	    UNSG32 RSVDx3C_b15                                 : 17;\
	}
    union { UNSG32 u32DPHYTX_DPHY_PLL2;
	    struct w32DPHYTX_DPHY_PLL2;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32DPHYTX_DPHY_PLLRB0_n_obs(r32)               _BFGET_(r32, 3, 0)
    #define   SET32DPHYTX_DPHY_PLLRB0_n_obs(r32, v)             _BFSET_(r32, 3, 0, v)
    #define   GET16DPHYTX_DPHY_PLLRB0_n_obs(r16)               _BFGET_(r16, 3, 0)
    #define   SET16DPHYTX_DPHY_PLLRB0_n_obs(r16, v)             _BFSET_(r16, 3, 0, v)

    #define   GET32DPHYTX_DPHY_PLLRB0_m_obs(r32)               _BFGET_(r32, 13, 4)
    #define   SET32DPHYTX_DPHY_PLLRB0_m_obs(r32, v)             _BFSET_(r32, 13, 4, v)
    #define   GET16DPHYTX_DPHY_PLLRB0_m_obs(r16)               _BFGET_(r16, 13, 4)
    #define   SET16DPHYTX_DPHY_PLLRB0_m_obs(r16, v)             _BFSET_(r16, 13, 4, v)

    #define   GET32DPHYTX_DPHY_PLLRB0_vco_cntrl_obs(r32)       _BFGET_(r32, 19, 14)
    #define   SET32DPHYTX_DPHY_PLLRB0_vco_cntrl_obs(r32, v)     _BFSET_(r32, 19, 14, v)

    #define   GET32DPHYTX_DPHY_PLLRB0_prop_cntrl_obs(r32)      _BFGET_(r32, 25, 20)
    #define   SET32DPHYTX_DPHY_PLLRB0_prop_cntrl_obs(r32, v)    _BFSET_(r32, 25, 20, v)
    #define   GET16DPHYTX_DPHY_PLLRB0_prop_cntrl_obs(r16)      _BFGET_(r16, 9, 4)
    #define   SET16DPHYTX_DPHY_PLLRB0_prop_cntrl_obs(r16, v)    _BFSET_(r16, 9, 4, v)

    #define   GET32DPHYTX_DPHY_PLLRB0_int_cntrl_obs(r32)       _BFGET_(r32, 31, 26)
    #define   SET32DPHYTX_DPHY_PLLRB0_int_cntrl_obs(r32, v)     _BFSET_(r32, 31, 26, v)
    #define   GET16DPHYTX_DPHY_PLLRB0_int_cntrl_obs(r16)       _BFGET_(r16, 15, 10)
    #define   SET16DPHYTX_DPHY_PLLRB0_int_cntrl_obs(r16, v)     _BFSET_(r16, 15, 10, v)

    #define     w32DPHYTX_DPHY_PLLRB0                          {\
	    UNSG32 uDPHY_PLLRB0_n_obs                          :  4;\
	    UNSG32 uDPHY_PLLRB0_m_obs                          : 10;\
	    UNSG32 uDPHY_PLLRB0_vco_cntrl_obs                  :  6;\
	    UNSG32 uDPHY_PLLRB0_prop_cntrl_obs                 :  6;\
	    UNSG32 uDPHY_PLLRB0_int_cntrl_obs                  :  6;\
	}
    union { UNSG32 u32DPHYTX_DPHY_PLLRB0;
	    struct w32DPHYTX_DPHY_PLLRB0;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32DPHYTX_DPHY_PLLRB1_gmp_cntrl_obs(r32)       _BFGET_(r32, 1, 0)
    #define   SET32DPHYTX_DPHY_PLLRB1_gmp_cntrl_obs(r32, v)     _BFSET_(r32, 1, 0, v)
    #define   GET16DPHYTX_DPHY_PLLRB1_gmp_cntrl_obs(r16)       _BFGET_(r16, 1, 0)
    #define   SET16DPHYTX_DPHY_PLLRB1_gmp_cntrl_obs(r16, v)     _BFSET_(r16, 1, 0, v)

    #define   GET32DPHYTX_DPHY_PLLRB1_cpbias_cntrl_obs(r32)    _BFGET_(r32, 8, 2)
    #define   SET32DPHYTX_DPHY_PLLRB1_cpbias_cntrl_obs(r32, v)  _BFSET_(r32, 8, 2, v)
    #define   GET16DPHYTX_DPHY_PLLRB1_cpbias_cntrl_obs(r16)    _BFGET_(r16, 8, 2)
    #define   SET16DPHYTX_DPHY_PLLRB1_cpbias_cntrl_obs(r16, v)  _BFSET_(r16, 8, 2, v)

    #define   GET32DPHYTX_DPHY_PLLRB1_pll_shadow_control_obs(r32) _BFGET_(r32, 9, 9)
    #define   SET32DPHYTX_DPHY_PLLRB1_pll_shadow_control_obs(r32, v) _BFSET_(r32, 9, 9, v)
    #define   GET16DPHYTX_DPHY_PLLRB1_pll_shadow_control_obs(r16) _BFGET_(r16, 9, 9)
    #define   SET16DPHYTX_DPHY_PLLRB1_pll_shadow_control_obs(r16, v) _BFSET_(r16, 9, 9, v)

    #define   GET32DPHYTX_DPHY_PLLRB1_lock_pll(r32)            _BFGET_(r32, 10, 10)
    #define   SET32DPHYTX_DPHY_PLLRB1_lock_pll(r32, v)          _BFSET_(r32, 10, 10, v)
    #define   GET16DPHYTX_DPHY_PLLRB1_lock_pll(r16)            _BFGET_(r16, 10, 10)
    #define   SET16DPHYTX_DPHY_PLLRB1_lock_pll(r16, v)          _BFSET_(r16, 10, 10, v)

    #define     w32DPHYTX_DPHY_PLLRB1                          {\
	    UNSG32 uDPHY_PLLRB1_gmp_cntrl_obs                  :  2;\
	    UNSG32 uDPHY_PLLRB1_cpbias_cntrl_obs               :  7;\
	    UNSG32 uDPHY_PLLRB1_pll_shadow_control_obs         :  1;\
	    UNSG32 uDPHY_PLLRB1_lock_pll                       :  1;\
	    UNSG32 RSVDx44_b11                                 : 21;\
	}
    union { UNSG32 u32DPHYTX_DPHY_PLLRB1;
	    struct w32DPHYTX_DPHY_PLLRB1;
	  };
    ///////////////////////////////////////////////////////////
    } SIE_DPHYTX;

    typedef union  T32DPHYTX_DPHY_CTL0 {
		UNSG32 u32;
	    struct w32DPHYTX_DPHY_CTL0;
		 } T32DPHYTX_DPHY_CTL0;
    typedef union  T32DPHYTX_DPHY_CTL1 {
		UNSG32 u32;
	    struct w32DPHYTX_DPHY_CTL1;
		 } T32DPHYTX_DPHY_CTL1;
    typedef union  T32DPHYTX_DPHY_CTL2 {
		UNSG32 u32;
	    struct w32DPHYTX_DPHY_CTL2;
		 } T32DPHYTX_DPHY_CTL2;
    typedef union  T32DPHYTX_DPHY_CTL3 {
		UNSG32 u32;
	    struct w32DPHYTX_DPHY_CTL3;
		 } T32DPHYTX_DPHY_CTL3;
    typedef union  T32DPHYTX_DPHY_CTL4 {
		UNSG32 u32;
	    struct w32DPHYTX_DPHY_CTL4;
		 } T32DPHYTX_DPHY_CTL4;
    typedef union  T32DPHYTX_DPHY_CTL5 {
		UNSG32 u32;
	    struct w32DPHYTX_DPHY_CTL5;
		 } T32DPHYTX_DPHY_CTL5;
    typedef union  T32DPHYTX_DPHY_CTL6 {
		UNSG32 u32;
	    struct w32DPHYTX_DPHY_CTL6;
		 } T32DPHYTX_DPHY_CTL6;
    typedef union  T32DPHYTX_DPHY_CTL7 {
		UNSG32 u32;
	    struct w32DPHYTX_DPHY_CTL7;
		 } T32DPHYTX_DPHY_CTL7;
    typedef union  T32DPHYTX_DPHY_CTL8 {
		UNSG32 u32;
	    struct w32DPHYTX_DPHY_CTL8;
		 } T32DPHYTX_DPHY_CTL8;
    typedef union  T32DPHYTX_DPHY_RB0 {
		UNSG32 u32;
	    struct w32DPHYTX_DPHY_RB0;
		 } T32DPHYTX_DPHY_RB0;
    typedef union  T32DPHYTX_DPHY_RB1 {
		UNSG32 u32;
	    struct w32DPHYTX_DPHY_RB1;
		 } T32DPHYTX_DPHY_RB1;
    typedef union  T32DPHYTX_DPHY_RB2 {
		UNSG32 u32;
	    struct w32DPHYTX_DPHY_RB2;
		 } T32DPHYTX_DPHY_RB2;
    typedef union  T32DPHYTX_DPHY_RB3 {
		UNSG32 u32;
	    struct w32DPHYTX_DPHY_RB3;
		 } T32DPHYTX_DPHY_RB3;
    typedef union  T32DPHYTX_DPHY_PLL0 {
		UNSG32 u32;
	    struct w32DPHYTX_DPHY_PLL0;
		 } T32DPHYTX_DPHY_PLL0;
    typedef union  T32DPHYTX_DPHY_PLL1 {
		UNSG32 u32;
	    struct w32DPHYTX_DPHY_PLL1;
		 } T32DPHYTX_DPHY_PLL1;
    typedef union  T32DPHYTX_DPHY_PLL2 {
		UNSG32 u32;
	    struct w32DPHYTX_DPHY_PLL2;
		 } T32DPHYTX_DPHY_PLL2;
    typedef union  T32DPHYTX_DPHY_PLLRB0 {
		UNSG32 u32;
	    struct w32DPHYTX_DPHY_PLLRB0;
		 } T32DPHYTX_DPHY_PLLRB0;
    typedef union  T32DPHYTX_DPHY_PLLRB1 {
		UNSG32 u32;
	    struct w32DPHYTX_DPHY_PLLRB1;
		 } T32DPHYTX_DPHY_PLLRB1;
    ///////////////////////////////////////////////////////////

    typedef union  TDPHYTX_DPHY_CTL0 {
		UNSG32 u32[1];
	    struct {
	    struct w32DPHYTX_DPHY_CTL0;
		   };
		 } TDPHYTX_DPHY_CTL0;
    typedef union  TDPHYTX_DPHY_CTL1 {
		UNSG32 u32[1];
	    struct {
	    struct w32DPHYTX_DPHY_CTL1;
		   };
		 } TDPHYTX_DPHY_CTL1;
    typedef union  TDPHYTX_DPHY_CTL2 {
		UNSG32 u32[1];
	    struct {
	    struct w32DPHYTX_DPHY_CTL2;
		   };
		 } TDPHYTX_DPHY_CTL2;
    typedef union  TDPHYTX_DPHY_CTL3 {
		UNSG32 u32[1];
	    struct {
	    struct w32DPHYTX_DPHY_CTL3;
		   };
		 } TDPHYTX_DPHY_CTL3;
    typedef union  TDPHYTX_DPHY_CTL4 {
		UNSG32 u32[1];
	    struct {
	    struct w32DPHYTX_DPHY_CTL4;
		   };
		 } TDPHYTX_DPHY_CTL4;
    typedef union  TDPHYTX_DPHY_CTL5 {
		UNSG32 u32[1];
	    struct {
	    struct w32DPHYTX_DPHY_CTL5;
		   };
		 } TDPHYTX_DPHY_CTL5;
    typedef union  TDPHYTX_DPHY_CTL6 {
		UNSG32 u32[1];
	    struct {
	    struct w32DPHYTX_DPHY_CTL6;
		   };
		 } TDPHYTX_DPHY_CTL6;
    typedef union  TDPHYTX_DPHY_CTL7 {
		UNSG32 u32[1];
	    struct {
	    struct w32DPHYTX_DPHY_CTL7;
		   };
		 } TDPHYTX_DPHY_CTL7;
    typedef union  TDPHYTX_DPHY_CTL8 {
		UNSG32 u32[1];
	    struct {
	    struct w32DPHYTX_DPHY_CTL8;
		   };
		 } TDPHYTX_DPHY_CTL8;
    typedef union  TDPHYTX_DPHY_RB0 {
		UNSG32 u32[1];
	    struct {
	    struct w32DPHYTX_DPHY_RB0;
		   };
		 } TDPHYTX_DPHY_RB0;
    typedef union  TDPHYTX_DPHY_RB1 {
		UNSG32 u32[1];
	    struct {
	    struct w32DPHYTX_DPHY_RB1;
		   };
		 } TDPHYTX_DPHY_RB1;
    typedef union  TDPHYTX_DPHY_RB2 {
		UNSG32 u32[1];
	    struct {
	    struct w32DPHYTX_DPHY_RB2;
		   };
		 } TDPHYTX_DPHY_RB2;
    typedef union  TDPHYTX_DPHY_RB3 {
		UNSG32 u32[1];
	    struct {
	    struct w32DPHYTX_DPHY_RB3;
		   };
		 } TDPHYTX_DPHY_RB3;
    typedef union  TDPHYTX_DPHY_PLL0 {
		UNSG32 u32[1];
	    struct {
	    struct w32DPHYTX_DPHY_PLL0;
		   };
		 } TDPHYTX_DPHY_PLL0;
    typedef union  TDPHYTX_DPHY_PLL1 {
		UNSG32 u32[1];
	    struct {
	    struct w32DPHYTX_DPHY_PLL1;
		   };
		 } TDPHYTX_DPHY_PLL1;
    typedef union  TDPHYTX_DPHY_PLL2 {
		UNSG32 u32[1];
	    struct {
	    struct w32DPHYTX_DPHY_PLL2;
		   };
		 } TDPHYTX_DPHY_PLL2;
    typedef union  TDPHYTX_DPHY_PLLRB0 {
		UNSG32 u32[1];
	    struct {
	    struct w32DPHYTX_DPHY_PLLRB0;
		   };
		 } TDPHYTX_DPHY_PLLRB0;
    typedef union  TDPHYTX_DPHY_PLLRB1 {
		UNSG32 u32[1];
	    struct {
	    struct w32DPHYTX_DPHY_PLLRB1;
		   };
		 } TDPHYTX_DPHY_PLLRB1;

    ///////////////////////////////////////////////////////////
     SIGN32 DPHYTX_drvrd(SIE_DPHYTX *p, UNSG32 base, SIGN32 mem, SIGN32 tst);
     SIGN32 DPHYTX_drvwr(SIE_DPHYTX *p, UNSG32 base, SIGN32 mem, SIGN32 tst, UNSG32 *pcmd);
       void DPHYTX_reset(SIE_DPHYTX *p);
     SIGN32 DPHYTX_cmp(SIE_DPHYTX *p, SIE_DPHYTX *pie, char *pfx, void *hLOG, SIGN32 mem, SIGN32 tst);
    #define DPHYTX_check(p, pie, pfx, hLOG) DPHYTX_cmp(p, pie, pfx, (void *)(hLOG), 0, 0)
    #define DPHYTX_print(p,    pfx, hLOG) DPHYTX_cmp(p, 0,  pfx, (void *)(hLOG), 0, 0)

#endif
//////
/// ENDOFINTERFACE: DPHYTX
////////////////////////////////////////////////////////////

//////
///
/// $INTERFACE SRAMPWR                                  (4,4)
///     # # ----------------------------------------------------------
///     @ 0x00000 ctrl                 (P-)
///               ###
///               * Control register
///               ###
///               %unsigned 1  SD                        0x0
///                                    : ON                        0x0
///                                    : SHUTDWN                   0x1
///                                                 ###
///                                                 * Shut down mode achieves highest leakage reduction without data retention
///                                                 ###
///               %unsigned 1  DSLP                      0x0
///                                    : ON                        0x0
///                                    : DEEPSLP                   0x1
///                                                 ###
///                                                 * Deep sleep mode powers down the most of peripheral circuit for leakage reduction and retains memory
///                                                 * array content with lower voltage
///                                                 ###
///               %unsigned 1  SLP                       0x0
///                                    : ON                        0x0
///                                    : SLEEP                     0x1
///                                                 ###
///                                                 * Sleep mode powers down most peripheral circuit for leakage reduction with data retention
///                                                 ###
///               %%        29         # Stuffing bits...
///     # # ----------------------------------------------------------
/// $ENDOFINTERFACE  # size:       4B, bits:       3b, padding:     0B
////////////////////////////////////////////////////////////
#ifndef h_SRAMPWR
#define h_SRAMPWR () {}

    #define     RA_SRAMPWR_ctrl                                0x0000

    #define     BA_SRAMPWR_ctrl_SD                             0x0000
    #define     B16SRAMPWR_ctrl_SD                             0x0000
    #define   LSb32SRAMPWR_ctrl_SD                                0
    #define   LSb16SRAMPWR_ctrl_SD                                0
    #define       bSRAMPWR_ctrl_SD                             1
    #define   MSK32SRAMPWR_ctrl_SD                                0x00000001
    #define        SRAMPWR_ctrl_SD_ON                                       0x0
    #define        SRAMPWR_ctrl_SD_SHUTDWN                                  0x1

    #define     BA_SRAMPWR_ctrl_DSLP                           0x0000
    #define     B16SRAMPWR_ctrl_DSLP                           0x0000
    #define   LSb32SRAMPWR_ctrl_DSLP                              1
    #define   LSb16SRAMPWR_ctrl_DSLP                              1
    #define       bSRAMPWR_ctrl_DSLP                           1
    #define   MSK32SRAMPWR_ctrl_DSLP                              0x00000002
    #define        SRAMPWR_ctrl_DSLP_ON                                     0x0
    #define        SRAMPWR_ctrl_DSLP_DEEPSLP                                0x1

    #define     BA_SRAMPWR_ctrl_SLP                            0x0000
    #define     B16SRAMPWR_ctrl_SLP                            0x0000
    #define   LSb32SRAMPWR_ctrl_SLP                               2
    #define   LSb16SRAMPWR_ctrl_SLP                               2
    #define       bSRAMPWR_ctrl_SLP                            1
    #define   MSK32SRAMPWR_ctrl_SLP                               0x00000004
    #define        SRAMPWR_ctrl_SLP_ON                                      0x0
    #define        SRAMPWR_ctrl_SLP_SLEEP                                   0x1
    ///////////////////////////////////////////////////////////

    typedef struct SIE_SRAMPWR {
    ///////////////////////////////////////////////////////////
    #define   GET32SRAMPWR_ctrl_SD(r32)                        _BFGET_(r32, 0, 0)
    #define   SET32SRAMPWR_ctrl_SD(r32, v)                      _BFSET_(r32, 0, 0, v)
    #define   GET16SRAMPWR_ctrl_SD(r16)                        _BFGET_(r16, 0, 0)
    #define   SET16SRAMPWR_ctrl_SD(r16, v)                      _BFSET_(r16, 0, 0, v)

    #define   GET32SRAMPWR_ctrl_DSLP(r32)                      _BFGET_(r32, 1, 1)
    #define   SET32SRAMPWR_ctrl_DSLP(r32, v)                    _BFSET_(r32, 1, 1, v)
    #define   GET16SRAMPWR_ctrl_DSLP(r16)                      _BFGET_(r16, 1, 1)
    #define   SET16SRAMPWR_ctrl_DSLP(r16, v)                    _BFSET_(r16, 1, 1, v)

    #define   GET32SRAMPWR_ctrl_SLP(r32)                       _BFGET_(r32, 2, 2)
    #define   SET32SRAMPWR_ctrl_SLP(r32, v)                     _BFSET_(r32, 2, 2, v)
    #define   GET16SRAMPWR_ctrl_SLP(r16)                       _BFGET_(r16, 2, 2)
    #define   SET16SRAMPWR_ctrl_SLP(r16, v)                     _BFSET_(r16, 2, 2, v)

    #define     w32SRAMPWR_ctrl                                {\
	    UNSG32 uctrl_SD                                    :  1;\
	    UNSG32 uctrl_DSLP                                  :  1;\
	    UNSG32 uctrl_SLP                                   :  1;\
	    UNSG32 RSVDx0_b3                                   : 29;\
	}
    union { UNSG32 u32SRAMPWR_ctrl;
	    struct w32SRAMPWR_ctrl;
	  };
    ///////////////////////////////////////////////////////////
    } SIE_SRAMPWR;

    typedef union  T32SRAMPWR_ctrl {
		UNSG32 u32;
	    struct w32SRAMPWR_ctrl;
		 } T32SRAMPWR_ctrl;
    ///////////////////////////////////////////////////////////

    typedef union  TSRAMPWR_ctrl {
		UNSG32 u32[1];
	    struct {
	    struct w32SRAMPWR_ctrl;
		   };
		 } TSRAMPWR_ctrl;

    ///////////////////////////////////////////////////////////
     SIGN32 SRAMPWR_drvrd(SIE_SRAMPWR *p, UNSG32 base, SIGN32 mem, SIGN32 tst);
     SIGN32 SRAMPWR_drvwr(SIE_SRAMPWR *p, UNSG32 base, SIGN32 mem, SIGN32 tst, UNSG32 *pcmd);
       void SRAMPWR_reset(SIE_SRAMPWR *p);
     SIGN32 SRAMPWR_cmp(SIE_SRAMPWR *p, SIE_SRAMPWR *pie, char *pfx, void *hLOG, SIGN32 mem, SIGN32 tst);
    #define SRAMPWR_check(p, pie, pfx, hLOG) SRAMPWR_cmp(p, pie, pfx, (void *)(hLOG), 0, 0)
    #define SRAMPWR_print(p,    pfx, hLOG) SRAMPWR_cmp(p, 0,  pfx, (void *)(hLOG), 0, 0)

#endif
//////
/// ENDOFINTERFACE: SRAMPWR
////////////////////////////////////////////////////////////

//////
///
/// $INTERFACE SRAMRWTC                                 (4,4)
///     # # ----------------------------------------------------------
///     @ 0x00000 ctrl0                (P-)
///               ###
///               * Control register
///               ###
///               %unsigned 4  RF1P                      0x5
///                                    ###
///                                    * RTSEL [1:0] = 01 (default)
///                                    * WTSEL[3:2] = 01 (default)
///                                    ###
///               %unsigned 4  UHDRF1P                   0x9
///                                    ###
///                                    * RTSEL [1:0] = 01 (default)
///                                    * WTSEL[3:2] = 10 (default)
///                                    ###
///               %unsigned 8  RF2P                      0x35
///                                    ###
///                                    * RCT [1:0] = 01 (default)
///                                    * WCT [3:2] = 01 (default)
///                                    * KP[6:4]      = 011 (default)
///                                    * Bit7 not used
///                                    ###
///               %unsigned 8  UHDRF2P                   0x1
///                                    ###
///                                    * RTSEL [1:0] = 01 (default)
///                                    * WTSEL [3:2] = 00 (default)
///                                    * MTSEL [5:4] = 00 (default)
///                                    * Bit 7 and 8 not used
///                                    ###
///               %unsigned 8  UHDRF2P_ULVT              0x15
///                                    ###
///                                    * RTSEL [1:0] = 01 (default)
///                                    * WTSEL [3:2] = 01 (default)
///                                    * MTSEL [5:4] = 01 (default)
///                                    * Bit 7 and 8 not used
///                                    ###
///     @ 0x00004 ctrl1                (P-)
///               ###
///               * Control register
///               ###
///               %unsigned 4  SHDMBSR1P                 0x5
///                                    ###
///                                    * RTSEL[1:0] = 01 (default)
///                                    * WTSEL[3:2] = 01 (default)
///                                    ###
///               %unsigned 4  SHDSBSR1P                 0x1
///                                    ###
///                                    * RTSEL[1:0] = 01 (default)
///                                    * WTSEL[3:2] = 00 (default)
///                                    ###
///               %unsigned 4  SHCMBSR1P_SSEG            0x1
///                                    ###
///                                    * RTSEL[1:0] = 01 (default)
///                                    * WTSEL[3:2] = 00 (default)
///                                    ###
///               %unsigned 4  SHCMBSR1P_USEG            0x5
///                                    ###
///                                    * RTSEL[1:0] = 01 (default)
///                                    * WTSEL[3:2] = 01 (default)
///                                    ###
///               %unsigned 4  SHCSBSR1P                 0x5
///                                    ###
///                                    * RTSEL[1:0] = 01 (default)
///                                    * WTSEL[3:2] = 01 (default)
///                                    ###
///               %unsigned 4  SHCSBSR1P_CUSTM           0xD
///                                    ###
///                                    * RTSEL[1:0] = 01 (default)
///                                    * WTSEL[3:2] = 11 (default)
///                                    ###
///               %unsigned 4  SPSRAM_WT0                0x1
///                                    ###
///                                    * RTSEL[1:0] = 01 (default)
///                                    * WTSEL[3:2] = 00 (default)
///                                    ###
///               %unsigned 4  SPSRAM_WT1                0x5
///                                    ###
///                                    * RTSEL[1:0] = 01 (default)
///                                    * WTSEL[3:2] = 01 (default)
///                                    ###
///     @ 0x00008 ctrl2                (P-)
///               ###
///               * Control register
///               ###
///               %unsigned 4  L1CACHE                   0x0
///                                    ###
///                                    * MCR[1:0] = 00 (default)
///                                    * MCW[3:2] = 00 (default)
///                                    ###
///               %unsigned 4  DPSR2P                    0x5
///                                    ###
///                                    * RTSEL[1:0] = 01 (default)
///                                    * WTSEL[3:2] = 01 (default)
///                                    ###
///               %unsigned 8  ROM                       0x15
///                                    ###
///                                    * RTSEL[1:0] = 01 (default)
///                                    * PTSEL[3:2] = 01 (default)
///                                    * TRB[5:4]: 01
///                                    * TM[6]: 0
///                                    * Bit 7 not used
///                                    ###
///               %%        16         # Stuffing bits...
///     # # ----------------------------------------------------------
/// $ENDOFINTERFACE  # size:      12B, bits:      80b, padding:     0B
////////////////////////////////////////////////////////////
#ifndef h_SRAMRWTC
#define h_SRAMRWTC () {}

    #define     RA_SRAMRWTC_ctrl0                              0x0000

    #define     BA_SRAMRWTC_ctrl0_RF1P                         0x0000
    #define     B16SRAMRWTC_ctrl0_RF1P                         0x0000
    #define   LSb32SRAMRWTC_ctrl0_RF1P                            0
    #define   LSb16SRAMRWTC_ctrl0_RF1P                            0
    #define       bSRAMRWTC_ctrl0_RF1P                         4
    #define   MSK32SRAMRWTC_ctrl0_RF1P                            0x0000000F

    #define     BA_SRAMRWTC_ctrl0_UHDRF1P                      0x0000
    #define     B16SRAMRWTC_ctrl0_UHDRF1P                      0x0000
    #define   LSb32SRAMRWTC_ctrl0_UHDRF1P                         4
    #define   LSb16SRAMRWTC_ctrl0_UHDRF1P                         4
    #define       bSRAMRWTC_ctrl0_UHDRF1P                      4
    #define   MSK32SRAMRWTC_ctrl0_UHDRF1P                         0x000000F0

    #define     BA_SRAMRWTC_ctrl0_RF2P                         0x0001
    #define     B16SRAMRWTC_ctrl0_RF2P                         0x0000
    #define   LSb32SRAMRWTC_ctrl0_RF2P                            8
    #define   LSb16SRAMRWTC_ctrl0_RF2P                            8
    #define       bSRAMRWTC_ctrl0_RF2P                         8
    #define   MSK32SRAMRWTC_ctrl0_RF2P                            0x0000FF00

    #define     BA_SRAMRWTC_ctrl0_UHDRF2P                      0x0002
    #define     B16SRAMRWTC_ctrl0_UHDRF2P                      0x0002
    #define   LSb32SRAMRWTC_ctrl0_UHDRF2P                         16
    #define   LSb16SRAMRWTC_ctrl0_UHDRF2P                         0
    #define       bSRAMRWTC_ctrl0_UHDRF2P                      8
    #define   MSK32SRAMRWTC_ctrl0_UHDRF2P                         0x00FF0000

    #define     BA_SRAMRWTC_ctrl0_UHDRF2P_ULVT                 0x0003
    #define     B16SRAMRWTC_ctrl0_UHDRF2P_ULVT                 0x0002
    #define   LSb32SRAMRWTC_ctrl0_UHDRF2P_ULVT                    24
    #define   LSb16SRAMRWTC_ctrl0_UHDRF2P_ULVT                    8
    #define       bSRAMRWTC_ctrl0_UHDRF2P_ULVT                 8
    #define   MSK32SRAMRWTC_ctrl0_UHDRF2P_ULVT                    0xFF000000
    ///////////////////////////////////////////////////////////
    #define     RA_SRAMRWTC_ctrl1                              0x0004

    #define     BA_SRAMRWTC_ctrl1_SHDMBSR1P                    0x0004
    #define     B16SRAMRWTC_ctrl1_SHDMBSR1P                    0x0004
    #define   LSb32SRAMRWTC_ctrl1_SHDMBSR1P                       0
    #define   LSb16SRAMRWTC_ctrl1_SHDMBSR1P                       0
    #define       bSRAMRWTC_ctrl1_SHDMBSR1P                    4
    #define   MSK32SRAMRWTC_ctrl1_SHDMBSR1P                       0x0000000F

    #define     BA_SRAMRWTC_ctrl1_SHDSBSR1P                    0x0004
    #define     B16SRAMRWTC_ctrl1_SHDSBSR1P                    0x0004
    #define   LSb32SRAMRWTC_ctrl1_SHDSBSR1P                       4
    #define   LSb16SRAMRWTC_ctrl1_SHDSBSR1P                       4
    #define       bSRAMRWTC_ctrl1_SHDSBSR1P                    4
    #define   MSK32SRAMRWTC_ctrl1_SHDSBSR1P                       0x000000F0

    #define     BA_SRAMRWTC_ctrl1_SHCMBSR1P_SSEG               0x0005
    #define     B16SRAMRWTC_ctrl1_SHCMBSR1P_SSEG               0x0004
    #define   LSb32SRAMRWTC_ctrl1_SHCMBSR1P_SSEG                  8
    #define   LSb16SRAMRWTC_ctrl1_SHCMBSR1P_SSEG                  8
    #define       bSRAMRWTC_ctrl1_SHCMBSR1P_SSEG               4
    #define   MSK32SRAMRWTC_ctrl1_SHCMBSR1P_SSEG                  0x00000F00

    #define     BA_SRAMRWTC_ctrl1_SHCMBSR1P_USEG               0x0005
    #define     B16SRAMRWTC_ctrl1_SHCMBSR1P_USEG               0x0004
    #define   LSb32SRAMRWTC_ctrl1_SHCMBSR1P_USEG                  12
    #define   LSb16SRAMRWTC_ctrl1_SHCMBSR1P_USEG                  12
    #define       bSRAMRWTC_ctrl1_SHCMBSR1P_USEG               4
    #define   MSK32SRAMRWTC_ctrl1_SHCMBSR1P_USEG                  0x0000F000

    #define     BA_SRAMRWTC_ctrl1_SHCSBSR1P                    0x0006
    #define     B16SRAMRWTC_ctrl1_SHCSBSR1P                    0x0006
    #define   LSb32SRAMRWTC_ctrl1_SHCSBSR1P                       16
    #define   LSb16SRAMRWTC_ctrl1_SHCSBSR1P                       0
    #define       bSRAMRWTC_ctrl1_SHCSBSR1P                    4
    #define   MSK32SRAMRWTC_ctrl1_SHCSBSR1P                       0x000F0000

    #define     BA_SRAMRWTC_ctrl1_SHCSBSR1P_CUSTM              0x0006
    #define     B16SRAMRWTC_ctrl1_SHCSBSR1P_CUSTM              0x0006
    #define   LSb32SRAMRWTC_ctrl1_SHCSBSR1P_CUSTM                 20
    #define   LSb16SRAMRWTC_ctrl1_SHCSBSR1P_CUSTM                 4
    #define       bSRAMRWTC_ctrl1_SHCSBSR1P_CUSTM              4
    #define   MSK32SRAMRWTC_ctrl1_SHCSBSR1P_CUSTM                 0x00F00000

    #define     BA_SRAMRWTC_ctrl1_SPSRAM_WT0                   0x0007
    #define     B16SRAMRWTC_ctrl1_SPSRAM_WT0                   0x0006
    #define   LSb32SRAMRWTC_ctrl1_SPSRAM_WT0                      24
    #define   LSb16SRAMRWTC_ctrl1_SPSRAM_WT0                      8
    #define       bSRAMRWTC_ctrl1_SPSRAM_WT0                   4
    #define   MSK32SRAMRWTC_ctrl1_SPSRAM_WT0                      0x0F000000

    #define     BA_SRAMRWTC_ctrl1_SPSRAM_WT1                   0x0007
    #define     B16SRAMRWTC_ctrl1_SPSRAM_WT1                   0x0006
    #define   LSb32SRAMRWTC_ctrl1_SPSRAM_WT1                      28
    #define   LSb16SRAMRWTC_ctrl1_SPSRAM_WT1                      12
    #define       bSRAMRWTC_ctrl1_SPSRAM_WT1                   4
    #define   MSK32SRAMRWTC_ctrl1_SPSRAM_WT1                      0xF0000000
    ///////////////////////////////////////////////////////////
    #define     RA_SRAMRWTC_ctrl2                              0x0008

    #define     BA_SRAMRWTC_ctrl2_L1CACHE                      0x0008
    #define     B16SRAMRWTC_ctrl2_L1CACHE                      0x0008
    #define   LSb32SRAMRWTC_ctrl2_L1CACHE                         0
    #define   LSb16SRAMRWTC_ctrl2_L1CACHE                         0
    #define       bSRAMRWTC_ctrl2_L1CACHE                      4
    #define   MSK32SRAMRWTC_ctrl2_L1CACHE                         0x0000000F

    #define     BA_SRAMRWTC_ctrl2_DPSR2P                       0x0008
    #define     B16SRAMRWTC_ctrl2_DPSR2P                       0x0008
    #define   LSb32SRAMRWTC_ctrl2_DPSR2P                          4
    #define   LSb16SRAMRWTC_ctrl2_DPSR2P                          4
    #define       bSRAMRWTC_ctrl2_DPSR2P                       4
    #define   MSK32SRAMRWTC_ctrl2_DPSR2P                          0x000000F0

    #define     BA_SRAMRWTC_ctrl2_ROM                          0x0009
    #define     B16SRAMRWTC_ctrl2_ROM                          0x0008
    #define   LSb32SRAMRWTC_ctrl2_ROM                             8
    #define   LSb16SRAMRWTC_ctrl2_ROM                             8
    #define       bSRAMRWTC_ctrl2_ROM                          8
    #define   MSK32SRAMRWTC_ctrl2_ROM                             0x0000FF00
    ///////////////////////////////////////////////////////////

    typedef struct SIE_SRAMRWTC {
    ///////////////////////////////////////////////////////////
    #define   GET32SRAMRWTC_ctrl0_RF1P(r32)                    _BFGET_(r32, 3, 0)
    #define   SET32SRAMRWTC_ctrl0_RF1P(r32, v)                  _BFSET_(r32, 3, 0, v)
    #define   GET16SRAMRWTC_ctrl0_RF1P(r16)                    _BFGET_(r16, 3, 0)
    #define   SET16SRAMRWTC_ctrl0_RF1P(r16, v)                  _BFSET_(r16, 3, 0, v)

    #define   GET32SRAMRWTC_ctrl0_UHDRF1P(r32)                 _BFGET_(r32, 7, 4)
    #define   SET32SRAMRWTC_ctrl0_UHDRF1P(r32, v)               _BFSET_(r32, 7, 4, v)
    #define   GET16SRAMRWTC_ctrl0_UHDRF1P(r16)                 _BFGET_(r16, 7, 4)
    #define   SET16SRAMRWTC_ctrl0_UHDRF1P(r16, v)               _BFSET_(r16, 7, 4, v)

    #define   GET32SRAMRWTC_ctrl0_RF2P(r32)                    _BFGET_(r32, 15, 8)
    #define   SET32SRAMRWTC_ctrl0_RF2P(r32, v)                  _BFSET_(r32, 15, 8, v)
    #define   GET16SRAMRWTC_ctrl0_RF2P(r16)                    _BFGET_(r16, 15, 8)
    #define   SET16SRAMRWTC_ctrl0_RF2P(r16, v)                  _BFSET_(r16, 15, 8, v)

    #define   GET32SRAMRWTC_ctrl0_UHDRF2P(r32)                 _BFGET_(r32, 23, 16)
    #define   SET32SRAMRWTC_ctrl0_UHDRF2P(r32, v)               _BFSET_(r32, 23, 16, v)
    #define   GET16SRAMRWTC_ctrl0_UHDRF2P(r16)                 _BFGET_(r16, 7, 0)
    #define   SET16SRAMRWTC_ctrl0_UHDRF2P(r16, v)               _BFSET_(r16, 7, 0, v)

    #define   GET32SRAMRWTC_ctrl0_UHDRF2P_ULVT(r32)            _BFGET_(r32, 31, 24)
    #define   SET32SRAMRWTC_ctrl0_UHDRF2P_ULVT(r32, v)          _BFSET_(r32, 31, 24, v)
    #define   GET16SRAMRWTC_ctrl0_UHDRF2P_ULVT(r16)            _BFGET_(r16, 15, 8)
    #define   SET16SRAMRWTC_ctrl0_UHDRF2P_ULVT(r16, v)          _BFSET_(r16, 15, 8, v)

    #define     w32SRAMRWTC_ctrl0                              {\
	    UNSG32 uctrl0_RF1P                                 :  4;\
	    UNSG32 uctrl0_UHDRF1P                              :  4;\
	    UNSG32 uctrl0_RF2P                                 :  8;\
	    UNSG32 uctrl0_UHDRF2P                              :  8;\
	    UNSG32 uctrl0_UHDRF2P_ULVT                         :  8;\
	}
    union { UNSG32 u32SRAMRWTC_ctrl0;
	    struct w32SRAMRWTC_ctrl0;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32SRAMRWTC_ctrl1_SHDMBSR1P(r32)               _BFGET_(r32, 3, 0)
    #define   SET32SRAMRWTC_ctrl1_SHDMBSR1P(r32, v)             _BFSET_(r32, 3, 0, v)
    #define   GET16SRAMRWTC_ctrl1_SHDMBSR1P(r16)               _BFGET_(r16, 3, 0)
    #define   SET16SRAMRWTC_ctrl1_SHDMBSR1P(r16, v)             _BFSET_(r16, 3, 0, v)

    #define   GET32SRAMRWTC_ctrl1_SHDSBSR1P(r32)               _BFGET_(r32, 7, 4)
    #define   SET32SRAMRWTC_ctrl1_SHDSBSR1P(r32, v)             _BFSET_(r32, 7, 4, v)
    #define   GET16SRAMRWTC_ctrl1_SHDSBSR1P(r16)               _BFGET_(r16, 7, 4)
    #define   SET16SRAMRWTC_ctrl1_SHDSBSR1P(r16, v)             _BFSET_(r16, 7, 4, v)

    #define   GET32SRAMRWTC_ctrl1_SHCMBSR1P_SSEG(r32)          _BFGET_(r32, 11, 8)
    #define   SET32SRAMRWTC_ctrl1_SHCMBSR1P_SSEG(r32, v)        _BFSET_(r32, 11, 8, v)
    #define   GET16SRAMRWTC_ctrl1_SHCMBSR1P_SSEG(r16)          _BFGET_(r16, 11, 8)
    #define   SET16SRAMRWTC_ctrl1_SHCMBSR1P_SSEG(r16, v)        _BFSET_(r16, 11, 8, v)

    #define   GET32SRAMRWTC_ctrl1_SHCMBSR1P_USEG(r32)          _BFGET_(r32, 15, 12)
    #define   SET32SRAMRWTC_ctrl1_SHCMBSR1P_USEG(r32, v)        _BFSET_(r32, 15, 12, v)
    #define   GET16SRAMRWTC_ctrl1_SHCMBSR1P_USEG(r16)          _BFGET_(r16, 15, 12)
    #define   SET16SRAMRWTC_ctrl1_SHCMBSR1P_USEG(r16, v)        _BFSET_(r16, 15, 12, v)

    #define   GET32SRAMRWTC_ctrl1_SHCSBSR1P(r32)               _BFGET_(r32, 19, 16)
    #define   SET32SRAMRWTC_ctrl1_SHCSBSR1P(r32, v)             _BFSET_(r32, 19, 16, v)
    #define   GET16SRAMRWTC_ctrl1_SHCSBSR1P(r16)               _BFGET_(r16, 3, 0)
    #define   SET16SRAMRWTC_ctrl1_SHCSBSR1P(r16, v)             _BFSET_(r16, 3, 0, v)

    #define   GET32SRAMRWTC_ctrl1_SHCSBSR1P_CUSTM(r32)         _BFGET_(r32, 23, 20)
    #define   SET32SRAMRWTC_ctrl1_SHCSBSR1P_CUSTM(r32, v)       _BFSET_(r32, 23, 20, v)
    #define   GET16SRAMRWTC_ctrl1_SHCSBSR1P_CUSTM(r16)         _BFGET_(r16, 7, 4)
    #define   SET16SRAMRWTC_ctrl1_SHCSBSR1P_CUSTM(r16, v)       _BFSET_(r16, 7, 4, v)

    #define   GET32SRAMRWTC_ctrl1_SPSRAM_WT0(r32)              _BFGET_(r32, 27, 24)
    #define   SET32SRAMRWTC_ctrl1_SPSRAM_WT0(r32, v)            _BFSET_(r32, 27, 24, v)
    #define   GET16SRAMRWTC_ctrl1_SPSRAM_WT0(r16)              _BFGET_(r16, 11, 8)
    #define   SET16SRAMRWTC_ctrl1_SPSRAM_WT0(r16, v)            _BFSET_(r16, 11, 8, v)

    #define   GET32SRAMRWTC_ctrl1_SPSRAM_WT1(r32)              _BFGET_(r32, 31, 28)
    #define   SET32SRAMRWTC_ctrl1_SPSRAM_WT1(r32, v)            _BFSET_(r32, 31, 28, v)
    #define   GET16SRAMRWTC_ctrl1_SPSRAM_WT1(r16)              _BFGET_(r16, 15, 12)
    #define   SET16SRAMRWTC_ctrl1_SPSRAM_WT1(r16, v)            _BFSET_(r16, 15, 12, v)

    #define     w32SRAMRWTC_ctrl1                              {\
	    UNSG32 uctrl1_SHDMBSR1P                            :  4;\
	    UNSG32 uctrl1_SHDSBSR1P                            :  4;\
	    UNSG32 uctrl1_SHCMBSR1P_SSEG                       :  4;\
	    UNSG32 uctrl1_SHCMBSR1P_USEG                       :  4;\
	    UNSG32 uctrl1_SHCSBSR1P                            :  4;\
	    UNSG32 uctrl1_SHCSBSR1P_CUSTM                      :  4;\
	    UNSG32 uctrl1_SPSRAM_WT0                           :  4;\
	    UNSG32 uctrl1_SPSRAM_WT1                           :  4;\
	}
    union { UNSG32 u32SRAMRWTC_ctrl1;
	    struct w32SRAMRWTC_ctrl1;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32SRAMRWTC_ctrl2_L1CACHE(r32)                 _BFGET_(r32, 3, 0)
    #define   SET32SRAMRWTC_ctrl2_L1CACHE(r32, v)               _BFSET_(r32, 3, 0, v)
    #define   GET16SRAMRWTC_ctrl2_L1CACHE(r16)                 _BFGET_(r16, 3, 0)
    #define   SET16SRAMRWTC_ctrl2_L1CACHE(r16, v)               _BFSET_(r16, 3, 0, v)

    #define   GET32SRAMRWTC_ctrl2_DPSR2P(r32)                  _BFGET_(r32, 7, 4)
    #define   SET32SRAMRWTC_ctrl2_DPSR2P(r32, v)                _BFSET_(r32, 7, 4, v)
    #define   GET16SRAMRWTC_ctrl2_DPSR2P(r16)                  _BFGET_(r16, 7, 4)
    #define   SET16SRAMRWTC_ctrl2_DPSR2P(r16, v)                _BFSET_(r16, 7, 4, v)

    #define   GET32SRAMRWTC_ctrl2_ROM(r32)                     _BFGET_(r32, 15, 8)
    #define   SET32SRAMRWTC_ctrl2_ROM(r32, v)                   _BFSET_(r32, 15, 8, v)
    #define   GET16SRAMRWTC_ctrl2_ROM(r16)                     _BFGET_(r16, 15, 8)
    #define   SET16SRAMRWTC_ctrl2_ROM(r16, v)                   _BFSET_(r16, 15, 8, v)

    #define     w32SRAMRWTC_ctrl2                              {\
	    UNSG32 uctrl2_L1CACHE                              :  4;\
	    UNSG32 uctrl2_DPSR2P                               :  4;\
	    UNSG32 uctrl2_ROM                                  :  8;\
	    UNSG32 RSVDx8_b16                                  : 16;\
	}
    union { UNSG32 u32SRAMRWTC_ctrl2;
	    struct w32SRAMRWTC_ctrl2;
	  };
    ///////////////////////////////////////////////////////////
    } SIE_SRAMRWTC;

    typedef union  T32SRAMRWTC_ctrl0 {
		UNSG32 u32;
	    struct w32SRAMRWTC_ctrl0;
		 } T32SRAMRWTC_ctrl0;
    typedef union  T32SRAMRWTC_ctrl1 {
		UNSG32 u32;
	    struct w32SRAMRWTC_ctrl1;
		 } T32SRAMRWTC_ctrl1;
    typedef union  T32SRAMRWTC_ctrl2 {
		UNSG32 u32;
	    struct w32SRAMRWTC_ctrl2;
		 } T32SRAMRWTC_ctrl2;
    ///////////////////////////////////////////////////////////

    typedef union  TSRAMRWTC_ctrl0 {
		UNSG32 u32[1];
	    struct {
	    struct w32SRAMRWTC_ctrl0;
		   };
		 } TSRAMRWTC_ctrl0;
    typedef union  TSRAMRWTC_ctrl1 {
		UNSG32 u32[1];
	    struct {
	    struct w32SRAMRWTC_ctrl1;
		   };
		 } TSRAMRWTC_ctrl1;
    typedef union  TSRAMRWTC_ctrl2 {
		UNSG32 u32[1];
	    struct {
	    struct w32SRAMRWTC_ctrl2;
		   };
		 } TSRAMRWTC_ctrl2;

    ///////////////////////////////////////////////////////////
     SIGN32 SRAMRWTC_drvrd(SIE_SRAMRWTC *p, UNSG32 base, SIGN32 mem, SIGN32 tst);
     SIGN32 SRAMRWTC_drvwr(SIE_SRAMRWTC *p, UNSG32 base, SIGN32 mem, SIGN32 tst, UNSG32 *pcmd);
       void SRAMRWTC_reset(SIE_SRAMRWTC *p);
     SIGN32 SRAMRWTC_cmp(SIE_SRAMRWTC *p, SIE_SRAMRWTC *pie, char *pfx, void *hLOG, SIGN32 mem, SIGN32 tst);
    #define SRAMRWTC_check(p, pie, pfx, hLOG) SRAMRWTC_cmp(p, pie, pfx, (void *)(hLOG), 0, 0)
    #define SRAMRWTC_print(p,    pfx, hLOG) SRAMRWTC_cmp(p, 0,  pfx, (void *)(hLOG), 0, 0)

#endif
//////
/// ENDOFINTERFACE: SRAMRWTC
////////////////////////////////////////////////////////////

//////
///
/// $INTERFACE INT                     biu              (4,4)
///     # # ----------------------------------------------------------
///     @ 0x00000 EN                   (P)
///               %unsigned 15 bus                       0x0
///                                    ###
///                                    * Interrupt Enable. Bit wise mapping given below
///                                    * 0 : DMIC Port interrupt enable
///                                    * 1 : Force Mute interrupt enable
///                                    * 2 : PTRACK1 interrupt enable
///                                    * 3 : PTRACK2 interrupt enable
///                                    * 4 : I2S1 sample count interrupt enable
///                                    * 5 : I2S2 sample count interrupt enable
///                                    * 6 : I2S3 sample count interrupt enable
///                                    * 7 : I2S4 sample count interrupt enable
///                                    * 8 : I2S5 sample count interrupt enable
///                                    * 9 : DRT sample count interrupt enable
///                                    * 10 : DCLASS sample count interrupt enable
///                                    * 11 : PDM sample count interrupt enable
///                                    * 12 : DMIC sample count interrupt enable
///                                    * 13 : DCLASS interrupt enable
///                                    * 14 : DRT interrupt enable
///                                    ###
///               %%        17         # Stuffing bits...
///     @ 0x00004 STS                  (R-)
///               %unsigned 15 bus
///                                    ###
///                                    * Interrupt Status. Bit wise mapping given below
///                                    * 0 : DMIC Port interrupt
///                                    * 1 : Force Mute interrupt
///                                    * 2 : PTRACK1 interrupt
///                                    * 3 : PTRACK2 interrupt
///                                    * 4 : I2S1 sample count interrupt
///                                    * 5 : I2S2 sample count interrupt
///                                    * 6 : I2S3 sample count interrupt
///                                    * 7 : I2S4 sample count interrupt
///                                    * 8 : I2S5 sample count interrupt
///                                    * 9 : DRT sample count interrupt
///                                    * 10 : DCLASS sample count interrupt
///                                    * 11 : PDM sample count interrupt
///                                    * 12 : DMIC sample count interrupt
///                                    * 13 : DCLASS interrupt
///                                    * 14 : DRT interrupt
///                                    ###
///               %%        17         # Stuffing bits...
///     # # ----------------------------------------------------------
/// $ENDOFINTERFACE  # size:       8B, bits:      30b, padding:     0B
////////////////////////////////////////////////////////////
#ifndef h_INT
#define h_INT () {}

    #define     RA_INT_EN                                      0x0000

    #define     BA_INT_EN_bus                                  0x0000
    #define     B16INT_EN_bus                                  0x0000
    #define   LSb32INT_EN_bus                                     0
    #define   LSb16INT_EN_bus                                     0
    #define       bINT_EN_bus                                  15
    #define   MSK32INT_EN_bus                                     0x00007FFF
    ///////////////////////////////////////////////////////////
    #define     RA_INT_STS                                     0x0004

    #define     BA_INT_STS_bus                                 0x0004
    #define     B16INT_STS_bus                                 0x0004
    #define   LSb32INT_STS_bus                                    0
    #define   LSb16INT_STS_bus                                    0
    #define       bINT_STS_bus                                 15
    #define   MSK32INT_STS_bus                                    0x00007FFF
    ///////////////////////////////////////////////////////////

    typedef struct SIE_INT {
    ///////////////////////////////////////////////////////////
    #define   GET32INT_EN_bus(r32)                             _BFGET_(r32, 14, 0)
    #define   SET32INT_EN_bus(r32, v)                           _BFSET_(r32, 14, 0, v)
    #define   GET16INT_EN_bus(r16)                             _BFGET_(r16, 14, 0)
    #define   SET16INT_EN_bus(r16, v)                           _BFSET_(r16, 14, 0, v)

    #define     w32INT_EN                                      {\
	    UNSG32 uEN_bus                                     : 15;\
	    UNSG32 RSVDx0_b15                                  : 17;\
	}
    union { UNSG32 u32INT_EN;
	    struct w32INT_EN;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32INT_STS_bus(r32)                            _BFGET_(r32, 14, 0)
    #define   SET32INT_STS_bus(r32, v)                          _BFSET_(r32, 14, 0, v)
    #define   GET16INT_STS_bus(r16)                            _BFGET_(r16, 14, 0)
    #define   SET16INT_STS_bus(r16, v)                          _BFSET_(r16, 14, 0, v)

    #define     w32INT_STS                                     {\
	    UNSG32 uSTS_bus                                    : 15;\
	    UNSG32 RSVDx4_b15                                  : 17;\
	}
    union { UNSG32 u32INT_STS;
	    struct w32INT_STS;
	  };
    ///////////////////////////////////////////////////////////
    } SIE_INT;

    typedef union  T32INT_EN {
		UNSG32 u32;
	    struct w32INT_EN;
		 } T32INT_EN;
    typedef union  T32INT_STS {
		UNSG32 u32;
	    struct w32INT_STS;
		 } T32INT_STS;
    ///////////////////////////////////////////////////////////

    typedef union  TINT_EN {
		UNSG32 u32[1];
	    struct {
	    struct w32INT_EN;
		   };
		 } TINT_EN;
    typedef union  TINT_STS {
		UNSG32 u32[1];
	    struct {
	    struct w32INT_STS;
		   };
		 } TINT_STS;

    ///////////////////////////////////////////////////////////
     SIGN32 INT_drvrd(SIE_INT *p, UNSG32 base, SIGN32 mem, SIGN32 tst);
     SIGN32 INT_drvwr(SIE_INT *p, UNSG32 base, SIGN32 mem, SIGN32 tst, UNSG32 *pcmd);
       void INT_reset(SIE_INT *p);
     SIGN32 INT_cmp(SIE_INT *p, SIE_INT *pie, char *pfx, void *hLOG, SIGN32 mem, SIGN32 tst);
    #define INT_check(p, pie, pfx, hLOG) INT_cmp(p, pie, pfx, (void *)(hLOG), 0, 0)
    #define INT_print(p,    pfx, hLOG) INT_cmp(p, 0,  pfx, (void *)(hLOG), 0, 0)

#endif
//////
/// ENDOFINTERFACE: INT
////////////////////////////////////////////////////////////

//////
///
/// $INTERFACE AVIO_debug_ctrl         biu              (4,4)
///     # # ----------------------------------------------------------
///     @ 0x00000 Ctrl0                (P)
///               %unsigned 5  debug_ctrl0               0x0
///                                    ###
///                                    * AVIO debug control [4:0] : connected to pad_pin_mux
///                                    ###
///               %%        27         # Stuffing bits...
///     # # ----------------------------------------------------------
/// $ENDOFINTERFACE  # size:       4B, bits:       5b, padding:     0B
////////////////////////////////////////////////////////////
#ifndef h_AVIO_debug_ctrl
#define h_AVIO_debug_ctrl () {}

    #define     RA_AVIO_debug_ctrl_Ctrl0                       0x0000

    #define     BA_AVIO_debug_ctrl_Ctrl0_debug_ctrl0           0x0000
    #define     B16AVIO_debug_ctrl_Ctrl0_debug_ctrl0           0x0000
    #define   LSb32AVIO_debug_ctrl_Ctrl0_debug_ctrl0              0
    #define   LSb16AVIO_debug_ctrl_Ctrl0_debug_ctrl0              0
    #define       bAVIO_debug_ctrl_Ctrl0_debug_ctrl0           5
    #define   MSK32AVIO_debug_ctrl_Ctrl0_debug_ctrl0              0x0000001F
    ///////////////////////////////////////////////////////////

    typedef struct SIE_AVIO_debug_ctrl {
    ///////////////////////////////////////////////////////////
    #define   GET32AVIO_debug_ctrl_Ctrl0_debug_ctrl0(r32)      _BFGET_(r32, 4, 0)
    #define   SET32AVIO_debug_ctrl_Ctrl0_debug_ctrl0(r32, v)    _BFSET_(r32, 4, 0, v)
    #define   GET16AVIO_debug_ctrl_Ctrl0_debug_ctrl0(r16)      _BFGET_(r16, 4, 0)
    #define   SET16AVIO_debug_ctrl_Ctrl0_debug_ctrl0(r16, v)    _BFSET_(r16, 4, 0, v)

    #define     w32AVIO_debug_ctrl_Ctrl0                       {\
	    UNSG32 uCtrl0_debug_ctrl0                          :  5;\
	    UNSG32 RSVDx0_b5                                   : 27;\
	}
    union { UNSG32 u32AVIO_debug_ctrl_Ctrl0;
	    struct w32AVIO_debug_ctrl_Ctrl0;
	  };
    ///////////////////////////////////////////////////////////
    } SIE_AVIO_debug_ctrl;

    typedef union  T32AVIO_debug_ctrl_Ctrl0 {
		UNSG32 u32;
	    struct w32AVIO_debug_ctrl_Ctrl0;
		 } T32AVIO_debug_ctrl_Ctrl0;
    ///////////////////////////////////////////////////////////

    typedef union  TAVIO_debug_ctrl_Ctrl0 {
		UNSG32 u32[1];
	    struct {
	    struct w32AVIO_debug_ctrl_Ctrl0;
		   };
		 } TAVIO_debug_ctrl_Ctrl0;

    ///////////////////////////////////////////////////////////
     SIGN32 AVIO_debug_ctrl_drvrd(SIE_AVIO_debug_ctrl *p, UNSG32 base, SIGN32 mem, SIGN32 tst);
     SIGN32 AVIO_debug_ctrl_drvwr(SIE_AVIO_debug_ctrl *p, UNSG32 base, SIGN32 mem, SIGN32 tst, UNSG32 *pcmd);
       void AVIO_debug_ctrl_reset(SIE_AVIO_debug_ctrl *p);
     SIGN32 AVIO_debug_ctrl_cmp(SIE_AVIO_debug_ctrl *p, SIE_AVIO_debug_ctrl *pie, char *pfx, void *hLOG, SIGN32 mem, SIGN32 tst);
    #define AVIO_debug_ctrl_check(p, pie, pfx, hLOG) AVIO_debug_ctrl_cmp(p, pie, pfx, (void *)(hLOG), 0, 0)
    #define AVIO_debug_ctrl_print(p,    pfx, hLOG) AVIO_debug_ctrl_cmp(p, 0,  pfx, (void *)(hLOG), 0, 0)

#endif
//////
/// ENDOFINTERFACE: AVIO_debug_ctrl
////////////////////////////////////////////////////////////

//////
///
/// $INTERFACE Dummy3Reg                                (4,4)
///     # # ----------------------------------------------------------
///     @ 0x00000                      (R-)
///               %unsigned 32 0x0
///                                    ###
///                                    * dummy3 registers
///                                    ###
///     # # ----------------------------------------------------------
/// $ENDOFINTERFACE  # size:       4B, bits:      32b, padding:     0B
////////////////////////////////////////////////////////////
#ifndef h_Dummy3Reg
#define h_Dummy3Reg () {}

    #define     BA_Dummy3Reg_0x0                               0x0000
    #define     B16Dummy3Reg_0x0                               0x0000
    #define   LSb32Dummy3Reg_0x0                                  0
    #define   LSb16Dummy3Reg_0x0                                  0
    #define       bDummy3Reg_0x0                               32
    #define   MSK32Dummy3Reg_0x0                                  0xFFFFFFFF
    ///////////////////////////////////////////////////////////

    typedef struct SIE_Dummy3Reg {
    ///////////////////////////////////////////////////////////
    #define   GET32Dummy3Reg_0x0(r32)                          _BFGET_(r32, 31, 0)
    #define   SET32Dummy3Reg_0x0(r32, v)                        _BFSET_(r32, 31, 0, v)

	    UNSG32 u_0x0                                       : 32;
    ///////////////////////////////////////////////////////////
    } SIE_Dummy3Reg;

    ///////////////////////////////////////////////////////////
     SIGN32 Dummy3Reg_drvrd(SIE_Dummy3Reg *p, UNSG32 base, SIGN32 mem, SIGN32 tst);
     SIGN32 Dummy3Reg_drvwr(SIE_Dummy3Reg *p, UNSG32 base, SIGN32 mem, SIGN32 tst, UNSG32 *pcmd);
       void Dummy3Reg_reset(SIE_Dummy3Reg *p);
     SIGN32 Dummy3Reg_cmp(SIE_Dummy3Reg *p, SIE_Dummy3Reg *pie, char *pfx, void *hLOG, SIGN32 mem, SIGN32 tst);
    #define Dummy3Reg_check(p, pie, pfx, hLOG) Dummy3Reg_cmp(p, pie, pfx, (void *)(hLOG), 0, 0)
    #define Dummy3Reg_print(p,    pfx, hLOG) Dummy3Reg_cmp(p, 0,  pfx, (void *)(hLOG), 0, 0)

#endif
//////
/// ENDOFINTERFACE: Dummy3Reg
////////////////////////////////////////////////////////////

//////
///
/// $INTERFACE AVIOGBLREG3                              (4,4)
///     # # ----------------------------------------------------------
///     @ 0x00000                      (P)
///     # 0x00000 Dummy3
///               $Dummy3Reg           Dummy3            REG    [2048]
///                                    ###
///                                    * dummy1 registers
///                                    ###
///     # # ----------------------------------------------------------
/// $ENDOFINTERFACE  # size:    8192B, bits:   65536b, padding:     0B
////////////////////////////////////////////////////////////
#ifndef h_AVIOGBLREG3
#define h_AVIOGBLREG3 () {}

    #define     RA_AVIOGBLREG3_Dummy3                          0x0000
    ///////////////////////////////////////////////////////////

    typedef struct SIE_AVIOGBLREG3 {
    ///////////////////////////////////////////////////////////
	      SIE_Dummy3Reg                                    ie_Dummy3[2048];
    ///////////////////////////////////////////////////////////
    } SIE_AVIOGBLREG3;

    ///////////////////////////////////////////////////////////
     SIGN32 AVIOGBLREG3_drvrd(SIE_AVIOGBLREG3 *p, UNSG32 base, SIGN32 mem, SIGN32 tst);
     SIGN32 AVIOGBLREG3_drvwr(SIE_AVIOGBLREG3 *p, UNSG32 base, SIGN32 mem, SIGN32 tst, UNSG32 *pcmd);
       void AVIOGBLREG3_reset(SIE_AVIOGBLREG3 *p);
     SIGN32 AVIOGBLREG3_cmp(SIE_AVIOGBLREG3 *p, SIE_AVIOGBLREG3 *pie, char *pfx, void *hLOG, SIGN32 mem, SIGN32 tst);
    #define AVIOGBLREG3_check(p, pie, pfx, hLOG) AVIOGBLREG3_cmp(p, pie, pfx, (void *)(hLOG), 0, 0)
    #define AVIOGBLREG3_print(p,    pfx, hLOG) AVIOGBLREG3_cmp(p, 0,  pfx, (void *)(hLOG), 0, 0)

#endif
//////
/// ENDOFINTERFACE: AVIOGBLREG3
////////////////////////////////////////////////////////////

//////
///
/// $INTERFACE APLL_WRAP               biu              (4,4)
///     # # ----------------------------------------------------------
///     @ 0x00000 APLL_CLK1_CTRL       (P)
///               ###
///               * Clock controls for APLL CLK after APLL
///               ###
///               %unsigned 1  clkSwitch                 0x0
///                                    ###
///                                    * 0: use source clock
///                                    * 1: use divided clock (decided by clkD3Switch and clkSel)
///                                    ###
///               %unsigned 1  clkD3Switch               0x0
///                                    ###
///                                    * 0 : divide factor is decided by clkSwitch and clkSel
///                                    * 1: use divide by 3 clock when clkSwitch = 1
///                                    ###
///               %unsigned 3  clkSel                    0x0
///                                    ###
///                                    * Use the following divide factor if clkD3Switch=0.
///                                    ###
///                                    : d2                        0x1
///                                    : d4                        0x2
///                                    : d6                        0x3
///                                    : d8                        0x4
///                                    : d12                       0x5
///               %unsigned 1  clkEn                     0x0
///                                    ###
///                                    * Clock enable for APLL.
///                                    ###
///               %%        26         # Stuffing bits...
///     @ 0x00004 CTRL0                (P)
///               %unsigned 4  clk_sel0                  0x0
///                                    ###
///                                    * Register used for clock selection
///                                    * 0: I2S1_BCLKIO_DO_LPBK
///                                    * 1: I2S2_BCLKIO_DO_LPBK
///                                    * 2: I2S3_BCLKIO_DO_LPBK
///                                    * 3: I2S4_BCLKIO_DO_LPBK
///                                    * 4: I2S5_BCLKIO_DO_LPBK
///                                    * 5: PDM_CLKIO_DO_LPBK
///                                    * 6: I2S1_MCLK_DO_LPBK
///                                    * 7: TDO_DO_LPBK
///                                    * 8: I2S1_BCLKIO_DI
///                                    * 9: I2S2_BCLKIO_DI
///                                    * 10: I2S3_BCLKIO_DI
///                                    * 11: I2S4_BCLKIO_DI
///                                    * 12: I2S5_BCLKIO_DI
///                                    * 13: PDM_CLKIO_DI
///                                    * 14: I2S1_MCLK_DI
///                                    * 15: I2S2_MCLK_DI
///                                    ###
///               %unsigned 1  clk_sel1                  0x0
///                                    ###
///                                    * Register used for clock selection
///                                    * 0: VPLL0_CLK
///                                    * 1: VPLL1_CLK
///                                    ###
///               %unsigned 2  clk_sel2                  0x0
///                                    ###
///                                    * Register used for clock selection
///                                    * 0: I2S or PDM clock selected based on clk_sel0
///                                    * 1: APLL loop back clock
///                                    * 2: VPLL0_CLK or VPLL1_CLK
///                                    * 3: DAIF_if_clk_pll_DI
///                                    ###
///               %unsigned 1  clk_sel3                  0x0
///                                    ###
///                                    * Register used for clock selection
///                                    * 0: APLL ref clock (source clock)
///                                    * 1: clock selected based on clk_sel2
///                                    ###
///               %%        24         # Stuffing bits...
///     @ 0x00008                      (P)
///     # 0x00008 APLL
///               $abipll              APLL              REG
///                                    ###
///                                    * All the registers for APLL
///                                    ###
///     # # ----------------------------------------------------------
/// $ENDOFINTERFACE  # size:      40B, bits:      79b, padding:     0B
////////////////////////////////////////////////////////////
#ifndef h_APLL_WRAP
#define h_APLL_WRAP () {}

    #define     RA_APLL_WRAP_APLL_CLK1_CTRL                    0x0000

    #define     BA_APLL_WRAP_APLL_CLK1_CTRL_clkSwitch          0x0000
    #define     B16APLL_WRAP_APLL_CLK1_CTRL_clkSwitch          0x0000
    #define   LSb32APLL_WRAP_APLL_CLK1_CTRL_clkSwitch             0
    #define   LSb16APLL_WRAP_APLL_CLK1_CTRL_clkSwitch             0
    #define       bAPLL_WRAP_APLL_CLK1_CTRL_clkSwitch          1
    #define   MSK32APLL_WRAP_APLL_CLK1_CTRL_clkSwitch             0x00000001

    #define     BA_APLL_WRAP_APLL_CLK1_CTRL_clkD3Switch        0x0000
    #define     B16APLL_WRAP_APLL_CLK1_CTRL_clkD3Switch        0x0000
    #define   LSb32APLL_WRAP_APLL_CLK1_CTRL_clkD3Switch           1
    #define   LSb16APLL_WRAP_APLL_CLK1_CTRL_clkD3Switch           1
    #define       bAPLL_WRAP_APLL_CLK1_CTRL_clkD3Switch        1
    #define   MSK32APLL_WRAP_APLL_CLK1_CTRL_clkD3Switch           0x00000002

    #define     BA_APLL_WRAP_APLL_CLK1_CTRL_clkSel             0x0000
    #define     B16APLL_WRAP_APLL_CLK1_CTRL_clkSel             0x0000
    #define   LSb32APLL_WRAP_APLL_CLK1_CTRL_clkSel                2
    #define   LSb16APLL_WRAP_APLL_CLK1_CTRL_clkSel                2
    #define       bAPLL_WRAP_APLL_CLK1_CTRL_clkSel             3
    #define   MSK32APLL_WRAP_APLL_CLK1_CTRL_clkSel                0x0000001C
    #define        APLL_WRAP_APLL_CLK1_CTRL_clkSel_d2                       0x1
    #define        APLL_WRAP_APLL_CLK1_CTRL_clkSel_d4                       0x2
    #define        APLL_WRAP_APLL_CLK1_CTRL_clkSel_d6                       0x3
    #define        APLL_WRAP_APLL_CLK1_CTRL_clkSel_d8                       0x4
    #define        APLL_WRAP_APLL_CLK1_CTRL_clkSel_d12                      0x5

    #define     BA_APLL_WRAP_APLL_CLK1_CTRL_clkEn              0x0000
    #define     B16APLL_WRAP_APLL_CLK1_CTRL_clkEn              0x0000
    #define   LSb32APLL_WRAP_APLL_CLK1_CTRL_clkEn                 5
    #define   LSb16APLL_WRAP_APLL_CLK1_CTRL_clkEn                 5
    #define       bAPLL_WRAP_APLL_CLK1_CTRL_clkEn              1
    #define   MSK32APLL_WRAP_APLL_CLK1_CTRL_clkEn                 0x00000020
    ///////////////////////////////////////////////////////////
    #define     RA_APLL_WRAP_CTRL0                             0x0004

    #define     BA_APLL_WRAP_CTRL0_clk_sel0                    0x0004
    #define     B16APLL_WRAP_CTRL0_clk_sel0                    0x0004
    #define   LSb32APLL_WRAP_CTRL0_clk_sel0                       0
    #define   LSb16APLL_WRAP_CTRL0_clk_sel0                       0
    #define       bAPLL_WRAP_CTRL0_clk_sel0                    4
    #define   MSK32APLL_WRAP_CTRL0_clk_sel0                       0x0000000F

    #define     BA_APLL_WRAP_CTRL0_clk_sel1                    0x0004
    #define     B16APLL_WRAP_CTRL0_clk_sel1                    0x0004
    #define   LSb32APLL_WRAP_CTRL0_clk_sel1                       4
    #define   LSb16APLL_WRAP_CTRL0_clk_sel1                       4
    #define       bAPLL_WRAP_CTRL0_clk_sel1                    1
    #define   MSK32APLL_WRAP_CTRL0_clk_sel1                       0x00000010

    #define     BA_APLL_WRAP_CTRL0_clk_sel2                    0x0004
    #define     B16APLL_WRAP_CTRL0_clk_sel2                    0x0004
    #define   LSb32APLL_WRAP_CTRL0_clk_sel2                       5
    #define   LSb16APLL_WRAP_CTRL0_clk_sel2                       5
    #define       bAPLL_WRAP_CTRL0_clk_sel2                    2
    #define   MSK32APLL_WRAP_CTRL0_clk_sel2                       0x00000060

    #define     BA_APLL_WRAP_CTRL0_clk_sel3                    0x0004
    #define     B16APLL_WRAP_CTRL0_clk_sel3                    0x0004
    #define   LSb32APLL_WRAP_CTRL0_clk_sel3                       7
    #define   LSb16APLL_WRAP_CTRL0_clk_sel3                       7
    #define       bAPLL_WRAP_CTRL0_clk_sel3                    1
    #define   MSK32APLL_WRAP_CTRL0_clk_sel3                       0x00000080
    ///////////////////////////////////////////////////////////
    #define     RA_APLL_WRAP_APLL                              0x0008
    ///////////////////////////////////////////////////////////

    typedef struct SIE_APLL_WRAP {
    ///////////////////////////////////////////////////////////
    #define   GET32APLL_WRAP_APLL_CLK1_CTRL_clkSwitch(r32)     _BFGET_(r32, 0, 0)
    #define   SET32APLL_WRAP_APLL_CLK1_CTRL_clkSwitch(r32, v)   _BFSET_(r32, 0, 0, v)
    #define   GET16APLL_WRAP_APLL_CLK1_CTRL_clkSwitch(r16)     _BFGET_(r16, 0, 0)
    #define   SET16APLL_WRAP_APLL_CLK1_CTRL_clkSwitch(r16, v)   _BFSET_(r16, 0, 0, v)

    #define   GET32APLL_WRAP_APLL_CLK1_CTRL_clkD3Switch(r32)   _BFGET_(r32, 1, 1)
    #define   SET32APLL_WRAP_APLL_CLK1_CTRL_clkD3Switch(r32, v) _BFSET_(r32, 1, 1, v)
    #define   GET16APLL_WRAP_APLL_CLK1_CTRL_clkD3Switch(r16)   _BFGET_(r16, 1, 1)
    #define   SET16APLL_WRAP_APLL_CLK1_CTRL_clkD3Switch(r16, v) _BFSET_(r16, 1, 1, v)

    #define   GET32APLL_WRAP_APLL_CLK1_CTRL_clkSel(r32)        _BFGET_(r32, 4, 2)
    #define   SET32APLL_WRAP_APLL_CLK1_CTRL_clkSel(r32, v)      _BFSET_(r32, 4, 2, v)
    #define   GET16APLL_WRAP_APLL_CLK1_CTRL_clkSel(r16)        _BFGET_(r16, 4, 2)
    #define   SET16APLL_WRAP_APLL_CLK1_CTRL_clkSel(r16, v)      _BFSET_(r16, 4, 2, v)

    #define   GET32APLL_WRAP_APLL_CLK1_CTRL_clkEn(r32)         _BFGET_(r32, 5, 5)
    #define   SET32APLL_WRAP_APLL_CLK1_CTRL_clkEn(r32, v)       _BFSET_(r32, 5, 5, v)
    #define   GET16APLL_WRAP_APLL_CLK1_CTRL_clkEn(r16)         _BFGET_(r16, 5, 5)
    #define   SET16APLL_WRAP_APLL_CLK1_CTRL_clkEn(r16, v)       _BFSET_(r16, 5, 5, v)

    #define     w32APLL_WRAP_APLL_CLK1_CTRL                    {\
	    UNSG32 uAPLL_CLK1_CTRL_clkSwitch                   :  1;\
	    UNSG32 uAPLL_CLK1_CTRL_clkD3Switch                 :  1;\
	    UNSG32 uAPLL_CLK1_CTRL_clkSel                      :  3;\
	    UNSG32 uAPLL_CLK1_CTRL_clkEn                       :  1;\
	    UNSG32 RSVDx0_b6                                   : 26;\
	}
    union { UNSG32 u32APLL_WRAP_APLL_CLK1_CTRL;
	    struct w32APLL_WRAP_APLL_CLK1_CTRL;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32APLL_WRAP_CTRL0_clk_sel0(r32)               _BFGET_(r32, 3, 0)
    #define   SET32APLL_WRAP_CTRL0_clk_sel0(r32, v)             _BFSET_(r32, 3, 0, v)
    #define   GET16APLL_WRAP_CTRL0_clk_sel0(r16)               _BFGET_(r16, 3, 0)
    #define   SET16APLL_WRAP_CTRL0_clk_sel0(r16, v)             _BFSET_(r16, 3, 0, v)

    #define   GET32APLL_WRAP_CTRL0_clk_sel1(r32)               _BFGET_(r32, 4, 4)
    #define   SET32APLL_WRAP_CTRL0_clk_sel1(r32, v)             _BFSET_(r32, 4, 4, v)
    #define   GET16APLL_WRAP_CTRL0_clk_sel1(r16)               _BFGET_(r16, 4, 4)
    #define   SET16APLL_WRAP_CTRL0_clk_sel1(r16, v)             _BFSET_(r16, 4, 4, v)

    #define   GET32APLL_WRAP_CTRL0_clk_sel2(r32)               _BFGET_(r32, 6, 5)
    #define   SET32APLL_WRAP_CTRL0_clk_sel2(r32, v)             _BFSET_(r32, 6, 5, v)
    #define   GET16APLL_WRAP_CTRL0_clk_sel2(r16)               _BFGET_(r16, 6, 5)
    #define   SET16APLL_WRAP_CTRL0_clk_sel2(r16, v)             _BFSET_(r16, 6, 5, v)

    #define   GET32APLL_WRAP_CTRL0_clk_sel3(r32)               _BFGET_(r32, 7, 7)
    #define   SET32APLL_WRAP_CTRL0_clk_sel3(r32, v)             _BFSET_(r32, 7, 7, v)
    #define   GET16APLL_WRAP_CTRL0_clk_sel3(r16)               _BFGET_(r16, 7, 7)
    #define   SET16APLL_WRAP_CTRL0_clk_sel3(r16, v)             _BFSET_(r16, 7, 7, v)

    #define     w32APLL_WRAP_CTRL0                             {\
	    UNSG32 uCTRL0_clk_sel0                             :  4;\
	    UNSG32 uCTRL0_clk_sel1                             :  1;\
	    UNSG32 uCTRL0_clk_sel2                             :  2;\
	    UNSG32 uCTRL0_clk_sel3                             :  1;\
	    UNSG32 RSVDx4_b8                                   : 24;\
	}
    union { UNSG32 u32APLL_WRAP_CTRL0;
	    struct w32APLL_WRAP_CTRL0;
	  };
    ///////////////////////////////////////////////////////////
	SIE_abipll                                       ie_APLL;
    ///////////////////////////////////////////////////////////
    } SIE_APLL_WRAP;

    typedef union  T32APLL_WRAP_APLL_CLK1_CTRL {
		UNSG32 u32;
	    struct w32APLL_WRAP_APLL_CLK1_CTRL;
		 } T32APLL_WRAP_APLL_CLK1_CTRL;
    typedef union  T32APLL_WRAP_CTRL0 {
		UNSG32 u32;
	    struct w32APLL_WRAP_CTRL0;
		 } T32APLL_WRAP_CTRL0;
    ///////////////////////////////////////////////////////////

    typedef union  TAPLL_WRAP_APLL_CLK1_CTRL {
		UNSG32 u32[1];
	    struct {
	    struct w32APLL_WRAP_APLL_CLK1_CTRL;
		   };
		 } TAPLL_WRAP_APLL_CLK1_CTRL;
    typedef union  TAPLL_WRAP_CTRL0 {
		UNSG32 u32[1];
	    struct {
	    struct w32APLL_WRAP_CTRL0;
		   };
		 } TAPLL_WRAP_CTRL0;

    ///////////////////////////////////////////////////////////
     SIGN32 APLL_WRAP_drvrd(SIE_APLL_WRAP *p, UNSG32 base, SIGN32 mem, SIGN32 tst);
     SIGN32 APLL_WRAP_drvwr(SIE_APLL_WRAP *p, UNSG32 base, SIGN32 mem, SIGN32 tst, UNSG32 *pcmd);
       void APLL_WRAP_reset(SIE_APLL_WRAP *p);
     SIGN32 APLL_WRAP_cmp(SIE_APLL_WRAP *p, SIE_APLL_WRAP *pie, char *pfx, void *hLOG, SIGN32 mem, SIGN32 tst);
    #define APLL_WRAP_check(p, pie, pfx, hLOG) APLL_WRAP_cmp(p, pie, pfx, (void *)(hLOG), 0, 0)
    #define APLL_WRAP_print(p,    pfx, hLOG) APLL_WRAP_cmp(p, 0,  pfx, (void *)(hLOG), 0, 0)

#endif
//////
/// ENDOFINTERFACE: APLL_WRAP
////////////////////////////////////////////////////////////

//////
///
/// $INTERFACE VPLL_WRAP               biu              (4,4)
///     # # ----------------------------------------------------------
///     @ 0x00000 VPLL_CTRL            (P)
///               ###
///               * Clock controls for VPLL CLK output
///               ###
///               %unsigned 1  clkOSwitch                0x0
///                                    ###
///                                    * 0: use source clock
///                                    * 1: use divided clock (decided by clkD3Switch and clkSel)
///                                    ###
///               %unsigned 1  clkOD3Switch              0x0
///                                    ###
///                                    * 0 : divide factor is decided by clkSwitch and clkSel
///                                    * 1: use divide by 3 clock when clkSwitch = 1
///                                    ###
///               %unsigned 3  clkOSel                   0x0
///                                    ###
///                                    * Use the following divide factor if clkD3Switch=0.
///                                    ###
///                                    : d2                        0x1
///                                    : d4                        0x2
///                                    : d6                        0x3
///                                    : d8                        0x4
///                                    : d12                       0x5
///               %unsigned 1  clkOEn                    0x0
///                                    ###
///                                    * Clock enable for VPLL CLK output.
///                                    * Not used.
///                                    * Clock controls for VPLL CLKO1
///                                    ###
///               %unsigned 1  clkO1Switch               0x0
///                                    ###
///                                    * Not used.
///                                    * 0: use source clock
///                                    * 1: use divided clock (decided by clkD3Switch and clkSel)
///                                    ###
///               %unsigned 1  clkO1D3Switch             0x0
///                                    ###
///                                    * Not used.
///                                    * 0 : divide factor is decided by clkSwitch and clkSel
///                                    * 1: use divide by 3 clock when clkSwitch = 1
///                                    ###
///               %unsigned 3  clkO1Sel                  0x0
///                                    ###
///                                    * Not used.
///                                    * Use the following divide factor if clkD3Switch=0.
///                                    ###
///                                    : d2                        0x1
///                                    : d4                        0x2
///                                    : d6                        0x3
///                                    : d8                        0x4
///                                    : d12                       0x5
///               %unsigned 1  clkO1En                   0x0
///                                    ###
///                                    * Not used.
///                                    * Clock enable for VPLL CLKO1.
///                                    ###
///               %%        20         # Stuffing bits...
///     @ 0x00004                      (P)
///     # 0x00004 VPLL
///               $abipll              VPLL              REG
///                                    ###
///                                    * All the registers for VPLL.
///                                    ###
///     # # ----------------------------------------------------------
/// $ENDOFINTERFACE  # size:      36B, bits:      77b, padding:     0B
////////////////////////////////////////////////////////////
#ifndef h_VPLL_WRAP
#define h_VPLL_WRAP () {}

    #define     RA_VPLL_WRAP_VPLL_CTRL                         0x0000

    #define     BA_VPLL_WRAP_VPLL_CTRL_clkOSwitch              0x0000
    #define     B16VPLL_WRAP_VPLL_CTRL_clkOSwitch              0x0000
    #define   LSb32VPLL_WRAP_VPLL_CTRL_clkOSwitch                 0
    #define   LSb16VPLL_WRAP_VPLL_CTRL_clkOSwitch                 0
    #define       bVPLL_WRAP_VPLL_CTRL_clkOSwitch              1
    #define   MSK32VPLL_WRAP_VPLL_CTRL_clkOSwitch                 0x00000001

    #define     BA_VPLL_WRAP_VPLL_CTRL_clkOD3Switch            0x0000
    #define     B16VPLL_WRAP_VPLL_CTRL_clkOD3Switch            0x0000
    #define   LSb32VPLL_WRAP_VPLL_CTRL_clkOD3Switch               1
    #define   LSb16VPLL_WRAP_VPLL_CTRL_clkOD3Switch               1
    #define       bVPLL_WRAP_VPLL_CTRL_clkOD3Switch            1
    #define   MSK32VPLL_WRAP_VPLL_CTRL_clkOD3Switch               0x00000002

    #define     BA_VPLL_WRAP_VPLL_CTRL_clkOSel                 0x0000
    #define     B16VPLL_WRAP_VPLL_CTRL_clkOSel                 0x0000
    #define   LSb32VPLL_WRAP_VPLL_CTRL_clkOSel                    2
    #define   LSb16VPLL_WRAP_VPLL_CTRL_clkOSel                    2
    #define       bVPLL_WRAP_VPLL_CTRL_clkOSel                 3
    #define   MSK32VPLL_WRAP_VPLL_CTRL_clkOSel                    0x0000001C
    #define        VPLL_WRAP_VPLL_CTRL_clkOSel_d2                           0x1
    #define        VPLL_WRAP_VPLL_CTRL_clkOSel_d4                           0x2
    #define        VPLL_WRAP_VPLL_CTRL_clkOSel_d6                           0x3
    #define        VPLL_WRAP_VPLL_CTRL_clkOSel_d8                           0x4
    #define        VPLL_WRAP_VPLL_CTRL_clkOSel_d12                          0x5

    #define     BA_VPLL_WRAP_VPLL_CTRL_clkOEn                  0x0000
    #define     B16VPLL_WRAP_VPLL_CTRL_clkOEn                  0x0000
    #define   LSb32VPLL_WRAP_VPLL_CTRL_clkOEn                     5
    #define   LSb16VPLL_WRAP_VPLL_CTRL_clkOEn                     5
    #define       bVPLL_WRAP_VPLL_CTRL_clkOEn                  1
    #define   MSK32VPLL_WRAP_VPLL_CTRL_clkOEn                     0x00000020

    #define     BA_VPLL_WRAP_VPLL_CTRL_clkO1Switch             0x0000
    #define     B16VPLL_WRAP_VPLL_CTRL_clkO1Switch             0x0000
    #define   LSb32VPLL_WRAP_VPLL_CTRL_clkO1Switch                6
    #define   LSb16VPLL_WRAP_VPLL_CTRL_clkO1Switch                6
    #define       bVPLL_WRAP_VPLL_CTRL_clkO1Switch             1
    #define   MSK32VPLL_WRAP_VPLL_CTRL_clkO1Switch                0x00000040

    #define     BA_VPLL_WRAP_VPLL_CTRL_clkO1D3Switch           0x0000
    #define     B16VPLL_WRAP_VPLL_CTRL_clkO1D3Switch           0x0000
    #define   LSb32VPLL_WRAP_VPLL_CTRL_clkO1D3Switch              7
    #define   LSb16VPLL_WRAP_VPLL_CTRL_clkO1D3Switch              7
    #define       bVPLL_WRAP_VPLL_CTRL_clkO1D3Switch           1
    #define   MSK32VPLL_WRAP_VPLL_CTRL_clkO1D3Switch              0x00000080

    #define     BA_VPLL_WRAP_VPLL_CTRL_clkO1Sel                0x0001
    #define     B16VPLL_WRAP_VPLL_CTRL_clkO1Sel                0x0000
    #define   LSb32VPLL_WRAP_VPLL_CTRL_clkO1Sel                   8
    #define   LSb16VPLL_WRAP_VPLL_CTRL_clkO1Sel                   8
    #define       bVPLL_WRAP_VPLL_CTRL_clkO1Sel                3
    #define   MSK32VPLL_WRAP_VPLL_CTRL_clkO1Sel                   0x00000700
    #define        VPLL_WRAP_VPLL_CTRL_clkO1Sel_d2                          0x1
    #define        VPLL_WRAP_VPLL_CTRL_clkO1Sel_d4                          0x2
    #define        VPLL_WRAP_VPLL_CTRL_clkO1Sel_d6                          0x3
    #define        VPLL_WRAP_VPLL_CTRL_clkO1Sel_d8                          0x4
    #define        VPLL_WRAP_VPLL_CTRL_clkO1Sel_d12                         0x5

    #define     BA_VPLL_WRAP_VPLL_CTRL_clkO1En                 0x0001
    #define     B16VPLL_WRAP_VPLL_CTRL_clkO1En                 0x0000
    #define   LSb32VPLL_WRAP_VPLL_CTRL_clkO1En                    11
    #define   LSb16VPLL_WRAP_VPLL_CTRL_clkO1En                    11
    #define       bVPLL_WRAP_VPLL_CTRL_clkO1En                 1
    #define   MSK32VPLL_WRAP_VPLL_CTRL_clkO1En                    0x00000800
    ///////////////////////////////////////////////////////////
    #define     RA_VPLL_WRAP_VPLL                              0x0004
    ///////////////////////////////////////////////////////////

    typedef struct SIE_VPLL_WRAP {
    ///////////////////////////////////////////////////////////
    #define   GET32VPLL_WRAP_VPLL_CTRL_clkOSwitch(r32)         _BFGET_(r32, 0, 0)
    #define   SET32VPLL_WRAP_VPLL_CTRL_clkOSwitch(r32, v)       _BFSET_(r32, 0, 0, v)
    #define   GET16VPLL_WRAP_VPLL_CTRL_clkOSwitch(r16)         _BFGET_(r16, 0, 0)
    #define   SET16VPLL_WRAP_VPLL_CTRL_clkOSwitch(r16, v)       _BFSET_(r16, 0, 0, v)

    #define   GET32VPLL_WRAP_VPLL_CTRL_clkOD3Switch(r32)       _BFGET_(r32, 1, 1)
    #define   SET32VPLL_WRAP_VPLL_CTRL_clkOD3Switch(r32, v)     _BFSET_(r32, 1, 1, v)
    #define   GET16VPLL_WRAP_VPLL_CTRL_clkOD3Switch(r16)       _BFGET_(r16, 1, 1)
    #define   SET16VPLL_WRAP_VPLL_CTRL_clkOD3Switch(r16, v)     _BFSET_(r16, 1, 1, v)

    #define   GET32VPLL_WRAP_VPLL_CTRL_clkOSel(r32)            _BFGET_(r32, 4, 2)
    #define   SET32VPLL_WRAP_VPLL_CTRL_clkOSel(r32, v)          _BFSET_(r32, 4, 2, v)
    #define   GET16VPLL_WRAP_VPLL_CTRL_clkOSel(r16)            _BFGET_(r16, 4, 2)
    #define   SET16VPLL_WRAP_VPLL_CTRL_clkOSel(r16, v)          _BFSET_(r16, 4, 2, v)

    #define   GET32VPLL_WRAP_VPLL_CTRL_clkOEn(r32)             _BFGET_(r32, 5, 5)
    #define   SET32VPLL_WRAP_VPLL_CTRL_clkOEn(r32, v)           _BFSET_(r32, 5, 5, v)
    #define   GET16VPLL_WRAP_VPLL_CTRL_clkOEn(r16)             _BFGET_(r16, 5, 5)
    #define   SET16VPLL_WRAP_VPLL_CTRL_clkOEn(r16, v)           _BFSET_(r16, 5, 5, v)

    #define   GET32VPLL_WRAP_VPLL_CTRL_clkO1Switch(r32)        _BFGET_(r32, 6, 6)
    #define   SET32VPLL_WRAP_VPLL_CTRL_clkO1Switch(r32, v)      _BFSET_(r32, 6, 6, v)
    #define   GET16VPLL_WRAP_VPLL_CTRL_clkO1Switch(r16)        _BFGET_(r16, 6, 6)
    #define   SET16VPLL_WRAP_VPLL_CTRL_clkO1Switch(r16, v)      _BFSET_(r16, 6, 6, v)

    #define   GET32VPLL_WRAP_VPLL_CTRL_clkO1D3Switch(r32)      _BFGET_(r32, 7, 7)
    #define   SET32VPLL_WRAP_VPLL_CTRL_clkO1D3Switch(r32, v)    _BFSET_(r32, 7, 7, v)
    #define   GET16VPLL_WRAP_VPLL_CTRL_clkO1D3Switch(r16)      _BFGET_(r16, 7, 7)
    #define   SET16VPLL_WRAP_VPLL_CTRL_clkO1D3Switch(r16, v)    _BFSET_(r16, 7, 7, v)

    #define   GET32VPLL_WRAP_VPLL_CTRL_clkO1Sel(r32)           _BFGET_(r32, 10, 8)
    #define   SET32VPLL_WRAP_VPLL_CTRL_clkO1Sel(r32, v)         _BFSET_(r32, 10, 8, v)
    #define   GET16VPLL_WRAP_VPLL_CTRL_clkO1Sel(r16)           _BFGET_(r16, 10, 8)
    #define   SET16VPLL_WRAP_VPLL_CTRL_clkO1Sel(r16, v)         _BFSET_(r16, 10, 8, v)

    #define   GET32VPLL_WRAP_VPLL_CTRL_clkO1En(r32)            _BFGET_(r32, 11, 11)
    #define   SET32VPLL_WRAP_VPLL_CTRL_clkO1En(r32, v)          _BFSET_(r32, 11, 11, v)
    #define   GET16VPLL_WRAP_VPLL_CTRL_clkO1En(r16)            _BFGET_(r16, 11, 11)
    #define   SET16VPLL_WRAP_VPLL_CTRL_clkO1En(r16, v)          _BFSET_(r16, 11, 11, v)

    #define     w32VPLL_WRAP_VPLL_CTRL                         {\
	    UNSG32 uVPLL_CTRL_clkOSwitch                       :  1;\
	    UNSG32 uVPLL_CTRL_clkOD3Switch                     :  1;\
	    UNSG32 uVPLL_CTRL_clkOSel                          :  3;\
	    UNSG32 uVPLL_CTRL_clkOEn                           :  1;\
	    UNSG32 uVPLL_CTRL_clkO1Switch                      :  1;\
	    UNSG32 uVPLL_CTRL_clkO1D3Switch                    :  1;\
	    UNSG32 uVPLL_CTRL_clkO1Sel                         :  3;\
	    UNSG32 uVPLL_CTRL_clkO1En                          :  1;\
	    UNSG32 RSVDx0_b12                                  : 20;\
	}
    union { UNSG32 u32VPLL_WRAP_VPLL_CTRL;
	    struct w32VPLL_WRAP_VPLL_CTRL;
	  };
    ///////////////////////////////////////////////////////////
	SIE_abipll                                       ie_VPLL;
    ///////////////////////////////////////////////////////////
    } SIE_VPLL_WRAP;

    typedef union  T32VPLL_WRAP_VPLL_CTRL {
		UNSG32 u32;
	    struct w32VPLL_WRAP_VPLL_CTRL;
		 } T32VPLL_WRAP_VPLL_CTRL;
    ///////////////////////////////////////////////////////////

    typedef union  TVPLL_WRAP_VPLL_CTRL {
		UNSG32 u32[1];
	    struct {
	    struct w32VPLL_WRAP_VPLL_CTRL;
		   };
		 } TVPLL_WRAP_VPLL_CTRL;

    ///////////////////////////////////////////////////////////
     SIGN32 VPLL_WRAP_drvrd(SIE_VPLL_WRAP *p, UNSG32 base, SIGN32 mem, SIGN32 tst);
     SIGN32 VPLL_WRAP_drvwr(SIE_VPLL_WRAP *p, UNSG32 base, SIGN32 mem, SIGN32 tst, UNSG32 *pcmd);
       void VPLL_WRAP_reset(SIE_VPLL_WRAP *p);
     SIGN32 VPLL_WRAP_cmp(SIE_VPLL_WRAP *p, SIE_VPLL_WRAP *pie, char *pfx, void *hLOG, SIGN32 mem, SIGN32 tst);
    #define VPLL_WRAP_check(p, pie, pfx, hLOG) VPLL_WRAP_cmp(p, pie, pfx, (void *)(hLOG), 0, 0)
    #define VPLL_WRAP_print(p,    pfx, hLOG) VPLL_WRAP_cmp(p, 0,  pfx, (void *)(hLOG), 0, 0)

#endif
//////
/// ENDOFINTERFACE: VPLL_WRAP
////////////////////////////////////////////////////////////

//////
///
/// $INTERFACE avioGbl                 biu              (4,4)
///     # # ----------------------------------------------------------
///     @ 0x00000                      (R-)
///     # 0x00000 MEMMAP_MIPI
///               $AVIOGBLREG3         MEMMAP_MIPI       MEM
///                                    ###
///                                    * Dummy (8KB) register space for MIPI-DSI
///                                    ###
///     @ 0x02000                      (P)
///     # 0x02000 VPLL0_WRAP
///               $VPLL_WRAP           VPLL0_WRAP        REG
///                                    ###
///                                    * All the registers for VPLL0 wrapper.
///                                    ###
///     @ 0x02024                      (P)
///     # 0x02024 VPLL1_WRAP
///               $VPLL_WRAP           VPLL1_WRAP        REG
///                                    ###
///                                    * All the registers for VPLL1 wrapper.
///                                    ###
///     @ 0x02048                      (P)
///     # 0x02048 APLL0_WRAP
///               $APLL_WRAP           APLL0_WRAP        REG
///                                    ###
///                                    * All the registers for APLL0 wrapper
///                                    ###
///     @ 0x02070                      (P)
///     # 0x02070 APLL1_WRAP
///               $APLL_WRAP           APLL1_WRAP        REG
///                                    ###
///                                    * All the registers for APLL1 wrapper
///                                    ###
///     @ 0x02098                      (P)
///     # 0x02098 AVIO_debug_ctrl
///               $AVIO_debug_ctrl     AVIO_debug_ctrl   REG
///     @ 0x0209C                      (P)
///     # 0x0209C DPHYTX
///               $DPHYTX              DPHYTX            REG
///                                    ###
///                                    * DPHYTX registers
///                                    ###
///     @ 0x020E4 AVPLLA_CLK_EN        (P)
///               %unsigned 6  ctrl                      0x0
///                                    ###
///                                    * Gates the output of APLL0 and APLL1 after divider and before it is passed to any logic.
///                                    * Bit#0 : used for VPLL0
///                                    * Bit#1 : used for VPLL1
///                                    * Bit#2 : used for APLL0 PLLOUT
///                                    * Bit#3 : used for APLL0 PLLOUTF
///                                    * Bit#4 : used for APLL1 PLLOUT
///                                    * Bit#5 : used for APLL1 PLLOUTF
///                                    * 0: Disable channel output
///                                    * 1: Enable channel output
///                                    * SW should program this bit as 1 after programming the respective APLL channel to make sure that clean clock is passed to the logic.
///                                    ###
///               %unsigned 1  dbg_mux_sel               0x0
///                                    ###
///                                    * *INTERNAL_ONLY**
///                                    * Not used
///                                    * 0: CLKOUT_TSTfrom APLL is connected to Clock Debug pin.
///                                    * 1:CLKOUT_C1 from APLL is connected to Clock Debug pin.
///                                    ###
///               %%        25         # Stuffing bits...
///     @ 0x020E8 SWPDWN_CTRL          (P-)
///               %unsigned 1  VPLL0_PD                  0x1
///                                    ###
///                                    * 1: VPLL0 power down
///                                    * 0: Normal operation
///                                    ###
///               %unsigned 1  VPLL1_PD                  0x1
///                                    ###
///                                    * 1: VPLL1 power down
///                                    * 0: Normal operation
///                                    ###
///               %unsigned 1  APLL0_PD                  0x1
///                                    ###
///                                    * 1: APLL0 power down
///                                    * 0: Normal operation
///                                    ###
///               %unsigned 1  APLL1_PD                  0x1
///                                    ###
///                                    * 1: APLL1 power down
///                                    * 0: Normal operation
///                                    ###
///               %%        28         # Stuffing bits...
///     @ 0x020EC RWTC_31to0           (P)
///               ###
///               * *INTERNAL_ONLY**
///               * Not used
///               * rwtcBus[31:0]
///               ###
///               %unsigned 32 value                     0x999955AA
///                                    ###
///                                    * *INTERNAL_ONLY**
///                                    * Not used
///                                    * RTWC [31:0] value for AVIO internal memories.
///                                    ###
///     @ 0x020F0 RWTC_57to32          (P)
///               ###
///               * *INTERNAL_ONLY**
///               * Not used
///               * rwtcBus[57:32]
///               ###
///               %unsigned 26 value                     0x1555BDE
///                                    ###
///                                    * *INTERNAL_ONLY**
///                                    * Not used
///                                    * RTWC [57:32] value for AVIO internal memories.
///                                    ###
///               %%        6          # Stuffing bits...
///     @ 0x020F4 CTRL                 (P)
///               %unsigned 1  AIODHUB_dyCG_en           0x1
///                                    ###
///                                    * If AIODHUB_CG_en is 1, then this bit is invalid
///                                    * 1: HW will gate the clock dynamically
///                                    * 0: free running clock
///                                    ###
///               %unsigned 1  AIODHUB_CG_en             0x0
///                                    ###
///                                    * 0: clock gating is based on AIODHUB_dyCG_en
///                                    * 1: static clock gating
///                                    ###
///               %unsigned 1  VPPDHUB_dyCG_en           0x1
///                                    ###
///                                    * If VPPDHUB_CG_en is 1, then this bit is invalid
///                                    * 1: HW will gate the clock dynamically
///                                    * 0: free running clock
///                                    ###
///               %unsigned 1  VPPDHUB_CG_en             0x0
///                                    ###
///                                    * 0: clock gating is based on VPPDHUB_dyCG_en
///                                    * 1: static clock gating
///                                    ###
///               %unsigned 4  INTR_EN
///                                    ###
///                                    * Bit:
///                                    * [0]: enable for SPDIF-RX Interrupt
///                                    * [1]: enable for SPDIF-RX CHOVR Interrupt
///                                    * [2]: enable for SPDIF-RX FPLL Lock Interrupt
///                                    * [3]: enable for BCM invalid request interrupt
///                                    ###
///               %unsigned 1  BCM_FIFO_FLUSH            0x0
///                                    ###
///                                    * Flushes OCPF async FIFO between aio64bdhub and BCM.
///                                    ###
///               %unsigned 1  BCMQ_FIFO_FLUSH           0x0
///                                    ###
///                                    * Flushes OCPF async FIFO between aio64bdhub and BCMQ.
///                                    ###
///               %%        22         # Stuffing bits...
///     @ 0x020F8 CTRL0                (P)
///               %unsigned 3  I2S1_MCLK_SEL             0x0
///                                    ###
///                                    * I2S1_MCLK mux selection
///                                    ###
///               %unsigned 3  I2S2_MCLK_SEL             0x0
///                                    ###
///                                    * I2S2_MCLK mux selection
///                                    ###
///               %unsigned 1  i2s1_mclk_inv             0x0
///                                    ###
///                                    * 0: No invert I2S1_MCLK
///                                    * 1: Invert I2S1_MCLK
///                                    ###
///               %unsigned 1  i2s2_mclk_inv             0x0
///                                    ###
///                                    * 0: No invert I2S2_MCLK
///                                    * 1: Invert I2S2_MCLK
///                                    ###
///               %unsigned 1  I2S1_MCLK_OEN             0x0
///                                    ###
///                                    * I2S1_MCLK direction control
///                                    * 0: input
///                                    * 1: output
///                                    ###
///               %unsigned 1  I2S2_MCLK_OEN             0x0
///                                    ###
///                                    * I2S2_MCLK direction control
///                                    * 0: input
///                                    * 1: output
///                                    ###
///               %unsigned 1  PDM_CLK_OEN               0x0
///                                    ###
///                                    * PDM_CLK direction control
///                                    * 0: input
///                                    * 1: output
///                                    ###
///               %unsigned 1  daif_clk_inv              0x0
///                                    ###
///                                    * 0: No invert DAIF_if_clk_if
///                                    * 1: Invert DAIF_if_clk_if
///                                    ###
///               %unsigned 1  dcls_clk_inv              0x0
///                                    ###
///                                    * 0: No invert IF_DCLS_SCLK
///                                    * 1: Invert IF_DCLS_SCLK
///                                    ###
///               %%        19         # Stuffing bits...
///     @ 0x020FC                      (P)
///     # 0x020FC AIO64bDHUB_SRAMPWR
///               $SRAMPWR             AIO64bDHUB_SRAMPWR REG
///                                    ###
///                                    * Power down control registers for AIO64bDhub SRAM.
///                                    ###
///     @ 0x02100                      (P)
///     # 0x02100 VPP128bDHUB_SRAMPWR
///               $SRAMPWR             VPP128bDHUB_SRAMPWR REG
///                                    ###
///                                    * Power down control registers for VPP128bDhub SRAM.
///                                    ###
///     @ 0x02104                      (P)
///     # 0x02104 MIPI_SRAMPWR
///               $SRAMPWR             MIPI_SRAMPWR      REG
///                                    ###
///                                    * Power down control registers for MIPI SRAM.
///                                    ###
///     @ 0x02108                      (P)
///     # 0x02108 SRAMRWTC
///               $SRAMRWTC            SRAMRWTC          REG
///                                    ###
///                                    * RWTC control registers for AVIO SRAM
///                                    ###
///     @ 0x02114                      (P)
///     # 0x02114 GIC_INT0
///               $INT                 GIC_INT0          REG
///                                    ###
///                                    * AVIO Interrupt0 registers
///                                    ###
///     @ 0x0211C                      (P)
///     # 0x0211C GIC_INT1
///               $INT                 GIC_INT1          REG
///                                    ###
///                                    * AVIO Interrupt1 registers
///                                    ###
///     @ 0x02124                      (P)
///     # 0x02124 GIC_INT2
///               $INT                 GIC_INT2          REG
///                                    ###
///                                    * AVIO Interrupt2 registers
///                                    ###
///     @ 0x0212C                      (P)
///     # 0x0212C GIC_INT3
///               $INT                 GIC_INT3          REG
///                                    ###
///                                    * AVIO Interrupt3 registers
///                                    ###
///     @ 0x02134                      (P)
///     # 0x02134 GIC_INT4
///               $INT                 GIC_INT4          REG
///                                    ###
///                                    * AVIO Interrupt4 registers
///                                    ###
///     @ 0x0213C                      (P)
///     # 0x0213C GIC_INT5
///               $INT                 GIC_INT5          REG
///                                    ###
///                                    * AVIO Interrupt5 registers
///                                    ###
///     @ 0x02144                      (P)
///     # 0x02144 GIC_INT6
///               $INT                 GIC_INT6          REG
///                                    ###
///                                    * AVIO Interrupt6 registers
///                                    ###
///     @ 0x0214C                      (P)
///     # 0x0214C GIC_INT7
///               $INT                 GIC_INT7          REG
///                                    ###
///                                    * AVIO Interrupt7 registers
///                                    ###
///     @ 0x02154                      (P)
///     # 0x02154 GIC_INT8
///               $INT                 GIC_INT8          REG
///                                    ###
///                                    * AVIO Interrupt8 registers
///                                    ###
///     @ 0x0215C                      (P)
///     # 0x0215C GIC_INT9
///               $INT                 GIC_INT9          REG
///                                    ###
///                                    * AVIO Interrupt9 registers
///                                    ###
///     @ 0x02164                      (P)
///     # 0x02164 GIC_INT10
///               $INT                 GIC_INT10         REG
///                                    ###
///                                    * AVIO Interrupt10 registers
///                                    ###
///     @ 0x0216C                      (P)
///     # 0x0216C GIC_INT11
///               $INT                 GIC_INT11         REG
///                                    ###
///                                    * AVIO Interrupt11 registers
///                                    ###
///     @ 0x02174                      (P)
///     # 0x02174 GIC_INT12
///               $INT                 GIC_INT12         REG
///                                    ###
///                                    * AVIO Interrupt12 registers
///                                    ###
///     @ 0x0217C                      (P)
///     # 0x0217C GIC_INT13
///               $INT                 GIC_INT13         REG
///                                    ###
///                                    * AVIO Interrupt13 registers
///                                    ###
///     @ 0x02184 GIC_INT              (R-)
///               %unsigned 15 status
///                                    ###
///                                    * Unmasked interrupt status.
///                                    * Bit wise mapping given below
///                                    * 0 : DMIC Port interrupt
///                                    * 1 : Force Mute interrupt
///                                    * 2 : PTRACK1 interrupt
///                                    * 3 : PTRACK2 interrupt
///                                    * 4 : I2S1 sample count interrupt
///                                    * 5 : I2S2 sample count interrupt
///                                    * 6 : I2S3 sample count interrupt
///                                    * 7 : I2S4 sample count interrupt
///                                    * 8 : I2S5 sample count interrupt
///                                    * 9 : DRT sample count interrupt
///                                    * 10 : DCLASS sample count interrupt
///                                    * 11 : PDM sample count interrupt
///                                    * 12 : DMIC sample count interrupt
///                                    * 13 : DCLASS interrupt
///                                    * 14 : DRT interrupt
///                                    ###
///               %%        17         # Stuffing bits...
///     @ 0x02188 INTR_CTRL            (P)
///               %unsigned 1  mipi_int_en               0x0
///                                    ###
///                                    * 0: Disable the interrupt
///                                    * 1: Enable the interrupt
///                                    ###
///               %unsigned 1  ptrack1_int_en            0x0
///                                    ###
///                                    * 0: Disable the interrupt
///                                    * 1: Enable the interrupt
///                                    ###
///               %unsigned 1  ptrack2_int_en            0x0
///                                    ###
///                                    * 0: Disable the interrupt
///                                    * 1: Enable the interrupt
///                                    ###
///               %unsigned 1  lcdc1_int_en              0x0
///                                    ###
///                                    * 0: Disable the interrupt
///                                    * 1: Enable the interrupt
///                                    ###
///               %unsigned 1  lcdc2_int_en              0x0
///                                    ###
///                                    * 0: Disable the interrupt
///                                    * 1: Enable the interrupt
///                                    ###
///               %unsigned 1  daif_int_en               0x0
///                                    ###
///                                    * 0: Disable the interrupt
///                                    * 1: Enable the interrupt
///                                    ###
///               %unsigned 1  daif_pwr_ok_int_en        0x0
///                                    ###
///                                    * 0: Disable the interrupt
///                                    * 1: Enable the interrupt
///                                    ###
///               %unsigned 1  daif_ana_int_en           0x0
///                                    ###
///                                    * 0: Disable the interrupt
///                                    * 1: Enable the interrupt
///                                    ###
///               %unsigned 1  drt_int_en                0x0
///                                    ###
///                                    * 0: Disable the interrupt
///                                    * 1: Enable the interrupt
///                                    ###
///               %unsigned 1  dclass_int_en             0x0
///                                    ###
///                                    * 0: Disable the interrupt
///                                    * 1: Enable the interrupt
///                                    ###
///               %unsigned 1  daif_pwr_ok_gic_int_en    0x0
///                                    ###
///                                    * 0: Disable the interrupt
///                                    * 1: Enable the interrupt
///                                    ###
///               %unsigned 1  daif_pwr_ok_int_pol       0x0
///                                    ###
///                                    * 0: Don’t invert DAIF_if_PWR_OK PAD input
///                                    * 1: Invert DAIF_if_PWR_OK PAD input
///                                    ###
///               %unsigned 1  daif_pwr_ok_int_edge      0x0
///                                    ###
///                                    * 0: interrupt is on posedge
///                                    * 1: interrupt is on both posedge and negedge
///                                    ###
///               %unsigned 1  daif_if_int_ana_pol       0x0
///                                    ###
///                                    * 0: Don’t invert DAIF_if_int_ana PAD input
///                                    * 1: Invert DAIF_if_int_ana PAD input
///                                    ###
///               %%        18         # Stuffing bits...
///     @ 0x0218C INTR_STS             (WOC-)
///               %unsigned 1  gic_daif_pwr_ok_int       0x0
///                                    ###
///                                    * DAIF power good interrupt going to GIC (Global Interrupt Controller)
///                                    ###
///               %%        31         # Stuffing bits...
///     @ 0x02190 DAIF_DRT_CTRL        (P)
///               %unsigned 3  clk_src_sel0              0x0
///                                    ###
///                                    * 0: aPllClkgA3
///                                    * 1: aPllClkgA4
///                                    * 2: DAIF_if_clk_pll_DI
///                                    * 3: I2S1_MCLK
///                                    * 4: aPllClkgA3F
///                                    * 5: aPllClkgA4F
///                                    * 6: DAIF_if_clk_pll_DI
///                                    * 7: I2S2_MCLK
///                                    ###
///               %unsigned 6  div_val1                  0x1
///                                    ###
///                                    * Clock divider division ratio is div_val1
///                                    * Supported values: 1 to 32
///                                    ###
///               %unsigned 4  div_val2                  0x0
///                                    ###
///                                    * Clock divider division ratio is 2**div_val2
///                                    ###
///               %unsigned 1  ClkEn                     0x1
///                                    ###
///                                    * DAIF DRT clock enable.
///                                    ###
///               %unsigned 1  daif_if_clk_inv           0x0
///                                    ###
///                                    * 0: DAIF_if_clk_if after loopback from PAD is not inverted
///                                    * 1: DAIF_if_clk_if after loopback from PAD is inverted
///                                    ###
///               %unsigned 1  drt_clk_sel               0x1
///                                    ###
///                                    * 0: DAIF_if_clk_pll_DI
///                                    * 1: clock selected based on clk_src_sel1
///                                    ###
///               %unsigned 1  drt_clk_en                0x1
///                                    ###
///                                    * Used for drt_clk
///                                    * 0: hardbypass or clock off
///                                    * 1: enable or clock on
///                                    ###
///               %unsigned 1  drt_sysClk_en             0x1
///                                    ###
///                                    * Used for gating sysClk(BIU clock) of DRT
///                                    * 0: hardbypass or clock off
///                                    * 1: enable or clock on
///                                    ###
///               %unsigned 1  daif_clk_en               0x1
///                                    ###
///                                    * Used for daif_clk
///                                    * 0: hardbypass or clock off
///                                    * 1: enable or clock on
///                                    ###
///               %unsigned 1  daif_sysClk_en            0x1
///                                    ###
///                                    * Used for gating sysClk(BIU clock) of DAIF
///                                    * 0: hardbypass or clock off
///                                    * 1: enable or clock on
///                                    ###
///               %%        12         # Stuffing bits...
///     @ 0x02194 DCLS_CTRL            (P)
///               %unsigned 3  clk_src_sel0              0x0
///                                    ###
///                                    * 0: aPllClkgA3
///                                    * 1: aPllClkgA4
///                                    * 2: DAIF_if_clk_pll_DI
///                                    * 3: I2S1_MCLK
///                                    * 4: aPllClkgA3F
///                                    * 5: aPllClkgA4F
///                                    * 6: DAIF_if_clk_pll_DI
///                                    * 7: I2S2_MCLK
///                                    ###
///               %unsigned 6  div_val1                  0x1
///                                    ###
///                                    * Clock divider division ratio is div_val1
///                                    * Supported values: 1 to 32
///                                    ###
///               %unsigned 4  div_val2                  0x0
///                                    ###
///                                    * Clock divider division ratio is 2**div_val2
///                                    ###
///               %unsigned 1  ClkEn                     0x0
///                                    ###
///                                    * DCLASS clock enable.
///                                    ###
///               %unsigned 1  dcls_sclk_inv             0x0
///               %unsigned 1  dcls_sysClk_en            0x0
///                                    ###
///                                    * Used for gating sysClk(BIU clock) of dclass_pwm
///                                    * 0: hardbypass or clock off
///                                    * 1: enable or clock on
///                                    ###
///               %%        16         # Stuffing bits...
///     @ 0x02198 SWRST_CTRL           (P-)
///               %unsigned 1  aioSyncRstn               0x1
///                                    ###
///                                    * Reset for AIO Top.
///                                    * 1: de-assert reset
///                                    * 0: Assert reset
///                                    ###
///               %unsigned 1  dpiSyncRstn               0x1
///                                    ###
///                                    * Reset for DSI Host controller.
///                                    * 1: de-assert reset
///                                    * 0: Assert reset
///                                    ###
///               %unsigned 1  lcdc1SyncRstn             0x1
///                                    ###
///                                    * Reset for LCDC1.
///                                    * 1: de-assert reset
///                                    * 0: Assert reset
///                                    ###
///               %unsigned 1  lcdc1SysSyncRstn          0x1
///                                    ###
///                                    * Reset for LCDC1 BIU.
///                                    * 1: de-assert reset
///                                    * 0: Assert reset
///                                    ###
///               %unsigned 1  lcdc2SyncRstn             0x1
///                                    ###
///                                    * Reset for LCDC2.
///                                    * 1: de-assert reset
///                                    * 0: Assert reset
///                                    ###
///               %unsigned 1  lcdc2SysSyncRstn          0x1
///                                    ###
///                                    * Reset for LCDC2 BIU.
///                                    * 1: de-assert reset
///                                    * 0: Assert reset
///                                    ###
///               %unsigned 1  daifSyncRstn              0x1
///                                    ###
///                                    * Reset for DAIF.
///                                    * 1: de-assert reset
///                                    * 0: Assert reset
///                                    ###
///               %unsigned 1  daif_nares_SyncRstn       0x1
///                                    ###
///                                    * Reset for DAIF.
///                                    * 1: de-assert reset
///                                    * 0: Assert reset
///                                    ###
///               %unsigned 1  daifSysSyncRstn           0x1
///                                    ###
///                                    * Reset for DAIF BIU.
///                                    * 1: de-assert reset
///                                    * 0: Assert reset
///                                    ###
///               %unsigned 1  drtSyncRstn               0x1
///                                    ###
///                                    * Reset for DRT.
///                                    * 1: de-assert reset
///                                    * 0: Assert reset
///                                    ###
///               %unsigned 1  drtSysSyncRstn            0x1
///                                    ###
///                                    * Reset for DRT BIU.
///                                    * 1: de-assert reset
///                                    * 0: Assert reset
///                                    ###
///               %unsigned 1  dclsSyncRstn              0x1
///                                    ###
///                                    * Reset for DCLS.
///                                    * 1: de-assert reset
///                                    * 0: Assert reset
///                                    ###
///               %unsigned 1  dclsSysSyncRstn           0x1
///                                    ###
///                                    * Reset for DCLS BIU.
///                                    * 1: de-assert reset
///                                    * 0: Assert reset
///                                    ###
///               %unsigned 1  ptrack1SysSyncRstn        0x1
///                                    ###
///                                    * Reset for PTRACK1 registers
///                                    * 1: de-assert reset
///                                    * 0: Assert reset
///                                    ###
///               %unsigned 1  ptrack1SyncRstn           0x1
///                                    ###
///                                    * Reset for PTRACK1 control logic
///                                    * 1: de-assert reset
///                                    * 0: Assert reset
///                                    ###
///               %unsigned 1  ptrack2SysSyncRstn        0x1
///                                    ###
///                                    * Reset for PTRACK2 registers
///                                    * 1: de-assert reset
///                                    * 0: Assert reset
///                                    ###
///               %unsigned 1  ptrack2SyncRstn           0x1
///                                    ###
///                                    * Reset for PTRACK2 control logic
///                                    * 1: de-assert reset
///                                    * 0: Assert reset
///                                    ###
///               %%        15         # Stuffing bits...
///     @ 0x0219C LCDC_CTRL            (P)
///               %unsigned 1  lcdc1_clk_sel             0x0
///                                    ###
///                                    * 0: LCDC1 clock is from VPLL0
///                                    * 1: LCDC1 clock is from VPLL1
///                                    ###
///               %unsigned 1  lcdc2_clk_sel             0x0
///                                    ###
///                                    * 0: LCDC2 clock is from VPLL0
///                                    * 1: LCDC2 clock is from VPLL1
///                                    ###
///               %unsigned 3  lcdc1_ClkSel              0x0
///                                    ###
///                                    * Use the following divide factor if clkD3Switch=0.
///                                    * 1: Div2
///                                    * 2: Div4
///                                    * 3: Div6
///                                    * 4: Div8
///                                    * 5: Div12
///                                    ###
///               %unsigned 1  lcdc1_ClkSwitch           0x0
///                                    ###
///                                    * Not used.
///                                    * 0: use source clock
///                                    * 1: use divided clock (decided by clkD3Switch and clkSel)
///                                    ###
///               %unsigned 1  lcdc1_ClkD3Switch         0x0
///                                    ###
///                                    * Not used.
///                                    * 0 : divide factor is decided by clkSwitch and clkSel
///                                    * 1: use divide by 3 clock when clkSwitch = 1
///                                    ###
///               %unsigned 1  lcdc1_ClkEn               0x0
///                                    ###
///                                    * Clock enable for LCDC1.
///                                    ###
///               %unsigned 1  lcdc1_sysClk_en           0x1
///                                    ###
///                                    * Used for gating sysClk(BIU clock) of LCDC1
///                                    * 0: hardbypass or clock off
///                                    * 1: enable or clock on
///                                    ###
///               %unsigned 3  lcdc2_ClkSel              0x0
///                                    ###
///                                    * Use the following divide factor if clkD3Switch=0.
///                                    * 1: Div2
///                                    * 2: Div4
///                                    * 3: Div6
///                                    * 4: Div8
///                                    * 5: Div12
///                                    ###
///               %unsigned 1  lcdc2_ClkSwitch           0x0
///                                    ###
///                                    * Not used.
///                                    * 0: use source clock
///                                    * 1: use divided clock (decided by clkD3Switch and clkSel)
///                                    ###
///               %unsigned 1  lcdc2_ClkD3Switch         0x0
///                                    ###
///                                    * Not used.
///                                    * 0 : divide factor is decided by clkSwitch and clkSel
///                                    * 1: use divide by 3 clock when clkSwitch = 1
///                                    ###
///               %unsigned 1  lcdc2_ClkEn               0x0
///                                    ###
///                                    * Clock enable for LCDC2.
///                                    ###
///               %unsigned 1  lcdc2_sysClk_en           0x1
///                                    ###
///                                    * Used for gating sysClk(BIU clock) of LCDC2
///                                    * 0: hardbypass or clock off
///                                    * 1: enable or clock on
///                                    ###
///               %%        16         # Stuffing bits...
///     @ 0x021A0 LCDC2_CTRL           (P)
///               %unsigned 1  eof_frst_sel              0x0
///                                    ###
///                                    * 0: to select FRST
///                                    * 1: to select EOF (end of frame)
///                                    ###
///               %unsigned 1  tear_sftrst               0x0
///                                    ###
///                                    * Soft reset control to clear tear_wait -timeout
///                                    ###
///               %unsigned 1  clken_ctrl0               0x1
///                                    ###
///                                    * 0: Clock for LCDC2 is controlled using DSI halt, DSI PHY physhutdownz/phyrstz/phystopstateclklane and DSI tear
///                                    * 1: Clock for LCDC2 is free running clock
///                                    ###
///               %unsigned 1  clken_ctrl1               0x0
///                                    ###
///                                    * 0: Clock for LCDC2 is controlled using DSI PHY physhutdownz/phyrstz/phystopstateclklane
///                                    * 1: Clock for LCDC2 is not controlled using DSI PHY physhutdownz/phyrstz/phystopstateclklane
///                                    ###
///               %unsigned 1  clken_ctrl2               0x0
///                                    ###
///                                    * 0: Clock for LCDC2 is controlled using DSI halt
///                                    * 1: Clock for LCDC2 is not controlled using DSI halt
///                                    ###
///               %unsigned 1  clken_ctrl3               0x0
///                                    ###
///                                    * 0: Clock for LCDC2 is controlled using DSI tear
///                                    * 1: Clock for LCDC2 is not controlled using DSI tear
///                                    ###
///               %%        26         # Stuffing bits...
///     @ 0x021A4 PTRACK_CTRL          (P)
///               %unsigned 1  ptrack1_sysClk_en         0x0
///                                    ###
///                                    * Used for gating sysClk(BIU clock) of PTRACK1
///                                    * 0: hardbypass or clock off
///                                    * 1: enable or clock on
///                                    ###
///               %unsigned 1  ptrack1_clk_en            0x0
///                                    ###
///                                    * Used for PTRACK1
///                                    * 0: hardbypass or clock off
///                                    * 1: enable or clock on
///                                    ###
///               %unsigned 1  ptrack2_sysClk_en         0x0
///                                    ###
///                                    * Used for gating sysClk(BIU clock) of PTRACK2
///                                    * 0: hardbypass or clock off
///                                    * 1: enable or clock on
///                                    ###
///               %unsigned 1  ptrack2_clk_en            0x0
///                                    ###
///                                    * Used for PTRACK1
///                                    * 0: hardbypass or clock off
///                                    * 1: enable or clock on
///                                    ###
///               %%        28         # Stuffing bits...
///     @ 0x021A8 MIPI_CTRL            (P)
///               %unsigned 1  mipiClkg_en               0x1
///                                    ###
///                                    * Used for mipiClk
///                                    * 0: hardbypass or clock off
///                                    * 1: enable or clock on
///                                    ###
///               %unsigned 1  mipiSysClkg_en            0x1
///                                    ###
///                                    * Used for mipiSysClk
///                                    * 0: hardbypass or clock off
///                                    * 1: enable or clock on
///                                    ###
///               %unsigned 1  dpidataen_pol             0x0
///                                    ###
///                                    * dpidataen polarity control. Write 1 to make output port dpidataen active-low.
///                                    ###
///               %unsigned 1  dpivsync_pol              0x0
///                                    ###
///                                    * dpivsync polarity control. Write 1 to make output port dpivsync active-low.
///                                    ###
///               %unsigned 1  dpihsync_pol              0x0
///                                    ###
///                                    * dpihsync polarity control. Write 1 to make output port dpihsync active-low.
///                                    ###
///               %unsigned 1  dpishutd_pol              0x0
///                                    ###
///                                    * dpihshutd polarity control. Write 1 to make output port dpishutd active-low.
///                                    ###
///               %unsigned 1  dpicolorm_pol             0x0
///                                    ###
///                                    * dpicolorm polarity control. Write 1 to make output port dpicolorm active-low.
///                                    * ABOVE REGISTER BIT SHOULD ONLY BE CONFIGURED BEFORE DSI HOST + DPHY POWER-UP PROGRAMMING SEQUENCE
///                                    ###
///               %unsigned 1  colormode                 0x0
///                                    ###
///                                    * Control Signal. It is used to switch between normal color and reduced color mode.
///                                    ###
///               %unsigned 1  shutdn                    0x0
///                                    ###
///                                    * Control Signal. It is used to shutdown the display.
///                                    ###
///               %unsigned 1  force_pll_on              0x0
///                                    ###
///                                    * Control signal to pass force pll signal to APLL
///                                    ###
///               %unsigned 1  tear_request_pulse        0x0
///                                    ###
///                                    * activate Tearing Effect
///                                    ###
///               %unsigned 1  updatecfg_pulse           0x0
///                                    ###
///                                    * This signal is used to indicate that the next frame will have new video configuration
///                                    ###
///               %unsigned 1  tear_sftrst               0x0
///                                    ###
///                                    * Soft reset control to clear tear_wait -timeout
///                                    ###
///               %unsigned 1  dsi_te_in_sel             0x0
///                                    ###
///                                    * 0: Select TE from DSI
///                                    * 1: Select TE from PAD
///                                    ###
///               %unsigned 1  dsi_te_in_sense           0x0
///                                    ###
///                                    * 0: Don't invert incoming TE
///                                    * 1: Invert incoming TE
///                                    ###
///               %unsigned 1  dsi_te_enable             0x0
///                                    ###
///                                    * 0: Disable TE
///                                    * 1: Enable TE
///                                    ###
///               %%        16         # Stuffing bits...
///     # 0x021AC MIPI_CTRL1
///               %unsigned 22 dsitedelay                0x0
///                                    ###
///                                    * after falling edge of te, wait for a number of dpiclk cycles and output control signal
///                                    ###
///               %unsigned 1  edpi_mode                 0x0
///                                    ###
///                                    * Control to enable edpi mode for DSI
///                                    ###
///               %%        9          # Stuffing bits...
///     @ 0x021B0 MIPI_CTRL_STS        (R-)
///               %unsigned 1  dsitewait
///               %%        31         # Stuffing bits...
///     @ 0x021B4                      (W-)
///     #         # Stuffing bytes...
///               %% 62048
///     # # ----------------------------------------------------------
/// $ENDOFINTERFACE  # size:   16384B, bits:    1382b, padding:     0B
////////////////////////////////////////////////////////////
#ifndef h_avioGbl
#define h_avioGbl () {}

    #define     RA_avioGbl_MEMMAP_MIPI                         0x0000
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_VPLL0_WRAP                          0x2000
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_VPLL1_WRAP                          0x2024
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_APLL0_WRAP                          0x2048
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_APLL1_WRAP                          0x2070
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_AVIO_debug_ctrl                     0x2098
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_DPHYTX                              0x209C
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_AVPLLA_CLK_EN                       0x20E4

    #define     BA_avioGbl_AVPLLA_CLK_EN_ctrl                  0x20E4
    #define     B16avioGbl_AVPLLA_CLK_EN_ctrl                  0x20E4
    #define   LSb32avioGbl_AVPLLA_CLK_EN_ctrl                     0
    #define   LSb16avioGbl_AVPLLA_CLK_EN_ctrl                     0
    #define       bavioGbl_AVPLLA_CLK_EN_ctrl                  6
    #define   MSK32avioGbl_AVPLLA_CLK_EN_ctrl                     0x0000003F

    #define     BA_avioGbl_AVPLLA_CLK_EN_dbg_mux_sel           0x20E4
    #define     B16avioGbl_AVPLLA_CLK_EN_dbg_mux_sel           0x20E4
    #define   LSb32avioGbl_AVPLLA_CLK_EN_dbg_mux_sel              6
    #define   LSb16avioGbl_AVPLLA_CLK_EN_dbg_mux_sel              6
    #define       bavioGbl_AVPLLA_CLK_EN_dbg_mux_sel           1
    #define   MSK32avioGbl_AVPLLA_CLK_EN_dbg_mux_sel              0x00000040
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_SWPDWN_CTRL                         0x20E8

    #define     BA_avioGbl_SWPDWN_CTRL_VPLL0_PD                0x20E8
    #define     B16avioGbl_SWPDWN_CTRL_VPLL0_PD                0x20E8
    #define   LSb32avioGbl_SWPDWN_CTRL_VPLL0_PD                   0
    #define   LSb16avioGbl_SWPDWN_CTRL_VPLL0_PD                   0
    #define       bavioGbl_SWPDWN_CTRL_VPLL0_PD                1
    #define   MSK32avioGbl_SWPDWN_CTRL_VPLL0_PD                   0x00000001

    #define     BA_avioGbl_SWPDWN_CTRL_VPLL1_PD                0x20E8
    #define     B16avioGbl_SWPDWN_CTRL_VPLL1_PD                0x20E8
    #define   LSb32avioGbl_SWPDWN_CTRL_VPLL1_PD                   1
    #define   LSb16avioGbl_SWPDWN_CTRL_VPLL1_PD                   1
    #define       bavioGbl_SWPDWN_CTRL_VPLL1_PD                1
    #define   MSK32avioGbl_SWPDWN_CTRL_VPLL1_PD                   0x00000002

    #define     BA_avioGbl_SWPDWN_CTRL_APLL0_PD                0x20E8
    #define     B16avioGbl_SWPDWN_CTRL_APLL0_PD                0x20E8
    #define   LSb32avioGbl_SWPDWN_CTRL_APLL0_PD                   2
    #define   LSb16avioGbl_SWPDWN_CTRL_APLL0_PD                   2
    #define       bavioGbl_SWPDWN_CTRL_APLL0_PD                1
    #define   MSK32avioGbl_SWPDWN_CTRL_APLL0_PD                   0x00000004

    #define     BA_avioGbl_SWPDWN_CTRL_APLL1_PD                0x20E8
    #define     B16avioGbl_SWPDWN_CTRL_APLL1_PD                0x20E8
    #define   LSb32avioGbl_SWPDWN_CTRL_APLL1_PD                   3
    #define   LSb16avioGbl_SWPDWN_CTRL_APLL1_PD                   3
    #define       bavioGbl_SWPDWN_CTRL_APLL1_PD                1
    #define   MSK32avioGbl_SWPDWN_CTRL_APLL1_PD                   0x00000008
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_RWTC_31to0                          0x20EC

    #define     BA_avioGbl_RWTC_31to0_value                    0x20EC
    #define     B16avioGbl_RWTC_31to0_value                    0x20EC
    #define   LSb32avioGbl_RWTC_31to0_value                       0
    #define   LSb16avioGbl_RWTC_31to0_value                       0
    #define       bavioGbl_RWTC_31to0_value                    32
    #define   MSK32avioGbl_RWTC_31to0_value                       0xFFFFFFFF
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_RWTC_57to32                         0x20F0

    #define     BA_avioGbl_RWTC_57to32_value                   0x20F0
    #define     B16avioGbl_RWTC_57to32_value                   0x20F0
    #define   LSb32avioGbl_RWTC_57to32_value                      0
    #define   LSb16avioGbl_RWTC_57to32_value                      0
    #define       bavioGbl_RWTC_57to32_value                   26
    #define   MSK32avioGbl_RWTC_57to32_value                      0x03FFFFFF
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_CTRL                                0x20F4

    #define     BA_avioGbl_CTRL_AIODHUB_dyCG_en                0x20F4
    #define     B16avioGbl_CTRL_AIODHUB_dyCG_en                0x20F4
    #define   LSb32avioGbl_CTRL_AIODHUB_dyCG_en                   0
    #define   LSb16avioGbl_CTRL_AIODHUB_dyCG_en                   0
    #define       bavioGbl_CTRL_AIODHUB_dyCG_en                1
    #define   MSK32avioGbl_CTRL_AIODHUB_dyCG_en                   0x00000001

    #define     BA_avioGbl_CTRL_AIODHUB_CG_en                  0x20F4
    #define     B16avioGbl_CTRL_AIODHUB_CG_en                  0x20F4
    #define   LSb32avioGbl_CTRL_AIODHUB_CG_en                     1
    #define   LSb16avioGbl_CTRL_AIODHUB_CG_en                     1
    #define       bavioGbl_CTRL_AIODHUB_CG_en                  1
    #define   MSK32avioGbl_CTRL_AIODHUB_CG_en                     0x00000002

    #define     BA_avioGbl_CTRL_VPPDHUB_dyCG_en                0x20F4
    #define     B16avioGbl_CTRL_VPPDHUB_dyCG_en                0x20F4
    #define   LSb32avioGbl_CTRL_VPPDHUB_dyCG_en                   2
    #define   LSb16avioGbl_CTRL_VPPDHUB_dyCG_en                   2
    #define       bavioGbl_CTRL_VPPDHUB_dyCG_en                1
    #define   MSK32avioGbl_CTRL_VPPDHUB_dyCG_en                   0x00000004

    #define     BA_avioGbl_CTRL_VPPDHUB_CG_en                  0x20F4
    #define     B16avioGbl_CTRL_VPPDHUB_CG_en                  0x20F4
    #define   LSb32avioGbl_CTRL_VPPDHUB_CG_en                     3
    #define   LSb16avioGbl_CTRL_VPPDHUB_CG_en                     3
    #define       bavioGbl_CTRL_VPPDHUB_CG_en                  1
    #define   MSK32avioGbl_CTRL_VPPDHUB_CG_en                     0x00000008

    #define     BA_avioGbl_CTRL_INTR_EN                        0x20F4
    #define     B16avioGbl_CTRL_INTR_EN                        0x20F4
    #define   LSb32avioGbl_CTRL_INTR_EN                           4
    #define   LSb16avioGbl_CTRL_INTR_EN                           4
    #define       bavioGbl_CTRL_INTR_EN                        4
    #define   MSK32avioGbl_CTRL_INTR_EN                           0x000000F0

    #define     BA_avioGbl_CTRL_BCM_FIFO_FLUSH                 0x20F5
    #define     B16avioGbl_CTRL_BCM_FIFO_FLUSH                 0x20F4
    #define   LSb32avioGbl_CTRL_BCM_FIFO_FLUSH                    8
    #define   LSb16avioGbl_CTRL_BCM_FIFO_FLUSH                    8
    #define       bavioGbl_CTRL_BCM_FIFO_FLUSH                 1
    #define   MSK32avioGbl_CTRL_BCM_FIFO_FLUSH                    0x00000100

    #define     BA_avioGbl_CTRL_BCMQ_FIFO_FLUSH                0x20F5
    #define     B16avioGbl_CTRL_BCMQ_FIFO_FLUSH                0x20F4
    #define   LSb32avioGbl_CTRL_BCMQ_FIFO_FLUSH                   9
    #define   LSb16avioGbl_CTRL_BCMQ_FIFO_FLUSH                   9
    #define       bavioGbl_CTRL_BCMQ_FIFO_FLUSH                1
    #define   MSK32avioGbl_CTRL_BCMQ_FIFO_FLUSH                   0x00000200
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_CTRL0                               0x20F8

    #define     BA_avioGbl_CTRL0_I2S1_MCLK_SEL                 0x20F8
    #define     B16avioGbl_CTRL0_I2S1_MCLK_SEL                 0x20F8
    #define   LSb32avioGbl_CTRL0_I2S1_MCLK_SEL                    0
    #define   LSb16avioGbl_CTRL0_I2S1_MCLK_SEL                    0
    #define       bavioGbl_CTRL0_I2S1_MCLK_SEL                 3
    #define   MSK32avioGbl_CTRL0_I2S1_MCLK_SEL                    0x00000007

    #define     BA_avioGbl_CTRL0_I2S2_MCLK_SEL                 0x20F8
    #define     B16avioGbl_CTRL0_I2S2_MCLK_SEL                 0x20F8
    #define   LSb32avioGbl_CTRL0_I2S2_MCLK_SEL                    3
    #define   LSb16avioGbl_CTRL0_I2S2_MCLK_SEL                    3
    #define       bavioGbl_CTRL0_I2S2_MCLK_SEL                 3
    #define   MSK32avioGbl_CTRL0_I2S2_MCLK_SEL                    0x00000038

    #define     BA_avioGbl_CTRL0_i2s1_mclk_inv                 0x20F8
    #define     B16avioGbl_CTRL0_i2s1_mclk_inv                 0x20F8
    #define   LSb32avioGbl_CTRL0_i2s1_mclk_inv                    6
    #define   LSb16avioGbl_CTRL0_i2s1_mclk_inv                    6
    #define       bavioGbl_CTRL0_i2s1_mclk_inv                 1
    #define   MSK32avioGbl_CTRL0_i2s1_mclk_inv                    0x00000040

    #define     BA_avioGbl_CTRL0_i2s2_mclk_inv                 0x20F8
    #define     B16avioGbl_CTRL0_i2s2_mclk_inv                 0x20F8
    #define   LSb32avioGbl_CTRL0_i2s2_mclk_inv                    7
    #define   LSb16avioGbl_CTRL0_i2s2_mclk_inv                    7
    #define       bavioGbl_CTRL0_i2s2_mclk_inv                 1
    #define   MSK32avioGbl_CTRL0_i2s2_mclk_inv                    0x00000080

    #define     BA_avioGbl_CTRL0_I2S1_MCLK_OEN                 0x20F9
    #define     B16avioGbl_CTRL0_I2S1_MCLK_OEN                 0x20F8
    #define   LSb32avioGbl_CTRL0_I2S1_MCLK_OEN                    8
    #define   LSb16avioGbl_CTRL0_I2S1_MCLK_OEN                    8
    #define       bavioGbl_CTRL0_I2S1_MCLK_OEN                 1
    #define   MSK32avioGbl_CTRL0_I2S1_MCLK_OEN                    0x00000100

    #define     BA_avioGbl_CTRL0_I2S2_MCLK_OEN                 0x20F9
    #define     B16avioGbl_CTRL0_I2S2_MCLK_OEN                 0x20F8
    #define   LSb32avioGbl_CTRL0_I2S2_MCLK_OEN                    9
    #define   LSb16avioGbl_CTRL0_I2S2_MCLK_OEN                    9
    #define       bavioGbl_CTRL0_I2S2_MCLK_OEN                 1
    #define   MSK32avioGbl_CTRL0_I2S2_MCLK_OEN                    0x00000200

    #define     BA_avioGbl_CTRL0_PDM_CLK_OEN                   0x20F9
    #define     B16avioGbl_CTRL0_PDM_CLK_OEN                   0x20F8
    #define   LSb32avioGbl_CTRL0_PDM_CLK_OEN                      10
    #define   LSb16avioGbl_CTRL0_PDM_CLK_OEN                      10
    #define       bavioGbl_CTRL0_PDM_CLK_OEN                   1
    #define   MSK32avioGbl_CTRL0_PDM_CLK_OEN                      0x00000400

    #define     BA_avioGbl_CTRL0_daif_clk_inv                  0x20F9
    #define     B16avioGbl_CTRL0_daif_clk_inv                  0x20F8
    #define   LSb32avioGbl_CTRL0_daif_clk_inv                     11
    #define   LSb16avioGbl_CTRL0_daif_clk_inv                     11
    #define       bavioGbl_CTRL0_daif_clk_inv                  1
    #define   MSK32avioGbl_CTRL0_daif_clk_inv                     0x00000800

    #define     BA_avioGbl_CTRL0_dcls_clk_inv                  0x20F9
    #define     B16avioGbl_CTRL0_dcls_clk_inv                  0x20F8
    #define   LSb32avioGbl_CTRL0_dcls_clk_inv                     12
    #define   LSb16avioGbl_CTRL0_dcls_clk_inv                     12
    #define       bavioGbl_CTRL0_dcls_clk_inv                  1
    #define   MSK32avioGbl_CTRL0_dcls_clk_inv                     0x00001000
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_AIO64bDHUB_SRAMPWR                  0x20FC
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_VPP128bDHUB_SRAMPWR                 0x2100
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_MIPI_SRAMPWR                        0x2104
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_SRAMRWTC                            0x2108
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_GIC_INT0                            0x2114
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_GIC_INT1                            0x211C
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_GIC_INT2                            0x2124
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_GIC_INT3                            0x212C
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_GIC_INT4                            0x2134
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_GIC_INT5                            0x213C
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_GIC_INT6                            0x2144
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_GIC_INT7                            0x214C
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_GIC_INT8                            0x2154
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_GIC_INT9                            0x215C
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_GIC_INT10                           0x2164
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_GIC_INT11                           0x216C
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_GIC_INT12                           0x2174
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_GIC_INT13                           0x217C
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_GIC_INT                             0x2184

    #define     BA_avioGbl_GIC_INT_status                      0x2184
    #define     B16avioGbl_GIC_INT_status                      0x2184
    #define   LSb32avioGbl_GIC_INT_status                         0
    #define   LSb16avioGbl_GIC_INT_status                         0
    #define       bavioGbl_GIC_INT_status                      15
    #define   MSK32avioGbl_GIC_INT_status                         0x00007FFF
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_INTR_CTRL                           0x2188

    #define     BA_avioGbl_INTR_CTRL_mipi_int_en               0x2188
    #define     B16avioGbl_INTR_CTRL_mipi_int_en               0x2188
    #define   LSb32avioGbl_INTR_CTRL_mipi_int_en                  0
    #define   LSb16avioGbl_INTR_CTRL_mipi_int_en                  0
    #define       bavioGbl_INTR_CTRL_mipi_int_en               1
    #define   MSK32avioGbl_INTR_CTRL_mipi_int_en                  0x00000001

    #define     BA_avioGbl_INTR_CTRL_ptrack1_int_en            0x2188
    #define     B16avioGbl_INTR_CTRL_ptrack1_int_en            0x2188
    #define   LSb32avioGbl_INTR_CTRL_ptrack1_int_en               1
    #define   LSb16avioGbl_INTR_CTRL_ptrack1_int_en               1
    #define       bavioGbl_INTR_CTRL_ptrack1_int_en            1
    #define   MSK32avioGbl_INTR_CTRL_ptrack1_int_en               0x00000002

    #define     BA_avioGbl_INTR_CTRL_ptrack2_int_en            0x2188
    #define     B16avioGbl_INTR_CTRL_ptrack2_int_en            0x2188
    #define   LSb32avioGbl_INTR_CTRL_ptrack2_int_en               2
    #define   LSb16avioGbl_INTR_CTRL_ptrack2_int_en               2
    #define       bavioGbl_INTR_CTRL_ptrack2_int_en            1
    #define   MSK32avioGbl_INTR_CTRL_ptrack2_int_en               0x00000004

    #define     BA_avioGbl_INTR_CTRL_lcdc1_int_en              0x2188
    #define     B16avioGbl_INTR_CTRL_lcdc1_int_en              0x2188
    #define   LSb32avioGbl_INTR_CTRL_lcdc1_int_en                 3
    #define   LSb16avioGbl_INTR_CTRL_lcdc1_int_en                 3
    #define       bavioGbl_INTR_CTRL_lcdc1_int_en              1
    #define   MSK32avioGbl_INTR_CTRL_lcdc1_int_en                 0x00000008

    #define     BA_avioGbl_INTR_CTRL_lcdc2_int_en              0x2188
    #define     B16avioGbl_INTR_CTRL_lcdc2_int_en              0x2188
    #define   LSb32avioGbl_INTR_CTRL_lcdc2_int_en                 4
    #define   LSb16avioGbl_INTR_CTRL_lcdc2_int_en                 4
    #define       bavioGbl_INTR_CTRL_lcdc2_int_en              1
    #define   MSK32avioGbl_INTR_CTRL_lcdc2_int_en                 0x00000010

    #define     BA_avioGbl_INTR_CTRL_daif_int_en               0x2188
    #define     B16avioGbl_INTR_CTRL_daif_int_en               0x2188
    #define   LSb32avioGbl_INTR_CTRL_daif_int_en                  5
    #define   LSb16avioGbl_INTR_CTRL_daif_int_en                  5
    #define       bavioGbl_INTR_CTRL_daif_int_en               1
    #define   MSK32avioGbl_INTR_CTRL_daif_int_en                  0x00000020

    #define     BA_avioGbl_INTR_CTRL_daif_pwr_ok_int_en        0x2188
    #define     B16avioGbl_INTR_CTRL_daif_pwr_ok_int_en        0x2188
    #define   LSb32avioGbl_INTR_CTRL_daif_pwr_ok_int_en           6
    #define   LSb16avioGbl_INTR_CTRL_daif_pwr_ok_int_en           6
    #define       bavioGbl_INTR_CTRL_daif_pwr_ok_int_en        1
    #define   MSK32avioGbl_INTR_CTRL_daif_pwr_ok_int_en           0x00000040

    #define     BA_avioGbl_INTR_CTRL_daif_ana_int_en           0x2188
    #define     B16avioGbl_INTR_CTRL_daif_ana_int_en           0x2188
    #define   LSb32avioGbl_INTR_CTRL_daif_ana_int_en              7
    #define   LSb16avioGbl_INTR_CTRL_daif_ana_int_en              7
    #define       bavioGbl_INTR_CTRL_daif_ana_int_en           1
    #define   MSK32avioGbl_INTR_CTRL_daif_ana_int_en              0x00000080

    #define     BA_avioGbl_INTR_CTRL_drt_int_en                0x2189
    #define     B16avioGbl_INTR_CTRL_drt_int_en                0x2188
    #define   LSb32avioGbl_INTR_CTRL_drt_int_en                   8
    #define   LSb16avioGbl_INTR_CTRL_drt_int_en                   8
    #define       bavioGbl_INTR_CTRL_drt_int_en                1
    #define   MSK32avioGbl_INTR_CTRL_drt_int_en                   0x00000100

    #define     BA_avioGbl_INTR_CTRL_dclass_int_en             0x2189
    #define     B16avioGbl_INTR_CTRL_dclass_int_en             0x2188
    #define   LSb32avioGbl_INTR_CTRL_dclass_int_en                9
    #define   LSb16avioGbl_INTR_CTRL_dclass_int_en                9
    #define       bavioGbl_INTR_CTRL_dclass_int_en             1
    #define   MSK32avioGbl_INTR_CTRL_dclass_int_en                0x00000200

    #define     BA_avioGbl_INTR_CTRL_daif_pwr_ok_gic_int_en    0x2189
    #define     B16avioGbl_INTR_CTRL_daif_pwr_ok_gic_int_en    0x2188
    #define   LSb32avioGbl_INTR_CTRL_daif_pwr_ok_gic_int_en       10
    #define   LSb16avioGbl_INTR_CTRL_daif_pwr_ok_gic_int_en       10
    #define       bavioGbl_INTR_CTRL_daif_pwr_ok_gic_int_en    1
    #define   MSK32avioGbl_INTR_CTRL_daif_pwr_ok_gic_int_en       0x00000400

    #define     BA_avioGbl_INTR_CTRL_daif_pwr_ok_int_pol       0x2189
    #define     B16avioGbl_INTR_CTRL_daif_pwr_ok_int_pol       0x2188
    #define   LSb32avioGbl_INTR_CTRL_daif_pwr_ok_int_pol          11
    #define   LSb16avioGbl_INTR_CTRL_daif_pwr_ok_int_pol          11
    #define       bavioGbl_INTR_CTRL_daif_pwr_ok_int_pol       1
    #define   MSK32avioGbl_INTR_CTRL_daif_pwr_ok_int_pol          0x00000800

    #define     BA_avioGbl_INTR_CTRL_daif_pwr_ok_int_edge      0x2189
    #define     B16avioGbl_INTR_CTRL_daif_pwr_ok_int_edge      0x2188
    #define   LSb32avioGbl_INTR_CTRL_daif_pwr_ok_int_edge         12
    #define   LSb16avioGbl_INTR_CTRL_daif_pwr_ok_int_edge         12
    #define       bavioGbl_INTR_CTRL_daif_pwr_ok_int_edge      1
    #define   MSK32avioGbl_INTR_CTRL_daif_pwr_ok_int_edge         0x00001000

    #define     BA_avioGbl_INTR_CTRL_daif_if_int_ana_pol       0x2189
    #define     B16avioGbl_INTR_CTRL_daif_if_int_ana_pol       0x2188
    #define   LSb32avioGbl_INTR_CTRL_daif_if_int_ana_pol          13
    #define   LSb16avioGbl_INTR_CTRL_daif_if_int_ana_pol          13
    #define       bavioGbl_INTR_CTRL_daif_if_int_ana_pol       1
    #define   MSK32avioGbl_INTR_CTRL_daif_if_int_ana_pol          0x00002000
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_INTR_STS                            0x218C

    #define     BA_avioGbl_INTR_STS_gic_daif_pwr_ok_int        0x218C
    #define     B16avioGbl_INTR_STS_gic_daif_pwr_ok_int        0x218C
    #define   LSb32avioGbl_INTR_STS_gic_daif_pwr_ok_int           0
    #define   LSb16avioGbl_INTR_STS_gic_daif_pwr_ok_int           0
    #define       bavioGbl_INTR_STS_gic_daif_pwr_ok_int        1
    #define   MSK32avioGbl_INTR_STS_gic_daif_pwr_ok_int           0x00000001
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_DAIF_DRT_CTRL                       0x2190

    #define     BA_avioGbl_DAIF_DRT_CTRL_clk_src_sel0          0x2190
    #define     B16avioGbl_DAIF_DRT_CTRL_clk_src_sel0          0x2190
    #define   LSb32avioGbl_DAIF_DRT_CTRL_clk_src_sel0             0
    #define   LSb16avioGbl_DAIF_DRT_CTRL_clk_src_sel0             0
    #define       bavioGbl_DAIF_DRT_CTRL_clk_src_sel0          3
    #define   MSK32avioGbl_DAIF_DRT_CTRL_clk_src_sel0             0x00000007

    #define     BA_avioGbl_DAIF_DRT_CTRL_div_val1              0x2190
    #define     B16avioGbl_DAIF_DRT_CTRL_div_val1              0x2190
    #define   LSb32avioGbl_DAIF_DRT_CTRL_div_val1                 3
    #define   LSb16avioGbl_DAIF_DRT_CTRL_div_val1                 3
    #define       bavioGbl_DAIF_DRT_CTRL_div_val1              6
    #define   MSK32avioGbl_DAIF_DRT_CTRL_div_val1                 0x000001F8

    #define     BA_avioGbl_DAIF_DRT_CTRL_div_val2              0x2191
    #define     B16avioGbl_DAIF_DRT_CTRL_div_val2              0x2190
    #define   LSb32avioGbl_DAIF_DRT_CTRL_div_val2                 9
    #define   LSb16avioGbl_DAIF_DRT_CTRL_div_val2                 9
    #define       bavioGbl_DAIF_DRT_CTRL_div_val2              4
    #define   MSK32avioGbl_DAIF_DRT_CTRL_div_val2                 0x00001E00

    #define     BA_avioGbl_DAIF_DRT_CTRL_ClkEn                 0x2191
    #define     B16avioGbl_DAIF_DRT_CTRL_ClkEn                 0x2190
    #define   LSb32avioGbl_DAIF_DRT_CTRL_ClkEn                    13
    #define   LSb16avioGbl_DAIF_DRT_CTRL_ClkEn                    13
    #define       bavioGbl_DAIF_DRT_CTRL_ClkEn                 1
    #define   MSK32avioGbl_DAIF_DRT_CTRL_ClkEn                    0x00002000

    #define     BA_avioGbl_DAIF_DRT_CTRL_daif_if_clk_inv       0x2191
    #define     B16avioGbl_DAIF_DRT_CTRL_daif_if_clk_inv       0x2190
    #define   LSb32avioGbl_DAIF_DRT_CTRL_daif_if_clk_inv          14
    #define   LSb16avioGbl_DAIF_DRT_CTRL_daif_if_clk_inv          14
    #define       bavioGbl_DAIF_DRT_CTRL_daif_if_clk_inv       1
    #define   MSK32avioGbl_DAIF_DRT_CTRL_daif_if_clk_inv          0x00004000

    #define     BA_avioGbl_DAIF_DRT_CTRL_drt_clk_sel           0x2191
    #define     B16avioGbl_DAIF_DRT_CTRL_drt_clk_sel           0x2190
    #define   LSb32avioGbl_DAIF_DRT_CTRL_drt_clk_sel              15
    #define   LSb16avioGbl_DAIF_DRT_CTRL_drt_clk_sel              15
    #define       bavioGbl_DAIF_DRT_CTRL_drt_clk_sel           1
    #define   MSK32avioGbl_DAIF_DRT_CTRL_drt_clk_sel              0x00008000

    #define     BA_avioGbl_DAIF_DRT_CTRL_drt_clk_en            0x2192
    #define     B16avioGbl_DAIF_DRT_CTRL_drt_clk_en            0x2192
    #define   LSb32avioGbl_DAIF_DRT_CTRL_drt_clk_en               16
    #define   LSb16avioGbl_DAIF_DRT_CTRL_drt_clk_en               0
    #define       bavioGbl_DAIF_DRT_CTRL_drt_clk_en            1
    #define   MSK32avioGbl_DAIF_DRT_CTRL_drt_clk_en               0x00010000

    #define     BA_avioGbl_DAIF_DRT_CTRL_drt_sysClk_en         0x2192
    #define     B16avioGbl_DAIF_DRT_CTRL_drt_sysClk_en         0x2192
    #define   LSb32avioGbl_DAIF_DRT_CTRL_drt_sysClk_en            17
    #define   LSb16avioGbl_DAIF_DRT_CTRL_drt_sysClk_en            1
    #define       bavioGbl_DAIF_DRT_CTRL_drt_sysClk_en         1
    #define   MSK32avioGbl_DAIF_DRT_CTRL_drt_sysClk_en            0x00020000

    #define     BA_avioGbl_DAIF_DRT_CTRL_daif_clk_en           0x2192
    #define     B16avioGbl_DAIF_DRT_CTRL_daif_clk_en           0x2192
    #define   LSb32avioGbl_DAIF_DRT_CTRL_daif_clk_en              18
    #define   LSb16avioGbl_DAIF_DRT_CTRL_daif_clk_en              2
    #define       bavioGbl_DAIF_DRT_CTRL_daif_clk_en           1
    #define   MSK32avioGbl_DAIF_DRT_CTRL_daif_clk_en              0x00040000

    #define     BA_avioGbl_DAIF_DRT_CTRL_daif_sysClk_en        0x2192
    #define     B16avioGbl_DAIF_DRT_CTRL_daif_sysClk_en        0x2192
    #define   LSb32avioGbl_DAIF_DRT_CTRL_daif_sysClk_en           19
    #define   LSb16avioGbl_DAIF_DRT_CTRL_daif_sysClk_en           3
    #define       bavioGbl_DAIF_DRT_CTRL_daif_sysClk_en        1
    #define   MSK32avioGbl_DAIF_DRT_CTRL_daif_sysClk_en           0x00080000
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_DCLS_CTRL                           0x2194

    #define     BA_avioGbl_DCLS_CTRL_clk_src_sel0              0x2194
    #define     B16avioGbl_DCLS_CTRL_clk_src_sel0              0x2194
    #define   LSb32avioGbl_DCLS_CTRL_clk_src_sel0                 0
    #define   LSb16avioGbl_DCLS_CTRL_clk_src_sel0                 0
    #define       bavioGbl_DCLS_CTRL_clk_src_sel0              3
    #define   MSK32avioGbl_DCLS_CTRL_clk_src_sel0                 0x00000007

    #define     BA_avioGbl_DCLS_CTRL_div_val1                  0x2194
    #define     B16avioGbl_DCLS_CTRL_div_val1                  0x2194
    #define   LSb32avioGbl_DCLS_CTRL_div_val1                     3
    #define   LSb16avioGbl_DCLS_CTRL_div_val1                     3
    #define       bavioGbl_DCLS_CTRL_div_val1                  6
    #define   MSK32avioGbl_DCLS_CTRL_div_val1                     0x000001F8

    #define     BA_avioGbl_DCLS_CTRL_div_val2                  0x2195
    #define     B16avioGbl_DCLS_CTRL_div_val2                  0x2194
    #define   LSb32avioGbl_DCLS_CTRL_div_val2                     9
    #define   LSb16avioGbl_DCLS_CTRL_div_val2                     9
    #define       bavioGbl_DCLS_CTRL_div_val2                  4
    #define   MSK32avioGbl_DCLS_CTRL_div_val2                     0x00001E00

    #define     BA_avioGbl_DCLS_CTRL_ClkEn                     0x2195
    #define     B16avioGbl_DCLS_CTRL_ClkEn                     0x2194
    #define   LSb32avioGbl_DCLS_CTRL_ClkEn                        13
    #define   LSb16avioGbl_DCLS_CTRL_ClkEn                        13
    #define       bavioGbl_DCLS_CTRL_ClkEn                     1
    #define   MSK32avioGbl_DCLS_CTRL_ClkEn                        0x00002000

    #define     BA_avioGbl_DCLS_CTRL_dcls_sclk_inv             0x2195
    #define     B16avioGbl_DCLS_CTRL_dcls_sclk_inv             0x2194
    #define   LSb32avioGbl_DCLS_CTRL_dcls_sclk_inv                14
    #define   LSb16avioGbl_DCLS_CTRL_dcls_sclk_inv                14
    #define       bavioGbl_DCLS_CTRL_dcls_sclk_inv             1
    #define   MSK32avioGbl_DCLS_CTRL_dcls_sclk_inv                0x00004000

    #define     BA_avioGbl_DCLS_CTRL_dcls_sysClk_en            0x2195
    #define     B16avioGbl_DCLS_CTRL_dcls_sysClk_en            0x2194
    #define   LSb32avioGbl_DCLS_CTRL_dcls_sysClk_en               15
    #define   LSb16avioGbl_DCLS_CTRL_dcls_sysClk_en               15
    #define       bavioGbl_DCLS_CTRL_dcls_sysClk_en            1
    #define   MSK32avioGbl_DCLS_CTRL_dcls_sysClk_en               0x00008000
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_SWRST_CTRL                          0x2198

    #define     BA_avioGbl_SWRST_CTRL_aioSyncRstn              0x2198
    #define     B16avioGbl_SWRST_CTRL_aioSyncRstn              0x2198
    #define   LSb32avioGbl_SWRST_CTRL_aioSyncRstn                 0
    #define   LSb16avioGbl_SWRST_CTRL_aioSyncRstn                 0
    #define       bavioGbl_SWRST_CTRL_aioSyncRstn              1
    #define   MSK32avioGbl_SWRST_CTRL_aioSyncRstn                 0x00000001

    #define     BA_avioGbl_SWRST_CTRL_dpiSyncRstn              0x2198
    #define     B16avioGbl_SWRST_CTRL_dpiSyncRstn              0x2198
    #define   LSb32avioGbl_SWRST_CTRL_dpiSyncRstn                 1
    #define   LSb16avioGbl_SWRST_CTRL_dpiSyncRstn                 1
    #define       bavioGbl_SWRST_CTRL_dpiSyncRstn              1
    #define   MSK32avioGbl_SWRST_CTRL_dpiSyncRstn                 0x00000002

    #define     BA_avioGbl_SWRST_CTRL_lcdc1SyncRstn            0x2198
    #define     B16avioGbl_SWRST_CTRL_lcdc1SyncRstn            0x2198
    #define   LSb32avioGbl_SWRST_CTRL_lcdc1SyncRstn               2
    #define   LSb16avioGbl_SWRST_CTRL_lcdc1SyncRstn               2
    #define       bavioGbl_SWRST_CTRL_lcdc1SyncRstn            1
    #define   MSK32avioGbl_SWRST_CTRL_lcdc1SyncRstn               0x00000004

    #define     BA_avioGbl_SWRST_CTRL_lcdc1SysSyncRstn         0x2198
    #define     B16avioGbl_SWRST_CTRL_lcdc1SysSyncRstn         0x2198
    #define   LSb32avioGbl_SWRST_CTRL_lcdc1SysSyncRstn            3
    #define   LSb16avioGbl_SWRST_CTRL_lcdc1SysSyncRstn            3
    #define       bavioGbl_SWRST_CTRL_lcdc1SysSyncRstn         1
    #define   MSK32avioGbl_SWRST_CTRL_lcdc1SysSyncRstn            0x00000008

    #define     BA_avioGbl_SWRST_CTRL_lcdc2SyncRstn            0x2198
    #define     B16avioGbl_SWRST_CTRL_lcdc2SyncRstn            0x2198
    #define   LSb32avioGbl_SWRST_CTRL_lcdc2SyncRstn               4
    #define   LSb16avioGbl_SWRST_CTRL_lcdc2SyncRstn               4
    #define       bavioGbl_SWRST_CTRL_lcdc2SyncRstn            1
    #define   MSK32avioGbl_SWRST_CTRL_lcdc2SyncRstn               0x00000010

    #define     BA_avioGbl_SWRST_CTRL_lcdc2SysSyncRstn         0x2198
    #define     B16avioGbl_SWRST_CTRL_lcdc2SysSyncRstn         0x2198
    #define   LSb32avioGbl_SWRST_CTRL_lcdc2SysSyncRstn            5
    #define   LSb16avioGbl_SWRST_CTRL_lcdc2SysSyncRstn            5
    #define       bavioGbl_SWRST_CTRL_lcdc2SysSyncRstn         1
    #define   MSK32avioGbl_SWRST_CTRL_lcdc2SysSyncRstn            0x00000020

    #define     BA_avioGbl_SWRST_CTRL_daifSyncRstn             0x2198
    #define     B16avioGbl_SWRST_CTRL_daifSyncRstn             0x2198
    #define   LSb32avioGbl_SWRST_CTRL_daifSyncRstn                6
    #define   LSb16avioGbl_SWRST_CTRL_daifSyncRstn                6
    #define       bavioGbl_SWRST_CTRL_daifSyncRstn             1
    #define   MSK32avioGbl_SWRST_CTRL_daifSyncRstn                0x00000040

    #define     BA_avioGbl_SWRST_CTRL_daif_nares_SyncRstn      0x2198
    #define     B16avioGbl_SWRST_CTRL_daif_nares_SyncRstn      0x2198
    #define   LSb32avioGbl_SWRST_CTRL_daif_nares_SyncRstn         7
    #define   LSb16avioGbl_SWRST_CTRL_daif_nares_SyncRstn         7
    #define       bavioGbl_SWRST_CTRL_daif_nares_SyncRstn      1
    #define   MSK32avioGbl_SWRST_CTRL_daif_nares_SyncRstn         0x00000080

    #define     BA_avioGbl_SWRST_CTRL_daifSysSyncRstn          0x2199
    #define     B16avioGbl_SWRST_CTRL_daifSysSyncRstn          0x2198
    #define   LSb32avioGbl_SWRST_CTRL_daifSysSyncRstn             8
    #define   LSb16avioGbl_SWRST_CTRL_daifSysSyncRstn             8
    #define       bavioGbl_SWRST_CTRL_daifSysSyncRstn          1
    #define   MSK32avioGbl_SWRST_CTRL_daifSysSyncRstn             0x00000100

    #define     BA_avioGbl_SWRST_CTRL_drtSyncRstn              0x2199
    #define     B16avioGbl_SWRST_CTRL_drtSyncRstn              0x2198
    #define   LSb32avioGbl_SWRST_CTRL_drtSyncRstn                 9
    #define   LSb16avioGbl_SWRST_CTRL_drtSyncRstn                 9
    #define       bavioGbl_SWRST_CTRL_drtSyncRstn              1
    #define   MSK32avioGbl_SWRST_CTRL_drtSyncRstn                 0x00000200

    #define     BA_avioGbl_SWRST_CTRL_drtSysSyncRstn           0x2199
    #define     B16avioGbl_SWRST_CTRL_drtSysSyncRstn           0x2198
    #define   LSb32avioGbl_SWRST_CTRL_drtSysSyncRstn              10
    #define   LSb16avioGbl_SWRST_CTRL_drtSysSyncRstn              10
    #define       bavioGbl_SWRST_CTRL_drtSysSyncRstn           1
    #define   MSK32avioGbl_SWRST_CTRL_drtSysSyncRstn              0x00000400

    #define     BA_avioGbl_SWRST_CTRL_dclsSyncRstn             0x2199
    #define     B16avioGbl_SWRST_CTRL_dclsSyncRstn             0x2198
    #define   LSb32avioGbl_SWRST_CTRL_dclsSyncRstn                11
    #define   LSb16avioGbl_SWRST_CTRL_dclsSyncRstn                11
    #define       bavioGbl_SWRST_CTRL_dclsSyncRstn             1
    #define   MSK32avioGbl_SWRST_CTRL_dclsSyncRstn                0x00000800

    #define     BA_avioGbl_SWRST_CTRL_dclsSysSyncRstn          0x2199
    #define     B16avioGbl_SWRST_CTRL_dclsSysSyncRstn          0x2198
    #define   LSb32avioGbl_SWRST_CTRL_dclsSysSyncRstn             12
    #define   LSb16avioGbl_SWRST_CTRL_dclsSysSyncRstn             12
    #define       bavioGbl_SWRST_CTRL_dclsSysSyncRstn          1
    #define   MSK32avioGbl_SWRST_CTRL_dclsSysSyncRstn             0x00001000

    #define     BA_avioGbl_SWRST_CTRL_ptrack1SysSyncRstn       0x2199
    #define     B16avioGbl_SWRST_CTRL_ptrack1SysSyncRstn       0x2198
    #define   LSb32avioGbl_SWRST_CTRL_ptrack1SysSyncRstn          13
    #define   LSb16avioGbl_SWRST_CTRL_ptrack1SysSyncRstn          13
    #define       bavioGbl_SWRST_CTRL_ptrack1SysSyncRstn       1
    #define   MSK32avioGbl_SWRST_CTRL_ptrack1SysSyncRstn          0x00002000

    #define     BA_avioGbl_SWRST_CTRL_ptrack1SyncRstn          0x2199
    #define     B16avioGbl_SWRST_CTRL_ptrack1SyncRstn          0x2198
    #define   LSb32avioGbl_SWRST_CTRL_ptrack1SyncRstn             14
    #define   LSb16avioGbl_SWRST_CTRL_ptrack1SyncRstn             14
    #define       bavioGbl_SWRST_CTRL_ptrack1SyncRstn          1
    #define   MSK32avioGbl_SWRST_CTRL_ptrack1SyncRstn             0x00004000

    #define     BA_avioGbl_SWRST_CTRL_ptrack2SysSyncRstn       0x2199
    #define     B16avioGbl_SWRST_CTRL_ptrack2SysSyncRstn       0x2198
    #define   LSb32avioGbl_SWRST_CTRL_ptrack2SysSyncRstn          15
    #define   LSb16avioGbl_SWRST_CTRL_ptrack2SysSyncRstn          15
    #define       bavioGbl_SWRST_CTRL_ptrack2SysSyncRstn       1
    #define   MSK32avioGbl_SWRST_CTRL_ptrack2SysSyncRstn          0x00008000

    #define     BA_avioGbl_SWRST_CTRL_ptrack2SyncRstn          0x219A
    #define     B16avioGbl_SWRST_CTRL_ptrack2SyncRstn          0x219A
    #define   LSb32avioGbl_SWRST_CTRL_ptrack2SyncRstn             16
    #define   LSb16avioGbl_SWRST_CTRL_ptrack2SyncRstn             0
    #define       bavioGbl_SWRST_CTRL_ptrack2SyncRstn          1
    #define   MSK32avioGbl_SWRST_CTRL_ptrack2SyncRstn             0x00010000
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_LCDC_CTRL                           0x219C

    #define     BA_avioGbl_LCDC_CTRL_lcdc1_clk_sel             0x219C
    #define     B16avioGbl_LCDC_CTRL_lcdc1_clk_sel             0x219C
    #define   LSb32avioGbl_LCDC_CTRL_lcdc1_clk_sel                0
    #define   LSb16avioGbl_LCDC_CTRL_lcdc1_clk_sel                0
    #define       bavioGbl_LCDC_CTRL_lcdc1_clk_sel             1
    #define   MSK32avioGbl_LCDC_CTRL_lcdc1_clk_sel                0x00000001

    #define     BA_avioGbl_LCDC_CTRL_lcdc2_clk_sel             0x219C
    #define     B16avioGbl_LCDC_CTRL_lcdc2_clk_sel             0x219C
    #define   LSb32avioGbl_LCDC_CTRL_lcdc2_clk_sel                1
    #define   LSb16avioGbl_LCDC_CTRL_lcdc2_clk_sel                1
    #define       bavioGbl_LCDC_CTRL_lcdc2_clk_sel             1
    #define   MSK32avioGbl_LCDC_CTRL_lcdc2_clk_sel                0x00000002

    #define     BA_avioGbl_LCDC_CTRL_lcdc1_ClkSel              0x219C
    #define     B16avioGbl_LCDC_CTRL_lcdc1_ClkSel              0x219C
    #define   LSb32avioGbl_LCDC_CTRL_lcdc1_ClkSel                 2
    #define   LSb16avioGbl_LCDC_CTRL_lcdc1_ClkSel                 2
    #define       bavioGbl_LCDC_CTRL_lcdc1_ClkSel              3
    #define   MSK32avioGbl_LCDC_CTRL_lcdc1_ClkSel                 0x0000001C

    #define     BA_avioGbl_LCDC_CTRL_lcdc1_ClkSwitch           0x219C
    #define     B16avioGbl_LCDC_CTRL_lcdc1_ClkSwitch           0x219C
    #define   LSb32avioGbl_LCDC_CTRL_lcdc1_ClkSwitch              5
    #define   LSb16avioGbl_LCDC_CTRL_lcdc1_ClkSwitch              5
    #define       bavioGbl_LCDC_CTRL_lcdc1_ClkSwitch           1
    #define   MSK32avioGbl_LCDC_CTRL_lcdc1_ClkSwitch              0x00000020

    #define     BA_avioGbl_LCDC_CTRL_lcdc1_ClkD3Switch         0x219C
    #define     B16avioGbl_LCDC_CTRL_lcdc1_ClkD3Switch         0x219C
    #define   LSb32avioGbl_LCDC_CTRL_lcdc1_ClkD3Switch            6
    #define   LSb16avioGbl_LCDC_CTRL_lcdc1_ClkD3Switch            6
    #define       bavioGbl_LCDC_CTRL_lcdc1_ClkD3Switch         1
    #define   MSK32avioGbl_LCDC_CTRL_lcdc1_ClkD3Switch            0x00000040

    #define     BA_avioGbl_LCDC_CTRL_lcdc1_ClkEn               0x219C
    #define     B16avioGbl_LCDC_CTRL_lcdc1_ClkEn               0x219C
    #define   LSb32avioGbl_LCDC_CTRL_lcdc1_ClkEn                  7
    #define   LSb16avioGbl_LCDC_CTRL_lcdc1_ClkEn                  7
    #define       bavioGbl_LCDC_CTRL_lcdc1_ClkEn               1
    #define   MSK32avioGbl_LCDC_CTRL_lcdc1_ClkEn                  0x00000080

    #define     BA_avioGbl_LCDC_CTRL_lcdc1_sysClk_en           0x219D
    #define     B16avioGbl_LCDC_CTRL_lcdc1_sysClk_en           0x219C
    #define   LSb32avioGbl_LCDC_CTRL_lcdc1_sysClk_en              8
    #define   LSb16avioGbl_LCDC_CTRL_lcdc1_sysClk_en              8
    #define       bavioGbl_LCDC_CTRL_lcdc1_sysClk_en           1
    #define   MSK32avioGbl_LCDC_CTRL_lcdc1_sysClk_en              0x00000100

    #define     BA_avioGbl_LCDC_CTRL_lcdc2_ClkSel              0x219D
    #define     B16avioGbl_LCDC_CTRL_lcdc2_ClkSel              0x219C
    #define   LSb32avioGbl_LCDC_CTRL_lcdc2_ClkSel                 9
    #define   LSb16avioGbl_LCDC_CTRL_lcdc2_ClkSel                 9
    #define       bavioGbl_LCDC_CTRL_lcdc2_ClkSel              3
    #define   MSK32avioGbl_LCDC_CTRL_lcdc2_ClkSel                 0x00000E00

    #define     BA_avioGbl_LCDC_CTRL_lcdc2_ClkSwitch           0x219D
    #define     B16avioGbl_LCDC_CTRL_lcdc2_ClkSwitch           0x219C
    #define   LSb32avioGbl_LCDC_CTRL_lcdc2_ClkSwitch              12
    #define   LSb16avioGbl_LCDC_CTRL_lcdc2_ClkSwitch              12
    #define       bavioGbl_LCDC_CTRL_lcdc2_ClkSwitch           1
    #define   MSK32avioGbl_LCDC_CTRL_lcdc2_ClkSwitch              0x00001000

    #define     BA_avioGbl_LCDC_CTRL_lcdc2_ClkD3Switch         0x219D
    #define     B16avioGbl_LCDC_CTRL_lcdc2_ClkD3Switch         0x219C
    #define   LSb32avioGbl_LCDC_CTRL_lcdc2_ClkD3Switch            13
    #define   LSb16avioGbl_LCDC_CTRL_lcdc2_ClkD3Switch            13
    #define       bavioGbl_LCDC_CTRL_lcdc2_ClkD3Switch         1
    #define   MSK32avioGbl_LCDC_CTRL_lcdc2_ClkD3Switch            0x00002000

    #define     BA_avioGbl_LCDC_CTRL_lcdc2_ClkEn               0x219D
    #define     B16avioGbl_LCDC_CTRL_lcdc2_ClkEn               0x219C
    #define   LSb32avioGbl_LCDC_CTRL_lcdc2_ClkEn                  14
    #define   LSb16avioGbl_LCDC_CTRL_lcdc2_ClkEn                  14
    #define       bavioGbl_LCDC_CTRL_lcdc2_ClkEn               1
    #define   MSK32avioGbl_LCDC_CTRL_lcdc2_ClkEn                  0x00004000

    #define     BA_avioGbl_LCDC_CTRL_lcdc2_sysClk_en           0x219D
    #define     B16avioGbl_LCDC_CTRL_lcdc2_sysClk_en           0x219C
    #define   LSb32avioGbl_LCDC_CTRL_lcdc2_sysClk_en              15
    #define   LSb16avioGbl_LCDC_CTRL_lcdc2_sysClk_en              15
    #define       bavioGbl_LCDC_CTRL_lcdc2_sysClk_en           1
    #define   MSK32avioGbl_LCDC_CTRL_lcdc2_sysClk_en              0x00008000
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_LCDC2_CTRL                          0x21A0

    #define     BA_avioGbl_LCDC2_CTRL_eof_frst_sel             0x21A0
    #define     B16avioGbl_LCDC2_CTRL_eof_frst_sel             0x21A0
    #define   LSb32avioGbl_LCDC2_CTRL_eof_frst_sel                0
    #define   LSb16avioGbl_LCDC2_CTRL_eof_frst_sel                0
    #define       bavioGbl_LCDC2_CTRL_eof_frst_sel             1
    #define   MSK32avioGbl_LCDC2_CTRL_eof_frst_sel                0x00000001

    #define     BA_avioGbl_LCDC2_CTRL_tear_sftrst              0x21A0
    #define     B16avioGbl_LCDC2_CTRL_tear_sftrst              0x21A0
    #define   LSb32avioGbl_LCDC2_CTRL_tear_sftrst                 1
    #define   LSb16avioGbl_LCDC2_CTRL_tear_sftrst                 1
    #define       bavioGbl_LCDC2_CTRL_tear_sftrst              1
    #define   MSK32avioGbl_LCDC2_CTRL_tear_sftrst                 0x00000002

    #define     BA_avioGbl_LCDC2_CTRL_clken_ctrl0              0x21A0
    #define     B16avioGbl_LCDC2_CTRL_clken_ctrl0              0x21A0
    #define   LSb32avioGbl_LCDC2_CTRL_clken_ctrl0                 2
    #define   LSb16avioGbl_LCDC2_CTRL_clken_ctrl0                 2
    #define       bavioGbl_LCDC2_CTRL_clken_ctrl0              1
    #define   MSK32avioGbl_LCDC2_CTRL_clken_ctrl0                 0x00000004

    #define     BA_avioGbl_LCDC2_CTRL_clken_ctrl1              0x21A0
    #define     B16avioGbl_LCDC2_CTRL_clken_ctrl1              0x21A0
    #define   LSb32avioGbl_LCDC2_CTRL_clken_ctrl1                 3
    #define   LSb16avioGbl_LCDC2_CTRL_clken_ctrl1                 3
    #define       bavioGbl_LCDC2_CTRL_clken_ctrl1              1
    #define   MSK32avioGbl_LCDC2_CTRL_clken_ctrl1                 0x00000008

    #define     BA_avioGbl_LCDC2_CTRL_clken_ctrl2              0x21A0
    #define     B16avioGbl_LCDC2_CTRL_clken_ctrl2              0x21A0
    #define   LSb32avioGbl_LCDC2_CTRL_clken_ctrl2                 4
    #define   LSb16avioGbl_LCDC2_CTRL_clken_ctrl2                 4
    #define       bavioGbl_LCDC2_CTRL_clken_ctrl2              1
    #define   MSK32avioGbl_LCDC2_CTRL_clken_ctrl2                 0x00000010

    #define     BA_avioGbl_LCDC2_CTRL_clken_ctrl3              0x21A0
    #define     B16avioGbl_LCDC2_CTRL_clken_ctrl3              0x21A0
    #define   LSb32avioGbl_LCDC2_CTRL_clken_ctrl3                 5
    #define   LSb16avioGbl_LCDC2_CTRL_clken_ctrl3                 5
    #define       bavioGbl_LCDC2_CTRL_clken_ctrl3              1
    #define   MSK32avioGbl_LCDC2_CTRL_clken_ctrl3                 0x00000020
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_PTRACK_CTRL                         0x21A4

    #define     BA_avioGbl_PTRACK_CTRL_ptrack1_sysClk_en       0x21A4
    #define     B16avioGbl_PTRACK_CTRL_ptrack1_sysClk_en       0x21A4
    #define   LSb32avioGbl_PTRACK_CTRL_ptrack1_sysClk_en          0
    #define   LSb16avioGbl_PTRACK_CTRL_ptrack1_sysClk_en          0
    #define       bavioGbl_PTRACK_CTRL_ptrack1_sysClk_en       1
    #define   MSK32avioGbl_PTRACK_CTRL_ptrack1_sysClk_en          0x00000001

    #define     BA_avioGbl_PTRACK_CTRL_ptrack1_clk_en          0x21A4
    #define     B16avioGbl_PTRACK_CTRL_ptrack1_clk_en          0x21A4
    #define   LSb32avioGbl_PTRACK_CTRL_ptrack1_clk_en             1
    #define   LSb16avioGbl_PTRACK_CTRL_ptrack1_clk_en             1
    #define       bavioGbl_PTRACK_CTRL_ptrack1_clk_en          1
    #define   MSK32avioGbl_PTRACK_CTRL_ptrack1_clk_en             0x00000002

    #define     BA_avioGbl_PTRACK_CTRL_ptrack2_sysClk_en       0x21A4
    #define     B16avioGbl_PTRACK_CTRL_ptrack2_sysClk_en       0x21A4
    #define   LSb32avioGbl_PTRACK_CTRL_ptrack2_sysClk_en          2
    #define   LSb16avioGbl_PTRACK_CTRL_ptrack2_sysClk_en          2
    #define       bavioGbl_PTRACK_CTRL_ptrack2_sysClk_en       1
    #define   MSK32avioGbl_PTRACK_CTRL_ptrack2_sysClk_en          0x00000004

    #define     BA_avioGbl_PTRACK_CTRL_ptrack2_clk_en          0x21A4
    #define     B16avioGbl_PTRACK_CTRL_ptrack2_clk_en          0x21A4
    #define   LSb32avioGbl_PTRACK_CTRL_ptrack2_clk_en             3
    #define   LSb16avioGbl_PTRACK_CTRL_ptrack2_clk_en             3
    #define       bavioGbl_PTRACK_CTRL_ptrack2_clk_en          1
    #define   MSK32avioGbl_PTRACK_CTRL_ptrack2_clk_en             0x00000008
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_MIPI_CTRL                           0x21A8

    #define     BA_avioGbl_MIPI_CTRL_mipiClkg_en               0x21A8
    #define     B16avioGbl_MIPI_CTRL_mipiClkg_en               0x21A8
    #define   LSb32avioGbl_MIPI_CTRL_mipiClkg_en                  0
    #define   LSb16avioGbl_MIPI_CTRL_mipiClkg_en                  0
    #define       bavioGbl_MIPI_CTRL_mipiClkg_en               1
    #define   MSK32avioGbl_MIPI_CTRL_mipiClkg_en                  0x00000001

    #define     BA_avioGbl_MIPI_CTRL_mipiSysClkg_en            0x21A8
    #define     B16avioGbl_MIPI_CTRL_mipiSysClkg_en            0x21A8
    #define   LSb32avioGbl_MIPI_CTRL_mipiSysClkg_en               1
    #define   LSb16avioGbl_MIPI_CTRL_mipiSysClkg_en               1
    #define       bavioGbl_MIPI_CTRL_mipiSysClkg_en            1
    #define   MSK32avioGbl_MIPI_CTRL_mipiSysClkg_en               0x00000002

    #define     BA_avioGbl_MIPI_CTRL_dpidataen_pol             0x21A8
    #define     B16avioGbl_MIPI_CTRL_dpidataen_pol             0x21A8
    #define   LSb32avioGbl_MIPI_CTRL_dpidataen_pol                2
    #define   LSb16avioGbl_MIPI_CTRL_dpidataen_pol                2
    #define       bavioGbl_MIPI_CTRL_dpidataen_pol             1
    #define   MSK32avioGbl_MIPI_CTRL_dpidataen_pol                0x00000004

    #define     BA_avioGbl_MIPI_CTRL_dpivsync_pol              0x21A8
    #define     B16avioGbl_MIPI_CTRL_dpivsync_pol              0x21A8
    #define   LSb32avioGbl_MIPI_CTRL_dpivsync_pol                 3
    #define   LSb16avioGbl_MIPI_CTRL_dpivsync_pol                 3
    #define       bavioGbl_MIPI_CTRL_dpivsync_pol              1
    #define   MSK32avioGbl_MIPI_CTRL_dpivsync_pol                 0x00000008

    #define     BA_avioGbl_MIPI_CTRL_dpihsync_pol              0x21A8
    #define     B16avioGbl_MIPI_CTRL_dpihsync_pol              0x21A8
    #define   LSb32avioGbl_MIPI_CTRL_dpihsync_pol                 4
    #define   LSb16avioGbl_MIPI_CTRL_dpihsync_pol                 4
    #define       bavioGbl_MIPI_CTRL_dpihsync_pol              1
    #define   MSK32avioGbl_MIPI_CTRL_dpihsync_pol                 0x00000010

    #define     BA_avioGbl_MIPI_CTRL_dpishutd_pol              0x21A8
    #define     B16avioGbl_MIPI_CTRL_dpishutd_pol              0x21A8
    #define   LSb32avioGbl_MIPI_CTRL_dpishutd_pol                 5
    #define   LSb16avioGbl_MIPI_CTRL_dpishutd_pol                 5
    #define       bavioGbl_MIPI_CTRL_dpishutd_pol              1
    #define   MSK32avioGbl_MIPI_CTRL_dpishutd_pol                 0x00000020

    #define     BA_avioGbl_MIPI_CTRL_dpicolorm_pol             0x21A8
    #define     B16avioGbl_MIPI_CTRL_dpicolorm_pol             0x21A8
    #define   LSb32avioGbl_MIPI_CTRL_dpicolorm_pol                6
    #define   LSb16avioGbl_MIPI_CTRL_dpicolorm_pol                6
    #define       bavioGbl_MIPI_CTRL_dpicolorm_pol             1
    #define   MSK32avioGbl_MIPI_CTRL_dpicolorm_pol                0x00000040

    #define     BA_avioGbl_MIPI_CTRL_colormode                 0x21A8
    #define     B16avioGbl_MIPI_CTRL_colormode                 0x21A8
    #define   LSb32avioGbl_MIPI_CTRL_colormode                    7
    #define   LSb16avioGbl_MIPI_CTRL_colormode                    7
    #define       bavioGbl_MIPI_CTRL_colormode                 1
    #define   MSK32avioGbl_MIPI_CTRL_colormode                    0x00000080

    #define     BA_avioGbl_MIPI_CTRL_shutdn                    0x21A9
    #define     B16avioGbl_MIPI_CTRL_shutdn                    0x21A8
    #define   LSb32avioGbl_MIPI_CTRL_shutdn                       8
    #define   LSb16avioGbl_MIPI_CTRL_shutdn                       8
    #define       bavioGbl_MIPI_CTRL_shutdn                    1
    #define   MSK32avioGbl_MIPI_CTRL_shutdn                       0x00000100

    #define     BA_avioGbl_MIPI_CTRL_force_pll_on              0x21A9
    #define     B16avioGbl_MIPI_CTRL_force_pll_on              0x21A8
    #define   LSb32avioGbl_MIPI_CTRL_force_pll_on                 9
    #define   LSb16avioGbl_MIPI_CTRL_force_pll_on                 9
    #define       bavioGbl_MIPI_CTRL_force_pll_on              1
    #define   MSK32avioGbl_MIPI_CTRL_force_pll_on                 0x00000200

    #define     BA_avioGbl_MIPI_CTRL_tear_request_pulse        0x21A9
    #define     B16avioGbl_MIPI_CTRL_tear_request_pulse        0x21A8
    #define   LSb32avioGbl_MIPI_CTRL_tear_request_pulse           10
    #define   LSb16avioGbl_MIPI_CTRL_tear_request_pulse           10
    #define       bavioGbl_MIPI_CTRL_tear_request_pulse        1
    #define   MSK32avioGbl_MIPI_CTRL_tear_request_pulse           0x00000400

    #define     BA_avioGbl_MIPI_CTRL_updatecfg_pulse           0x21A9
    #define     B16avioGbl_MIPI_CTRL_updatecfg_pulse           0x21A8
    #define   LSb32avioGbl_MIPI_CTRL_updatecfg_pulse              11
    #define   LSb16avioGbl_MIPI_CTRL_updatecfg_pulse              11
    #define       bavioGbl_MIPI_CTRL_updatecfg_pulse           1
    #define   MSK32avioGbl_MIPI_CTRL_updatecfg_pulse              0x00000800

    #define     BA_avioGbl_MIPI_CTRL_tear_sftrst               0x21A9
    #define     B16avioGbl_MIPI_CTRL_tear_sftrst               0x21A8
    #define   LSb32avioGbl_MIPI_CTRL_tear_sftrst                  12
    #define   LSb16avioGbl_MIPI_CTRL_tear_sftrst                  12
    #define       bavioGbl_MIPI_CTRL_tear_sftrst               1
    #define   MSK32avioGbl_MIPI_CTRL_tear_sftrst                  0x00001000

    #define     BA_avioGbl_MIPI_CTRL_dsi_te_in_sel             0x21A9
    #define     B16avioGbl_MIPI_CTRL_dsi_te_in_sel             0x21A8
    #define   LSb32avioGbl_MIPI_CTRL_dsi_te_in_sel                13
    #define   LSb16avioGbl_MIPI_CTRL_dsi_te_in_sel                13
    #define       bavioGbl_MIPI_CTRL_dsi_te_in_sel             1
    #define   MSK32avioGbl_MIPI_CTRL_dsi_te_in_sel                0x00002000

    #define     BA_avioGbl_MIPI_CTRL_dsi_te_in_sense           0x21A9
    #define     B16avioGbl_MIPI_CTRL_dsi_te_in_sense           0x21A8
    #define   LSb32avioGbl_MIPI_CTRL_dsi_te_in_sense              14
    #define   LSb16avioGbl_MIPI_CTRL_dsi_te_in_sense              14
    #define       bavioGbl_MIPI_CTRL_dsi_te_in_sense           1
    #define   MSK32avioGbl_MIPI_CTRL_dsi_te_in_sense              0x00004000

    #define     BA_avioGbl_MIPI_CTRL_dsi_te_enable             0x21A9
    #define     B16avioGbl_MIPI_CTRL_dsi_te_enable             0x21A8
    #define   LSb32avioGbl_MIPI_CTRL_dsi_te_enable                15
    #define   LSb16avioGbl_MIPI_CTRL_dsi_te_enable                15
    #define       bavioGbl_MIPI_CTRL_dsi_te_enable             1
    #define   MSK32avioGbl_MIPI_CTRL_dsi_te_enable                0x00008000

    #define     RA_avioGbl_MIPI_CTRL1                          0x21AC

    #define     BA_avioGbl_MIPI_CTRL_dsitedelay                0x21AC
    #define     B16avioGbl_MIPI_CTRL_dsitedelay                0x21AC
    #define   LSb32avioGbl_MIPI_CTRL_dsitedelay                   0
    #define   LSb16avioGbl_MIPI_CTRL_dsitedelay                   0
    #define       bavioGbl_MIPI_CTRL_dsitedelay                22
    #define   MSK32avioGbl_MIPI_CTRL_dsitedelay                   0x003FFFFF

    #define     BA_avioGbl_MIPI_CTRL_edpi_mode                 0x21AE
    #define     B16avioGbl_MIPI_CTRL_edpi_mode                 0x21AE
    #define   LSb32avioGbl_MIPI_CTRL_edpi_mode                    22
    #define   LSb16avioGbl_MIPI_CTRL_edpi_mode                    6
    #define       bavioGbl_MIPI_CTRL_edpi_mode                 1
    #define   MSK32avioGbl_MIPI_CTRL_edpi_mode                    0x00400000
    ///////////////////////////////////////////////////////////
    #define     RA_avioGbl_MIPI_CTRL_STS                       0x21B0

    #define     BA_avioGbl_MIPI_CTRL_STS_dsitewait             0x21B0
    #define     B16avioGbl_MIPI_CTRL_STS_dsitewait             0x21B0
    #define   LSb32avioGbl_MIPI_CTRL_STS_dsitewait                0
    #define   LSb16avioGbl_MIPI_CTRL_STS_dsitewait                0
    #define       bavioGbl_MIPI_CTRL_STS_dsitewait             1
    #define   MSK32avioGbl_MIPI_CTRL_STS_dsitewait                0x00000001
    ///////////////////////////////////////////////////////////

    typedef struct SIE_avioGbl {
    ///////////////////////////////////////////////////////////
	SIE_AVIOGBLREG3                                  ie_MEMMAP_MIPI;
    ///////////////////////////////////////////////////////////
	SIE_VPLL_WRAP                                    ie_VPLL0_WRAP;
    ///////////////////////////////////////////////////////////
	SIE_VPLL_WRAP                                    ie_VPLL1_WRAP;
    ///////////////////////////////////////////////////////////
	SIE_APLL_WRAP                                    ie_APLL0_WRAP;
    ///////////////////////////////////////////////////////////
	SIE_APLL_WRAP                                    ie_APLL1_WRAP;
    ///////////////////////////////////////////////////////////
	SIE_AVIO_debug_ctrl                              ie_AVIO_debug_ctrl;
    ///////////////////////////////////////////////////////////
	SIE_DPHYTX                                       ie_DPHYTX;
    ///////////////////////////////////////////////////////////
    #define   GET32avioGbl_AVPLLA_CLK_EN_ctrl(r32)             _BFGET_(r32, 5, 0)
    #define   SET32avioGbl_AVPLLA_CLK_EN_ctrl(r32, v)           _BFSET_(r32, 5, 0, v)
    #define   GET16avioGbl_AVPLLA_CLK_EN_ctrl(r16)             _BFGET_(r16, 5, 0)
    #define   SET16avioGbl_AVPLLA_CLK_EN_ctrl(r16, v)           _BFSET_(r16, 5, 0, v)

    #define   GET32avioGbl_AVPLLA_CLK_EN_dbg_mux_sel(r32)      _BFGET_(r32, 6, 6)
    #define   SET32avioGbl_AVPLLA_CLK_EN_dbg_mux_sel(r32, v)    _BFSET_(r32, 6, 6, v)
    #define   GET16avioGbl_AVPLLA_CLK_EN_dbg_mux_sel(r16)      _BFGET_(r16, 6, 6)
    #define   SET16avioGbl_AVPLLA_CLK_EN_dbg_mux_sel(r16, v)    _BFSET_(r16, 6, 6, v)

    #define     w32avioGbl_AVPLLA_CLK_EN                       {\
	    UNSG32 uAVPLLA_CLK_EN_ctrl                         :  6;\
	    UNSG32 uAVPLLA_CLK_EN_dbg_mux_sel                  :  1;\
	    UNSG32 RSVDx20E4_b7                                : 25;\
	}
    union { UNSG32 u32avioGbl_AVPLLA_CLK_EN;
	    struct w32avioGbl_AVPLLA_CLK_EN;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32avioGbl_SWPDWN_CTRL_VPLL0_PD(r32)           _BFGET_(r32, 0, 0)
    #define   SET32avioGbl_SWPDWN_CTRL_VPLL0_PD(r32, v)         _BFSET_(r32, 0, 0, v)
    #define   GET16avioGbl_SWPDWN_CTRL_VPLL0_PD(r16)           _BFGET_(r16, 0, 0)
    #define   SET16avioGbl_SWPDWN_CTRL_VPLL0_PD(r16, v)         _BFSET_(r16, 0, 0, v)

    #define   GET32avioGbl_SWPDWN_CTRL_VPLL1_PD(r32)           _BFGET_(r32, 1, 1)
    #define   SET32avioGbl_SWPDWN_CTRL_VPLL1_PD(r32, v)         _BFSET_(r32, 1, 1, v)
    #define   GET16avioGbl_SWPDWN_CTRL_VPLL1_PD(r16)           _BFGET_(r16, 1, 1)
    #define   SET16avioGbl_SWPDWN_CTRL_VPLL1_PD(r16, v)         _BFSET_(r16, 1, 1, v)

    #define   GET32avioGbl_SWPDWN_CTRL_APLL0_PD(r32)           _BFGET_(r32, 2, 2)
    #define   SET32avioGbl_SWPDWN_CTRL_APLL0_PD(r32, v)         _BFSET_(r32, 2, 2, v)
    #define   GET16avioGbl_SWPDWN_CTRL_APLL0_PD(r16)           _BFGET_(r16, 2, 2)
    #define   SET16avioGbl_SWPDWN_CTRL_APLL0_PD(r16, v)         _BFSET_(r16, 2, 2, v)

    #define   GET32avioGbl_SWPDWN_CTRL_APLL1_PD(r32)           _BFGET_(r32, 3, 3)
    #define   SET32avioGbl_SWPDWN_CTRL_APLL1_PD(r32, v)         _BFSET_(r32, 3, 3, v)
    #define   GET16avioGbl_SWPDWN_CTRL_APLL1_PD(r16)           _BFGET_(r16, 3, 3)
    #define   SET16avioGbl_SWPDWN_CTRL_APLL1_PD(r16, v)         _BFSET_(r16, 3, 3, v)

    #define     w32avioGbl_SWPDWN_CTRL                         {\
	    UNSG32 uSWPDWN_CTRL_VPLL0_PD                       :  1;\
	    UNSG32 uSWPDWN_CTRL_VPLL1_PD                       :  1;\
	    UNSG32 uSWPDWN_CTRL_APLL0_PD                       :  1;\
	    UNSG32 uSWPDWN_CTRL_APLL1_PD                       :  1;\
	    UNSG32 RSVDx20E8_b4                                : 28;\
	}
    union { UNSG32 u32avioGbl_SWPDWN_CTRL;
	    struct w32avioGbl_SWPDWN_CTRL;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32avioGbl_RWTC_31to0_value(r32)               _BFGET_(r32, 31, 0)
    #define   SET32avioGbl_RWTC_31to0_value(r32, v)             _BFSET_(r32, 31, 0, v)

    #define     w32avioGbl_RWTC_31to0                          {\
	    UNSG32 uRWTC_31to0_value                           : 32;\
	}
    union { UNSG32 u32avioGbl_RWTC_31to0;
	    struct w32avioGbl_RWTC_31to0;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32avioGbl_RWTC_57to32_value(r32)              _BFGET_(r32, 25, 0)
    #define   SET32avioGbl_RWTC_57to32_value(r32, v)            _BFSET_(r32, 25, 0, v)

    #define     w32avioGbl_RWTC_57to32                         {\
	    UNSG32 uRWTC_57to32_value                          : 26;\
	    UNSG32 RSVDx20F0_b26                               :  6;\
	}
    union { UNSG32 u32avioGbl_RWTC_57to32;
	    struct w32avioGbl_RWTC_57to32;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32avioGbl_CTRL_AIODHUB_dyCG_en(r32)           _BFGET_(r32, 0, 0)
    #define   SET32avioGbl_CTRL_AIODHUB_dyCG_en(r32, v)         _BFSET_(r32, 0, 0, v)
    #define   GET16avioGbl_CTRL_AIODHUB_dyCG_en(r16)           _BFGET_(r16, 0, 0)
    #define   SET16avioGbl_CTRL_AIODHUB_dyCG_en(r16, v)         _BFSET_(r16, 0, 0, v)

    #define   GET32avioGbl_CTRL_AIODHUB_CG_en(r32)             _BFGET_(r32, 1, 1)
    #define   SET32avioGbl_CTRL_AIODHUB_CG_en(r32, v)           _BFSET_(r32, 1, 1, v)
    #define   GET16avioGbl_CTRL_AIODHUB_CG_en(r16)             _BFGET_(r16, 1, 1)
    #define   SET16avioGbl_CTRL_AIODHUB_CG_en(r16, v)           _BFSET_(r16, 1, 1, v)

    #define   GET32avioGbl_CTRL_VPPDHUB_dyCG_en(r32)           _BFGET_(r32, 2, 2)
    #define   SET32avioGbl_CTRL_VPPDHUB_dyCG_en(r32, v)         _BFSET_(r32, 2, 2, v)
    #define   GET16avioGbl_CTRL_VPPDHUB_dyCG_en(r16)           _BFGET_(r16, 2, 2)
    #define   SET16avioGbl_CTRL_VPPDHUB_dyCG_en(r16, v)         _BFSET_(r16, 2, 2, v)

    #define   GET32avioGbl_CTRL_VPPDHUB_CG_en(r32)             _BFGET_(r32, 3, 3)
    #define   SET32avioGbl_CTRL_VPPDHUB_CG_en(r32, v)           _BFSET_(r32, 3, 3, v)
    #define   GET16avioGbl_CTRL_VPPDHUB_CG_en(r16)             _BFGET_(r16, 3, 3)
    #define   SET16avioGbl_CTRL_VPPDHUB_CG_en(r16, v)           _BFSET_(r16, 3, 3, v)

    #define   GET32avioGbl_CTRL_INTR_EN(r32)                   _BFGET_(r32, 7, 4)
    #define   SET32avioGbl_CTRL_INTR_EN(r32, v)                 _BFSET_(r32, 7, 4, v)
    #define   GET16avioGbl_CTRL_INTR_EN(r16)                   _BFGET_(r16, 7, 4)
    #define   SET16avioGbl_CTRL_INTR_EN(r16, v)                 _BFSET_(r16, 7, 4, v)

    #define   GET32avioGbl_CTRL_BCM_FIFO_FLUSH(r32)            _BFGET_(r32, 8, 8)
    #define   SET32avioGbl_CTRL_BCM_FIFO_FLUSH(r32, v)          _BFSET_(r32, 8, 8, v)
    #define   GET16avioGbl_CTRL_BCM_FIFO_FLUSH(r16)            _BFGET_(r16, 8, 8)
    #define   SET16avioGbl_CTRL_BCM_FIFO_FLUSH(r16, v)          _BFSET_(r16, 8, 8, v)

    #define   GET32avioGbl_CTRL_BCMQ_FIFO_FLUSH(r32)           _BFGET_(r32, 9, 9)
    #define   SET32avioGbl_CTRL_BCMQ_FIFO_FLUSH(r32, v)         _BFSET_(r32, 9, 9, v)
    #define   GET16avioGbl_CTRL_BCMQ_FIFO_FLUSH(r16)           _BFGET_(r16, 9, 9)
    #define   SET16avioGbl_CTRL_BCMQ_FIFO_FLUSH(r16, v)         _BFSET_(r16, 9, 9, v)

    #define     w32avioGbl_CTRL                                {\
	    UNSG32 uCTRL_AIODHUB_dyCG_en                       :  1;\
	    UNSG32 uCTRL_AIODHUB_CG_en                         :  1;\
	    UNSG32 uCTRL_VPPDHUB_dyCG_en                       :  1;\
	    UNSG32 uCTRL_VPPDHUB_CG_en                         :  1;\
	    UNSG32 uCTRL_INTR_EN                               :  4;\
	    UNSG32 uCTRL_BCM_FIFO_FLUSH                        :  1;\
	    UNSG32 uCTRL_BCMQ_FIFO_FLUSH                       :  1;\
	    UNSG32 RSVDx20F4_b10                               : 22;\
	}
    union { UNSG32 u32avioGbl_CTRL;
	    struct w32avioGbl_CTRL;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32avioGbl_CTRL0_I2S1_MCLK_SEL(r32)            _BFGET_(r32, 2, 0)
    #define   SET32avioGbl_CTRL0_I2S1_MCLK_SEL(r32, v)          _BFSET_(r32, 2, 0, v)
    #define   GET16avioGbl_CTRL0_I2S1_MCLK_SEL(r16)            _BFGET_(r16, 2, 0)
    #define   SET16avioGbl_CTRL0_I2S1_MCLK_SEL(r16, v)          _BFSET_(r16, 2, 0, v)

    #define   GET32avioGbl_CTRL0_I2S2_MCLK_SEL(r32)            _BFGET_(r32, 5, 3)
    #define   SET32avioGbl_CTRL0_I2S2_MCLK_SEL(r32, v)          _BFSET_(r32, 5, 3, v)
    #define   GET16avioGbl_CTRL0_I2S2_MCLK_SEL(r16)            _BFGET_(r16, 5, 3)
    #define   SET16avioGbl_CTRL0_I2S2_MCLK_SEL(r16, v)          _BFSET_(r16, 5, 3, v)

    #define   GET32avioGbl_CTRL0_i2s1_mclk_inv(r32)            _BFGET_(r32, 6, 6)
    #define   SET32avioGbl_CTRL0_i2s1_mclk_inv(r32, v)          _BFSET_(r32, 6, 6, v)
    #define   GET16avioGbl_CTRL0_i2s1_mclk_inv(r16)            _BFGET_(r16, 6, 6)
    #define   SET16avioGbl_CTRL0_i2s1_mclk_inv(r16, v)          _BFSET_(r16, 6, 6, v)

    #define   GET32avioGbl_CTRL0_i2s2_mclk_inv(r32)            _BFGET_(r32, 7, 7)
    #define   SET32avioGbl_CTRL0_i2s2_mclk_inv(r32, v)          _BFSET_(r32, 7, 7, v)
    #define   GET16avioGbl_CTRL0_i2s2_mclk_inv(r16)            _BFGET_(r16, 7, 7)
    #define   SET16avioGbl_CTRL0_i2s2_mclk_inv(r16, v)          _BFSET_(r16, 7, 7, v)

    #define   GET32avioGbl_CTRL0_I2S1_MCLK_OEN(r32)            _BFGET_(r32, 8, 8)
    #define   SET32avioGbl_CTRL0_I2S1_MCLK_OEN(r32, v)          _BFSET_(r32, 8, 8, v)
    #define   GET16avioGbl_CTRL0_I2S1_MCLK_OEN(r16)            _BFGET_(r16, 8, 8)
    #define   SET16avioGbl_CTRL0_I2S1_MCLK_OEN(r16, v)          _BFSET_(r16, 8, 8, v)

    #define   GET32avioGbl_CTRL0_I2S2_MCLK_OEN(r32)            _BFGET_(r32, 9, 9)
    #define   SET32avioGbl_CTRL0_I2S2_MCLK_OEN(r32, v)          _BFSET_(r32, 9, 9, v)
    #define   GET16avioGbl_CTRL0_I2S2_MCLK_OEN(r16)            _BFGET_(r16, 9, 9)
    #define   SET16avioGbl_CTRL0_I2S2_MCLK_OEN(r16, v)          _BFSET_(r16, 9, 9, v)

    #define   GET32avioGbl_CTRL0_PDM_CLK_OEN(r32)              _BFGET_(r32, 10, 10)
    #define   SET32avioGbl_CTRL0_PDM_CLK_OEN(r32, v)            _BFSET_(r32, 10, 10, v)
    #define   GET16avioGbl_CTRL0_PDM_CLK_OEN(r16)              _BFGET_(r16, 10, 10)
    #define   SET16avioGbl_CTRL0_PDM_CLK_OEN(r16, v)            _BFSET_(r16, 10, 10, v)

    #define   GET32avioGbl_CTRL0_daif_clk_inv(r32)             _BFGET_(r32, 11, 11)
    #define   SET32avioGbl_CTRL0_daif_clk_inv(r32, v)           _BFSET_(r32, 11, 11, v)
    #define   GET16avioGbl_CTRL0_daif_clk_inv(r16)             _BFGET_(r16, 11, 11)
    #define   SET16avioGbl_CTRL0_daif_clk_inv(r16, v)           _BFSET_(r16, 11, 11, v)

    #define   GET32avioGbl_CTRL0_dcls_clk_inv(r32)             _BFGET_(r32, 12, 12)
    #define   SET32avioGbl_CTRL0_dcls_clk_inv(r32, v)           _BFSET_(r32, 12, 12, v)
    #define   GET16avioGbl_CTRL0_dcls_clk_inv(r16)             _BFGET_(r16, 12, 12)
    #define   SET16avioGbl_CTRL0_dcls_clk_inv(r16, v)           _BFSET_(r16, 12, 12, v)

    #define     w32avioGbl_CTRL0                               {\
	    UNSG32 uCTRL0_I2S1_MCLK_SEL                        :  3;\
	    UNSG32 uCTRL0_I2S2_MCLK_SEL                        :  3;\
	    UNSG32 uCTRL0_i2s1_mclk_inv                        :  1;\
	    UNSG32 uCTRL0_i2s2_mclk_inv                        :  1;\
	    UNSG32 uCTRL0_I2S1_MCLK_OEN                        :  1;\
	    UNSG32 uCTRL0_I2S2_MCLK_OEN                        :  1;\
	    UNSG32 uCTRL0_PDM_CLK_OEN                          :  1;\
	    UNSG32 uCTRL0_daif_clk_inv                         :  1;\
	    UNSG32 uCTRL0_dcls_clk_inv                         :  1;\
	    UNSG32 RSVDx20F8_b13                               : 19;\
	}
    union { UNSG32 u32avioGbl_CTRL0;
	    struct w32avioGbl_CTRL0;
	  };
    ///////////////////////////////////////////////////////////
	SIE_SRAMPWR                                      ie_AIO64bDHUB_SRAMPWR;
    ///////////////////////////////////////////////////////////
	SIE_SRAMPWR                                      ie_VPP128bDHUB_SRAMPWR;
    ///////////////////////////////////////////////////////////
	SIE_SRAMPWR                                      ie_MIPI_SRAMPWR;
    ///////////////////////////////////////////////////////////
	SIE_SRAMRWTC                                     ie_SRAMRWTC;
    ///////////////////////////////////////////////////////////
	SIE_INT                                          ie_GIC_INT0;
    ///////////////////////////////////////////////////////////
	SIE_INT                                          ie_GIC_INT1;
    ///////////////////////////////////////////////////////////
	SIE_INT                                          ie_GIC_INT2;
    ///////////////////////////////////////////////////////////
	SIE_INT                                          ie_GIC_INT3;
    ///////////////////////////////////////////////////////////
	SIE_INT                                          ie_GIC_INT4;
    ///////////////////////////////////////////////////////////
	SIE_INT                                          ie_GIC_INT5;
    ///////////////////////////////////////////////////////////
	SIE_INT                                          ie_GIC_INT6;
    ///////////////////////////////////////////////////////////
	SIE_INT                                          ie_GIC_INT7;
    ///////////////////////////////////////////////////////////
	SIE_INT                                          ie_GIC_INT8;
    ///////////////////////////////////////////////////////////
	SIE_INT                                          ie_GIC_INT9;
    ///////////////////////////////////////////////////////////
	SIE_INT                                          ie_GIC_INT10;
    ///////////////////////////////////////////////////////////
	SIE_INT                                          ie_GIC_INT11;
    ///////////////////////////////////////////////////////////
	SIE_INT                                          ie_GIC_INT12;
    ///////////////////////////////////////////////////////////
	SIE_INT                                          ie_GIC_INT13;
    ///////////////////////////////////////////////////////////
    #define   GET32avioGbl_GIC_INT_status(r32)                 _BFGET_(r32, 14, 0)
    #define   SET32avioGbl_GIC_INT_status(r32, v)               _BFSET_(r32, 14, 0, v)
    #define   GET16avioGbl_GIC_INT_status(r16)                 _BFGET_(r16, 14, 0)
    #define   SET16avioGbl_GIC_INT_status(r16, v)               _BFSET_(r16, 14, 0, v)

    #define     w32avioGbl_GIC_INT                             {\
	    UNSG32 uGIC_INT_status                             : 15;\
	    UNSG32 RSVDx2184_b15                               : 17;\
	}
    union { UNSG32 u32avioGbl_GIC_INT;
	    struct w32avioGbl_GIC_INT;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32avioGbl_INTR_CTRL_mipi_int_en(r32)          _BFGET_(r32, 0, 0)
    #define   SET32avioGbl_INTR_CTRL_mipi_int_en(r32, v)        _BFSET_(r32, 0, 0, v)
    #define   GET16avioGbl_INTR_CTRL_mipi_int_en(r16)          _BFGET_(r16, 0, 0)
    #define   SET16avioGbl_INTR_CTRL_mipi_int_en(r16, v)        _BFSET_(r16, 0, 0, v)

    #define   GET32avioGbl_INTR_CTRL_ptrack1_int_en(r32)       _BFGET_(r32, 1, 1)
    #define   SET32avioGbl_INTR_CTRL_ptrack1_int_en(r32, v)     _BFSET_(r32, 1, 1, v)
    #define   GET16avioGbl_INTR_CTRL_ptrack1_int_en(r16)       _BFGET_(r16, 1, 1)
    #define   SET16avioGbl_INTR_CTRL_ptrack1_int_en(r16, v)     _BFSET_(r16, 1, 1, v)

    #define   GET32avioGbl_INTR_CTRL_ptrack2_int_en(r32)       _BFGET_(r32, 2, 2)
    #define   SET32avioGbl_INTR_CTRL_ptrack2_int_en(r32, v)     _BFSET_(r32, 2, 2, v)
    #define   GET16avioGbl_INTR_CTRL_ptrack2_int_en(r16)       _BFGET_(r16, 2, 2)
    #define   SET16avioGbl_INTR_CTRL_ptrack2_int_en(r16, v)     _BFSET_(r16, 2, 2, v)

    #define   GET32avioGbl_INTR_CTRL_lcdc1_int_en(r32)         _BFGET_(r32, 3, 3)
    #define   SET32avioGbl_INTR_CTRL_lcdc1_int_en(r32, v)       _BFSET_(r32, 3, 3, v)
    #define   GET16avioGbl_INTR_CTRL_lcdc1_int_en(r16)         _BFGET_(r16, 3, 3)
    #define   SET16avioGbl_INTR_CTRL_lcdc1_int_en(r16, v)       _BFSET_(r16, 3, 3, v)

    #define   GET32avioGbl_INTR_CTRL_lcdc2_int_en(r32)         _BFGET_(r32, 4, 4)
    #define   SET32avioGbl_INTR_CTRL_lcdc2_int_en(r32, v)       _BFSET_(r32, 4, 4, v)
    #define   GET16avioGbl_INTR_CTRL_lcdc2_int_en(r16)         _BFGET_(r16, 4, 4)
    #define   SET16avioGbl_INTR_CTRL_lcdc2_int_en(r16, v)       _BFSET_(r16, 4, 4, v)

    #define   GET32avioGbl_INTR_CTRL_daif_int_en(r32)          _BFGET_(r32, 5, 5)
    #define   SET32avioGbl_INTR_CTRL_daif_int_en(r32, v)        _BFSET_(r32, 5, 5, v)
    #define   GET16avioGbl_INTR_CTRL_daif_int_en(r16)          _BFGET_(r16, 5, 5)
    #define   SET16avioGbl_INTR_CTRL_daif_int_en(r16, v)        _BFSET_(r16, 5, 5, v)

    #define   GET32avioGbl_INTR_CTRL_daif_pwr_ok_int_en(r32)   _BFGET_(r32, 6, 6)
    #define   SET32avioGbl_INTR_CTRL_daif_pwr_ok_int_en(r32, v) _BFSET_(r32, 6, 6, v)
    #define   GET16avioGbl_INTR_CTRL_daif_pwr_ok_int_en(r16)   _BFGET_(r16, 6, 6)
    #define   SET16avioGbl_INTR_CTRL_daif_pwr_ok_int_en(r16, v) _BFSET_(r16, 6, 6, v)

    #define   GET32avioGbl_INTR_CTRL_daif_ana_int_en(r32)      _BFGET_(r32, 7, 7)
    #define   SET32avioGbl_INTR_CTRL_daif_ana_int_en(r32, v)    _BFSET_(r32, 7, 7, v)
    #define   GET16avioGbl_INTR_CTRL_daif_ana_int_en(r16)      _BFGET_(r16, 7, 7)
    #define   SET16avioGbl_INTR_CTRL_daif_ana_int_en(r16, v)    _BFSET_(r16, 7, 7, v)

    #define   GET32avioGbl_INTR_CTRL_drt_int_en(r32)           _BFGET_(r32, 8, 8)
    #define   SET32avioGbl_INTR_CTRL_drt_int_en(r32, v)         _BFSET_(r32, 8, 8, v)
    #define   GET16avioGbl_INTR_CTRL_drt_int_en(r16)           _BFGET_(r16, 8, 8)
    #define   SET16avioGbl_INTR_CTRL_drt_int_en(r16, v)         _BFSET_(r16, 8, 8, v)

    #define   GET32avioGbl_INTR_CTRL_dclass_int_en(r32)        _BFGET_(r32, 9, 9)
    #define   SET32avioGbl_INTR_CTRL_dclass_int_en(r32, v)      _BFSET_(r32, 9, 9, v)
    #define   GET16avioGbl_INTR_CTRL_dclass_int_en(r16)        _BFGET_(r16, 9, 9)
    #define   SET16avioGbl_INTR_CTRL_dclass_int_en(r16, v)      _BFSET_(r16, 9, 9, v)

    #define   GET32avioGbl_INTR_CTRL_daif_pwr_ok_gic_int_en(r32) _BFGET_(r32, 10, 10)
    #define   SET32avioGbl_INTR_CTRL_daif_pwr_ok_gic_int_en(r32, v) _BFSET_(r32, 10, 10, v)
    #define   GET16avioGbl_INTR_CTRL_daif_pwr_ok_gic_int_en(r16) _BFGET_(r16, 10, 10)
    #define   SET16avioGbl_INTR_CTRL_daif_pwr_ok_gic_int_en(r16, v) _BFSET_(r16, 10, 10, v)

    #define   GET32avioGbl_INTR_CTRL_daif_pwr_ok_int_pol(r32)  _BFGET_(r32, 11, 11)
    #define   SET32avioGbl_INTR_CTRL_daif_pwr_ok_int_pol(r32, v) _BFSET_(r32, 11, 11, v)
    #define   GET16avioGbl_INTR_CTRL_daif_pwr_ok_int_pol(r16)  _BFGET_(r16, 11, 11)
    #define   SET16avioGbl_INTR_CTRL_daif_pwr_ok_int_pol(r16, v) _BFSET_(r16, 11, 11, v)

    #define   GET32avioGbl_INTR_CTRL_daif_pwr_ok_int_edge(r32) _BFGET_(r32, 12, 12)
    #define   SET32avioGbl_INTR_CTRL_daif_pwr_ok_int_edge(r32, v) _BFSET_(r32, 12, 12, v)
    #define   GET16avioGbl_INTR_CTRL_daif_pwr_ok_int_edge(r16) _BFGET_(r16, 12, 12)
    #define   SET16avioGbl_INTR_CTRL_daif_pwr_ok_int_edge(r16, v) _BFSET_(r16, 12, 12, v)

    #define   GET32avioGbl_INTR_CTRL_daif_if_int_ana_pol(r32)  _BFGET_(r32, 13, 13)
    #define   SET32avioGbl_INTR_CTRL_daif_if_int_ana_pol(r32, v) _BFSET_(r32, 13, 13, v)
    #define   GET16avioGbl_INTR_CTRL_daif_if_int_ana_pol(r16)  _BFGET_(r16, 13, 13)
    #define   SET16avioGbl_INTR_CTRL_daif_if_int_ana_pol(r16, v) _BFSET_(r16, 13, 13, v)

    #define     w32avioGbl_INTR_CTRL                           {\
	    UNSG32 uINTR_CTRL_mipi_int_en                      :  1;\
	    UNSG32 uINTR_CTRL_ptrack1_int_en                   :  1;\
	    UNSG32 uINTR_CTRL_ptrack2_int_en                   :  1;\
	    UNSG32 uINTR_CTRL_lcdc1_int_en                     :  1;\
	    UNSG32 uINTR_CTRL_lcdc2_int_en                     :  1;\
	    UNSG32 uINTR_CTRL_daif_int_en                      :  1;\
	    UNSG32 uINTR_CTRL_daif_pwr_ok_int_en               :  1;\
	    UNSG32 uINTR_CTRL_daif_ana_int_en                  :  1;\
	    UNSG32 uINTR_CTRL_drt_int_en                       :  1;\
	    UNSG32 uINTR_CTRL_dclass_int_en                    :  1;\
	    UNSG32 uINTR_CTRL_daif_pwr_ok_gic_int_en           :  1;\
	    UNSG32 uINTR_CTRL_daif_pwr_ok_int_pol              :  1;\
	    UNSG32 uINTR_CTRL_daif_pwr_ok_int_edge             :  1;\
	    UNSG32 uINTR_CTRL_daif_if_int_ana_pol              :  1;\
	    UNSG32 RSVDx2188_b14                               : 18;\
	}
    union { UNSG32 u32avioGbl_INTR_CTRL;
	    struct w32avioGbl_INTR_CTRL;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32avioGbl_INTR_STS_gic_daif_pwr_ok_int(r32)   _BFGET_(r32, 0, 0)
    #define   SET32avioGbl_INTR_STS_gic_daif_pwr_ok_int(r32, v) _BFSET_(r32, 0, 0, v)
    #define   GET16avioGbl_INTR_STS_gic_daif_pwr_ok_int(r16)   _BFGET_(r16, 0, 0)
    #define   SET16avioGbl_INTR_STS_gic_daif_pwr_ok_int(r16, v) _BFSET_(r16, 0, 0, v)

    #define     w32avioGbl_INTR_STS                            {\
	    UNSG32 uINTR_STS_gic_daif_pwr_ok_int               :  1;\
	    UNSG32 RSVDx218C_b1                                : 31;\
	}
    union { UNSG32 u32avioGbl_INTR_STS;
	    struct w32avioGbl_INTR_STS;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32avioGbl_DAIF_DRT_CTRL_clk_src_sel0(r32)     _BFGET_(r32, 2, 0)
    #define   SET32avioGbl_DAIF_DRT_CTRL_clk_src_sel0(r32, v)   _BFSET_(r32, 2, 0, v)
    #define   GET16avioGbl_DAIF_DRT_CTRL_clk_src_sel0(r16)     _BFGET_(r16, 2, 0)
    #define   SET16avioGbl_DAIF_DRT_CTRL_clk_src_sel0(r16, v)   _BFSET_(r16, 2, 0, v)

    #define   GET32avioGbl_DAIF_DRT_CTRL_div_val1(r32)         _BFGET_(r32, 8, 3)
    #define   SET32avioGbl_DAIF_DRT_CTRL_div_val1(r32, v)       _BFSET_(r32, 8, 3, v)
    #define   GET16avioGbl_DAIF_DRT_CTRL_div_val1(r16)         _BFGET_(r16, 8, 3)
    #define   SET16avioGbl_DAIF_DRT_CTRL_div_val1(r16, v)       _BFSET_(r16, 8, 3, v)

    #define   GET32avioGbl_DAIF_DRT_CTRL_div_val2(r32)         _BFGET_(r32, 12, 9)
    #define   SET32avioGbl_DAIF_DRT_CTRL_div_val2(r32, v)       _BFSET_(r32, 12, 9, v)
    #define   GET16avioGbl_DAIF_DRT_CTRL_div_val2(r16)         _BFGET_(r16, 12, 9)
    #define   SET16avioGbl_DAIF_DRT_CTRL_div_val2(r16, v)       _BFSET_(r16, 12, 9, v)

    #define   GET32avioGbl_DAIF_DRT_CTRL_ClkEn(r32)            _BFGET_(r32, 13, 13)
    #define   SET32avioGbl_DAIF_DRT_CTRL_ClkEn(r32, v)          _BFSET_(r32, 13, 13, v)
    #define   GET16avioGbl_DAIF_DRT_CTRL_ClkEn(r16)            _BFGET_(r16, 13, 13)
    #define   SET16avioGbl_DAIF_DRT_CTRL_ClkEn(r16, v)          _BFSET_(r16, 13, 13, v)

    #define   GET32avioGbl_DAIF_DRT_CTRL_daif_if_clk_inv(r32)  _BFGET_(r32, 14, 14)
    #define   SET32avioGbl_DAIF_DRT_CTRL_daif_if_clk_inv(r32, v) _BFSET_(r32, 14, 14, v)
    #define   GET16avioGbl_DAIF_DRT_CTRL_daif_if_clk_inv(r16)  _BFGET_(r16, 14, 14)
    #define   SET16avioGbl_DAIF_DRT_CTRL_daif_if_clk_inv(r16, v) _BFSET_(r16, 14, 14, v)

    #define   GET32avioGbl_DAIF_DRT_CTRL_drt_clk_sel(r32)      _BFGET_(r32, 15, 15)
    #define   SET32avioGbl_DAIF_DRT_CTRL_drt_clk_sel(r32, v)    _BFSET_(r32, 15, 15, v)
    #define   GET16avioGbl_DAIF_DRT_CTRL_drt_clk_sel(r16)      _BFGET_(r16, 15, 15)
    #define   SET16avioGbl_DAIF_DRT_CTRL_drt_clk_sel(r16, v)    _BFSET_(r16, 15, 15, v)

    #define   GET32avioGbl_DAIF_DRT_CTRL_drt_clk_en(r32)       _BFGET_(r32, 16, 16)
    #define   SET32avioGbl_DAIF_DRT_CTRL_drt_clk_en(r32, v)     _BFSET_(r32, 16, 16, v)
    #define   GET16avioGbl_DAIF_DRT_CTRL_drt_clk_en(r16)       _BFGET_(r16, 0, 0)
    #define   SET16avioGbl_DAIF_DRT_CTRL_drt_clk_en(r16, v)     _BFSET_(r16, 0, 0, v)

    #define   GET32avioGbl_DAIF_DRT_CTRL_drt_sysClk_en(r32)    _BFGET_(r32, 17, 17)
    #define   SET32avioGbl_DAIF_DRT_CTRL_drt_sysClk_en(r32, v)  _BFSET_(r32, 17, 17, v)
    #define   GET16avioGbl_DAIF_DRT_CTRL_drt_sysClk_en(r16)    _BFGET_(r16, 1, 1)
    #define   SET16avioGbl_DAIF_DRT_CTRL_drt_sysClk_en(r16, v)  _BFSET_(r16, 1, 1, v)

    #define   GET32avioGbl_DAIF_DRT_CTRL_daif_clk_en(r32)      _BFGET_(r32, 18, 18)
    #define   SET32avioGbl_DAIF_DRT_CTRL_daif_clk_en(r32, v)    _BFSET_(r32, 18, 18, v)
    #define   GET16avioGbl_DAIF_DRT_CTRL_daif_clk_en(r16)      _BFGET_(r16, 2, 2)
    #define   SET16avioGbl_DAIF_DRT_CTRL_daif_clk_en(r16, v)    _BFSET_(r16, 2, 2, v)

    #define   GET32avioGbl_DAIF_DRT_CTRL_daif_sysClk_en(r32)   _BFGET_(r32, 19, 19)
    #define   SET32avioGbl_DAIF_DRT_CTRL_daif_sysClk_en(r32, v) _BFSET_(r32, 19, 19, v)
    #define   GET16avioGbl_DAIF_DRT_CTRL_daif_sysClk_en(r16)   _BFGET_(r16, 3, 3)
    #define   SET16avioGbl_DAIF_DRT_CTRL_daif_sysClk_en(r16, v) _BFSET_(r16, 3, 3, v)

    #define     w32avioGbl_DAIF_DRT_CTRL                       {\
	    UNSG32 uDAIF_DRT_CTRL_clk_src_sel0                 :  3;\
	    UNSG32 uDAIF_DRT_CTRL_div_val1                     :  6;\
	    UNSG32 uDAIF_DRT_CTRL_div_val2                     :  4;\
	    UNSG32 uDAIF_DRT_CTRL_ClkEn                        :  1;\
	    UNSG32 uDAIF_DRT_CTRL_daif_if_clk_inv              :  1;\
	    UNSG32 uDAIF_DRT_CTRL_drt_clk_sel                  :  1;\
	    UNSG32 uDAIF_DRT_CTRL_drt_clk_en                   :  1;\
	    UNSG32 uDAIF_DRT_CTRL_drt_sysClk_en                :  1;\
	    UNSG32 uDAIF_DRT_CTRL_daif_clk_en                  :  1;\
	    UNSG32 uDAIF_DRT_CTRL_daif_sysClk_en               :  1;\
	    UNSG32 RSVDx2190_b20                               : 12;\
	}
    union { UNSG32 u32avioGbl_DAIF_DRT_CTRL;
	    struct w32avioGbl_DAIF_DRT_CTRL;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32avioGbl_DCLS_CTRL_clk_src_sel0(r32)         _BFGET_(r32, 2, 0)
    #define   SET32avioGbl_DCLS_CTRL_clk_src_sel0(r32, v)       _BFSET_(r32, 2, 0, v)
    #define   GET16avioGbl_DCLS_CTRL_clk_src_sel0(r16)         _BFGET_(r16, 2, 0)
    #define   SET16avioGbl_DCLS_CTRL_clk_src_sel0(r16, v)       _BFSET_(r16, 2, 0, v)

    #define   GET32avioGbl_DCLS_CTRL_div_val1(r32)             _BFGET_(r32, 8, 3)
    #define   SET32avioGbl_DCLS_CTRL_div_val1(r32, v)           _BFSET_(r32, 8, 3, v)
    #define   GET16avioGbl_DCLS_CTRL_div_val1(r16)             _BFGET_(r16, 8, 3)
    #define   SET16avioGbl_DCLS_CTRL_div_val1(r16, v)           _BFSET_(r16, 8, 3, v)

    #define   GET32avioGbl_DCLS_CTRL_div_val2(r32)             _BFGET_(r32, 12, 9)
    #define   SET32avioGbl_DCLS_CTRL_div_val2(r32, v)           _BFSET_(r32, 12, 9, v)
    #define   GET16avioGbl_DCLS_CTRL_div_val2(r16)             _BFGET_(r16, 12, 9)
    #define   SET16avioGbl_DCLS_CTRL_div_val2(r16, v)           _BFSET_(r16, 12, 9, v)

    #define   GET32avioGbl_DCLS_CTRL_ClkEn(r32)                _BFGET_(r32, 13, 13)
    #define   SET32avioGbl_DCLS_CTRL_ClkEn(r32, v)              _BFSET_(r32, 13, 13, v)
    #define   GET16avioGbl_DCLS_CTRL_ClkEn(r16)                _BFGET_(r16, 13, 13)
    #define   SET16avioGbl_DCLS_CTRL_ClkEn(r16, v)              _BFSET_(r16, 13, 13, v)

    #define   GET32avioGbl_DCLS_CTRL_dcls_sclk_inv(r32)        _BFGET_(r32, 14, 14)
    #define   SET32avioGbl_DCLS_CTRL_dcls_sclk_inv(r32, v)      _BFSET_(r32, 14, 14, v)
    #define   GET16avioGbl_DCLS_CTRL_dcls_sclk_inv(r16)        _BFGET_(r16, 14, 14)
    #define   SET16avioGbl_DCLS_CTRL_dcls_sclk_inv(r16, v)      _BFSET_(r16, 14, 14, v)

    #define   GET32avioGbl_DCLS_CTRL_dcls_sysClk_en(r32)       _BFGET_(r32, 15, 15)
    #define   SET32avioGbl_DCLS_CTRL_dcls_sysClk_en(r32, v)     _BFSET_(r32, 15, 15, v)
    #define   GET16avioGbl_DCLS_CTRL_dcls_sysClk_en(r16)       _BFGET_(r16, 15, 15)
    #define   SET16avioGbl_DCLS_CTRL_dcls_sysClk_en(r16, v)     _BFSET_(r16, 15, 15, v)

    #define     w32avioGbl_DCLS_CTRL                           {\
	    UNSG32 uDCLS_CTRL_clk_src_sel0                     :  3;\
	    UNSG32 uDCLS_CTRL_div_val1                         :  6;\
	    UNSG32 uDCLS_CTRL_div_val2                         :  4;\
	    UNSG32 uDCLS_CTRL_ClkEn                            :  1;\
	    UNSG32 uDCLS_CTRL_dcls_sclk_inv                    :  1;\
	    UNSG32 uDCLS_CTRL_dcls_sysClk_en                   :  1;\
	    UNSG32 RSVDx2194_b16                               : 16;\
	}
    union { UNSG32 u32avioGbl_DCLS_CTRL;
	    struct w32avioGbl_DCLS_CTRL;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32avioGbl_SWRST_CTRL_aioSyncRstn(r32)         _BFGET_(r32, 0, 0)
    #define   SET32avioGbl_SWRST_CTRL_aioSyncRstn(r32, v)       _BFSET_(r32, 0, 0, v)
    #define   GET16avioGbl_SWRST_CTRL_aioSyncRstn(r16)         _BFGET_(r16, 0, 0)
    #define   SET16avioGbl_SWRST_CTRL_aioSyncRstn(r16, v)       _BFSET_(r16, 0, 0, v)

    #define   GET32avioGbl_SWRST_CTRL_dpiSyncRstn(r32)         _BFGET_(r32, 1, 1)
    #define   SET32avioGbl_SWRST_CTRL_dpiSyncRstn(r32, v)       _BFSET_(r32, 1, 1, v)
    #define   GET16avioGbl_SWRST_CTRL_dpiSyncRstn(r16)         _BFGET_(r16, 1, 1)
    #define   SET16avioGbl_SWRST_CTRL_dpiSyncRstn(r16, v)       _BFSET_(r16, 1, 1, v)

    #define   GET32avioGbl_SWRST_CTRL_lcdc1SyncRstn(r32)       _BFGET_(r32, 2, 2)
    #define   SET32avioGbl_SWRST_CTRL_lcdc1SyncRstn(r32, v)     _BFSET_(r32, 2, 2, v)
    #define   GET16avioGbl_SWRST_CTRL_lcdc1SyncRstn(r16)       _BFGET_(r16, 2, 2)
    #define   SET16avioGbl_SWRST_CTRL_lcdc1SyncRstn(r16, v)     _BFSET_(r16, 2, 2, v)

    #define   GET32avioGbl_SWRST_CTRL_lcdc1SysSyncRstn(r32)    _BFGET_(r32, 3, 3)
    #define   SET32avioGbl_SWRST_CTRL_lcdc1SysSyncRstn(r32, v)  _BFSET_(r32, 3, 3, v)
    #define   GET16avioGbl_SWRST_CTRL_lcdc1SysSyncRstn(r16)    _BFGET_(r16, 3, 3)
    #define   SET16avioGbl_SWRST_CTRL_lcdc1SysSyncRstn(r16, v)  _BFSET_(r16, 3, 3, v)

    #define   GET32avioGbl_SWRST_CTRL_lcdc2SyncRstn(r32)       _BFGET_(r32, 4, 4)
    #define   SET32avioGbl_SWRST_CTRL_lcdc2SyncRstn(r32, v)     _BFSET_(r32, 4, 4, v)
    #define   GET16avioGbl_SWRST_CTRL_lcdc2SyncRstn(r16)       _BFGET_(r16, 4, 4)
    #define   SET16avioGbl_SWRST_CTRL_lcdc2SyncRstn(r16, v)     _BFSET_(r16, 4, 4, v)

    #define   GET32avioGbl_SWRST_CTRL_lcdc2SysSyncRstn(r32)    _BFGET_(r32, 5, 5)
    #define   SET32avioGbl_SWRST_CTRL_lcdc2SysSyncRstn(r32, v)  _BFSET_(r32, 5, 5, v)
    #define   GET16avioGbl_SWRST_CTRL_lcdc2SysSyncRstn(r16)    _BFGET_(r16, 5, 5)
    #define   SET16avioGbl_SWRST_CTRL_lcdc2SysSyncRstn(r16, v)  _BFSET_(r16, 5, 5, v)

    #define   GET32avioGbl_SWRST_CTRL_daifSyncRstn(r32)        _BFGET_(r32, 6, 6)
    #define   SET32avioGbl_SWRST_CTRL_daifSyncRstn(r32, v)      _BFSET_(r32, 6, 6, v)
    #define   GET16avioGbl_SWRST_CTRL_daifSyncRstn(r16)        _BFGET_(r16, 6, 6)
    #define   SET16avioGbl_SWRST_CTRL_daifSyncRstn(r16, v)      _BFSET_(r16, 6, 6, v)

    #define   GET32avioGbl_SWRST_CTRL_daif_nares_SyncRstn(r32) _BFGET_(r32, 7, 7)
    #define   SET32avioGbl_SWRST_CTRL_daif_nares_SyncRstn(r32, v) _BFSET_(r32, 7, 7, v)
    #define   GET16avioGbl_SWRST_CTRL_daif_nares_SyncRstn(r16) _BFGET_(r16, 7, 7)
    #define   SET16avioGbl_SWRST_CTRL_daif_nares_SyncRstn(r16, v) _BFSET_(r16, 7, 7, v)

    #define   GET32avioGbl_SWRST_CTRL_daifSysSyncRstn(r32)     _BFGET_(r32, 8, 8)
    #define   SET32avioGbl_SWRST_CTRL_daifSysSyncRstn(r32, v)   _BFSET_(r32, 8, 8, v)
    #define   GET16avioGbl_SWRST_CTRL_daifSysSyncRstn(r16)     _BFGET_(r16, 8, 8)
    #define   SET16avioGbl_SWRST_CTRL_daifSysSyncRstn(r16, v)   _BFSET_(r16, 8, 8, v)

    #define   GET32avioGbl_SWRST_CTRL_drtSyncRstn(r32)         _BFGET_(r32, 9, 9)
    #define   SET32avioGbl_SWRST_CTRL_drtSyncRstn(r32, v)       _BFSET_(r32, 9, 9, v)
    #define   GET16avioGbl_SWRST_CTRL_drtSyncRstn(r16)         _BFGET_(r16, 9, 9)
    #define   SET16avioGbl_SWRST_CTRL_drtSyncRstn(r16, v)       _BFSET_(r16, 9, 9, v)

    #define   GET32avioGbl_SWRST_CTRL_drtSysSyncRstn(r32)      _BFGET_(r32, 10, 10)
    #define   SET32avioGbl_SWRST_CTRL_drtSysSyncRstn(r32, v)    _BFSET_(r32, 10, 10, v)
    #define   GET16avioGbl_SWRST_CTRL_drtSysSyncRstn(r16)      _BFGET_(r16, 10, 10)
    #define   SET16avioGbl_SWRST_CTRL_drtSysSyncRstn(r16, v)    _BFSET_(r16, 10, 10, v)

    #define   GET32avioGbl_SWRST_CTRL_dclsSyncRstn(r32)        _BFGET_(r32, 11, 11)
    #define   SET32avioGbl_SWRST_CTRL_dclsSyncRstn(r32, v)      _BFSET_(r32, 11, 11, v)
    #define   GET16avioGbl_SWRST_CTRL_dclsSyncRstn(r16)        _BFGET_(r16, 11, 11)
    #define   SET16avioGbl_SWRST_CTRL_dclsSyncRstn(r16, v)      _BFSET_(r16, 11, 11, v)

    #define   GET32avioGbl_SWRST_CTRL_dclsSysSyncRstn(r32)     _BFGET_(r32, 12, 12)
    #define   SET32avioGbl_SWRST_CTRL_dclsSysSyncRstn(r32, v)   _BFSET_(r32, 12, 12, v)
    #define   GET16avioGbl_SWRST_CTRL_dclsSysSyncRstn(r16)     _BFGET_(r16, 12, 12)
    #define   SET16avioGbl_SWRST_CTRL_dclsSysSyncRstn(r16, v)   _BFSET_(r16, 12, 12, v)

    #define   GET32avioGbl_SWRST_CTRL_ptrack1SysSyncRstn(r32)  _BFGET_(r32, 13, 13)
    #define   SET32avioGbl_SWRST_CTRL_ptrack1SysSyncRstn(r32, v) _BFSET_(r32, 13, 13, v)
    #define   GET16avioGbl_SWRST_CTRL_ptrack1SysSyncRstn(r16)  _BFGET_(r16, 13, 13)
    #define   SET16avioGbl_SWRST_CTRL_ptrack1SysSyncRstn(r16, v) _BFSET_(r16, 13, 13, v)

    #define   GET32avioGbl_SWRST_CTRL_ptrack1SyncRstn(r32)     _BFGET_(r32, 14, 14)
    #define   SET32avioGbl_SWRST_CTRL_ptrack1SyncRstn(r32, v)   _BFSET_(r32, 14, 14, v)
    #define   GET16avioGbl_SWRST_CTRL_ptrack1SyncRstn(r16)     _BFGET_(r16, 14, 14)
    #define   SET16avioGbl_SWRST_CTRL_ptrack1SyncRstn(r16, v)   _BFSET_(r16, 14, 14, v)

    #define   GET32avioGbl_SWRST_CTRL_ptrack2SysSyncRstn(r32)  _BFGET_(r32, 15, 15)
    #define   SET32avioGbl_SWRST_CTRL_ptrack2SysSyncRstn(r32, v) _BFSET_(r32, 15, 15, v)
    #define   GET16avioGbl_SWRST_CTRL_ptrack2SysSyncRstn(r16)  _BFGET_(r16, 15, 15)
    #define   SET16avioGbl_SWRST_CTRL_ptrack2SysSyncRstn(r16, v) _BFSET_(r16, 15, 15, v)

    #define   GET32avioGbl_SWRST_CTRL_ptrack2SyncRstn(r32)     _BFGET_(r32, 16, 16)
    #define   SET32avioGbl_SWRST_CTRL_ptrack2SyncRstn(r32, v)   _BFSET_(r32, 16, 16, v)
    #define   GET16avioGbl_SWRST_CTRL_ptrack2SyncRstn(r16)     _BFGET_(r16, 0, 0)
    #define   SET16avioGbl_SWRST_CTRL_ptrack2SyncRstn(r16, v)   _BFSET_(r16, 0, 0, v)

    #define     w32avioGbl_SWRST_CTRL                          {\
	    UNSG32 uSWRST_CTRL_aioSyncRstn                     :  1;\
	    UNSG32 uSWRST_CTRL_dpiSyncRstn                     :  1;\
	    UNSG32 uSWRST_CTRL_lcdc1SyncRstn                   :  1;\
	    UNSG32 uSWRST_CTRL_lcdc1SysSyncRstn                :  1;\
	    UNSG32 uSWRST_CTRL_lcdc2SyncRstn                   :  1;\
	    UNSG32 uSWRST_CTRL_lcdc2SysSyncRstn                :  1;\
	    UNSG32 uSWRST_CTRL_daifSyncRstn                    :  1;\
	    UNSG32 uSWRST_CTRL_daif_nares_SyncRstn             :  1;\
	    UNSG32 uSWRST_CTRL_daifSysSyncRstn                 :  1;\
	    UNSG32 uSWRST_CTRL_drtSyncRstn                     :  1;\
	    UNSG32 uSWRST_CTRL_drtSysSyncRstn                  :  1;\
	    UNSG32 uSWRST_CTRL_dclsSyncRstn                    :  1;\
	    UNSG32 uSWRST_CTRL_dclsSysSyncRstn                 :  1;\
	    UNSG32 uSWRST_CTRL_ptrack1SysSyncRstn              :  1;\
	    UNSG32 uSWRST_CTRL_ptrack1SyncRstn                 :  1;\
	    UNSG32 uSWRST_CTRL_ptrack2SysSyncRstn              :  1;\
	    UNSG32 uSWRST_CTRL_ptrack2SyncRstn                 :  1;\
	    UNSG32 RSVDx2198_b17                               : 15;\
	}
    union { UNSG32 u32avioGbl_SWRST_CTRL;
	    struct w32avioGbl_SWRST_CTRL;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32avioGbl_LCDC_CTRL_lcdc1_clk_sel(r32)        _BFGET_(r32, 0, 0)
    #define   SET32avioGbl_LCDC_CTRL_lcdc1_clk_sel(r32, v)      _BFSET_(r32, 0, 0, v)
    #define   GET16avioGbl_LCDC_CTRL_lcdc1_clk_sel(r16)        _BFGET_(r16, 0, 0)
    #define   SET16avioGbl_LCDC_CTRL_lcdc1_clk_sel(r16, v)      _BFSET_(r16, 0, 0, v)

    #define   GET32avioGbl_LCDC_CTRL_lcdc2_clk_sel(r32)        _BFGET_(r32, 1, 1)
    #define   SET32avioGbl_LCDC_CTRL_lcdc2_clk_sel(r32, v)      _BFSET_(r32, 1, 1, v)
    #define   GET16avioGbl_LCDC_CTRL_lcdc2_clk_sel(r16)        _BFGET_(r16, 1, 1)
    #define   SET16avioGbl_LCDC_CTRL_lcdc2_clk_sel(r16, v)      _BFSET_(r16, 1, 1, v)

    #define   GET32avioGbl_LCDC_CTRL_lcdc1_ClkSel(r32)         _BFGET_(r32, 4, 2)
    #define   SET32avioGbl_LCDC_CTRL_lcdc1_ClkSel(r32, v)       _BFSET_(r32, 4, 2, v)
    #define   GET16avioGbl_LCDC_CTRL_lcdc1_ClkSel(r16)         _BFGET_(r16, 4, 2)
    #define   SET16avioGbl_LCDC_CTRL_lcdc1_ClkSel(r16, v)       _BFSET_(r16, 4, 2, v)

    #define   GET32avioGbl_LCDC_CTRL_lcdc1_ClkSwitch(r32)      _BFGET_(r32, 5, 5)
    #define   SET32avioGbl_LCDC_CTRL_lcdc1_ClkSwitch(r32, v)    _BFSET_(r32, 5, 5, v)
    #define   GET16avioGbl_LCDC_CTRL_lcdc1_ClkSwitch(r16)      _BFGET_(r16, 5, 5)
    #define   SET16avioGbl_LCDC_CTRL_lcdc1_ClkSwitch(r16, v)    _BFSET_(r16, 5, 5, v)

    #define   GET32avioGbl_LCDC_CTRL_lcdc1_ClkD3Switch(r32)    _BFGET_(r32, 6, 6)
    #define   SET32avioGbl_LCDC_CTRL_lcdc1_ClkD3Switch(r32, v)  _BFSET_(r32, 6, 6, v)
    #define   GET16avioGbl_LCDC_CTRL_lcdc1_ClkD3Switch(r16)    _BFGET_(r16, 6, 6)
    #define   SET16avioGbl_LCDC_CTRL_lcdc1_ClkD3Switch(r16, v)  _BFSET_(r16, 6, 6, v)

    #define   GET32avioGbl_LCDC_CTRL_lcdc1_ClkEn(r32)          _BFGET_(r32, 7, 7)
    #define   SET32avioGbl_LCDC_CTRL_lcdc1_ClkEn(r32, v)        _BFSET_(r32, 7, 7, v)
    #define   GET16avioGbl_LCDC_CTRL_lcdc1_ClkEn(r16)          _BFGET_(r16, 7, 7)
    #define   SET16avioGbl_LCDC_CTRL_lcdc1_ClkEn(r16, v)        _BFSET_(r16, 7, 7, v)

    #define   GET32avioGbl_LCDC_CTRL_lcdc1_sysClk_en(r32)      _BFGET_(r32, 8, 8)
    #define   SET32avioGbl_LCDC_CTRL_lcdc1_sysClk_en(r32, v)    _BFSET_(r32, 8, 8, v)
    #define   GET16avioGbl_LCDC_CTRL_lcdc1_sysClk_en(r16)      _BFGET_(r16, 8, 8)
    #define   SET16avioGbl_LCDC_CTRL_lcdc1_sysClk_en(r16, v)    _BFSET_(r16, 8, 8, v)

    #define   GET32avioGbl_LCDC_CTRL_lcdc2_ClkSel(r32)         _BFGET_(r32, 11, 9)
    #define   SET32avioGbl_LCDC_CTRL_lcdc2_ClkSel(r32, v)       _BFSET_(r32, 11, 9, v)
    #define   GET16avioGbl_LCDC_CTRL_lcdc2_ClkSel(r16)         _BFGET_(r16, 11, 9)
    #define   SET16avioGbl_LCDC_CTRL_lcdc2_ClkSel(r16, v)       _BFSET_(r16, 11, 9, v)

    #define   GET32avioGbl_LCDC_CTRL_lcdc2_ClkSwitch(r32)      _BFGET_(r32, 12, 12)
    #define   SET32avioGbl_LCDC_CTRL_lcdc2_ClkSwitch(r32, v)    _BFSET_(r32, 12, 12, v)
    #define   GET16avioGbl_LCDC_CTRL_lcdc2_ClkSwitch(r16)      _BFGET_(r16, 12, 12)
    #define   SET16avioGbl_LCDC_CTRL_lcdc2_ClkSwitch(r16, v)    _BFSET_(r16, 12, 12, v)

    #define   GET32avioGbl_LCDC_CTRL_lcdc2_ClkD3Switch(r32)    _BFGET_(r32, 13, 13)
    #define   SET32avioGbl_LCDC_CTRL_lcdc2_ClkD3Switch(r32, v)  _BFSET_(r32, 13, 13, v)
    #define   GET16avioGbl_LCDC_CTRL_lcdc2_ClkD3Switch(r16)    _BFGET_(r16, 13, 13)
    #define   SET16avioGbl_LCDC_CTRL_lcdc2_ClkD3Switch(r16, v)  _BFSET_(r16, 13, 13, v)

    #define   GET32avioGbl_LCDC_CTRL_lcdc2_ClkEn(r32)          _BFGET_(r32, 14, 14)
    #define   SET32avioGbl_LCDC_CTRL_lcdc2_ClkEn(r32, v)        _BFSET_(r32, 14, 14, v)
    #define   GET16avioGbl_LCDC_CTRL_lcdc2_ClkEn(r16)          _BFGET_(r16, 14, 14)
    #define   SET16avioGbl_LCDC_CTRL_lcdc2_ClkEn(r16, v)        _BFSET_(r16, 14, 14, v)

    #define   GET32avioGbl_LCDC_CTRL_lcdc2_sysClk_en(r32)      _BFGET_(r32, 15, 15)
    #define   SET32avioGbl_LCDC_CTRL_lcdc2_sysClk_en(r32, v)    _BFSET_(r32, 15, 15, v)
    #define   GET16avioGbl_LCDC_CTRL_lcdc2_sysClk_en(r16)      _BFGET_(r16, 15, 15)
    #define   SET16avioGbl_LCDC_CTRL_lcdc2_sysClk_en(r16, v)    _BFSET_(r16, 15, 15, v)

    #define     w32avioGbl_LCDC_CTRL                           {\
	    UNSG32 uLCDC_CTRL_lcdc1_clk_sel                    :  1;\
	    UNSG32 uLCDC_CTRL_lcdc2_clk_sel                    :  1;\
	    UNSG32 uLCDC_CTRL_lcdc1_ClkSel                     :  3;\
	    UNSG32 uLCDC_CTRL_lcdc1_ClkSwitch                  :  1;\
	    UNSG32 uLCDC_CTRL_lcdc1_ClkD3Switch                :  1;\
	    UNSG32 uLCDC_CTRL_lcdc1_ClkEn                      :  1;\
	    UNSG32 uLCDC_CTRL_lcdc1_sysClk_en                  :  1;\
	    UNSG32 uLCDC_CTRL_lcdc2_ClkSel                     :  3;\
	    UNSG32 uLCDC_CTRL_lcdc2_ClkSwitch                  :  1;\
	    UNSG32 uLCDC_CTRL_lcdc2_ClkD3Switch                :  1;\
	    UNSG32 uLCDC_CTRL_lcdc2_ClkEn                      :  1;\
	    UNSG32 uLCDC_CTRL_lcdc2_sysClk_en                  :  1;\
	    UNSG32 RSVDx219C_b16                               : 16;\
	}
    union { UNSG32 u32avioGbl_LCDC_CTRL;
	    struct w32avioGbl_LCDC_CTRL;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32avioGbl_LCDC2_CTRL_eof_frst_sel(r32)        _BFGET_(r32, 0, 0)
    #define   SET32avioGbl_LCDC2_CTRL_eof_frst_sel(r32, v)      _BFSET_(r32, 0, 0, v)
    #define   GET16avioGbl_LCDC2_CTRL_eof_frst_sel(r16)        _BFGET_(r16, 0, 0)
    #define   SET16avioGbl_LCDC2_CTRL_eof_frst_sel(r16, v)      _BFSET_(r16, 0, 0, v)

    #define   GET32avioGbl_LCDC2_CTRL_tear_sftrst(r32)         _BFGET_(r32, 1, 1)
    #define   SET32avioGbl_LCDC2_CTRL_tear_sftrst(r32, v)       _BFSET_(r32, 1, 1, v)
    #define   GET16avioGbl_LCDC2_CTRL_tear_sftrst(r16)         _BFGET_(r16, 1, 1)
    #define   SET16avioGbl_LCDC2_CTRL_tear_sftrst(r16, v)       _BFSET_(r16, 1, 1, v)

    #define   GET32avioGbl_LCDC2_CTRL_clken_ctrl0(r32)         _BFGET_(r32, 2, 2)
    #define   SET32avioGbl_LCDC2_CTRL_clken_ctrl0(r32, v)       _BFSET_(r32, 2, 2, v)
    #define   GET16avioGbl_LCDC2_CTRL_clken_ctrl0(r16)         _BFGET_(r16, 2, 2)
    #define   SET16avioGbl_LCDC2_CTRL_clken_ctrl0(r16, v)       _BFSET_(r16, 2, 2, v)

    #define   GET32avioGbl_LCDC2_CTRL_clken_ctrl1(r32)         _BFGET_(r32, 3, 3)
    #define   SET32avioGbl_LCDC2_CTRL_clken_ctrl1(r32, v)       _BFSET_(r32, 3, 3, v)
    #define   GET16avioGbl_LCDC2_CTRL_clken_ctrl1(r16)         _BFGET_(r16, 3, 3)
    #define   SET16avioGbl_LCDC2_CTRL_clken_ctrl1(r16, v)       _BFSET_(r16, 3, 3, v)

    #define   GET32avioGbl_LCDC2_CTRL_clken_ctrl2(r32)         _BFGET_(r32, 4, 4)
    #define   SET32avioGbl_LCDC2_CTRL_clken_ctrl2(r32, v)       _BFSET_(r32, 4, 4, v)
    #define   GET16avioGbl_LCDC2_CTRL_clken_ctrl2(r16)         _BFGET_(r16, 4, 4)
    #define   SET16avioGbl_LCDC2_CTRL_clken_ctrl2(r16, v)       _BFSET_(r16, 4, 4, v)

    #define   GET32avioGbl_LCDC2_CTRL_clken_ctrl3(r32)         _BFGET_(r32, 5, 5)
    #define   SET32avioGbl_LCDC2_CTRL_clken_ctrl3(r32, v)       _BFSET_(r32, 5, 5, v)
    #define   GET16avioGbl_LCDC2_CTRL_clken_ctrl3(r16)         _BFGET_(r16, 5, 5)
    #define   SET16avioGbl_LCDC2_CTRL_clken_ctrl3(r16, v)       _BFSET_(r16, 5, 5, v)

    #define     w32avioGbl_LCDC2_CTRL                          {\
	    UNSG32 uLCDC2_CTRL_eof_frst_sel                    :  1;\
	    UNSG32 uLCDC2_CTRL_tear_sftrst                     :  1;\
	    UNSG32 uLCDC2_CTRL_clken_ctrl0                     :  1;\
	    UNSG32 uLCDC2_CTRL_clken_ctrl1                     :  1;\
	    UNSG32 uLCDC2_CTRL_clken_ctrl2                     :  1;\
	    UNSG32 uLCDC2_CTRL_clken_ctrl3                     :  1;\
	    UNSG32 RSVDx21A0_b6                                : 26;\
	}
    union { UNSG32 u32avioGbl_LCDC2_CTRL;
	    struct w32avioGbl_LCDC2_CTRL;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32avioGbl_PTRACK_CTRL_ptrack1_sysClk_en(r32)  _BFGET_(r32, 0, 0)
    #define   SET32avioGbl_PTRACK_CTRL_ptrack1_sysClk_en(r32, v) _BFSET_(r32, 0, 0, v)
    #define   GET16avioGbl_PTRACK_CTRL_ptrack1_sysClk_en(r16)  _BFGET_(r16, 0, 0)
    #define   SET16avioGbl_PTRACK_CTRL_ptrack1_sysClk_en(r16, v) _BFSET_(r16, 0, 0, v)

    #define   GET32avioGbl_PTRACK_CTRL_ptrack1_clk_en(r32)     _BFGET_(r32, 1, 1)
    #define   SET32avioGbl_PTRACK_CTRL_ptrack1_clk_en(r32, v)   _BFSET_(r32, 1, 1, v)
    #define   GET16avioGbl_PTRACK_CTRL_ptrack1_clk_en(r16)     _BFGET_(r16, 1, 1)
    #define   SET16avioGbl_PTRACK_CTRL_ptrack1_clk_en(r16, v)   _BFSET_(r16, 1, 1, v)

    #define   GET32avioGbl_PTRACK_CTRL_ptrack2_sysClk_en(r32)  _BFGET_(r32, 2, 2)
    #define   SET32avioGbl_PTRACK_CTRL_ptrack2_sysClk_en(r32, v) _BFSET_(r32, 2, 2, v)
    #define   GET16avioGbl_PTRACK_CTRL_ptrack2_sysClk_en(r16)  _BFGET_(r16, 2, 2)
    #define   SET16avioGbl_PTRACK_CTRL_ptrack2_sysClk_en(r16, v) _BFSET_(r16, 2, 2, v)

    #define   GET32avioGbl_PTRACK_CTRL_ptrack2_clk_en(r32)     _BFGET_(r32, 3, 3)
    #define   SET32avioGbl_PTRACK_CTRL_ptrack2_clk_en(r32, v)   _BFSET_(r32, 3, 3, v)
    #define   GET16avioGbl_PTRACK_CTRL_ptrack2_clk_en(r16)     _BFGET_(r16, 3, 3)
    #define   SET16avioGbl_PTRACK_CTRL_ptrack2_clk_en(r16, v)   _BFSET_(r16, 3, 3, v)

    #define     w32avioGbl_PTRACK_CTRL                         {\
	    UNSG32 uPTRACK_CTRL_ptrack1_sysClk_en              :  1;\
	    UNSG32 uPTRACK_CTRL_ptrack1_clk_en                 :  1;\
	    UNSG32 uPTRACK_CTRL_ptrack2_sysClk_en              :  1;\
	    UNSG32 uPTRACK_CTRL_ptrack2_clk_en                 :  1;\
	    UNSG32 RSVDx21A4_b4                                : 28;\
	}
    union { UNSG32 u32avioGbl_PTRACK_CTRL;
	    struct w32avioGbl_PTRACK_CTRL;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32avioGbl_MIPI_CTRL_mipiClkg_en(r32)          _BFGET_(r32, 0, 0)
    #define   SET32avioGbl_MIPI_CTRL_mipiClkg_en(r32, v)        _BFSET_(r32, 0, 0, v)
    #define   GET16avioGbl_MIPI_CTRL_mipiClkg_en(r16)          _BFGET_(r16, 0, 0)
    #define   SET16avioGbl_MIPI_CTRL_mipiClkg_en(r16, v)        _BFSET_(r16, 0, 0, v)

    #define   GET32avioGbl_MIPI_CTRL_mipiSysClkg_en(r32)       _BFGET_(r32, 1, 1)
    #define   SET32avioGbl_MIPI_CTRL_mipiSysClkg_en(r32, v)     _BFSET_(r32, 1, 1, v)
    #define   GET16avioGbl_MIPI_CTRL_mipiSysClkg_en(r16)       _BFGET_(r16, 1, 1)
    #define   SET16avioGbl_MIPI_CTRL_mipiSysClkg_en(r16, v)     _BFSET_(r16, 1, 1, v)

    #define   GET32avioGbl_MIPI_CTRL_dpidataen_pol(r32)        _BFGET_(r32, 2, 2)
    #define   SET32avioGbl_MIPI_CTRL_dpidataen_pol(r32, v)      _BFSET_(r32, 2, 2, v)
    #define   GET16avioGbl_MIPI_CTRL_dpidataen_pol(r16)        _BFGET_(r16, 2, 2)
    #define   SET16avioGbl_MIPI_CTRL_dpidataen_pol(r16, v)      _BFSET_(r16, 2, 2, v)

    #define   GET32avioGbl_MIPI_CTRL_dpivsync_pol(r32)         _BFGET_(r32, 3, 3)
    #define   SET32avioGbl_MIPI_CTRL_dpivsync_pol(r32, v)       _BFSET_(r32, 3, 3, v)
    #define   GET16avioGbl_MIPI_CTRL_dpivsync_pol(r16)         _BFGET_(r16, 3, 3)
    #define   SET16avioGbl_MIPI_CTRL_dpivsync_pol(r16, v)       _BFSET_(r16, 3, 3, v)

    #define   GET32avioGbl_MIPI_CTRL_dpihsync_pol(r32)         _BFGET_(r32, 4, 4)
    #define   SET32avioGbl_MIPI_CTRL_dpihsync_pol(r32, v)       _BFSET_(r32, 4, 4, v)
    #define   GET16avioGbl_MIPI_CTRL_dpihsync_pol(r16)         _BFGET_(r16, 4, 4)
    #define   SET16avioGbl_MIPI_CTRL_dpihsync_pol(r16, v)       _BFSET_(r16, 4, 4, v)

    #define   GET32avioGbl_MIPI_CTRL_dpishutd_pol(r32)         _BFGET_(r32, 5, 5)
    #define   SET32avioGbl_MIPI_CTRL_dpishutd_pol(r32, v)       _BFSET_(r32, 5, 5, v)
    #define   GET16avioGbl_MIPI_CTRL_dpishutd_pol(r16)         _BFGET_(r16, 5, 5)
    #define   SET16avioGbl_MIPI_CTRL_dpishutd_pol(r16, v)       _BFSET_(r16, 5, 5, v)

    #define   GET32avioGbl_MIPI_CTRL_dpicolorm_pol(r32)        _BFGET_(r32, 6, 6)
    #define   SET32avioGbl_MIPI_CTRL_dpicolorm_pol(r32, v)      _BFSET_(r32, 6, 6, v)
    #define   GET16avioGbl_MIPI_CTRL_dpicolorm_pol(r16)        _BFGET_(r16, 6, 6)
    #define   SET16avioGbl_MIPI_CTRL_dpicolorm_pol(r16, v)      _BFSET_(r16, 6, 6, v)

    #define   GET32avioGbl_MIPI_CTRL_colormode(r32)            _BFGET_(r32, 7, 7)
    #define   SET32avioGbl_MIPI_CTRL_colormode(r32, v)          _BFSET_(r32, 7, 7, v)
    #define   GET16avioGbl_MIPI_CTRL_colormode(r16)            _BFGET_(r16, 7, 7)
    #define   SET16avioGbl_MIPI_CTRL_colormode(r16, v)          _BFSET_(r16, 7, 7, v)

    #define   GET32avioGbl_MIPI_CTRL_shutdn(r32)               _BFGET_(r32, 8, 8)
    #define   SET32avioGbl_MIPI_CTRL_shutdn(r32, v)             _BFSET_(r32, 8, 8, v)
    #define   GET16avioGbl_MIPI_CTRL_shutdn(r16)               _BFGET_(r16, 8, 8)
    #define   SET16avioGbl_MIPI_CTRL_shutdn(r16, v)             _BFSET_(r16, 8, 8, v)

    #define   GET32avioGbl_MIPI_CTRL_force_pll_on(r32)         _BFGET_(r32, 9, 9)
    #define   SET32avioGbl_MIPI_CTRL_force_pll_on(r32, v)       _BFSET_(r32, 9, 9, v)
    #define   GET16avioGbl_MIPI_CTRL_force_pll_on(r16)         _BFGET_(r16, 9, 9)
    #define   SET16avioGbl_MIPI_CTRL_force_pll_on(r16, v)       _BFSET_(r16, 9, 9, v)

    #define   GET32avioGbl_MIPI_CTRL_tear_request_pulse(r32)   _BFGET_(r32, 10, 10)
    #define   SET32avioGbl_MIPI_CTRL_tear_request_pulse(r32, v) _BFSET_(r32, 10, 10, v)
    #define   GET16avioGbl_MIPI_CTRL_tear_request_pulse(r16)   _BFGET_(r16, 10, 10)
    #define   SET16avioGbl_MIPI_CTRL_tear_request_pulse(r16, v) _BFSET_(r16, 10, 10, v)

    #define   GET32avioGbl_MIPI_CTRL_updatecfg_pulse(r32)      _BFGET_(r32, 11, 11)
    #define   SET32avioGbl_MIPI_CTRL_updatecfg_pulse(r32, v)    _BFSET_(r32, 11, 11, v)
    #define   GET16avioGbl_MIPI_CTRL_updatecfg_pulse(r16)      _BFGET_(r16, 11, 11)
    #define   SET16avioGbl_MIPI_CTRL_updatecfg_pulse(r16, v)    _BFSET_(r16, 11, 11, v)

    #define   GET32avioGbl_MIPI_CTRL_tear_sftrst(r32)          _BFGET_(r32, 12, 12)
    #define   SET32avioGbl_MIPI_CTRL_tear_sftrst(r32, v)        _BFSET_(r32, 12, 12, v)
    #define   GET16avioGbl_MIPI_CTRL_tear_sftrst(r16)          _BFGET_(r16, 12, 12)
    #define   SET16avioGbl_MIPI_CTRL_tear_sftrst(r16, v)        _BFSET_(r16, 12, 12, v)

    #define   GET32avioGbl_MIPI_CTRL_dsi_te_in_sel(r32)        _BFGET_(r32, 13, 13)
    #define   SET32avioGbl_MIPI_CTRL_dsi_te_in_sel(r32, v)      _BFSET_(r32, 13, 13, v)
    #define   GET16avioGbl_MIPI_CTRL_dsi_te_in_sel(r16)        _BFGET_(r16, 13, 13)
    #define   SET16avioGbl_MIPI_CTRL_dsi_te_in_sel(r16, v)      _BFSET_(r16, 13, 13, v)

    #define   GET32avioGbl_MIPI_CTRL_dsi_te_in_sense(r32)      _BFGET_(r32, 14, 14)
    #define   SET32avioGbl_MIPI_CTRL_dsi_te_in_sense(r32, v)    _BFSET_(r32, 14, 14, v)
    #define   GET16avioGbl_MIPI_CTRL_dsi_te_in_sense(r16)      _BFGET_(r16, 14, 14)
    #define   SET16avioGbl_MIPI_CTRL_dsi_te_in_sense(r16, v)    _BFSET_(r16, 14, 14, v)

    #define   GET32avioGbl_MIPI_CTRL_dsi_te_enable(r32)        _BFGET_(r32, 15, 15)
    #define   SET32avioGbl_MIPI_CTRL_dsi_te_enable(r32, v)      _BFSET_(r32, 15, 15, v)
    #define   GET16avioGbl_MIPI_CTRL_dsi_te_enable(r16)        _BFGET_(r16, 15, 15)
    #define   SET16avioGbl_MIPI_CTRL_dsi_te_enable(r16, v)      _BFSET_(r16, 15, 15, v)

    #define     w32avioGbl_MIPI_CTRL                           {\
	    UNSG32 uMIPI_CTRL_mipiClkg_en                      :  1;\
	    UNSG32 uMIPI_CTRL_mipiSysClkg_en                   :  1;\
	    UNSG32 uMIPI_CTRL_dpidataen_pol                    :  1;\
	    UNSG32 uMIPI_CTRL_dpivsync_pol                     :  1;\
	    UNSG32 uMIPI_CTRL_dpihsync_pol                     :  1;\
	    UNSG32 uMIPI_CTRL_dpishutd_pol                     :  1;\
	    UNSG32 uMIPI_CTRL_dpicolorm_pol                    :  1;\
	    UNSG32 uMIPI_CTRL_colormode                        :  1;\
	    UNSG32 uMIPI_CTRL_shutdn                           :  1;\
	    UNSG32 uMIPI_CTRL_force_pll_on                     :  1;\
	    UNSG32 uMIPI_CTRL_tear_request_pulse               :  1;\
	    UNSG32 uMIPI_CTRL_updatecfg_pulse                  :  1;\
	    UNSG32 uMIPI_CTRL_tear_sftrst                      :  1;\
	    UNSG32 uMIPI_CTRL_dsi_te_in_sel                    :  1;\
	    UNSG32 uMIPI_CTRL_dsi_te_in_sense                  :  1;\
	    UNSG32 uMIPI_CTRL_dsi_te_enable                    :  1;\
	    UNSG32 RSVDx21A8_b16                               : 16;\
	}
    union { UNSG32 u32avioGbl_MIPI_CTRL;
	    struct w32avioGbl_MIPI_CTRL;
	  };
    #define   GET32avioGbl_MIPI_CTRL_dsitedelay(r32)           _BFGET_(r32, 21, 0)
    #define   SET32avioGbl_MIPI_CTRL_dsitedelay(r32, v)         _BFSET_(r32, 21, 0, v)

    #define   GET32avioGbl_MIPI_CTRL_edpi_mode(r32)            _BFGET_(r32, 22, 22)
    #define   SET32avioGbl_MIPI_CTRL_edpi_mode(r32, v)          _BFSET_(r32, 22, 22, v)
    #define   GET16avioGbl_MIPI_CTRL_edpi_mode(r16)            _BFGET_(r16, 6, 6)
    #define   SET16avioGbl_MIPI_CTRL_edpi_mode(r16, v)          _BFSET_(r16, 6, 6, v)

    #define     w32avioGbl_MIPI_CTRL1                          {\
	    UNSG32 uMIPI_CTRL_dsitedelay                       : 22;\
	    UNSG32 uMIPI_CTRL_edpi_mode                        :  1;\
	    UNSG32 RSVDx21AC_b23                               :  9;\
	}
    union { UNSG32 u32avioGbl_MIPI_CTRL1;
	    struct w32avioGbl_MIPI_CTRL1;
	  };
    ///////////////////////////////////////////////////////////
    #define   GET32avioGbl_MIPI_CTRL_STS_dsitewait(r32)        _BFGET_(r32, 0, 0)
    #define   SET32avioGbl_MIPI_CTRL_STS_dsitewait(r32, v)      _BFSET_(r32, 0, 0, v)
    #define   GET16avioGbl_MIPI_CTRL_STS_dsitewait(r16)        _BFGET_(r16, 0, 0)
    #define   SET16avioGbl_MIPI_CTRL_STS_dsitewait(r16, v)      _BFSET_(r16, 0, 0, v)

    #define     w32avioGbl_MIPI_CTRL_STS                       {\
	    UNSG32 uMIPI_CTRL_STS_dsitewait                    :  1;\
	    UNSG32 RSVDx21B0_b1                                : 31;\
	}
    union { UNSG32 u32avioGbl_MIPI_CTRL_STS;
	    struct w32avioGbl_MIPI_CTRL_STS;
	  };
    ///////////////////////////////////////////////////////////
	     UNSG8 RSVDx21B4[7756];
    ///////////////////////////////////////////////////////////
    } SIE_avioGbl;

    typedef union  T32avioGbl_AVPLLA_CLK_EN {
		UNSG32 u32;
	    struct w32avioGbl_AVPLLA_CLK_EN;
		 } T32avioGbl_AVPLLA_CLK_EN;
    typedef union  T32avioGbl_SWPDWN_CTRL {
		UNSG32 u32;
	    struct w32avioGbl_SWPDWN_CTRL;
		 } T32avioGbl_SWPDWN_CTRL;
    typedef union  T32avioGbl_RWTC_31to0 {
		UNSG32 u32;
	    struct w32avioGbl_RWTC_31to0;
		 } T32avioGbl_RWTC_31to0;
    typedef union  T32avioGbl_RWTC_57to32 {
		UNSG32 u32;
	    struct w32avioGbl_RWTC_57to32;
		 } T32avioGbl_RWTC_57to32;
    typedef union  T32avioGbl_CTRL {
		UNSG32 u32;
	    struct w32avioGbl_CTRL;
		 } T32avioGbl_CTRL;
    typedef union  T32avioGbl_CTRL0 {
		UNSG32 u32;
	    struct w32avioGbl_CTRL0;
		 } T32avioGbl_CTRL0;
    typedef union  T32avioGbl_GIC_INT {
		UNSG32 u32;
	    struct w32avioGbl_GIC_INT;
		 } T32avioGbl_GIC_INT;
    typedef union  T32avioGbl_INTR_CTRL {
		UNSG32 u32;
	    struct w32avioGbl_INTR_CTRL;
		 } T32avioGbl_INTR_CTRL;
    typedef union  T32avioGbl_INTR_STS {
		UNSG32 u32;
	    struct w32avioGbl_INTR_STS;
		 } T32avioGbl_INTR_STS;
    typedef union  T32avioGbl_DAIF_DRT_CTRL {
		UNSG32 u32;
	    struct w32avioGbl_DAIF_DRT_CTRL;
		 } T32avioGbl_DAIF_DRT_CTRL;
    typedef union  T32avioGbl_DCLS_CTRL {
		UNSG32 u32;
	    struct w32avioGbl_DCLS_CTRL;
		 } T32avioGbl_DCLS_CTRL;
    typedef union  T32avioGbl_SWRST_CTRL {
		UNSG32 u32;
	    struct w32avioGbl_SWRST_CTRL;
		 } T32avioGbl_SWRST_CTRL;
    typedef union  T32avioGbl_LCDC_CTRL {
		UNSG32 u32;
	    struct w32avioGbl_LCDC_CTRL;
		 } T32avioGbl_LCDC_CTRL;
    typedef union  T32avioGbl_LCDC2_CTRL {
		UNSG32 u32;
	    struct w32avioGbl_LCDC2_CTRL;
		 } T32avioGbl_LCDC2_CTRL;
    typedef union  T32avioGbl_PTRACK_CTRL {
		UNSG32 u32;
	    struct w32avioGbl_PTRACK_CTRL;
		 } T32avioGbl_PTRACK_CTRL;
    typedef union  T32avioGbl_MIPI_CTRL {
		UNSG32 u32;
	    struct w32avioGbl_MIPI_CTRL;
		 } T32avioGbl_MIPI_CTRL;
    typedef union  T32avioGbl_MIPI_CTRL1 {
		UNSG32 u32;
	    struct w32avioGbl_MIPI_CTRL1;
		 } T32avioGbl_MIPI_CTRL1;
    typedef union  T32avioGbl_MIPI_CTRL_STS {
		UNSG32 u32;
	    struct w32avioGbl_MIPI_CTRL_STS;
		 } T32avioGbl_MIPI_CTRL_STS;
    ///////////////////////////////////////////////////////////

    typedef union  TavioGbl_AVPLLA_CLK_EN {
		UNSG32 u32[1];
	    struct {
	    struct w32avioGbl_AVPLLA_CLK_EN;
		   };
		 } TavioGbl_AVPLLA_CLK_EN;
    typedef union  TavioGbl_SWPDWN_CTRL {
		UNSG32 u32[1];
	    struct {
	    struct w32avioGbl_SWPDWN_CTRL;
		   };
		 } TavioGbl_SWPDWN_CTRL;
    typedef union  TavioGbl_RWTC_31to0 {
		UNSG32 u32[1];
	    struct {
	    struct w32avioGbl_RWTC_31to0;
		   };
		 } TavioGbl_RWTC_31to0;
    typedef union  TavioGbl_RWTC_57to32 {
		UNSG32 u32[1];
	    struct {
	    struct w32avioGbl_RWTC_57to32;
		   };
		 } TavioGbl_RWTC_57to32;
    typedef union  TavioGbl_CTRL {
		UNSG32 u32[1];
	    struct {
	    struct w32avioGbl_CTRL;
		   };
		 } TavioGbl_CTRL;
    typedef union  TavioGbl_CTRL0 {
		UNSG32 u32[1];
	    struct {
	    struct w32avioGbl_CTRL0;
		   };
		 } TavioGbl_CTRL0;
    typedef union  TavioGbl_GIC_INT {
		UNSG32 u32[1];
	    struct {
	    struct w32avioGbl_GIC_INT;
		   };
		 } TavioGbl_GIC_INT;
    typedef union  TavioGbl_INTR_CTRL {
		UNSG32 u32[1];
	    struct {
	    struct w32avioGbl_INTR_CTRL;
		   };
		 } TavioGbl_INTR_CTRL;
    typedef union  TavioGbl_INTR_STS {
		UNSG32 u32[1];
	    struct {
	    struct w32avioGbl_INTR_STS;
		   };
		 } TavioGbl_INTR_STS;
    typedef union  TavioGbl_DAIF_DRT_CTRL {
		UNSG32 u32[1];
	    struct {
	    struct w32avioGbl_DAIF_DRT_CTRL;
		   };
		 } TavioGbl_DAIF_DRT_CTRL;
    typedef union  TavioGbl_DCLS_CTRL {
		UNSG32 u32[1];
	    struct {
	    struct w32avioGbl_DCLS_CTRL;
		   };
		 } TavioGbl_DCLS_CTRL;
    typedef union  TavioGbl_SWRST_CTRL {
		UNSG32 u32[1];
	    struct {
	    struct w32avioGbl_SWRST_CTRL;
		   };
		 } TavioGbl_SWRST_CTRL;
    typedef union  TavioGbl_LCDC_CTRL {
		UNSG32 u32[1];
	    struct {
	    struct w32avioGbl_LCDC_CTRL;
		   };
		 } TavioGbl_LCDC_CTRL;
    typedef union  TavioGbl_LCDC2_CTRL {
		UNSG32 u32[1];
	    struct {
	    struct w32avioGbl_LCDC2_CTRL;
		   };
		 } TavioGbl_LCDC2_CTRL;
    typedef union  TavioGbl_PTRACK_CTRL {
		UNSG32 u32[1];
	    struct {
	    struct w32avioGbl_PTRACK_CTRL;
		   };
		 } TavioGbl_PTRACK_CTRL;
    typedef union  TavioGbl_MIPI_CTRL {
		UNSG32 u32[2];
	    struct {
	    struct w32avioGbl_MIPI_CTRL;
	    struct w32avioGbl_MIPI_CTRL1;
		   };
		 } TavioGbl_MIPI_CTRL;
    typedef union  TavioGbl_MIPI_CTRL_STS {
		UNSG32 u32[1];
	    struct {
	    struct w32avioGbl_MIPI_CTRL_STS;
		   };
		 } TavioGbl_MIPI_CTRL_STS;

    ///////////////////////////////////////////////////////////
     SIGN32 avioGbl_drvrd(SIE_avioGbl *p, UNSG32 base, SIGN32 mem, SIGN32 tst);
     SIGN32 avioGbl_drvwr(SIE_avioGbl *p, UNSG32 base, SIGN32 mem, SIGN32 tst, UNSG32 *pcmd);
       void avioGbl_reset(SIE_avioGbl *p);
     SIGN32 avioGbl_cmp(SIE_avioGbl *p, SIE_avioGbl *pie, char *pfx, void *hLOG, SIGN32 mem, SIGN32 tst);
    #define avioGbl_check(p, pie, pfx, hLOG) avioGbl_cmp(p, pie, pfx, (void *)(hLOG), 0, 0)
    #define avioGbl_print(p,    pfx, hLOG) avioGbl_cmp(p, 0,  pfx, (void *)(hLOG), 0, 0)

#endif
//////
/// ENDOFINTERFACE: avioGbl
////////////////////////////////////////////////////////////

#ifdef __cplusplus
  }
#endif
#pragma  pack()

#endif
//////
/// ENDOFFILE: avioGbl.h
////////////////////////////////////////////////////////////
