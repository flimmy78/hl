#ifndef MAIN_H
#define MAIN_H
#include <CyFlash.h>
#include "stdbool.h"
#include "app_protocol.h"
#include "app_LED.h"
#include "app_lock.h"  
#include "app_ble.h"
#include "app_uart.h"
void AppCallBack(uint32 , void *);  
uint16 Get_Adc(void);
    
#endif

/* [] END OF FILE */
