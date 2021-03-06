#include "menuL2_item.h"
#include "menuL3_item.h"
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
#define  CONTROLMODE_MENU_NUM   3
#define  FLYMODE_MENU_NUM    	2
#define  FLYSPEED_MENU_NUM		3
#define  FLIPENABLE_MENU_NUM	2
#define  LANGUAGE_MENU_NUM    	3
#define	 EXPMODULE_MENU_NUM		4

#define  OLED_SET_MENU_NUM		4

MenuItem_Typedef  controlmodeMenu[CONTROLMODE_MENU_NUM];
MenuItem_Typedef  flymodeMenu[FLYMODE_MENU_NUM];
MenuItem_Typedef  flyspeedMenu[FLYSPEED_MENU_NUM];
MenuItem_Typedef  flipEnableMenu[FLIPENABLE_MENU_NUM];
MenuItem_Typedef  languageMenu[LANGUAGE_MENU_NUM];
MenuItem_Typedef  expModuleMenu[EXPMODULE_MENU_NUM];

MenuItem_Typedef  oledSetMenu[OLED_SET_MENU_NUM];

/****** 选中图标 阴码 逐列式 顺向(高位在前) *****/
const uint8_t radio_selected_img[32]= {
    0x00,0x00,0x03,0xC0,0x0C,0x30,0x10,0x08,0x11,0x88,0x23,0xC4,0x27,0xE4,0x27,0xE4,
    0x23,0xC4,0x11,0x88,0x10,0x08,0x0C,0x30,0x03,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,
};

/****** 非选中图标 阴码 逐列式 顺向(高位在前) *****/
const uint8_t  radio_unselected_img[32]= {
    0x00,0x00,0x03,0xC0,0x0C,0x30,0x10,0x08,0x10,0x08,0x20,0x04,0x20,0x04,0x20,0x04,
    0x20,0x04,0x10,0x08,0x10,0x08,0x0C,0x30,0x03,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,
};

const uint8_t* controlmodeLanguage[3][CONTROLMODE_MENU_NUM]= {
    {
        "定高模式",
        "手动模式",
        "定点模式",
    },
    {
        "Althold Mode",
        "Manual Mode",
        "3Dhold Mode",
    },
    {
        "定高模式",
        "手動模式",
        "定點模式",
    },
};
const uint8_t* flymodeLanguage[3][FLYMODE_MENU_NUM]= {
    {
        "无头模式",
        "有头模式",
    },
    {
        "Headless",
        "X-mode",
    },
    {
        "無頭模式",
        "有頭模式",
    },
};
const uint8_t* flySpeedLanguage[3][FLYSPEED_MENU_NUM]= {
    {
        "低速模式",
        "中速模式",
        "高速模式",
    },
    {
        "Low speed",
        "Medium speed",
        "High speed",
    },
    {
        "低速模式",
        "中速模式",
        "高速模式",
    }
};
const uint8_t* flipEnableLanguage[3][FLIPENABLE_MENU_NUM]= {
    {
        "开启",
        "关闭",
    },
    {
        "Enable",
        "Disable",
    },
    {
        "開啟",
        "關閉",
    }
};
const uint8_t* languageChoiceLanguage[3][LANGUAGE_MENU_NUM]= {
    {
        "简体中文",
        "English",
        "繁体中文"
    },
    {
        "简体中文",
        "English",
        "繁体中文"
    },
    {
        "简体中文",
        "English",
        "繁体中文"
    }
};
const uint8_t* expModuleLanguage[3][EXPMODULE_MENU_NUM]= {
    {
        " 未发现模块！",
        "1.RGB灯环",
        "1.摄像头模块",
        "1.光流模块",
    },
    {
        "No mudule found!",
        "1.RGB_LED Ring",
        "1.Camera module",
        "1.opFlow module",
    },
    {
        " 未發現模塊！",
        "1.RGB燈環",
        "1.攝像頭模塊",
        "1.光流模塊",
    }
};

const uint8_t* oledSetLanguage[3][OLED_SET_MENU_NUM]= {
    {
        "1.显示开关",
        "2.亮度设置",
        "3.显示方向",
        "4.显示效果",
    },
    {
        "1.OLED On/Off",
        "2.Light Set",
        "3.Display Dir",
        "4.Display Effect",
    },
    {
        "1.顯示開關",
        "2.亮度設置",
        "3.顯示方向",
        "4.顯示效果",
    }
};

static void setCtrlmodeAlthold(void)
{
    gotoLastMenu();
    configParam.flight.ctrl = ALTHOLD_MODE;
}

static void setCtrlmodeManual(void)
{
    gotoLastMenu();
    configParam.flight.ctrl = MANUAL_MODE;
}

static void setCtrlmode3Dhold(void)
{
    gotoLastMenu();
    configParam.flight.ctrl = THREEHOLD_MODE;
}

