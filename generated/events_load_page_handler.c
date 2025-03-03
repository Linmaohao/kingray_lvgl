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

static void load_page_bar_load_event_handler (lv_event_t *e)
{
	lv_obj_t *target = lv_event_get_target(e);
	lv_obj_draw_part_dsc_t * dsc = lv_event_get_param(e);
	if(lv_area_get_width(dsc->draw_area) > lv_area_get_width(&(target->coords))) {
		ui_load_scr_animation(&guider_ui, &guider_ui.main_page, guider_ui.main_page_del, &guider_ui.load_page_del, setup_scr_main_page, LV_SCR_LOAD_ANIM_NONE, 200, 200, false, true);
	}
}


void events_init_load_page(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->load_page_bar_load, load_page_bar_load_event_handler, LV_EVENT_DRAW_PART_END, NULL);
}
