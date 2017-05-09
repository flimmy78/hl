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
#include "app_protocol.h"
#include "app_ble.h"
#include "app_uart.h"
#include "app_Com.h"
#include <string.h>
#include <stdlib.h>
#include "Rc4.h"
#include "md5.h"

uint8 packetTX[20];
uint8 packetTXStep = 0;
uint8 recv_buff[40];
uint8 AppKey[8];

#define LOCK_OPEN_FLAG_SET 3
static  uint8  lock_open_flag = 0; //key_touch_lock
static  uint8  lock_flag = 0;      //
static  uint16 lock_timeflow = 0;  //key_touch_lock

typedef struct _KEY_STR
{
    //uint8 root_key[8]; //根密钥       a0a1a2a3a4a5a6a7
    //uint8 ctrl_key[8]; //控制密钥     b0b1b2b3b4b5b6b7
    uint8 dynamic_key[8]; //动态密钥  
}KEY_STR; //

struct _KEY_STR key_str = {/*{0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7},\
                           {0xb0,0xb1,0xb2,0xb3,0xb4,0xb5,0xb6,0xb7,},*/
                           {0}};

/***********************************************
* 函数名：void SendNotification(void)
* 描述  ：蓝牙发送函数
***********************************************/
void SendNotification_zx(uint8 Lenth)
{
    /* Create a new notification packet */
    CYBLE_GATTS_HANDLE_VALUE_NTF_T notificationPacket;
    notificationPacket.attrHandle = CYBLE_CUSTOM_SERVICE_RX_FROM_APP_CHAR_HANDLE;
    notificationPacket.value.val = packetTX;   
    notificationPacket.value.len = Lenth;
    /* Report data to BLE component */
    CyBle_GattsNotification(cyBle_connHandle, &notificationPacket);
}

/***********************************************
* 函数名：void SendNotification(void)
* 描述  ：蓝牙发送函数
***********************************************/
void SendNotification(void)
{
    /* Create a new notification packet */
    CYBLE_GATTS_HANDLE_VALUE_NTF_T notificationPacket;
    notificationPacket.attrHandle = CYBLE_CUSTOM_SERVICE_RX_FROM_APP_CHAR_HANDLE;
    notificationPacket.value.val = packetTX;   
    notificationPacket.value.len = 20;
    /* Report data to BLE component */
    CyBle_GattsNotification(cyBle_connHandle, &notificationPacket);
 
}

/***********************************************
* 函数名：void Send_LockInfo(void)
* 描述  ：发送锁设备信息
***********************************************/
void Send_LockInfo(void)
{
    uint8 i;
    uint16 crc;
    uint16 data_rand;
    memset(packetTX,0x00,sizeof(packetTX));
    packetTX[0] = 0x23;         //命令字
    packetTX[1] = 0;            //包号
    packetTX[2] = 15;           //长度
    
    for(i=0; i<4; i++)      //生成LOCKKEY
    {
        data_rand = rand(); 
        Lock_Info.LockKey[i*2 + 0] = data_rand / 256;
        Lock_Info.LockKey[i*2 + 1] = data_rand % 256; 
    }    
    memcpy(packetTX + 3, Lock_Info.DeviceID,15);
    rc4_encrypt(System_Config.ManageKey,MKEY_LEN,packetTX + 10,8);  //对随机密钥加密
    crc = comCalCRC16(packetTX,18);
    packetTX[18] = crc / 256;
    packetTX[19] = crc % 256; 
    
    //SendNotification();
}

/***********************************************
* 函数名：void Back_Massage_Minwen(uint8 cmd,uint8 data)
* 描述  ：返回信息-明文
***********************************************/
void Back_Massage_Minwen(uint8 cmd,uint8 data)
{
    uint16 crc;
    memset(packetTX,0x00,sizeof(packetTX));
    packetTX[0] = cmd;          //命令字
    packetTX[1] = 0;            //包号
    packetTX[2] = 1;            //长度
    packetTX[3] = data;         //结果
    
    crc = comCalCRC16(packetTX,4);
    packetTX[4] = crc / 256;
    packetTX[5] = crc % 256;   
    //SendNotification();
}


