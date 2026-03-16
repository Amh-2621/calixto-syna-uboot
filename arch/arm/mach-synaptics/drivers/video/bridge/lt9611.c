// SPDX-License-Identifier: GPL-2.0
/*
 * Copyright (c) 2019-2020. Linaro Limited.
 */
/*
 * Copyright (C) 2016~2025 Synaptics Incorporated. All rights reserved.
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

#include <common.h>
#include <dm.h>
#include <errno.h>
#include <i2c.h>
#include <video_bridge.h>
#include <power/regulator.h>
#include "videomodes.h"
#include "lt9611.h"

#define EDID_SEG_SIZE	256
#define EDID_LEN	32
#define EDID_LOOP	8
#define KEY_DDC_ACCS_DONE 0x02
#define DDC_NO_ACK	0x50

#define LT9611_4LANES	0

#define LT9611_WRITE_BYTE(dev, off, pdata)	{\
				u8 buf = (off & 0xFF00) >> 8 ;\
				dm_i2c_write(dev, 0xFF, &buf, 1); \
				dm_i2c_write(dev, off & 0xFF, pdata, 1);\
			}

struct lt9611 {
	struct udevice *dev;
	struct regmap *regmap;
	u8 ac_mode;
	u8 power_on;
	u8 sleep;
	struct i2c_client *client;
	u32 vic;

	struct gpio_desc reset_gpio;
	struct gpio_desc enable_gpio;
};

#define LT9611_PAGE_CONTROL	0xff

struct lt9611_mode {
	u16 hdisplay;
	u16 vdisplay;
	u8 vrefresh;
	u8 lanes;
	u8 intfs;
};

struct lt9611 stlt9611;

static void lt9611_power_on(struct udevice *dev)
{
	uint8_t data;

	/* LT9611_System_Init */
	data = 0x18;
	LT9611_WRITE_BYTE(dev, 0x8101, &data); /* sel xtal clock */

	/* timer for frequency meter */
	data = 0x69;
	LT9611_WRITE_BYTE(dev, 0x821b, &data); /* timer 2 */

	data = 0x78;
	LT9611_WRITE_BYTE(dev, 0x821c, &data);

	data = 0x69;
	LT9611_WRITE_BYTE(dev, 0x82cb, &data); /* timer 1 */

	data = 0x78;
	LT9611_WRITE_BYTE(dev, 0x82cc, &data);

	/* irq init */
	data = 0x01;
	LT9611_WRITE_BYTE(dev, 0x8251, &data);

	/* power consumption for work */
	data = 0xf0;
	LT9611_WRITE_BYTE(dev, 0x8004, &data);

	data = 0xf0;
	LT9611_WRITE_BYTE(dev, 0x8006, &data);

	data = 0x80;
	LT9611_WRITE_BYTE(dev, 0x800a, &data);

	data = 0x40;
	LT9611_WRITE_BYTE(dev, 0x800b, &data);

	data = 0xef;
	LT9611_WRITE_BYTE(dev, 0x800d, &data);

	data = 0xfa;
	LT9611_WRITE_BYTE(dev, 0x8011, &data);
}

static void lt9611_mipi_input_analog(struct udevice *dev)
{
	uint8_t data;

	data = 0x60;
	LT9611_WRITE_BYTE(dev, 0x8106, &data);  /* port A rx current */

	data = 0xfe;
	LT9611_WRITE_BYTE(dev, 0x810a, &data);  /* port A ldo voltage set */

	data = 0xbf;
	LT9611_WRITE_BYTE(dev, 0x810b, &data);  /* enable port A lprx */

	data = 0x40;
	LT9611_WRITE_BYTE(dev, 0x8111, &data);  /* port B rx current */

	data = 0xfe;
	LT9611_WRITE_BYTE(dev, 0x8115, &data);  /* port B ldo voltage set */

	data = 0xbf;
	LT9611_WRITE_BYTE(dev, 0x8116, &data);  /* enable port B lprx */

	data = 0x03;
	LT9611_WRITE_BYTE(dev, 0x811c, &data);  /* PortA clk lane no-LP mode */

	data = 0x03;
	LT9611_WRITE_BYTE(dev, 0x8120, &data);  /* PortB clk lane with-LP mode */
}

