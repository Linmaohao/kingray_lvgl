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

#define PRESET_PAGE_TITLE				"PRESET"

#define IPSET_IP_LBL_X					30
#define IPSET_IP_LBL_Y					100
#define IPSET_IP_LBL_WIDTH				48
#define IPSET_IP_LBL_HEIGHT				24

#define IPSET_IP_X						86
#define IPSET_IP_Y						98
#define IPSET_IP_WIDTH					40
#define IPSET_IP_HEIGHT					22
#define IPSET_IP_X_SPAN					60
#define IPSET_IP_Y_SPAN					26

#define IPSET_ENSURE_X					250
#define IPSET_ENSURE_Y					200
#define IPSET_ENSURE_WIDTH				60
#define IPSET_ENSURE_HEIGHT				30

#define IPSET_MAC_X						20
#define IPSET_MAC_Y						215
#define IPSET_MAC_WIDTH					220
#define IPSET_MAC_HEIGHT				30

const uint8_t ip_ption[] = 
{
  "  0\n" "  1\n" "  2\n" "  3\n" "  4\n" "  5\n" "  6\n" "  7\n" "  8\n" "  9\n" " 10\n" " 11\n" " 12\n" " 13\n" " 14\n" " 15\n" " 16\n" " 17\n" " 18\n" " 19\n" " 20\n" " 21\n" " 22\n" " 23\n" " 24\n" " 25\n" " 26\n" " 27\n" " 28\n" " 29\n" " 30\n" " 31\n" " 32\n" " 33\n" " 34\n" " 35\n" " 36\n" " 37\n" " 38\n" " 39\n" 

  " 40\n" " 41\n" " 42\n" " 43\n" " 44\n" " 45\n" " 46\n" " 47\n" " 48\n" " 49\n" " 50\n" " 51\n" " 52\n" " 53\n" " 54\n" " 55\n" " 56\n" " 57\n" " 58\n" " 59\n" " 60\n" " 61\n" " 62\n" " 63\n" " 64\n" " 65\n" " 66\n" " 67\n" " 68\n" " 69\n" " 70\n" " 71\n" " 72\n" " 73\n" " 74\n" " 75\n" " 76\n" " 77\n" " 78\n" " 79\n" 

  " 80\n" " 81\n" " 82\n" " 83\n" " 84\n" " 85\n" " 86\n" " 87\n" " 88\n" " 89\n" " 90\n" " 91\n" " 92\n" " 93\n" " 94\n" " 95\n" " 96\n" " 97\n" " 98\n" " 99\n" "100\n" "101\n" "102\n" "103\n" "104\n" "105\n" "106\n" "107\n" "108\n" "109\n" "110\n" "111\n" "112\n" "113\n" "114\n" "115\n" "116\n" "117\n" "118\n" "119\n" 

  "120\n" "121\n" "122\n" "123\n" "124\n" "125\n" "126\n" "127\n" "128\n" "129\n" "130\n" "131\n" "132\n" "133\n" "134\n" "135\n" "136\n" "137\n" "138\n" "139\n" "140\n" "141\n" "142\n" "143\n" "144\n" "145\n" "146\n" "147\n" "148\n" "149\n" "150\n" "151\n" "152\n" "153\n" "154\n" "155\n" "156\n" "157\n" "158\n" "159\n" 

  "160\n" "161\n" "162\n" "163\n" "164\n" "165\n" "166\n" "167\n" "168\n" "169\n" "170\n" "171\n" "172\n" "173\n" "174\n" "175\n" "176\n" "177\n" "178\n" "179\n" "180\n" "181\n" "182\n" "183\n" "184\n" "185\n" "186\n" "187\n" "188\n" "189\n" "190\n" "191\n" "192\n" "193\n" "194\n" "195\n" "196\n" "197\n" "198\n" "199\n" 

  "200\n" "201\n" "202\n" "203\n" "204\n" "205\n" "206\n" "207\n" "208\n" "209\n" "210\n" "211\n" "212\n" "213\n" "214\n" "215\n" "216\n" "217\n" "218\n" "219\n" "220\n" "221\n" "222\n" "223\n" "224\n" "225\n" "226\n" "227\n" "228\n" "229\n" "230\n" "231\n" "232\n" "233\n" "234\n" "235\n" "236\n" "237\n" "238\n" "239\n" 

  "240\n" "241\n" "242\n" "243\n" "244\n" "245\n" "246\n" "247\n" "248\n" "249\n" "250\n" "251\n" "252\n" "253\n" "254\n" "255" 
};