/***********************************************
* 函数名：void Send_Battery_Voltage(void)
* 描述  ：发送钥匙电压
***********************************************/
void Send_Battery_Voltage(void)
{
    uint16 vol = 3900;      //电池电压需采样计算
    uint16 crc;
    vol = Get_Adc();
    memset(packetTX,0x00,20);
    packetTX[0] = GET_BATTERY_VOLTAGE;
    packetTX[1] = 0;
    packetTX[2] = 2;
    packetTX[3] = vol/256;
    packetTX[4] = vol%256;
    crc = comCalCRC16(packetTX,5);
    packetTX[5] = crc / 256;
    packetTX[6] = crc % 256;  
    //SendNotification();
}




/***********************************************
* 函数名：void Send_Factory_Info(void)
* 描述  ：发送钥匙出厂信息
***********************************************/
void Send_Factory_Info(void)
{
    uint16 crc;
    memset(packetTX,0x00,20);
    
    packetTX[0] = REQUEST_FACTORY_INFO;
    packetTX[1] = 0;
    packetTX[2] = 13;
    packetTX[3] = BLE_NORMAL_KEY;
    memcpy(packetTX + 4, System_Config.DeviceID,4);

    packetTX[8] = Ver_H;
    packetTX[9] = Ver_L;
    packetTX[10] = Hw_Ver_H;
    packetTX[11] = Hw_Ver_L;   
    
    packetTX[12] = 1;
    
    packetTX[13] = FACTORY_YEAR;
    packetTX[14] = FACTORY_MONTH;
    packetTX[15] = FACTORY_DAY;
    
    crc = comCalCRC16(packetTX,16);
    packetTX[16] = crc / 256;
    packetTX[17] = crc % 256;  
    //SendNotification();
}


/***********************************************
* 函数名：void Back_Massage_Minwen(uint8 cmd,uint8 data)
* 描述  ：分包应答
***********************************************/
void Back_subpackage(uint8 cmd,uint8 pk_num)
{
    uint16 crc;
    memset(packetTX,0x00,sizeof(packetTX));
    packetTX[0] = cmd;
    packetTX[1] = pk_num;           //包号
    packetTX[2] = 0;                //命令字    

    crc = comCalCRC16(packetTX,3);
    packetTX[3] = crc / 256;
    packetTX[4] = crc % 256;   
    //SendNotification();
}


/***********************************************
* 函数名：void Hl_Back_KeyInfo()
* 描述  ：返回钥匙信息
***********************************************/
void Hl_Back_KeyInfo(void)
{
    uint8 sendlen;
    uint16 batt_val = 0;
    packetTX[0] = CMD_GET_KEYINFO;
    packetTX[1] = 8;
    
    memcpy(&packetTX[2], &System_Config.DeviceID, 4); //钥匙ID
    
    packetTX[6] = Ver_H;
    packetTX[7] = Ver_L;
    
    batt_val = Get_Adc();
    packetTX[8] = (uint8)(batt_val >> 8);
    packetTX[9] = (uint8)(batt_val);
    //packetTX[8] = 0xe;
    //packetTX[9] = 0x00;
    
    packetTX[10] = Xor_Check(&packetTX[2], 8);
  
    
    sendlen = packetTX[1] + 3;
    
    SendNotification_zx(sendlen);
}

/***********************************************
* 函数名：void  Hl_Back_Msg(uint8 cmd, uint8 result)
* 描述  ：返回应答结果
***********************************************/
void  Hl_Back_Msg(uint8 cmd, uint8 result)
{
    uint8 sendlen;

    packetTX[0] = cmd;
    packetTX[1] = 1;
    packetTX[2] = result;
    
    packetTX[3] = Xor_Check(&packetTX[2], packetTX[1]);
    
    sendlen = packetTX[1] + 3;
    
    SendNotification_zx(sendlen);
}

/***********************************************
* 函数名：void Hl_Back_Lock_Open(void)
* 描述  ：返回开锁应答结果
***********************************************/
void Hl_Back_Lock_Open(uint8 r)
{
    uint8 sendlen;

    packetTX[0] = CMD_LOCK_OPEN;
    packetTX[1] = 2;
    packetTX[2] = r; //结果
    packetTX[3] = 1; //锁状态
    
    packetTX[4] = Xor_Check(&packetTX[2], packetTX[1]);
    //packetTX[4] = 0;
    sendlen = packetTX[1] + 3;
    
    SendNotification_zx(sendlen);
}

