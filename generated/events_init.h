/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/


#ifndef EVENTS_INIT_H_
#define EVENTS_INIT_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"

typedef struct {
	int number;
	float some_float;
	const uint8_t *some_string;
} event_data_t;

void events_init(lv_ui *ui);

void events_init_load_page(lv_ui *ui);
void events_init_main_page(lv_ui *ui);
void events_init_standby_page(lv_ui *ui);
void events_init_menu_page(lv_ui *ui);
void events_init_volume_page(lv_ui *ui);
void events_init_preset_page(lv_ui *ui);
void events_init_source_page(lv_ui *ui);
void events_init_status_page(lv_ui *ui);
void events_init_rename_page(lv_ui *ui);
void events_init_ipset_page(lv_ui *ui);
void events_init_info_page(lv_ui *ui);
void events_init_screen_page(lv_ui *ui);

void CommonCallback(int key_value);

#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */
