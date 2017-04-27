/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "app_lock.h"
#include "RC4.h"
#include "app_protocol.h"
#include "app_Com.h"
#include <string.h>
#include <CyFlash.h>

const uint8 LockIdentify[16] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F};
const uint8 Manage_Key[16] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00};



DelayTime  Delay_Time = {};
FLAG  Flag = {};
SYSTEM_CFG System_Config = {};
LOCK_INFO Lock_Info = {};


/***********************************************************
 * @function_name: void Alarm_Event(u8* Data)
 * @function_file: Dr_Alarm.c
 * @描  述： 报警事件主程序
 *
 * @参  数： 报警事件
 * @返  回： 无
 * @作  者： ZhangQun (2014-9-2)
 *---------------------------------------------------------
 * @修改人： ZhangQun (2014-9-2)
***********************************************************/
void Alarm_Event(uint8 Event)
{
   switch (Event)
    {
        case EVENT_1:	//绿灯亮1S
            if (Delay_Time.Alarm_Count == 0)
            {
                GREEN_OFF;
            }
            Delay_Time.Alarm_Count ++;
            if(Delay_Time.Alarm_Count > 1000)
            {
                Delay_Time.Alarm_Count = 0;
                GREEN_ON;
                Flag.Alarm_Work_Step = EVENT_0;
            }
            break;

        case EVENT_2:   //蜂鸣器：嘀滴
            if (  (Delay_Time.Alarm_Count == 0) 
               || (Delay_Time.Alarm_Count == 200) )
            {
                GREEN_OFF;
                PWM_Start();
            }
            if (Delay_Time.Alarm_Count == 100)
            {
                GREEN_ON;
                PWM_Stop();
            }            
            Delay_Time.Alarm_Count ++;
            if (Delay_Time.Alarm_Count >= 300)
            {
                Delay_Time.Alarm_Count = 0;
                GREEN_ON;
                PWM_Stop();
                Flag.Alarm_Work_Step = EVENT_0;            
            }           
            break;

        case EVENT_3:       //蜂鸣器 滴滴滴
            if (  (Delay_Time.Alarm_Count == 0) 
               || (Delay_Time.Alarm_Count == 200)
               || (Delay_Time.Alarm_Count == 400))
            {
                BEEP_OPEN;
            }
            if (  (Delay_Time.Alarm_Count == 100)
               || (Delay_Time.Alarm_Count == 300) ) 
            {
                BEEP_CLOSE;
            }            
            Delay_Time.Alarm_Count ++;
            if (Delay_Time.Alarm_Count >= 500)
            {
                Delay_Time.Alarm_Count = 0;
                BEEP_CLOSE;
                Flag.Alarm_Work_Step = EVENT_0;            
            }              
            break;

        case EVENT_4:
            if (  (Delay_Time.Alarm_Count == 0) 
               || (Delay_Time.Alarm_Count == 200) )
            {
                BEEP_OPEN;
            }
            if (Delay_Time.Alarm_Count == 100)
            {
                BEEP_CLOSE;
            }     
            Delay_Time.Alarm_Count ++;
            if (Delay_Time.Alarm_Count >= 300)
            {
                Delay_Time.Alarm_Count = 0;
                BEEP_CLOSE;
                Flag.Alarm_Work_Step = EVENT_0;            
            }    
            break;      
            
        case EVENT_5:
            if((Delay_Time.Alarm_Count % 100) == 0)
            {
                if(((Delay_Time.Alarm_Count / 100) % 2) == 0)
                {
                    BEEP_OPEN;
                }
                else
                {
                    BEEP_CLOSE;
                }
            }
            Delay_Time.Alarm_Count ++;
            if(Delay_Time.Alarm_Count >=1000)
            {
                Delay_Time.Alarm_Count = 0;
            }
            break;
			
        case EVENT_0:	//正常事件
        default:
            Delay_Time.Alarm_Count = 0;
            BEEP_CLOSE;
            break;
    }
}


/***********************************************************
 * @function_name: void Write_Flash(uint32 Addr,uint8* Data,uint8 Length)
 * @描  述： 参数存储
************************************************************/
void Write_Flash(uint8* Data,uint8 Length)
{
    uint8 write_buff[0x80] = {0x00};
    memcpy(write_buff,Data,Length);
    CySysFlashWriteRow(SysCfg_FLASH_ROW, write_buff);
}

/***********************************************************
 * @function_name: void Read_Flash(uint32 Addr,uint8* Data,uint8 Length)
 * @描  述： 参数存储
************************************************************/
void Read_Flash(uint32 Addr,uint8* Data,uint8 Length)
{
    uint8 i=0;
    for (i = 0; i < Length; i++)
    {
        *Data = (*((uint8 *) (Addr + i)));
        Data ++;
    }
}

/***********************************************************
 * @function_name: void Power_Off(void)
 * @描  述： 关机程序
************************************************************/
void Power_Off(void)
{
    Delay_Time.Delay_1s ++;
    if(Delay_Time.Delay_1s > 1000)       //1S
    {
        Delay_Time.Delay_1s = 0;
        Delay_Time.Delay_1min ++;
        if(Delay_Time.Delay_1min >= 120)
        {
            Delay_Time.Delay_1min = 0;
            POWERON_OUT_Write(LOW);
        }
    }
}

/***********************************************************
 * @function_name: void Load_Config(void)
 * @描  述： 参数存储
************************************************************/
void Load_Config(void)
{
    uint8 sum;
    Read_Flash(SysCfg_FLASH_ADDR,(uint8 *)&System_Config,sizeof(System_Config));
    sum = CRC_Sum((uint8 *)&System_Config,sizeof(System_Config)-1);
    if(sum != System_Config.sum)
    {
        memcpy(System_Config.ManageKey,Manage_Key,16);
        System_Config.DeviceID[0] = 0x01;
        System_Config.DeviceID[1] = 0x02;
        System_Config.DeviceID[2] = 0x03;
        System_Config.DeviceID[3] = 0x04;
        System_Config.sum = CRC_Sum((uint8 *)&System_Config,sizeof(System_Config)-1);
        Write_Flash((uint8 *)&System_Config,sizeof(System_Config));
    }
}




/* [] END OF FILE */
