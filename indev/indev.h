#ifndef INDEV_H
#define INDEV_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
//#include "lvgl/lvgl.h"

/*********************
 *      DEFINES
 *********************/

#define PIN_74HC176_CLK         129 /*GPIO4 PA1*/
#define PIN_74HC176_QH          130 /*GPIO4 PA2*/
#define PIN_74HC176_SH          141 /*GPIO4 PB5*/

typedef enum{
    ENCODER_STATUS_ENTER = 0,
    ENCODER_STATUS_RIGHT,
    ENCODER_STATUS_LEFT,
//    ENCODER_CONTINUE_ERAD,

    KEY_STATUS_STANDBY,
    KEY_STATUS_MUTE_A,
    KEY_STATUS_MUTE_B,
    KEY_STATUS_MUTE_C,
    KEY_STATUS_MUTE_D,
    KEY_STATUS_ESC,
    KEY_STATUS_NOTHING = 254,
//    NO_VALUE_CHANGE = 255,
} operate_status_t;

/**********************
 * GLOBAL PROTOTYPES
 **********************/
operate_status_t indev_scan_key(void);
operate_status_t indev_scan_encoder(void);
void indev_init(void);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*INDEV_H*/