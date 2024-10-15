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

#define INFO_PAGE_TITLE					"INFO"

#define INFO_PAGE_HEIGHT                150
#define INFO_PAGE_Y                     50

#define INFO_FACTORY_TOPIC_WIDTH        200

#define INFO_TOPIC_X                    6
#define INFO_TOPIC_Y                    2
#define INFO_TOPIC_SPAN                 36

void setup_scr_info_page(lv_ui *ui)
{
	//Write codes info_page
	ui->info_page = lv_obj_create(NULL);
	lv_obj_set_size(ui->info_page, LV_HOR_RES_MAX, LV_VER_RES_MAX);
	lv_obj_set_scrollbar_mode(ui->info_page, LV_SCROLLBAR_MODE_OFF);

	//Write style for info_page, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->info_page, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->info_page, BACKGROUND_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->info_page, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes info_page_title
	ui->info_page_title = lv_label_create(ui->info_page);
	lv_label_set_long_mode(ui->info_page_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->info_page_title, 0, 0);
    lv_obj_set_size(ui->info_page_title, LV_HOR_RES_MAX, TITLE_HEIGHT);

	//Write style for ui->info_page_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->info_page_title, MAIN_FONT_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->info_page_title, &lv_font_montserratMedium_24, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->info_page_title, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->info_page_title, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->info_page_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->info_page_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->info_page_title, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->info_page_title, DESIGNATED_COLOR_BLUE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->info_page_title, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_label_set_text(ui->info_page_title, INFO_PAGE_TITLE);

    //Write codes info_page_message_page
    ui->info_page_message_page = lv_obj_create(ui->info_page);
    lv_obj_set_size(ui->info_page_message_page, LV_HOR_RES_MAX, INFO_PAGE_HEIGHT);
    lv_obj_set_pos(ui->info_page_message_page, 0, INFO_PAGE_Y);
    lv_obj_set_scrollbar_mode(ui->info_page_message_page, LV_SCROLLBAR_MODE_AUTO);
	lv_obj_set_style_pad_all(ui->info_page_message_page, 0, 0);

	//Write style for info_page_message_page, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->info_page_message_page, LV_OPA_TRANSP, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->info_page_message_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->info_page_message_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Init a new style for info
	lv_style_t *info_style = (lv_style_t *)malloc(sizeof(lv_style_t));
    lv_style_init(info_style);
	lv_style_set_bg_opa(info_style, LV_OPA_TRANSP);
	lv_style_set_text_font(info_style, &lv_font_montserratMedium_24);
	lv_style_set_border_width(info_style, 0);
	lv_style_set_text_align(info_style, LV_TEXT_ALIGN_LEFT);
	lv_style_set_text_color(info_style, MAIN_FONT_COLOR);

	//Write codes for info_page_factory_topic
	ui->info_page_factory_topic = lv_label_create(ui->info_page_message_page);
	lv_obj_set_pos(ui->info_page_factory_topic, INFO_TOPIC_X, INFO_TOPIC_Y);
	lv_obj_set_width(ui->info_page_factory_topic, INFO_FACTORY_TOPIC_WIDTH);
	lv_label_set_long_mode(ui->info_page_factory_topic, LV_LABEL_LONG_SCROLL);
	lv_obj_add_style(ui->info_page_factory_topic, info_style, LV_PART_MAIN);
	lv_label_set_text(ui->info_page_factory_topic, "MFRS:  43A");

	//Write codes for info_page_software_version
	ui->info_page_software_version = lv_label_create(ui->info_page_message_page);
	lv_obj_set_pos(ui->info_page_software_version, INFO_TOPIC_X, INFO_TOPIC_Y + INFO_TOPIC_SPAN);
	lv_obj_set_width(ui->info_page_software_version, INFO_FACTORY_TOPIC_WIDTH);
	lv_label_set_long_mode(ui->info_page_software_version, LV_LABEL_LONG_SCROLL);
	lv_obj_add_style(ui->info_page_software_version, info_style, LV_PART_MAIN);
	lv_label_set_text(ui->info_page_software_version, "SW V:  10.10.11");

	//Write codes for info_page_hardware_version
	ui->info_page_hardware_version = lv_label_create(ui->info_page_message_page);
	lv_obj_set_pos(ui->info_page_hardware_version, INFO_TOPIC_X, INFO_TOPIC_Y + INFO_TOPIC_SPAN*2);
	lv_obj_set_width(ui->info_page_hardware_version, INFO_FACTORY_TOPIC_WIDTH);
	lv_label_set_long_mode(ui->info_page_hardware_version, LV_LABEL_LONG_SCROLL);
	lv_obj_add_style(ui->info_page_hardware_version, info_style, LV_PART_MAIN);
	lv_label_set_text(ui->info_page_hardware_version, "HW V:  43.66.32");

	//Update current screen layout.
	lv_obj_update_layout(ui->info_page);

}
