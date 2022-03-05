#include "menuL3_item.h"
#include "menuL2_item.h"
#include "menu_ui.h"
#include "windows.h"
#include "scrollbar.h"
#include "joystick.h"
#include "keyTask.h"
#include "display.h"
#include "OLED.h"
#include "config_param.h"
#include "24l01.h"
#include "menuL1_item.h"
#include "atkp.h"
#include "remoter_ctrl.h"

/********************************************************************************
 * 本程序只供学习使用，未经作者许可，不得用于其它任何用途
 * ALIENTEK MiniFly_Remotor
 * 二级菜单驱动代码
 * 正点原子@ALIENTEK
 * 技术论坛:www.openedv.com
 * 创建日期:2018/6/1
 * 版本：V1.0
 * 版权所有，盗版必究。
 * Copyright(C) 广州市星翼电子科技有限公司 2014-2024
 * All rights reserved
********************************************************************************/

/*菜单项数*/
#define  LED_RING_MENU_NUM      10
#define  WIFI_CAMERA_MENU_NUM   2
#define  OPTICAL_FLOW_MENU_NUM  2

#define  OLED_ON_OFF_MENU_NUM   2
#define  OLED_LIGHT_MENU_NUM    10
#define  OLED_DIR_MENU_NUM      2
#define  OLED_EFFECT_MENU_NUM   4

MenuItem_Typedef  ledringMenu[LED_RING_MENU_NUM];
MenuItem_Typedef  cameraMenu[WIFI_CAMERA_MENU_NUM];
MenuItem_Typedef  opflowMenu[OPTICAL_FLOW_MENU_NUM];

MenuItem_Typedef  oledonoffMenu[OLED_ON_OFF_MENU_NUM];
MenuItem_Typedef  oledlightMenu[OLED_LIGHT_MENU_NUM];
MenuItem_Typedef  oleddirMenu[OLED_DIR_MENU_NUM];
MenuItem_Typedef  oledeffectMenu[OLED_EFFECT_MENU_NUM];

const uint8_t* ledringLanguage[3][LED_RING_MENU_NUM]= {
    {
        "关闭",
        "颜色测试",
        "姿态感应",
        "陀螺感应",
        "闪烁警报",
        "手电筒",
        "呼吸灯",
        "流水灯1",
        "流水灯2",
        "流水灯3",
    },
    {
        "Turn off",
        "Color Test",
        "Attitude induce",
        "Gyro induce",
        "Blink LED",
        "Flashlight",
        "Breathing LED",
        "Spin Effect1",
        "Spin Effect2",
        "Spin Effect3",
    },
    {
        "關閉",
        "顏色測試",
        "姿態感應",
        "陀螺感應",
        "閃爍警報",
        "手電筒",
        "呼吸燈",
        "流水燈1",
        "流水燈2",
        "流水燈3",
    },
};
const uint8_t* cameraLanguage[3][WIFI_CAMERA_MENU_NUM]= {
    {
        "开启",
        "关闭",
    },
    {
        "Turn On",
        "Turn Off",
    },
    {
        "開啟",
        "關閉",
    }
};
const uint8_t* opflowLanguage[3][OPTICAL_FLOW_MENU_NUM]= {
    {
        "开启激光",
        "关闭激光",
    },
    {
        "Turn On Vl53lxx",
        "Turn Off Vl53lxx",
    },
    {
        "開啟激光",
        "關閉激光",
    }
};

const uint8_t* oledonoffLanguage[3][OLED_ON_OFF_MENU_NUM]= {
    {
        "关闭屏幕",
        "打开屏幕",
    },
    {
        "Screen off",
        "Screen on",
    },
    {
        "關閉屏幕",
        "打開屏幕",
    },
};

const uint8_t* oledlightLanguage[3][OLED_LIGHT_MENU_NUM]= {
    {
        "亮度1",
        "亮度2",
        "亮度3",
        "亮度4",
        "亮度5",
        "亮度6",
        "亮度7",
        "亮度8",
        "亮度9",
        "亮度10",
    },
    {
        "Level 1",
        "Level 2",
        "Level 3",
        "Level 4",
        "Level 5",
        "Level 6",
        "Level 7",
        "Level 8",
        "Level 9",
        "Level 10",
        
    },
    {
        "亮度1",
        "亮度2",
        "亮度3",
        "亮度4",
        "亮度5",
        "亮度6",
        "亮度7",
        "亮度8",
        "亮度9",
        "亮度10",
    },
};

