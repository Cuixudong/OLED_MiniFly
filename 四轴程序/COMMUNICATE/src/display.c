#include "sys.h"
#include <string.h>
#include <stdbool.h>
#include "config.h"
#include "system.h"
#include "led.h"
#include "spi.h"
#include "oled.h"
#include "ledseq.h"
#include "power_control.h"
#include "commander.h"
#include "radiolink.h"
#include "remoter_ctrl.h"
#include "stabilizer.h"
#include "sensfusion6.h"
#include "display.h"

/*FreeRTOS相关头文件*/
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

static bool isInit = false;
__IO oledMode_t oled_mode = {0};

void displayInit(void)
{
    if(isInit) return;
    
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    GPIO_InitStructure.GPIO_Pin = OLED_CS_Pin;  //CS
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(OLED_CS_GPIO_Port, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = OLED_RST_Pin;              //RST
    GPIO_Init(OLED_RST_GPIO_Port, &GPIO_InitStructure);
    
    GPIO_InitStructure.GPIO_Pin = OLED_DC_Pin;              //DC
    GPIO_Init(OLED_DC_GPIO_Port, &GPIO_InitStructure);
    
    spi2Init();
    isInit = true;
}

static void registerWrite(uint8_t reg, uint8_t value)
{
    // 最高位为1 写寄存器
    reg |= 0x80u;

    spiBeginTransaction();
    delay_us(50);
    spiExchange(1, &reg, &reg);
    delay_us(50);
    spiExchange(1, &value, &value);
    delay_us(50);

    spiEndTransaction();
    delay_us(200);
}
static uint8_t registerRead(uint8_t reg)
{
    uint8_t data = 0;

    // 最高位为0 读寄存器
    reg &= ~0x80u;

    spiBeginTransaction();

    delay_us(50);
    spiExchange(1, &reg, &reg);
    delay_us(500);
    spiExchange(1, &data, &data);
    delay_us(50);

    spiEndTransaction();
    delay_us(200);

    return data;
}

extern void main_3d_loop(float x,float y,float z);

__IO uint8_t oled_mod[4] = {1,8,0,0};

static void display_msg(void)
{
    char str[32];
    int i,dat;
    static uint8_t mo = 0;
//    MiniFlyMsg_t mf_Msg;
//    mf_Msg.version = configParam.version;//参数版本
//    mf_Msg.mpu_selfTest = getIsMPU9250Present();//9250自检
//    mf_Msg.baro_slfTest = getIsBaroPresent();//气压自检
//    mf_Msg.isCanFly = getIsCalibrated();//重力方向，可飞标志
//    
//    float bat = pmGetBatteryVoltage();//电池电压
//    bool flyable = getFlyable();//解锁标志
//    
//    Axis3i16 acc;//原始加速度
//    Axis3i16 gyro;//原始角速度
//    Axis3i16 mag;//原始磁场
//    getSensorRawData(&acc, &gyro, &mag);
//    
//    Axis3f acc1,vel,pos;//浮点加速度、角速度、位置
//    getStateData(&acc1, &vel, &pos);
    
    motorPWM_t motorPWM;//电机PWM
    getMotorPWM(&motorPWM);
    
    attitude_t attitude;//姿态角
    getAttitudeData(&attitude);
//    int baroData = getBaroData();//气压
    
//    sprintf(str,"三轴姿态角: ");
//    OLED_Show_Str(0, 0,str,16,1);
//    sprintf(str,"X:%.1f   ",attitude.roll);
//    OLED_Show_Str(0,16,str,16,1);
//    sprintf(str,"Y:%.1f   ",attitude.pitch);
//    OLED_Show_Str(0,32,str,16,1);
//    sprintf(str,"Z:%.1f   ",attitude.yaw);
//    OLED_Show_Str(0,48,str,16,1);
    
    switch(oled_mode._oled_mode)
    {
        case OLED_CMD_OFF:
            OLED_Display_Off();
            break;
        case OLED_CMD_ON:
            OLED_Display_On();
            break;
        case OLED_CMD_DIR_N:
            OLED_SetDir(3);
            break;
        case OLED_CMD_DIR_I:
            OLED_SetDir(2);
            break;
        case OLED_CMD_LIGHT_1:
        case OLED_CMD_LIGHT_2:
        case OLED_CMD_LIGHT_3:
        case OLED_CMD_LIGHT_4:
        case OLED_CMD_LIGHT_5:
        case OLED_CMD_LIGHT_6:
        case OLED_CMD_LIGHT_7:
        case OLED_CMD_LIGHT_8:
        case OLED_CMD_LIGHT_9:
        case OLED_CMD_LIGHT_10:
            OLED_SetContrast(255 - ((OLED_CMD_LIGHT_10 - oled_mode._oled_mode) & 0x0F) * 25);
            break;
        case OLED_CMD_EFF_1:
        case OLED_CMD_EFF_2:
        case OLED_CMD_EFF_3:
        case OLED_CMD_EFF_4:
            mo = oled_mode._oled_mode - OLED_CMD_EFF_1;
            break;
    }
    oled_mode._oled_mode = 0;
    
    if(oled_mod[0] != 0)/*OLED打开*/
    {
        OLED_Clear(0);
        switch(oled_mod[3])
        {
            case 0:
                sprintf(str,"三轴姿态角:");
                OLED_Show_Str(0, 0,str,16,1);
                sprintf(str,"X:%.1f   ",attitude.roll);
                OLED_Show_Str(10,16,str,16,1);
                sprintf(str,"Y:%.1f   ",attitude.pitch);
                OLED_Show_Str(10,32,str,16,1);
                sprintf(str,"Z:%.1f   ",attitude.yaw);
                OLED_Show_Str(10,48,str,16,1);
            
                sprintf(str,"油门");
                OLED_Show_Str(96, 0,str,16,1);
                sprintf(str,"%5d",motorPWM.m1);
                OLED_Show_Str(98,16,str,12,1);
                sprintf(str,"%5d",motorPWM.m2);
                OLED_Show_Str(98,28,str,12,1);
                sprintf(str,"%5d",motorPWM.m3);
                OLED_Show_Str(98,40,str,12,1);
                sprintf(str,"%5d",motorPWM.m4);
                OLED_Show_Str(98,52,str,12,1);
                break;
            case 1:
                #if 0
                for(i=0;i<3;i++)
                {
                    OLED_DrawRectangle(5,14 + i * 13,122,14 + i * 13 + 10,1);
                }
                OLED_DrawRectangle(  0, 0,60 ,10,1);
                OLED_DrawRectangle( 70, 0,127,10,1);
                OLED_DrawRectangle(  0,53,60 ,63,1);
                OLED_DrawRectangle( 70,53,127,63,1);
                #endif
                for(i=0;i<3;i++)
                {
                    if(i == 0)
                    {
                        dat = 2*(int)attitude.roll;
                    }
                    else if(i == 1)
                    {
                        dat = 2*(int)attitude.pitch;
                    }
                    else if(i == 2)
                    {
                        dat = (int)attitude.yaw;
                    }
                    if(dat > 180)dat = 180;if(dat<-180)dat=-180;
                    if(dat < 0)
                    {
                        OLED_Fill(63 + dat * 62 / 180,14 + i * 13,63,14 + i * 13 + 10,1);
                    }
                    else if(dat > 0)
                    {
                        OLED_Fill(62,14 + i * 13,62 + dat * 62 / 180,14 + i * 13 + 10,1);
                    }
                    else
                    {
                        OLED_Fill(62,14 + i * 13,63,14 + i * 13 + 10,1);
                    }
                }
                OLED_DrawRectangle(  0, 0,motorPWM.m4 * 62 / 65536,10,1);
                OLED_DrawRectangle( 127-motorPWM.m1 * 62 / 65536, 0,127,10,1);
                OLED_DrawRectangle(  0,53,motorPWM.m3 * 62 / 65536 ,63,1);
                OLED_DrawRectangle( 127-motorPWM.m2 * 62 / 65536,53,127,63,1);
                break;
            case 2:
            case 3:
                sprintf(str,"姿态角:");
                OLED_Show_Str(0, 0,str,16,1);
                sprintf(str,"X:%d   ",(int)attitude.roll);
                OLED_Show_Str(0,16,str,16,1);
                sprintf(str,"Y:%d   ",(int)attitude.pitch);
                OLED_Show_Str(0,32,str,16,1);
                sprintf(str,"Z:%d   ",(int)attitude.yaw);
                OLED_Show_Str(0,48,str,16,1);
            
                main_3d_loop(attitude.pitch,-attitude.roll,attitude.yaw);
                break;
            default:
                break;
        }
    }
}

void displayTask(void *param)   /* 显示任务 */
{
    u32 tickCount;

    tickCount = getSysTickCnt();

    vTaskDelay(500);
    displayInit();
    vTaskDelay(40);
    OLED_Init();
    OLED_Show_Str(0,0,"正常模式OLED",16,1);
    OLED_Refresh_Gram();
    
    while(1)
    {
        vTaskDelay(30);
        tickCount = getSysTickCnt();
        display_msg();
        OLED_Refresh_Gram();
    }
}
