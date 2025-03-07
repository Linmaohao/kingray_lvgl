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

void events_init(lv_ui *ui)
{
	events_init_load_page(ui);
}

// 通用按键处理
void CommonCallback(int key_value)
{
//  Am_Gain_Base_t amGain;
//  uint8_t doSet = 1;
  
//   Channel_Detail_t chDetail;
//   chDetail.channel.chDiff = CH_IN;
//   chDetail.channel.detailNo = CHN_NONE;
  
  switch(key_value)
  {
    case CUSTOM_KEY_MUTE_A:
    //   chDetail.channel.chNo = IN_CHA;
    //   g_WndCtrl.chMute[0] = (g_WndCtrl.chMute[0] == AM_GAIN_MUTE_STATE_MUTE) ? AM_GAIN_MUTE_STATE_UNMUTE : AM_GAIN_MUTE_STATE_MUTE;
    //   GainMuteCtrl(&chDetail, g_WndCtrl.chMute[0], NULL);
		break;
    case CUSTOM_KEY_MUTE_B:
    //   chDetail.channel.chNo = IN_CHB;
    //   g_WndCtrl.chMute[1] = (g_WndCtrl.chMute[1] == AM_GAIN_MUTE_STATE_MUTE) ? AM_GAIN_MUTE_STATE_UNMUTE : AM_GAIN_MUTE_STATE_MUTE;
    //   GainMuteCtrl(&chDetail, g_WndCtrl.chMute[1], NULL);
		break;
    case CUSTOM_KEY_MUTE_C:
    //   chDetail.channel.chNo = IN_CHC;
    //   g_WndCtrl.chMute[2] = (g_WndCtrl.chMute[2] == AM_GAIN_MUTE_STATE_MUTE) ? AM_GAIN_MUTE_STATE_UNMUTE : AM_GAIN_MUTE_STATE_MUTE;
    //   GainMuteCtrl(&chDetail, g_WndCtrl.chMute[2], NULL);
		break;
    case CUSTOM_KEY_MUTE_D:
    //   chDetail.channel.chNo = IN_CHD;
    //   g_WndCtrl.chMute[3] = (g_WndCtrl.chMute[3] == AM_GAIN_MUTE_STATE_MUTE) ? AM_GAIN_MUTE_STATE_UNMUTE : AM_GAIN_MUTE_STATE_MUTE;
    //   GainMuteCtrl(&chDetail, g_WndCtrl.chMute[3], NULL);
		break;
    case CUSTOM_KEY_STANDBY:
    {
    //   uint8_t ampStatus = AmpWorkStatusGet();
    //   DBG_Printf("key amp status: %d", ampStatus);
    //   AmpWorkStatusSet(!ampStatus);
		// 此处做待机的处理
		ui_load_scr_animation(&guider_ui, &guider_ui.standby_page, guider_ui.standby_page_del, &guider_ui.main_page_del, setup_scr_standby_page, LV_SCR_LOAD_ANIM_NONE, 5, 5, true, true);

		break;
    }
  }
}