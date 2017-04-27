/*******************************************************************************
* File Name: door_sensor.c  
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
#include "door_sensor.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        door_sensor_PC =   (door_sensor_PC & \
                                (uint32)(~(uint32)(door_sensor_DRIVE_MODE_IND_MASK << (door_sensor_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (door_sensor_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: door_sensor_Write
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
void door_sensor_Write(uint8 value) 
{
    uint8 drVal = (uint8)(door_sensor_DR & (uint8)(~door_sensor_MASK));
    drVal = (drVal | ((uint8)(value << door_sensor_SHIFT) & door_sensor_MASK));
    door_sensor_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: door_sensor_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  door_sensor_DM_STRONG     Strong Drive 
*  door_sensor_DM_OD_HI      Open Drain, Drives High 
*  door_sensor_DM_OD_LO      Open Drain, Drives Low 
*  door_sensor_DM_RES_UP     Resistive Pull Up 
*  door_sensor_DM_RES_DWN    Resistive Pull Down 
*  door_sensor_DM_RES_UPDWN  Resistive Pull Up/Down 
*  door_sensor_DM_DIG_HIZ    High Impedance Digital 
*  door_sensor_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void door_sensor_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(door_sensor__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: door_sensor_Read
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
*  Macro door_sensor_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 door_sensor_Read(void) 
{
    return (uint8)((door_sensor_PS & door_sensor_MASK) >> door_sensor_SHIFT);
}


/*******************************************************************************
* Function Name: door_sensor_ReadDataReg
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
uint8 door_sensor_ReadDataReg(void) 
{
    return (uint8)((door_sensor_DR & door_sensor_MASK) >> door_sensor_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(door_sensor_INTSTAT) 

    /*******************************************************************************
    * Function Name: door_sensor_ClearInterrupt
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
    uint8 door_sensor_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(door_sensor_INTSTAT & door_sensor_MASK);
		door_sensor_INTSTAT = maskedStatus;
        return maskedStatus >> door_sensor_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
