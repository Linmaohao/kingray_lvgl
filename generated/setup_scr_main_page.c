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

// dev name
#define MAIN_PAGE_DEV_NAME_X                         2
#define MAIN_PAGE_DEV_NAME_Y                         2
#define MAIN_PAGE_DEV_NAME_WIDTH                     130
// lock
#define MAIN_PAGE_LOCK_X                             142
#define MAIN_PAGE_LOCK_Y                             2
#define MAIN_PAGE_LOCK_WIDTH                         32
// preset name
#define MAIN_PAGE_PRESET_NAME_X                      178
#define MAIN_PAGE_PRESET_NAME_Y                      2
#define MAIN_PAGE_PRESET_NAME_WIDTH                  130
// temperature
#define MAIN_PAGE_TP_X                               1
#define MAIN_PAGE_TP_Y                               TITLE_HEIGHT
#define MAIN_PAGE_TP_WIDTH                           150
// volume
#define MAIN_PAGE_VOL_X                              152
#define MAIN_PAGE_VOL_Y                              TITLE_HEIGHT
#define MAIN_PAGE_VOL_WIDTH                          168
// pc control
#define MAIN_PAGE_PC_CONTROL_X                       1
#define MAIN_PAGE_PC_CONTROL_Y                       (MAIN_PAGE_TP_Y + LABEL_HEIGHT + 1)
#define MAIN_PAGE_PC_CONTROL_WIDTH                   318
#define MAIN_PAGE_PC_CONTROL_HEIGHT                  24
// work mode
#define MAIN_PAGE_WORKMODE_X                         1
#define MAIN_PAGE_WORKMODE_Y                         (MAIN_PAGE_PC_CONTROL_Y + MAIN_PAGE_PC_CONTROL_HEIGHT + 1)
#define MAIN_PAGE_WORKMODE_WIDTH                     82
#define MAIN_PAGE_WORKMODE_HEIGHT                    22
// vu page
#define MAIN_PAGE_VU_PAGE_X                          0
#define MAIN_PAGE_VU_PAGE_Y                          (MAIN_PAGE_WORKMODE_Y + MAIN_PAGE_WORKMODE_HEIGHT + 2)
#define MAIN_PAGE_VU_PAGE_WIDTH                      LV_HOR_RES_MAX
#define MAIN_PAGE_VU_PAGE_HEIGHT                     (LV_VER_RES_MAX - MAIN_PAGE_VU_PAGE_Y - 4)
#define MAIN_PAGE_VU_CHN_HEIGHT                      26
#define MAIN_PAGE_VU_CHN_Y_SPAN                      30
// clip sens
#define MAIN_PAGE_CLIP_SENS_X                        1
#define MAIN_PAGE_CLIP_SENS_WIDTH                    51
// channel mute
#define MAIN_PAGE_CH_MUTE_WIDTH                      MAIN_PAGE_VU_CHN_HEIGHT
// vu
#define MAIN_PAGE_CH_VU_WIDTH                        179
#define MAIN_PAGE_CH_VU_IMG_WIDTH                    176
#define MAIN_PAGE_CH_VU_IMG_HEIGHT                   20
// gain limit
#define MAIN_PAGE_GAIN_LIMIT_WIDTH                   58


