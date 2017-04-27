/*******************************************************************************
* File Name: Beep_Ctrl.h  
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

#if !defined(CY_PINS_Beep_Ctrl_H) /* Pins Beep_Ctrl_H */
#define CY_PINS_Beep_Ctrl_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Beep_Ctrl_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Beep_Ctrl_Write(uint8 value) ;
void    Beep_Ctrl_SetDriveMode(uint8 mode) ;
uint8   Beep_Ctrl_ReadDataReg(void) ;
uint8   Beep_Ctrl_Read(void) ;
uint8   Beep_Ctrl_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Beep_Ctrl_DRIVE_MODE_BITS        (3)
#define Beep_Ctrl_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Beep_Ctrl_DRIVE_MODE_BITS))

#define Beep_Ctrl_DM_ALG_HIZ         (0x00u)
#define Beep_Ctrl_DM_DIG_HIZ         (0x01u)
#define Beep_Ctrl_DM_RES_UP          (0x02u)
#define Beep_Ctrl_DM_RES_DWN         (0x03u)
#define Beep_Ctrl_DM_OD_LO           (0x04u)
#define Beep_Ctrl_DM_OD_HI           (0x05u)
#define Beep_Ctrl_DM_STRONG          (0x06u)
#define Beep_Ctrl_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Beep_Ctrl_MASK               Beep_Ctrl__MASK
#define Beep_Ctrl_SHIFT              Beep_Ctrl__SHIFT
#define Beep_Ctrl_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Beep_Ctrl_PS                     (* (reg32 *) Beep_Ctrl__PS)
/* Port Configuration */
#define Beep_Ctrl_PC                     (* (reg32 *) Beep_Ctrl__PC)
/* Data Register */
#define Beep_Ctrl_DR                     (* (reg32 *) Beep_Ctrl__DR)
/* Input Buffer Disable Override */
#define Beep_Ctrl_INP_DIS                (* (reg32 *) Beep_Ctrl__PC2)


#if defined(Beep_Ctrl__INTSTAT)  /* Interrupt Registers */

    #define Beep_Ctrl_INTSTAT                (* (reg32 *) Beep_Ctrl__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Beep_Ctrl_DRIVE_MODE_SHIFT       (0x00u)
#define Beep_Ctrl_DRIVE_MODE_MASK        (0x07u << Beep_Ctrl_DRIVE_MODE_SHIFT)


#endif /* End Pins Beep_Ctrl_H */


/* [] END OF FILE */
