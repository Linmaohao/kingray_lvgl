/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"

#define STATUS_PAGE_TITLE				"STATUS"

#define STATUS_TIP_X					3
#define STATUS_TIP_Y					40
#define STATUS_TIP_WIDTH				26
#define STATUS_TIP_X_SPAN				170
#define STATUS_TIP_Y_SPAN				32

#define STATUS_STR_WIDTH				100


#define STATUS_PAGE_Y					104
#define STATUS_PAGE_HEIGHT				138

#define STATUS_ROUTER_X					3
#define STATUS_ROUTER_Y					10
#define STATUS_ROUTER_X_SPAN			34
#define STATUS_ROUTER_Y_SPAN			31

#define STATUS_CHN_X					214
#define STATUS_CHN_Y					(STATUS_ROUTER_Y + 5)
#define STATUS_CHN_Y_SPAN				STATUS_ROUTER_Y_SPAN
#define STATUS_CHN_WIDTH				56
#define STATUS_CHN_HEIGHT				34

#define STATUS_ROLLER_X					156
#define STATUS_ROLLER_Y					STATUS_CHN_Y
#define STATUS_ROLLER_Y_SPAN			62
#define STATUS_ROLLER_WIDTH				34
#define STATUS_ROLLER_HEIGHT			46



const uint8_t work_mode[][9] =
{
	"STEREO",
	"PRALLEL",
	"BRIDGE",
	"MATRIX",
};

const uint8_t work_mode_tips[][9] =
{
	"S",
	"P",
	"B",
	"M",
};

const uint8_t work_mode_in_channel[][2] =
{
	"A",
	"B",
	"C",
	"D",
};

const uint8_t channel_name[][CHANNEL_SIZE] =
{
	{"CH1"},
	{"CH2"},
	{"CH3"},
	{"CH4"},
};

const lv_point_t channel_out_line[2] =
{
	{0, 0},
	{10, 0},
};

const lv_point_t channel_polyline[4] =
{
	{0, 0},
	{6, 0},
	{6, 20},
	{12, 20},
};

const uint8_t* work_mode_options = "S\nP\nB\nM";

