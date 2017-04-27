/*******************************************************************************
* File Name: Wake_Up.c  
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
#include "Wake_Up.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Wake_Up_PC =   (Wake_Up_PC & \
                                (uint32)(~(uint32)(Wake_Up_DRIVE_MODE_IND_MASK << (Wake_Up_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Wake_Up_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Wake_Up_Write
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
void Wake_Up_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Wake_Up_DR & (uint8)(~Wake_Up_MASK));
    drVal = (drVal | ((uint8)(value << Wake_Up_SHIFT) & Wake_Up_MASK));
    Wake_Up_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Wake_Up_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Wake_Up_DM_STRONG     Strong Drive 
*  Wake_Up_DM_OD_HI      Open Drain, Drives High 
*  Wake_Up_DM_OD_LO      Open Drain, Drives Low 
*  Wake_Up_DM_RES_UP     Resistive Pull Up 
*  Wake_Up_DM_RES_DWN    Resistive Pull Down 
*  Wake_Up_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Wake_Up_DM_DIG_HIZ    High Impedance Digital 
*  Wake_Up_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Wake_Up_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Wake_Up__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Wake_Up_Read
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
*  Macro Wake_Up_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Wake_Up_Read(void) 
{
    return (uint8)((Wake_Up_PS & Wake_Up_MASK) >> Wake_Up_SHIFT);
}


/*******************************************************************************
* Function Name: Wake_Up_ReadDataReg
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
uint8 Wake_Up_ReadDataReg(void) 
{
    return (uint8)((Wake_Up_DR & Wake_Up_MASK) >> Wake_Up_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Wake_Up_INTSTAT) 

    /*******************************************************************************
    * Function Name: Wake_Up_ClearInterrupt
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
    uint8 Wake_Up_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Wake_Up_INTSTAT & Wake_Up_MASK);
		Wake_Up_INTSTAT = maskedStatus;
        return maskedStatus >> Wake_Up_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
