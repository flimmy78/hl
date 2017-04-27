/*******************************************************************************
* File Name: extend_sensor.h  
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

#if !defined(CY_PINS_extend_sensor_H) /* Pins extend_sensor_H */
#define CY_PINS_extend_sensor_H

#include "cytypes.h"
#include "cyfitter.h"
#include "extend_sensor_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    extend_sensor_Write(uint8 value) ;
void    extend_sensor_SetDriveMode(uint8 mode) ;
uint8   extend_sensor_ReadDataReg(void) ;
uint8   extend_sensor_Read(void) ;
uint8   extend_sensor_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define extend_sensor_DRIVE_MODE_BITS        (3)
#define extend_sensor_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - extend_sensor_DRIVE_MODE_BITS))

#define extend_sensor_DM_ALG_HIZ         (0x00u)
#define extend_sensor_DM_DIG_HIZ         (0x01u)
#define extend_sensor_DM_RES_UP          (0x02u)
#define extend_sensor_DM_RES_DWN         (0x03u)
#define extend_sensor_DM_OD_LO           (0x04u)
#define extend_sensor_DM_OD_HI           (0x05u)
#define extend_sensor_DM_STRONG          (0x06u)
#define extend_sensor_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define extend_sensor_MASK               extend_sensor__MASK
#define extend_sensor_SHIFT              extend_sensor__SHIFT
#define extend_sensor_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define extend_sensor_PS                     (* (reg32 *) extend_sensor__PS)
/* Port Configuration */
#define extend_sensor_PC                     (* (reg32 *) extend_sensor__PC)
/* Data Register */
#define extend_sensor_DR                     (* (reg32 *) extend_sensor__DR)
/* Input Buffer Disable Override */
#define extend_sensor_INP_DIS                (* (reg32 *) extend_sensor__PC2)


#if defined(extend_sensor__INTSTAT)  /* Interrupt Registers */

    #define extend_sensor_INTSTAT                (* (reg32 *) extend_sensor__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define extend_sensor_DRIVE_MODE_SHIFT       (0x00u)
#define extend_sensor_DRIVE_MODE_MASK        (0x07u << extend_sensor_DRIVE_MODE_SHIFT)


#endif /* End Pins extend_sensor_H */


/* [] END OF FILE */