/***********************************************
* 函数名：void Hl_Back_Lock_Info(void)
* 描述  ：返回锁设备信息 预备开锁
***********************************************/
void Hl_Back_Lock_Info(void)
{
    uint8 sendlen;
    uint8 rc4_key[16];
    
    packetTX[0] = CMD_UP_LOCKINFO;
    
    packetTX[1] = 7;
    
    memcmp(&packetTX[2], Lock_Info.DeviceID, 4);
    
    packetTX[6] = Ver_H;
    packetTX[7] = Ver_L;
    
    packetTX[8] = 0; //锁状态

    memcpy(rc4_key, key_str.dynamic_key, 8);       //动态密钥做高8字节
    memcpy(&rc4_key[8], System_Config.root_key, 8);      //根密钥做低8字节
    
    App_RC4(rc4_key, 16, &packetTX[2], 7); //加密
   
    packetTX[9] = Xor_Check(&packetTX[2], packetTX[1]);  //异或校验
    
    sendlen = packetTX[1] + 3;
    
    SendNotification_zx(sendlen);
}

/**************************************************************
// C prototype : void HexToStr(BYTE *pbDest, BYTE *pbSrc, int nLen)
// parameter(s): [OUT] pbDest - 存放目标字符串
// [IN] pbSrc - 输入16进制数的起始地址
// [IN] nLen - 16进制数的字节数
// return value:
// remarks : 将16进制数转化为字符串
*****************************************************************/
void HexToStr(char *pbDest, uint8 *pbSrc, uint16 nLen)
{
    char ddl,ddh;
    int i;

    for (i=0; i<nLen; i++)
    {
        ddh = 48 + pbSrc[i] / 16;
        ddl = 48 + pbSrc[i] % 16;
        if (ddh > 57) ddh = ddh + ('a' - '9' - 1);
        if (ddl > 57) ddl = ddl + ('a' - '9' - 1);
        pbDest[i*2] = ddh;
        pbDest[i*2+1] = ddl;
    }

    pbDest[nLen*2] = '\0';
}

/***********************************************
* 函数名：void test_md5(void)
* 描述  ：md5测试
***********************************************/
void test_md5(void)
{
    uint8 key[16];  //hex
    char  dest_key[36];  //字符串
    
    uint8 data[5]; 
    
    unsigned char decrypt[16]; //生成的MD5标签
    MD5_CTX md5; 
    
   /* key_str.dynamic_key[0] = 0xb1;
    key_str.dynamic_key[1] = 0xe3;
    key_str.dynamic_key[2] = 0x37;
    key_str.dynamic_key[3] = 0xde;
    key_str.dynamic_key[4] = 0x14;
    key_str.dynamic_key[5] = 0xd6;
    key_str.dynamic_key[6] = 0xe4;
    key_str.dynamic_key[7] = 0xfe;*/
    
    memcpy(key, key_str.dynamic_key, 8);  //high 8
    memcpy(&key[8], System_Config.ctrl_key, 8); //low 8
    
    HexToStr(dest_key, key, 16);
    
    MD5Init(&md5);                
    MD5Update(&md5, (unsigned char *)dest_key, strlen((char *)dest_key));  
    MD5Final(&md5, decrypt); //生成MD5标签
    
    data[0] = 0xd5;
    data[1] = 0x59;
    data[2] = 0x5e;
    data[3] = 0x78;
    data[4] = 0x6e;
    
    App_RC4(decrypt, 16, data, 5);
    
    MD5Init(&md5);    
}

/***********************************************
* 函数名：void key_touch_lock_process(void)
* 描述  ：当钥匙接入锁孔时 发送03包给APP 
          在main中被调用
***********************************************/
void key_touch_lock_process(void)
{
    if(lock_open_flag == LOCK_OPEN_FLAG_SET)
    {
        if(lock_flag == 0) //允许开锁一次
        { 
           lock_flag = 1;  //允许开锁一次
           Hl_Back_Lock_Info(); //发送03包  当钥匙接入锁孔时发送  
        }
        
        if(++lock_timeflow > 1000) //钥匙离开锁孔检测
        {
           lock_timeflow = 0;                                                                                                                                                                  
           lock_open_flag = 0;
           lock_flag = 0; 
        }
    }    
}

