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

#ifndef __DWCMSHC_SDHCI_H
#define __DWCMSHC_SDHCI_H
#include <common.h>
#include <dm.h>
#include <reset.h>
#include <sdhci.h>
#include <clk.h>

extern int mmc_send_cmd(struct mmc *mmc, struct mmc_cmd *cmd, struct mmc_data *data);

#define SDHCI_TUNING_LOOP_COUNT	128

/* Host Controller */
#define SDHCI_P_VENDOR_SPECIFIC_AREA	0xe8
#define SDHCI_P_VENDOR_SPECIFIC_AREA_MASK 0xfff
#define SDHCI_EMMC_CTRL_OFFSET			0x2c
#define CARD_IS_EMMC BIT(0)
#define EMMC_RST_N BIT(2)
#define EMMC_RST_N_OE BIT(3)

#define PHY_AT_CTRL_R_REG_OFFSET 0x40
#define AT_EN BIT(0)
#define CI_EN BIT(1)
#define SWIN_TH_EN BIT(2)
#define RPT_TUNE_ERR BIT(3)
#define TUNE_CLK_STOP_EN BIT(16)
#define PRE_CHANGE_DLY_SFT 17
#define PRE_CHANGE_DLY_MSK	(0x3 << PRE_CHANGE_DLY_SFT)
#define POST_CHANGE_DLY_SFT 19
#define POST_CHANGE_DLY_MSK (0x3 << POST_CHANGE_DLY_SFT)

/* PHY */
#define PHY_REG_BASE 0x300
#define PHY_REG(off) (PHY_REG_BASE + (off))

#define PHY_CNFG_REG PHY_REG(0)
#define PHY_RSTN BIT(0)
#define PHY_PWRGOOD BIT(1)

/* PHY PAD */
#define PHY_CMDPAD_CNFG_REG PHY_REG(0x4)
#define PHY_DATPAD_CNFG_REG PHY_REG(0x6)
#define PHY_CLKPAD_CNFG_REG PHY_REG(0x8)
#define PHY_STBPAD_CNFG_REG PHY_REG(0xa)
#define PHY_RSTNPAD_CNFG_REG PHY_REG(0xc)

/*PHY PAD GENERAL modes */
#define PAD_SP_8    0x8
#define PAD_SP_9    0x9
#define PAD_SN_8    0x8

/* PHY RX SEL modes */
#define RXSELOFF        0x0
#define SCHMITT1P8      0x1
#define SCHMITT3P3      0x2
#define SCHMITT1P2      0x3
#define COMPARATOR1P8   0x4
#define COMPARATOR1P2   0x5
#define COMPARATOR1P82  0x6
#define INTERNALLPBK    0x7

/* PHY WEAKPULL_EN modes */
#define WPE_DISABLE  0x0
#define WPE_PULLUP   0x1
#define WPE_PULLDOWN 0x2

/* PHY TXSLEW_CTRL_P modes */
#define TX_SLEW_P_0    0x0
#define TX_SLEW_P_2    0x2
#define TX_SLEW_P_3    0x3

/* PHY TXSLEW_CTRL_N modes */
#define TX_SLEW_N_2    0x2
#define TX_SLEW_N_3    0x3

#define PHY_COMMDL_CNFG_REG PHY_REG(0x1c)
#define DLSTEP_SEL BIT(0)
#define DLOUT_EN BIT(1)

#define PHY_SDCLKDL_CNFG_REG PHY_REG(0x1d)
#define EXTDLY_EN BIT(0)
#define BYPASS_EN BIT(1)
#define INPSEL_CNFG_SFT 2
#define INPSEL_CNFG_MSK (0x3 << INPSEL_CNFG_SFT)
#define UPDATE_DC BIT(4)

#define PHY_SDCLKDL_DC_REG PHY_REG(0x1e)
#define CCKDL_DC_SFT 0
#define CCKDL_DC_MSK (0x7f << CCKDL_DC_SFT)

