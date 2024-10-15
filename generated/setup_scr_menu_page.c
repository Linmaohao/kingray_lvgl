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

#define MENU_PAGE_TITLE						"MENU"

#define DESIGNATED_LIGHT_BLUE				lv_color_hex(0x172C3D)
#define LOCK_DEFAULT_COLOR					lv_color_hex(0xe6e2e6)
#define LOCK_CHECKED_COLOR					lv_color_hex(0x2195f6)

#define MENU_PAGE_LIST_PAGE_HEIGHT			194

#define MENU_PAGE_ITEM_WIDTH				280
#define MENU_PAGE_ITEM_HEIGHT				30
#define MENU_PAGE_ITEM_X					4
#define MENU_PAGE_ITEM_Y					2
#define MENU_PAGE_ITEM_Y_SPAN				32

#define MENU_PAGE_ITEM_NO_X					30
#define MENU_PAGE_ITEM_NO_Y					3
#define MENU_PAGE_ITEM_NO_WIDTH				22

#define MENU_PAGE_ITEM_HEAD_X				60
#define MENU_PAGE_ITEM_HEAD_Y				3
#define MENU_PAGE_ITEM_HEAD_WIDTH			180

#define MENU_PAGE_ITEM_LOCK_X				180
#define MENU_PAGE_ITEM_LOCK_Y				3
#define MENU_PAGE_ITEM_LOCK_WIDTH			50
#define MENU_PAGE_ITEM_LOCK_HEIGHT			24

typedef struct 
{
  uint8_t idx;
  char title[12];
}menu_info_t;

const menu_info_t menu_info[] =
{
  {MENU_E_VOLUME, "VOLUME     "},
  {MENU_E_PRESET, "PRESET     "},
  {MENU_E_SOURCE, "SOURCE     "},
  {MENU_E_STATUS, "STATUS     "},
  {MENU_E_RENAME, "RENAME     "},
  {MENU_E_IPSET,  "IP SETTING "},
  {MENU_E_LOCK,   "LOCK:      "},
  {MENU_E_INFO,   "INFO       "},
  {MENU_E_SCREEN, "SCREEN     "},
};


