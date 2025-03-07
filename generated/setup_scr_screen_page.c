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

#define SCREEN_PAGE_TITLE					"SCREEN"

#define SCREEN_TOPIC_X						8
#define SCREEN_TOPIC_Y						90
#define SCREEN_TOPIC_SPAN					36

#define SCREEN_RLR_TIME_WIDTH				25
#define SCREEN_RLR_TIME_HEIGHT				30

#define SCREEN_SWITCH_WIDTH					46
#define SCREEN_SWITCH_HEIGHT				22

const char backlight_option[] = 
{
  "1\n" "2\n" "3\n" "4\n" "5\n" "6\n" "7\n" "8\n" "9\n" "10\n" "11\n" "12\n" "13\n" "14\n" "15\n" "16\n" "17\n" "18\n" "19\n" "20\n" "21\n" "22\n" "23\n" "24\n" "25\n" "26\n" "27\n" "28\n" "29\n" "30\n" 
  
  "31\n" "32\n" "33\n" "34\n" "35\n" "36\n" "37\n" "38\n" "39\n" "40\n" "41\n" "42\n" "43\n" "44\n" "45\n" "46\n" "47\n" "48\n" "49\n" "50\n" "51\n" "52\n" "53\n" "54\n" "55\n" "56\n" "57\n" "58\n" "59\n" "60" 
};

