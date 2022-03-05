#ifndef __OLED_H
#define __OLED_H
#include "sys.h"

/********************************************************************************
 * 本程序只供学习使用，未经作者许可，不得用于其它任何用途
 * ALIENTEK MiniFly_Remotor
 * SSD1306 OLED驱动代码
 * 驱动方式:STM32硬件SPI
 * 正点原子@ALIENTEK
 * 技术论坛:www.openedv.com
 * 创建日期:2018/6/1
 * 版本：V1.0
 * 版权所有，盗版必究。
 * Copyright(C) 广州市星翼电子科技有限公司 2014-2024
 * All rights reserved
********************************************************************************/

#define  OLED_SPI   SPI2
//#define OLED_CS  	PDout(6)
#define OLED_RST 	PBout(14)
#define OLED_RS  	PBout(12)

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

//OLED控制用函数
void oled_wr_byte(uint8_t dat,uint8_t cmd);
void oled_displayON(void);
void oled_displayOFF(void);
void oled_refreshGram(void);
void oledInit(void);
void oled_clear(void);
void oled_drawPoint(uint8_t x,uint8_t y,uint8_t t);
uint8_t oled_readPoint(uint8_t x,uint8_t y);
void oled_fill(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t dot);
void oled_showChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t f_w,uint8_t f_h,uint8_t mode);
void oled_showNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t f_w,uint8_t f_h);
void oled_showString(uint8_t x,uint8_t y,const uint8_t *p,uint8_t f_w,uint8_t f_h);
void oled_showPicture(uint8_t x,uint8_t y,const uint8_t *p,uint8_t p_w,uint8_t p_h);
#endif