static void lt9611_hdmi_tx_digital(struct lt9611 *lt9611)
{
	uint8_t data;
	struct udevice *dev = lt9611->dev;

	data = 0x46 - lt9611->vic;
	LT9611_WRITE_BYTE(dev, 0x8443, &data);

	data = lt9611->vic;
	LT9611_WRITE_BYTE(dev, 0x8447, &data);

	data = 0x0A;
	LT9611_WRITE_BYTE(dev, 0x843d, &data); /* UD1 infoframe */

	data = 0x8c;
	LT9611_WRITE_BYTE(dev, 0x82d6, &data);

	data = 0x04;
	LT9611_WRITE_BYTE(dev, 0x82d7, &data);
}

static void lt9611_hdmi_tx_phy(struct lt9611 *lt9611)
{
	uint8_t data;
	struct udevice *dev = lt9611->dev;

	data = 0x6a;
	LT9611_WRITE_BYTE(dev, 0x8130, &data);

	data = 0x44;
	LT9611_WRITE_BYTE(dev, 0x8131, &data); /* HDMI DC mode */

	data = 0x4a;
	LT9611_WRITE_BYTE(dev, 0x8132, &data);

	data = 0x0b;
	LT9611_WRITE_BYTE(dev, 0x8133, &data);

	data = 0x00;
	LT9611_WRITE_BYTE(dev, 0x8134, &data);

	data = 0x00;
	LT9611_WRITE_BYTE(dev, 0x8135, &data);

	data = 0x00;
	LT9611_WRITE_BYTE(dev, 0x8136, &data);

	data = 0x44;
	LT9611_WRITE_BYTE(dev, 0x8137, &data);

	data = 0x0f;
	LT9611_WRITE_BYTE(dev, 0x813f, &data);

	data = 0xa0;
	LT9611_WRITE_BYTE(dev, 0x8140, &data);

	data = 0xa0;
	LT9611_WRITE_BYTE(dev, 0x8141, &data);

	data = 0xa0;
	LT9611_WRITE_BYTE(dev, 0x8142, &data);

	data = 0xa0;
	LT9611_WRITE_BYTE(dev, 0x8143, &data);

	data = 0x0a;
	LT9611_WRITE_BYTE(dev, 0x8144, &data);
}

static int lt9611_mipi_input_digital(struct udevice *dev,
				     const struct ctfb_res_modes *mode)
{
	uint8_t data;

	data = LT9611_4LANES;
	LT9611_WRITE_BYTE(dev, 0x8300, &data);

	data = (mode->xres == 3840) ? 0x03 : 0x00;
	LT9611_WRITE_BYTE(dev, 0x830a, &data);

	data = 0x80;
	LT9611_WRITE_BYTE(dev, 0x824f, &data);

	data = 0x10;
	LT9611_WRITE_BYTE(dev, 0x8250, &data);

	data = 0x0a;
	LT9611_WRITE_BYTE(dev, 0x8302, &data);

	data = 0x0a;
	LT9611_WRITE_BYTE(dev, 0x8306, &data);

	return 0;
}

static void lt9611_mipi_video_setup(struct udevice *dev,
				    const struct ctfb_res_modes *mode)
{
	uint8_t data;
	u32 h_total, hactive, hsync_len, hfront_porch, hsync_porch;
	u32 v_total, vactive, vsync_len, vfront_porch, vsync_porch;

	h_total = mode->xres + mode->left_margin + mode->right_margin + mode->hsync_len;
	v_total = mode->yres + mode->upper_margin + mode->lower_margin + mode->vsync_len;

	hactive = mode->xres;
	hsync_len = mode->hsync_len;
	hfront_porch = mode->left_margin;
	hsync_porch = hsync_len + mode->right_margin ;

	vactive = mode->yres;
	vsync_len = mode->vsync_len;
	vfront_porch = mode->upper_margin;
	vsync_porch =  vsync_len + mode->lower_margin;

	data = (u8)(v_total / 256);
	LT9611_WRITE_BYTE(dev, 0x830d, &data);

	data = (u8)(v_total % 256);
	LT9611_WRITE_BYTE(dev, 0x830e, &data);

	data = (u8)(vactive / 256);
	LT9611_WRITE_BYTE(dev, 0x830f, &data);

	data = (u8)(vactive % 256);
	LT9611_WRITE_BYTE(dev, 0x8310, &data);

	data = (u8)(h_total / 256);
	LT9611_WRITE_BYTE(dev, 0x8311, &data);

	data = (u8)(h_total % 256);
	LT9611_WRITE_BYTE(dev, 0x8312, &data);

	data = (u8)(hactive / 256);
	LT9611_WRITE_BYTE(dev, 0x8313, &data);

	data = (u8)(hactive % 256);
	LT9611_WRITE_BYTE(dev, 0x8314, &data);

	data = (u8)(vsync_len % 256);
	LT9611_WRITE_BYTE(dev, 0x8315, &data);

	data = (u8)(hsync_len % 256);
	LT9611_WRITE_BYTE(dev, 0x8316, &data);

	data = (u8)(vfront_porch % 256);
	LT9611_WRITE_BYTE(dev, 0x8317, &data);

	data = (u8)(vsync_porch % 256);
	LT9611_WRITE_BYTE(dev, 0x8318, &data);

	data = (u8)(hfront_porch % 256);
	LT9611_WRITE_BYTE(dev, 0x8319, &data);

	data = (u8)(hsync_porch / 256);
	LT9611_WRITE_BYTE(dev, 0x831a, &data);

	data = (u8)(hsync_porch % 256);
	LT9611_WRITE_BYTE(dev, 0x831b, &data);
}

