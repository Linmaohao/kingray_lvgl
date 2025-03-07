/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_standby_page(lv_ui *ui)
{
	//Write codes standby_page
	ui->standby_page = lv_obj_create(NULL);
	lv_obj_set_size(ui->standby_page, LV_HOR_RES_MAX, LV_VER_RES_MAX);
	lv_obj_set_scrollbar_mode(ui->standby_page, LV_SCROLLBAR_MODE_OFF);

	//Write style for standby_page, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->standby_page, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->standby_page, BACKGROUND_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->standby_page, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);


	//The custom code of standby_page.
	ui->standby_page_img_standby = lv_img_create(ui->standby_page);
	lv_img_set_src(ui->standby_page_img_standby, &sleep_mode);
	lv_obj_set_size(ui->standby_page_img_standby, LV_HOR_RES_MAX, LV_VER_RES_MAX);

	ui->standby_page_group = lv_group_create();
    lv_indev_set_group(indev_keypad, ui->standby_page_group);
    lv_indev_set_group(indev_encoder, ui->standby_page_group);

	lv_group_add_obj(ui->standby_page_group, ui->standby_page);

	//Update current screen layout.
	lv_obj_update_layout(ui->standby_page);

	events_init_standby_page(ui);
}
