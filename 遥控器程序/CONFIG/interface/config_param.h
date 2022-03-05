#ifndef __CONFIG_PARAM_H
#define __CONFIG_PARAM_H
#include <stdbool.h>
#include "sys.h"
#include "24l01.h"
#include "remoter_ctrl.h"
#include "joystick.h"

/********************************************************************************
 * ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
 * ALIENTEK MiniFly
 * ���ò�����������
 * ����ԭ��@ALIENTEK
 * ������̳:www.openedv.com
 * ��������:2018/6/1
 * �汾��V1.0
 * ��Ȩ���У�����ؾ���
 * Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
 * All rights reserved
********************************************************************************/

#define BOOTLOADER_SIZE		0 //(9*1024)		/*9K bootloader*/
#define CONFIG_PARAM_SIZE	(127*1024)		/*128K���ڱ������*/

#define CONFIG_PARAM_ADDR 	(FLASH_BASE + CONFIG_PARAM_SIZE)/*���ò��������ַ*/
#define FIRMWARE_START_ADDR (FLASH_BASE)

/* Ĭ�����ò��� */
#define  VERSION	13		/*��ʾ�汾ΪV1.3*/
#define  DISPLAY_LANGUAGE	SIMPLE_CHINESE

#define  RADIO_CHANNEL 		2
#define  RADIO_DATARATE 	DATA_RATE_250K
#define  RADIO_ADDRESS 		0x123456789AULL

#define  FLIGHT_CTRL_MODE	ALTHOLD_MODE
#define  FLIGHT_MODE		HEAD_LESS
#define  FLIGHT_SPEED		LOW_SPEED
#define  FLIP_SET			FLIP_DISABLE


enum ctrlMode
{
    ALTHOLD_MODE,
    MANUAL_MODE,
    THREEHOLD_MODE,
};

enum flightMode
{
    HEAD_LESS,
    X_MODE,
};

enum flightSpeed
{
    LOW_SPEED,
    MID_SPEED,
    HIGH_SPEED,
};

enum flipEnable
{
    FLIP_ENABLE,
    FLIP_DISABLE,
};

enum oledOnoff
{
    OLED_ON,
    OLED_OFF,
};

enum oledLight
{
    LIGHT_1,
    LIGHT_2,
    LIGHT_3,
    LIGHT_4,
    LIGHT_5,
    LIGHT_6,
    LIGHT_7,
    LIGHT_8,
    LIGHT_9,
    LIGHT_10,
};

enum oledEffect
{
    EFFECT_1,
    EFFECT_2,
    EFFECT_3,
    EFFECT_4,
    EFFECT_5,
};

enum oledDir
{
    OLED_DIR_N,
    OLED_DIR_I,
};

enum language
{
    SIMPLE_CHINESE,
    ENGLISH,
    COMPLEX_CHINESE,
};

/*�������ýṹ*/
typedef struct {
    enum ctrlMode ctrl;
    enum flightMode mode;
    enum flightSpeed speed;
    enum flipEnable flip;
} flightConfig_t;

typedef struct {
    enum oledOnoff oledonoff;
    enum oledLight oledlig;
    enum oledEffect oledeff;
    enum oledDir oledfir;
} oledConfig_t;

/*�������ýṹ*/
typedef struct {
    uint8_t channel;
    enum nrfRate dataRate;
    uint32_t addressHigh;/*ͨ�ŵ�ַ��4�ֽ�*/
    uint32_t addressLow;	/*ͨ�ŵ�ַ��4�ֽ�*/
} radioConfig_t;

/*����΢���ṹ*/
typedef __packed struct {
    float pitch;
    float roll;
} trim_t;

/*��������ṹ*/
typedef struct {
    uint8_t version;             /*����汾��*/
    enum language language; /*��ʾ����*/
    radioConfig_t radio;    /*�������ò���*/
    flightConfig_t flight;  /*�������ò���*/
    joystickParam_t jsParam;/*ҡ��У׼����*/
    trim_t trim;            /*��̬΢������*/
    oledConfig_t oledconf;
    
    uint8_t cksum;               /*У��*/
} configParam_t;


extern configParam_t configParam;


void configParamInit(void);
void configParamTask(void* param);
void writeConfigParamToFlash(void);
void configParamReset(void);

#endif

