#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "./indev.h"

#define GPIO_PATH "/sys/class/gpio/"

/*
#define ENCODER_ENTER_PIN_VALUE     0x08FE
#define ENCODER_RIGHT_PIN_VALUE     0x08FD
#define ENCODER_LEFT_PIN_VALUE      0x08FB
#define ENCODER_PEAK_PIN_VALUE      0x08F9
#define DEFAULT_PIN_VALUE           0x08FF

#define KEY_MUTE_A_PIN_VALUE    0x08EF
#define KEY_MUTE_B_PIN_VALUE    0x08DF
#define KEY_MUTE_C_PIN_VALUE    0x08BF
#define KEY_MUTE_D_PIN_VALUE    0x087F
#define KEY_STANDBY_PIN_VALUE   0x00FF
#define KEY_ESC_PIN_VALUE       0x08F7
*/
#define ENCODER_ENTER_BIT     0x0001
#define ENCODER_RIGHT_BIT     0x0002
#define ENCODER_LEFT_BIT      0x0004
#define ENCODER_PEAK_BIT      0x0006
#define ENCODER_DEFAULT_BIT   0x0007

#define KEY_MUTE_A_BIT        0x0010
#define KEY_MUTE_B_BIT        0x0020
#define KEY_MUTE_C_BIT        0x0040
#define KEY_MUTE_D_BIT        0x0080
#define KEY_STANDBY_BIT       0x0800
#define KEY_ESC_BIT           0x0008

// 定义编码器状态的枚举类型
typedef enum {
    ENCODER_IDLE,         // 静止状态
    ENCODER_ROTATE_RIGHT, // 右旋状态
    ENCODER_ROTATE_LEFT   // 左旋状态
} encoder_state_t;

static bool encoder_confirm_pressed = false;            // 编码器确认键状态
static encoder_state_t encoder_state = ENCODER_IDLE;    // 初始状态为静止
static unsigned short last_encoder_value = 0xFFFF;      // 上一次读取的值
static unsigned short last_key_value = 0xFFFF;          // 上一次读取的值

// 导出GPIO引脚，使其可用
void gpio_export(int pin) {
    char buffer[64];
    int len;
    int fd;

    fd = open(GPIO_PATH "export", O_WRONLY);
    if (fd == -1) {
        perror("gpio/export");
        return;
    }

    len = snprintf(buffer, sizeof(buffer), "%d", pin);
    if (write(fd, buffer, len) == -1) {
        perror("Error writing to export");
    }

    close(fd);
}

// 设置GPIO引脚的方向（in 或 out）
void gpio_direction(int pin, const char *direction) {
    char path[64];
    int fd;

    snprintf(path, sizeof(path), GPIO_PATH "gpio%d/direction", pin);
    fd = open(path, O_WRONLY);
    if (fd == -1) {
        perror("gpio/direction");
        return;
    }

    if (write(fd, direction, strlen(direction)) == -1) {
        perror("Error writing to direction");
    }

    close(fd);
}

// 向GPIO引脚写入值（0 或 1）
void gpio_write(int pin, int value) {
    char path[64];
    char buffer[2];
    int fd;

    snprintf(path, sizeof(path), GPIO_PATH "gpio%d/value", pin);
    fd = open(path, O_WRONLY);
    if (fd == -1) {
        perror("gpio/value");
        return;
    }

    snprintf(buffer, sizeof(buffer), "%d", value);
    if (write(fd, buffer, sizeof(buffer)) == -1) {
        perror("Error writing to value");
    }

    close(fd);
}

// 从GPIO引脚读取值（返回 0 或 1）
int gpio_read(int pin) {
    char path[64];
    char value_str[3];
    int fd;

    snprintf(path, sizeof(path), GPIO_PATH "gpio%d/value", pin);
    fd = open(path, O_RDONLY);
    if (fd == -1) {
        perror("gpio/value");
        return -1;
    }

    if (read(fd, value_str, 3) == -1) {
        perror("Error reading value");
        close(fd);
        return -1;
    }

    close(fd);

    return atoi(value_str);  // 转换为整数（0 或 1）
}

unsigned short read_74HC165(void) {
    unsigned short value = 0;

    gpio_write(PIN_74HC176_SH, 0);
    usleep(10);
    gpio_write(PIN_74HC176_SH, 1);

    for (int i = 0; i < 16; i++) {
        gpio_write(PIN_74HC176_CLK, 0);         // 拉低时钟
        usleep(10);                             // 确保时钟稳定
        value <<= 1;                            // 左移以腾出空间
        value |= gpio_read(PIN_74HC176_QH);     // 读取 Q7 的值
        gpio_write(PIN_74HC176_CLK, 1);         // 拉高时钟
        usleep(10);                             // 确保时钟稳定
    }
    return value;
}

