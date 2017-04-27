/*******************************************************************************
* File Name: motor_D.h  
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

#if !defined(CY_PINS_motor_D_H) /* Pins motor_D_H */
#define CY_PINS_motor_D_H

#include "cytypes.h"
#include "cyfitter.h"
#include "motor_D_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    motor_D_Write(uint8 value) ;
void    motor_D_SetDriveMode(uint8 mode) ;
uint8   motor_D_ReadDataReg(void) ;
uint8   motor_D_Read(void) ;
uint8   motor_D_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define motor_D_DRIVE_MODE_BITS        (3)
#define motor_D_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - motor_D_DRIVE_MODE_BITS))

#define motor_D_DM_ALG_HIZ         (0x00u)
#define motor_D_DM_DIG_HIZ         (0x01u)
#define motor_D_DM_RES_UP          (0x02u)
#define motor_D_DM_RES_DWN         (0x03u)
#define motor_D_DM_OD_LO           (0x04u)
#define motor_D_DM_OD_HI           (0x05u)
#define motor_D_DM_STRONG          (0x06u)
#define motor_D_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define motor_D_MASK               motor_D__MASK
#define motor_D_SHIFT              motor_D__SHIFT
#define motor_D_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define motor_D_PS                     (* (reg32 *) motor_D__PS)
/* Port Configuration */
#define motor_D_PC                     (* (reg32 *) motor_D__PC)
/* Data Register */
#define motor_D_DR                     (* (reg32 *) motor_D__DR)
/* Input Buffer Disable Override */
#define motor_D_INP_DIS                (* (reg32 *) motor_D__PC2)


#if defined(motor_D__INTSTAT)  /* Interrupt Registers */

    #define motor_D_INTSTAT                (* (reg32 *) motor_D__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define motor_D_DRIVE_MODE_SHIFT       (0x00u)
#define motor_D_DRIVE_MODE_MASK        (0x07u << motor_D_DRIVE_MODE_SHIFT)


#endif /* End Pins motor_D_H */


/* [] END OF FILE */
