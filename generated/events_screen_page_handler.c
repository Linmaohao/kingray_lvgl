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
#include "generated/gui_guider.h"
#include "lvgl.h"

#if LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif

static void screen_page_backlight_time_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	printf("----------- backlight_time code = %d\n", code);

	switch (code) {
	// 按下第一次是FOCUSED，第二次是click
	case LV_EVENT_CLICKED:
	{
		// 编写代码保存当前值
		int select = lv_roller_get_selected(guider_ui.screen_page_backlight_time);
		printf("backlight_time = %d\n", select);
		break;
	}
	case LV_EVENT_KEY:
	{
		// 获取当前按键indev的动作
		int key_value = lv_indev_get_key(lv_indev_get_act());
		printf("key_value = %d\n", key_value);
		if (key_value == LV_KEY_ESC)
		{
			// 判断是否处于编辑状态
			int is_editing = lv_obj_has_state(guider_ui.screen_page_backlight_time, LV_STATE_EDITED);
			if (is_editing) {
				printf("Roller is in EDIT mode.\n");
				lv_obj_clear_state(guider_ui.screen_page_backlight_time, LV_STATE_EDITED);
			} else {
				ui_load_scr_animation(&guider_ui, &guider_ui.menu_page, guider_ui.menu_page_del, &guider_ui.info_page_del, setup_scr_menu_page, LV_SCR_LOAD_ANIM_NONE, 5, 5, true, true);
				printf("Roller is in NORMAL mode.\n");
			}
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

static void screen_page_backlight_switch_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_VALUE_CHANGED:
	{
		// 使能按键处理
		int is_on = lv_obj_has_state(guider_ui.screen_page_backlight_switch, LV_STATE_CHECKED);
		if (is_on) {
			printf("Switch is ON\n");
		} else {
			printf("Switch is OFF\n");
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
			ui_load_scr_animation(&guider_ui, &guider_ui.menu_page, guider_ui.menu_page_del, &guider_ui.info_page_del, setup_scr_menu_page, LV_SCR_LOAD_ANIM_NONE, 5, 5, true, true);
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
	// lv_event_code_t code = lv_event_get_code(e);
	// lv_obj_t *obj = lv_event_get_target(e);
	// //printf("code = %d\n", code);
	// switch (code) {
	// case LV_EVENT_CLICKED:
	// {
	// 	lv_group_set_editing(guider_ui.screen_page_group, true);
	// 	break;
	// }
	// default:
	// 	break;
	// }
}

void events_init_screen_page(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_page_backlight_time, screen_page_backlight_time_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_page_backlight_switch, screen_page_backlight_switch_event_handler, LV_EVENT_ALL, NULL);
}