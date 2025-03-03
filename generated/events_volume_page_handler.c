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

static void volume_page_mute_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *obj = lv_event_get_target(e);
	lv_state_t state = lv_obj_get_state(obj);
	switch (code) {
	case LV_EVENT_CLICKED:
	{
		printf("status = %x\n", state);
		printf("code = %d\n", code);
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
	lv_state_t state = lv_obj_get_state(obj);
	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_group_set_editing(guider_ui.volume_page_group, true);
		break;
	}
	case LV_EVENT_VALUE_CHANGED:
	{
		uint8_t str[10];
		event_data_t *data = (event_data_t *)lv_event_get_user_data(e);
		float value = lv_slider_get_value(obj) / 10.0f;
    	snprintf(str, sizeof(str), "%.1f", value);
		printf("%d\n", data->number);
    	lv_label_set_text(guider_ui.volume_page_gain_label[data->number], str);
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
		lv_obj_add_event_cb(ui->volume_page_mute_btn[i], volume_page_mute_event_handler, LV_EVENT_ALL, event_data);
		lv_obj_add_event_cb(ui->volume_page_gain[i], volume_page_gain_event_handler, LV_EVENT_ALL, event_data);
	}
}