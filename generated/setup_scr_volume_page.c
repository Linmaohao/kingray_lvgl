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

#define VOLUME_PAGE_TITLE				"VOLUME"

#define VOL_CTRL_MIN					-600      // ->60db
#define VOL_CTRL_MAX					150       // ->15db

#define VOL_CHN_X						1
#define VOL_CHN_WIDTH					68
#define VOL_CHN_Y						10
#define VOL_CHN_HEIGHT					30
#define VOL_CHN_Y_SPAN					38

#define VOL_CHN_MUTE_WIDTH				30

#define VOL_CHN_GAIN_WIDTH				130  
#define VOL_CHN_GAIN_HEIGHT				10
#define VOL_CHN_GAIN_LBL_WIDTH			66


void setup_scr_volume_page(lv_ui *ui)
{
	//Write codes volume_page
	ui->volume_page = lv_obj_create(NULL);
	lv_obj_set_size(ui->volume_page, LV_HOR_RES_MAX, LV_VER_RES_MAX);
	lv_obj_set_scrollbar_mode(ui->volume_page, LV_SCROLLBAR_MODE_OFF);

	//Write style for volume_page, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->volume_page, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->volume_page, BACKGROUND_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->volume_page, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes volume_page_title
	ui->volume_page_title = lv_label_create(ui->volume_page);
	lv_label_set_long_mode(ui->volume_page_title, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->volume_page_title, 0, 0);
	lv_obj_set_size(ui->volume_page_title, LV_HOR_RES_MAX, TITLE_HEIGHT);

	//Write style for volume_page_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->volume_page_title, MAIN_FONT_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->volume_page_title, &lv_font_montserratMedium_24, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->volume_page_title, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->volume_page_title, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->volume_page_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->volume_page_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->volume_page_title, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->volume_page_title, DESIGNATED_COLOR_BLUE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->volume_page_title, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_label_set_text(ui->volume_page_title, VOLUME_PAGE_TITLE);

    //Write codes menu_page_list_page
    ui->volume_page_list_page = lv_obj_create(ui->volume_page);
    lv_obj_set_size(ui->volume_page_list_page, LV_HOR_RES_MAX, LV_VER_RES_MAX - TITLE_HEIGHT - 10);
    lv_obj_set_pos(ui->volume_page_list_page, 0, TITLE_HEIGHT + 4);
    lv_obj_set_scrollbar_mode(ui->volume_page_list_page, LV_SCROLLBAR_MODE_OFF);
	lv_obj_set_style_pad_all(ui->volume_page_list_page, 0, 0);

	//Write style for volume_page_list_page, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->volume_page_list_page, LV_OPA_TRANSP, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->volume_page_list_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->volume_page_list_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Create a group
	ui->volume_page_group = lv_group_create();

	for(int i = 0; i < LAYOUT_TOTAL_CHN_SIZE; i++){
		//Write codes volume_page_channel_name
		ui->volume_page_channel_name[i] = lv_label_create(ui->volume_page_list_page);
		lv_label_set_long_mode(ui->volume_page_channel_name[i], LV_LABEL_LONG_WRAP);
		lv_obj_set_pos(ui->volume_page_channel_name[i], VOL_CHN_X, VOL_CHN_Y + VOL_CHN_Y_SPAN * i);
		lv_obj_set_size(ui->volume_page_channel_name[i], VOL_CHN_WIDTH, VOL_CHN_HEIGHT);

		//Write style for volume_page_channel_name, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
		set_channel_name_style(ui->volume_page_channel_name[i]);
		if(i < LAYOUT_INPUT_SIZE)
			lv_label_set_text(ui->volume_page_channel_name[i], in_channel_label[i]);
		else
			lv_label_set_text(ui->volume_page_channel_name[i], out_channel_label[i - LAYOUT_INPUT_SIZE]);

		//Write codes volume_page_mute_btn
		ui->volume_page_mute_btn[i] = lv_btn_create(ui->volume_page_list_page);
		ui->volume_page_mute_label[i] = lv_label_create(ui->volume_page_mute_btn[i]);
		lv_label_set_text(ui->volume_page_mute_label[i], "M");
		lv_label_set_long_mode(ui->volume_page_mute_label[i], LV_LABEL_LONG_WRAP);
		lv_obj_align(ui->volume_page_mute_label[i], LV_ALIGN_CENTER, 0, 0);
		lv_obj_set_size(ui->volume_page_mute_btn[i], VOL_CHN_MUTE_WIDTH, VOL_CHN_MUTE_WIDTH);
		lv_obj_align_to(ui->volume_page_mute_btn[i], ui->volume_page_channel_name[i], LV_ALIGN_OUT_RIGHT_TOP, 6, 0);

		//Write style for volume_page_mute_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
		lv_obj_set_style_bg_opa(ui->volume_page_mute_btn[i], 0, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_border_width(ui->volume_page_mute_btn[i], 2, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_border_color(ui->volume_page_mute_btn[i], lv_color_white(), LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_radius(ui->volume_page_mute_btn[i], 2, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_text_color(ui->volume_page_mute_btn[i], MAIN_FONT_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_text_font(ui->volume_page_mute_btn[i], &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_text_align(ui->volume_page_mute_btn[i], LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_shadow_width(ui->volume_page_mute_btn[i], 0, LV_PART_MAIN|LV_STATE_DEFAULT);

		//Write style for volume_page_mute_btn, Part: LV_PART_MAIN, State: LV_STATE_FOCUSED.
		lv_obj_set_style_bg_opa(ui->volume_page_mute_btn[i], LV_OPA_COVER, LV_PART_MAIN|LV_STATE_FOCUSED);
		lv_obj_set_style_bg_color(ui->volume_page_mute_btn[i], lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN|LV_STATE_FOCUSED);
		lv_obj_set_style_outline_opa(ui->volume_page_mute_btn[i], LV_OPA_COVER, LV_PART_MAIN|LV_STATE_FOCUSED);
		lv_obj_set_style_outline_color(ui->volume_page_mute_btn[i], lv_palette_lighten(LV_PALETTE_ORANGE, 1), LV_PART_MAIN|LV_STATE_FOCUSED);
		lv_obj_set_style_outline_pad(ui->volume_page_mute_btn[i], 2, LV_PART_MAIN|LV_STATE_FOCUSED);
		lv_obj_set_style_outline_width(ui->volume_page_mute_btn[i], 3, LV_PART_MAIN|LV_STATE_FOCUSED);

		//Write codes volume_page_gain
		ui->volume_page_gain[i] = lv_slider_create(ui->volume_page_list_page);
		lv_obj_set_size(ui->volume_page_gain[i], VOL_CHN_GAIN_WIDTH, 10);
		lv_obj_align_to(ui->volume_page_gain[i], ui->volume_page_mute_btn[i], LV_ALIGN_OUT_RIGHT_MID, 9, 0);
		lv_slider_set_range(ui->volume_page_gain[i], VOL_CTRL_MIN, VOL_CTRL_MAX);

		//Write style for volume_page_gain, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
		lv_obj_set_style_border_width(ui->volume_page_gain[i], 1, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_border_color(ui->volume_page_gain[i], lv_color_white(), LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_bg_color(ui->volume_page_gain[i], lv_palette_main(LV_PALETTE_GREEN), LV_PART_INDICATOR|LV_STATE_DEFAULT);
		lv_obj_set_style_bg_color(ui->volume_page_gain[i], lv_color_white(), LV_PART_KNOB|LV_STATE_DEFAULT);

		//Write style for volume_page_gain, Part: LV_PART_MAIN, State: LV_STATE_FOCUSED.
		lv_obj_set_style_outline_opa(ui->volume_page_gain[i], LV_OPA_COVER, LV_PART_MAIN|LV_STATE_FOCUSED);
		lv_obj_set_style_outline_color(ui->volume_page_gain[i], lv_palette_lighten(LV_PALETTE_ORANGE, 1), LV_PART_MAIN|LV_STATE_FOCUSED);
		lv_obj_set_style_outline_pad(ui->volume_page_gain[i], 4, LV_PART_MAIN|LV_STATE_FOCUSED);
		lv_obj_set_style_outline_width(ui->volume_page_gain[i], 2, LV_PART_MAIN|LV_STATE_FOCUSED);

		//Write style for volume_page_gain, Part: LV_PART_MAIN, State: LV_STATE_FOCUSED|LV_STATE_EDITED.
		lv_obj_set_style_outline_opa(ui->volume_page_gain[i], LV_OPA_COVER, LV_STATE_FOCUSED|LV_STATE_EDITED);
		lv_obj_set_style_outline_color(ui->volume_page_gain[i], lv_palette_lighten(LV_PALETTE_DEEP_ORANGE, 1), LV_STATE_FOCUSED|LV_STATE_EDITED);
		lv_obj_set_style_outline_pad(ui->volume_page_gain[i], 2, LV_STATE_FOCUSED|LV_STATE_EDITED);
		lv_obj_set_style_outline_width(ui->volume_page_gain[i], 2, LV_STATE_FOCUSED|LV_STATE_EDITED);

		//Write codes volume_page_gain_label
		ui->volume_page_gain_label[i] = lv_label_create(ui->volume_page_list_page);
		lv_label_set_long_mode(ui->volume_page_gain_label[i], LV_LABEL_LONG_WRAP);
		lv_obj_align_to(ui->volume_page_gain_label[i], ui->volume_page_gain[i], LV_ALIGN_OUT_RIGHT_MID, 9, -8);
		lv_obj_set_size(ui->volume_page_gain_label[i], VOL_CHN_GAIN_LBL_WIDTH, VOL_CHN_HEIGHT);
		lv_label_set_text(ui->volume_page_gain_label[i], "-44.4");
		
		//Write style for volume_page_gain_label, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
		lv_obj_set_style_bg_opa(ui->volume_page_gain_label[i], 0, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_border_width(ui->volume_page_gain_label[i], 2, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_border_color(ui->volume_page_gain_label[i], lv_color_white(), LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_text_color(ui->volume_page_gain_label[i], MAIN_FONT_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_text_font(ui->volume_page_gain_label[i], &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_radius(ui->volume_page_gain_label[i], 2, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_text_align(ui->volume_page_gain_label[i], LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_pad_top(ui->volume_page_gain_label[i], 4, LV_PART_MAIN|LV_STATE_DEFAULT);

		//Add to group
		lv_group_add_obj(ui->volume_page_group, ui->volume_page_mute_btn[i]);
		lv_group_add_obj(ui->volume_page_group, ui->volume_page_gain[i]);
	}

	lv_indev_set_group(indev_keypad, ui->volume_page_group);
    lv_indev_set_group(indev_encoder, ui->volume_page_group);
	lv_group_focus_obj(ui->volume_page_mute_btn[0]);
	events_init_volume_page(ui);

	//Update current screen layout.
	lv_obj_update_layout(ui->volume_page);

}
