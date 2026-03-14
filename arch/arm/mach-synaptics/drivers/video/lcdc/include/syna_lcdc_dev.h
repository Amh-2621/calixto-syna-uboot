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

#ifndef SYNA_LCDC_DEV_H
#define SYNA_LCDC_DEV_H

#include "bcmbuf.h"
#include "syna_lcdc_reg.h"
#include "vbuf.h"
#include "avioDhub.h"
#include "vdec_com.h"

#define SYNA_LCDC_INTF_TYPE_DPI	(SYNA_LCDC_TYPE_DPI_MCU | SYNA_LCDC_TYPE_DPI_RGB)
#define SYNA_LCDC_INTF_TYPE_DSI	(SYNA_LCDC_TYPE_DSI_CMD)

#define BCM_BUF_COUNT	0x2
#define BCM_BUFFER_SIZE	(4 * 1024)
#define DMA_CMD_BUFFER_SIZE	(256)

#define INT_FRAME_START	0x1
#define INT_FRAME_DONE	0x2
#define INT_UNDERRUN	0x4

#define SYNA_MEMMAP_AVIO_GBL_BASE	(MEMMAP_AVIO_REG_BASE + AVIO_MEMMAP_AVIO_GBL_BASE)

#define LCDC_CMD_SIZE	0xA
#define DSI_CMD_MODE_POS	14
#define DSI_WAIT_TE_POS	15

#define LCDC_DSI_CMD_MODE	(1 << DSI_CMD_MODE_POS)
#define LCDC_WAIT_FOR_TE	(1 << DSI_WAIT_TE_POS)

#define CURR_VBI_BCM_BUF	(&dev->bcmbuf[dev->bufferCurSet].vbi_bcm_buf)
#define CURR_VBI_DMA_CFGQ	(&(dev->bcmbuf[dev->bufferCurSet].vbi_cfgQ[SYNA_DHUB_CFGQ_TYPE_DMA]))
#define CURR_VBI_BCM_CFGQ	(&(dev->bcmbuf[dev->bufferCurSet].vbi_cfgQ[SYNA_DHUB_CFGQ_TYPE_BCM]))

#define INTR_CLEAR_WAIT_DELAY	10000
typedef enum SYNA_LCDC_ERROR_t {
	SYNA_LCDC_OK            = 0x0000,   /**< Success. */
	SYNA_LCDC_EBADPARAM     = 0x0001,   /**< Function parameter error. */
	SYNA_LCDC_ENOMEM        = 0x0002,   /**< Not enough memory. */
	SYNA_LCDC_EUNSUPPORT    = 0x0003,   /**< plane not connected in configuration*/
	SYNA_LCDC_ECMDQFULL     = 0x0004,   /**< Command Queue is full */
	SYNA_LCDC_EFRAMEQFULL   = 0x0005,   /**< Frame Queue is full */
	SYNA_LCDC_EBCMBUFFULL   = 0x0006,   /**< BCM Buffer is full */
	SYNA_LCDC_EVBIBUFFULL   = 0x0007   /**< VBI Buffer is full */
} SYNA_LCDC_ERROR;

enum syna_lcdc_pix_fmt {
	SYNA_LCDC_PIXFMT_ARGB32,
	SYNA_LCDC_PIXFMT_ARGB32_PM,
	SYNA_LCDC_PIXFMT_RGB565,
	SYNA_LCDC_PIXFMT_RGB888,
	SYNA_LCDC_PIXFMT_MAX
};

enum syna_lcdc_pix_order {
	SYNA_LCDC_PIXORDER_XRGB = 0,
	SYNA_LCDC_PIXORDER_XBGR = 1,
	SYNA_LCDC_PIXORDER_RGBX = 2,
	SYNA_LCDC_PIXORDER_BGRX = 3,
	SYNA_LCDC_PIXORDER_MAX
};

typedef enum syna_lcdc_interface_t_ {
	SYNA_LCDC_TYPE_DPI_RGB   = 0x1, /*TFT + DSI_VIDEO*/
	SYNA_LCDC_TYPE_DPI_MCU   = 0x2,
	SYNA_LCDC_TYPE_DSI_CMD   = 0x4
} syna_lcdc_interface_t;

typedef enum syna_lcdc_output_mode_t_ {
	SYNA_LCDC_MODE_0    = 0x0,
	SYNA_LCDC_MODE_1    = 0x1,
	SYNA_LCDC_MODE_2    = 0x2,
	SYNA_LCDC_MODE_3    = 0x3
} syna_lcdc_output_mode_t;

enum SYNA_LCDC_NUM {
	SYNA_LCDC_1 = 0,
	SYNA_LCDC_2 = 1,
	SYNA_LCDC_MAX = 2
};

typedef enum _SYNA_DHUB_CFGQ_TYPE_ {
	SYNA_DHUB_CFGQ_TYPE_DMA = 0x0,
	SYNA_DHUB_CFGQ_TYPE_BCM = 0x1,
	SYNA_DHUB_CFGQ_TYPE_MAX = 0x2
} SYNA_DHUB_CFGQ_TYPE;

