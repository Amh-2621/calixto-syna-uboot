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

#ifndef	_IMAGE_2_IO_H
#define	_IMAGE_2_IO_H


#define __raw_writeb(v,a)   (*(volatile unsigned char *)(a) = (v))
#define __raw_writew(v,a)   (*(volatile unsigned short *)(a) = (v))
#define __raw_writel(v,a)   (*(volatile unsigned int *)(a) = (v))

#define __raw_readb(a)      (*(volatile unsigned char *)(a))
#define __raw_readw(a)      (*(volatile unsigned short *)(a))
#define __raw_readl(a)      (*(volatile unsigned int *)(a))


#define writeb	__raw_writeb
#define writew	__raw_writew
#define writel	__raw_writel

#define readb	__raw_readb
#define	readw	__raw_readw
#define	readl	__raw_readl

#ifndef BFM_HOST_Bus_Write32
#define BFM_HOST_Bus_Write32(offset, val)	((*(volatile unsigned int*)(offset))=val)
#endif

#ifndef BFM_HOST_Bus_Read32
#define BFM_HOST_Bus_Read32(offset, holder)	((*(volatile unsigned int*)(holder))=(*(volatile unsigned int*)(offset)))
#endif

#define	MV_BYTE_SWAP_16BIT(X)	((((X) & 0xff) << 8) | (((X) & 0xff00) >> 8))
#define	MV_BYTE_SWAP_32BIT(X)	((((X) & 0xff) << 24) | (((X) & 0xff00) << 8) | (((X) & 0xff0000) >> 8) | (((X) & 0xff000000) >> 24))
#define	MV_BYTE_SWAP_64BIT(X)	((MV_U64) ((((X) & 0xffULL) << 56) | (((X) & 0xff00ULL) << 40) |			\
				(((X) & 0xff0000ULL) << 24) | (((X) & 0xff000000ULL) << 8) |				\
				(((X) & 0xff00000000ULL) >> 8) | (((X) & 0xff0000000000ULL) >> 24) |			\
				(((X) & 0xff000000000000ULL) >> 40) | (((X) & 0xff00000000000000ULL) >> 56)))


#define __LITTLE_ENDIAN1		1
#if	(defined(__BIG_ENDIAN))
#	define	MV_16BIT_LE(X)		MV_BYTE_SWAP_16BIT(X)
#	define	MV_32BIT_LE(X)		MV_BYTE_SWAP_32BIT(X)
#	define	MV_64BIT_LE(X)		MV_BYTE_SWAP_64BIT(X)
#	define	MV_16BIT_BE(X)		(X)
#	define	MV_32BIT_BE(X)		(X)
#	define	MV_64BIT_BE(X)		(X)

#elif	(defined(__LITTLE_ENDIAN1))
#	define	MV_16BIT_LE(X)		(X)
#	define	MV_32BIT_LE(X)		(X)
#	define	MV_64BIT_LE(X)		(X)
#	define	MV_16BIT_BE(X)		MV_BYTE_SWAP_16BIT(X)
#	define	MV_32BIT_BE(X)		MV_BYTE_SWAP_32BIT(X)
#	define	MV_64BIT_BE(X)		MV_BYTE_SWAP_64BIT(X)
#endif

#define	MV_32BIT_LE_FAST(val)			MV_32BIT_LE(val)
#define	MV_16BIT_LE_FAST(val)			MV_16BIT_LE(val)
#define	MV_32BIT_BE_FAST(val)			MV_32BIT_BE(val)
#define	MV_16BIT_BE_FAST(val)			MV_16BIT_BE(val)


#define	MV_MEMIO_LE16_WRITE(addr, data)	writew(addr, MV_16BIT_LE_FAST(data))
#define	MV_MEMIO_LE16_READ(addr)		MV_16BIT_LE_FAST(readw(addr))
#define	MV_MEMIO_LE32_WRITE(addr, data)	writel(addr, MV_32BIT_LE_FAST(data))
#define	MV_MEMIO_LE32_READ(addr)		MV_32BIT_LE_FAST(readl(addr))

#define GA_REG_WORD32_READ(addr, holder) 	(*(holder) = ((*((volatile unsigned int*)(uintptr_t)(addr)))))
#define GA_REG_WORD32_WRITE(addr, data)		((*((volatile unsigned int*)(uintptr_t)(addr))) = ((unsigned int)(data)))

#endif
