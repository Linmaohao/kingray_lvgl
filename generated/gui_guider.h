/*
* Copyright 2024 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

#define AM_WORK_MODE_GROUP_NUM			2
#define LAYOUT_INPUT_SIZE				4
#define LAYOUT_OUTPUT_SIZE				4
#define LAYOUT_TOTAL_CHN_SIZE			(LAYOUT_INPUT_SIZE + LAYOUT_OUTPUT_SIZE)
#define CHANNEL_SIZE					4
#define BACKGROUND_COLOR				lv_color_hex(0x000000)
#define MAIN_FONT_COLOR					lv_color_hex(0xffffff)
#define DESIGNATED_COLOR_BLUE			lv_color_hex(0x192fb4)
#define RENAME_DISPLAY_NAME_LEN			8

extern const uint8_t in_channel_label[][8];
extern const uint8_t out_channel_label[][8];
extern lv_indev_t * indev_keypad;
extern lv_indev_t * indev_encoder;

typedef enum
{
  MENU_E_VOLUME,
  MENU_E_PRESET,
  MENU_E_SOURCE,
  MENU_E_STATUS,
  MENU_E_RENAME,
  MENU_E_IPSET,
  MENU_E_LOCK,
  MENU_E_INFO,
  MENU_E_SCREEN,
  
  MENU_E_NUM,
}MENU_E;


// Expose all elements here
typedef struct
{
	lv_obj_t *load_page;
	lv_obj_t *load_page_bar_load;
	lv_obj_t *load_page_label_load;
	bool load_page_del;

	lv_obj_t *main_page;
	lv_obj_t *main_page_title;
	lv_obj_t *main_page_device_name;
	lv_obj_t *main_page_preset_name;
	lv_obj_t *main_page_lock;
	lv_obj_t *main_page_temperature;
	lv_obj_t *main_page_volume;
	lv_obj_t *main_page_pc_control;
	lv_obj_t *main_page_work_mode[AM_WORK_MODE_GROUP_NUM];
	// in_vu_page and out_vu_page
	lv_obj_t *main_page_vu_page[2];
	lv_obj_t *main_page_clip_in_sens[LAYOUT_INPUT_SIZE];
	lv_obj_t *main_page_in_channel_mute[LAYOUT_INPUT_SIZE];
	lv_obj_t *main_page_in_volume_unit[LAYOUT_INPUT_SIZE];
	lv_obj_t *main_page_in_volume_unit_line[LAYOUT_INPUT_SIZE];
	lv_obj_t *main_page_in_gain_limit[LAYOUT_INPUT_SIZE];
	lv_obj_t *main_page_clip_out_sens[LAYOUT_OUTPUT_SIZE];
	lv_obj_t *main_page_out_channel_mute[LAYOUT_OUTPUT_SIZE];
	lv_obj_t *main_page_out_volume_unit[LAYOUT_OUTPUT_SIZE];
	lv_obj_t *main_page_out_volume_unit_line[LAYOUT_OUTPUT_SIZE];
	lv_obj_t *main_page_out_gain_limit[LAYOUT_OUTPUT_SIZE];

	// lv_obj_t *main_page_btn_test;
	// lv_obj_t *main_page_btn_test_label;
	lv_group_t *main_page_group;
	bool main_page_del;

	lv_obj_t *standby_page;
	lv_obj_t *standby_page_img_standby;
	bool standby_page_del;

	lv_obj_t *menu_page;
	lv_obj_t *menu_page_title;
	lv_obj_t *menu_page_list_page;
	lv_obj_t *menu_page_item_container[MENU_E_NUM];
	lv_obj_t *menu_page_item_number[MENU_E_NUM];
	lv_obj_t *menu_page_item_content[MENU_E_NUM];
	lv_obj_t *menu_page_lock;
	lv_obj_t *menu_page_message_box;
	lv_group_t *menu_page_group;
	lv_group_t *menu_page_message_group;
	bool menu_page_del;

	lv_obj_t *volume_page;
	lv_obj_t *volume_page_title;
	lv_obj_t *volume_page_list_page;
	lv_obj_t *volume_page_channel_name[LAYOUT_TOTAL_CHN_SIZE];
	lv_obj_t *volume_page_mute_btn[LAYOUT_TOTAL_CHN_SIZE];
	lv_obj_t *volume_page_mute_label[LAYOUT_TOTAL_CHN_SIZE];
	lv_obj_t *volume_page_gain[LAYOUT_TOTAL_CHN_SIZE];
	lv_obj_t *volume_page_gain_label[LAYOUT_TOTAL_CHN_SIZE];
	lv_group_t *volume_page_group;
	bool volume_page_del;

	lv_obj_t *preset_page;
	lv_obj_t *preset_page_title;
	lv_obj_t *preset_page_list_page;
	lv_obj_t **preset_page_preset;
	lv_group_t *preset_page_group;
	bool preset_page_del;

	lv_obj_t *source_page;
	lv_obj_t *source_page_title;
	lv_obj_t *source_page_in_channel[LAYOUT_INPUT_SIZE];
	lv_obj_t *source_page_source[LAYOUT_INPUT_SIZE];
	lv_obj_t *source_page_sens[LAYOUT_INPUT_SIZE];
	lv_group_t *source_page_group;
	bool source_page_del;

	lv_obj_t *status_page;
	lv_obj_t *status_page_title;
	lv_obj_t *status_page_tips[4];
	lv_obj_t *status_page_tips_description[4];
	lv_obj_t *status_page_work_mode_page;
	lv_obj_t *status_page_btn_router[LAYOUT_OUTPUT_SIZE][LAYOUT_INPUT_SIZE];
	lv_obj_t *status_page_btn_label[LAYOUT_OUTPUT_SIZE][LAYOUT_INPUT_SIZE];
	lv_obj_t *status_page_channel_name[CHANNEL_SIZE];
	lv_obj_t *status_page_channel_out_line[CHANNEL_SIZE];
	lv_obj_t *status_page_channel_in_line[CHANNEL_SIZE];
	lv_obj_t *status_page_poly_line[CHANNEL_SIZE/2];
	lv_obj_t *status_page_work_mode_select[CHANNEL_SIZE/2];
	lv_obj_t *status_page_speaker[CHANNEL_SIZE/2];
	lv_group_t *status_page_group;
	bool status_page_del;

	lv_obj_t *rename_page;
	lv_obj_t *rename_page_title;
	lv_obj_t *rename_page_name[RENAME_DISPLAY_NAME_LEN];
	lv_group_t *rename_page_group;
	bool rename_page_del;

	lv_obj_t *ipset_page;
	lv_obj_t *ipset_page_title;
	lv_obj_t *ipset_page_ip_topic;
	lv_obj_t *ipset_page_ip[4];
	lv_obj_t *ipset_page_gw_topic;
	lv_obj_t *ipset_page_gw[4];
	lv_obj_t *ipset_page_mac;
	lv_obj_t *ipset_page_ensure_btn;
	lv_obj_t *ipset_page_ensure_label;
	lv_group_t *ipset_page_group;
	bool ipset_page_del;

	lv_obj_t *info_page;
	lv_obj_t *info_page_title;
	lv_obj_t *info_page_message_page;
	lv_obj_t *info_page_factory_topic;
	lv_obj_t *info_page_software_version;
	lv_obj_t *info_page_hardware_version;
	bool info_page_del;

	lv_obj_t *screen_page;
	lv_obj_t *screen_page_title;
	lv_obj_t *screen_page_backlight;
	lv_obj_t *screen_page_backlight_switch;
	lv_obj_t *screen_page_backlight_time_topic;
	lv_obj_t *screen_page_backlight_time;
	lv_obj_t *screen_page_backlight_time_unit;
	lv_group_t *screen_page_group;
	bool screen_page_del;
}lv_ui;

typedef void (*ui_setup_scr_t)(lv_ui * ui);

void ui_init_style(lv_style_t * style);

void ui_load_scr_animation(lv_ui *ui, lv_obj_t ** new_scr, bool new_scr_del, bool * old_scr_del, ui_setup_scr_t setup_scr,
                           lv_scr_load_anim_t anim_type, uint32_t time, uint32_t delay, bool is_clean, bool auto_del);

void ui_move_animation(void * var, int32_t duration, int32_t delay, int32_t x_end, int32_t y_end, lv_anim_path_cb_t path_cb,
                       uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                       lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);

void ui_scale_animation(void * var, int32_t duration, int32_t delay, int32_t width, int32_t height, lv_anim_path_cb_t path_cb,
                        uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                        lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);

void ui_img_zoom_animation(void * var, int32_t duration, int32_t delay, int32_t zoom, lv_anim_path_cb_t path_cb,
                           uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time, uint32_t playback_delay,
                           lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);

void ui_img_rotate_animation(void * var, int32_t duration, int32_t delay, lv_coord_t x, lv_coord_t y, int32_t rotate,
                   lv_anim_path_cb_t path_cb, uint16_t repeat_cnt, uint32_t repeat_delay, uint32_t playback_time,
                   uint32_t playback_delay, lv_anim_start_cb_t start_cb, lv_anim_ready_cb_t ready_cb, lv_anim_deleted_cb_t deleted_cb);

void init_scr_del_flag(lv_ui *ui);

void setup_ui(lv_ui *ui);


extern lv_ui guider_ui;

void setup_scr_load_page(lv_ui *ui);
void setup_scr_main_page(lv_ui *ui);
void setup_scr_standby_page(lv_ui *ui);
void setup_scr_menu_page(lv_ui *ui);
void setup_scr_volume_page(lv_ui *ui);
void setup_scr_preset_page(lv_ui *ui);
void setup_scr_source_page(lv_ui *ui);
void setup_scr_status_page(lv_ui *ui);
void setup_scr_rename_page(lv_ui *ui);
void setup_scr_ipset_page(lv_ui *ui);
void setup_scr_info_page(lv_ui *ui);
void setup_scr_screen_page(lv_ui *ui);


void set_channel_name_style(lv_obj_t* obj);

LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_montserratMedium_20)
LV_FONT_DECLARE(lv_font_iconfont_20)
LV_FONT_DECLARE(lv_font_montserratMedium_14)
LV_FONT_DECLARE(lv_font_montserratMedium_18)
LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_montserratMedium_24)
LV_FONT_DECLARE(lv_font_montserratMedium_22)
LV_FONT_DECLARE(lv_font_montserratMedium_8)
LV_FONT_DECLARE(lv_front_source_fzltxh_20)

#ifdef __cplusplus
}
#endif
#endif
