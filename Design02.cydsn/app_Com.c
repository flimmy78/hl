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
#include "app_Com.h"
#include "app_protocol.h"
#include "app_lock.h"
#include "Rc4.h"

ComArray Com_Array;
uint8 App_Key[8];
uint8 Own_Key[8] = {0x01,0x03,0x05,0x07,0x05,0x03,0x01,0x07};
uint8 Target_Key[8];
/***********************************************
* 函数名：void Com_Recv_Prov(void)
* 描述  ：处理串口接收指令
***********************************************/
void Com_Recv_Prov(void)
{
    uint8 Cmd;
    uint16 Rec_CRC,Check_CRC;
       
    if(Com_Array.Rx_Flag)
    {
        Com_Array.Rx_Flag = 0;
        Delay_Time.Delay_1s = 0;
        Delay_Time.Delay_1min = 0;
        Rec_CRC = Com_Array.Rx_buff[Com_Array.Rx_Length - 2] *256 + Com_Array.Rx_buff[Com_Array.Rx_Length - 1];
        Check_CRC = comCalCRC16(Com_Array.Rx_buff,Com_Array.Rx_Length - 2);
        if(Rec_CRC == Check_CRC)
        {
            Cmd = Com_Array.Rx_buff[0];
            switch(Cmd)
            {
                case REQUEST_DEVICE_CMD:    //  请求设备信息
                    Delay_Time.Ask_Lock_Delay  = 0;
                    Flag.Begin_Ask_Lock = 0;
                    Delay_Time.NoLock_Count = 0;
                    memcpy(Lock_Info.DeviceID,Com_Array.Rx_buff+3,4);
                    memcpy(Lock_Info.Version,Com_Array.Rx_buff+7,2);
                    Lock_Info.InitState = Com_Array.Rx_buff[9];
                    if(Flag.Open_Lock_Success == 0)     
                    {
                        packetTXStep = Send_Lock_Info;
                    }
                    break;
                
                case CHECK_CODE_CMD:
                    Com_Array.Tx_State = SWAP_KEY;
                    break;
                
                case SWAP_KEY_CMD:
                    rc4_encrypt(Own_Key,KEY_LEN,Com_Array.Rx_buff + 2,10);		//key1解密
                    memcpy(Target_Key,&Com_Array.Rx_buff[2],8);
                    Com_Array.Tx_State = REQUEST_INDEX;
                    break;
                
                case REQUEST_LOCK_INDEX:    // 请求锁检索号
                    Com_Array.Tx_State = OPEN_LOCK;
                    break;
                
                case OPEN_LOCK_CMD:
                    Com_Array.Tx_State = IDLE;
                    packetTXStep = Reply_OpenLock;
                    Flag.Alarm_Work_Step = EVENT_2;
                    Flag.Open_Lock_Success = 1;
                    break;
     
                case SET_LOCK_ID:
                    break;
                    
                default:
                    break;
            }
        }
        memset(Com_Array.Rx_buff,0,sizeof(Com_Array.Rx_buff));
    }
    
    if(Com_Array.Rx_Delay > 100)
    {
        Com_Array.Rx_Delay = 0;
        Com_Array.Rx_Begin_Flag = 0;
        Com_Array.Rx_Count = 0;
        memset(Com_Array.Rx_buff,0,sizeof(Com_Array.Rx_buff));
    }
    
    if(Flag.Begin_Ask_Lock)
    {
        Delay_Time.Ask_Lock_Delay ++;
        if(Delay_Time.Ask_Lock_Delay > 100) //100秒没有应答
        {
            Delay_Time.Ask_Lock_Delay = 0;
            Delay_Time.NoLock_Count ++;
            //Flag.Open_Lock_Success = 0;
            Flag.Begin_Ask_Lock = 0;
        }
        if(Delay_Time.NoLock_Count >=3)
        {
            Delay_Time.NoLock_Count = 0;
            Flag.Open_Lock_Success = 0;
        }
    }
}

