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

#ifndef __PINCTRL_SYNA_DOLPHIN_H
#define __PINCTRL_SYNA_DOLPHIN_H

#include <dm/device.h>
#include <dm/pinctrl.h>

#include "pinctrl_syna.h"

static const struct syna_desc_group dolphin_soc_pinctrl_groups[] = {
	SYNA_PINCTRL_GROUP("SDIO_CDn", 0x0, 0x3, 0x00,
			   SYNA_PINCTRL_FUNC(0x0, "sdio"), /* CDn */
			SYNA_PINCTRL_FUNC(0x1, "gpio"), /* GPIO45 */
			SYNA_PINCTRL_FUNC(0x2, "tw1")), /* SCL */
	SYNA_PINCTRL_GROUP("SDIO_WP", 0x0, 0x3, 0x03,
			   SYNA_PINCTRL_FUNC(0x0, "sdio"), /* WP */
			SYNA_PINCTRL_FUNC(0x1, "gpio"), /* GPIO44 */
			SYNA_PINCTRL_FUNC(0x2, "tw1")), /* SDA */
	SYNA_PINCTRL_GROUP("SPI1_SS0n", 0x0, 0x3, 0x06,
			   SYNA_PINCTRL_FUNC(0x0, "spi1"), /* SS0n */
			SYNA_PINCTRL_FUNC(0x1, "gpio")), /* GPIO54 */
	SYNA_PINCTRL_GROUP("SPI1_SS1n", 0x0, 0x3, 0x09,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO53 */
			SYNA_PINCTRL_FUNC(0x1, "spi1"), /* SS1n */
			SYNA_PINCTRL_FUNC(0x4, "pwm"), /* PWM1 */
			SYNA_PINCTRL_FUNC(0x7, "phy")), /* DBG14 */
	SYNA_PINCTRL_GROUP("SPI1_SS2n", 0x0, 0x3, 0x0c,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO52 */
			SYNA_PINCTRL_FUNC(0x1, "spi1"), /* SS2n */
			SYNA_PINCTRL_FUNC(0x2, "sts7"), /* CLK */
			SYNA_PINCTRL_FUNC(0x4, "pwm"), /* PWM0 */
			SYNA_PINCTRL_FUNC(0x7, "phy")), /* DBG12 */
	SYNA_PINCTRL_GROUP("SPI1_SS3n", 0x0, 0x3, 0x0f,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO51 */
			SYNA_PINCTRL_FUNC(0x1, "spi1"), /* SS3n */
			SYNA_PINCTRL_FUNC(0x2, "sts7"), /* SD */
			SYNA_PINCTRL_FUNC(0x7, "phy")), /* DBG13 */
	SYNA_PINCTRL_GROUP("SPI1_SDO", 0x0, 0x3, 0x12,
			   SYNA_PINCTRL_FUNC(0x0, "spi1"), /* SDO */
			SYNA_PINCTRL_FUNC(0x1, "gpio")), /* GPIO50 */
	SYNA_PINCTRL_GROUP("SPI1_SCLK", 0x0, 0x3, 0x15,
			   SYNA_PINCTRL_FUNC(0x0, "spi1"), /* SCLK */
			SYNA_PINCTRL_FUNC(0x1, "gpio")), /* GPIO49 */
	SYNA_PINCTRL_GROUP("SPI1_SDI", 0x0, 0x3, 0x18,
			   SYNA_PINCTRL_FUNC(0x0, "spi1"), /* SDI */
			SYNA_PINCTRL_FUNC(0x1, "gpio")), /* GPIO48 */
	SYNA_PINCTRL_GROUP("TW0_SCL", 0x0, 0x3, 0x1b,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO47 */
			SYNA_PINCTRL_FUNC(0x1, "tw0"), /* SCL */
			SYNA_PINCTRL_FUNC(0x7, "phy")), /* DBG10 */
	SYNA_PINCTRL_GROUP("TW0_SDA", 0x4, 0x3, 0x00,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO46 */
			SYNA_PINCTRL_FUNC(0x1, "tw0"), /* SDA */
			SYNA_PINCTRL_FUNC(0x7, "phy")), /* DBG11 */
	SYNA_PINCTRL_GROUP("STS0_CLK", 0x4, 0x3, 0x03,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO43 */
			SYNA_PINCTRL_FUNC(0x1, "sts0"), /* CLK */
			SYNA_PINCTRL_FUNC(0x2, "cpupll"), /* CLKO */
			SYNA_PINCTRL_FUNC(0x4, "uart3"), /* RXD */
			SYNA_PINCTRL_FUNC(0x7, "phy")), /* DBG0 */
	SYNA_PINCTRL_GROUP("STS0_SOP", 0x4, 0x3, 0x06,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO42 */
			SYNA_PINCTRL_FUNC(0x1, "sts0"), /* SOP */
			SYNA_PINCTRL_FUNC(0x2, "syspll"), /* CLKO */
			SYNA_PINCTRL_FUNC(0x3, "sts5"), /* CLK */
			SYNA_PINCTRL_FUNC(0x4, "uart3"), /* TXD */
			SYNA_PINCTRL_FUNC(0x7, "phy")), /* DBG1 */
	SYNA_PINCTRL_GROUP("STS0_SD", 0x4, 0x3, 0x09,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO41 */
			SYNA_PINCTRL_FUNC(0x1, "sts0"), /* SD */
			SYNA_PINCTRL_FUNC(0x2, "mempll"), /* CLKO */
			SYNA_PINCTRL_FUNC(0x4, "uart3"), /* CTSn */
			SYNA_PINCTRL_FUNC(0x7, "phy")), /* DBG2 */
	SYNA_PINCTRL_GROUP("STS0_VALD", 0x4, 0x3, 0x0c,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO40 */
			SYNA_PINCTRL_FUNC(0x1, "sts0"), /* VALD */
			SYNA_PINCTRL_FUNC(0x3, "sts5"), /* SD */
			SYNA_PINCTRL_FUNC(0x4, "uart3"), /* RTSn */
			SYNA_PINCTRL_FUNC(0x7, "phy")), /* DBG3 */
	SYNA_PINCTRL_GROUP("STS1_CLK", 0x4, 0x3, 0x0f,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO39 */
			SYNA_PINCTRL_FUNC(0x1, "sts1"), /* CLK */
			SYNA_PINCTRL_FUNC(0x2, "pwm"), /* pwm0 */
			SYNA_PINCTRL_FUNC(0x7, "phy")), /* DBG4 */
	SYNA_PINCTRL_GROUP("STS1_SOP", 0x4, 0x3, 0x12,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO38 */
			SYNA_PINCTRL_FUNC(0x1, "sts1"), /* SOP */
			SYNA_PINCTRL_FUNC(0x2, "pwm"), /* PWM1 */
			SYNA_PINCTRL_FUNC(0x3, "sts6"), /* CLK */
			SYNA_PINCTRL_FUNC(0x7, "phy")), /* DBG5 */
	SYNA_PINCTRL_GROUP("STS1_SD", 0x4, 0x3, 0x15,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO37 */
			SYNA_PINCTRL_FUNC(0x1, "sts1"), /* SD */
			SYNA_PINCTRL_FUNC(0x2, "pwm"), /* PWM2 */
			SYNA_PINCTRL_FUNC(0x7, "phy")), /* DBG6 */
	SYNA_PINCTRL_GROUP("STS1_VALD", 0x4, 0x3, 0x18,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO36 */
			SYNA_PINCTRL_FUNC(0x1, "sts1"), /* VALD */
			SYNA_PINCTRL_FUNC(0x2, "pwm"), /* PWM3 */
			SYNA_PINCTRL_FUNC(0x3, "sts6"), /* SD */
			SYNA_PINCTRL_FUNC(0x7, "phy")), /* DBG7 */
	SYNA_PINCTRL_GROUP("USB2_DRV_VBUS", 0x4, 0x3, 0x1b,
			   SYNA_PINCTRL_FUNC(0x0, "usb2"), /* VBUS */
			SYNA_PINCTRL_FUNC(0x1, "gpio")), /* GPIO55 */
	SYNA_PINCTRL_GROUP("RGMII_MDC", 0x8, 0x3, 0x00,
			   SYNA_PINCTRL_FUNC(0x0, "rgmii"), /* MDC */
			SYNA_PINCTRL_FUNC(0x1, "gpio"), /* GPIO29 */
			SYNA_PINCTRL_FUNC(0x7, "phy")), /* DBG8 */
	SYNA_PINCTRL_GROUP("RGMII_MDIO", 0x8, 0x3, 0x03,
			   SYNA_PINCTRL_FUNC(0x0, "rgmii"), /* MDIO */
			SYNA_PINCTRL_FUNC(0x1, "gpio"), /* GPIO28 */
			SYNA_PINCTRL_FUNC(0x7, "phy")), /* DBG9 */
	SYNA_PINCTRL_GROUP("RGMII_TXC", 0x8, 0x3, 0x06,
			   SYNA_PINCTRL_FUNC(0x0, "rgmii"), /* TXC */
			SYNA_PINCTRL_FUNC(0x1, "gpio")), /* GPIO23 */
	SYNA_PINCTRL_GROUP("RGMII_TXD0", 0x8, 0x3, 0x09,
			   SYNA_PINCTRL_FUNC(0x0, "rgmii"), /* TXD0 */
			SYNA_PINCTRL_FUNC(0x1, "gpio")), /* GPIO27 */
	SYNA_PINCTRL_GROUP("RGMII_TXD1", 0x8, 0x3, 0x0c,
			   SYNA_PINCTRL_FUNC(0x0, "rgmii"), /* TXD1 */
			SYNA_PINCTRL_FUNC(0x1, "gpio"), /* GPIO26 */
			SYNA_PINCTRL_FUNC(0x7, "phy")), /* DBG15 */
	SYNA_PINCTRL_GROUP("RGMII_TXD2", 0x8, 0x3, 0x0f,
			   SYNA_PINCTRL_FUNC(0x0, "rgmii"), /* TXD2 */
			SYNA_PINCTRL_FUNC(0x1, "gpio")), /* GPIO25 */
	SYNA_PINCTRL_GROUP("RGMII_TXD3", 0x8, 0x3, 0x12,
			   SYNA_PINCTRL_FUNC(0x0, "rgmii"), /* TXD3 */
			SYNA_PINCTRL_FUNC(0x1, "gpio")), /* GPIO24 */
	SYNA_PINCTRL_GROUP("RGMII_TXCTL", 0x8, 0x3, 0x15,
			   SYNA_PINCTRL_FUNC(0x0, "rgmii"), /* TXCTL */
			SYNA_PINCTRL_FUNC(0x1, "gpio")), /* GPIO22 */
	SYNA_PINCTRL_GROUP("RGMII_RXC", 0x8, 0x3, 0x18,
			   SYNA_PINCTRL_FUNC(0x0, "rgmii"), /* RXC */
			SYNA_PINCTRL_FUNC(0x1, "gpio")), /* GPIO31 */
	SYNA_PINCTRL_GROUP("RGMII_RXD0", 0x8, 0x3, 0x1b,
			   SYNA_PINCTRL_FUNC(0x0, "rgmii"), /* RXD0 */
			SYNA_PINCTRL_FUNC(0x1, "gpio")), /* GPIO35 */
	SYNA_PINCTRL_GROUP("RGMII_RXD1", 0xc, 0x3, 0x00,
			   SYNA_PINCTRL_FUNC(0x0, "rgmii"), /* RXD1 */
			SYNA_PINCTRL_FUNC(0x1, "gpio")), /* GPIO34 */
	SYNA_PINCTRL_GROUP("RGMII_RXD2", 0xc, 0x3, 0x03,
			   SYNA_PINCTRL_FUNC(0x0, "rgmii"), /* RXD2 */
			SYNA_PINCTRL_FUNC(0x1, "gpio")), /* GPIO33 */
	SYNA_PINCTRL_GROUP("RGMII_RXD3", 0xc, 0x3, 0x06,
			   SYNA_PINCTRL_FUNC(0x0, "rgmii"), /* RXD3 */
			SYNA_PINCTRL_FUNC(0x1, "gpio")), /* GPIO32 */
	SYNA_PINCTRL_GROUP("RGMII_RXCTL", 0xc, 0x3, 0x09,
			   SYNA_PINCTRL_FUNC(0x0, "rgmii"), /* RXCTL */
			SYNA_PINCTRL_FUNC(0x1, "gpio")), /* GPIO30 */
};