#define PHY_SMPLDL_CNFG_REG PHY_REG(0x20)
#define SEXTDLY_EN BIT(0)
#define SBYPASS_EN BIT(1)
#define SINPSEL_CNFG_SFT 2
#define SINPSEL_CNFG_MSK (0x3 << SINPSEL_CNFG_SFT)
#define SINPSEL_OVERRIDE BIT(4)

#define PHY_ATDL_CNFG_REG PHY_REG(0x21)
#define AEXTDLY_EN BIT(0)
#define ABYPASS_EN BIT(1)
#define AINPSEL_CNFG_SFT 2
#define AINPSEL_CNFG_MSK (0x3 << AINPSEL_CNFG_SFT)

#define PHY_DLL_CTRL_REG PHY_REG(0x24)
#define DLL_EN BIT(0)

#define PHY_DLL_CNFG1_REG PHY_REG(0x25)
#define WAITCYCLE_SFT 0
#define SLVDLY_SFT 4
#define WAITCYCLE_MSK (0x3 << WAITCYCLE_SFT)
#define SLVDLY_MSK (0x3 << SLVDLY_SFT)

#define PHY_DLL_CNFG2_REG PHY_REG(0x26)

#define PHY_DLLDL_CNFG_REG PHY_REG(0x28)
#define SLV_INPSEL_SFT 5
#define SLV_INPSEL_MSK (0x3 << SLV_INPSEL_SFT)

#define PHY_DLLLBT_CNFG_REG PHY_REG(0x2c)

#define PHY_DLL_STATUS_REG PHY_REG(0x2e)
#define LOCK_STS BIT(0)
#define ERROR_STS BIT(1)

#define PHY_DLLDBG_MLKDC_REG PHY_REG(0x30)
#define PHY_DLLDBG_SLKDC_REG PHY_REG(0x32)

#define PHY_GEN_SETTING(pad_sp, pad_sn) \
	 ((((pad_sp) & 0x0f) << 16) | \
	 (((pad_sn) & 0x0f) << 20))
#define PHY_GEN_MASK PHY_GEN_SETTING(0xf, 0xf)

struct phy_gen_setting {
	u32 reg;
	u32 mask;
	u32 setting;
};

#define PHY_PAD_SETTING(rxsel, weakpull_en, txslew_ctrl_p, txslew_ctrl_n) \
	(((rxsel) & 0x3) | \
	(((weakpull_en) & 0x3) << 3) | \
	(((txslew_ctrl_p) & 0xf) << 5) | \
	((txslew_ctrl_n) & 0xf) << 9)
#define PHY_PAD_MASK PHY_PAD_SETTING(0x3, 0x3, 0xf, 0xf)
#define PHY_PAD_SETTING_NUM 5

struct phy_pad_setting {
	u32 reg;
	u16 mask;
	u16 setting;
};

struct dwcmshc_sdhci_plat {
	struct mmc_config cfg;
	struct mmc mmc;
	struct reset_ctl_bulk reset_ctl;
	u32 mmc_type;
	u32 sdclkdl_dc;
	u32 pad_sp;
	u32 pad_sn;
	u32 dll_delay_offset;
	enum mmc_voltage phy_voltage;
	int fixed_voltage;
};

struct phy_gen_setting gen_setting_1v8 = {PHY_CNFG_REG, PHY_GEN_MASK, PHY_GEN_SETTING(PAD_SP_8, PAD_SN_8)};
struct phy_pad_setting pad_setting_1v8[PHY_PAD_SETTING_NUM] = {
	{PHY_CMDPAD_CNFG_REG, PHY_PAD_MASK, PHY_PAD_SETTING(SCHMITT1P8, WPE_PULLUP, TX_SLEW_P_0, TX_SLEW_N_3)},
	{PHY_DATPAD_CNFG_REG, PHY_PAD_MASK, PHY_PAD_SETTING(SCHMITT1P8, WPE_PULLUP, TX_SLEW_P_0, TX_SLEW_N_3)},
	{PHY_CLKPAD_CNFG_REG, PHY_PAD_MASK, PHY_PAD_SETTING(RXSELOFF, WPE_DISABLE, TX_SLEW_P_0, TX_SLEW_N_3)},
	{PHY_STBPAD_CNFG_REG, PHY_PAD_MASK, PHY_PAD_SETTING(SCHMITT1P8, WPE_PULLDOWN, TX_SLEW_P_0, TX_SLEW_N_3)},
	{PHY_RSTNPAD_CNFG_REG, PHY_PAD_MASK, PHY_PAD_SETTING(SCHMITT1P8, WPE_PULLUP, TX_SLEW_P_0, TX_SLEW_N_3) }
};