/***********************************************
* 函数名：void Com_Send_Prov(void)
* 描述  ：串口发送数据
***********************************************/
void Com_Send_Prov(void)
{
    switch (Com_Array.Tx_State)
    {
    case IDLE:	//空闲
        break;   
        
    case RE_REQUEST:
        Com_Array.Tx_Wait ++;
        if(Com_Array.Tx_Wait >= 300)      //500ms查询一次
        {
            Com_Array.Tx_Wait  = 0;
            Request_Device_Info(); 
            Flag.Begin_Ask_Lock = 1;
        }
        break;
        
    case RE_CHECKCODE:
        Com_Array.Tx_Wait ++;
        if (Com_Array.Tx_Wait  >= 100)
        {
            Com_Array.Tx_Wait  = 0;
            Check_Code(); 
        }
        break;        
        
    case SEND_DELAY:	//正在发送等待
        Com_Array.Tx_Wait ++;
        if (Com_Array.Tx_Wait  >= 1000)
        {
            Com_Array.Tx_Wait  = 0;
            Com_Array.Tx_State = RE_SEND;
        }
        break;

    case RE_SEND:	//重发
        Com_Array.Tx_Wait ++;
        if (Com_Array.Tx_Wait  >= 1000)
        {
            Com_Array.Tx_Wait = 0;
            if (Com_Array.Tx_Count < 3)
            {
                Com_Array.Tx_Count ++;
                Send_Com(Com_Array.Tx_buff,Com_Array.Tx_Length);
            }
            else
            {
                Com_Array.Tx_Count = 0;
                Com_Array.Tx_State = RE_CHECKCODE;
            }
        }
        break;
        
    case CHECK_CODE:        //对码
        Check_Code();
        Com_Array.Tx_State = SEND_DELAY;        
        break;
        
    case SWAP_KEY:          //交换密钥
        Swap_Key();
        Com_Array.Tx_State = SEND_DELAY;        
        break;
        
    case REQUEST_INDEX:     //请求索引号
        Request_Index();
        Com_Array.Tx_State = SEND_DELAY;        
        break;
        
    case OPEN_LOCK:         //开锁
        Open_Lock();
        Com_Array.Tx_State = SEND_DELAY;       
        break;
             
    default:
        break;
        
    }
}

/***********************************************
* 函数名：void Request_Device_Info(void)
* 描述  ：请求锁的设备信息
***********************************************/
void Request_Device_Info(void)
{
    uint16 crc;
    Com_Array.Tx_buff[0] = REQUEST_DEVICE_CMD;
    Com_Array.Tx_buff[1] = 0;
    crc = comCalCRC16(Com_Array.Tx_buff,2);
    
    Com_Array.Tx_buff[2] = crc / 256;
    Com_Array.Tx_buff[3] = crc % 256;   
    Com_Array.Tx_Length = 4;
    Send_Com(Com_Array.Tx_buff,Com_Array.Tx_Length);
}

/***********************************************
* 函数名：void Check_Code(void)
* 描述  ：对码
***********************************************/
void Check_Code(void)
{
    uint16 crc;
    Com_Array.Tx_buff[0] = CHECK_CODE_CMD;
    Com_Array.Tx_buff[1] = 2;
    crc = comCalCRC16(Com_Array.Tx_buff,2);					//内部效验码
    Com_Array.Tx_buff[2] = crc / 256;
    Com_Array.Tx_buff[3] = crc % 256; 
    
    rc4_encrypt(System_Config.ManageKey,MKEY_LEN,Com_Array.Tx_buff + 2, 2);			//管理中心密钥加密
    crc = comCalCRC16(Com_Array.Tx_buff,4);					//外部校验
    Com_Array.Tx_buff[4] = crc / 256;
    Com_Array.Tx_buff[5] = crc % 256;     
    Com_Array.Tx_Length = 6;    
    Send_Com(Com_Array.Tx_buff,Com_Array.Tx_Length);
}

/***********************************************
* 函数名：void Swap_Key(void)
* 描述  ：交换密钥
***********************************************/
void Swap_Key(void)
{
    uint16 crc;

    Com_Array.Tx_buff[0] = SWAP_KEY_CMD;
    Com_Array.Tx_buff[1] = 11;
    memcpy(Com_Array.Tx_buff + 2, Own_Key, 8);
    Com_Array.Tx_buff[10] = 0; 
    crc = comCalCRC16(Com_Array.Tx_buff,11);					//内部效验码
    Com_Array.Tx_buff[11] = crc / 256;
    Com_Array.Tx_buff[12] = crc % 256; 
    
    rc4_encrypt(System_Config.ManageKey,MKEY_LEN,Com_Array.Tx_buff + 2, 11);			//管理中心密钥加密
    crc = comCalCRC16(Com_Array.Tx_buff,13);					//外部校验
    Com_Array.Tx_buff[13] = crc / 256;
    Com_Array.Tx_buff[14] = crc % 256;     
    Com_Array.Tx_Length = 15;    
    Send_Com(Com_Array.Tx_buff,Com_Array.Tx_Length);    
}

