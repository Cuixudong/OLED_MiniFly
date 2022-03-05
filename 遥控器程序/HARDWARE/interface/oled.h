#ifndef __OLED_H
#define __OLED_H
#include "sys.h"

/********************************************************************************
 * ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
 * ALIENTEK MiniFly_Remotor
 * SSD1306 OLED��������
 * ������ʽ:STM32Ӳ��SPI
 * ����ԭ��@ALIENTEK
 * ������̳:www.openedv.com
 * ��������:2018/6/1
 * �汾��V1.0
 * ��Ȩ���У�����ؾ���
 * Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
 * All rights reserved
********************************************************************************/

#define  OLED_SPI   SPI2
//#define OLED_CS  	PDout(6)
#define OLED_RST 	PBout(14)
#define OLED_RS  	PBout(12)

#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

//OLED�����ú���
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










