/*******************************************************************************
* File Name: app_Ble.h
*
* Description:
*  Contains the function prototypes and constants available to the example
*  project.
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#ifndef APP_BLE_H
    
    #define APP_BLE_H
    
    #include <project.h>
    #include "stdbool.h"
    #include "app_UART.h"
    #include "main.h"
    
    /***************************************
    *       Constants
    ***************************************/
    #define NOTIFICATON_ENABLED         0x0001
    #define NOTIFICATON_DISABLED        0x0000
    
    #define BLE_PACKET_SIZE_MAX                 (44u)
    
    extern uint8 packetRX[BLE_PACKET_SIZE_MAX];
    extern uint32 packetRXSize;
    extern uint32 packetRXFlag;  
    extern uint8 packetTX[20];

    
    /***************************************
    *       Function Prototypes
    ***************************************/
    void HandleBleProcessing(void);    
 
    void HandleCmdBle(void);
    
    
    
#endif

/* [] END OF FILE */
