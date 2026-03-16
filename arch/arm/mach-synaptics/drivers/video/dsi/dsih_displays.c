// SPDX-License-Identifier: GPL-2.0
/**
 * Copyright (C) 2018 Synopsys, Inc.
 *
 * @file dsih_displays.c
 * @brief included as a part of MIPI DSI Host driver
 * included as a part of Synopsys MIPI DSI Host controller driver
 *
 * @author Luis Oliveira <luis.oliveira@synopsys.com>
 */
/*
 * Copyright (C) 2024 Synaptics Incorporated
 */

#include "dsih_displays.h"
#include "dsih_api.h"
#include "dsih_hal.h"
#include "dsih_dphy.h"

static struct mipi_dsi_dev *mipi_dev = NULL;

void copy_dpi_param_changes(dsih_dpi_video_t * from_param,
				dsih_dpi_video_t * to_param)
{
	to_param->no_of_lanes = from_param->no_of_lanes;
	to_param->non_continuous_clock = from_param->non_continuous_clock;
	to_param->virtual_channel = from_param->virtual_channel;
	to_param->video_mode = from_param->video_mode;
	to_param->byte_clock = from_param->byte_clock;
	to_param->pixel_clock = from_param->pixel_clock;
	to_param->color_coding = from_param->color_coding;
	to_param->is_18_loosely = from_param->is_18_loosely;
	to_param->h_polarity = from_param->h_polarity;
	to_param->h_active_pixels = from_param->h_active_pixels;
	to_param->h_sync_pixels = from_param->h_sync_pixels;
	to_param->h_back_porch_pixels = from_param->h_back_porch_pixels;
	to_param->h_total_pixels = from_param->h_total_pixels;
	to_param->v_polarity = from_param->v_polarity;
	to_param->v_active_lines = from_param->v_active_lines;
	to_param->v_sync_lines = from_param->v_sync_lines;
	to_param->v_back_porch_lines = from_param->v_back_porch_lines;
	to_param->v_total_lines = from_param->v_total_lines;
	to_param->max_hs_to_lp_cycles = from_param->max_hs_to_lp_cycles;
	to_param->max_lp_to_hs_cycles = from_param->max_lp_to_hs_cycles;
	to_param->max_clk_hs_to_lp_cycles = from_param->max_clk_hs_to_lp_cycles;
	to_param->max_clk_lp_to_hs_cycles = from_param->max_clk_lp_to_hs_cycles;
	to_param->eotp_rx_en = from_param->eotp_rx_en;
	to_param->eotp_tx_en = from_param->eotp_tx_en;
	to_param->no_of_chunks = from_param->no_of_chunks;
	to_param->null_packet_size = from_param->null_packet_size;
	to_param->dpi_lp_cmd_en = from_param->dpi_lp_cmd_en;
}

void copy_edpi_param_changes(dsih_cmd_mode_video_t * from_param,
				 dsih_cmd_mode_video_t * to_param)
{
	to_param->color_coding = from_param->color_coding;
	to_param->virtual_channel = from_param->virtual_channel;
	to_param->lp = from_param->lp;
	to_param->te = from_param->te;
	to_param->bta = from_param->bta;
	to_param->h_start = from_param->h_start;
	to_param->h_active_pixels = from_param->h_active_pixels;
	to_param->packet_size = from_param->packet_size;
	to_param->v_start = from_param->v_start;
	to_param->v_active_lines = from_param->v_active_lines;
	to_param->no_of_lanes = from_param->no_of_lanes;
	to_param->byte_clock = from_param->byte_clock;
	to_param->pixel_clock = from_param->pixel_clock;
}

/****************************************/
/*	look up tables					*/
/****************************************/
int pre_video_mode(struct mipi_dsi_dev *dev, unsigned mode, int lanes)
{
	dsi_get_transition_times(dev);
	return 0;
}

int pre_command_mode(struct mipi_dsi_dev *dev, unsigned mode, int lanes)
{
	return 0;
}


void dsi_register_device (void *mipi)
{
	mipi_dev = (struct mipi_dsi_dev*) mipi;
}

int dsi_panel_send_cmd (unsigned int cmdsize, unsigned char *pcmd)
{
    int i = 0, retval = 0;

	if (!mipi_dev) {
		pr_err("MIPI not init/registered\n");
		return -EINVAL;
	}

	mipi_dsih_cmd_mode(mipi_dev, 1);
	while (i < cmdsize)
	{
		/*Op-code*/
		switch (pcmd[i])
		{
			case DSI_CMD_DELAY:
				{
					unsigned int delay;
					delay = pcmd[i+1] |
						(pcmd[i+2] << 8) |
						(pcmd[i+3] << 16) |
						(pcmd[i+4] << 24);
					udelay(delay);
					i+=5;
				}
				break;

			case DSI_CMD_BYTE_WRITE:
			case DSI_CMD_SHORT_WRITE:
			case GEN_CMD_BYTE_WRITE:
			case GEN_CMD_SHORT_WRITE:
				{
					mipi_dsih_gen_wr_packet(mipi_dev, 0,
							pcmd[i],
							&pcmd[i+2],
							pcmd[i+1]);
					i = i + pcmd[i+1] + 2;
				}
				break;

			case GEN_CMD_LONG_WRITE:
			case DSI_CMD_LONG_WRITE:
				{
					unsigned char dsi_cmd[MAX_DSI_LONG_WRITE_PARAMS];
					dsi_cmd[0] = pcmd[i+1];
					dsi_cmd[1] = 0;
					memcpy(&dsi_cmd[2], &pcmd[i+2], dsi_cmd[0]);
					mipi_dsih_gen_wr_packet(mipi_dev, 0,
							pcmd[i],
							dsi_cmd,
							pcmd[i+1]+2);
					i = i + pcmd[i+1] + 2;
				}
				break;

			default:
				{
					retval = -1;
					pr_err("Unsupported Command[%d]\n", pcmd[i]);
				}
				break;
		}

		if (retval == -1)
			break;
	}

	mipi_dsih_cmd_mode(mipi_dev, 0);
	return retval;
}
