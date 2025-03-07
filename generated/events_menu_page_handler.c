/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

#if LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif

static void menu_page_item_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *obj = lv_event_get_target(e);
	if (code >= LV_EVENT_COVER_CHECK && code <= LV_EVENT_DRAW_PART_END) {
	} else {
		printf("menu code = %d\n", code);
	}
	switch (code) {
	case LV_EVENT_CLICKED:
	{
		event_data_t *data = (event_data_t *)lv_event_get_user_data(e);
		switch(data->number) {
			case MENU_E_VOLUME:
				ui_load_scr_animation(&guider_ui, &guider_ui.volume_page, guider_ui.volume_page_del, &guider_ui.main_page_del, setup_scr_volume_page, LV_SCR_LOAD_ANIM_NONE, 5, 5, true, true);
				break;
			case MENU_E_PRESET:
				ui_load_scr_animation(&guider_ui, &guider_ui.preset_page, guider_ui.preset_page_del, &guider_ui.main_page_del, setup_scr_preset_page, LV_SCR_LOAD_ANIM_NONE, 5, 5, true, true);
				break;
			case MENU_E_SOURCE:
				ui_load_scr_animation(&guider_ui, &guider_ui.source_page, guider_ui.source_page_del, &guider_ui.main_page_del, setup_scr_source_page, LV_SCR_LOAD_ANIM_NONE, 5, 5, true, true);
				break;
			case MENU_E_STATUS:
				ui_load_scr_animation(&guider_ui, &guider_ui.status_page, guider_ui.status_page_del, &guider_ui.main_page_del, setup_scr_status_page, LV_SCR_LOAD_ANIM_NONE, 5, 5, true, true);
				break;
			case MENU_E_RENAME:
				ui_load_scr_animation(&guider_ui, &guider_ui.rename_page, guider_ui.rename_page_del, &guider_ui.main_page_del, setup_scr_rename_page, LV_SCR_LOAD_ANIM_NONE, 5, 5, true, true);
				break;
			case MENU_E_IPSET:
				ui_load_scr_animation(&guider_ui, &guider_ui.ipset_page, guider_ui.ipset_page_del, &guider_ui.main_page_del, setup_scr_ipset_page, LV_SCR_LOAD_ANIM_NONE, 5, 5, true, true);
				break;
			case MENU_E_LOCK:
				if (lv_obj_has_state(guider_ui.menu_page_lock, LV_STATE_CHECKED)) {
					lv_obj_clear_state(guider_ui.menu_page_lock, LV_STATE_CHECKED);
				} else {
					lv_obj_add_state(guider_ui.menu_page_lock, LV_STATE_CHECKED);
				}
				break;
			case MENU_E_INFO:
				ui_load_scr_animation(&guider_ui, &guider_ui.info_page, guider_ui.info_page_del, &guider_ui.main_page_del, setup_scr_info_page, LV_SCR_LOAD_ANIM_NONE, 5, 5, true, true);
				break;
			case MENU_E_SCREEN:
				ui_load_scr_animation(&guider_ui, &guider_ui.screen_page, guider_ui.screen_page_del, &guider_ui.main_page_del, setup_scr_screen_page, LV_SCR_LOAD_ANIM_NONE, 5, 5, true, true);
				break;
			default:
				break;
		}
		break;
	}
	case LV_EVENT_KEY:
	{
		// 获取当前按键indev的动作
		int key_value = lv_indev_get_key(lv_indev_get_act());
		printf("key_value = %d\n", key_value);
		if (key_value == LV_KEY_ESC)
		{
			ui_load_scr_animation(&guider_ui, &guider_ui.main_page, guider_ui.main_page_del, &guider_ui.load_page_del, setup_scr_main_page, LV_SCR_LOAD_ANIM_NONE, 5, 5, false, true);
		}
    	// 其他按键处理
		else
		{
		  CommonCallback(key_value);
		}
	}
	default:
		break;
	}
}

static void menu_page_message_event_handler(lv_event_t *e)
{
	lv_obj_t * obj = lv_event_get_target(e);
	lv_event_code_t code = lv_event_get_code(e);
	if (code >= LV_EVENT_COVER_CHECK && code <= LV_EVENT_DRAW_PART_END) {
	} else {
		printf("code = %d\n", code);
	}
	switch (code) {
		case LV_EVENT_VALUE_CHANGED:
		{
			printf("=========== LV_EVENT_VALUE_CHANGED\n");
		}
		case LV_EVENT_CLICKED:
		{
			uint16_t id = lv_msgbox_get_active_btn(guider_ui.menu_page_message_box);
			switch(id) {
			case 0:
			{
				printf("it is ok button\n");
				lv_msgbox_close(guider_ui.menu_page_message_box);
				lv_indev_set_group(indev_encoder, guider_ui.menu_page_group);
				lv_indev_set_group(indev_keypad, guider_ui.menu_page_group);
				break;
			}
			case 1:
			{
				printf("it is cancel button\n");
				lv_msgbox_close(guider_ui.menu_page_message_box);
				lv_indev_set_group(indev_encoder, guider_ui.menu_page_group);
				lv_indev_set_group(indev_keypad, guider_ui.menu_page_group);
				// 不知为何加了下面的，无法关闭msgbox
				// if (lv_obj_has_state(guider_ui.menu_page_lock, LV_STATE_CHECKED)) {
				// 	lv_obj_clear_state(guider_ui.menu_page_lock, LV_STATE_CHECKED);
				// } else {
				// 	lv_obj_add_state(guider_ui.menu_page_lock, LV_STATE_CHECKED);
				// }
				break;
			}
			default:
				break;
			}
		}
		case LV_EVENT_FOCUSED:
		{
			// lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, LV_PART_MAIN | LV_STATE_FOCUSED);
			// lv_obj_set_style_text_color(obj, lv_color_black(), LV_PART_MAIN | LV_STATE_FOCUSED);
			printf("=========== LV_EVENT_FOCUSED\n");
			break;
		}
		case LV_EVENT_KEY:
		{
			// 不做处理
		break;
		}
		default:
			break;
		}
	}

