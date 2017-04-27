/*******************************************************************************
* File Name: shrink_sensor.h  
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

#if !defined(CY_PINS_shrink_sensor_H) /* Pins shrink_sensor_H */
#define CY_PINS_shrink_sensor_H

#include "cytypes.h"
#include "cyfitter.h"
#include "shrink_sensor_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    shrink_sensor_Write(uint8 value) ;
void    shrink_sensor_SetDriveMode(uint8 mode) ;
uint8   shrink_sensor_ReadDataReg(void) ;
uint8   shrink_sensor_Read(void) ;
uint8   shrink_sensor_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define shrink_sensor_DRIVE_MODE_BITS        (3)
#define shrink_sensor_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - shrink_sensor_DRIVE_MODE_BITS))

#define shrink_sensor_DM_ALG_HIZ         (0x00u)
#define shrink_sensor_DM_DIG_HIZ         (0x01u)
#define shrink_sensor_DM_RES_UP          (0x02u)
#define shrink_sensor_DM_RES_DWN         (0x03u)
#define shrink_sensor_DM_OD_LO           (0x04u)
#define shrink_sensor_DM_OD_HI           (0x05u)
#define shrink_sensor_DM_STRONG          (0x06u)
#define shrink_sensor_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define shrink_sensor_MASK               shrink_sensor__MASK
#define shrink_sensor_SHIFT              shrink_sensor__SHIFT
#define shrink_sensor_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define shrink_sensor_PS                     (* (reg32 *) shrink_sensor__PS)
/* Port Configuration */
#define shrink_sensor_PC                     (* (reg32 *) shrink_sensor__PC)
/* Data Register */
#define shrink_sensor_DR                     (* (reg32 *) shrink_sensor__DR)
/* Input Buffer Disable Override */
#define shrink_sensor_INP_DIS                (* (reg32 *) shrink_sensor__PC2)


#if defined(shrink_sensor__INTSTAT)  /* Interrupt Registers */

    #define shrink_sensor_INTSTAT                (* (reg32 *) shrink_sensor__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define shrink_sensor_DRIVE_MODE_SHIFT       (0x00u)
#define shrink_sensor_DRIVE_MODE_MASK        (0x07u << shrink_sensor_DRIVE_MODE_SHIFT)


#endif /* End Pins shrink_sensor_H */


/* [] END OF FILE */
