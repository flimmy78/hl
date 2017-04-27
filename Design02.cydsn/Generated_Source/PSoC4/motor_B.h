/*******************************************************************************
* File Name: motor_B.h  
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

#if !defined(CY_PINS_motor_B_H) /* Pins motor_B_H */
#define CY_PINS_motor_B_H

#include "cytypes.h"
#include "cyfitter.h"
#include "motor_B_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    motor_B_Write(uint8 value) ;
void    motor_B_SetDriveMode(uint8 mode) ;
uint8   motor_B_ReadDataReg(void) ;
uint8   motor_B_Read(void) ;
uint8   motor_B_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define motor_B_DRIVE_MODE_BITS        (3)
#define motor_B_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - motor_B_DRIVE_MODE_BITS))

#define motor_B_DM_ALG_HIZ         (0x00u)
#define motor_B_DM_DIG_HIZ         (0x01u)
#define motor_B_DM_RES_UP          (0x02u)
#define motor_B_DM_RES_DWN         (0x03u)
#define motor_B_DM_OD_LO           (0x04u)
#define motor_B_DM_OD_HI           (0x05u)
#define motor_B_DM_STRONG          (0x06u)
#define motor_B_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define motor_B_MASK               motor_B__MASK
#define motor_B_SHIFT              motor_B__SHIFT
#define motor_B_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define motor_B_PS                     (* (reg32 *) motor_B__PS)
/* Port Configuration */
#define motor_B_PC                     (* (reg32 *) motor_B__PC)
/* Data Register */
#define motor_B_DR                     (* (reg32 *) motor_B__DR)
/* Input Buffer Disable Override */
#define motor_B_INP_DIS                (* (reg32 *) motor_B__PC2)


#if defined(motor_B__INTSTAT)  /* Interrupt Registers */

    #define motor_B_INTSTAT                (* (reg32 *) motor_B__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define motor_B_DRIVE_MODE_SHIFT       (0x00u)
#define motor_B_DRIVE_MODE_MASK        (0x07u << motor_B_DRIVE_MODE_SHIFT)


#endif /* End Pins motor_B_H */


/* [] END OF FILE */