static void lt9611_pll_setup(struct udevice *dev, const struct ctfb_res_modes *mode)
{
	unsigned int pclk = mode->pixclock_khz;
	uint8_t data;

	data = 0x40;
	LT9611_WRITE_BYTE(dev, 0x8123, &data);

	data = 0x64;
	LT9611_WRITE_BYTE(dev, 0x8124, &data);

	data = 0x80;
	LT9611_WRITE_BYTE(dev, 0x8125, &data);

	data = 0x55;
	LT9611_WRITE_BYTE(dev, 0x8126, &data);

	data = 0x37;
	LT9611_WRITE_BYTE(dev, 0x812c, &data);

	data = 0x01;
	LT9611_WRITE_BYTE(dev, 0x812f, &data);

	data = 0x55;
	LT9611_WRITE_BYTE(dev, 0x8126, &data);

	data = 0x66;
	LT9611_WRITE_BYTE(dev, 0x8127, &data);

	data = 0x88;
	LT9611_WRITE_BYTE(dev, 0x8128, &data);

	data = 0x20;
	LT9611_WRITE_BYTE(dev, 0x812a, &data);

	if (pclk > 150000)
		data = 0x88;
	else if (pclk > 70000)
		data = 0x99;
	else
		data = 0xaa;

	LT9611_WRITE_BYTE(dev, 0x812d, &data);

	/*
	 * first divide pclk by 2 first
	 *  - write divide by 64k to 19:16 bits which means shift by 17
	 *  - write divide by 256 to 15:8 bits which means shift by 9
	 *  - write remainder to 7:0 bits, which means shift by 1
	 */
	data = pclk >> 17;
	LT9611_WRITE_BYTE(dev, 0x82e3, &data); /* pclk[19:16] */

	data = pclk >> 9;
	LT9611_WRITE_BYTE(dev, 0x82e4, &data); /* pclk[15:8]  */

	data = pclk >> 1;
	LT9611_WRITE_BYTE(dev, 0x82e5, &data); /* pclk[7:0]   */

	data = 0x20;
	LT9611_WRITE_BYTE(dev, 0x82de, &data);

	data = 0xe0;
	LT9611_WRITE_BYTE(dev, 0x82de, &data);

	data = 0xf1;
	LT9611_WRITE_BYTE(dev, 0x8016, &data);

	data = 0xf3;
	LT9611_WRITE_BYTE(dev, 0x8016, &data);

	return;
}