const uint8_t* oleddirLanguage[3][OLED_DIR_MENU_NUM]= {
    {
        "正向",
        "反向",
    },
    {
        "Normal",
        "Reverse",
    },
    {
        "正向",
        "反向",
    },
};

const uint8_t* oledeffectLanguage[3][OLED_EFFECT_MENU_NUM]= {
    {
        "数字效果",
        "图形效果",
        "三维效果",
        "默认效果",
    },
    {
        "Num Effect",
        "Shape Effect",
        "3D Effect",
        "Nor Effect",
    },
    {
        "數字效果",
        "圖形效果",
        "三維效果",
        "默認效果",
    },
};

static void setLedringEffect0(void)
{
    gotoLastMenu();
    sendRmotorCmd(CMD_LEDRING_EFFECT, 0);
}

static void setLedringEffect1(void)
{
    gotoLastMenu();
    sendRmotorCmd(CMD_LEDRING_EFFECT, 1);
}

static void setLedringEffect2(void)
{
    gotoLastMenu();
    sendRmotorCmd(CMD_LEDRING_EFFECT, 2);
}

static void setLedringEffect3(void)
{
    gotoLastMenu();
    sendRmotorCmd(CMD_LEDRING_EFFECT, 3);
}

static void setLedringEffect4(void)
{
    gotoLastMenu();
    sendRmotorCmd(CMD_LEDRING_EFFECT, 4);
}

static void setLedringEffect5(void)
{
    gotoLastMenu();
    sendRmotorCmd(CMD_LEDRING_EFFECT, 5);
}

static void setLedringEffect6(void)
{
    gotoLastMenu();
    sendRmotorCmd(CMD_LEDRING_EFFECT, 6);
}


static void setLedringEffect7(void)
{
    gotoLastMenu();
    sendRmotorCmd(CMD_LEDRING_EFFECT, 7);
}

static void setLedringEffect8(void)
{
    gotoLastMenu();
    sendRmotorCmd(CMD_LEDRING_EFFECT, 8);
}

static void setLedringEffect9(void)
{
    gotoLastMenu();
    sendRmotorCmd(CMD_LEDRING_EFFECT, 9);
}

/*初始化ledring菜单*/
void ledringMenuInit(void)
{
    for(int i=0; i<LED_RING_MENU_NUM; i++)
    {
        ledringMenu[i].menuItemCount = LED_RING_MENU_NUM;
        ledringMenu[i].isSelect = false;
        ledringMenu[i].icoSelected = radio_selected_img;
        ledringMenu[i].icoUnselected = radio_unselected_img;
        ledringMenu[i].title = ledringLanguage[configParam.language][i];
        ledringMenu[i].parentMenu = mainMenu;
        ledringMenu[i].childrenMenu = NULL;
    }

    ledringMenu[0].isSelect = true;
    ledringMenu[0].Function = setLedringEffect0;
    ledringMenu[1].Function = setLedringEffect1;
    ledringMenu[2].Function = setLedringEffect2;
    ledringMenu[3].Function = setLedringEffect3;
    ledringMenu[4].Function = setLedringEffect4;
    ledringMenu[5].Function = setLedringEffect5;
    ledringMenu[6].Function = setLedringEffect6;
    ledringMenu[7].Function = setLedringEffect7;
    ledringMenu[8].Function = setLedringEffect8;
    ledringMenu[9].Function = setLedringEffect9;
}

static void turnOnExpModule(void)
{
    gotoLastMenu();
    sendRmotorCmd(CMD_POWER_MODULE, 1);
}

