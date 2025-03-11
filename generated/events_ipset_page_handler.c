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

// 用作malloc的free标记，防止重复释放（有这种现象），IP占4，GW占4
static u_int8_t ip_gw_free_glag[8] = {0};

static void ipset_page_number_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *obj = lv_event_get_target(e);
	event_data_t *data = (event_data_t *)lv_event_get_user_data(e);

	switch (code) {
	// 按下第一次是FOCUSED，第二次是click，需要知道序号保存ip
	case LV_EVENT_CLICKED:
	{
		if (data->number >= 0 && data->number < 4) {
			int ip = lv_roller_get_selected(guider_ui.ipset_page_ip[data->number]);
			printf("ip address [%d] = %d\n", data->number, ip);
		} else if (data->number >= 4 && data->number < 8) {
			int gw = lv_roller_get_selected(guider_ui.ipset_page_gw[data->number - 4]);
			printf("ip gatewway [%d] = %d\n", data->number - 4, gw);
		}
		// lv_group_set_editing(guider_ui.ipset_page_group, true);
		// lv_state_t state = lv_obj_get_state(obj);
		break;
	}
	case LV_EVENT_KEY:
	{
		// 获取当前按键indev的动作
		int key_value = lv_indev_get_key(lv_indev_get_act());
		printf("key_value = %d\n", key_value);
		if (key_value == LV_KEY_ESC)
		{
			lv_obj_t *obj_tmp = NULL;
			if (data->number >= 0 && data->number < 4) {
				obj_tmp = guider_ui.ipset_page_ip[data->number];
			} else if (data->number >= 4 && data->number < 8) {
				obj_tmp = guider_ui.ipset_page_gw[data->number - 4];
			}

			// 判断是否处于编辑状态
			int is_editing = lv_obj_has_state(obj_tmp, LV_STATE_EDITED);
			if (is_editing) {
				printf("Roller is in EDIT mode.\n");
				// lv_obj_clear_state(guider_ui.screen_page_backlight_time, LV_STATE_EDITED);
				// lv_obj_clear_flag(guider_ui.screen_page_backlight_time, LV_OBJ_FLAG_SCROLLABLE);
				// 重新聚焦
				lv_group_focus_obj(obj_tmp);
			} else {
				ui_load_scr_animation(&guider_ui, &guider_ui.menu_page, guider_ui.menu_page_del, &guider_ui.ipset_page_del, setup_scr_menu_page, LV_SCR_LOAD_ANIM_NONE, 5, 5, true, true);
				printf("Roller is in NORMAL mode.\n");
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
		if (data->number >= 0 && data->number < 8 && !ip_gw_free_glag[data->number])
		{
			ip_gw_free_glag[data->number] = 1;
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

static void ipset_page_ensure_handler(lv_event_t *e)
{
	printf("ensure btn process\n");
}

void events_init_ipset_page(lv_ui *ui)
{
	for (int i = 0; i < 8; i++){
		event_data_t *event_data = (event_data_t *)malloc(sizeof(event_data_t));
		event_data->number = i;
		ip_gw_free_glag[i] = 0;

		if (i >= 0 && i < 4){
			lv_obj_add_event_cb(ui->ipset_page_ip[i], ipset_page_number_event_handler, LV_EVENT_ALL, event_data);
		} else {
			lv_obj_add_event_cb(ui->ipset_page_gw[i-4], ipset_page_number_event_handler, LV_EVENT_ALL, event_data);
		}
	}
	lv_obj_add_event_cb(ui->ipset_page_ensure_btn, ipset_page_ensure_handler, LV_EVENT_CLICKED, NULL);
}
