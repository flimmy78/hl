#include "main.h"
#include "stdlib.h"
#include "Rc4.h"
#include "app_Com.h"

#define BLE_ON     1     //  0:蓝牙关闭，   1：蓝牙打开

char8 BLEDeviceName[11] = {0x54,0x4c,0x2d,0x30,0x31,0x30,0x32,0x30,0x33,0x30,0x34};

CY_ISR(TimerHand)
{
    System_Timer_ClearInterrupt(System_Timer_INTR_MASK_TC);
    Delay_Time.Delay_1ms = 0;   
    
    if(Com_Array.Rx_Begin_Flag)
    {
        Com_Array.Rx_Delay ++;
    }
}

/***********************************************
    串口接收中断
***********************************************/
CY_ISR(MY_UART_SCB_IRQ_Interrupt)
{
    UART_ClearRxInterruptSource(UART_INTR_RX_NOT_EMPTY);
    
    if(Com_Array.Tx_Begin == 0)
    {
       if((Com_Array.Rx_Count % 2) == 0)
        {
            Com_Array.Rx_Index = Com_Array.Rx_Count / 2 ;
            Com_Array.Rx_buff[Com_Array.Rx_Index] = UART_SpiUartReadRxData();//读取串口接收缓冲区的数据
        }
        Com_Array.Rx_Count ++;
        if(Com_Array.Rx_Index > 40)
        {
            Com_Array.Rx_Count = 0;
            Com_Array.Rx_Index = 0;
            Com_Array.Rx_Delay = 0;
            Com_Array.Rx_Begin_Flag = 0;
        }
      
        if(Com_Array.Rx_Count == 1)         //第一个字时开始超时计时
        {
            Com_Array.Rx_Begin_Flag = 1;
        }
        
        if(Com_Array.Rx_Index == 1)         //数据包长度
        {
            Com_Array.Rx_Length = Com_Array.Rx_buff[1] + 4;
        }  
        
        if((Com_Array.Rx_Index > 3) && (Com_Array.Rx_Index == (Com_Array.Rx_Length - 1)))
        {
            Com_Array.Rx_Flag = 1;          //接收到整包
        }
    }
    else
    {
        Com_Array.Rx_Count = 0;
    }
    UART_SpiUartClearRxBuffer();   
}

#define BRIGHTNESS_DECREASE         (100u)

CY_ISR(InterruptHandler)
{
    static     uint8 beep = 0;
	/* Clear TC Inerrupt */
   	PWM_ClearInterrupt(PWM_INTR_MASK_TC);
    
    if(beep == 0)
    {
        beep = 1;
        BEEP_OPEN;
    }
    else
    {
        beep = 0;
        BEEP_CLOSE;
    }
}

int main()
{
#if BLE_ON
    CYBLE_API_RESULT_T      bleApiResult;
    uint8 i;
#endif

    System_Timer_Start();
    Timer_isr_StartEx(TimerHand);    

    UART_Start(); 
    UART_SCB_IRQ_Start();
    UART_SCB_IRQ_StartEx(MY_UART_SCB_IRQ_Interrupt);
    POWERON_OUT_Write(HIGH);
    TC_ISR_StartEx(InterruptHandler);
    Load_Config();
    ADC_Start();

#if BLE_ON
    if(System_Config.IDChangeFlag)                 //开机检测，是否更新蓝牙设备名
    {
        for(i=0; i<4; i++)
        {
            BLEDeviceName[3+2*i] = Hex_To_Ascii(System_Config.DeviceID[i] / 16);
            BLEDeviceName[4+2*i] = Hex_To_Ascii(System_Config.DeviceID[i] % 16);
        }
        CyBle_GapSetLocalName(BLEDeviceName);       //修改蓝牙设备名
    }
    bleApiResult = CyBle_Start(AppCallBack); 
    if(bleApiResult == CYBLE_ERROR_OK)
    {
        //
    }
#endif
    CyGlobalIntEnable;
    CyDelay(10);

#if BLE_ON    
    CyBle_ProcessEvents();
#endif
    
    RED_OFF;
    GREEN_ON;
    Com_Array.Tx_State = RE_REQUEST;
    while(1)
    {      
#if BLE_ON        
        HandleBleProcessing();//BLE连接与断开
        CyBle_ProcessEvents();    
        ReceiveBleCmd();   
        SendBleCmd();
#endif        
        Com_Recv_Prov();     
        Com_Send_Prov();
        
        if(Com_Array.Tx_Begin)      //自动关闭发送
        {
            Com_Array.Tx_Delay ++;
            if(Com_Array.Tx_Delay > 3)
            {
                Com_Array.Tx_Begin = 0;
                Com_Array.Tx_Delay = 0;
            }
        }
        
        Power_Off();
        
        Alarm_Event(Flag.Alarm_Work_Step);  //声光报警状态
  
        key_touch_lock_process();
        
        while(Delay_Time.Delay_1ms);        //1MS
        Delay_Time.Delay_1ms = 1;     
    }
}


/***********************************************
* 函数名：uint16 Get_Adc(void)
* 描述  ：采集电压
1677-3.623V
1849-4.0V
***********************************************/
uint16 Get_Adc(void)
{
    uint16 adcResult;
    uint32 mvolts;
    ADC_StartConvert();
    ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);

    adcResult = ADC_GetResult16(0x00);
    mvolts = (4000 * adcResult) / 1849;
    return (uint16)mvolts;
}


/* END OF FILE */