static void turnOffExpModule(void)
{
    gotoLastMenu();
    sendRmotorCmd(CMD_POWER_MODULE, 0);
}
/*初始摄像头设置菜单*/
void cameraMenuInit(void)
{
    for(int i=0; i<WIFI_CAMERA_MENU_NUM; i++)
    {
        cameraMenu[i].menuItemCount = WIFI_CAMERA_MENU_NUM;
        cameraMenu[i].isSelect = false;
        cameraMenu[i].icoSelected = radio_selected_img;
        cameraMenu[i].icoUnselected = radio_unselected_img;
        cameraMenu[i].title = cameraLanguage[configParam.language][i];
        cameraMenu[i].Function = NULL;
        cameraMenu[i].parentMenu = mainMenu;
        cameraMenu[i].childrenMenu = NULL;
    }

    cameraMenu[0].isSelect = true;
    cameraMenu[0].Function = turnOnExpModule;
    cameraMenu[1].Function = turnOffExpModule;
}

static void turnOnVl53lxx(void)
{
    gotoLastMenu();
    sendRmotorCmd(CMD_POWER_VL53LXX, 1);
}

static void turnOffVl53lxx(void)
{
    gotoLastMenu();
    sendRmotorCmd(CMD_POWER_VL53LXX, 0);
}
/*初始摄像头设置菜单*/
void vl53lxxMenuInit(void)
{
    for(int i=0; i<OPTICAL_FLOW_MENU_NUM; i++)
    {
        opflowMenu[i].menuItemCount = OPTICAL_FLOW_MENU_NUM;
        opflowMenu[i].isSelect = false;
        opflowMenu[i].icoSelected = radio_selected_img;
        opflowMenu[i].icoUnselected = radio_unselected_img;
        opflowMenu[i].title = opflowLanguage[configParam.language][i];
        opflowMenu[i].Function = NULL;
        opflowMenu[i].parentMenu = mainMenu;
        opflowMenu[i].childrenMenu = NULL;
    }

    opflowMenu[0].isSelect = true;
    opflowMenu[0].Function = turnOnVl53lxx;
    opflowMenu[1].Function = turnOffVl53lxx;
}

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

static void turnOnOLED(void)
{
    gotoLastMenu();
    sendRmotorCmd(CMD_OLED_MODE, OLED_CMD_ON);
}
static void turnOffOLED(void)
{
    gotoLastMenu();
    sendRmotorCmd(CMD_OLED_MODE, OLED_CMD_OFF);
}

void oledonoffMenuInit(void)
{
    for(int i=0; i<OLED_ON_OFF_MENU_NUM; i++)
    {
        oledonoffMenu[i].menuItemCount = OLED_ON_OFF_MENU_NUM;
        oledonoffMenu[i].isSelect = false;
        oledonoffMenu[i].icoSelected = radio_selected_img;
        oledonoffMenu[i].icoUnselected = radio_unselected_img;
        oledonoffMenu[i].title = oledonoffLanguage[configParam.language][i];
        oledonoffMenu[i].Function = NULL;
        oledonoffMenu[i].parentMenu = mainMenu;
        oledonoffMenu[i].childrenMenu = NULL;
    }

    oledonoffMenu[0].isSelect = true;
    oledonoffMenu[0].Function = turnOffOLED;
    oledonoffMenu[1].Function = turnOnOLED;
}

static void setOledLight1(void) {gotoLastMenu();sendRmotorCmd(CMD_OLED_MODE, OLED_CMD_LIGHT_1);}
static void setOledLight2(void) {gotoLastMenu();sendRmotorCmd(CMD_OLED_MODE, OLED_CMD_LIGHT_2);}
static void setOledLight3(void) {gotoLastMenu();sendRmotorCmd(CMD_OLED_MODE, OLED_CMD_LIGHT_3);}
static void setOledLight4(void) {gotoLastMenu();sendRmotorCmd(CMD_OLED_MODE, OLED_CMD_LIGHT_4);}
static void setOledLight5(void) {gotoLastMenu();sendRmotorCmd(CMD_OLED_MODE, OLED_CMD_LIGHT_5);}
static void setOledLight6(void) {gotoLastMenu();sendRmotorCmd(CMD_OLED_MODE, OLED_CMD_LIGHT_6);}
static void setOledLight7(void) {gotoLastMenu();sendRmotorCmd(CMD_OLED_MODE, OLED_CMD_LIGHT_7);}
static void setOledLight8(void) {gotoLastMenu();sendRmotorCmd(CMD_OLED_MODE, OLED_CMD_LIGHT_8);}
static void setOledLight9(void) {gotoLastMenu();sendRmotorCmd(CMD_OLED_MODE, OLED_CMD_LIGHT_9);}
static void setOledLight10(void) {gotoLastMenu();sendRmotorCmd(CMD_OLED_MODE, OLED_CMD_LIGHT_10);}