/*初始化控制模式菜单*/
void controlmodeMenuInit(void)
{
    for(int i=0; i<CONTROLMODE_MENU_NUM; i++)
    {
        controlmodeMenu[i].menuItemCount = CONTROLMODE_MENU_NUM;
        controlmodeMenu[i].isSelect = false;
        controlmodeMenu[i].icoSelected = radio_selected_img;
        controlmodeMenu[i].icoUnselected = radio_unselected_img;
        controlmodeMenu[i].title = controlmodeLanguage[configParam.language][i];
        controlmodeMenu[i].parentMenu = mainMenu;
        controlmodeMenu[i].childrenMenu = NULL;
    }
    controlmodeMenu[0].Function = setCtrlmodeAlthold;
    controlmodeMenu[1].Function = setCtrlmodeManual;
    controlmodeMenu[2].Function = setCtrlmode3Dhold;
    switch(configParam.flight.ctrl)
    {
    case ALTHOLD_MODE:
        controlmodeMenu[0].isSelect = true;
        break;
    case MANUAL_MODE:
        controlmodeMenu[1].isSelect = true;
        break;
    case THREEHOLD_MODE:
        controlmodeMenu[2].isSelect = true;
    }
}

static void setFlymodeHeadless(void)
{
    gotoLastMenu();
    configParam.flight.mode = HEAD_LESS;
}

static void setFlymodeXmode(void)
{
    gotoLastMenu();
    configParam.flight.mode = X_MODE;
}

/*初始化飞行模式菜单*/
void flymodeMenuInit(void)
{
    for(int i=0; i<FLYMODE_MENU_NUM; i++)
    {
        flymodeMenu[i].menuItemCount = FLYMODE_MENU_NUM;
        flymodeMenu[i].isSelect = false;
        flymodeMenu[i].icoSelected = radio_selected_img;
        flymodeMenu[i].icoUnselected = radio_unselected_img;
        flymodeMenu[i].title = flymodeLanguage[configParam.language][i];
        flymodeMenu[i].Function = NULL;
        flymodeMenu[i].parentMenu = mainMenu;
        flymodeMenu[i].childrenMenu = NULL;
    }
    flymodeMenu[0].Function = setFlymodeHeadless;
    flymodeMenu[1].Function = setFlymodeXmode;
    switch(configParam.flight.mode)
    {
    case HEAD_LESS:
        flymodeMenu[0].isSelect = true;
        break;
    case X_MODE:
        flymodeMenu[1].isSelect = true;
        break;
    }
}

static void setFlightLowSpeed(void)
{
    gotoLastMenu();
    configParam.flight.speed = LOW_SPEED;
}

static void setFlightMidSpeed(void)
{
    gotoLastMenu();
    configParam.flight.speed = MID_SPEED;
}

static void setFlightHighSpeed(void)
{
    gotoLastMenu();
    configParam.flight.speed = HIGH_SPEED;
}

/*初始化飞行速度菜单*/
void flySpeedMenuInit(void)
{
    for(int i=0; i<FLYSPEED_MENU_NUM; i++)
    {
        flyspeedMenu[i].menuItemCount = FLYSPEED_MENU_NUM;
        flyspeedMenu[i].isSelect = false;
        flyspeedMenu[i].icoSelected = radio_selected_img;
        flyspeedMenu[i].icoUnselected = radio_unselected_img;
        flyspeedMenu[i].title = flySpeedLanguage[configParam.language][i];
        flyspeedMenu[i].Function = NULL;
        flyspeedMenu[i].parentMenu = mainMenu;
        flyspeedMenu[i].childrenMenu = NULL;
    }
    flyspeedMenu[0].Function = setFlightLowSpeed;
    flyspeedMenu[1].Function = setFlightMidSpeed;
    flyspeedMenu[2].Function = setFlightHighSpeed;
    switch(configParam.flight.speed)
    {
    case LOW_SPEED:
        flyspeedMenu[0].isSelect = true;
        break;
    case MID_SPEED:
        flyspeedMenu[1].isSelect = true;
        break;
    case HIGH_SPEED:
        flyspeedMenu[2].isSelect = true;
        break;
    }
}

static void setFlipEnable(void)
{
    gotoLastMenu();
    configParam.flight.flip = FLIP_ENABLE;
}

static void setFlipDisable(void)
{
    gotoLastMenu();
    configParam.flight.flip = FLIP_DISABLE;
}

/*初始化翻滚使能菜单*/
void flipEnableMenuInit(void)
{
    for(int i=0; i<FLIPENABLE_MENU_NUM; i++)
    {
        flipEnableMenu[i].menuItemCount = FLIPENABLE_MENU_NUM;
        flipEnableMenu[i].isSelect = false;
        flipEnableMenu[i].icoSelected = radio_selected_img;
        flipEnableMenu[i].icoUnselected = radio_unselected_img;
        flipEnableMenu[i].title = flipEnableLanguage[configParam.language][i];
        flipEnableMenu[i].parentMenu = mainMenu;
        flipEnableMenu[i].childrenMenu = NULL;
    }
    flipEnableMenu[0].Function = setFlipEnable;
    flipEnableMenu[1].Function = setFlipDisable;
    switch(configParam.flight.flip)
    {
    case FLIP_ENABLE:
        flipEnableMenu[0].isSelect = true;
        break;
    case FLIP_DISABLE:
        flipEnableMenu[1].isSelect = true;
        break;
    }
}


