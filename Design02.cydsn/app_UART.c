/*****************************************************************************************
* File Name: app_UART.c
*
* Description:
*  Common BLE application code for client devices.
*
*****************************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*****************************************************************************************/

#include "app_UART.h"
#include "app_Ble.h"
extern char blename[11];
uint8   uartRxData[20];
uint16  uartRxDataLength;
uint8   uartRxflag;
/*****************************************************************************************
* Function Name: HandleUartTxTraffic
******************************************************************************************
*
* Summary:
*  This function takes data from UART RX buffer and pushes it to the server 
*  as Notifications.
*
* Parameters:
*  uint16 - CCCD for checking if notifications are enabled  
*
* Return:
*   None.
*
*****************************************************************************************/
void HandleUartTxTraffic(void)
{
    uint8   index;
    static uint16 uartIdleCount = UART_IDLE_TIMEOUT;
    uartRxDataLength = UART_SpiUartGetRxBufferSize();
    if(0 != uartRxDataLength)
    {
        if(--uartIdleCount == 0)
        {
            /*uartTxDataLength remains unchanged */;
            uartRxflag=1;
        }
        else
        {
            uartRxDataLength = 0;
        }
        if(0 != uartRxDataLength)
        {
            uartIdleCount       = UART_IDLE_TIMEOUT;            
            for(index = 0; index < uartRxDataLength; index++)
            {
                uartRxData[index] = (uint8) UART_UartGetByte();
            }
        }
    }

}

/*****************************************************************************************
* Function Name: HandleUartRxTraffic
******************************************************************************************
*
* Summary:
*  This function takes data from received "write without response" command from
*  server and, pushes it to the UART TX buffer. 
*
* Parameters:
*  CYBLE_GATTS_WRITE_REQ_PARAM_T * - the "write without response" param as
*                                    recieved by the BLE stack
*
* Return:
*   None.
*通过串口发送到PC机
*****************************************************************************************/
void HandleUartRxTraffic(CYBLE_GATTS_WRITE_REQ_PARAM_T * uartRxDataWrReq)
{
    //if(uartRxDataWrReq->handleValPair.attrHandle == CYBLE_SERVER_UART_SERVER_UART_RX_DATA_CHAR_HANDLE)
    {
        UART_SpiUartPutArray(uartRxDataWrReq->handleValPair.value.val, \
                                    (uint32) uartRxDataWrReq->handleValPair.value.len);
    }
}




/*****************************************************************************************
* Function Name: DisableUartRxInt
******************************************************************************************
*
* Summary:
*  This function disables the UART RX interrupt.
*
* Parameters:
*   None.
*
* Return:
*   None.
*
*****************************************************************************************/
void DisableUartRxInt(void)
{
    UART_INTR_RX_MASK_REG &= ~UART_RX_INTR_MASK;  
}

/*****************************************************************************************
* Function Name: EnableUartRxInt
******************************************************************************************
*
* Summary:
*  This function enables the UART RX interrupt.
*
* Parameters:
*   None.
*
* Return:
*   None.
*
*****************************************************************************************/
void EnableUartRxInt(void)
{
    UART_INTR_RX_MASK_REG |= UART_RX_INTR_MASK;  
}

/* [] END OF FILE */