void setup_scr_ipset_page(lv_ui *ui)
{
	//Write codes ipset_page
	ui->ipset_page = lv_obj_create(NULL);
	lv_obj_set_size(ui->ipset_page, LV_HOR_RES_MAX, LV_VER_RES_MAX);
	lv_obj_set_scrollbar_mode(ui->ipset_page, LV_SCROLLBAR_MODE_OFF);

	//Write style for ipset_page, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->ipset_page, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->ipset_page, BACKGROUND_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->ipset_page, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes ipset_page_title
	ui->ipset_page_title = lv_label_create(ui->ipset_page);
	lv_label_set_long_mode(ui->ipset_page_title, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ipset_page_title, 0, 0);
    lv_obj_set_size(ui->ipset_page_title, LV_HOR_RES_MAX, TITLE_HEIGHT);

	//Write style for ui->ipset_page_title, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->ipset_page_title, MAIN_FONT_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->ipset_page_title, &lv_font_montserratMedium_24, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_opa(ui->ipset_page_title, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->ipset_page_title, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->ipset_page_title, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->ipset_page_title, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->ipset_page_title, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->ipset_page_title, DESIGNATED_COLOR_BLUE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->ipset_page_title, 6, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_label_set_text(ui->ipset_page_title, PRESET_PAGE_TITLE);

	//Init a new style for topic
	lv_style_t *main_style = (lv_style_t *)malloc(sizeof(lv_style_t));
    lv_style_init(main_style);
	lv_style_set_border_width(main_style, 0);
	lv_style_set_text_color(main_style, MAIN_FONT_COLOR);
	lv_style_set_text_font(main_style, &lv_font_montserratMedium_18);
	lv_style_set_text_align(main_style, LV_TEXT_ALIGN_CENTER);
	lv_style_set_text_letter_space(main_style, 2);
	lv_style_set_bg_opa(main_style, LV_OPA_TRANSP);
	
	//Write codes ipset_page_ip_topic
	ui->ipset_page_ip_topic = lv_label_create(ui->ipset_page);
	lv_label_set_long_mode(ui->ipset_page_ip_topic, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ipset_page_ip_topic, IPSET_IP_LBL_X, IPSET_IP_LBL_Y);
    lv_obj_set_size(ui->ipset_page_ip_topic, IPSET_IP_LBL_WIDTH, IPSET_IP_LBL_HEIGHT);
	lv_label_set_text(ui->ipset_page_ip_topic, "IP:");

	//Write style for ipset_page_ip_topic
	lv_obj_add_style(ui->ipset_page_ip_topic, main_style, LV_PART_MAIN);

	//Write codes ipset_page_gw_topic
	ui->ipset_page_gw_topic = lv_label_create(ui->ipset_page);
	lv_label_set_long_mode(ui->ipset_page_gw_topic, LV_LABEL_LONG_WRAP);
	lv_obj_align_to(ui->ipset_page_gw_topic, ui->ipset_page_ip_topic, LV_ALIGN_OUT_BOTTOM_MID, -10, 10);
	lv_obj_set_size(ui->ipset_page_gw_topic, IPSET_IP_LBL_WIDTH, IPSET_IP_LBL_HEIGHT);
	lv_label_set_text(ui->ipset_page_gw_topic, "GW:");

	//Write style for ipset_page_gw_topic
	lv_obj_add_style(ui->ipset_page_gw_topic, main_style, LV_PART_MAIN);

	//Write codes ipset_page_group
	ui->ipset_page_group = lv_group_create();

    for (int i = 0; i < 4; i++)
    {
		//Write codes ipset_page_ip
		ui->ipset_page_ip[i] = lv_roller_create(ui->ipset_page);
		lv_obj_set_pos(ui->ipset_page_ip[i], IPSET_IP_X + IPSET_IP_X_SPAN * i, IPSET_IP_Y);
		lv_roller_set_visible_row_count(ui->ipset_page_ip[i], 1);
		lv_obj_set_size(ui->ipset_page_ip[i], IPSET_IP_WIDTH, IPSET_IP_HEIGHT);
		lv_roller_set_options(ui->ipset_page_ip[i], ip_ption, LV_ROLLER_MODE_NORMAL);

		//Write style for ipset_page_ip, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
		lv_obj_set_style_border_color(ui->ipset_page_ip[i], lv_color_white(), LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_border_width(ui->ipset_page_ip[i], 1, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_border_side(ui->ipset_page_ip[i], LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_text_letter_space(ui->ipset_page_ip[i], 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    	lv_obj_set_style_radius(ui->ipset_page_ip[i], 0, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_bg_color(ui->ipset_page_ip[i], BACKGROUND_COLOR, LV_PART_MAIN|LV_PART_SELECTED|LV_STATE_DEFAULT);

		//Write style for ipset_page_ip, Part: LV_PART_SELECTED, State: LV_STATE_FOCUSED.
		lv_obj_set_style_text_color(ui->ipset_page_ip[i], lv_color_black(), LV_PART_SELECTED|LV_STATE_FOCUSED);
		lv_obj_set_style_bg_color(ui->ipset_page_ip[i], lv_color_white(), LV_PART_SELECTED|LV_STATE_FOCUSED);

		//Write style for rename_page_name, Part: LV_PART_SELECTED, State: LV_STATE_FOCUSED|LV_STATE_EDITED.
		lv_obj_set_style_bg_color(ui->ipset_page_ip[i], lv_palette_main(LV_PALETTE_GREEN), LV_PART_SELECTED|(LV_STATE_FOCUSED|LV_STATE_EDITED));
		lv_obj_set_style_outline_opa(ui->ipset_page_ip[i], LV_OPA_TRANSP, LV_STATE_FOCUSED|LV_STATE_EDITED);
		
		lv_group_add_obj(ui->ipset_page_group, ui->ipset_page_ip[i]);

		//Write codes ipset_page_gw
		ui->ipset_page_gw[i] = lv_roller_create(ui->ipset_page);
    	lv_obj_align_to(ui->ipset_page_gw[i], ui->ipset_page_ip[i], LV_ALIGN_OUT_BOTTOM_LEFT, 0, 10);
		lv_roller_set_visible_row_count(ui->ipset_page_gw[i], 1);
		lv_obj_set_size(ui->ipset_page_gw[i], IPSET_IP_WIDTH, IPSET_IP_HEIGHT);
		lv_roller_set_options(ui->ipset_page_gw[i], ip_ption, LV_ROLLER_MODE_NORMAL);

		//Write style for ipset_page_gw
		lv_obj_set_style_border_color(ui->ipset_page_gw[i], lv_color_white(), LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_border_width(ui->ipset_page_gw[i], 1, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_border_side(ui->ipset_page_gw[i], LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_text_letter_space(ui->ipset_page_gw[i], 2, LV_PART_MAIN|LV_STATE_DEFAULT);
    	lv_obj_set_style_radius(ui->ipset_page_gw[i], 0, LV_PART_MAIN|LV_STATE_DEFAULT);
		lv_obj_set_style_bg_color(ui->ipset_page_gw[i], BACKGROUND_COLOR, LV_PART_MAIN|LV_PART_SELECTED|LV_STATE_DEFAULT);

		//Write style for ipset_page_gw, Part: LV_PART_SELECTED, State: LV_STATE_FOCUSED.
		lv_obj_set_style_text_color(ui->ipset_page_gw[i], lv_color_black(), LV_PART_SELECTED|LV_STATE_FOCUSED);
		lv_obj_set_style_bg_color(ui->ipset_page_gw[i], lv_color_white(), LV_PART_SELECTED|LV_STATE_FOCUSED);

		//Write style for rename_page_name, Part: LV_PART_SELECTED, State: LV_STATE_FOCUSED|LV_STATE_EDITED.
		lv_obj_set_style_bg_color(ui->ipset_page_gw[i], lv_palette_main(LV_PALETTE_GREEN), LV_PART_SELECTED|(LV_STATE_FOCUSED|LV_STATE_EDITED));
		lv_obj_set_style_outline_opa(ui->ipset_page_gw[i], LV_OPA_TRANSP, LV_STATE_FOCUSED|LV_STATE_EDITED);

		lv_group_add_obj(ui->ipset_page_group, ui->ipset_page_gw[i]);
    }

	//Write style for ipset_page_mac, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	ui->ipset_page_mac = lv_label_create(ui->ipset_page);
	lv_label_set_long_mode(ui->ipset_page_mac, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->ipset_page_mac, IPSET_MAC_X, IPSET_MAC_Y);
    lv_obj_set_size(ui->ipset_page_mac, IPSET_MAC_WIDTH, IPSET_MAC_HEIGHT);
	lv_label_set_text(ui->ipset_page_mac, "MAC: 38:26:34:25:39:05");
	lv_obj_add_style(ui->ipset_page_mac, main_style, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->ipset_page_mac, &lv_font_montserratMedium_14, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write code ipset_page_ensure
	ui->ipset_page_ensure_btn = lv_btn_create(ui->ipset_page);
	ui->ipset_page_ensure_label = lv_label_create(ui->ipset_page_ensure_btn);
	lv_label_set_text(ui->ipset_page_ensure_label, "OK");
	lv_label_set_long_mode(ui->ipset_page_ensure_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->ipset_page_ensure_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_pos(ui->ipset_page_ensure_btn, IPSET_ENSURE_X, IPSET_ENSURE_Y);
	lv_obj_set_size(ui->ipset_page_ensure_btn, IPSET_ENSURE_WIDTH, IPSET_ENSURE_HEIGHT);

	//Write style for ipset_page_ensure_btn, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->ipset_page_ensure_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->ipset_page_ensure_btn, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->ipset_page_ensure_btn, lv_color_white(), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->ipset_page_ensure_btn, IPSET_ENSURE_HEIGHT/2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->ipset_page_ensure_btn, MAIN_FONT_COLOR, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->ipset_page_ensure_btn, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->ipset_page_ensure_btn, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->ipset_page_ensure_btn, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for ipset_page_ensure_btn, Part: LV_PART_MAIN, State: LV_STATE_FOCUSED.
	lv_obj_set_style_bg_opa(ui->ipset_page_ensure_btn, 255, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_bg_color(ui->ipset_page_ensure_btn, lv_color_white(), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_border_color(ui->ipset_page_ensure_btn, DESIGNATED_COLOR_BLUE, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_text_color(ui->ipset_page_ensure_btn, lv_color_black(), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_outline_opa(ui->ipset_page_ensure_btn, LV_OPA_COVER, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_outline_color(ui->ipset_page_ensure_btn, lv_palette_lighten(LV_PALETTE_ORANGE, 1), LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_outline_pad(ui->ipset_page_ensure_btn, 2, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_set_style_outline_width(ui->ipset_page_ensure_btn, 3, LV_PART_MAIN|LV_STATE_FOCUSED);

	lv_group_add_obj(ui->ipset_page_group, ui->ipset_page_ensure_btn);

	lv_group_focus_obj(ui->ipset_page_ensure_btn);

	events_init_ipset_page(ui);

	//Update current screen layout.
	lv_obj_update_layout(ui->ipset_page);

}
