#ifndef __MENUL3_ITEM_H
#define __MENUL3_ITEM_H
#include <stdint.h>
#include "gui_menu.h"

/********************************************************************************	 
 * ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
 * ALIENTEK MiniFly_Remotor
 * �����˵���������		
 * ����ԭ��@ALIENTEK
 * ������̳:www.openedv.com
 * ��������:2018/6/1
 * �汾��V1.0
 * ��Ȩ���У�����ؾ���
 * Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
 * All rights reserved
********************************************************************************/

extern MenuItem_Typedef  ledringMenu[];
extern MenuItem_Typedef  cameraMenu[];
extern MenuItem_Typedef  opflowMenu[];

extern MenuItem_Typedef  oledonoffMenu[];
extern MenuItem_Typedef  oledlightMenu[];
extern MenuItem_Typedef  oleddirMenu[];
extern MenuItem_Typedef  oledeffectMenu[];

void ledringMenuInit(void);
void cameraMenuInit(void);
void vl53lxxMenuInit(void);
void oledonoffMenuInit(void);
void oledlightMenuInit(void);
void oleddirMenuInit(void);
void oledeffectMenuInit(void);

#endif /*__MENUL3_ITEM_H*/

