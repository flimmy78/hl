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

#include <project.h>

#define HIGH    1
#define LOW     0

#define LOCK_LED_OPEN   LED_Ctrl_Write(HIGH)        //锁头灯亮
#define LOCK_LED_CLOSE  LED_Ctrl_Write(LOW)         //锁头灯灭

#define BEEP_OPEN       Beep_Ctrl_Write(HIGH)       //蜂鸣器打开
#define BEEP_CLOSE      Beep_Ctrl_Write(LOW)        //蜂鸣器关闭

#define RED_ON          LED_RED_Write(LOW)         //红灯亮    
#define RED_OFF         LED_RED_Write(HIGH)          //红灯灭

#define GREEN_ON        LED_GREEN_Write(LOW)       //绿灯亮
#define GREEN_OFF       LED_GREEN_Write(HIGH)        //绿灯灭


/****报警事件*******/
#define EVENT_0				0			//正常状态
#define EVENT_1				1			//蜂鸣器：嘀
#define EVENT_2				2			//蜂鸣器：嘀滴
#define EVENT_3				3			//蜂鸣器：嘀嘀滴
#define EVENT_4				4			//蜂鸣器：嘀嘀，LED灯：闪烁两次
#define EVENT_5             5           //蜂鸣器：滴滴滴.....

#define HALL_CLOSE    0                 //门磁合适，检测到数据
#define HALL_OPEN     1                 //门磁断开，未检测到

#define DELAY_30S       30000
#define DELAY_10S       10000
#define DELAY_5S        5000
#define DELAY_2S        2000
#define DELAY_1S        1000


#define SysCfg_FLASH_ROW       (CY_FLASH_NUMBER_ROWS - 2u)
#define SysCfg_FLASH_ADDR      (SysCfg_FLASH_ROW * CY_FLASH_SIZEOF_ROW)

typedef struct
{
    uint8 ManageKey[16];            //管理中心密钥
    uint8 DeviceID[4];              //锁设备号
    uint8 root_key[8];              //根密钥
    uint8 ctrl_key[8];              //控制密钥
    uint8 IDChangeFlag;             //设备号修改标志
    uint8 sum;                      //校验码
}SYSTEM_CFG;
extern SYSTEM_CFG System_Config;    //锁系统参数
extern SYSTEM_CFG Sys_cfg;
extern const uint8 Manage_Key[16];
extern const uint8 LockIdentify[16];

typedef struct
{
    uint8 DeviceID[4];              //设备号
    uint8 Version[2];               //版本号
    uint8 InitState;                //初始化状态
    uint8 LockKey[8];               //锁密钥
}LOCK_INFO; 
extern LOCK_INFO Lock_Info;



/*******************************************************************************
** 延时计数器结构
********************************************************************************/
typedef struct
{
    uint16  Alarm_Count;            //报警状态计时器

    uint16  Ask_Lock_Delay;         //请求锁信息超时
    uint8   NoLock_Count;           //
    
	uint8   Delay_1ms;         		//系统时间秒的统计4次为1秒
    uint16   Delay_1s;               //延时1S
    uint16   Delay_1min;             //延时1分钟
}DelayTime;
extern DelayTime  Delay_Time;

/*******************************************************************************
** 各类标志位
*******************************************************************************/
typedef struct
{
    unsigned Alarm_Work_Step        : 3;        //声光报警工作状态 
    unsigned Open_Lock_Success      : 1;        //请求锁成功
    
    unsigned Begin_Ask_Lock         : 1;        //开始请求锁信息
    unsigned : 3;
}FLAG;
extern FLAG  Flag;

void Power_Off(void);
void Alarm_Event(uint8 Event);
void Write_Flash(uint8* Data,uint8 Length);
void Read_Flash(uint32 Addr,uint8* Data,uint8 Length);

void Load_Config(void);
/* [] END OF FILE */
