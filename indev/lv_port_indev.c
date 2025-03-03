/**
 * @file lv_port_indev_templ.c
 *
 */

/*Copy this file as "lv_port_indev.c" and set this value to "1" to enable content*/
#include <sys/types.h>
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_indev.h"
#include "indev.h"
#include "lvgl.h"
#include <stdio.h>

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

static void keypad_init(void);
static void keypad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);

static void encoder_init(void);
static void encoder_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data);
static void encoder_handler(void);

/**********************
 *  STATIC VARIABLES
 **********************/
lv_indev_t * indev_keypad;
lv_indev_t * indev_encoder;

static int32_t encoder_diff;
static lv_indev_state_t encoder_state;
// static u_int8_t continue_flag = 0;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_indev_init(void)
{
    /**
     * Here you will find example implementation of input devices supported by LittelvGL:
     *  - Keypad (supports GUI usage only with key)
     *  - Encoder (supports GUI usage only with: left, right, push)
     *
     *  The `..._read()` function are only examples.
     *  You should shape them according to your hardware
     */

    static lv_indev_drv_t indev_drv_keypad;
    static lv_indev_drv_t indev_drv_encoder;

    /*------------------
     * Keypad
     * -----------------*/

    /*Initialize your keypad or keyboard if you have*/
    keypad_init();

    /*Register a keypad input device*/
    lv_indev_drv_init(&indev_drv_keypad);
    indev_drv_keypad.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv_keypad.read_cb = keypad_read;
    indev_keypad = lv_indev_drv_register(&indev_drv_keypad);

    /*Later you should create group(s) with `lv_group_t * group = lv_group_create()`,
     *add objects to the group with `lv_group_add_obj(group, obj)`
     *and assign this input device to group to navigate in it:
     *`lv_indev_set_group(indev_keypad, group);`*/

    /*------------------
     * Encoder
     * -----------------*/

    /*Initialize your encoder if you have*/
    encoder_init();

    /*Register a encoder input device*/
    lv_indev_drv_init(&indev_drv_encoder);
    indev_drv_encoder.type = LV_INDEV_TYPE_ENCODER;
    indev_drv_encoder.read_cb = encoder_read;
    indev_encoder = lv_indev_drv_register(&indev_drv_encoder);

    /*Later you should create group(s) with `lv_group_t * group = lv_group_create()`,
     *add objects to the group with `lv_group_add_obj(group, obj)`
     *and assign this input device to group to navigate in it:
     *`lv_indev_set_group(indev_encoder, group);`*/
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*------------------
 * Keypad
 * -----------------*/

/*Initialize your keypad*/
static void keypad_init(void)
{
    /*Merge into encoder*/
}

/*Will be called by the library to read the keypad*/
static void keypad_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    static uint32_t last_key = 0;

    /*Get whether the a key is pressed and save the pressed key*/
    operate_status_t act_key = indev_scan_key();
    if(act_key != KEY_STATUS_NOTHING) {
        data->state = LV_INDEV_STATE_PR;

        /*Translate the keys to LVGL control characters according to your key definitions*/
        switch(act_key) {
            case KEY_STATUS_MUTE_A:
                act_key = CUSTOM_KEY_MUTE_A;
                break;
            case KEY_STATUS_MUTE_B:
                act_key = CUSTOM_KEY_MUTE_B;
                break;
            case KEY_STATUS_MUTE_C:
                act_key = CUSTOM_KEY_MUTE_C;
                break;
            case KEY_STATUS_MUTE_D:
                act_key = CUSTOM_KEY_MUTE_D;
                break;
            case KEY_STATUS_STANDBY:
                act_key = CUSTOM_KEY_STANDBY;
                break;
            case KEY_STATUS_ESC:
                act_key = LV_KEY_ESC;
                break;
        }

        last_key = act_key;
    }
    else {
        data->state = LV_INDEV_STATE_REL;
    }

    data->key = last_key;
}

/*------------------
 * Encoder
 * -----------------*/

/*Initialize your encoder*/
static void encoder_init(void)
{
    indev_init();
}

/*Will be called by the library to read the encoder*/
static void encoder_read(lv_indev_drv_t * indev_drv, lv_indev_data_t * data)
{
    // printf("start now time = %lu\n", get_jiffies());
    operate_status_t encoder_act = indev_scan_encoder();
    encoder_state = LV_INDEV_STATE_REL;
    encoder_diff = 0;
    switch(encoder_act) {
        case ENCODER_STATUS_ENTER:
            encoder_diff = 0;
            encoder_state = LV_INDEV_STATE_PR;
            break;
        case ENCODER_STATUS_RIGHT:
            encoder_diff = 1;
            // continue_flag = 0;
            break;
        case ENCODER_STATUS_LEFT:
            encoder_diff = -1;
            // continue_flag = 0;
            break;
    //    case ENCODER_CONTINUE_ERAD:
    //         continue_flag = 1;
    //         break;
    }
    // 每次进来都会置0，需要保存之前的状态，不好判断状态
    // if (continue_flag == 1) {
    //     printf("continue flag enable\n");
    //     data->continue_reading = true;
    // }

    data->enc_diff = encoder_diff;
    data->state = encoder_state;
    // printf("end now time = %lu\n", get_jiffies());
    if (data->enc_diff == 0 && data->state == 0) return;
    // printf("data->enc_diff = %d data->state = %d\n", data->enc_diff, data->state);
}

/*Call this function in an interrupt to process encoder events (turn, press)*/
/*
static void encoder_handler(void)
{
    encoder_diff += 0;
    encoder_state = LV_INDEV_STATE_REL;
}
*/
#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
