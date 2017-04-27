/*******************************************************************************
* File Name: motor_B.c  
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
#include "motor_B.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        motor_B_PC =   (motor_B_PC & \
                                (uint32)(~(uint32)(motor_B_DRIVE_MODE_IND_MASK << (motor_B_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (motor_B_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: motor_B_Write
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
void motor_B_Write(uint8 value) 
{
    uint8 drVal = (uint8)(motor_B_DR & (uint8)(~motor_B_MASK));
    drVal = (drVal | ((uint8)(value << motor_B_SHIFT) & motor_B_MASK));
    motor_B_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: motor_B_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  motor_B_DM_STRONG     Strong Drive 
*  motor_B_DM_OD_HI      Open Drain, Drives High 
*  motor_B_DM_OD_LO      Open Drain, Drives Low 
*  motor_B_DM_RES_UP     Resistive Pull Up 
*  motor_B_DM_RES_DWN    Resistive Pull Down 
*  motor_B_DM_RES_UPDWN  Resistive Pull Up/Down 
*  motor_B_DM_DIG_HIZ    High Impedance Digital 
*  motor_B_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void motor_B_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(motor_B__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: motor_B_Read
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
*  Macro motor_B_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 motor_B_Read(void) 
{
    return (uint8)((motor_B_PS & motor_B_MASK) >> motor_B_SHIFT);
}


/*******************************************************************************
* Function Name: motor_B_ReadDataReg
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
uint8 motor_B_ReadDataReg(void) 
{
    return (uint8)((motor_B_DR & motor_B_MASK) >> motor_B_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(motor_B_INTSTAT) 

    /*******************************************************************************
    * Function Name: motor_B_ClearInterrupt
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
    uint8 motor_B_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(motor_B_INTSTAT & motor_B_MASK);
		motor_B_INTSTAT = maskedStatus;
        return maskedStatus >> motor_B_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