/***********************************************
* 函数名：void key_touch_lock_flag_set(void)
* 描述  ：当钥匙接入锁孔时 确认并设置标识 
          在app_com.c void Com_Recv_Prov(void)中被调用
***********************************************/
void key_touch_lock_flag_set(void)
{
    if(++lock_open_flag >= LOCK_OPEN_FLAG_SET) //接入确认
    {
       lock_open_flag = LOCK_OPEN_FLAG_SET;
    }
    
    lock_timeflow = 0; //在通讯中进行清零  进行超时检测
}


/***********************************************
* 函数名：void ReceiveBleCmd(void)
* 描述  ：处理蓝牙接收指令
***********************************************/
void ReceiveBleCmd(void)
{
    uint8 cmd, datalen;
    uint8 data_crc,check_crc;
    
    uint8 packet_rx[20];
    
    if(packetRXFlag)
    {
        packetRXFlag=0;         
        memcpy(packet_rx, packetRX, packetRXSize);
        memset(packetTX, 0, sizeof(packetTX));
        cmd = packet_rx[0];
        datalen = packet_rx[1];
        
        check_crc = Xor_Check(&packet_rx[2], datalen);     //检查校验
        data_crc = packet_rx[2 + datalen];
        
        if(check_crc == data_crc)
        {
            switch(cmd)
            {
                case CMD_GET_KEYINFO:
                Hl_Back_KeyInfo();
                break;
                
                case CMD_DYNAMIC_KEY: 
                memcpy(key_str.dynamic_key, &packet_rx[2], 8); //获得动态密钥
                Hl_Back_Msg(cmd, 1); //响应02包                         
                break;
                
                case CMD_LOCK_OPEN:
                {
                  uint8 key[16];  //hex
                  char  dest_key[36];  //字符串 
                  unsigned char decrypt[16]; //生成的MD5标签
                  MD5_CTX md5; 
                  
                  memcpy(key, key_str.dynamic_key, 8);  //high 8
                  memcpy(&key[8], System_Config.ctrl_key, 8); //low 8
                  
                  HexToStr(dest_key, key, 16);
                  
                  MD5Init(&md5);                
                  MD5Update(&md5, (unsigned char *)dest_key, strlen((char *)dest_key));  
                  MD5Final(&md5, decrypt); //生成MD5标签
                  
                  App_RC4(decrypt, 16, &packet_rx[2], 5); //RC4解密 
                  if(packet_rx[2] == Lock_Info.DeviceID[0] &&
                     packet_rx[3] == Lock_Info.DeviceID[1] &&
                     packet_rx[4] == Lock_Info.DeviceID[2] &&
                     packet_rx[5] == Lock_Info.DeviceID[3]){
                        
                        Com_Array.Tx_State = RE_CHECKCODE;     //开锁
                        Hl_Back_Lock_Open(1);
                  }
                  else
                  {
                    
                    Hl_Back_Lock_Open(0);
                  }
                }
                   
                break;
                
                case CMD_RESET_KEY: //新的根密钥和控制密钥
                {
                   uint8 key[16];  //hex
                   memcpy(key, key_str.dynamic_key, 8);  //high 8
                   memcpy(&key[8], System_Config.root_key, 8); //low 8
                   
                   App_RC4(key, 16, &packet_rx[2], 16); //RC4解密 
                   
                   memcpy(System_Config.root_key, &packet_rx[2], 8); //新的根密钥
                   memcpy(System_Config.ctrl_key, &packet_rx[6], 8); //新的控制密钥
                   
                   System_Config.sum = CRC_Sum((uint8 *)&System_Config,sizeof(System_Config)-1);
                   Write_Flash((uint8 *)&System_Config, sizeof(System_Config));
                   
                   Hl_Back_Msg(cmd, 1);
                }
                break;
                
                case CMD_RESET_LOCKID:
                {
                    uint8 key[16];  //hex
                    memcpy(key, key_str.dynamic_key, 8);  //high 8
                    memcpy(&key[8], System_Config.root_key, 8); //low 8
                   
                    App_RC4(key, 16, &packet_rx[2], 6); //RC4解密 
                    
                    memcpy(Lock_Info.DeviceID, &packet_rx[2], 4);
                    Hl_Back_Msg(cmd, 1);
                    
                    Set_Lock_ID(); //设置锁ID
                }
                break;
                
                case CMD_RESET_KEYID:
                 Hl_Back_Msg(cmd, 1);
                break;
                
                default:
                break;
            }
        }

    }
    
    //test_03packet();
}