void setup_scr_status_page(lv_ui *ui)
{
	//Write codes status_page
	ui->status_page = lv_obj_create(NULL);
	lv_obj_set_size(ui->status_page, LV_HOR_RES_MAX, LV_VER_RES_MAX);
	lv_obj_set_scrollbar_mode(ui->status_page, LV_SCROLLBAR_MODE_OFF);

	//Write style for status_page, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->status_page, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->status_page, BACKGROUND_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->status_page, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes status_page_title
	ui->status_page_title = lv_label_create(ui->status_page);
	lv_label_set_long_mode(ui->status_page_title, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->status_page_title, 0, 0);
	lv_obj_set_size(ui->status_page_title, LV_HOR_RES_MAX, TITLE_HEIGHT);

	//Write style for status_page_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->status_page_title, MAIN_FONT_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->status_page_title, &lv_font_montserratMedium_24, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->status_page_title, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->status_page_title, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->status_page_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->status_page_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->status_page_title, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->status_page_title, DESIGNATED_COLOR_BLUE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->status_page_title, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_label_set_text(ui->status_page_title, STATUS_PAGE_TITLE);

	for (int i = 0; i < 2; i++){
		for (int j = 0; j < 2; j++){
			int k = i * 2 + j;
			//Write codes status_page_tips
			ui->status_page_tips[k] = lv_label_create(ui->status_page);
			lv_obj_set_pos(ui->status_page_tips[k], STATUS_TIP_X + i * STATUS_TIP_X_SPAN, STATUS_TIP_Y + j * STATUS_TIP_Y_SPAN);
			lv_label_set_text(ui->status_page_tips[k], work_mode_tips[k]);
			lv_label_set_long_mode(ui->status_page_tips[k], LV_LABEL_LONG_WRAP);
			lv_obj_set_size(ui->status_page_tips[k], STATUS_TIP_WIDTH, STATUS_TIP_WIDTH);

			//Write style for status_page_tips, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
			lv_obj_set_style_text_align(ui->status_page_tips[k], LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
			lv_obj_set_style_text_font(ui->status_page_tips[k], &lv_font_montserratMedium_22, LV_PART_MAIN|LV_STATE_DEFAULT);
			lv_obj_set_style_text_color(ui->status_page_tips[k], lv_color_black(), LV_PART_MAIN|LV_STATE_DEFAULT);
			lv_obj_set_style_bg_opa(ui->status_page_tips[k], LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
			lv_obj_set_style_bg_color(ui->status_page_tips[k], lv_color_white(), LV_PART_MAIN|LV_STATE_DEFAULT);
			lv_obj_set_style_radius(ui->status_page_tips[k], 3, LV_PART_MAIN|LV_STATE_DEFAULT);
			lv_obj_set_style_pad_top(ui->status_page_tips[k], 1, LV_PART_MAIN|LV_STATE_DEFAULT);

			//Write codes status_page_tips_description
			ui->status_page_tips_description[k] = lv_label_create(ui->status_page);
			lv_obj_align_to(ui->status_page_tips_description[k], ui->status_page_tips[k], LV_ALIGN_OUT_RIGHT_TOP, 4, 0);
			lv_label_set_text(ui->status_page_tips_description[k], work_mode[k]);
			lv_label_set_long_mode(ui->status_page_tips_description[k], LV_LABEL_LONG_WRAP);
			lv_obj_set_size(ui->status_page_tips_description[k], STATUS_STR_WIDTH, STATUS_TIP_WIDTH);

			//Write style for status_page_tips, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
			lv_obj_set_style_text_align(ui->status_page_tips_description[k], LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
			lv_obj_set_style_text_font(ui->status_page_tips_description[k], &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
			lv_obj_set_style_text_color(ui->status_page_tips_description[k], lv_color_white(), LV_PART_MAIN|LV_STATE_DEFAULT);
			lv_obj_set_style_bg_opa(ui->status_page_tips_description[k], LV_OPA_TRANSP, LV_PART_MAIN|LV_STATE_DEFAULT);
			lv_obj_set_style_pad_top(ui->status_page_tips_description[k], 2, LV_PART_MAIN|LV_STATE_DEFAULT);
		}
	}

	//Write codes status_page_tips
	ui->status_page_work_mode_page = lv_obj_create(ui->status_page);
	lv_obj_set_size(ui->status_page_work_mode_page, LV_HOR_RES_MAX, STATUS_PAGE_HEIGHT);
	lv_obj_set_pos(ui->status_page_work_mode_page, 0, STATUS_PAGE_Y);
	lv_obj_set_scrollbar_mode(ui->status_page_work_mode_page, LV_SCROLLBAR_MODE_OFF);
	lv_obj_set_style_pad_all(ui->status_page_work_mode_page, 0, 0);

	//Write style for status_page_work_mode_page, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->status_page_work_mode_page, LV_OPA_TRANSP, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->status_page_work_mode_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	for (int out = 0; out < LAYOUT_OUTPUT_SIZE; out++)
	{
		for (int in = 0; in < LAYOUT_INPUT_SIZE; in++)
		{
			//Write codes status_page_btn_router
			ui->status_page_btn_router[out][in] = lv_btn_create(ui->status_page_work_mode_page);
			ui->status_page_btn_label[out][in] = lv_label_create(ui->status_page_btn_router[out][in]);
			lv_label_set_text(ui->status_page_btn_label[out][in], work_mode_in_channel[in]);
			lv_obj_align(ui->status_page_btn_label[out][in], LV_ALIGN_CENTER, 0, 0);
			lv_obj_set_pos(ui->status_page_btn_router[out][in], STATUS_ROUTER_X + in * STATUS_ROUTER_X_SPAN, \
							STATUS_ROUTER_Y + out * STATUS_ROUTER_Y_SPAN);
			lv_obj_set_size(ui->status_page_btn_router[out][in], STATUS_TIP_WIDTH, STATUS_TIP_WIDTH);

			//Write style for status_page_btn_router, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
			lv_obj_set_style_bg_opa(ui->status_page_btn_router[out][in], LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
			lv_obj_set_style_bg_color(ui->status_page_btn_router[out][in], lv_color_black(), LV_PART_MAIN|LV_STATE_DEFAULT);
			lv_obj_set_style_border_width(ui->status_page_btn_router[out][in], 1, LV_PART_MAIN|LV_STATE_DEFAULT);
			lv_obj_set_style_border_color(ui->status_page_btn_router[out][in], lv_color_white(), LV_PART_MAIN|LV_STATE_DEFAULT);
			lv_obj_set_style_radius(ui->status_page_btn_router[out][in], 2, LV_PART_MAIN|LV_STATE_DEFAULT);
			lv_obj_set_style_text_color(ui->status_page_btn_router[out][in], MAIN_FONT_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
			lv_obj_set_style_text_font(ui->status_page_btn_router[out][in], &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
			lv_obj_set_style_text_align(ui->status_page_btn_router[out][in], LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
			lv_obj_set_style_shadow_width(ui->status_page_btn_router[out][in], 0, LV_PART_MAIN|LV_STATE_DEFAULT);

			//Write style for status_page_btn_router, Part: LV_PART_MAIN, State: LV_STATE_FOCUSED.
			lv_obj_set_style_bg_opa(ui->status_page_btn_router[out][in], LV_OPA_COVER, LV_PART_MAIN|LV_STATE_FOCUSED);
			lv_obj_set_style_bg_color(ui->status_page_btn_router[out][in], DESIGNATED_COLOR_BLUE, LV_PART_MAIN|LV_STATE_FOCUSED);
			lv_obj_set_style_outline_opa(ui->status_page_btn_router[out][in], LV_OPA_COVER, LV_PART_MAIN|LV_STATE_FOCUSED);
			lv_obj_set_style_outline_color(ui->status_page_btn_router[out][in], lv_palette_lighten(LV_PALETTE_ORANGE, 1), LV_PART_MAIN|LV_STATE_FOCUSED);
			lv_obj_set_style_outline_pad(ui->status_page_btn_router[out][in], 2, LV_PART_MAIN|LV_STATE_FOCUSED);
			lv_obj_set_style_outline_width(ui->status_page_btn_router[out][in], 2, LV_PART_MAIN|LV_STATE_FOCUSED);
		}
	}

	for(int i = 0; i < CHANNEL_SIZE; i++){
		// Write codes status_page_channel_name
		ui->status_page_channel_name[i] = lv_label_create(ui->status_page_work_mode_page);
		lv_label_set_long_mode(ui->status_page_channel_name[i], LV_LABEL_LONG_WRAP);
		lv_label_set_text(ui->status_page_channel_name[i], channel_name[i]);
		lv_obj_set_pos(ui->status_page_channel_name[i], STATUS_CHN_X, STATUS_CHN_Y + STATUS_CHN_Y_SPAN * i);
		lv_obj_set_size(ui->status_page_channel_name[i], STATUS_CHN_WIDTH, STATUS_CHN_HEIGHT);
		//lv_obj_align(ui->status_page_channel_name[i], LV_ALIGN_CENTER, 0, 0);

		//Write style for status_page_channel_name, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
		lv_obj_set_style_text_color(ui->status_page_channel_name[i], MAIN_FONT_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_text_font(ui->status_page_channel_name[i], &lv_font_montserratMedium_18, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_text_letter_space(ui->status_page_channel_name[i], 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	}

	for(int i = 0; i < CHANNEL_SIZE; i++){
		// Write codes status_page_channel_out_line
		ui->status_page_channel_out_line[i] = lv_line_create(ui->status_page_work_mode_page);
		lv_line_set_points(ui->status_page_channel_out_line[i], channel_out_line, 2);
		lv_obj_align_to(ui->status_page_channel_out_line[i], ui->status_page_channel_name[i], LV_ALIGN_OUT_LEFT_MID, -4, -8);

		//Write style for status_page_channel_out_line, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
		lv_obj_set_style_line_width(ui->status_page_channel_out_line[i], 3, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_line_color(ui->status_page_channel_out_line[i], lv_color_white(), LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_line_rounded(ui->status_page_channel_out_line[i], true, LV_PART_MAIN|LV_STATE_DEFAULT);
	}

	for(int i = 0; i < CHANNEL_SIZE / 2; i++){
		//Write code status_page_work_mode_select
		ui->status_page_work_mode_select[i] = lv_roller_create(ui->status_page_work_mode_page);
		lv_roller_set_options(ui->status_page_work_mode_select[i], work_mode_options, LV_ROLLER_MODE_NORMAL);
		lv_roller_set_visible_row_count(ui->status_page_work_mode_select[i], 1);
		lv_obj_set_pos(ui->status_page_work_mode_select[i], STATUS_ROLLER_X, STATUS_ROLLER_Y + STATUS_ROLLER_Y_SPAN * i);
		lv_obj_set_size(ui->status_page_work_mode_select[i], STATUS_ROLLER_WIDTH, STATUS_ROLLER_HEIGHT);

		//Write style for status_page_work_mode_select, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
		lv_obj_set_style_bg_opa(ui->status_page_work_mode_select[i], LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_bg_color(ui->status_page_work_mode_select[i], BACKGROUND_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
    	lv_obj_set_style_radius(ui->status_page_work_mode_select[i], 2, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_border_width(ui->status_page_work_mode_select[i], 0, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_pad_all(ui->status_page_work_mode_select[i], 0, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_text_font(ui->status_page_work_mode_select[i], &lv_font_montserratMedium_24, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_border_width(ui->status_page_work_mode_select[i], 1, LV_PART_SELECTED|LV_STATE_DEFAULT);
		lv_obj_set_style_border_color(ui->status_page_work_mode_select[i], lv_color_white(), LV_PART_SELECTED|LV_STATE_DEFAULT);

		//Write style for status_page_work_mode_select, Part: LV_PART_SELECTED, State: LV_STATE_FOCUSED.
		lv_obj_set_style_text_color(ui->status_page_work_mode_select[i], lv_color_black(), LV_PART_SELECTED|LV_STATE_FOCUSED);
		lv_obj_set_style_bg_color(ui->status_page_work_mode_select[i], lv_color_white(), LV_PART_SELECTED|LV_STATE_FOCUSED);
		lv_obj_set_style_outline_opa(ui->status_page_work_mode_select[i], LV_OPA_COVER, LV_STATE_FOCUSED);
		lv_obj_set_style_outline_color(ui->status_page_work_mode_select[i], lv_palette_lighten(LV_PALETTE_ORANGE, 1), LV_STATE_FOCUSED);
		lv_obj_set_style_outline_pad(ui->status_page_work_mode_select[i], 2, LV_STATE_FOCUSED);
		lv_obj_set_style_outline_width(ui->status_page_work_mode_select[i], 2, LV_STATE_FOCUSED);

		//Write style for status_page_work_mode_select, Part: LV_PART_SELECTED, State: LV_STATE_FOCUSED|LV_STATE_EDITED.
		lv_obj_set_style_bg_color(ui->status_page_work_mode_select[i], lv_palette_main(LV_PALETTE_GREEN), LV_PART_SELECTED|(LV_STATE_FOCUSED|LV_STATE_EDITED));
		lv_obj_set_style_outline_opa(ui->status_page_work_mode_select[i], LV_OPA_COVER, LV_STATE_FOCUSED|LV_STATE_EDITED);
		lv_obj_set_style_outline_color(ui->status_page_work_mode_select[i], lv_palette_lighten(LV_PALETTE_ORANGE, 1), LV_STATE_FOCUSED|LV_STATE_EDITED);
		lv_obj_set_style_outline_pad(ui->status_page_work_mode_select[i], 2, LV_STATE_FOCUSED|LV_STATE_EDITED);
		lv_obj_set_style_outline_width(ui->status_page_work_mode_select[i], 2, LV_STATE_FOCUSED|LV_STATE_EDITED);

		//lv_roller_set_selected(ui->status_page_work_mode_select[i], name_record[i], LV_ANIM_OFF);

		//Write codes status_page_speaker
		ui->status_page_speaker[i] = lv_img_create(ui->status_page_work_mode_page);
		lv_img_set_src(ui->status_page_speaker[i], &router_speaker);
		lv_obj_align_to(ui->status_page_speaker[i], ui->status_page_work_mode_select[i], LV_ALIGN_OUT_RIGHT_MID, 75, 0);

		//Write codes status_page_poly_line
		ui->status_page_poly_line[i] = lv_line_create(ui->status_page_work_mode_page);
		lv_line_set_points(ui->status_page_poly_line[i], channel_polyline, 4);
		lv_obj_align_to(ui->status_page_poly_line[i], ui->status_page_work_mode_select[i], LV_ALIGN_OUT_LEFT_MID, -6, -4);

		//Write style for status_page_poly_line, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
		lv_obj_set_style_line_width(ui->status_page_poly_line[i], 3, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_line_color(ui->status_page_poly_line[i], lv_color_white(), LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_line_rounded(ui->status_page_poly_line[i], true, LV_PART_MAIN|LV_STATE_DEFAULT);
		//lv_obj_add_flag(ui->status_page_poly_line[i], LV_OBJ_FLAG_HIDDEN);
	}

	for(int i = 0; i < CHANNEL_SIZE; i++){
		// Write codes status_page_channel_in_line
		ui->status_page_channel_in_line[i] = lv_line_create(ui->status_page_work_mode_page);
		lv_line_set_points(ui->status_page_channel_in_line[i], channel_out_line, 2);
		lv_obj_align_to(ui->status_page_channel_in_line[i], ui->status_page_channel_out_line[i], LV_ALIGN_OUT_LEFT_MID, -50, -1);

		//Write style for status_page_channel_in_line, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
		lv_obj_set_style_line_width(ui->status_page_channel_in_line[i], 3, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_line_color(ui->status_page_channel_in_line[i], lv_color_white(), LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_line_rounded(ui->status_page_channel_in_line[i], true, LV_PART_MAIN|LV_STATE_DEFAULT);
		//lv_obj_add_flag(ui->status_page_channel_in_line[i], LV_OBJ_FLAG_HIDDEN);
	}

	// Add group
	ui->status_page_group = lv_group_create();
	lv_group_add_obj(ui->status_page_group, ui->status_page_work_mode_select[0]);
	for (int i = 0; i < LAYOUT_OUTPUT_SIZE / 2; i++){
		for (int j = 0; j < LAYOUT_OUTPUT_SIZE; j++){
			lv_group_add_obj(ui->status_page_group, ui->status_page_btn_router[i][j]);
		}
	}
	lv_group_add_obj(ui->status_page_group, ui->status_page_work_mode_select[1]);
	for (int i = LAYOUT_OUTPUT_SIZE / 2; i < LAYOUT_OUTPUT_SIZE; i++){
		for (int j = 0; j < LAYOUT_INPUT_SIZE; j++){
			lv_group_add_obj(ui->status_page_group, ui->status_page_btn_router[i][j]);
		}
	}
	lv_group_focus_obj(ui->status_page_work_mode_select[0]);

	events_init_status_page(ui);

	//Update current screen layout.
	lv_obj_update_layout(ui->status_page);

}