struct phy_gen_setting gen_setting_3v3 = {PHY_CNFG_REG, PHY_GEN_MASK, PHY_GEN_SETTING(PAD_SP_9, PAD_SN_8)};
struct phy_pad_setting pad_setting_3v3[PHY_PAD_SETTING_NUM] = {
	{PHY_CMDPAD_CNFG_REG, PHY_PAD_MASK, PHY_PAD_SETTING(SCHMITT3P3, WPE_PULLUP, TX_SLEW_P_3, TX_SLEW_N_2)},
	{PHY_DATPAD_CNFG_REG, PHY_PAD_MASK, PHY_PAD_SETTING(SCHMITT3P3, WPE_PULLUP, TX_SLEW_P_3, TX_SLEW_N_2)},
	{PHY_CLKPAD_CNFG_REG, PHY_PAD_MASK, PHY_PAD_SETTING(RXSELOFF, WPE_DISABLE, TX_SLEW_P_3, TX_SLEW_N_2)},
	{PHY_STBPAD_CNFG_REG, PHY_PAD_MASK, PHY_PAD_SETTING(SCHMITT3P3, WPE_PULLDOWN, TX_SLEW_P_3, TX_SLEW_N_2)},
	{PHY_RSTNPAD_CNFG_REG, PHY_PAD_MASK, PHY_PAD_SETTING(SCHMITT3P3, WPE_PULLUP, TX_SLEW_P_3, TX_SLEW_N_2) }
};

#ifdef CONFIG_TARGET_PLATYPUS
u8 phy_delay[MMC_MODES_END] = {
	40,  /* MMC_LEGACY */
	127, /* SD_LEGACY */
	40,  /* MMC_HS */
	35,  /* SD_HS */
	40,  /* MMC_HS_52 */
	40,  /* MMC_DDR_52 */
	100, /* UHS_SDR12 */
	100, /* UHS_SDR25 */
	100, /* UHS_SDR50 */
	43,  /* UHS_DDR50 */
	43,  /* UHS_SDR104 */
	40,  /* MMC_HS_200 */
	20,  /* MMC_HS_400 */
	0,   /* MMC_HS_400_ES */
};
#endif

#ifdef CONFIG_TARGET_DOLPHIN
u8 phy_delay[MMC_MODES_END] = {
	40,  /* MMC_LEGACY */
	127, /* SD_LEGACY */
	40,  /* MMC_HS */
	35,  /* SD_HS */
	40,  /* MMC_HS_52 */
	40,  /* MMC_DDR_52 */
	100, /* UHS_SDR12 */
	100, /* UHS_SDR25 */
	100, /* UHS_SDR50 */
	95,  /* UHS_DDR50 */
	50,  /* UHS_SDR104 */
	40,  /* MMC_HS_200 */
	20,  /* MMC_HS_400 */
	0,   /* MMC_HS_400_ES */
};
#endif

#ifdef CONFIG_TARGET_MYNA2
u8 phy_delay[MMC_MODES_END] = {
	40,  /* MMC_LEGACY */
	127, /* SD_LEGACY */
	40,  /* MMC_HS */
	35,  /* SD_HS */
	40,  /* MMC_HS_52 */
	40,  /* MMC_DDR_52 */
	100, /* UHS_SDR12 */
	100, /* UHS_SDR25 */
	100, /* UHS_SDR50 */
	43,  /* UHS_DDR50 */
	43,  /* UHS_SDR104 */
	40,  /* MMC_HS_200 */
	20,  /* MMC_HS_400 */
	0,   /* MMC_HS_400_ES */
};
#endif

#endif /* __DWCMSHC_SDHCI_H */
