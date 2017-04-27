/*******************************************************************************
* File Name: RX.h  
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

#if !defined(CY_PINS_RX_H) /* Pins RX_H */
#define CY_PINS_RX_H

#include "cytypes.h"
#include "cyfitter.h"
#include "RX_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    RX_Write(uint8 value) ;
void    RX_SetDriveMode(uint8 mode) ;
uint8   RX_ReadDataReg(void) ;
uint8   RX_Read(void) ;
uint8   RX_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define RX_DRIVE_MODE_BITS        (3)
#define RX_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - RX_DRIVE_MODE_BITS))

#define RX_DM_ALG_HIZ         (0x00u)
#define RX_DM_DIG_HIZ         (0x01u)
#define RX_DM_RES_UP          (0x02u)
#define RX_DM_RES_DWN         (0x03u)
#define RX_DM_OD_LO           (0x04u)
#define RX_DM_OD_HI           (0x05u)
#define RX_DM_STRONG          (0x06u)
#define RX_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define RX_MASK               RX__MASK
#define RX_SHIFT              RX__SHIFT
#define RX_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RX_PS                     (* (reg32 *) RX__PS)
/* Port Configuration */
#define RX_PC                     (* (reg32 *) RX__PC)
/* Data Register */
#define RX_DR                     (* (reg32 *) RX__DR)
/* Input Buffer Disable Override */
#define RX_INP_DIS                (* (reg32 *) RX__PC2)


#if defined(RX__INTSTAT)  /* Interrupt Registers */

    #define RX_INTSTAT                (* (reg32 *) RX__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define RX_DRIVE_MODE_SHIFT       (0x00u)
#define RX_DRIVE_MODE_MASK        (0x07u << RX_DRIVE_MODE_SHIFT)


#endif /* End Pins RX_H */


/* [] END OF FILE */