static const struct syna_desc_group dolphin_avio_pinctrl_groups[] = {
	SYNA_PINCTRL_GROUP("I2S1_DO0", 0x0, 0x3, 0x00,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO19 */
			SYNA_PINCTRL_FUNC(0x1, "i2s1"), /* DO0 */
			SYNA_PINCTRL_FUNC(0x7, "avio")), /* DBG4 */
	SYNA_PINCTRL_GROUP("I2S1_DO1", 0x0, 0x3, 0x03,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO17 */
			SYNA_PINCTRL_FUNC(0x1, "i2s1"), /* DO1 */
			SYNA_PINCTRL_FUNC(0x3, "sts2"), /* CLK */
			SYNA_PINCTRL_FUNC(0x7, "avio")), /* DBG5 */
	SYNA_PINCTRL_GROUP("I2S1_DO2", 0x0, 0x3, 0x06,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO16 */
			SYNA_PINCTRL_FUNC(0x1, "i2s1"), /* DO2 */
			SYNA_PINCTRL_FUNC(0x2, "pwm"), /* PWM2 */
			SYNA_PINCTRL_FUNC(0x3, "sts2"), /* SD */
			SYNA_PINCTRL_FUNC(0x4, "pdm"), /* DI2 */
			SYNA_PINCTRL_FUNC(0x7, "avio")), /* DBG6 */
	SYNA_PINCTRL_GROUP("I2S1_DO3", 0x0, 0x3, 0x09,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO15 */
			SYNA_PINCTRL_FUNC(0x1, "i2s1"), /* DO3 */
			SYNA_PINCTRL_FUNC(0x2, "pwm"), /* PWM3 */
			SYNA_PINCTRL_FUNC(0x3, "sts3"), /* CLK */
			SYNA_PINCTRL_FUNC(0x4, "pdm"), /* DI3 */
			SYNA_PINCTRL_FUNC(0x7, "avio")), /* DBG7 */
	SYNA_PINCTRL_GROUP("I2S1_LRCKIO", 0x0, 0x3, 0x0c,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO21 */
			SYNA_PINCTRL_FUNC(0x1, "i2s1"), /* LRCKIO */
			SYNA_PINCTRL_FUNC(0x2, "pwm"), /* PWM0 */
			SYNA_PINCTRL_FUNC(0x3, "arc_test"), /* OUT */
			SYNA_PINCTRL_FUNC(0x7, "avio")), /* DBG0 */
	SYNA_PINCTRL_GROUP("I2S1_BCLKIO", 0x0, 0x3, 0x0f,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO20 */
			SYNA_PINCTRL_FUNC(0x1, "i2s1"), /* BCLKIO */
			SYNA_PINCTRL_FUNC(0x2, "pwm"), /* PWM1 */
			SYNA_PINCTRL_FUNC(0x7, "avio")), /* DBG1 */
	SYNA_PINCTRL_GROUP("SPDIFO", 0x0, 0x3, 0x12,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO14 */
			SYNA_PINCTRL_FUNC(0x1, "spdifo"),
			SYNA_PINCTRL_FUNC(0x4, "avpll")), /* CLKO */
	SYNA_PINCTRL_GROUP("SPDIFI", 0x0, 0x3, 0x15,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO4 */
			SYNA_PINCTRL_FUNC(0x1, "spdifi"),
			SYNA_PINCTRL_FUNC(0x2, "pdm")), /* DI */
	SYNA_PINCTRL_GROUP("I2S2_LRCKIO", 0x0, 0x3, 0x18,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO13 */
			SYNA_PINCTRL_FUNC(0x1, "i2s2")), /* LRCKIO */
	SYNA_PINCTRL_GROUP("I2S2_BCLKIO", 0x0, 0x3, 0x1b,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO12 */
			SYNA_PINCTRL_FUNC(0x1, "i2s2"), /* BCLKIO */
			SYNA_PINCTRL_FUNC(0x2, "pdm")), /* CLKIO */
	SYNA_PINCTRL_GROUP("I2S2_DI0", 0x4, 0x3, 0x00,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO11 */
			SYNA_PINCTRL_FUNC(0x1, "i2s2"), /* DI0 */
			SYNA_PINCTRL_FUNC(0x2, "pdm")), /* DI3 */
	SYNA_PINCTRL_GROUP("I2S2_DI1", 0x4, 0x3, 0x03,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO10 */
			SYNA_PINCTRL_FUNC(0x1, "i2s2"), /* DI1 */
			SYNA_PINCTRL_FUNC(0x2, "pdm"), /* DI2 */
			SYNA_PINCTRL_FUNC(0x3, "sts3")), /* SD */
	SYNA_PINCTRL_GROUP("I2S2_DI2", 0x4, 0x3, 0x06,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO9 */
			SYNA_PINCTRL_FUNC(0x1, "i2s2"), /* DI2 */
			SYNA_PINCTRL_FUNC(0x2, "pdm"), /* DI1 */
			SYNA_PINCTRL_FUNC(0x3, "sts4")), /* CLK */
	SYNA_PINCTRL_GROUP("I2S2_DI3", 0x4, 0x3, 0x09,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO8 */
			SYNA_PINCTRL_FUNC(0x1, "i2s2"), /* DI3 */
			SYNA_PINCTRL_FUNC(0x2, "pdm"), /* DI0 */
			SYNA_PINCTRL_FUNC(0x3, "sts4")), /* SD */
	SYNA_PINCTRL_GROUP("I2S1_MCLK", 0x4, 0x3, 0x0c,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO18 */
			SYNA_PINCTRL_FUNC(0x1, "i2s1"), /* MCLK */
			SYNA_PINCTRL_FUNC(0x7, "avio")), /* DBG3 */
	SYNA_PINCTRL_GROUP("I2S2_MCLK", 0x4, 0x3, 0x0f,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO7 */
			SYNA_PINCTRL_FUNC(0x1, "i2s2"), /* MCLK */
			SYNA_PINCTRL_FUNC(0x2, "pdm"), /* CLKIO */
			SYNA_PINCTRL_FUNC(0x4, "hdmi")), /* FBCLK */
	SYNA_PINCTRL_GROUP("TX_EDDC_SCL", 0x4, 0x3, 0x12,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO6 */
			SYNA_PINCTRL_FUNC(0x1, "tx_eddc")), /* SCL */
	SYNA_PINCTRL_GROUP("TX_EDDC_SDA", 0x4, 0x3, 0x15,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO5 */
			SYNA_PINCTRL_FUNC(0x1, "tx_eddc")), /* SDA */
	SYNA_PINCTRL_GROUP("I2S3_DO", 0x4, 0x3, 0x18,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO1 */
			SYNA_PINCTRL_FUNC(0x1, "i2s3"), /* DO */
			SYNA_PINCTRL_FUNC(0x7, "avio")), /* DBG2 */
	SYNA_PINCTRL_GROUP("I2S3_LRCKIO", 0x4, 0x3, 0x1b,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO3 */
			SYNA_PINCTRL_FUNC(0x1, "i2s3")), /* LRCKIO */
	SYNA_PINCTRL_GROUP("I2S3_BCLKIO", 0x8, 0x3, 0x00,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO2 */
			SYNA_PINCTRL_FUNC(0x1, "i2s3")), /* BCLKIO */
	SYNA_PINCTRL_GROUP("I2S3_DI", 0x8, 0x3, 0x03,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO0 */
			SYNA_PINCTRL_FUNC(0x1, "i2s3")), /* DI */
};

