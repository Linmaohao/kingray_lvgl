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

#define BAR_ANIM_TIME		2000

void setup_scr_load_page(lv_ui *ui)
{
	//Write codes load_page
	ui->load_page = lv_obj_create(NULL);
	lv_obj_set_size(ui->load_page, LV_HOR_RES_MAX, LV_VER_RES_MAX);
	lv_obj_set_scrollbar_mode(ui->load_page, LV_SCROLLBAR_MODE_OFF);

	//Write style for load_page, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->load_page, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->load_page, BACKGROUND_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->load_page, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes load_page_bar_load, set to 10s
	ui->load_page_bar_load = lv_bar_create(ui->load_page);
	lv_obj_set_style_anim_time(ui->load_page_bar_load, BAR_ANIM_TIME, 0);
	lv_bar_set_mode(ui->load_page_bar_load, LV_BAR_MODE_RANGE);
	lv_bar_set_range(ui->load_page_bar_load, 0, 100);
	lv_bar_set_value(ui->load_page_bar_load, 100, LV_ANIM_ON);
	lv_bar_set_start_value(ui->load_page_bar_load, 0, LV_ANIM_ON);
	lv_obj_set_pos(ui->load_page_bar_load, 35, 167);
	lv_obj_set_size(ui->load_page_bar_load, 250, 22);

	//Write style for load_page_bar_load, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->load_page_bar_load, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->load_page_bar_load, lv_color_hex(0x009ea9), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->load_page_bar_load, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->load_page_bar_load, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->load_page_bar_load, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for load_page_bar_load, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->load_page_bar_load, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->load_page_bar_load, lv_color_hex(0x00ff6a), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->load_page_bar_load, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->load_page_bar_load, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write codes load_page_label_load
	ui->load_page_label_load = lv_label_create(ui->load_page);
	lv_label_set_text(ui->load_page_label_load, "Loading");
	lv_label_set_long_mode(ui->load_page_label_load, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->load_page_label_load, 110, 134);
	lv_obj_set_size(ui->load_page_label_load, 100, 21);

	//Write style for load_page_label_load, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->load_page_label_load, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->load_page_label_load, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->load_page_label_load, MAIN_FONT_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->load_page_label_load, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->load_page_label_load, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->load_page_label_load, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->load_page_label_load, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->load_page_label_load, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->load_page_label_load, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->load_page_label_load, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->load_page_label_load, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->load_page_label_load, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->load_page_label_load, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->load_page_label_load, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//The custom code of load_page.
	

	//Update current screen layout.
	lv_obj_update_layout(ui->load_page);

}