typedef struct syna_lcdc_panel_t {
	unsigned char intf_type;     /*DPI TFT or CPU, DSI Video or CMD*/
	unsigned int bits_per_pixel; /*16, 18 or 24-bits per pixel*/
	unsigned char mode;      /*refer lcdc_output.xlsx*/
	unsigned char ext_te;    /*External tearing Effect*/
	unsigned int te_delay;
	unsigned char iclk;      /*lpclock polarity*/
	unsigned char rgb_swap;
	unsigned char rotation;      /*0, 90, 180, 270*/

	/*htotal = hsync_len + left_margin + xres + right_margin*/
	unsigned int hsync_len;
	unsigned int right_margin; //FP
	unsigned int xres;
	unsigned int left_margin;  //BP

	/*vtotal = vsync_len + upper_margin + yres + lower_margin*/
	unsigned int vsync_len;
	unsigned int lower_margin; //FP
	unsigned int yres;
	unsigned int upper_margin; //BP

	unsigned int refresh;
	/*htotal * vtotal * refresh*/
	unsigned int pixclock;

	/*htotal + hskip*/
	unsigned int hskip;
	/*vtotal + vskip*/
	unsigned int vskip;
} SYNA_LCDC_PANEL;

typedef struct _SYNA_BCMBUF_DATA_T_ {
	BCMBUF    vbi_bcm_buf;
	DHUB_CFGQ vbi_cfgQ[SYNA_DHUB_CFGQ_TYPE_MAX];   //O : DMA, 1: BCM
	void *vpp_mem_handle[SYNA_DHUB_CFGQ_TYPE_MAX];
} SYNA_BCMBUF_DATA;

struct syna_lcdc_dev {
	unsigned char lcdcID;     /*to identify the LCDC1 and LCDC2*/
	unsigned char bcm_enable; /* Use BCM engine or not for programming registers */
	unsigned char bcm_autopush_en;
	unsigned char en_intr_handler;
	unsigned int core_addr;
	struct syna_lcdc_panel_t *panel;

	VBUF_INFO *curr_frame; /*Slot for new frame*/
	VBUF_INFO *prev_frame;  /*Slot for current display frame*/
	int dmaRID;      /*DMA Read channel ID*/
	int dhubID;      /*DHUB channel handle*/
	int intrID;      /*Main interrupt*/
	int intrNo;      /*GIC interrupt number*/

	unsigned int interrupts;
	unsigned int underruns;
	unsigned int bufferCurSet;

	SYNA_BCMBUF_DATA bcmbuf[BCM_BUF_COUNT];

	BOOL    isTGConfig;
	unsigned int m_srcfmt;
	unsigned int m_order;
	unsigned int m_content_width;
	unsigned int m_content_height;
	unsigned int m_bits_per_pixel;
	unsigned char u8Gamma[33]; //GAMMA Table

//	struct semaphore vsync_sem;
	void   *vpp_mem_list;
};

typedef struct panel_info_t {
	unsigned int hact;
	unsigned int hfp;
	unsigned int hsa;
	unsigned int hbp;
	unsigned int vact;
	unsigned int vfp;
	unsigned int vsa;
	unsigned int vbp;
	unsigned int pixelclock;
	int      outformat;
	int      bpp;
	int      rgbswap;
} PANEL_TIMING_INFO;

typedef struct dsi_desc_t {
	int    byteclock;
	int    lpcmd;
	int    non_continuous_clock;
	int    lanes;
	int    eotp_tx;
	int    datapolarity;
	int    eotp_rx;
	int    h_polarity;
	int    v_polarity;
	int    data_polarity;
	int    cmdsize;
	int    htotal;
	int    video_mode;
	int    receive_ack;
	int    is_18_loose;
	int    color_coding;
	int    chunks;
	int    null_pkt;
	unsigned int cmdbufferSize;
	unsigned char  *pcmd;
} SYNA_DSI_DESC;

typedef enum {
	DISPLAY_TYPE_TFT,
	DISPLAY_TYPE_DSI,
	DISPLAY_TYPE_MAX
} ENUM_DISPLAY_TYPE;

struct lcdc_config {
	struct mipi_dsi_dev *dsi_dev;
	unsigned int    irqno;
	BOOL   is_dev_avail[DISPLAY_TYPE_MAX];
	SYNA_DSI_DESC synaDsiInfo;
	PANEL_TIMING_INFO pTimingInfo[DISPLAY_TYPE_MAX];
};

extern HDL_dhub2d VPP_dhubHandle;
extern HDL_dhub2d AG_dhubHandle;

unsigned long syna_lcdc_readl(struct syna_lcdc_dev *dev, unsigned long addr);
void syna_lcdc_writel(struct syna_lcdc_dev *dev, unsigned long addr, unsigned long val);
int syna_lcdc_pushframe(int planeID, void *pnew);
int syna_lcdc_dlr_create(struct syna_lcdc_dev *dev, int num);
void syna_lcdc_dlr_handler(struct syna_lcdc_dev *dev);
void syna_bcmbuf_flip(struct syna_lcdc_dev *dev);
void syna_bcmbuf_submit(struct syna_lcdc_dev *dev, int use_vbi);
void syna_lcdc_irq(int intrMask);
int syna_lcdc_waitVsync(int lcdcId);
void syna_lcdc_releaseVsync(int lcdcId);
void syna_lcdc_hw_config(int lcdcID, SYNA_LCDC_PANEL *panel);
void syna_lcdc_dlr_destroy(struct syna_lcdc_dev *dev);
void syna_lcdc_clear_disable_interrupts(void);
int drv_lcdc_init(void *ctxt);

#endif
