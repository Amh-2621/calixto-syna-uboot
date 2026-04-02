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

#ifndef CTYPES_H_
#define CTYPES_H_

/*---------------------------------------------------------------------------
    Microsoft Visual C++
  ---------------------------------------------------------------------------*/
#if defined(_MSC_VER)

    typedef	unsigned char       UNSG8;
    typedef	signed char         SIGN8;
    typedef	unsigned short      UNSG16;
    typedef	signed short        SIGN16;
    typedef	unsigned int        UNSG32;
    typedef	signed int          SIGN32;
    typedef	unsigned __int64    UNSG64;
    typedef	signed __int64      SIGN64;
    typedef	float               REAL32;
    typedef	double              REAL64;

    #ifndef INLINE
	#define	INLINE          static __forceinline
    #endif

/*---------------------------------------------------------------------------
    ARMCC (RVCT)
  ---------------------------------------------------------------------------*/
#elif defined(__ARMCC_VERSION)

    typedef	unsigned char       UNSG8;
    typedef	signed char         SIGN8;
    typedef	unsigned short      UNSG16;
    typedef	signed short        SIGN16;
    typedef	unsigned int        UNSG32;
    typedef	signed int          SIGN32;
    typedef	unsigned long long  UNSG64;
    typedef	signed long long    SIGN64;
    typedef	float               REAL32;
    typedef	double              REAL64;

    #ifndef INLINE
	#define INLINE          static inline
    #endif

/*---------------------------------------------------------------------------
    ZSP uses this define
  ---------------------------------------------------------------------------*/
#elif defined(ZSP)

    typedef	unsigned char       UNSG8;
    typedef	signed char         SIGN8;
    typedef	unsigned short      UNSG16;
    typedef	signed short        SIGN16;
    typedef	unsigned long       UNSG32;
    typedef	signed long         SIGN32;
    typedef	unsigned long long  UNSG64;
    typedef	signed long long    SIGN64;
    typedef	float               REAL32;
    typedef	double              REAL64;

    #ifndef INLINE
	#define INLINE          static inline
    #endif

/*---------------------------------------------------------------------------
    GNU C/C++
  ---------------------------------------------------------------------------*/
#elif defined(__GNUC__)

    typedef	unsigned char       UNSG8;
    typedef	signed char         SIGN8;
    typedef	unsigned short      UNSG16;
    typedef	signed short        SIGN16;
    typedef	unsigned int        UNSG32;
    typedef	signed int          SIGN32;
    typedef	unsigned long long  UNSG64;
    typedef	signed long long    SIGN64;
    typedef	float               REAL32;
    typedef	double              REAL64;

    #ifndef INLINE
	#define INLINE          static inline
    #endif

#endif

/*---------------------------------------------------------------------------
    NULL
  ---------------------------------------------------------------------------*/

#ifndef NULL
    #ifdef __cplusplus
	#define NULL            0
    #else
	#define NULL            ((void *)0)
    #endif
#endif

/*---------------------------------------------------------------------------
    Multiple-word types
  ---------------------------------------------------------------------------*/
#ifndef	Txxb
	#define	Txxb
	typedef	UNSG8				T8b;
	typedef	UNSG16				T16b;
	typedef	UNSG32				T32b;
	typedef	UNSG32				T64b[2];
	typedef	UNSG32				T96b[3];
	typedef	UNSG32				T128b[4];
	typedef	UNSG32				T160b[5];
	typedef	UNSG32				T192b[6];
	typedef	UNSG32				T224b[7];
	typedef	UNSG32				T256b[8];
#endif

#endif
