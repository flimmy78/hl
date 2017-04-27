/*******************************************************************************
* File Name: Wake_Up.h  
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

#if !defined(CY_PINS_Wake_Up_H) /* Pins Wake_Up_H */
#define CY_PINS_Wake_Up_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Wake_Up_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Wake_Up_Write(uint8 value) ;
void    Wake_Up_SetDriveMode(uint8 mode) ;
uint8   Wake_Up_ReadDataReg(void) ;
uint8   Wake_Up_Read(void) ;
uint8   Wake_Up_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Wake_Up_DRIVE_MODE_BITS        (3)
#define Wake_Up_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Wake_Up_DRIVE_MODE_BITS))

#define Wake_Up_DM_ALG_HIZ         (0x00u)
#define Wake_Up_DM_DIG_HIZ         (0x01u)
#define Wake_Up_DM_RES_UP          (0x02u)
#define Wake_Up_DM_RES_DWN         (0x03u)
#define Wake_Up_DM_OD_LO           (0x04u)
#define Wake_Up_DM_OD_HI           (0x05u)
#define Wake_Up_DM_STRONG          (0x06u)
#define Wake_Up_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Wake_Up_MASK               Wake_Up__MASK
#define Wake_Up_SHIFT              Wake_Up__SHIFT
#define Wake_Up_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Wake_Up_PS                     (* (reg32 *) Wake_Up__PS)
/* Port Configuration */
#define Wake_Up_PC                     (* (reg32 *) Wake_Up__PC)
/* Data Register */
#define Wake_Up_DR                     (* (reg32 *) Wake_Up__DR)
/* Input Buffer Disable Override */
#define Wake_Up_INP_DIS                (* (reg32 *) Wake_Up__PC2)


#if defined(Wake_Up__INTSTAT)  /* Interrupt Registers */

    #define Wake_Up_INTSTAT                (* (reg32 *) Wake_Up__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Wake_Up_DRIVE_MODE_SHIFT       (0x00u)
#define Wake_Up_DRIVE_MODE_MASK        (0x07u << Wake_Up_DRIVE_MODE_SHIFT)


#endif /* End Pins Wake_Up_H */


/* [] END OF FILE */
