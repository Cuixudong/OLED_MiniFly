#include "string.h"
#include <math.h>
#include "sensfusion6.h"
#include "remoter_ctrl.h"
#include "config_param.h"
#include "commander.h"
#include "flip.h"
#include "radiolink.h"
#include "sensors.h"
#include "pm.h"
#include "stabilizer.h"
#include "module_mgt.h"
#include "ledring12.h"
#include "vl53lxx.h"

/*FreeRTOS���ͷ�ļ�*/
#include "FreeRTOS.h"
#include "task.h"

/********************************************************************************
 * ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
 * ALIENTEK MiniFly
 * ң����������������
 * ����ԭ��@ALIENTEK
 * ������̳:www.openedv.com
 * ��������:2017/5/12
 * �汾��V1.3
 * ��Ȩ���У�����ؾ���
 * Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
 * All rights reserved
 *
 * �޸�˵��:
 * �汾V1.3 �����ϵ�У׼ͨ�����ϴ�΢����Ϣ��
********************************************************************************/

ctrlVal_t remoterCtrl;/*���͵�commander��̬��������*/
static MiniFlyMsg_t mf_Msg;

static u8 reSendTimes = 3;	/*΢���ط�����*/

/*����������Ϣ*/
void sendMsgACK(void)
{
    mf_Msg.version = configParam.version;
    mf_Msg.mpu_selfTest = getIsMPU9250Present();
    mf_Msg.baro_slfTest = getIsBaroPresent();
    mf_Msg.isCanFly = getIsCalibrated();
    if(mf_Msg.isCanFly == true)	/*У׼ͨ��֮����΢��ֵ*/
    {
        if(reSendTimes > 0) /*΢���ط�����*/
        {
            reSendTimes--;
            mf_Msg.trimPitch = configParam.trimP;
            mf_Msg.trimRoll = configParam.trimR;
        }
    }
    mf_Msg.isLowpower = getIsLowpower();

    atkp_t p;
    p.msgID = UP_REMOTER;
    p.dataLen = sizeof(mf_Msg)+1;
    p.data[0] = ACK_MSG;
    memcpy(p.data+1, &mf_Msg, sizeof(mf_Msg));
    radiolinkSendPacketBlocking(&p);
}

/*ң�����ݽ��մ���*/
void remoterCtrlProcess(atkp_t* pk)
{
    if(pk->data[0] == REMOTER_CMD)
    {
        switch(pk->data[1])
        {
        case CMD_FLIGHT_LAND:
            if(getCommanderKeyFlight() != true)
            {
                setCommanderKeyFlight(true);
                setCommanderKeyland(false);
            }
            else
            {
                setCommanderKeyFlight(false);
                setCommanderKeyland(true);
            }
            break;

        case CMD_EMER_STOP:
            setCommanderKeyFlight(false);
            setCommanderKeyland(false);
            break;

        case CMD_FLIP:
            setFlipDir(pk->data[2]);
            break;

        case CMD_GET_MSG:
            sendMsgACK();
            break;

        case CMD_POWER_MODULE:
            break;
        case CMD_LEDRING_EFFECT:
            break;
        case CMD_POWER_VL53LXX:
            break;
        case CMD_OLED_MODE:
            setOledMode(pk->data[2]);
            break;
        }
    }
    else if(pk->data[0] == REMOTER_DATA)
    {
        remoterData_t remoterData = *(remoterData_t*)(pk->data+1);

        remoterCtrl.roll = remoterData.roll;
        remoterCtrl.pitch = remoterData.pitch;
        remoterCtrl.yaw = remoterData.yaw;
        remoterCtrl.thrust = remoterData.thrust * 655.35f;
        remoterCtrl.trimPitch = remoterData.trimPitch;
        remoterCtrl.trimRoll = remoterData.trimRoll;

        setCommanderCtrlMode(remoterData.ctrlMode);
        setCommanderFlightmode(remoterData.flightMode);
        flightCtrldataCache(ATK_REMOTER, remoterCtrl);
    }
}

