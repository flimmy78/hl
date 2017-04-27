/*******************************************************************************
* File Name: key_sensor.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_key_sensor_H) /* Pins key_sensor_H */
#define CY_PINS_key_sensor_H

#include "cytypes.h"
#include "cyfitter.h"
#include "key_sensor_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    key_sensor_Write(uint8 value) ;
void    key_sensor_SetDriveMode(uint8 mode) ;
uint8   key_sensor_ReadDataReg(void) ;
uint8   key_sensor_Read(void) ;
uint8   key_sensor_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define key_sensor_DRIVE_MODE_BITS        (3)
#define key_sensor_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - key_sensor_DRIVE_MODE_BITS))

#define key_sensor_DM_ALG_HIZ         (0x00u)
#define key_sensor_DM_DIG_HIZ         (0x01u)
#define key_sensor_DM_RES_UP          (0x02u)
#define key_sensor_DM_RES_DWN         (0x03u)
#define key_sensor_DM_OD_LO           (0x04u)
#define key_sensor_DM_OD_HI           (0x05u)
#define key_sensor_DM_STRONG          (0x06u)
#define key_sensor_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define key_sensor_MASK               key_sensor__MASK
#define key_sensor_SHIFT              key_sensor__SHIFT
#define key_sensor_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define key_sensor_PS                     (* (reg32 *) key_sensor__PS)
/* Port Configuration */
#define key_sensor_PC                     (* (reg32 *) key_sensor__PC)
/* Data Register */
#define key_sensor_DR                     (* (reg32 *) key_sensor__DR)
/* Input Buffer Disable Override */
#define key_sensor_INP_DIS                (* (reg32 *) key_sensor__PC2)


#if defined(key_sensor__INTSTAT)  /* Interrupt Registers */

    #define key_sensor_INTSTAT                (* (reg32 *) key_sensor__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define key_sensor_DRIVE_MODE_SHIFT       (0x00u)
#define key_sensor_DRIVE_MODE_MASK        (0x07u << key_sensor_DRIVE_MODE_SHIFT)


#endif /* End Pins key_sensor_H */


/* [] END OF FILE */
