/*******************************************************************************
* File Name: NSS.c  
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
#include "NSS.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        NSS_PC =   (NSS_PC & \
                                (uint32)(~(uint32)(NSS_DRIVE_MODE_IND_MASK << (NSS_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (NSS_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: NSS_Write
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
void NSS_Write(uint8 value) 
{
    uint8 drVal = (uint8)(NSS_DR & (uint8)(~NSS_MASK));
    drVal = (drVal | ((uint8)(value << NSS_SHIFT) & NSS_MASK));
    NSS_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: NSS_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  NSS_DM_STRONG     Strong Drive 
*  NSS_DM_OD_HI      Open Drain, Drives High 
*  NSS_DM_OD_LO      Open Drain, Drives Low 
*  NSS_DM_RES_UP     Resistive Pull Up 
*  NSS_DM_RES_DWN    Resistive Pull Down 
*  NSS_DM_RES_UPDWN  Resistive Pull Up/Down 
*  NSS_DM_DIG_HIZ    High Impedance Digital 
*  NSS_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void NSS_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(NSS__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: NSS_Read
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
*  Macro NSS_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 NSS_Read(void) 
{
    return (uint8)((NSS_PS & NSS_MASK) >> NSS_SHIFT);
}


/*******************************************************************************
* Function Name: NSS_ReadDataReg
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
uint8 NSS_ReadDataReg(void) 
{
    return (uint8)((NSS_DR & NSS_MASK) >> NSS_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(NSS_INTSTAT) 

    /*******************************************************************************
    * Function Name: NSS_ClearInterrupt
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
    uint8 NSS_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(NSS_INTSTAT & NSS_MASK);
		NSS_INTSTAT = maskedStatus;
        return maskedStatus >> NSS_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