void create_message_box(void) {
	//Write codes menu_page_message_box
	static const char * menu_page_message_box_btns[] = {"Ok","Cancel",""};
	guider_ui.menu_page_message_box = lv_msgbox_create(guider_ui.menu_page, NULL, "Is change configure?", menu_page_message_box_btns, false);
	lv_obj_set_size(lv_msgbox_get_btns(guider_ui.menu_page_message_box), 180, 30);
	lv_obj_align(guider_ui.menu_page_message_box, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_size(guider_ui.menu_page_message_box, 200, 80);

	lv_obj_set_style_bg_opa(guider_ui.menu_page_message_box, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(guider_ui.menu_page_message_box, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_content_main_default
	static lv_style_t style_content_main_default;
	ui_init_style(&style_content_main_default);

	lv_style_set_text_color(&style_content_main_default, lv_color_white());
	lv_style_set_text_font(&style_content_main_default, &lv_font_montserratMedium_16);
	lv_style_set_text_opa(&style_content_main_default, LV_OPA_COVER);
	lv_style_set_text_letter_space(&style_content_main_default, 0);
	lv_obj_add_style(lv_msgbox_get_text(guider_ui.menu_page_message_box), &style_content_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_extra_btns_items_default
	static lv_style_t style_extra_btns_items_default;
	ui_init_style(&style_extra_btns_items_default);

	lv_style_set_bg_opa(&style_extra_btns_items_default, LV_OPA_COVER);
	lv_style_set_bg_color(&style_extra_btns_items_default, lv_palette_main(LV_PALETTE_GREEN));
	lv_style_set_bg_grad_dir(&style_extra_btns_items_default, LV_GRAD_DIR_NONE);
	lv_style_set_border_width(&style_extra_btns_items_default, 0);
	lv_style_set_radius(&style_extra_btns_items_default, 10);
	lv_style_set_text_color(&style_extra_btns_items_default, lv_color_black());
	lv_style_set_text_font(&style_extra_btns_items_default, &lv_font_montserratMedium_18);
	lv_style_set_text_opa(&style_extra_btns_items_default, LV_OPA_COVER);
	lv_style_set_shadow_width(&style_extra_btns_items_default, 0);
	lv_obj_t *btns = lv_msgbox_get_btns(guider_ui.menu_page_message_box);
	lv_obj_add_style(btns, &style_extra_btns_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

	lv_obj_set_style_bg_opa(btns, LV_OPA_COVER, LV_PART_MAIN | LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(btns, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN | LV_STATE_DEFAULT);

	//Add focus style
	lv_obj_set_style_outline_opa(btns, LV_OPA_COVER, LV_PART_ITEMS|LV_STATE_FOCUSED);
	lv_obj_set_style_outline_color(btns, lv_palette_lighten(LV_PALETTE_BLUE, 1), LV_PART_ITEMS|LV_STATE_FOCUSED);
	lv_obj_set_style_outline_width(btns, 3, LV_PART_ITEMS|LV_STATE_FOCUSED);
	lv_obj_add_style(btns, &style_extra_btns_items_default, LV_PART_ITEMS|LV_STATE_FOCUSED);

	// 添加焦点样式
	// lv_obj_set_style_bg_opa(btns, LV_OPA_COVER, LV_PART_ITEMS | LV_STATE_FOCUSED);
	// lv_obj_set_style_bg_color(btns, lv_palette_main(LV_PALETTE_GREEN), LV_PART_ITEMS | LV_STATE_FOCUSED);
	// lv_obj_set_style_text_color(btns, lv_color_black(), LV_PART_ITEMS | LV_STATE_FOCUSED);
	// lv_obj_set_style_text_opa(btns, LV_OPA_COVER, LV_PART_ITEMS | LV_STATE_FOCUSED);


	//lv_obj_add_event_cb(guider_ui.menu_page_message_box, menu_page_message_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(guider_ui.menu_page_message_box, menu_page_message_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(btns, menu_page_message_event_handler, LV_EVENT_ALL, NULL);


	lv_group_add_obj(guider_ui.menu_page_message_group, btns);
	lv_indev_set_group(indev_keypad, guider_ui.menu_page_message_group);
	lv_indev_set_group(indev_encoder, guider_ui.menu_page_message_group);
	lv_group_focus_obj(btns);  // 聚焦到第一个按钮
	lv_group_set_editing(guider_ui.menu_page_message_group, true);
	lv_btnmatrix_set_one_checked(btns, true);
}

static void menu_page_lock_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *obj = lv_event_get_target(e);
	printf("code = %d\n", code);
	switch (code) {
	case LV_EVENT_REFR_EXT_DRAW_SIZE:
	{
		create_message_box();
		break;
	}
	default:
		break;
	}
}

void events_init_menu_page(lv_ui *ui)
{
	for (int i = 0; i < MENU_E_NUM; i++) {
		event_data_t *event_data = (event_data_t *)malloc(sizeof(event_data_t));
		event_data->number = i;
		// lv_obj_add_event_cb(ui->menu_page_item_container[i], menu_page_item_event_handler, LV_EVENT_ALL, event_data);
		lv_obj_add_event_cb(ui->menu_page_item_container[i], menu_page_item_event_handler, LV_EVENT_ALL, event_data);
	}
	lv_obj_add_event_cb(ui->menu_page_lock, menu_page_lock_event_handler, LV_EVENT_ALL, NULL);
}