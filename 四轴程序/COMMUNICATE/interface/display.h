#ifndef __DISPLAY_H
#define __DISPLAY_H
#include <stdbool.h>
#include "atkp.h"

#define DISPLAY_CYCLE  20   //ms

#define OLED_CMD_ON         0x70
#define OLED_CMD_OFF        0x71
#define OLED_CMD_LIGHT_1    0x80
#define OLED_CMD_LIGHT_2    0x81
#define OLED_CMD_LIGHT_3    0x82
#define OLED_CMD_LIGHT_4    0x83
#define OLED_CMD_LIGHT_5    0x84
#define OLED_CMD_LIGHT_6    0x85
#define OLED_CMD_LIGHT_7    0x86
#define OLED_CMD_LIGHT_8    0x87
#define OLED_CMD_LIGHT_9    0x88
#define OLED_CMD_LIGHT_10   0x89
#define OLED_CMD_DIR_N      0x90
#define OLED_CMD_DIR_I      0x91
#define OLED_CMD_EFF_1      0xA0
#define OLED_CMD_EFF_2      0xA1
#define OLED_CMD_EFF_3      0xA2
#define OLED_CMD_EFF_4      0xA3

typedef __packed struct _oledMode_t
{
//    __packed union
//    {
//        __packed struct
//        {
//            uint8_t oledonoff   :1;
//            uint8_t light       :4;
//            uint8_t dir         :1;
//            uint8_t oledeffect  :2;
//        };
//        uint8_t _oled_mode;
//    };
    
    uint8_t _oled_mode;
} oledMode_t;

extern __IO oledMode_t oled_mode;
extern __IO uint8_t oled_mod[4];

void displayInit(void);
void displayTask(void *param);

#endif /* __PM_H */
