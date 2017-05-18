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

#define CRC_POLY 0xA001

#define Ver_H  0x01         //软件版本号高位
#define Ver_L  0x00         //软件版本号低位

#define Hw_Ver_H    0x01    //硬件版本号高位
#define Hw_Ver_L    0x00    //硬件版本号低位


#define FACTORY_YEAR    16
#define FACTORY_MONTH   11
#define FACTORY_DAY     15


#define NORMAL_KEY      0x03
#define BLE_NORMAL_KEY  0x13


/*****************************************************
				返回报文应答状态，异常代码
******************************************************/
#define PRO_SUCCESS			    0x00			//正确成功通讯
#define DEVICE_INIT_ERROR		0x01			//设备初始化或者恢复出厂失败
#define MKEY_ERROR				0x02			//管理中心密钥不准确（对码出错）
#define LOCK_NAME_ERROR			0x03			//锁识别号不正确

#define FIRST_CRC_ERROR			0x21			//解密前的校验出错
#define SECOND_CRC_ERROR		0x22			//解密后的校验出错
#define FRAME_LENGTH_ERROR		0x23			//指令长度不对
#define CMD_CONDITION_ERROR		0x24			//指令未达到操作条件
#define INIT_SWAPKEY_ERROR		0x25			//已经初始化的设备接收到初始化交换密钥指令

/************通用协议*********************/
#define REQUEST_DEVICE_CMD		0x01			//请求设备信息
#define INIT_SWAP_KEY_CMD		0x02			//初始化交换密钥
#define	SWAP_KEY_CMD			0x03			//交换密钥
#define CHECK_CODE_CMD			0x04			//对码

/************钥匙与锁身份卡通讯协议********/
#define REQUEST_LOCK_INDEX		0x06			//请求装置索引号
#define OPEN_LOCK_CMD  			0x07			//开锁
#define SET_LOCK_ID             0x0A            //设置锁设备号
#define REQUEST_FACTORY_INFO    0x0B            //获取出厂信息
#define SET_KEY_ID              0x0C            //设置钥匙设备号
#define GET_BATTERY_VOLTAGE     0x1D            //读取钥匙电压
#define SET_MANAGE_KEY          0x14            //设置管理中心密钥
#define SET_TIME

/************蓝牙发生步骤********/
#define BLE_IDLE                0x00            //空闲
#define Send_Lock_Info          0x01            //发送锁信息
#define Reply_OpenLock          0x02            //应答开锁


//华立
#define CMD_GET_KEYINFO         0x01     //APP获取钥匙信息
#define CMD_DYNAMIC_KEY         0x02     //APP与钥匙之间同步动态密钥
#define CMD_UP_LOCKINFO         0x03     //上传锁信息
#define CMD_LOCK_OPEN           0x04     //开锁
#define CMD_RESET_KEY           0x05     //重置钥匙密钥
#define CMD_RESET_LOCKID        0x06     //重置锁设备号
#define CMD_RESET_KEYID         0x07     //重置钥匙ID和蓝牙ID
#define CMD_RECOVERY            0x08     //恢复出厂设置




extern uint8 packetTXStep;

void SendNotification(void);
void Send_LockInfo(void);
void ReceiveBleCmd(void);
void SendBleCmd(void);
void Back_subpackage(uint8 cmd,uint8 pk_num);

uint16 comCalCRC16(uint8 *pucBuf, uint8 uwLength);
void Back_Massage_Minwen(uint8 cmd,uint8 data);

uint8 Xor_Check(uint8 *Data, uint8 Length);
void App_RC4(uint8 *key,uint8 key_leng, uint8 *buf, uint8 len);

void key_touch_lock_process(void);
void key_touch_lock_flag_set(void);

unsigned char * HloveyRC4( unsigned char * aKey, short aKeylength, unsigned char * aInput,  short aInputlength);
int strToHex(char *ch, char *hex);

/* [] END OF FILE */