static void lt9611_pcr_setup(struct udevice *dev, const struct ctfb_res_modes *mode)
{
	uint8_t data;

	data = 0x01;
	LT9611_WRITE_BYTE(dev, 0x830b, &data);

	data = 0x10;
	LT9611_WRITE_BYTE(dev, 0x830c, &data);

	data = 0x00;
	LT9611_WRITE_BYTE(dev, 0x8348, &data);

	data = 0x81;
	LT9611_WRITE_BYTE(dev, 0x8349, &data);

	data = 0x4a;
	LT9611_WRITE_BYTE(dev, 0x8321, &data);

	data = 0x71;
	LT9611_WRITE_BYTE(dev, 0x8324, &data);

	data = 0x30;
	LT9611_WRITE_BYTE(dev, 0x8325, &data);

	data = 0x01;
	LT9611_WRITE_BYTE(dev, 0x832a, &data);

	data = 0x40;
	LT9611_WRITE_BYTE(dev, 0x834a, &data);

	data = 0x10;
	LT9611_WRITE_BYTE(dev, 0x831d, &data);

	data = 0x38;
	LT9611_WRITE_BYTE(dev, 0x832d, &data);

	data = 0x08;
	LT9611_WRITE_BYTE(dev, 0x8331, &data);

	switch (mode->xres) {
	case 640:
		data = 0x14;
		LT9611_WRITE_BYTE(dev, 0x8326, &data);
		break;
	case 1920:
		data = 0x37;
		LT9611_WRITE_BYTE(dev, 0x8326, &data);
		break;
	case 3840:
		data = 0x03;
		LT9611_WRITE_BYTE(dev, 0x830b, &data);

		data = 0xd0;
		LT9611_WRITE_BYTE(dev, 0x830c, &data);

		data = 0x03;
		LT9611_WRITE_BYTE(dev, 0x8348, &data);

		data = 0xe0;
		LT9611_WRITE_BYTE(dev, 0x8349, &data);

		data = 0x72;
		LT9611_WRITE_BYTE(dev, 0x8324, &data);

		data = 0x00;
		LT9611_WRITE_BYTE(dev, 0x8325, &data);

		data = 0x01;
		LT9611_WRITE_BYTE(dev, 0x832a, &data);

		data = 0x10;
		LT9611_WRITE_BYTE(dev, 0x834a, &data);

		data = 0x10;
		LT9611_WRITE_BYTE(dev, 0x831d, &data);

		data = 0x37;
		LT9611_WRITE_BYTE(dev, 0x8326, &data);

		break;
	}

	/* pcr rst */
	data = 0x5a;
	LT9611_WRITE_BYTE(dev, 0x8011, &data);

	data = 0xfa;
	LT9611_WRITE_BYTE(dev, 0x8011, &data);
}

static int lt9611_ofdata_to_platdata(struct udevice *dev)
{
	return 0;
}

static int lt9611_bind(struct udevice *dev)
{
	return 0;
}

static int lt9611_probe(struct udevice *dev)
{
	int ret = 0;
	uint8_t data;

	gpio_request_by_name(dev, "enable-gpio", 0, &stlt9611.enable_gpio,
					GPIOD_IS_OUT);

	dm_gpio_set_value(&stlt9611.enable_gpio, 1);

	stlt9611.dev = dev;
	data = 0x1;
	LT9611_WRITE_BYTE(dev, 0x80ee, &data);
	lt9611_power_on(dev);
	lt9611_mipi_input_analog(dev);
	lt9611_hdmi_tx_digital(&stlt9611);
	lt9611_hdmi_tx_phy(&stlt9611);

	/* Enable HDMI output */
	data = 0xea;
	LT9611_WRITE_BYTE(dev, 0x8130, &data);

	return ret;
}

void lt9611_bridge_modeset(struct udevice *dev,
				struct ctfb_res_modes *mode)
{
	uint8_t data;

	switch (mode->yres) {
	case 1080:
		stlt9611.vic = 16;
		break;
	default:
		printf("Resolution not supported\n");
		return;
	}

	data = 0x01;
	LT9611_WRITE_BYTE(dev, 0x80ee, &data);

	lt9611_mipi_input_digital(dev, mode);
	lt9611_pll_setup(dev, mode);
	lt9611_mipi_video_setup(dev, mode);
	lt9611_pcr_setup(dev, mode);
}

static const struct udevice_id lt9611_match_table[] = {
	{ .compatible = "syna-bridge,lt9611" },
	{ }
};

static int lt9611_attach(struct udevice *dev)
{
	return 0;
}

struct video_bridge_ops lt9611_ops = {
	.attach = lt9611_attach,
};

U_BOOT_DRIVER(lt9611) = {
	.name	= "lt9611",
	.id	= UCLASS_VIDEO_BRIDGE,
	.of_match = lt9611_match_table,
	.ofdata_to_platdata = &lt9611_ofdata_to_platdata,
	.bind = lt9611_bind,
	.probe	= lt9611_probe,
	.ops	= &lt9611_ops,
};