// 处理按键输入
operate_status_t handle_key(unsigned short value) {
    if (!(value & KEY_MUTE_A_BIT)) {printf("mute A press\n");return KEY_STATUS_MUTE_A;}
    else if (!(value & KEY_MUTE_B_BIT)) {printf("mute B press\n");return KEY_STATUS_MUTE_B;}
    else if (!(value & KEY_MUTE_C_BIT)) {printf("mute C press\n");return KEY_STATUS_MUTE_C;}
    else if (!(value & KEY_MUTE_D_BIT)) {printf("mute D press\n");return KEY_STATUS_MUTE_D;}
    else if (!(value & KEY_STANDBY_BIT)) {printf("standby press\n");return KEY_STATUS_STANDBY;}
    else if (!(value & KEY_ESC_BIT)) {printf("esc but press\n");return KEY_STATUS_ESC;}
    else return KEY_STATUS_NOTHING;
}

// 编码器状态机
operate_status_t handle_encoder(unsigned short value) {

    if (!(value & ENCODER_ENTER_BIT)) {
        if (!encoder_confirm_pressed) {                 // 按键按下的初次检测
            encoder_confirm_pressed = true;
            printf("Encoder confirm key pressed\n");
        }
    } else if (value & ENCODER_ENTER_BIT) {
        if (encoder_confirm_pressed) {
            encoder_confirm_pressed = false;            // 按键释放
            printf("Encoder confirm key released\n");
            return ENCODER_STATUS_ENTER;
        }
    }

    operate_status_t ret = KEY_STATUS_NOTHING;
    switch (encoder_state) {
        case ENCODER_IDLE:
            if (!(value & ENCODER_RIGHT_BIT)) {
                encoder_state = ENCODER_ROTATE_RIGHT;   // 检测到右旋起点，继续读
//                ret = ENCODER_CONTINUE_ERAD;
            } else if (!(value & ENCODER_LEFT_BIT)) {
                encoder_state = ENCODER_ROTATE_LEFT;    // 检测到左旋起点，继续读
//                ret = ENCODER_CONTINUE_ERAD;
            }
            break;

        case ENCODER_ROTATE_RIGHT:
            if (!(value & ENCODER_PEAK_BIT)) {
                encoder_state = ENCODER_ROTATE_RIGHT;   // 右旋中间过程，继续读
//                ret = ENCODER_CONTINUE_ERAD;
            } else if (!(value & ENCODER_LEFT_BIT)) {
                printf("Encoder turned right\n");
                encoder_state = ENCODER_IDLE;           // 右旋完成，返回到静止状态
                ret = ENCODER_STATUS_RIGHT;
            } else if ((value & ENCODER_DEFAULT_BIT) == ENCODER_DEFAULT_BIT) {
                encoder_state = ENCODER_IDLE;           // 右旋不完整，返回到静止状态
            }
            break;

        case ENCODER_ROTATE_LEFT:
            if (!(value & ENCODER_PEAK_BIT)) {
                encoder_state = ENCODER_ROTATE_LEFT;    // 左旋中间过程，继续读
//                ret = ENCODER_CONTINUE_ERAD;
            } else if (!(value & ENCODER_RIGHT_BIT)) {
                printf("Encoder turned left\n");
                encoder_state = ENCODER_IDLE;           // 左旋完成，返回到静止状态
                ret = ENCODER_STATUS_LEFT;
            } else if ((value & ENCODER_DEFAULT_BIT) == ENCODER_DEFAULT_BIT) {
                encoder_state = ENCODER_IDLE;           // 左旋不完整，返回到静止状态
            }
            break;
    }

    return ret;
}

void indev_init(void) {
    gpio_export(PIN_74HC176_CLK);
    gpio_export(PIN_74HC176_QH);
    gpio_export(PIN_74HC176_SH);
    gpio_direction(PIN_74HC176_CLK, "out");
    gpio_direction(PIN_74HC176_SH, "out");
    gpio_direction(PIN_74HC176_QH, "in");
}

// 扫描编码器状态
operate_status_t indev_scan_encoder(void){
    unsigned short current_value = read_74HC165();

    if (current_value != last_encoder_value) {              // 检测变化
        //printf("encoder_state = %d", encoder_state);
        printf("Encoder data changed: 0x%04X  --> 0x%04X\n", last_encoder_value, current_value);
        last_encoder_value = current_value;                 // 更新最后的值

        return handle_encoder(current_value);
    }

    return KEY_STATUS_NOTHING;
}

// 扫描key状态
operate_status_t indev_scan_key(void){
    unsigned short current_value = read_74HC165();

    if (current_value != last_key_value) {              // 检测变化
        //printf("encoder_state = %d", encoder_state);
        printf("Key data changed: 0x%04X  --> 0x%04X\n", last_key_value, current_value);
        last_key_value = current_value;                 // 更新最后的值

        return handle_key(current_value);
    }

    return KEY_STATUS_NOTHING;
}