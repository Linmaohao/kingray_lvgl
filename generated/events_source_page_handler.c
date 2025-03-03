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

static void source_page_source_event_handler(lv_event_t *e)
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
	case LV_EVENT_VALUE_CHANGED:
	{
		char a[12] = {};
		printf("status = %x\n", state);
		printf("code = %d\n", code);
		lv_dropdown_get_selected_str(obj, a, 12);
		printf("selected str = %s\n", a);
		break;
	}
	default:
		break;
	}
}


static void source_page_sens_event_handler(lv_event_t *e)
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
	case LV_EVENT_VALUE_CHANGED:
	{
		char a[12] = {};
		printf("status = %x\n", state);
		printf("code = %d\n", code);
		lv_dropdown_get_selected_str(obj, a, 12);
		printf("selected str = %s\n", a);
		break;
	}
	default:
		break;
	}
}
void events_init_source_page(lv_ui *ui)
{
	for (int i = 0; i < LAYOUT_INPUT_SIZE; i++){
		lv_obj_add_event_cb(ui->source_page_source[i], source_page_source_event_handler, LV_EVENT_ALL, NULL);
		lv_obj_add_event_cb(ui->source_page_sens[i], source_page_sens_event_handler, LV_EVENT_ALL, NULL);
	}
}