/*******************************************************************************
* File Name: POWERON_OUT.h  
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

#if !defined(CY_PINS_POWERON_OUT_H) /* Pins POWERON_OUT_H */
#define CY_PINS_POWERON_OUT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "POWERON_OUT_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    POWERON_OUT_Write(uint8 value) ;
void    POWERON_OUT_SetDriveMode(uint8 mode) ;
uint8   POWERON_OUT_ReadDataReg(void) ;
uint8   POWERON_OUT_Read(void) ;
uint8   POWERON_OUT_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define POWERON_OUT_DRIVE_MODE_BITS        (3)
#define POWERON_OUT_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - POWERON_OUT_DRIVE_MODE_BITS))

#define POWERON_OUT_DM_ALG_HIZ         (0x00u)
#define POWERON_OUT_DM_DIG_HIZ         (0x01u)
#define POWERON_OUT_DM_RES_UP          (0x02u)
#define POWERON_OUT_DM_RES_DWN         (0x03u)
#define POWERON_OUT_DM_OD_LO           (0x04u)
#define POWERON_OUT_DM_OD_HI           (0x05u)
#define POWERON_OUT_DM_STRONG          (0x06u)
#define POWERON_OUT_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define POWERON_OUT_MASK               POWERON_OUT__MASK
#define POWERON_OUT_SHIFT              POWERON_OUT__SHIFT
#define POWERON_OUT_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define POWERON_OUT_PS                     (* (reg32 *) POWERON_OUT__PS)
/* Port Configuration */
#define POWERON_OUT_PC                     (* (reg32 *) POWERON_OUT__PC)
/* Data Register */
#define POWERON_OUT_DR                     (* (reg32 *) POWERON_OUT__DR)
/* Input Buffer Disable Override */
#define POWERON_OUT_INP_DIS                (* (reg32 *) POWERON_OUT__PC2)


#if defined(POWERON_OUT__INTSTAT)  /* Interrupt Registers */

    #define POWERON_OUT_INTSTAT                (* (reg32 *) POWERON_OUT__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define POWERON_OUT_DRIVE_MODE_SHIFT       (0x00u)
#define POWERON_OUT_DRIVE_MODE_MASK        (0x07u << POWERON_OUT_DRIVE_MODE_SHIFT)


#endif /* End Pins POWERON_OUT_H */


/* [] END OF FILE */
