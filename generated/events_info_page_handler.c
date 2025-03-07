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
#include "../indev/lv_port_indev.h"

#if LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif

static void info_page_event_handler (lv_event_t *e)
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

void events_init_info_page(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->info_page, info_page_event_handler, LV_EVENT_KEY, NULL);
}