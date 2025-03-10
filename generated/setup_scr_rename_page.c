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

#define RENAME_PAGE_TITLE				"RENAME"

#define RENAME_ITEM_X					6
#define RENAME_ITEM_X_SPAN				38
#define RENAME_ITEM_Y					100
#define RENAME_ITEM_WIDTH				30
#define RENAME_ITEM_HEIGHT				43

const char *char_select = 
{
  " \n" 

  "-\n" 

  "0\n" "1\n" "2\n" "3\n" "4\n" "5\n" "6\n" "7\n" "8\n" "9\n" 

  "A\n" "B\n" "C\n" "D\n" "E\n" "F\n" "G\n" "H\n" "I\n" "J\n" "K\n" "L\n" "M\n" "N\n" "O\n" "P\n" "Q\n" "R\n" "S\n" "T\n" "U\n" "V\n" "W\n" "X\n" "Y\n" "Z\n" 

  "_\n" 

  "a\n" "b\n" "c\n" "d\n" "e\n" "f\n" "g\n" "h\n" "i\n" "j\n" "k\n" "l\n" "m\n" "n\n" "o\n" "p\n" "q\n" "r\n" "s\n" "t\n" "u\n" "v\n" "w\n" "x\n" "y\n" "z" 
};

uint8_t name_record[8] = {'4', '3', 'H', 'H', ' ', ' ', ' ', ' '};

void setup_scr_rename_page(lv_ui *ui)
{
	printf("============ \n");
	//Write codes rename_page
	ui->rename_page = lv_obj_create(NULL);
	lv_obj_set_size(ui->rename_page, LV_HOR_RES_MAX, LV_VER_RES_MAX);
	lv_obj_set_scrollbar_mode(ui->rename_page, LV_SCROLLBAR_MODE_OFF);

	//Write style for rename_page, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->rename_page, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->rename_page, BACKGROUND_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->rename_page, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes rename_page_title
	ui->rename_page_title = lv_label_create(ui->rename_page);
	lv_label_set_text(ui->rename_page_title, RENAME_PAGE_TITLE);
	lv_label_set_long_mode(ui->rename_page_title, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->rename_page_title, 0, 0);
	lv_obj_set_size(ui->rename_page_title, LV_HOR_RES_MAX, TITLE_HEIGHT);

	//Write style for rename_page_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->rename_page_title, MAIN_FONT_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->rename_page_title, &lv_font_montserratMedium_24, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->rename_page_title, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->rename_page_title, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->rename_page_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->rename_page_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->rename_page_title, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->rename_page_title, DESIGNATED_COLOR_BLUE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->rename_page_title, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_label_set_text(ui->rename_page_title, RENAME_PAGE_TITLE);

	//Write codes rename_page_group
	ui->rename_page_group = lv_group_create();

	for(int i = 0; i < RENAME_DISPLAY_NAME_LEN; i++){
		ui->rename_page_name[i] = lv_roller_create(ui->rename_page);
		lv_roller_set_options(ui->rename_page_name[i], char_select, LV_ROLLER_MODE_NORMAL);
		lv_roller_set_visible_row_count(ui->rename_page_name[i], 1);
		lv_obj_set_pos(ui->rename_page_name[i], RENAME_ITEM_X + RENAME_ITEM_X_SPAN * i, RENAME_ITEM_Y);
		lv_obj_set_size(ui->rename_page_name[i], RENAME_ITEM_WIDTH, RENAME_ITEM_HEIGHT);

		//Write style for rename_page_name, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
		lv_obj_set_style_bg_opa(ui->rename_page_name[i], LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_bg_color(ui->rename_page_name[i], BACKGROUND_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
    	lv_obj_set_style_radius(ui->rename_page_name[i], 0, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_border_width(ui->rename_page_name[i], 0, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_pad_all(ui->rename_page_name[i], 0, LV_PART_MAIN|LV_STATE_DEFAULT);

		//Write style for rename_page_name, Part: LV_PART_SELECTED, State: LV_STATE_FOCUSED.
		lv_obj_set_style_text_color(ui->rename_page_name[i], lv_color_black(), LV_PART_SELECTED|LV_STATE_FOCUSED);
		lv_obj_set_style_bg_color(ui->rename_page_name[i], lv_color_white(), LV_PART_SELECTED|LV_STATE_FOCUSED);
		lv_obj_set_style_outline_opa(ui->rename_page_name[i], LV_OPA_COVER, LV_STATE_FOCUSED);
		lv_obj_set_style_outline_color(ui->rename_page_name[i], lv_palette_lighten(LV_PALETTE_ORANGE, 1), LV_STATE_FOCUSED);
		lv_obj_set_style_outline_pad(ui->rename_page_name[i], 2, LV_STATE_FOCUSED);
		lv_obj_set_style_outline_width(ui->rename_page_name[i], 3, LV_STATE_FOCUSED);

		//Write style for rename_page_name, Part: LV_PART_SELECTED, State: LV_STATE_FOCUSED|LV_STATE_EDITED.
		lv_obj_set_style_bg_color(ui->rename_page_name[i], lv_palette_main(LV_PALETTE_GREEN), LV_PART_SELECTED|(LV_STATE_FOCUSED|LV_STATE_EDITED));
		lv_obj_set_style_outline_opa(ui->rename_page_name[i], LV_OPA_COVER, LV_STATE_FOCUSED|LV_STATE_EDITED);
		lv_obj_set_style_outline_color(ui->rename_page_name[i], lv_palette_lighten(LV_PALETTE_ORANGE, 1), LV_STATE_FOCUSED|LV_STATE_EDITED);
		lv_obj_set_style_outline_pad(ui->rename_page_name[i], 2, LV_STATE_FOCUSED|LV_STATE_EDITED);
		lv_obj_set_style_outline_width(ui->rename_page_name[i], 3, LV_STATE_FOCUSED|LV_STATE_EDITED);

		lv_roller_set_selected(ui->rename_page_name[i], name_record[i], LV_ANIM_OFF);

		lv_group_add_obj(ui->rename_page_group, ui->rename_page_name[i]);
	}

	lv_indev_set_group(indev_keypad, ui->rename_page_group);
    lv_indev_set_group(indev_encoder, ui->rename_page_group);
	lv_group_focus_obj(ui->rename_page_name[0]);

	events_init_rename_page(ui);

	//Update current screen layout.
	lv_obj_update_layout(ui->rename_page);
}