static const struct syna_desc_group dolphin_sysmgr_pinctrl_groups[] = {
	SYNA_PINCTRL_GROUP("SM_TW2_SCL", 0x0, 0x3, 0x00,
			   SYNA_PINCTRL_FUNC(0x0, "rx_edid"), /* SCL */
			SYNA_PINCTRL_FUNC(0x1, "tw2"), /* SCL */
			SYNA_PINCTRL_FUNC(0x2, "gpio")), /* SM GPIO0 */
	SYNA_PINCTRL_GROUP("SM_TW2_SDA", 0x0, 0x3, 0x03,
			   SYNA_PINCTRL_FUNC(0x0, "rx_edid"), /* SDA */
			SYNA_PINCTRL_FUNC(0x1, "tw2"), /* SDA */
			SYNA_PINCTRL_FUNC(0x2, "gpio")), /* SM GPIO1 */
	SYNA_PINCTRL_GROUP("SM_URT1_TXD", 0x0, 0x3, 0x06,
			   SYNA_PINCTRL_FUNC(0x0, "porb"), /* VOUT 1p05 */
			SYNA_PINCTRL_FUNC(0x1, "uart1"), /* TXD */
			SYNA_PINCTRL_FUNC(0x2, "gpio"), /* SM GPIO4 */
			SYNA_PINCTRL_FUNC(0x3, "pwm"), /* PWM2 */
			SYNA_PINCTRL_FUNC(0x4, "timer"), /* TIMER0 */
			SYNA_PINCTRL_FUNC(0x5, "porb")), /* AVDD LV */
	SYNA_PINCTRL_GROUP("SM_URT1_RXD", 0x0, 0x3, 0x09,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* SM GPIO5 */
			SYNA_PINCTRL_FUNC(0x1, "uart1"), /* RXD */
			SYNA_PINCTRL_FUNC(0x2, "clk_25m"),
			SYNA_PINCTRL_FUNC(0x3, "pwm"), /* PWM3 */
			SYNA_PINCTRL_FUNC(0x4, "timer"), /* TIMER1 */
			SYNA_PINCTRL_FUNC(0x5, "por")), /* VDDSOC_RSTB */
	SYNA_PINCTRL_GROUP("SM_HDMI_HPD", 0x0, 0x3, 0x0c,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* SM GPIO2 */
			SYNA_PINCTRL_FUNC(0x1, "hdmi")), /* HPD */
	SYNA_PINCTRL_GROUP("SM_HDMI_CEC", 0x0, 0x3, 0x0f,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* SM GPIO3 */
			SYNA_PINCTRL_FUNC(0x1, "hdmi")), /* CEC */
	SYNA_PINCTRL_GROUP("SM_TMS", 0x0, 0x3, 0x12,
			   SYNA_PINCTRL_FUNC(0x0, "jtag"), /* TMS */
			SYNA_PINCTRL_FUNC(0x1, "gpio"), /* SM GPIO6 */
			SYNA_PINCTRL_FUNC(0x2, "pwm")), /* PWM0 */
	SYNA_PINCTRL_GROUP("SM_TDI", 0x0, 0x3, 0x15,
			   SYNA_PINCTRL_FUNC(0x0, "jtag"), /* TDI */
			SYNA_PINCTRL_FUNC(0x1, "gpio"), /* SM GPIO7 */
			SYNA_PINCTRL_FUNC(0x2, "pwm")), /* PWM1 */
	SYNA_PINCTRL_GROUP("SM_TDO", 0x0, 0x3, 0x18,
			   SYNA_PINCTRL_FUNC(0x0, "jtag"), /* TDO */
			SYNA_PINCTRL_FUNC(0x1, "gpio")), /* SM GPIO8 */
	SYNA_PINCTRL_GROUP("SM_TW3_SCL", 0x0, 0x3, 0x1b,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* SM GPIO9 */
			SYNA_PINCTRL_FUNC(0x1, "tw3"), /* SCL */
			SYNA_PINCTRL_FUNC(0x2, "pwm")), /* PWM2 */
	SYNA_PINCTRL_GROUP("SM_TW3_SDA", 0x4, 0x3, 0x00,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* SM GPIO10 */
			SYNA_PINCTRL_FUNC(0x1, "tw3"), /* SDA */
			SYNA_PINCTRL_FUNC(0x2, "pwm")), /* PWM3 */
	SYNA_PINCTRL_GROUP("SM_SPI2_SS0n", 0x4, 0x3, 0x03,
			   SYNA_PINCTRL_FUNC(0x0, "spi2"), /* SS0 n*/
			SYNA_PINCTRL_FUNC(0x1, "gpio"), /* SM GPIO17 */
			SYNA_PINCTRL_FUNC(0x7, "porb")), /* AVDD33_LV */
	SYNA_PINCTRL_GROUP("SM_SPI2_SS1n", 0x4, 0x3, 0x06,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* SM GPIO16 */
			SYNA_PINCTRL_FUNC(0x1, "spi2"), /* SS1n */
			SYNA_PINCTRL_FUNC(0x6, "uart1"), /* RTSn */
			SYNA_PINCTRL_FUNC(0x7, "vdd")), /* CPU PORTB */
	SYNA_PINCTRL_GROUP("SM_SPI2_SS2n", 0x4, 0x3, 0x09,
			   SYNA_PINCTRL_FUNC(0x0, "mon"), /* VDD 1P8 */
			SYNA_PINCTRL_FUNC(0x1, "spi2"), /* SS2n */
			SYNA_PINCTRL_FUNC(0x2, "gpio"), /* SM GPIO15 */
			SYNA_PINCTRL_FUNC(0x3, "pwm"), /* PWM0 */
			SYNA_PINCTRL_FUNC(0x4, "timer"), /* TIMER0 */
			SYNA_PINCTRL_FUNC(0x5, "uart2"), /* TXD */
			SYNA_PINCTRL_FUNC(0x7, "clk_25m")),
	SYNA_PINCTRL_GROUP("SM_SPI2_SS3n", 0x4, 0x3, 0x0c,
			   SYNA_PINCTRL_FUNC(0x0, "pwr_ok"),
			SYNA_PINCTRL_FUNC(0x1, "spi2"), /* SS3n */
			SYNA_PINCTRL_FUNC(0x2, "gpio"), /* SM GPIO14 */
			SYNA_PINCTRL_FUNC(0x3, "pwm"), /* PWM1 */
			SYNA_PINCTRL_FUNC(0x4, "timer"), /* TIMER1 */
			SYNA_PINCTRL_FUNC(0x5, "uart2"), /* RXD */
			SYNA_PINCTRL_FUNC(0x7, "uart1")), /* CTSn */
	SYNA_PINCTRL_GROUP("SM_SPI2_SDO", 0x4, 0x3, 0x0f,
			   SYNA_PINCTRL_FUNC(0x0, "spi2"), /* SDO */
			SYNA_PINCTRL_FUNC(0x1, "gpio"), /* SM GPIO13 */
			SYNA_PINCTRL_FUNC(0x2, "uart2")), /* RTSn */
	SYNA_PINCTRL_GROUP("SM_SPI2_SDI", 0x4, 0x3, 0x12,
			   SYNA_PINCTRL_FUNC(0x0, "spi2"), /* SDI */
			SYNA_PINCTRL_FUNC(0x1, "gpio"), /* SM GPIO12 */
			SYNA_PINCTRL_FUNC(0x2, "uart2")), /* CTSn */
	SYNA_PINCTRL_GROUP("SM_SPI2_SCLK", 0x4, 0x3, 0x15,
			   SYNA_PINCTRL_FUNC(0x0, "spi2"), /* SCLK */
			SYNA_PINCTRL_FUNC(0x1, "gpio")), /* SM GPIO11 */
	SYNA_PINCTRL_GROUP("SM_URT0_TXD", 0x4, 0x3, 0x18,
			   SYNA_PINCTRL_FUNC(0x0, "uart0"), /* TXD */
			SYNA_PINCTRL_FUNC(0x1, "gpio")), /* SM GPIO19 */
	SYNA_PINCTRL_GROUP("SM_URT0_RXD", 0x4, 0x3, 0x1b,
			   SYNA_PINCTRL_FUNC(0x0, "uart0"), /* RXD */
			SYNA_PINCTRL_FUNC(0x1, "gpio")), /* SM GPIO19 */
	SYNA_PINCTRL_GROUP("SM_HDMIRX_HPD", 0x8, 0x3, 0x00,
			   SYNA_PINCTRL_FUNC(0x0, "hdmirx"), /* HPD */
			SYNA_PINCTRL_FUNC(0x1, "gpio")), /* SM GPIO20 */
	SYNA_PINCTRL_GROUP("SM_HDMIRX_PWR5V", 0x8, 0x3, 0x03,
			   SYNA_PINCTRL_FUNC(0x0, "hdmirx"), /* PWR5V */
			SYNA_PINCTRL_FUNC(0x1, "gpio")), /* SM GPIO21 */
};

static const struct syna_pinctrl_desc dolphin_soc_pinctrl_data = {
	.groups = dolphin_soc_pinctrl_groups,
	.ngroups = ARRAY_SIZE(dolphin_soc_pinctrl_groups),
};

static const struct syna_pinctrl_desc dolphin_avio_pinctrl_data = {
	.groups = dolphin_avio_pinctrl_groups,
	.ngroups = ARRAY_SIZE(dolphin_avio_pinctrl_groups),
};

static const struct syna_pinctrl_desc dolphin_sysmgr_pinctrl_data = {
	.groups = dolphin_sysmgr_pinctrl_groups,
	.ngroups = ARRAY_SIZE(dolphin_sysmgr_pinctrl_groups),
};

#endif /* __PINCTRL_SYNA_DOLPHIN_H */