static void setLanguageSimpleChinese(void)
{
    gotoLastMenu();
    configParam.language = SIMPLE_CHINESE;
    mainMenuInit();
    flymodeMenuInit();
    controlmodeMenuInit();
    languageMenuInit();
    flySpeedMenuInit();
    flipEnableMenuInit();
    expModuleMenuInit();
    oledSetMenuInit();
    ledringMenuInit();
    cameraMenuInit();
    vl53lxxMenuInit();
    oledonoffMenuInit();
    oledlightMenuInit();
    oleddirMenuInit();
    oledeffectMenuInit();
}

static void setLanguageEnglish(void)
{
    gotoLastMenu();
    configParam.language = ENGLISH;
    mainMenuInit();
    flymodeMenuInit();
    controlmodeMenuInit();
    languageMenuInit();
    flySpeedMenuInit();
    flipEnableMenuInit();
    expModuleMenuInit();
    oledSetMenuInit();
    ledringMenuInit();
    cameraMenuInit();
    vl53lxxMenuInit();
    oledonoffMenuInit();
    oledlightMenuInit();
    oleddirMenuInit();
    oledeffectMenuInit();
}

static void setLanguageComplexChinese(void)
{
    gotoLastMenu();
    configParam.language = COMPLEX_CHINESE;
    mainMenuInit();
    flymodeMenuInit();
    controlmodeMenuInit();
    languageMenuInit();
    flySpeedMenuInit();
    flipEnableMenuInit();
    expModuleMenuInit();
    oledSetMenuInit();
    ledringMenuInit();
    cameraMenuInit();
    vl53lxxMenuInit();
    oledonoffMenuInit();
    oledlightMenuInit();
    oleddirMenuInit();
    oledeffectMenuInit();
}

/*初始化语言选择菜单*/
void languageMenuInit(void)
{
    for(int i=0; i<LANGUAGE_MENU_NUM; i++)
    {
        languageMenu[i].menuItemCount = LANGUAGE_MENU_NUM;
        languageMenu[i].isSelect = false;
        languageMenu[i].icoSelected = radio_selected_img;
        languageMenu[i].icoUnselected = radio_unselected_img;
        languageMenu[i].title = languageChoiceLanguage[configParam.language][i];
        languageMenu[i].parentMenu = mainMenu;
        languageMenu[i].childrenMenu = NULL;
    }
    languageMenu[0].Function = setLanguageSimpleChinese;
    languageMenu[1].Function = setLanguageEnglish;
    languageMenu[2].Function = setLanguageComplexChinese;

    switch(configParam.language)
    {
    case SIMPLE_CHINESE:
        languageMenu[0].isSelect = true;
        break;
    case ENGLISH:
        languageMenu[1].isSelect = true;
        break;
    case COMPLEX_CHINESE:
        languageMenu[2].isSelect = true;
    }
}

/*初始化扩展模块菜单*/
void expModuleMenuInit(void)
{
    for(int i=0; i<EXPMODULE_MENU_NUM; i++)
    {
        expModuleMenu[i].menuItemCount = 1;
        expModuleMenu[i].isSelect = true;
        expModuleMenu[i].icoSelected = finger_img;
        expModuleMenu[i].icoUnselected = NULL;
        expModuleMenu[i].title = expModuleLanguage[configParam.language][i];
        expModuleMenu[i].Function = NULL;
        expModuleMenu[i].parentMenu = mainMenu;
        expModuleMenu[i].childrenMenu = NULL;
    }
    expModuleMenu[1].childrenMenu = ledringMenu;
    expModuleMenu[1].Function = gotoNextMenu;

    expModuleMenu[2].childrenMenu = cameraMenu;
    expModuleMenu[2].Function = gotoNextMenu;

    expModuleMenu[3].childrenMenu = opflowMenu;
    expModuleMenu[3].Function = gotoNextMenu;
}

void oledSetMenuInit(void)
{
    for(int i=0; i<OLED_SET_MENU_NUM; i++)
    {
        oledSetMenu[i].menuItemCount = OLED_SET_MENU_NUM;
        oledSetMenu[i].isSelect = false;
        oledSetMenu[i].icoSelected = finger_img;
        oledSetMenu[i].icoUnselected = NULL;
        oledSetMenu[i].title = oledSetLanguage[configParam.language][i];
        oledSetMenu[i].Function = gotoNextMenu;
        oledSetMenu[i].parentMenu = mainMenu;
        oledSetMenu[i].childrenMenu = NULL;
    }

    oledSetMenu[0].isSelect = true;
    oledSetMenu[0].childrenMenu = oledonoffMenu;
    oledSetMenu[1].childrenMenu = oledlightMenu;
    oledSetMenu[2].childrenMenu = oleddirMenu;
    oledSetMenu[3].childrenMenu = oledeffectMenu;
}