/***********************************************
* 函数名：void Request_Index(void)
* 描述  ：请求检索号
***********************************************/
void Request_Index(void)
{
    uint16 crc;
    Com_Array.Tx_buff[0] = REQUEST_LOCK_INDEX;
    Com_Array.Tx_buff[1] = 2;
    crc = comCalCRC16(Com_Array.Tx_buff,2);
    Com_Array.Tx_buff[2] = crc / 256;
    Com_Array.Tx_buff[3] = crc % 256;   
    rc4_encrypt(Target_Key,KEY_LEN,Com_Array.Tx_buff + 2, 2);
    crc = comCalCRC16(Com_Array.Tx_buff,4);
    Com_Array.Tx_buff[4] = crc / 256;
    Com_Array.Tx_buff[5] = crc % 256;      
    Com_Array.Tx_Length = 6;
    Send_Com(Com_Array.Tx_buff,Com_Array.Tx_Length);
}

/***********************************************
* 函数名：void Open_Lock(void)
* 描述  ：请求检索号
***********************************************/
void Open_Lock(void)
{
    uint16 crc;
    uint8 Time[7] = {0x07,0xe0,0x0a,0x09,0x12,0x20,0x00};
    
    Com_Array.Tx_buff[0] = OPEN_LOCK_CMD;
    Com_Array.Tx_buff[1] = 32;
    
    memcpy(Com_Array.Tx_buff + 2,LockIdentify,16);
    memcpy(Com_Array.Tx_buff + 18,Time,7);
    memcpy(Com_Array.Tx_buff + 25,System_Config.DeviceID,4);

    Com_Array.Tx_buff[25] = 0x00;
    Com_Array.Tx_buff[26] = 0x00;
    Com_Array.Tx_buff[31] = 0x01;
    crc = comCalCRC16(Com_Array.Tx_buff,32);
    Com_Array.Tx_buff[32] = crc / 256;
    Com_Array.Tx_buff[33] = crc % 256;   
    
    
    rc4_encrypt(Target_Key,KEY_LEN,Com_Array.Tx_buff + 2, 32);
    crc = comCalCRC16(Com_Array.Tx_buff,34);
    Com_Array.Tx_buff[34] = crc / 256;
    Com_Array.Tx_buff[35] = crc % 256;      
    Com_Array.Tx_Length = 36;
    Send_Com(Com_Array.Tx_buff,Com_Array.Tx_Length);    
}


/***********************************************
* 函数名：void Set_Lock_ID(void)
* 描述  ：请求锁的设备信息
***********************************************/
void Set_Lock_ID(void)
{
    uint16 crc;
    Com_Array.Tx_buff[0] = SET_LOCK_ID;
    Com_Array.Tx_buff[1] = 4;
    
    memcpy(Com_Array.Tx_buff + 2,Lock_Info.DeviceID,4);
    
    crc = comCalCRC16(Com_Array.Tx_buff,6);
    
    Com_Array.Tx_buff[7] = crc / 256;
    Com_Array.Tx_buff[8] = crc % 256;   
    Com_Array.Tx_Length = 8;
    Send_Com(Com_Array.Tx_buff,Com_Array.Tx_Length);
}

/***********************************************
* 函数名：void Send_Com(uint8 *TX_Buffer,uint8 Length)
* 描述  ：串口发送数据
***********************************************/
void Send_Com(uint8 *TX_Buffer,uint8 Length)
{
    uint8 i;
    Com_Array.Tx_Begin = 1;
    
    for(i=0; i<Length; i++ )
    {
        UART_UartPutChar(TX_Buffer[i]);
    }
    Com_Array.Tx_Wait = 0;
}



/* [] END OF FILE */
