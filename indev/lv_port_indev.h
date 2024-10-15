
/**
 * @file lv_port_indev_templ.h
 *
 */

/*Copy this file as "lv_port_indev.h" and set this value to "1" to enable content*/
#if 1

#ifndef LV_PORT_INDEV_H
#define LV_PORT_INDEV_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lvgl/lvgl.h"

/*********************
 *      DEFINES
 *********************/
#define CUSTOM_KEY_MUTE_A       32  /*0x20*/
#define CUSTOM_KEY_MUTE_B       33  /*0x21*/
#define CUSTOM_KEY_MUTE_C       34  /*0x22*/
#define CUSTOM_KEY_MUTE_D       35  /*0x23*/
#define CUSTOM_KEY_STANDBY      36  /*0x24*/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/
void lv_port_indev_init(void);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LV_PORT_INDEV_H*/

#endif /*Disable/Enable content*/
