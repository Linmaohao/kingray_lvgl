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
static u_int8_t name_free_glag[RENAME_DISPLAY_NAME_LEN] = {0};

static void rename_page_name_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *obj = lv_event_get_target(e);
	event_data_t *data = (event_data_t *)lv_event_get_user_data(e);

	switch (code) {
		case LV_EVENT_CLICKED:
		{
			// 编写代码保存当前值
			char buf[2] = {0};

			lv_roller_get_selected_str(obj, buf, 1);
			printf("this work [%d] is = %c\n", data->number, buf[0]);
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
				int is_editing = lv_obj_has_state(obj, LV_STATE_EDITED);
				if (is_editing) {
					// 重新聚焦
					lv_group_focus_obj(obj);
				} else {
					ui_load_scr_animation(&guider_ui, &guider_ui.menu_page, guider_ui.menu_page_del, &guider_ui.rename_page_del, setup_scr_menu_page, LV_SCR_LOAD_ANIM_NONE, 5, 5, true, true);
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
			if (data->number >= 0 && data->number < RENAME_DISPLAY_NAME_LEN && !name_free_glag[data->number])
			{
				name_free_glag[data->number] = 1;
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

void events_init_rename_page(lv_ui *ui)
{
	for (int i = 0; i < RENAME_DISPLAY_NAME_LEN; i++){
		event_data_t *event_data = (event_data_t *)malloc(sizeof(event_data_t));
		event_data->number = i;
		name_free_glag[i] = 0;
		lv_obj_add_event_cb(ui->rename_page_name[i], rename_page_name_event_handler, LV_EVENT_ALL, event_data);
	}
}