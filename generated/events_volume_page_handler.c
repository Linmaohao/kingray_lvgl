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
#include <sys/types.h>
#include "lvgl.h"

#if LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif

// 用作malloc的free标记，防止重复释放（有这种现象）
static u_int8_t mute_free_glag[LAYOUT_TOTAL_CHN_SIZE] = {0};
static u_int8_t gain_free_glag[LAYOUT_TOTAL_CHN_SIZE] = {0};

static void volume_page_mute_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *obj = lv_event_get_target(e);
	//lv_state_t state = lv_obj_get_state(obj);
	event_data_t *data = (event_data_t *)lv_event_get_user_data(e);
	switch (code) {
	case LV_EVENT_CLICKED:
	{
		printf("mute number = %d\n", data->number);
		break;
	}
	case LV_EVENT_KEY:
	{
		// 获取当前按键indev的动作
		int key_value = lv_indev_get_key(lv_indev_get_act());
		printf("key_value = %d\n", key_value);
		if (key_value == LV_KEY_ESC)
		{
			ui_load_scr_animation(&guider_ui, &guider_ui.menu_page, guider_ui.menu_page_del, &guider_ui.volume_page_del, setup_scr_menu_page, LV_SCR_LOAD_ANIM_NONE, 5, 5, true, true);
		}
		// 其他按键处理
		else
		{
			CommonCallback(key_value);
		}
		break;
	}
	case LV_EVENT_DELETE:
	{
		if (data->number >= 0 && data->number < LAYOUT_TOTAL_CHN_SIZE && !mute_free_glag[data->number])
		{
			mute_free_glag[data->number] = 1;
			// printf("!!!!!!!!!!!!!!!!!!!!! delete number = %d\n", data->number);
			free(data);
			data = NULL;
		}
		break;
	}
	default:
		break;
	}
}

static void volume_page_gain_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *obj = lv_event_get_target(e);
	// 获取当前状态
	lv_state_t state = lv_obj_get_state(obj);
	event_data_t *data = (event_data_t *)lv_event_get_user_data(e);

	switch (code) {
		case LV_EVENT_VALUE_CHANGED:
		{
			uint8_t str[10];
			float value = lv_slider_get_value(obj) / 10.0f;
			snprintf(str, sizeof(str), "%.1f", value);
			printf("%d\n", data->number);
			lv_label_set_text(guider_ui.volume_page_gain_label[data->number], str);
			break;
		}
		case LV_EVENT_KEY:
		{
			// 获取当前按键indev的动作
			int key_value = lv_indev_get_key(lv_indev_get_act());
			printf("key_value = %d\n", key_value);
			if (key_value == LV_KEY_ESC)
			{
				// printf("state = %4x", state);
				if (state & LV_STATE_EDITED) {
					lv_group_focus_obj(obj);
				} else {
					ui_load_scr_animation(&guider_ui, &guider_ui.menu_page, guider_ui.menu_page_del, &guider_ui.volume_page_del, setup_scr_menu_page, LV_SCR_LOAD_ANIM_NONE, 5, 5, true, true);
				}
			}
			// 其他按键处理
			else
			{
				CommonCallback(key_value);
			}
			break;
		}
		case LV_EVENT_DELETE:
		{
			if (data->number >= 0 && data->number < LAYOUT_TOTAL_CHN_SIZE && !gain_free_glag[data->number])
			{
				gain_free_glag[data->number] = 1;
				// printf("!!!!!!!!!!!!!!!!!!!!! delete number = %d\n", data->number);
				free(data);
				data = NULL;
			}
			break;
		}
		default:
			break;
	}
}

void events_init_volume_page(lv_ui *ui)
{
	for (int i = 0; i < LAYOUT_TOTAL_CHN_SIZE; i++){
		event_data_t *event_data = (event_data_t *)malloc(sizeof(event_data_t));
		event_data->number = i;
		mute_free_glag[i] = 0;
		gain_free_glag[i] = 0;
		lv_obj_add_event_cb(ui->volume_page_mute_btn[i], volume_page_mute_event_handler, LV_EVENT_ALL, event_data);
		lv_obj_add_event_cb(ui->volume_page_gain[i], volume_page_gain_event_handler, LV_EVENT_ALL, event_data);
	}
}