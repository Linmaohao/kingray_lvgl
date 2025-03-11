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

#define SOURCE_PAGE_TITLE			"SOURCE"

#define SOURCE_CHN_X				2
#define SOURCE_CHN_Y				46

#define SOURCE_CHN_WIDTH			56
#define SOURCE_CHN_HEIGHT			32
#define SOURCE_CHN_Y_SPAN			46

#define SOURCE_SRC_WIDTH			120

#define SOURCE_SENS_WIDTH			86


const char* source_opt =
{
  "Analog\n"
  "Dante\n"
  "Mix\n"
  "Analog+\n"
  "Dante+"
};

void setup_scr_source_page(lv_ui *ui)
{
	//Write codes source_page
	ui->source_page = lv_obj_create(NULL);
	lv_obj_set_size(ui->source_page, LV_HOR_RES_MAX, LV_VER_RES_MAX);
	lv_obj_set_scrollbar_mode(ui->source_page, LV_SCROLLBAR_MODE_OFF);

	//Write style for source_page, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->source_page, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->source_page, BACKGROUND_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->source_page, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes source_page_title
	ui->source_page_title = lv_label_create(ui->source_page);
	lv_label_set_long_mode(ui->source_page_title, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->source_page_title, 0, 0);
	lv_obj_set_size(ui->source_page_title, LV_HOR_RES_MAX, TITLE_HEIGHT);

	//Write style for source_page_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->source_page_title, MAIN_FONT_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->source_page_title, &lv_font_montserratMedium_24, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->source_page_title, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->source_page_title, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->source_page_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->source_page_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->source_page_title, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->source_page_title, DESIGNATED_COLOR_BLUE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->source_page_title, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_label_set_text(ui->source_page_title, SOURCE_PAGE_TITLE);

	//Init a new style for default status
	static lv_style_t dropdown_default_style;
	ui_init_style(&dropdown_default_style);
	lv_style_set_text_color(&dropdown_default_style, MAIN_FONT_COLOR);
	lv_style_set_text_font(&dropdown_default_style, &lv_font_montserratMedium_18);
	lv_style_set_border_width(&dropdown_default_style, 2);
	lv_style_set_border_opa(&dropdown_default_style, LV_OPA_COVER);
	lv_style_set_border_color(&dropdown_default_style, lv_color_white());
	lv_style_set_pad_top(&dropdown_default_style, 6);
	lv_style_set_radius(&dropdown_default_style, 4);
	lv_style_set_bg_opa(&dropdown_default_style, LV_OPA_COVER);
	lv_style_set_bg_color(&dropdown_default_style, BACKGROUND_COLOR);

	//Init a new style for focus status
	static lv_style_t dropdown_focus_style;
	ui_init_style(&dropdown_focus_style);
	lv_style_set_outline_width(&dropdown_focus_style, 2);
	lv_style_set_outline_opa(&dropdown_focus_style, LV_OPA_COVER);
	lv_style_set_outline_color(&dropdown_focus_style, lv_palette_lighten(LV_PALETTE_ORANGE, 1));
	lv_style_set_outline_pad(&dropdown_focus_style, 2);
	lv_style_set_bg_opa(&dropdown_focus_style, LV_OPA_COVER);
	lv_style_set_bg_color(&dropdown_focus_style, lv_color_white());
	lv_style_set_text_color(&dropdown_focus_style, lv_palette_main(LV_PALETTE_GREEN));

	//Init a new style for selected part and checked status
	static lv_style_t dropdown_style_selected_checked;
	ui_init_style(&dropdown_style_selected_checked);
	lv_style_set_border_width(&dropdown_style_selected_checked, 0);
	lv_style_set_bg_opa(&dropdown_style_selected_checked, LV_OPA_COVER);
	lv_style_set_bg_color(&dropdown_style_selected_checked, lv_palette_main(LV_PALETTE_GREEN));

	//Create a group
	ui->source_page_group = lv_group_create();
	
	for(int i = 0; i < LAYOUT_INPUT_SIZE; i++){
		//Write codes source_page_in_channel[i]
		ui->source_page_in_channel[i] = lv_label_create(ui->source_page);
		lv_label_set_long_mode(ui->source_page_in_channel[i], LV_LABEL_LONG_WRAP);
		lv_obj_set_pos(ui->source_page_in_channel[i], SOURCE_CHN_X, SOURCE_CHN_Y + SOURCE_CHN_Y_SPAN * i);
		lv_obj_set_size(ui->source_page_in_channel[i], SOURCE_CHN_WIDTH, SOURCE_CHN_HEIGHT);

		//Write style for source_page_in_channel, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
		set_channel_name_style(ui->source_page_in_channel[i]);
		lv_label_set_text(ui->source_page_in_channel[i], in_channel_label[i]);

		//Write codes source_page_source[i]
		ui->source_page_source[i] = lv_dropdown_create(ui->source_page);
		lv_dropdown_set_options(ui->source_page_source[i], source_opt);
		lv_dropdown_set_symbol(ui->source_page_source[i], NULL);
		lv_obj_align_to(ui->source_page_source[i], ui->source_page_in_channel[i], LV_ALIGN_OUT_RIGHT_TOP, 8, 0);
		lv_obj_set_size(ui->source_page_source[i], SOURCE_SRC_WIDTH, SOURCE_CHN_HEIGHT);

		//Write style state: LV_STATE_FOCUSED for &dropdown_default_style
		lv_obj_add_style(ui->source_page_source[i], &dropdown_default_style, LV_PART_MAIN|LV_STATE_DEFAULT);

		//Write style state: LV_STATE_FOCUSED for &focus_style
		lv_obj_add_style(ui->source_page_source[i], &dropdown_focus_style, LV_PART_MAIN|LV_STATE_FOCUSED);

		//Write style state: LV_STATE_CHECKED for &style_selected_checked
		lv_obj_add_style(lv_dropdown_get_list(ui->source_page_source[i]), &dropdown_style_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);


		//Write codes source_page_sens[i]
		ui->source_page_sens[i] = lv_dropdown_create(ui->source_page);
		lv_dropdown_set_options(ui->source_page_sens[i], "0dBu\n6dBu");
		lv_dropdown_set_symbol(ui->source_page_sens[i], NULL);
		lv_obj_align_to(ui->source_page_sens[i], ui->source_page_source[i], LV_ALIGN_OUT_RIGHT_TOP, 8, 0);
		lv_obj_set_size(ui->source_page_sens[i], SOURCE_SENS_WIDTH, SOURCE_CHN_HEIGHT);

		//Write style state: LV_STATE_FOCUSED for &dropdown_default_style
		lv_obj_add_style(ui->source_page_sens[i], &dropdown_default_style, LV_PART_MAIN|LV_STATE_DEFAULT);

		//Write style state: LV_STATE_FOCUSED for &focus_style
		lv_obj_add_style(ui->source_page_sens[i], &dropdown_focus_style, LV_PART_MAIN|LV_STATE_FOCUSED);

		//Write style state: LV_STATE_CHECKED for &style_selected_checked
		lv_obj_add_style(lv_dropdown_get_list(ui->source_page_sens[i]), &dropdown_style_selected_checked, LV_PART_SELECTED|LV_STATE_CHECKED);

		//Add to group
		lv_group_add_obj(ui->source_page_group, ui->source_page_source[i]);
		lv_group_add_obj(ui->source_page_group, ui->source_page_sens[i]);

	}

	lv_indev_set_group(indev_keypad, ui->source_page_group);
    lv_indev_set_group(indev_encoder, ui->source_page_group);

	lv_group_focus_obj(ui->source_page_source[0]);
	events_init_source_page(ui);

	//Update current screen layout.
	lv_obj_update_layout(ui->source_page);

}
