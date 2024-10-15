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

#define PRESET_PAGE_TITLE				"PRESET"

#define PRESET_PAGE_HEIGHT				190
#define PRESET_ITEM_X					5
#define PRESET_ITEM_Y					3
#define PRESET_ITEM_Y_SPAN				38
#define PRESET_ITEM_WIDTH				300
#define PRESET_ITEM_HEIGHT				32

uint8_t *preset_name[10] = {"1. PresetName", "2. kingrayTest1", "3. kingrayTest2", "4. kingrayTest3", "5. kingrayTest4", "6. kingrayTest5", "7. kingrayTest6", "8. kingrayTest7", "9. kingrayTest8", "10. kingrayTest9"};
//uint8_t *preset_name[5] = {"1. PresetName", "2. kingrayTest1", "3. kingrayTest2", "4. kingrayTest3", "5. kingrayTest4", "6. kingrayTest5", "7. kingrayTest6", "8. kingrayTest7", "9. kingrayTest8", "10. kingrayTest9"};
uint8_t item_number = 10;

void setup_scr_preset_page(lv_ui *ui)
{
	//Write codes preset_page
	ui->preset_page = lv_obj_create(NULL);
	lv_obj_set_size(ui->preset_page, LV_HOR_RES_MAX, LV_VER_RES_MAX);
	lv_obj_set_scrollbar_mode(ui->preset_page, LV_SCROLLBAR_MODE_OFF);

	//Write style for preset_page, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->preset_page, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->preset_page, BACKGROUND_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->preset_page, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes preset_page_title
	ui->preset_page_title = lv_label_create(ui->preset_page);
	lv_label_set_long_mode(ui->preset_page_title, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->preset_page_title, 0, 0);
	lv_obj_set_size(ui->preset_page_title, LV_HOR_RES_MAX, TITLE_HEIGHT);

	//Write style for preset_page_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->preset_page_title, MAIN_FONT_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->preset_page_title, &lv_font_montserratMedium_24, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->preset_page_title, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->preset_page_title, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->preset_page_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->preset_page_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->preset_page_title, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->preset_page_title, DESIGNATED_COLOR_BLUE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->preset_page_title, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_label_set_text(ui->preset_page_title, PRESET_PAGE_TITLE);

    //Write codes preset_page_list_page
    ui->preset_page_list_page = lv_obj_create(ui->preset_page);
    lv_obj_set_size(ui->preset_page_list_page, LV_HOR_RES_MAX, PRESET_PAGE_HEIGHT);
    lv_obj_set_pos(ui->preset_page_list_page, 0, TITLE_HEIGHT + 4);
    lv_obj_set_scrollbar_mode(ui->preset_page_list_page, LV_SCROLLBAR_MODE_AUTO);
	lv_obj_set_style_pad_all(ui->preset_page_list_page, 0, 0);

	//Write style for preset_page_list_page, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->preset_page_list_page, LV_OPA_TRANSP, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->preset_page_list_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->preset_page_list_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes preset_page_group
	ui->preset_page_group = lv_group_create();

	ui->preset_page_preset = (lv_obj_t **)malloc(item_number * sizeof(lv_obj_t *));
	for (int i = 0; i < item_number; i++)
	{
		ui->preset_page_preset[i] = lv_label_create(ui->preset_page_list_page);
		lv_label_set_long_mode(ui->preset_page_preset[i], LV_LABEL_LONG_SCROLL);
		lv_label_set_recolor(ui->preset_page_preset[i], true);
		lv_obj_set_pos(ui->preset_page_preset[i], PRESET_ITEM_X, PRESET_ITEM_Y + PRESET_ITEM_Y_SPAN * i);
		lv_obj_set_size(ui->preset_page_preset[i], PRESET_ITEM_WIDTH, PRESET_ITEM_HEIGHT);
		lv_label_set_text(ui->preset_page_preset[i], preset_name[i]);

		//Write style for preset_page_preset[i], Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
		lv_obj_set_style_text_align(ui->preset_page_preset[i], LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_text_font(ui->preset_page_preset[i], &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_text_color(ui->preset_page_preset[i], MAIN_FONT_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_radius(ui->preset_page_preset[i], 2, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_border_width(ui->preset_page_preset[i], 1, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_border_color(ui->preset_page_preset[i], lv_color_white(), LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_border_opa(ui->preset_page_preset[i], LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);

		lv_obj_set_style_pad_top(ui->preset_page_preset[i], 4, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_pad_left(ui->preset_page_preset[i], 20, LV_PART_MAIN|LV_STATE_DEFAULT);

		//Write style for preset_page_preset[i], Part: LV_PART_MAIN, State: LV_STATE_FOCUSED.
		lv_obj_set_style_border_width(ui->preset_page_preset[i], 3, LV_PART_MAIN|LV_STATE_FOCUSED);
		lv_obj_set_style_border_color(ui->preset_page_preset[i], lv_palette_lighten(LV_PALETTE_ORANGE, 1), LV_PART_MAIN|LV_STATE_FOCUSED);
		lv_obj_set_style_border_opa(ui->preset_page_preset[i], LV_OPA_COVER, LV_PART_MAIN|LV_STATE_FOCUSED);
		lv_obj_set_style_bg_color(ui->preset_page_preset[i], MAIN_FONT_COLOR, LV_PART_MAIN|LV_STATE_FOCUSED);
		lv_obj_set_style_text_color(ui->preset_page_preset[i], lv_palette_main(LV_PALETTE_GREEN), LV_PART_MAIN|LV_STATE_FOCUSED);

		lv_group_add_obj(ui->preset_page_group, ui->preset_page_preset[i]);
	}

	lv_group_focus_obj(ui->preset_page_preset[0]);

	//Update current screen layout.
	lv_obj_update_layout(ui->preset_page);

}
