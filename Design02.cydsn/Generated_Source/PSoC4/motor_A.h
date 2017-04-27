/*******************************************************************************
* File Name: motor_A.h  
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

#if !defined(CY_PINS_motor_A_H) /* Pins motor_A_H */
#define CY_PINS_motor_A_H

#include "cytypes.h"
#include "cyfitter.h"
#include "motor_A_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    motor_A_Write(uint8 value) ;
void    motor_A_SetDriveMode(uint8 mode) ;
uint8   motor_A_ReadDataReg(void) ;
uint8   motor_A_Read(void) ;
uint8   motor_A_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define motor_A_DRIVE_MODE_BITS        (3)
#define motor_A_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - motor_A_DRIVE_MODE_BITS))

#define motor_A_DM_ALG_HIZ         (0x00u)
#define motor_A_DM_DIG_HIZ         (0x01u)
#define motor_A_DM_RES_UP          (0x02u)
#define motor_A_DM_RES_DWN         (0x03u)
#define motor_A_DM_OD_LO           (0x04u)
#define motor_A_DM_OD_HI           (0x05u)
#define motor_A_DM_STRONG          (0x06u)
#define motor_A_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define motor_A_MASK               motor_A__MASK
#define motor_A_SHIFT              motor_A__SHIFT
#define motor_A_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define motor_A_PS                     (* (reg32 *) motor_A__PS)
/* Port Configuration */
#define motor_A_PC                     (* (reg32 *) motor_A__PC)
/* Data Register */
#define motor_A_DR                     (* (reg32 *) motor_A__DR)
/* Input Buffer Disable Override */
#define motor_A_INP_DIS                (* (reg32 *) motor_A__PC2)


#if defined(motor_A__INTSTAT)  /* Interrupt Registers */

    #define motor_A_INTSTAT                (* (reg32 *) motor_A__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define motor_A_DRIVE_MODE_SHIFT       (0x00u)
#define motor_A_DRIVE_MODE_MASK        (0x07u << motor_A_DRIVE_MODE_SHIFT)


#endif /* End Pins motor_A_H */


/* [] END OF FILE */
