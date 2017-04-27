/*******************************************************************************
* File Name: NSS.h  
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

#if !defined(CY_PINS_NSS_H) /* Pins NSS_H */
#define CY_PINS_NSS_H

#include "cytypes.h"
#include "cyfitter.h"
#include "NSS_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    NSS_Write(uint8 value) ;
void    NSS_SetDriveMode(uint8 mode) ;
uint8   NSS_ReadDataReg(void) ;
uint8   NSS_Read(void) ;
uint8   NSS_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define NSS_DRIVE_MODE_BITS        (3)
#define NSS_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - NSS_DRIVE_MODE_BITS))

#define NSS_DM_ALG_HIZ         (0x00u)
#define NSS_DM_DIG_HIZ         (0x01u)
#define NSS_DM_RES_UP          (0x02u)
#define NSS_DM_RES_DWN         (0x03u)
#define NSS_DM_OD_LO           (0x04u)
#define NSS_DM_OD_HI           (0x05u)
#define NSS_DM_STRONG          (0x06u)
#define NSS_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define NSS_MASK               NSS__MASK
#define NSS_SHIFT              NSS__SHIFT
#define NSS_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define NSS_PS                     (* (reg32 *) NSS__PS)
/* Port Configuration */
#define NSS_PC                     (* (reg32 *) NSS__PC)
/* Data Register */
#define NSS_DR                     (* (reg32 *) NSS__DR)
/* Input Buffer Disable Override */
#define NSS_INP_DIS                (* (reg32 *) NSS__PC2)


#if defined(NSS__INTSTAT)  /* Interrupt Registers */

    #define NSS_INTSTAT                (* (reg32 *) NSS__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define NSS_DRIVE_MODE_SHIFT       (0x00u)
#define NSS_DRIVE_MODE_MASK        (0x07u << NSS_DRIVE_MODE_SHIFT)


#endif /* End Pins NSS_H */


/* [] END OF FILE */