/***********************************************
* 函数名：void SendBleCmd(void)
* 描述  ：处理蓝牙发送指令
***********************************************/
void SendBleCmd(void)
{
    switch(packetTXStep)
    {
        case BLE_IDLE:
            break;
        
        case Send_Lock_Info:
            Send_LockInfo();
            packetTXStep = BLE_IDLE;
            break;
        
        case Reply_OpenLock:
            packetTXStep = BLE_IDLE;
            Com_Array.Tx_State = RE_REQUEST;
            Back_Massage_Minwen(OPEN_LOCK_CMD,PRO_SUCCESS);
            break;
        
        default:
            break;     
    }
}

/***********************************************
* 函数名：uint16 comCalCRC16(uint8 *pucBuf, uint8 uwLength)
* 描述  ：CRC16校验
***********************************************/
uint16 comCalCRC16(uint8 *pucBuf, uint8 uwLength)
{
    uint16 uiCRCValue=0xffff;
    uint8 ucLoop;
    uint8 * pu8Buf = (uint8 *)pucBuf;
    while (uwLength--)
    {
        uiCRCValue ^= *pu8Buf++;
        for (ucLoop=0; ucLoop<8; ucLoop++)
        {
            if (uiCRCValue & 0x0001)
            {
                uiCRCValue >>= 1;
                uiCRCValue ^= CRC_POLY;
            }
            else
            {
                uiCRCValue >>= 1;
            }
        }
    }
    uiCRCValue ^= 0x0000;
    return uiCRCValue;
}

/*****************************
 * @function_name: uint8 Xor_Check(uint8 *Data, uint8 Length)
 * @function_file: xxxx.c
 * @描  述：       指定长度数组异或校验计算，XOR 
 *
 * @参  数：       *Data：输入待校验的数据流， Length：数据长度 
 * @返  回：       异或校验和
 * @备  注：	   校验计算长度为1字节，值位数据内容区的所有数据异或值，不包
               括包号，指令编号和数据内容长度 
 * @举  例 
 T    L        V         C
02  0003      010200    03
*data = 0x01 0x02 0x00
length= 0x03
sum  = 0x03
*********************************/
uint8 Xor_Check(uint8 *Data, uint8 Length)
{
    uint8 sum=0,i;
    for(i=0; i<Length; i++)
    {
    sum ^= *(Data + i);	
    }
    return sum;
}

/***********************************************************
* @function_name: void Load_System_Config(void)
* @function_file: AppProtocol.c
* @描  述：APP rc4加密算法
* @参  数：
* @返  回： void
**********************************************************/
void App_RC4(uint8 *key,uint8 key_leng, uint8 *buf, uint8 len)
{
	uint8 Sbox[256];
	uint8 Kbox[256];
	uint16 i;
	uint16 j=0;
	uint16 k;
	uint16 index = 0;
	uint8 temp;
	uint8 *data;
	data = buf;
	
	if ((buf == NULL) || (len <= 0))		//数据不存在
	{	
		return;
	}
	for(i=0; i<256; i++)
	{
		Sbox[i] = i;
		Kbox[i] = key[i % key_leng];
	}
	
	for(i=0; i<256; i++)
	{
		j = (j + Sbox[i] + Kbox[i]) % 256;
		temp = Sbox[i];
		Sbox[i] = Sbox[j];
		Sbox[j] = temp;
	}
	
	while(index < len)
	{
		i = (i + 1) % 256;
		j = (j + Sbox[i]) % 256;
		temp = Sbox[i];
		Sbox[i] = Sbox[j];
		Sbox[j] = temp;
		k = (Sbox[i] + Sbox[j]) % 256;
		buf[index] = data[index] ^ Sbox[k]; 
		index++;
	}
}


/* [] END OF FILE */
