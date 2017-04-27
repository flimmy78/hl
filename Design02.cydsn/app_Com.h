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
/*****************************************************
				发送任务状态
******************************************************/
#define IDLE					0x00			//空闲状态
#define SEND_DELAY				0x01			//发送等待
#define RE_SEND					0x03			//重发

#define REQUEST_DEVICE			0x04			//请求查询设备
#define CHECK_CODE              0x05            //对码
#define SWAP_KEY                0x06            //交换密钥
#define REQUEST_INDEX           0x07            //请求检索号
#define OPEN_LOCK               0x08            //开锁


#define RE_REQUEST              0x10            //重复查询
#define RE_CHECKCODE            0x11



typedef struct
{
    uint8 Rx_buff[40];         //串口接收缓存
    uint8 Tx_buff[60];         //串口发送缓存
    
    uint8 Rx_Length;            //串口接收数据长度
    uint8 Rx_Count;             //串口接收计数器
    uint8 Rx_Index;
    uint8 Rx_Begin_Flag;        //串口接收开始标志
    uint8 Rx_Delay;             //串口超时
    uint8 Rx_Flag;              //串口接收标志
    uint8 Rx_Tag;
    
    uint8 Tx_Length;
    uint8 Tx_State;
    uint8 Tx_Mode;              //正在发生标志
    uint16 Tx_Wait;
    uint8 Tx_Count;
    uint8 Tx_Delay;
    
    uint8 Tx_Begin;
    
    uint16 Crc;
}ComArray;
extern ComArray Com_Array;







void Com_Recv_Prov(void);
void Com_Send_Prov(void);
void Send_Com(uint8 *TX_Buffer,uint8 Length);

void Request_Device_Info(void);
void Check_Code(void);
void Swap_Key(void);
void Request_Index(void);
void Open_Lock(void);
void Set_Lock_ID(void);


/* [] END OF FILE */
