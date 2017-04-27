/*******************************************************************************
* File Name: TX.h  
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

#if !defined(CY_PINS_TX_H) /* Pins TX_H */
#define CY_PINS_TX_H

#include "cytypes.h"
#include "cyfitter.h"
#include "TX_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    TX_Write(uint8 value) ;
void    TX_SetDriveMode(uint8 mode) ;
uint8   TX_ReadDataReg(void) ;
uint8   TX_Read(void) ;
uint8   TX_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define TX_DRIVE_MODE_BITS        (3)
#define TX_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - TX_DRIVE_MODE_BITS))

#define TX_DM_ALG_HIZ         (0x00u)
#define TX_DM_DIG_HIZ         (0x01u)
#define TX_DM_RES_UP          (0x02u)
#define TX_DM_RES_DWN         (0x03u)
#define TX_DM_OD_LO           (0x04u)
#define TX_DM_OD_HI           (0x05u)
#define TX_DM_STRONG          (0x06u)
#define TX_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define TX_MASK               TX__MASK
#define TX_SHIFT              TX__SHIFT
#define TX_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define TX_PS                     (* (reg32 *) TX__PS)
/* Port Configuration */
#define TX_PC                     (* (reg32 *) TX__PC)
/* Data Register */
#define TX_DR                     (* (reg32 *) TX__DR)
/* Input Buffer Disable Override */
#define TX_INP_DIS                (* (reg32 *) TX__PC2)


#if defined(TX__INTSTAT)  /* Interrupt Registers */

    #define TX_INTSTAT                (* (reg32 *) TX__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define TX_DRIVE_MODE_SHIFT       (0x00u)
#define TX_DRIVE_MODE_MASK        (0x07u << TX_DRIVE_MODE_SHIFT)


#endif /* End Pins TX_H */


/* [] END OF FILE */
