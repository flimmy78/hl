/*******************************************************************************
* File Name: POWERON_OUT.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "POWERON_OUT.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        POWERON_OUT_PC =   (POWERON_OUT_PC & \
                                (uint32)(~(uint32)(POWERON_OUT_DRIVE_MODE_IND_MASK << (POWERON_OUT_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (POWERON_OUT_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: POWERON_OUT_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void POWERON_OUT_Write(uint8 value) 
{
    uint8 drVal = (uint8)(POWERON_OUT_DR & (uint8)(~POWERON_OUT_MASK));
    drVal = (drVal | ((uint8)(value << POWERON_OUT_SHIFT) & POWERON_OUT_MASK));
    POWERON_OUT_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: POWERON_OUT_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  POWERON_OUT_DM_STRONG     Strong Drive 
*  POWERON_OUT_DM_OD_HI      Open Drain, Drives High 
*  POWERON_OUT_DM_OD_LO      Open Drain, Drives Low 
*  POWERON_OUT_DM_RES_UP     Resistive Pull Up 
*  POWERON_OUT_DM_RES_DWN    Resistive Pull Down 
*  POWERON_OUT_DM_RES_UPDWN  Resistive Pull Up/Down 
*  POWERON_OUT_DM_DIG_HIZ    High Impedance Digital 
*  POWERON_OUT_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void POWERON_OUT_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(POWERON_OUT__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: POWERON_OUT_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro POWERON_OUT_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 POWERON_OUT_Read(void) 
{
    return (uint8)((POWERON_OUT_PS & POWERON_OUT_MASK) >> POWERON_OUT_SHIFT);
}


/*******************************************************************************
* Function Name: POWERON_OUT_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 POWERON_OUT_ReadDataReg(void) 
{
    return (uint8)((POWERON_OUT_DR & POWERON_OUT_MASK) >> POWERON_OUT_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(POWERON_OUT_INTSTAT) 

    /*******************************************************************************
    * Function Name: POWERON_OUT_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 POWERON_OUT_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(POWERON_OUT_INTSTAT & POWERON_OUT_MASK);
		POWERON_OUT_INTSTAT = maskedStatus;
        return maskedStatus >> POWERON_OUT_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