void setup_scr_main_page(lv_ui *ui)
{
	//Write codes page
	ui->main_page = lv_obj_create(NULL);
	lv_obj_set_size(ui->main_page, LV_HOR_RES_MAX, LV_VER_RES_MAX);
	lv_obj_set_scrollbar_mode(ui->main_page, LV_SCROLLBAR_MODE_OFF);

	//Write style for page, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->main_page, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->main_page, BACKGROUND_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->main_page, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes main_page_title
	ui->main_page_title = lv_obj_create(ui->main_page);
    lv_obj_set_pos(ui->main_page_title, 0, 0);
    lv_obj_set_size(ui->main_page_title, LV_HOR_RES_MAX, TITLE_HEIGHT);
    lv_obj_set_style_border_width(ui->main_page_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_page_title, DESIGNATED_COLOR_BLUE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->main_page_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Init a new style
	lv_style_t *main_style = (lv_style_t *)malloc(sizeof(lv_style_t));
    lv_style_init(main_style);
	lv_style_set_border_width(main_style, 0);
	lv_style_set_radius(main_style, 0);
	lv_style_set_text_color(main_style, MAIN_FONT_COLOR);
	lv_style_set_text_font(main_style, &lv_font_montserratMedium_24);
	lv_style_set_text_opa(main_style, LV_OPA_COVER);
	lv_style_set_text_letter_space(main_style, 1);
	lv_style_set_text_line_space(main_style, 0);
	lv_style_set_text_align(main_style, LV_TEXT_ALIGN_LEFT);
	lv_style_set_bg_opa(main_style, LV_OPA_TRANSP);
	lv_style_set_bg_grad_dir(main_style, LV_GRAD_DIR_NONE);
	lv_style_set_pad_top(main_style, 4);
	lv_style_set_pad_right(main_style, 0);
	lv_style_set_pad_bottom(main_style, 0);
	lv_style_set_pad_left(main_style, 5);
	lv_style_set_shadow_width(main_style, 0);

	//Write codes main_page_device_name
	ui->main_page_device_name = lv_label_create(ui->main_page);
	// lv_label_set_text(ui->main_page_device_name, "43Az");

	lv_obj_set_style_text_font(ui->main_page_device_name, &lv_front_source_fzltxh_20,  LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_label_set_text(ui->main_page_device_name, "嵌入式测试");

	lv_label_set_long_mode(ui->main_page_device_name, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->main_page_device_name, MAIN_PAGE_DEV_NAME_X, MAIN_PAGE_DEV_NAME_Y);
	lv_obj_set_size(ui->main_page_device_name, MAIN_PAGE_DEV_NAME_WIDTH, LABEL_HEIGHT);

	//Write style for main_page_device_name
	lv_obj_add_style(ui->main_page_device_name, main_style, LV_PART_MAIN);

	//Write codes main_page_lock
	ui->main_page_lock = lv_label_create(ui->main_page);
	lv_label_set_text(ui->main_page_lock, "");
	lv_label_set_long_mode(ui->main_page_lock, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->main_page_lock, MAIN_PAGE_LOCK_X, MAIN_PAGE_LOCK_Y);
	lv_obj_set_size(ui->main_page_lock, MAIN_PAGE_LOCK_WIDTH, LABEL_HEIGHT);

	//Write style for main_page_lock, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_add_style(ui->main_page_lock, main_style, LV_PART_MAIN);
	lv_obj_set_style_text_font(ui->main_page_lock, &lv_font_iconfont_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->main_page_lock, 8, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes main_page_preset_name
	ui->main_page_preset_name = lv_label_create(ui->main_page);
	lv_label_set_text(ui->main_page_preset_name, "1. Default Preset");
	lv_label_set_long_mode(ui->main_page_preset_name, LV_LABEL_LONG_SCROLL);
	lv_obj_set_pos(ui->main_page_preset_name, MAIN_PAGE_PRESET_NAME_X, MAIN_PAGE_PRESET_NAME_Y);
	lv_obj_set_size(ui->main_page_preset_name, MAIN_PAGE_PRESET_NAME_WIDTH, LABEL_HEIGHT);

	//Write style for main_page_preset_name
	lv_obj_add_style(ui->main_page_preset_name, main_style, LV_PART_MAIN);

	//Write codes main_page_temperature
	ui->main_page_temperature = lv_label_create(ui->main_page);
	lv_label_set_text(ui->main_page_temperature, "TP  44.1°C");
	lv_label_set_long_mode(ui->main_page_temperature, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->main_page_temperature, MAIN_PAGE_TP_X, MAIN_PAGE_TP_Y);
	lv_obj_set_size(ui->main_page_temperature, MAIN_PAGE_TP_WIDTH, LABEL_HEIGHT);

	//Write style for main_page_temperature, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_add_style(ui->main_page_temperature, main_style, LV_PART_MAIN);

	//Write codes main_page_volume
	ui->main_page_volume = lv_label_create(ui->main_page);
	lv_label_set_text(ui->main_page_volume, "VOL -30.0dB");
	lv_label_set_long_mode(ui->main_page_volume, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->main_page_volume, MAIN_PAGE_VOL_X, MAIN_PAGE_VOL_Y);
	lv_obj_set_size(ui->main_page_volume, MAIN_PAGE_VOL_WIDTH, LABEL_HEIGHT);

	//Write style for main_page_volume, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_add_style(ui->main_page_volume, main_style, LV_PART_MAIN);

	//Write codes main_page_pc_control
	ui->main_page_pc_control = lv_label_create(ui->main_page);
	lv_label_set_text(ui->main_page_pc_control, "protect");
	lv_label_set_long_mode(ui->main_page_pc_control, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->main_page_pc_control, MAIN_PAGE_PC_CONTROL_X, MAIN_PAGE_PC_CONTROL_Y);
	lv_obj_set_size(ui->main_page_pc_control, MAIN_PAGE_PC_CONTROL_WIDTH, MAIN_PAGE_PC_CONTROL_HEIGHT);

	//Write style for ui->main_page_pc_control, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_add_style(ui->main_page_pc_control, main_style, LV_PART_MAIN);
    lv_obj_set_style_text_align(ui->main_page_pc_control, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->main_page_pc_control, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->main_page_pc_control, DESIGNATED_COLOR_BLUE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->main_page_pc_control, &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->main_page_pc_control, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_flag(ui->main_page_pc_control, LV_OBJ_FLAG_HIDDEN);

	//init a new style.
	lv_style_t *frameStyle = (lv_style_t *)malloc(sizeof(lv_style_t));
    lv_style_init(frameStyle);
	lv_style_set_border_width(frameStyle, 1);
	lv_style_set_border_opa(frameStyle, LV_OPA_COVER);
	lv_style_set_border_color(frameStyle, MAIN_FONT_COLOR);
	lv_style_set_border_side(frameStyle, LV_BORDER_SIDE_FULL);
	lv_style_set_radius(frameStyle, 0);
	lv_style_set_text_color(frameStyle, MAIN_FONT_COLOR);
	lv_style_set_text_font(frameStyle, &lv_font_montserratMedium_16);
	lv_style_set_text_opa(frameStyle, LV_OPA_COVER);
	lv_style_set_text_letter_space(frameStyle, 0);
	lv_style_set_text_line_space(frameStyle, 0);
	lv_style_set_text_align(frameStyle, LV_TEXT_ALIGN_CENTER);
	lv_style_set_bg_opa(frameStyle, LV_OPA_TRANSP);
	lv_style_set_bg_color(frameStyle, DESIGNATED_COLOR_BLUE);
	lv_style_set_bg_grad_dir(frameStyle, LV_GRAD_DIR_NONE);
	lv_style_set_pad_top(frameStyle, 2);
	lv_style_set_pad_right(frameStyle, 0);
	lv_style_set_pad_bottom(frameStyle, 1);
	lv_style_set_pad_left(frameStyle, 0);
	lv_style_set_shadow_width(frameStyle, 0);

	for (int i = 0; i < AM_WORK_MODE_GROUP_NUM; i++)
    {
		//Write codes ui->main_page_work_mode
    	ui->main_page_work_mode[i] = lv_label_create(ui->main_page);
		lv_label_set_text(ui->main_page_work_mode[i], "MATRIX");
    	lv_obj_set_pos(ui->main_page_work_mode[i], MAIN_PAGE_WORKMODE_X + (MAIN_PAGE_WORKMODE_WIDTH+3)*i, MAIN_PAGE_WORKMODE_Y);
    	lv_label_set_long_mode(ui->main_page_work_mode[i], LV_LABEL_LONG_WRAP);
    	lv_obj_set_size(ui->main_page_work_mode[i], MAIN_PAGE_WORKMODE_WIDTH, MAIN_PAGE_WORKMODE_HEIGHT);
    	lv_obj_add_style(ui->main_page_work_mode[i], frameStyle, LV_PART_MAIN);
		lv_obj_set_style_bg_opa(ui->main_page_work_mode[i], 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    }

	//Write codes main_page_vu_page[0]
	ui->main_page_vu_page[0] = lv_obj_create(ui->main_page);
	lv_obj_set_size(ui->main_page_vu_page[0], MAIN_PAGE_VU_PAGE_WIDTH, MAIN_PAGE_VU_PAGE_HEIGHT);
	lv_obj_set_pos(ui->main_page_vu_page[0], MAIN_PAGE_VU_PAGE_X, MAIN_PAGE_VU_PAGE_Y);
	lv_obj_set_scrollbar_mode(ui->main_page_vu_page[0], LV_SCROLLBAR_MODE_OFF);
	lv_obj_set_style_pad_all(ui->main_page_vu_page[0], 0, 0);

	//Write style for main_page_vu_page[0], Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->main_page_vu_page[0], LV_OPA_TRANSP, LV_PART_MAIN|LV_STATE_DEFAULT);
	//lv_obj_set_style_bg_grad_dir(ui->main_page_vu_page[0], LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->main_page_vu_page[0], 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->main_page_vu_page[0], 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	for (int i = 0; i < LAYOUT_INPUT_SIZE; i++) {
		//Write codes ui->main_page_clip_in_sens
		ui->main_page_clip_in_sens[i] = lv_label_create(ui->main_page_vu_page[0]);
		lv_obj_set_style_text_align(ui->main_page_clip_in_sens[i], LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_add_style(ui->main_page_clip_in_sens[i], frameStyle, LV_PART_MAIN);
		lv_label_set_long_mode(ui->main_page_clip_in_sens[i], LV_LABEL_LONG_WRAP);
		lv_obj_set_size(ui->main_page_clip_in_sens[i], MAIN_PAGE_CLIP_SENS_WIDTH, MAIN_PAGE_VU_CHN_HEIGHT);
		lv_obj_set_style_pad_bottom(ui->main_page_clip_in_sens[i], 1, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_align(ui->main_page_clip_in_sens[i], LV_ALIGN_DEFAULT, MAIN_PAGE_CLIP_SENS_X, 1 + MAIN_PAGE_VU_CHN_Y_SPAN * i);
		lv_label_set_text(ui->main_page_clip_in_sens[i], "0dBu");
		
		//Write codes ui->main_page_in_channel_mute
		ui->main_page_in_channel_mute[i] = lv_label_create(ui->main_page_vu_page[0]);
		lv_obj_set_style_text_align(ui->main_page_in_channel_mute[i], LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_add_style(ui->main_page_in_channel_mute[i], frameStyle, LV_PART_MAIN);
		lv_label_set_long_mode(ui->main_page_in_channel_mute[i], LV_LABEL_LONG_WRAP);
		lv_obj_set_size(ui->main_page_in_channel_mute[i], MAIN_PAGE_CH_MUTE_WIDTH, MAIN_PAGE_CH_MUTE_WIDTH);
		lv_obj_set_style_pad_bottom(ui->main_page_in_channel_mute[i], 1, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_align_to(ui->main_page_in_channel_mute[i], ui->main_page_clip_in_sens[i], LV_ALIGN_OUT_RIGHT_TOP, 1, 0);
		lv_obj_set_style_text_font(ui->main_page_in_channel_mute[i], &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_label_set_text(ui->main_page_in_channel_mute[i], "A");

		//Write codes ui->main_page_in_volume_unit_line
		ui->main_page_in_volume_unit_line[i] = lv_obj_create(ui->main_page_vu_page[0]);
		lv_obj_add_style(ui->main_page_in_volume_unit_line[i], frameStyle, LV_PART_MAIN);
		lv_obj_set_size(ui->main_page_in_volume_unit_line[i], MAIN_PAGE_CH_VU_WIDTH, MAIN_PAGE_VU_CHN_HEIGHT);
		lv_obj_align_to(ui->main_page_in_volume_unit_line[i], ui->main_page_in_channel_mute[i], LV_ALIGN_OUT_RIGHT_TOP, 1, 0);

		//Write codes ui->main_page_in_volume_unit
		ui->main_page_in_volume_unit[i] = lv_img_create(ui->main_page_vu_page[0]);
		lv_img_set_src(ui->main_page_in_volume_unit[i], &vu_dark);
		lv_obj_set_size(ui->main_page_in_volume_unit[i], MAIN_PAGE_CH_VU_IMG_WIDTH, MAIN_PAGE_CH_VU_IMG_HEIGHT);
		lv_obj_align_to(ui->main_page_in_volume_unit[i], ui->main_page_in_volume_unit_line[i], LV_ALIGN_LEFT_MID, 1, 0);

		/* hide vu light now */
		/*
		ui->main_page_in_volume_unit[i] = lv_img_create(ui->main_page_vu_page[0]);
		lv_img_set_src(ui->main_page_in_volume_unit[i], &vu_light);
		lv_obj_set_size(ui->main_page_in_volume_unit[i], MAIN_PAGE_CH_VU_IMG_WIDTH, MAIN_PAGE_CH_VU_IMG_HEIGHT);
		lv_obj_align_to(ui->main_page_in_volume_unit[i], ui->main_page_in_volume_unit_line[i], LV_ALIGN_LEFT_MID, 1, 0);
		*/

		//Write codes ui->main_page_in_gain_limit
		ui->main_page_in_gain_limit[i] = lv_label_create(ui->main_page_vu_page[0]);
		lv_obj_set_size(ui->main_page_in_gain_limit[i], MAIN_PAGE_GAIN_LIMIT_WIDTH, MAIN_PAGE_VU_CHN_HEIGHT);
		lv_obj_add_style(ui->main_page_in_gain_limit[i], frameStyle, LV_PART_MAIN);
		lv_obj_set_style_pad_right(ui->main_page_in_gain_limit[i], 2, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_align_to(ui->main_page_in_gain_limit[i], ui->main_page_in_volume_unit_line[i], LV_ALIGN_OUT_RIGHT_TOP, 1, 0);
		lv_obj_set_style_text_font(ui->main_page_in_gain_limit[i], &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_label_set_text(ui->main_page_in_gain_limit[i], "-41.0");
	}
	// this operation will hide in_vu_page
	lv_obj_add_flag(ui->main_page_vu_page[0], LV_OBJ_FLAG_HIDDEN);

	//Write codes main_page_vu_page[1]
	ui->main_page_vu_page[1] = lv_obj_create(ui->main_page);
	lv_obj_set_size(ui->main_page_vu_page[1], MAIN_PAGE_VU_PAGE_WIDTH, MAIN_PAGE_VU_PAGE_HEIGHT);
	lv_obj_set_pos(ui->main_page_vu_page[1], MAIN_PAGE_VU_PAGE_X, MAIN_PAGE_VU_PAGE_Y);
	lv_obj_set_scrollbar_mode(ui->main_page_vu_page[1], LV_SCROLLBAR_MODE_OFF);
	lv_obj_set_style_pad_all(ui->main_page_vu_page[1], 0, 0);

	//Write style for main_page_vu_page[1], Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->main_page_vu_page[1], LV_OPA_TRANSP, LV_PART_MAIN|LV_STATE_DEFAULT);
	//lv_obj_set_style_bg_grad_dir(ui->main_page_vu_page[1], LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->main_page_vu_page[1], 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->main_page_vu_page[1], 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	for (int i = 0; i < LAYOUT_OUTPUT_SIZE; i++) {
		//Write codes ui->main_page_clip_out_sens
		ui->main_page_clip_out_sens[i] = lv_label_create(ui->main_page_vu_page[1]);
		lv_obj_set_style_text_align(ui->main_page_clip_out_sens[i], LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_add_style(ui->main_page_clip_out_sens[i], frameStyle, LV_PART_MAIN);
		lv_label_set_long_mode(ui->main_page_clip_out_sens[i], LV_LABEL_LONG_WRAP);
		lv_obj_set_size(ui->main_page_clip_out_sens[i], MAIN_PAGE_CLIP_SENS_WIDTH, MAIN_PAGE_VU_CHN_HEIGHT);
		lv_obj_set_style_pad_bottom(ui->main_page_clip_out_sens[i], 1, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_align(ui->main_page_clip_out_sens[i], LV_ALIGN_DEFAULT, MAIN_PAGE_CLIP_SENS_X, 1 + MAIN_PAGE_VU_CHN_Y_SPAN * i);
		lv_label_set_text(ui->main_page_clip_out_sens[i], "M");
		
		//Write codes ui->main_page_out_channel_mute
		ui->main_page_out_channel_mute[i] = lv_label_create(ui->main_page_vu_page[1]);
		lv_obj_set_style_text_align(ui->main_page_out_channel_mute[i], LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_add_style(ui->main_page_out_channel_mute[i], frameStyle, LV_PART_MAIN);
		lv_label_set_long_mode(ui->main_page_out_channel_mute[i], LV_LABEL_LONG_WRAP);
		lv_obj_set_size(ui->main_page_out_channel_mute[i], MAIN_PAGE_CH_MUTE_WIDTH, MAIN_PAGE_CH_MUTE_WIDTH);
		lv_obj_set_style_pad_bottom(ui->main_page_out_channel_mute[i], 1, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_align_to(ui->main_page_out_channel_mute[i], ui->main_page_clip_out_sens[i], LV_ALIGN_OUT_RIGHT_TOP, 1, 0);
		lv_obj_set_style_text_font(ui->main_page_out_channel_mute[i], &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_label_set_text(ui->main_page_out_channel_mute[i], "1");

		//Write codes ui->main_page_out_volume_unit_line
		ui->main_page_out_volume_unit_line[i] = lv_obj_create(ui->main_page_vu_page[1]);
		lv_obj_add_style(ui->main_page_out_volume_unit_line[i], frameStyle, LV_PART_MAIN);
		lv_obj_set_size(ui->main_page_out_volume_unit_line[i], MAIN_PAGE_CH_VU_WIDTH, MAIN_PAGE_VU_CHN_HEIGHT);
		lv_obj_align_to(ui->main_page_out_volume_unit_line[i], ui->main_page_out_channel_mute[i], LV_ALIGN_OUT_RIGHT_TOP, 1, 0);

		//Write codes ui->main_page_out_volume_unit
		ui->main_page_out_volume_unit[i] = lv_img_create(ui->main_page_vu_page[1]);
		lv_img_set_src(ui->main_page_out_volume_unit[i], &vu_dark);
		lv_obj_set_size(ui->main_page_out_volume_unit[i], MAIN_PAGE_CH_VU_IMG_WIDTH, MAIN_PAGE_CH_VU_IMG_HEIGHT);
		lv_obj_align_to(ui->main_page_out_volume_unit[i], ui->main_page_out_volume_unit_line[i], LV_ALIGN_LEFT_MID, 1, 0);

		/* hide vu light now */
		/*
		ui->main_page_out_volume_unit[i] = lv_img_create(ui->main_page_vu_page[1]);
		lv_img_set_src(ui->main_page_out_volume_unit[i], &vu_light);
		lv_obj_set_size(ui->main_page_out_volume_unit[i], MAIN_PAGE_CH_VU_IMG_WIDTH, MAIN_PAGE_CH_VU_IMG_HEIGHT);
		lv_obj_align_to(ui->main_page_out_volume_unit[i], ui->main_page_out_volume_unit_line[i], LV_ALIGN_LEFT_MID, 1, 0);
		*/

		//Write codes ui->main_page_out_gain_limit
		ui->main_page_out_gain_limit[i] = lv_label_create(ui->main_page_vu_page[1]);
		lv_obj_set_size(ui->main_page_out_gain_limit[i], MAIN_PAGE_GAIN_LIMIT_WIDTH, MAIN_PAGE_VU_CHN_HEIGHT);
		lv_obj_add_style(ui->main_page_out_gain_limit[i], frameStyle, LV_PART_MAIN);
		lv_obj_set_style_pad_right(ui->main_page_out_gain_limit[i], 2, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_align_to(ui->main_page_out_gain_limit[i], ui->main_page_out_volume_unit_line[i], LV_ALIGN_OUT_RIGHT_TOP, 1, 0);
		lv_obj_set_style_text_font(ui->main_page_out_gain_limit[i], &lv_font_montserratMedium_20, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_label_set_text(ui->main_page_out_gain_limit[i], "-60.0");
	}
	// this operation will hide out_vu_page
	// lv_obj_add_flag(ui->main_page_vu_page[1], LV_OBJ_FLAG_HIDDEN);

	/*TEST button !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
	ui->main_page_btn_test = lv_btn_create(ui->main_page);
	ui->main_page_btn_test_label = lv_label_create(ui->main_page_btn_test);
	lv_label_set_text(ui->main_page_btn_test_label, "test");
	lv_label_set_long_mode(ui->main_page_btn_test_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->main_page_btn_test_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->main_page_btn_test, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->main_page_btn_test, 278, 85);
	lv_obj_set_size(ui->main_page_btn_test, 35, 26);

	lv_obj_set_style_bg_opa(ui->main_page_btn_test, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->main_page_btn_test, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->main_page_btn_test, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->main_page_btn_test, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->main_page_btn_test, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->main_page_btn_test, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->main_page_btn_test, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->main_page_btn_test, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->main_page_btn_test, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->main_page_btn_test, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->main_page);

	//Init events for screen.
	events_init_main_page(ui);
}