void oledlightMenuInit(void)
{
    for(int i=0; i<OLED_LIGHT_MENU_NUM; i++)
    {
        oledlightMenu[i].menuItemCount = OLED_LIGHT_MENU_NUM;
        oledlightMenu[i].isSelect = false;
        oledlightMenu[i].icoSelected = radio_selected_img;
        oledlightMenu[i].icoUnselected = radio_unselected_img;
        oledlightMenu[i].title = oledlightLanguage[configParam.language][i];
        oledlightMenu[i].Function = NULL;
        oledlightMenu[i].parentMenu = mainMenu;
        oledlightMenu[i].childrenMenu = NULL;
    }

    oledlightMenu[0].isSelect = true;
    oledlightMenu[0].Function = setOledLight1;
    oledlightMenu[1].Function = setOledLight2;
    oledlightMenu[2].Function = setOledLight3;
    oledlightMenu[3].Function = setOledLight4;
    oledlightMenu[4].Function = setOledLight5;
    oledlightMenu[5].Function = setOledLight6;
    oledlightMenu[6].Function = setOledLight7;
    oledlightMenu[7].Function = setOledLight8;
    oledlightMenu[8].Function = setOledLight9;
    oledlightMenu[9].Function = setOledLight10;
}

static void setOledDir1(void)
{
    gotoLastMenu();
    sendRmotorCmd(CMD_OLED_MODE, OLED_CMD_DIR_N);
}

static void setOledDir2(void)
{
    gotoLastMenu();
    sendRmotorCmd(CMD_OLED_MODE, OLED_CMD_DIR_I);
}

void oleddirMenuInit(void)
{
    for(int i=0; i<OLED_DIR_MENU_NUM; i++)
    {
        oleddirMenu[i].menuItemCount = OLED_DIR_MENU_NUM;
        oleddirMenu[i].isSelect = false;
        oleddirMenu[i].icoSelected = radio_selected_img;
        oleddirMenu[i].icoUnselected = radio_unselected_img;
        oleddirMenu[i].title = oleddirLanguage[configParam.language][i];
        oleddirMenu[i].Function = NULL;
        oleddirMenu[i].parentMenu = mainMenu;
        oleddirMenu[i].childrenMenu = NULL;
    }

    oleddirMenu[0].isSelect = true;
    oleddirMenu[0].Function = setOledDir1;
    oleddirMenu[1].Function = setOledDir2;
}

static void setOledEffect1(void)
{
    gotoLastMenu();
    sendRmotorCmd(CMD_OLED_MODE, OLED_CMD_EFF_1);
}
static void setOledEffect2(void)
{
    gotoLastMenu();
    sendRmotorCmd(CMD_OLED_MODE, OLED_CMD_EFF_2);
}
static void setOledEffect3(void)
{
    gotoLastMenu();
    sendRmotorCmd(CMD_OLED_MODE, OLED_CMD_EFF_3);
}
static void setOledEffect4(void)
{
    gotoLastMenu();
    sendRmotorCmd(CMD_OLED_MODE, OLED_CMD_EFF_4);
}

void oledeffectMenuInit(void)
{
    for(int i=0; i<OLED_EFFECT_MENU_NUM; i++)
    {
        oledeffectMenu[i].menuItemCount = OLED_EFFECT_MENU_NUM;
        oledeffectMenu[i].isSelect = false;
        oledeffectMenu[i].icoSelected = radio_selected_img;
        oledeffectMenu[i].icoUnselected = radio_unselected_img;
        oledeffectMenu[i].title = oledeffectLanguage[configParam.language][i];
        oledeffectMenu[i].Function = NULL;
        oledeffectMenu[i].parentMenu = mainMenu;
        oledeffectMenu[i].childrenMenu = NULL;
    }

    oledeffectMenu[0].isSelect = true;
    oledeffectMenu[0].Function = setOledEffect1;
    oledeffectMenu[1].Function = setOledEffect2;
    oledeffectMenu[2].Function = setOledEffect3;
    oledeffectMenu[3].Function = setOledEffect4;
}
