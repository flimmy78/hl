/*******************************************************************************
* File Name: FSU_DO.h  
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

#if !defined(CY_PINS_FSU_DO_H) /* Pins FSU_DO_H */
#define CY_PINS_FSU_DO_H

#include "cytypes.h"
#include "cyfitter.h"
#include "FSU_DO_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    FSU_DO_Write(uint8 value) ;
void    FSU_DO_SetDriveMode(uint8 mode) ;
uint8   FSU_DO_ReadDataReg(void) ;
uint8   FSU_DO_Read(void) ;
uint8   FSU_DO_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define FSU_DO_DRIVE_MODE_BITS        (3)
#define FSU_DO_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - FSU_DO_DRIVE_MODE_BITS))

#define FSU_DO_DM_ALG_HIZ         (0x00u)
#define FSU_DO_DM_DIG_HIZ         (0x01u)
#define FSU_DO_DM_RES_UP          (0x02u)
#define FSU_DO_DM_RES_DWN         (0x03u)
#define FSU_DO_DM_OD_LO           (0x04u)
#define FSU_DO_DM_OD_HI           (0x05u)
#define FSU_DO_DM_STRONG          (0x06u)
#define FSU_DO_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define FSU_DO_MASK               FSU_DO__MASK
#define FSU_DO_SHIFT              FSU_DO__SHIFT
#define FSU_DO_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define FSU_DO_PS                     (* (reg32 *) FSU_DO__PS)
/* Port Configuration */
#define FSU_DO_PC                     (* (reg32 *) FSU_DO__PC)
/* Data Register */
#define FSU_DO_DR                     (* (reg32 *) FSU_DO__DR)
/* Input Buffer Disable Override */
#define FSU_DO_INP_DIS                (* (reg32 *) FSU_DO__PC2)


#if defined(FSU_DO__INTSTAT)  /* Interrupt Registers */

    #define FSU_DO_INTSTAT                (* (reg32 *) FSU_DO__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define FSU_DO_DRIVE_MODE_SHIFT       (0x00u)
#define FSU_DO_DRIVE_MODE_MASK        (0x07u << FSU_DO_DRIVE_MODE_SHIFT)


#endif /* End Pins FSU_DO_H */


/* [] END OF FILE */
