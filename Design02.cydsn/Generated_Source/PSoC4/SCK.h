/*******************************************************************************
* File Name: SCK.h  
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

#if !defined(CY_PINS_SCK_H) /* Pins SCK_H */
#define CY_PINS_SCK_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SCK_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    SCK_Write(uint8 value) ;
void    SCK_SetDriveMode(uint8 mode) ;
uint8   SCK_ReadDataReg(void) ;
uint8   SCK_Read(void) ;
uint8   SCK_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define SCK_DRIVE_MODE_BITS        (3)
#define SCK_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SCK_DRIVE_MODE_BITS))

#define SCK_DM_ALG_HIZ         (0x00u)
#define SCK_DM_DIG_HIZ         (0x01u)
#define SCK_DM_RES_UP          (0x02u)
#define SCK_DM_RES_DWN         (0x03u)
#define SCK_DM_OD_LO           (0x04u)
#define SCK_DM_OD_HI           (0x05u)
#define SCK_DM_STRONG          (0x06u)
#define SCK_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define SCK_MASK               SCK__MASK
#define SCK_SHIFT              SCK__SHIFT
#define SCK_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SCK_PS                     (* (reg32 *) SCK__PS)
/* Port Configuration */
#define SCK_PC                     (* (reg32 *) SCK__PC)
/* Data Register */
#define SCK_DR                     (* (reg32 *) SCK__DR)
/* Input Buffer Disable Override */
#define SCK_INP_DIS                (* (reg32 *) SCK__PC2)


#if defined(SCK__INTSTAT)  /* Interrupt Registers */

    #define SCK_INTSTAT                (* (reg32 *) SCK__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define SCK_DRIVE_MODE_SHIFT       (0x00u)
#define SCK_DRIVE_MODE_MASK        (0x07u << SCK_DRIVE_MODE_SHIFT)


#endif /* End Pins SCK_H */


/* [] END OF FILE */
