/*******************************************************************************
* File Name: Key_Test.h  
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

#if !defined(CY_PINS_Key_Test_H) /* Pins Key_Test_H */
#define CY_PINS_Key_Test_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Key_Test_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Key_Test_Write(uint8 value) ;
void    Key_Test_SetDriveMode(uint8 mode) ;
uint8   Key_Test_ReadDataReg(void) ;
uint8   Key_Test_Read(void) ;
uint8   Key_Test_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Key_Test_DRIVE_MODE_BITS        (3)
#define Key_Test_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Key_Test_DRIVE_MODE_BITS))

#define Key_Test_DM_ALG_HIZ         (0x00u)
#define Key_Test_DM_DIG_HIZ         (0x01u)
#define Key_Test_DM_RES_UP          (0x02u)
#define Key_Test_DM_RES_DWN         (0x03u)
#define Key_Test_DM_OD_LO           (0x04u)
#define Key_Test_DM_OD_HI           (0x05u)
#define Key_Test_DM_STRONG          (0x06u)
#define Key_Test_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Key_Test_MASK               Key_Test__MASK
#define Key_Test_SHIFT              Key_Test__SHIFT
#define Key_Test_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Key_Test_PS                     (* (reg32 *) Key_Test__PS)
/* Port Configuration */
#define Key_Test_PC                     (* (reg32 *) Key_Test__PC)
/* Data Register */
#define Key_Test_DR                     (* (reg32 *) Key_Test__DR)
/* Input Buffer Disable Override */
#define Key_Test_INP_DIS                (* (reg32 *) Key_Test__PC2)


#if defined(Key_Test__INTSTAT)  /* Interrupt Registers */

    #define Key_Test_INTSTAT                (* (reg32 *) Key_Test__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Key_Test_DRIVE_MODE_SHIFT       (0x00u)
#define Key_Test_DRIVE_MODE_MASK        (0x07u << Key_Test_DRIVE_MODE_SHIFT)


#endif /* End Pins Key_Test_H */


/* [] END OF FILE */