void setup_scr_menu_page(lv_ui *ui)
{
	
	//Write codes menu_page
	ui->menu_page = lv_obj_create(NULL);
	lv_obj_set_size(ui->menu_page, LV_HOR_RES_MAX, LV_VER_RES_MAX);
	lv_obj_set_scrollbar_mode(ui->menu_page, LV_SCROLLBAR_MODE_OFF);

	//Write style for menu_page, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->menu_page, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->menu_page, BACKGROUND_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->menu_page, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes menu_page_title
	ui->menu_page_title = lv_label_create(ui->menu_page);
	lv_label_set_long_mode(ui->menu_page_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->menu_page_title, 0, 0);
    lv_obj_set_size(ui->menu_page_title, LV_HOR_RES_MAX, TITLE_HEIGHT);

	//Write style for ui->menu_page_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->menu_page_title, MAIN_FONT_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->menu_page_title, &lv_font_montserratMedium_24, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->menu_page_title, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->menu_page_title, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->menu_page_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->menu_page_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->menu_page_title, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->menu_page_title, DESIGNATED_COLOR_BLUE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->menu_page_title, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_label_set_text(ui->menu_page_title, MENU_PAGE_TITLE);

	
    //Write codes menu_page_list_page
    ui->menu_page_list_page = lv_obj_create(ui->menu_page);
    lv_obj_set_size(ui->menu_page_list_page, LV_HOR_RES_MAX, MENU_PAGE_LIST_PAGE_HEIGHT);
    lv_obj_set_pos(ui->menu_page_list_page, 0, TITLE_HEIGHT + 4);
    lv_obj_set_scrollbar_mode(ui->menu_page_list_page, LV_SCROLLBAR_MODE_AUTO);
	lv_obj_set_style_pad_all(ui->menu_page_list_page, 0, 0);
	//lv_obj_set_layout(ui->menu_page_list_page, LV_OBJ_FLAG_SCROLL_ON_FOCUS);

	//Write style for menu_page_list_page, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->menu_page_list_page, LV_OPA_TRANSP, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->menu_page_list_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->menu_page_list_page, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Init a new style for scroll bar.
	lv_style_t *scroll_bar_style = (lv_style_t *)malloc(sizeof(lv_style_t));
    lv_style_init(scroll_bar_style);
	lv_style_set_radius(scroll_bar_style, 0);
	lv_style_set_bg_opa(scroll_bar_style, LV_OPA_COVER);
	lv_style_set_bg_color(scroll_bar_style, MAIN_FONT_COLOR);
	lv_style_set_pad_top(scroll_bar_style, 50);
	lv_style_set_pad_bottom(scroll_bar_style, 50);
	lv_style_set_size(scroll_bar_style, 10);

	//Add to scroll bar.
	//lv_obj_add_style(ui->menu_page_list_page, scroll_bar_style, LV_PART_SCROLLBAR);


	//Init a new style for item container.
	lv_style_t *item_container_style = (lv_style_t *)malloc(sizeof(lv_style_t));
    lv_style_init(item_container_style);
	lv_style_set_border_width(item_container_style, 1);
	lv_style_set_border_color(item_container_style, lv_color_white());
	lv_style_set_radius(item_container_style, 2);
	lv_style_set_bg_opa(item_container_style, LV_OPA_TRANSP);
	lv_style_set_pad_top(item_container_style, 2);

	lv_style_t *item_container_focused_style = (lv_style_t *)malloc(sizeof(lv_style_t));
	lv_style_init(item_container_focused_style);
	lv_style_set_border_width(item_container_focused_style, 2);
	lv_style_set_bg_color(item_container_focused_style, DESIGNATED_LIGHT_BLUE);
	lv_style_set_border_color(item_container_focused_style, DESIGNATED_COLOR_BLUE);
	lv_style_set_bg_opa(item_container_focused_style, LV_OPA_COVER);

	//Init a new style for number.
	lv_style_t *number_style = (lv_style_t *)malloc(sizeof(lv_style_t));
	lv_style_init(number_style);
	lv_style_set_text_font(number_style, &lv_font_montserratMedium_16);
	lv_style_set_border_width(number_style, 0);
	lv_style_set_radius(number_style, 1);
	lv_style_set_text_align(number_style, LV_TEXT_ALIGN_CENTER);
	lv_style_set_bg_color(number_style, DESIGNATED_COLOR_BLUE);
	lv_style_set_bg_opa(number_style, LV_OPA_COVER);
	lv_style_set_text_color(number_style, MAIN_FONT_COLOR);
	lv_style_set_pad_top(number_style, 2);
	/*
	lv_style_t *number_focused_style = (lv_style_t *)malloc(sizeof(lv_style_t));
	lv_style_init(number_focused_style);
	lv_style_set_bg_color(number_focused_style, lv_color_white());
	lv_style_set_text_color(number_focused_style, lv_color_black());
	//lv_style_set_bg_color(&number_style, LV_STATE_EDITED, LV_COLOR_LIME);
	*/
	//Init a new style for content.
	lv_style_t *content_style = (lv_style_t *)malloc(sizeof(lv_style_t));
	lv_style_init(content_style);
	lv_style_set_text_font(content_style, &lv_font_montserratMedium_24);
	lv_style_set_border_width(content_style, 0);
	lv_style_set_text_color(content_style, lv_color_white());
	lv_style_set_pad_top(content_style, 0);

	//Create menu page group
	ui->menu_page_group = lv_group_create();
	lv_group_set_wrap(ui->menu_page_group, false);
	//ui->menu_page_item_container = (lv_obj_t **)malloc(MENU_E_NUM * sizeof(lv_obj_t *));
	//ui->menu_page_item_number = (lv_obj_t **)malloc(MENU_E_NUM * sizeof(lv_obj_t *));
	//ui->menu_page_item_content = (lv_obj_t **)malloc(MENU_E_NUM * sizeof(lv_obj_t *));

	for(int i = 0; i < MENU_E_NUM; i++){
		// menu item container
		//ui->menu_page_item_container[i] = lv_obj_create(ui->menu_page_list_page);
		ui->menu_page_item_container[i] = lv_btn_create(ui->menu_page_list_page);
		lv_obj_set_size(ui->menu_page_item_container[i], MENU_PAGE_ITEM_WIDTH, MENU_PAGE_ITEM_HEIGHT);
		lv_obj_set_pos(ui->menu_page_item_container[i], MENU_PAGE_ITEM_X, MENU_PAGE_ITEM_Y + MENU_PAGE_ITEM_Y_SPAN * i);
		lv_obj_set_style_pad_all(ui->menu_page_item_container[i], 0, 0);
		lv_obj_add_style(ui->menu_page_item_container[i], item_container_style, LV_PART_MAIN);
		lv_obj_add_style(ui->menu_page_item_container[i], item_container_focused_style, LV_STATE_FOCUSED);
    	lv_obj_set_scrollbar_mode(ui->menu_page_item_container[i], LV_SCROLLBAR_MODE_OFF);
		lv_obj_set_style_shadow_width(ui->menu_page_item_container[i], 0, LV_PART_MAIN|LV_STATE_DEFAULT);

		// menu item number
		ui->menu_page_item_number[i] = lv_label_create(ui->menu_page_item_container[i]);
		lv_obj_set_pos(ui->menu_page_item_number[i], MENU_PAGE_ITEM_NO_X, MENU_PAGE_ITEM_NO_Y);
		lv_label_set_long_mode(ui->menu_page_item_number[i], LV_LABEL_LONG_WRAP);
		lv_obj_set_size(ui->menu_page_item_number[i], MENU_PAGE_ITEM_NO_WIDTH, MENU_PAGE_ITEM_NO_WIDTH);
		lv_obj_set_pos(ui->menu_page_item_number[i], MENU_PAGE_ITEM_NO_X, MENU_PAGE_ITEM_NO_Y);
		lv_obj_add_style(ui->menu_page_item_number[i], number_style, LV_PART_MAIN);
		//lv_obj_add_style(ui->menu_page_item_number[i], number_focused_style, LV_STATE_FOCUSED);
		uint8_t number[3];
		snprintf(number, 3, "%d", i+1);
		lv_label_set_text(ui->menu_page_item_number[i], number);

		// menu item content
		ui->menu_page_item_content[i] = lv_label_create(ui->menu_page_item_container[i]);
		lv_obj_set_size(ui->menu_page_item_content[i], MENU_PAGE_ITEM_HEAD_WIDTH, MENU_PAGE_ITEM_HEIGHT);
		lv_obj_set_pos(ui->menu_page_item_content[i], MENU_PAGE_ITEM_HEAD_X, MENU_PAGE_ITEM_HEAD_Y);
		lv_obj_set_style_text_align(ui->menu_page_item_content[i], LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_add_style(ui->menu_page_item_content[i], content_style, LV_PART_MAIN);
		lv_label_set_text(ui->menu_page_item_content[i], menu_info[i].title);

		//Add to group
		lv_group_add_obj(ui->menu_page_group, ui->menu_page_item_container[i]);
	}

	//Write codes menu_page_lock
	ui->menu_page_lock = lv_switch_create(ui->menu_page_item_container[MENU_E_LOCK]);
	lv_obj_set_pos(ui->menu_page_lock, MENU_PAGE_ITEM_LOCK_X, MENU_PAGE_ITEM_LOCK_Y);
	lv_obj_set_size(ui->menu_page_lock, MENU_PAGE_ITEM_LOCK_WIDTH, MENU_PAGE_ITEM_LOCK_HEIGHT);

	//Write style for menu_page_lock, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->menu_page_lock, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->menu_page_lock, LOCK_DEFAULT_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->menu_page_lock, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->menu_page_lock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->menu_page_lock, MENU_PAGE_ITEM_LOCK_HEIGHT/2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->menu_page_lock, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for menu_page_lock, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
	lv_obj_set_style_bg_opa(ui->menu_page_lock, 255, LV_PART_INDICATOR|LV_STATE_CHECKED);
	lv_obj_set_style_bg_color(ui->menu_page_lock, LOCK_CHECKED_COLOR, LV_PART_INDICATOR|LV_STATE_CHECKED);
	lv_obj_set_style_bg_grad_dir(ui->menu_page_lock, LV_GRAD_DIR_NONE, LV_PART_INDICATOR|LV_STATE_CHECKED);
	lv_obj_set_style_border_width(ui->menu_page_lock, 0, LV_PART_INDICATOR|LV_STATE_CHECKED);

	lv_group_focus_obj(ui->menu_page_item_container[6]);
	events_init_menu_page(ui);

	//Create menu page message box group
	ui->menu_page_message_box = lv_group_create();
	lv_group_set_wrap(ui->menu_page_message_box, false);

	//Update current screen layout.
	lv_obj_update_layout(ui->menu_page);

}
