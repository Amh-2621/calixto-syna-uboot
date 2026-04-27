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

#ifndef __PINCTRL_SYNA_MYNA2_H
#define __PINCTRL_SYNA_MYNA2_H

#include <dm/device.h>
#include <dm/pinctrl.h>

#include "pinctrl_syna.h"

static const struct syna_desc_group myna2_soc_pinctrl_groups[] = {
	SYNA_PINCTRL_GROUP("TW0_SCL", 0x0, 0x3, 0x00,
			   SYNA_PINCTRL_FUNC(0x0, "tw0"), /* SCL */
			SYNA_PINCTRL_FUNC(0x1, "gpio"), /* GPIO10 */
			SYNA_PINCTRL_FUNC(0x2, "urt0a"), /* CTSn */
			SYNA_PINCTRL_FUNC(0x3, "i2s4")), /* LRCK */
	SYNA_PINCTRL_GROUP("TW0_SDA", 0x0, 0x3, 0x03,
			   SYNA_PINCTRL_FUNC(0x0, "tw0"), /* SDA */
			SYNA_PINCTRL_FUNC(0x1, "gpio"), /* GPIO11 */
			SYNA_PINCTRL_FUNC(0x2, "urt0a"), /* RTSn */
			SYNA_PINCTRL_FUNC(0x3, "i2s4")), /* BCLK */
	SYNA_PINCTRL_GROUP("TW1_SCL", 0x0, 0x3, 0x06,
			   SYNA_PINCTRL_FUNC(0x0, "tw1"), /* SCL */
			SYNA_PINCTRL_FUNC(0x1, "gpio"), /* GPIO12 */
			SYNA_PINCTRL_FUNC(0x3, "i2s4"), /* DO */
			SYNA_PINCTRL_FUNC(0x5, "io3p3_for_n")),
	SYNA_PINCTRL_GROUP("TW1_SDA", 0x0, 0x3, 0x09,
			   SYNA_PINCTRL_FUNC(0x0, "tw1"), /* SDA */
			SYNA_PINCTRL_FUNC(0x1, "gpio"), /* GPIO13 */
			SYNA_PINCTRL_FUNC(0x3, "i2s4"), /* DI */
			SYNA_PINCTRL_FUNC(0x5, "por_vddsoc_rstb")),
	SYNA_PINCTRL_GROUP("TMS", 0x0, 0x3, 0x0c,
			   SYNA_PINCTRL_FUNC(0x0, "tms"), /* TMS */
			SYNA_PINCTRL_FUNC(0x1, "gpio"), /* GPIO0 */
			SYNA_PINCTRL_FUNC(0x2, "urt0b"), /* TXD */
			SYNA_PINCTRL_FUNC(0x3, "key")), /* COL2 */
	SYNA_PINCTRL_GROUP("TDI", 0x0, 0x3, 0x0f,
			   SYNA_PINCTRL_FUNC(0x0, "tdi"), /* TDI */
			SYNA_PINCTRL_FUNC(0x1, "gpio"), /* GPIO1 */
			SYNA_PINCTRL_FUNC(0x2, "urt0b"), /* RXD */
			SYNA_PINCTRL_FUNC(0x3, "key"), /* COL3 */
			SYNA_PINCTRL_FUNC(0x4, "gpio_trig")), /* GPIO_TRIG[0] */
	SYNA_PINCTRL_GROUP("TDO", 0x0, 0x3, 0x12,
			   SYNA_PINCTRL_FUNC(0x0, "tdo"), /* TDO */
			SYNA_PINCTRL_FUNC(0x1, "gpio"), /* GPIO2 */
			SYNA_PINCTRL_FUNC(0x2, "pdmb"), /* CLKIO */
			SYNA_PINCTRL_FUNC(0x3, "i2s2")), /* MCLK */
	SYNA_PINCTRL_GROUP("SPI1_SS0n", 0x0, 0x3, 0x15,
			   SYNA_PINCTRL_FUNC(0x0, "spi1"), /* SS0n */
			SYNA_PINCTRL_FUNC(0x1, "gpio")), /* GPIO3 */
	SYNA_PINCTRL_GROUP("SPI1_SS1n", 0x0, 0x3, 0x18,
			   SYNA_PINCTRL_FUNC(0x0, "core_for_n"),
			SYNA_PINCTRL_FUNC(0x1, "spi1"), /*  SS1n*/
			SYNA_PINCTRL_FUNC(0x2, "gpio"), /* GPIO4 */
			SYNA_PINCTRL_FUNC(0x3, "dsi_te"), /* DSI_TE */
			SYNA_PINCTRL_FUNC(0x4, "gpio_trig")), /* GPIO_TRIG[1] */
	SYNA_PINCTRL_GROUP("SPI1_SS2n", 0x0, 0x3, 0x1b,
			   SYNA_PINCTRL_FUNC(0x0, "urt0a"), /* RXD */
			SYNA_PINCTRL_FUNC(0x1, "spi1"), /*  SS2n*/
			SYNA_PINCTRL_FUNC(0x2, "gpio"), /* GPIO5 */
			SYNA_PINCTRL_FUNC(0x4, "gpio_trig")), /* GPIO_TRIG[2] */

	SYNA_PINCTRL_GROUP("SPI1_SS3n", 0x4, 0x3, 0x00,
			   SYNA_PINCTRL_FUNC(0x0, "urt0a"), /* TXD */
			SYNA_PINCTRL_FUNC(0x1, "spi1"), /*  SS3n*/
			SYNA_PINCTRL_FUNC(0x2, "gpio")), /* GPIO6 */
	SYNA_PINCTRL_GROUP("SPI1_SDO", 0x4, 0x3, 0x03,
			   SYNA_PINCTRL_FUNC(0x0, "spi1"), /* SDO */
			SYNA_PINCTRL_FUNC(0x1, "gpio"), /* GPIO7 */
			SYNA_PINCTRL_FUNC(0x7, "syspll0")), /* CLKO */
	SYNA_PINCTRL_GROUP("SPI1_SDI", 0x4, 0x3, 0x06,
			   SYNA_PINCTRL_FUNC(0x0, "spi1"), /* SDI */
			SYNA_PINCTRL_FUNC(0x1, "gpio"), /* GPIO9 */
			SYNA_PINCTRL_FUNC(0x7, "syspll1")), /* CLKO */
	SYNA_PINCTRL_GROUP("SPI1_SCLK", 0x4, 0x3, 0x09,
			   SYNA_PINCTRL_FUNC(0x0, "spi1"), /* SCLK */
			SYNA_PINCTRL_FUNC(0x1, "gpio")), /* GPIO8 */
	SYNA_PINCTRL_GROUP("TW2_SCL", 0x4, 0x3, 0x0c,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO37 */
			SYNA_PINCTRL_FUNC(0x1, "tw2"), /* SCL */
			SYNA_PINCTRL_FUNC(0x2, "key"), /* ROW0 */
			SYNA_PINCTRL_FUNC(0x3, "rgmii")), /* rgmiib_MDC */
	SYNA_PINCTRL_GROUP("TW2_SDA", 0x4, 0x3, 0x0f,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO38 */
			SYNA_PINCTRL_FUNC(0x1, "tw2"), /* SDA */
			SYNA_PINCTRL_FUNC(0x2, "key"), /* ROW1 */
			SYNA_PINCTRL_FUNC(0x3, "rgmii"), /* rgmiib_MDIO */
			SYNA_PINCTRL_FUNC(0x7, "phy")), /* DBG15 */
	SYNA_PINCTRL_GROUP("SPI2_SS0n", 0x4, 0x3, 0x12,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO30 */
			SYNA_PINCTRL_FUNC(0x1, "spi2")), /* SS0n  */
	SYNA_PINCTRL_GROUP("SPI2_SS1n", 0x4, 0x3, 0x15,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO31 */
			SYNA_PINCTRL_FUNC(0x1, "spi2"), /*  SS1n*/
			SYNA_PINCTRL_FUNC(0x3, "daif_if"), /* CDC_DIR */
			SYNA_PINCTRL_FUNC(0x7, "phy")), /* DBG14 */
	SYNA_PINCTRL_GROUP("SPI2_SS2n", 0x4, 0x3, 0x18,
			   SYNA_PINCTRL_FUNC(0x0, "io_por_n"), /* IO_POR_N */
			SYNA_PINCTRL_FUNC(0x1, "gpio"), /* GPIO32 */
			SYNA_PINCTRL_FUNC(0x2, "spi2"), /*  SS2n*/
			SYNA_PINCTRL_FUNC(0x3, "daif_if"), /* PWR_OK */
			SYNA_PINCTRL_FUNC(0x4, "pdm"), /* DI[2] */
			SYNA_PINCTRL_FUNC(0x7, "phy")), /* DBG12 */
	SYNA_PINCTRL_GROUP("SPI2_SS3n", 0x4, 0x3, 0x1b,
			   SYNA_PINCTRL_FUNC(0x0, "pwr_ok"), /* PWR_OK */
			SYNA_PINCTRL_FUNC(0x1, "gpio"), /* GPIO33 */
			SYNA_PINCTRL_FUNC(0x2, "spi2"), /*  SS3n*/
			SYNA_PINCTRL_FUNC(0x3, "daif_if"), /* NARES */
			SYNA_PINCTRL_FUNC(0x4, "pdm"), /* DI[3] */
			SYNA_PINCTRL_FUNC(0x7, "phy")), /* DBG13 */

	SYNA_PINCTRL_GROUP("SPI2_SDO", 0x8, 0x3, 0x00,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /*  GPIO34 */
			SYNA_PINCTRL_FUNC(0x1, "spi2"), /* SDO */
			SYNA_PINCTRL_FUNC(0x7, "mempll")), /* CLKO */
	SYNA_PINCTRL_GROUP("SPI2_SCLK", 0x8, 0x3, 0x03,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO35 */
			SYNA_PINCTRL_FUNC(0x1, "spi2"), /* SCLK */
			SYNA_PINCTRL_FUNC(0x7, "dbg")), /* CLKO */
	SYNA_PINCTRL_GROUP("SPI2_SDI", 0x8, 0x3, 0x06,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO36 */
			SYNA_PINCTRL_FUNC(0x1, "spi2"), /* SDI */
			SYNA_PINCTRL_FUNC(0x7, "cpupll")), /* CLKO */
	SYNA_PINCTRL_GROUP("TW3_SCL", 0x8, 0x3, 0x09,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO41 */
			SYNA_PINCTRL_FUNC(0x1, "tw3"), /* SCL */
			SYNA_PINCTRL_FUNC(0x2, "urt1a"), /* RTSn */
			SYNA_PINCTRL_FUNC(0x3, "if"), /* DCLS */
			SYNA_PINCTRL_FUNC(0x7, "phy")), /* DBG7 */
	SYNA_PINCTRL_GROUP("TW3_SDA", 0x8, 0x3, 0x0c,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO42 */
			SYNA_PINCTRL_FUNC(0x1, "tw3"), /* SDA */
			SYNA_PINCTRL_FUNC(0x2, "urt1a"), /* CTSn */
			SYNA_PINCTRL_FUNC(0x3, "if"), /* DCLS_N */
			SYNA_PINCTRL_FUNC(0x7, "phy")), /* DBG6 */
	SYNA_PINCTRL_GROUP("URT1_RXD", 0x8, 0x3, 0x0f,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO39 */
			SYNA_PINCTRL_FUNC(0x2, "urt1a"), /* RXD */
			SYNA_PINCTRL_FUNC(0x3, "key"), /* ROW2 */
			SYNA_PINCTRL_FUNC(0x4, "gpio_trig"), /* TRIG[3] */
			SYNA_PINCTRL_FUNC(0x7, "phy")), /* DBG5 */
	SYNA_PINCTRL_GROUP("URT1_TXD", 0x8, 0x3, 0x12,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO40 */
			SYNA_PINCTRL_FUNC(0x2, "urt1a"), /* TXD */
			SYNA_PINCTRL_FUNC(0x3, "key"), /* ROW3 */
			SYNA_PINCTRL_FUNC(0x7, "phy")), /* DBG4 */
	SYNA_PINCTRL_GROUP("PWM0", 0x8, 0x3, 0x15,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO46 */
			SYNA_PINCTRL_FUNC(0x1, "pwm"), /* PWM[0] */
			SYNA_PINCTRL_FUNC(0x2, "rgmii"), /*  PTP_PPS_O*/
			SYNA_PINCTRL_FUNC(0x7, "phy")), /* DBG3 */
	SYNA_PINCTRL_GROUP("PWM1", 0x8, 0x3, 0x18,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO45 */
			SYNA_PINCTRL_FUNC(0x1, "pwm"), /* PWM[1] */
			SYNA_PINCTRL_FUNC(0x7, "phy")), /* DBG2 */
	SYNA_PINCTRL_GROUP("PWM2", 0x8, 0x3, 0x1b,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO44 */
			SYNA_PINCTRL_FUNC(0x1, "pwm"), /* PWM[2] */
			SYNA_PINCTRL_FUNC(0x2, "key"), /* COL1 */
			SYNA_PINCTRL_FUNC(0x7, "phy")), /* DBG1 */

	SYNA_PINCTRL_GROUP("PWM3", 0xc, 0x3, 0x00,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO43 */
			SYNA_PINCTRL_FUNC(0x1, "pwm"), /* PWM[3] */
			SYNA_PINCTRL_FUNC(0x3, "if"), /* DCLS_SCLK */
			SYNA_PINCTRL_FUNC(0x7, "phy")), /* DBG0 */
	SYNA_PINCTRL_GROUP("GPIO_A0", 0xc, 0x3, 0x03,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO50 */
			SYNA_PINCTRL_FUNC(0x1, "rgmii"), /* rgmiia_MDIO  */
			SYNA_PINCTRL_FUNC(0x2, "pwm"), /* PWM[1]  */
			SYNA_PINCTRL_FUNC(0x7, "phy")), /* DBG8 */
	SYNA_PINCTRL_GROUP("GPIO_A1", 0xc, 0x3, 0x06,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO49 */
			SYNA_PINCTRL_FUNC(0x1, "rgmii"), /* rgmiia_MDC  */
			SYNA_PINCTRL_FUNC(0x2, "pwm"), /* PWM[2]  */
			SYNA_PINCTRL_FUNC(0x7, "phy")), /* DBG9 */
	SYNA_PINCTRL_GROUP("GPIO_A2", 0xc, 0x3, 0x09,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO48 */
			SYNA_PINCTRL_FUNC(0x2, "key"), /* ROW5 */
			SYNA_PINCTRL_FUNC(0x3, "urt1b"), /* TXD */
			SYNA_PINCTRL_FUNC(0x7, "phy")), /* DBG10 */
	SYNA_PINCTRL_GROUP("GPIO_A3", 0xc, 0x3, 0x0c,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO47 */
			SYNA_PINCTRL_FUNC(0x2, "key"), /* ROW4 */
			SYNA_PINCTRL_FUNC(0x3, "urt1b"), /* RXD */
			SYNA_PINCTRL_FUNC(0x7, "phy")), /* DBG11 */
	SYNA_PINCTRL_GROUP("USB2_DRV_VBUS", 0xc, 0x3, 0x0f,
			   SYNA_PINCTRL_FUNC(0x0, "usb2_drv_Vbus"),
			SYNA_PINCTRL_FUNC(0x1, "gpio")), /* GPIO51 */
	SYNA_PINCTRL_GROUP("SDIO_CDn", 0xc, 0x3, 0x12,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO54 */
			SYNA_PINCTRL_FUNC(0x1, "sdio"), /* CDn */
			SYNA_PINCTRL_FUNC(0x2, "key"), /* COL0 */
			SYNA_PINCTRL_FUNC(0x3, "urt1b")), /* RTSn */
	SYNA_PINCTRL_GROUP("SDIO_WP", 0xc, 0x3, 0x15,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO55 */
			SYNA_PINCTRL_FUNC(0x1, "sdio"), /* WP */
			SYNA_PINCTRL_FUNC(0x3, "urt1b")), /* CTSn */
	SYNA_PINCTRL_GROUP("NFALE", 0xc, 0x3, 0x18,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO52 */
			SYNA_PINCTRL_FUNC(0x1, "nfale")), /* NFALE */
	SYNA_PINCTRL_GROUP("NFLCS", 0xc, 0x3, 0x1b,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO53 */
			SYNA_PINCTRL_FUNC(0x1, "nflcs")), /* NFLCS */

	SYNA_PINCTRL_GROUP("RGMII_CLK_OUT", 0x10, 0x3, 0x00,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO_X53 */
			SYNA_PINCTRL_FUNC(0x1, "rgmii")), /* CLK_OUT */
	SYNA_PINCTRL_GROUP("RGMIITXC", 0x10, 0x3, 0x03,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO_X43 */
			SYNA_PINCTRL_FUNC(0x1, "rgmii")), /* TXC */
	SYNA_PINCTRL_GROUP("RGMIITD0", 0x10, 0x3, 0x06,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO_X19 */
			SYNA_PINCTRL_FUNC(0x1, "rgmii")), /* TXD[0] */
	SYNA_PINCTRL_GROUP("RGMIITD1", 0x10, 0x3, 0x09,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO_X20 */
			SYNA_PINCTRL_FUNC(0x1, "rgmii")), /* TXD[1] */
	SYNA_PINCTRL_GROUP("RGMIITD2", 0x10, 0x3, 0x0c,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO_X21 */
			SYNA_PINCTRL_FUNC(0x1, "rgmii")), /* TXD[2] */
	SYNA_PINCTRL_GROUP("RGMIITD3", 0x10, 0x3, 0x0f,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO_X22 */
			SYNA_PINCTRL_FUNC(0x1, "rgmii")), /* TXD[3] */
	SYNA_PINCTRL_GROUP("RGMIITXCTL", 0x10, 0x3, 0x12,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO_X51 */
			SYNA_PINCTRL_FUNC(0x1, "rgmii")), /* TXCTL */
	SYNA_PINCTRL_GROUP("RGMIIRXC", 0x10, 0x3, 0x15,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO_X42 */
			SYNA_PINCTRL_FUNC(0x1, "rgmii")), /* RXC */
	SYNA_PINCTRL_GROUP("RGMIIRD0", 0x10, 0x3, 0x18,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO_X31 */
			SYNA_PINCTRL_FUNC(0x1, "rgmii")), /* RXD[0] */
	SYNA_PINCTRL_GROUP("RGMIIRD1", 0x10, 0x3, 0x1b,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO_X32 */
			SYNA_PINCTRL_FUNC(0x1, "rgmii")), /* RXD[1] */

	SYNA_PINCTRL_GROUP("RGMIIRD2", 0x14, 0x3, 0x00,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO_X33 */
			SYNA_PINCTRL_FUNC(0x1, "rgmii")), /* RXD[2] */
	SYNA_PINCTRL_GROUP("RGMIIRD3", 0x14, 0x3, 0x03,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO_X41 */
			SYNA_PINCTRL_FUNC(0x1, "rgmii")), /* RXD[3] */
	SYNA_PINCTRL_GROUP("RGMIIRXCTL", 0x14, 0x3, 0x06,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO_X52 */
			SYNA_PINCTRL_FUNC(0x1, "rgmii")), /* RXCTL */
	SYNA_PINCTRL_GROUP("I2S1_DO", 0x14, 0x3, 0x09,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO16 */
			SYNA_PINCTRL_FUNC(0x1, "i2s1"), /* DO */
			SYNA_PINCTRL_FUNC(0x3, "daif_if"), /* CDC_DAT_DA */
			SYNA_PINCTRL_FUNC(0x7, "aio")), /* DBG[4] */
	SYNA_PINCTRL_GROUP("I2S1_DI", 0x14, 0x3, 0x0c,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO18 */
			SYNA_PINCTRL_FUNC(0x1, "i2s1"), /* DI */
			SYNA_PINCTRL_FUNC(0x3, "daif_if"), /* DAT_DA */
			SYNA_PINCTRL_FUNC(0x4, "apll0"), /* CLKO */
			SYNA_PINCTRL_FUNC(0x7, "aio")), /* DBG[5] */
	SYNA_PINCTRL_GROUP("I2S1_LRCK", 0x14, 0x3, 0x0f,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO14 */
			SYNA_PINCTRL_FUNC(0x1, "i2s1"), /* LRCK */
			SYNA_PINCTRL_FUNC(0x3, "daif_if"), /* CLK_PLL */
			SYNA_PINCTRL_FUNC(0x7, "aio")), /* DBG[0] */
	SYNA_PINCTRL_GROUP("I2S1_BCLK", 0x14, 0x3, 0x12,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO15 */
			SYNA_PINCTRL_FUNC(0x1, "i2s1"), /* BCLK */
			SYNA_PINCTRL_FUNC(0x3, "daif_if"), /* CDC_DAT_AD */
			SYNA_PINCTRL_FUNC(0x7, "aio")), /* DBG[1] */
	SYNA_PINCTRL_GROUP("I2S1_MCLK", 0x14, 0x3, 0x15,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO17 */
			SYNA_PINCTRL_FUNC(0x1, "i2s1"), /* MCLK */
			SYNA_PINCTRL_FUNC(0x3, "daif_if"), /* CLK_IF */
			SYNA_PINCTRL_FUNC(0x7, "aio")), /* DBG[3] */
	SYNA_PINCTRL_GROUP("I2S2_LRCK", 0x14, 0x3, 0x18,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO19 */
			SYNA_PINCTRL_FUNC(0x1, "i2s2"), /* LRCK */
			SYNA_PINCTRL_FUNC(0x2, "urt0b"), /* CTSn */
			SYNA_PINCTRL_FUNC(0x3, "daif_if")), /* DAT_AD */
	SYNA_PINCTRL_GROUP("I2S2_BCLK", 0x14, 0x3, 0x1b,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO20 */
			SYNA_PINCTRL_FUNC(0x1, "i2s2"), /* BCLK */
			SYNA_PINCTRL_FUNC(0x2, "urt0b"), /* RTSn */
			SYNA_PINCTRL_FUNC(0x3, "daif_if")), /* EN_AD */

	SYNA_PINCTRL_GROUP("I2S2_DO", 0x18, 0x3, 0x00,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO21 */
			SYNA_PINCTRL_FUNC(0x1, "i2s2"), /* DO */
			SYNA_PINCTRL_FUNC(0x3, "daif_if"), /* O:EN_DA */
			SYNA_PINCTRL_FUNC(0x7, "aio")), /* DBG[6] */
	SYNA_PINCTRL_GROUP("I2S2_DI", 0x18, 0x3, 0x03,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO22 */
			SYNA_PINCTRL_FUNC(0x1, "i2s2"), /* DI */
			SYNA_PINCTRL_FUNC(0x3, "daif_if"), /* INT_ANA */
			SYNA_PINCTRL_FUNC(0x4, "vpll0"), /* CLKO */
			SYNA_PINCTRL_FUNC(0x7, "aio")), /* DBG[7] */
	SYNA_PINCTRL_GROUP("PDM_CLKIO", 0x18, 0x3, 0x06,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO25 */
			SYNA_PINCTRL_FUNC(0x1, "pdm"), /* CLKIO */
			SYNA_PINCTRL_FUNC(0x2, "i2s2")), /* CMLK */
	SYNA_PINCTRL_GROUP("PDM_DI0", 0x18, 0x3, 0x09,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO24 */
			SYNA_PINCTRL_FUNC(0x1, "pdm")), /* DI[0] */
	SYNA_PINCTRL_GROUP("PDM_DI1", 0x18, 0x3, 0x0c,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO23 */
			SYNA_PINCTRL_FUNC(0x1, "pdm")), /* DI[1] */
	SYNA_PINCTRL_GROUP("I2S3_DO", 0x18, 0x3, 0x0f,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO28 */
			SYNA_PINCTRL_FUNC(0x1, "i2s3"), /* DO */
			SYNA_PINCTRL_FUNC(0x4, "apll1"), /* CLKO */
			SYNA_PINCTRL_FUNC(0x7, "aio")), /* DBG[2] */
	SYNA_PINCTRL_GROUP("I2S3_LRCK", 0x18, 0x3, 0x12,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO26 */
			SYNA_PINCTRL_FUNC(0x1, "i2s3")), /* LRCK */
	SYNA_PINCTRL_GROUP("I2S3_BCLK", 0x18, 0x3, 0x15,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO27 */
			SYNA_PINCTRL_FUNC(0x1, "i2s3")), /* BCLK*/
	SYNA_PINCTRL_GROUP("I2S3_DI", 0x18, 0x3, 0x18,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO29 */
			SYNA_PINCTRL_FUNC(0x1, "i2s3"), /* DI */
			SYNA_PINCTRL_FUNC(0x4, "vpll1")), /* CLKO */
	SYNA_PINCTRL_GROUP("LCDD0", 0x18, 0x3, 0x1b,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO_X12 */
			SYNA_PINCTRL_FUNC(0x1, "lcd"), /* LCDD0 */
			SYNA_PINCTRL_FUNC(0x2, "key"), /* ROW6 */
			SYNA_PINCTRL_FUNC(0x3, "tw3b")), /* SCL */

	SYNA_PINCTRL_GROUP("LCDD1", 0x1c, 0x3, 0x00,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO_X13 */
			SYNA_PINCTRL_FUNC(0x1, "lcd"), /* LCDD1 */
			SYNA_PINCTRL_FUNC(0x2, "key"), /* ROW7 */
			SYNA_PINCTRL_FUNC(0x3, "tw3b")), /* SDA */
	SYNA_PINCTRL_GROUP("LCDD2", 0x1c, 0x3, 0x03,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO56 */
			SYNA_PINCTRL_FUNC(0x1, "lcd")), /* LCDD2 */
	SYNA_PINCTRL_GROUP("LCDD3", 0x1c, 0x3, 0x06,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO57 */
			SYNA_PINCTRL_FUNC(0x1, "lcd")), /* LCDD3 */
	SYNA_PINCTRL_GROUP("LCDD4", 0x1c, 0x3, 0x09,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO58 */
			SYNA_PINCTRL_FUNC(0x1, "lcd")), /* LCDD4 */
	SYNA_PINCTRL_GROUP("LCDD5", 0x1c, 0x3, 0x0c,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO59 */
			SYNA_PINCTRL_FUNC(0x1, "lcd")), /* LCDD5 */
	SYNA_PINCTRL_GROUP("LCDD6", 0x1c, 0x3, 0x0f,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO60 */
			SYNA_PINCTRL_FUNC(0x1, "lcd")), /* LCDD6 */
	SYNA_PINCTRL_GROUP("LCDD7", 0x1c, 0x3, 0x12,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO61 */
			SYNA_PINCTRL_FUNC(0x1, "lcd")), /* LCDD7 */
	SYNA_PINCTRL_GROUP("LCDD8", 0x1c, 0x3, 0x15,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO_X0 */
			SYNA_PINCTRL_FUNC(0x1, "lcd"), /* LCDD8 */
			SYNA_PINCTRL_FUNC(0x2, "key"), /* COL6 */
			SYNA_PINCTRL_FUNC(0x3, "i2s5")), /* DO */
	SYNA_PINCTRL_GROUP("LCDD9", 0x1c, 0x3, 0x18,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO_X1 */
			SYNA_PINCTRL_FUNC(0x1, "lcd"), /* LCDD9 */
			SYNA_PINCTRL_FUNC(0x2, "key"), /* COL7 */
			SYNA_PINCTRL_FUNC(0x3, "i2s5")), /* DI */
	SYNA_PINCTRL_GROUP("LCDD10", 0x1c, 0x3, 0x1b,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO62 */
			SYNA_PINCTRL_FUNC(0x1, "lcd")), /* LCDD10 */

	SYNA_PINCTRL_GROUP("LCDD11", 0x20, 0x3, 0x00,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO63 */
			SYNA_PINCTRL_FUNC(0x1, "lcd")), /* LCDD11 */
	SYNA_PINCTRL_GROUP("LCDD12", 0x20, 0x3, 0x03,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO64 */
			SYNA_PINCTRL_FUNC(0x1, "lcd")), /* LCDD12 */
	SYNA_PINCTRL_GROUP("LCDD13", 0x20, 0x3, 0x06,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO65 */
			SYNA_PINCTRL_FUNC(0x1, "lcd")), /* LCDD13 */
	SYNA_PINCTRL_GROUP("LCDD14", 0x20, 0x3, 0x09,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO66 */
			SYNA_PINCTRL_FUNC(0x1, "lcd")), /* LCDD14 */
	SYNA_PINCTRL_GROUP("LCDD15", 0x20, 0x3, 0x0c,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO67 */
			SYNA_PINCTRL_FUNC(0x1, "lcd")), /* LCDD15 */
	SYNA_PINCTRL_GROUP("LCDD16", 0x20, 0x3, 0x0f,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO_X2 */
			SYNA_PINCTRL_FUNC(0x1, "lcd"), /* LCDD16 */
			SYNA_PINCTRL_FUNC(0x2, "key"), /* ROW8 */
			SYNA_PINCTRL_FUNC(0x3, "i2s5")), /* LRCK */
	SYNA_PINCTRL_GROUP("LCDD17", 0x20, 0x3, 0x12,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO_X39 */
			SYNA_PINCTRL_FUNC(0x1, "lcd"), /* LCDD17 */
			SYNA_PINCTRL_FUNC(0x2, "key"), /* ROW9 */
			SYNA_PINCTRL_FUNC(0x3, "i2s5")), /* BCLK */
	SYNA_PINCTRL_GROUP("LCDD18", 0x20, 0x3, 0x15,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO68 */
			SYNA_PINCTRL_FUNC(0x1, "lcd")), /* LCDD18 */
	SYNA_PINCTRL_GROUP("LCDD19", 0x20, 0x3, 0x18,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO69 */
			SYNA_PINCTRL_FUNC(0x1, "lcd")), /* LCDD19 */
	SYNA_PINCTRL_GROUP("LCDD20", 0x20, 0x3, 0x1b,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO70 */
			SYNA_PINCTRL_FUNC(0x1, "lcd")), /* LCDD20 */

	SYNA_PINCTRL_GROUP("LCDD21", 0x24, 0x3, 0x00,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO71 */
			SYNA_PINCTRL_FUNC(0x1, "lcd")), /* LCDD21 */
	SYNA_PINCTRL_GROUP("LCDD22", 0x24, 0x3, 0x03,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO_X40 */
			SYNA_PINCTRL_FUNC(0x1, "lcd")), /* LCDD22 */
	SYNA_PINCTRL_GROUP("LCDD23", 0x24, 0x3, 0x06,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO_X14 */
			SYNA_PINCTRL_FUNC(0x1, "lcd")), /* LCDD23 */
	SYNA_PINCTRL_GROUP("LPCLK", 0x24, 0x3, 0x09,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO_X15 */
			SYNA_PINCTRL_FUNC(0x1, "lpclk")), /* LPCLK */
	SYNA_PINCTRL_GROUP("LCDGPIO0", 0x24, 0x3, 0x0c,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO_X16 */
			SYNA_PINCTRL_FUNC(0x1, "lcdgpio")), /* LCDGPIO0 */
	SYNA_PINCTRL_GROUP("LCDGPIO1", 0x24, 0x3, 0x0f,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO_X17 */
			SYNA_PINCTRL_FUNC(0x1, "lcdgpio")), /* LCDGPIO1 */
	SYNA_PINCTRL_GROUP("LCDGPIO2", 0x24, 0x3, 0x12,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO_X18 */
			SYNA_PINCTRL_FUNC(0x1, "lcdgpio")), /* LCDGPIO2 */
	SYNA_PINCTRL_GROUP("LCDGPIO3", 0x24, 0x3, 0x15,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO_X10 */
			SYNA_PINCTRL_FUNC(0x1, "lcdgpio"), /* LCDGPIO3 */
			SYNA_PINCTRL_FUNC(0x2, "key"), /* COL4 */
			SYNA_PINCTRL_FUNC(0x3, "sdio")), /* SDIOB_CDn */
	SYNA_PINCTRL_GROUP("LCDGPIO4", 0x24, 0x3, 0x18,
			   SYNA_PINCTRL_FUNC(0x0, "gpio"), /* GPIO_X11 */
			SYNA_PINCTRL_FUNC(0x1, "lcdgpio"), /* LCDGPIO4 */
			SYNA_PINCTRL_FUNC(0x2, "key"), /* COL5 */
			SYNA_PINCTRL_FUNC(0x3, "sdio")), /* SDIOB_WP */
};

static const struct syna_pinctrl_desc myna2_soc_pinctrl_data = {
	.groups = myna2_soc_pinctrl_groups,
	.ngroups = ARRAY_SIZE(myna2_soc_pinctrl_groups),
};

#endif /* __PINCTRL_SYNA_MYNA2_H */
