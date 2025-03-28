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
#include "../indev/lv_port_indev.h"
#include "lvgl.h"

#if LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif

// static void main_page_btn_test_event_handler (lv_event_t *e)
// {
// 	lv_event_code_t code = lv_event_get_code(e);

// 	switch (code) {
// 	case LV_EVENT_CLICKED:
// 	{
// 		// ui_load_scr_animation(&guider_ui, &guider_ui.standby_page, guider_ui.standby_page_del, &guider_ui.main_page_del, setup_scr_standby_page, LV_SCR_LOAD_ANIM_NONE, 200, 200, true, true);
// 		ui_load_scr_animation(&guider_ui, &guider_ui.menu_page, guider_ui.menu_page_del, &guider_ui.main_page_del, setup_scr_menu_page, LV_SCR_LOAD_ANIM_NONE, 200, 200, true, true);
// 		// ui_load_scr_animation(&guider_ui, &guider_ui.info_page, guider_ui.info_page_del, &guider_ui.main_page_del, setup_scr_info_page, LV_SCR_LOAD_ANIM_NONE, 200, 200, true, true);
// 		// ui_load_scr_animation(&guider_ui, &guider_ui.screen_page, guider_ui.screen_page_del, &guider_ui.main_page_del, setup_scr_screen_page, LV_SCR_LOAD_ANIM_NONE, 200, 200, true, true);
// 		// ui_load_scr_animation(&guider_ui, &guider_ui.preset_page, guider_ui.preset_page_del, &guider_ui.main_page_del, setup_scr_preset_page, LV_SCR_LOAD_ANIM_NONE, 200, 200, true, true);
// 		// ui_load_scr_animation(&guider_ui, &guider_ui.rename_page, guider_ui.rename_page_del, &guider_ui.main_page_del, setup_scr_rename_page, LV_SCR_LOAD_ANIM_NONE, 200, 200, true, true);
// 		// ui_load_scr_animation(&guider_ui, &guider_ui.ipset_page, guider_ui.ipset_page_del, &guider_ui.main_page_del, setup_scr_ipset_page, LV_SCR_LOAD_ANIM_NONE, 200, 200, true, true);
// 		// ui_load_scr_animation(&guider_ui, &guider_ui.source_page, guider_ui.source_page_del, &guider_ui.main_page_del, setup_scr_source_page, LV_SCR_LOAD_ANIM_NONE, 200, 200, true, true);
// 		// ui_load_scr_animation(&guider_ui, &guider_ui.volume_page, guider_ui.volume_page_del, &guider_ui.main_page_del, setup_scr_volume_page, LV_SCR_LOAD_ANIM_NONE, 200, 200, true, true);
// 		// ui_load_scr_animation(&guider_ui, &guider_ui.status_page, guider_ui.status_page_del, &guider_ui.main_page_del, setup_scr_status_page, LV_SCR_LOAD_ANIM_NONE, 200, 200, true, true);

// 		break;
// 	}
// 	default:
// 		break;
// 	}
// }

static void main_page_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	if (code < LV_EVENT_COVER_CHECK || code > LV_EVENT_DRAW_PART_END) {
		printf("main code = %d\n", code);
	}

	switch (code) {
	// case LV_EVENT_CLICKED:	// 按下第一次是FOCUSED
	case LV_EVENT_LONG_PRESSED:
	{
		printf("LONG PRESS !!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");
		ui_load_scr_animation(&guider_ui, &guider_ui.menu_page, guider_ui.menu_page_del, &guider_ui.main_page_del, setup_scr_menu_page, LV_SCR_LOAD_ANIM_NONE, 5, 5, true, true);
	}
	case LV_EVENT_FOCUSED:
	{
		// ui_load_scr_animation(&guider_ui, &guider_ui.standby_page, guider_ui.standby_page_del, &guider_ui.main_page_del, setup_scr_standby_page, LV_SCR_LOAD_ANIM_NONE, 200, 200, true, true);
		//ui_load_scr_animation(&guider_ui, &guider_ui.menu_page, guider_ui.menu_page_del, &guider_ui.main_page_del, setup_scr_menu_page, LV_SCR_LOAD_ANIM_NONE, 5, 5, true, true);
		break;
	}
	case LV_EVENT_KEY:
	{
		// 获取当前按键indev的动作
		int key_value = lv_indev_get_key(lv_indev_get_act());
		printf("key_value = %d\n", key_value);
		if (key_value == LV_KEY_ESC)
		{

		}
    	// 其他按键处理
		else
		{
		  CommonCallback(key_value);
		}
		break;
	}
	default:
		break;
	}
	printf("----\n");
}

void events_init_main_page(lv_ui *ui)
{
	//lv_obj_add_event_cb(ui->main_page_btn_test, main_page_btn_test_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->main_page_temp_btn, main_page_event_handler, LV_EVENT_ALL, NULL);
}