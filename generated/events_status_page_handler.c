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

static void status_page_btn_event_handler(lv_event_t *e)
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

static void status_page_work_mode_event_handler(lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);
	lv_obj_t *obj = lv_event_get_target(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_group_set_editing(guider_ui.status_page_group, true);
		lv_state_t state = lv_obj_get_state(obj);
		printf("%x\n", state);
		printf("code = %d\n", code);

		break;
	}
	case LV_EVENT_VALUE_CHANGED:
	{
		uint16_t sel = lv_roller_get_selected(guider_ui.status_page_work_mode_select[0]);
		printf("code === %d selected = %d\n", code, sel);
	}
	default:
		break;
	}
}

void events_init_status_page(lv_ui *ui)
{
	for (int i = 0; i < LAYOUT_OUTPUT_SIZE; i++){
		for ( int j = 0; j < LAYOUT_INPUT_SIZE; j++){
			lv_obj_add_event_cb(ui->status_page_btn_router[i][j], status_page_btn_event_handler, LV_EVENT_ALL, NULL);
		}
	}
	for (int i = 0; i < LAYOUT_OUTPUT_SIZE / 2; i++){
		lv_obj_add_event_cb(ui->status_page_work_mode_select[i], status_page_work_mode_event_handler, LV_EVENT_ALL, NULL);
	}
}