void setup_scr_screen_page(lv_ui *ui)
{
	//Write codes screen_page
	ui->screen_page = lv_obj_create(NULL);
	lv_obj_set_size(ui->screen_page, LV_HOR_RES_MAX, LV_VER_RES_MAX);
	lv_obj_set_scrollbar_mode(ui->screen_page, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_page, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_page, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_page, BACKGROUND_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_page, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_page_title
	ui->screen_page_title = lv_label_create(ui->screen_page);
	lv_label_set_long_mode(ui->screen_page_title, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_page_title, 0, 0);
	lv_obj_set_size(ui->screen_page_title, LV_HOR_RES_MAX, TITLE_HEIGHT);

	//Write style for screen_page_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_page_title, MAIN_FONT_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_page_title, &lv_font_montserratMedium_24, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_page_title, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_page_title, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_page_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_page_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_page_title, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_page_title, DESIGNATED_COLOR_BLUE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_page_title, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_label_set_text(ui->screen_page_title, SCREEN_PAGE_TITLE);

	//Write codes screen screen_page_backlight
	ui->screen_page_backlight = lv_label_create(ui->screen_page);
	lv_label_set_long_mode(ui->screen_page_backlight, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_page_backlight, SCREEN_TOPIC_X, SCREEN_TOPIC_Y);

	//Write style for screen_page_backlight, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_font(ui->screen_page_backlight, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_page_backlight, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_page_backlight, MAIN_FONT_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_label_set_text(ui->screen_page_backlight, "Backlight Auto Close:");

	//Write codes screen_page_backlight_switch
	ui->screen_page_backlight_switch = lv_switch_create(ui->screen_page);
	lv_obj_align_to(ui->screen_page_backlight_switch, ui->screen_page_backlight, LV_ALIGN_OUT_RIGHT_TOP, 20, 0);
	lv_obj_set_size(ui->screen_page_backlight_switch, SCREEN_SWITCH_WIDTH, SCREEN_SWITCH_HEIGHT);

	//Write style for screen_page_backlight_switch, Part: LV_PART_MAIN | LV_PART_INDICATOR, State: LV_STATE_FOCUSED
	lv_obj_set_style_border_width(ui->screen_page_backlight_switch, 2, LV_PART_MAIN|LV_PART_INDICATOR|LV_STATE_FOCUSED);
	lv_obj_set_style_outline_opa(ui->screen_page_backlight_switch, LV_OPA_COVER, LV_PART_MAIN|LV_PART_INDICATOR|LV_STATE_FOCUSED);
	lv_obj_set_style_outline_color(ui->screen_page_backlight_switch, lv_palette_lighten(LV_PALETTE_ORANGE, 1), LV_PART_MAIN|LV_PART_INDICATOR|LV_STATE_FOCUSED);
	lv_obj_set_style_outline_pad(ui->screen_page_backlight_switch, 2, LV_PART_MAIN|LV_PART_INDICATOR|LV_STATE_FOCUSED);
	lv_obj_set_style_outline_width(ui->screen_page_backlight_switch, 3, LV_PART_MAIN|LV_PART_INDICATOR|LV_STATE_FOCUSED);


	//Write codes screen_page_backlight_time_topic
	ui->screen_page_backlight_time_topic = lv_label_create(ui->screen_page);
	lv_label_set_long_mode(ui->screen_page_backlight_time_topic, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_page_backlight_time_topic, SCREEN_TOPIC_X, SCREEN_TOPIC_Y + SCREEN_TOPIC_SPAN);

	//Write style for screen_page_backlight_time_topic, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_font(ui->screen_page_backlight_time_topic, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->screen_page_backlight_time_topic, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_page_backlight_time_topic, MAIN_FONT_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_label_set_text(ui->screen_page_backlight_time_topic, "Backlight time:");

	//Write codes screen_page_backlight_time
	ui->screen_page_backlight_time = lv_roller_create(ui->screen_page);
	lv_obj_align_to(ui->screen_page_backlight_time, ui->screen_page_backlight_time_topic, LV_ALIGN_OUT_RIGHT_TOP, 10, 0);
	lv_roller_set_visible_row_count(ui->screen_page_backlight_time, 1);
	lv_roller_set_options(ui->screen_page_backlight_time, backlight_option, LV_ROLLER_MODE_NORMAL);
	lv_obj_set_size(ui->screen_page_backlight_time, SCREEN_RLR_TIME_WIDTH, SCREEN_RLR_TIME_HEIGHT);
    lv_obj_set_style_radius(ui->screen_page_backlight_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_page_backlight_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_page_backlight_time, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_page_backlight_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_page_backlight_time, BACKGROUND_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_all(ui->screen_page_backlight_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_page_backlight_time, Part: LV_PART_MAIN State: LV_STATE_FOCUSED.
	lv_obj_set_style_text_color(ui->screen_page_backlight_time, lv_color_black(), LV_PART_SELECTED|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_color(ui->screen_page_backlight_time, lv_color_white(), LV_PART_SELECTED|LV_STATE_FOCUSED);
	lv_obj_set_style_outline_opa(ui->screen_page_backlight_time, LV_OPA_COVER, LV_STATE_FOCUSED);
	lv_obj_set_style_outline_color(ui->screen_page_backlight_time, lv_palette_lighten(LV_PALETTE_ORANGE, 1), LV_STATE_FOCUSED);
	lv_obj_set_style_outline_pad(ui->screen_page_backlight_time, 2, LV_STATE_FOCUSED);
	lv_obj_set_style_outline_width(ui->screen_page_backlight_time, 3, LV_STATE_FOCUSED);

	//Write style for screen_page_backlight_time, Part: LV_PART_SELECTED, State: LV_STATE_FOCUSED | LV_STATE_EDITED.
	lv_obj_set_style_text_color(ui->screen_page_backlight_time, lv_color_black(), LV_PART_SELECTED|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_color(ui->screen_page_backlight_time, lv_palette_main(LV_PALETTE_GREEN), LV_PART_SELECTED|LV_STATE_FOCUSED|LV_STATE_EDITED);
	lv_obj_set_style_outline_opa(ui->screen_page_backlight_time, LV_OPA_COVER, LV_STATE_FOCUSED|LV_STATE_EDITED);
	lv_obj_set_style_outline_color(ui->screen_page_backlight_time, lv_palette_lighten(LV_PALETTE_ORANGE, 1), LV_STATE_FOCUSED|LV_STATE_EDITED);
	lv_obj_set_style_outline_pad(ui->screen_page_backlight_time, 2, LV_STATE_FOCUSED|LV_STATE_EDITED);
	lv_obj_set_style_outline_width(ui->screen_page_backlight_time, 3, LV_STATE_FOCUSED|LV_STATE_EDITED);

	//Write codes screen_page_backlight_time_unit
	ui->screen_page_backlight_time_unit = lv_label_create(ui->screen_page);
	lv_label_set_long_mode(ui->screen_page_backlight_time_unit, LV_LABEL_LONG_WRAP);
	lv_obj_align_to(ui->screen_page_backlight_time_unit, ui->screen_page_backlight_time, LV_ALIGN_OUT_RIGHT_TOP, 10, 0);

	//Write style for screen_page_backlight_time_unit, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_font(ui->screen_page_backlight_time_unit, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_page_backlight_time_unit, MAIN_FONT_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_label_set_text(ui->screen_page_backlight_time_unit, "min");


	//Group
	ui->screen_page_group = lv_group_create();
	lv_indev_set_group(indev_keypad, ui->screen_page_group);
    lv_indev_set_group(indev_encoder, ui->screen_page_group);
	lv_group_add_obj(ui->screen_page_group, ui->screen_page_backlight_switch);
	lv_group_add_obj(ui->screen_page_group, ui->screen_page_backlight_time);
	lv_group_focus_obj(ui->screen_page_backlight_switch);

	events_init_screen_page(ui);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_page);
}
