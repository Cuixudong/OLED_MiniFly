#ifndef __OLED_H
#define __OLED_H

#include <sys.h>
#include <stdint.h>
#include <string.h>

#define OLED_CMD    0       //写命令
#define OLED_DATA   1       //写数据

#define OLED_W      128
#define OLED_H      64
#define USB_HW_SPI  1       //硬SPI

#ifndef OLED_CS_Pin
#define OLED_CS_Pin GPIO_Pin_0
#endif
#ifndef OLED_CS_GPIO_Port
#define OLED_CS_GPIO_Port GPIOB
#endif
#ifndef OLED_RST_Pin
#define OLED_RST_Pin GPIO_Pin_1
#endif
#ifndef OLED_RST_GPIO_Port
#define OLED_RST_GPIO_Port GPIOB
#endif
#ifndef OLED_DC_Pin
#define OLED_DC_Pin GPIO_Pin_8
#endif
#ifndef OLED_DC_GPIO_Port
#define OLED_DC_GPIO_Port GPIOA
#endif

#if (!USB_HW_SPI)

#ifndef OLED_D0_Pin
#define OLED_D0_Pin GPIO_Pin_13
#endif
#ifndef OLED_D0_GPIO_Port
#define OLED_D0_GPIO_Port GPIOB
#endif
#ifndef OLED_D1_Pin
#define OLED_D1_Pin GPIO_Pin_15
#endif
#ifndef OLED_D1_GPIO_Port
#define OLED_D1_GPIO_Port GPIOB
#endif

#define OLED_D0_H   GPIO_SetBits(OLED_D0_GPIO_Port,OLED_D0_Pin)
#define OLED_D0_L   GPIO_ResetBits(OLED_D0_GPIO_Port,OLED_D0_Pin)
#define OLED_D1_H   GPIO_SetBits(OLED_D1_GPIO_Port,OLED_D1_Pin)
#define OLED_D1_L   GPIO_ResetBits(OLED_D1_GPIO_Port,OLED_D1_Pin)
#endif

//OLED操作脚
#define OLED_DC_H   GPIO_SetBits(OLED_DC_GPIO_Port,OLED_DC_Pin)
#define OLED_DC_L   GPIO_ResetBits(OLED_DC_GPIO_Port,OLED_DC_Pin)
#define OLED_CS_H   GPIO_SetBits(OLED_CS_GPIO_Port,OLED_CS_Pin)
#define OLED_CS_L   GPIO_ResetBits(OLED_CS_GPIO_Port,OLED_CS_Pin)
#define OLED_RST_H  GPIO_SetBits(OLED_RST_GPIO_Port,OLED_RST_Pin)
#define OLED_RST_L  GPIO_ResetBits(OLED_RST_GPIO_Port,OLED_RST_Pin)

//OLED控制用函数
void OLED_WR_Byte(uint8_t dat,uint8_t cmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Refresh_Gram(void);

void OLED_Init(void);
void OLED_Clear(uint8_t para);
void OLED_DrawPoint(uint16_t x,uint16_t y,uint8_t t);
void OLED_Fill(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2,uint8_t dot);
void OLED_ShowChar(uint16_t x,uint16_t y,char chr,uint8_t size,uint8_t mode);
void OLED_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint8_t mode);
void OLED_ShowString(uint16_t x,uint16_t y,char *p,uint8_t size);

void OLED_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint8_t dot);
void OLED_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint8_t dot);
void OLED_Draw_Circle(uint16_t x0,uint16_t y0,uint16_t r,uint8_t dot);
uint8_t OLED_ReadPoint(uint16_t x,uint16_t y);

void OLED_Show_Font(uint16_t x,uint16_t y,char  *font,uint8_t f_w,uint8_t f_h,uint8_t mode);
void OLED_Show_Str(uint16_t x,uint16_t y,char *str,uint8_t f_h,uint8_t mode);

void OLED_SetDir(uint8_t para);
void OLED_SetContrast(uint8_t para);

#endif
