/*******************************************************************************
* File Name: extend_sensor.c  
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
#include "extend_sensor.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        extend_sensor_PC =   (extend_sensor_PC & \
                                (uint32)(~(uint32)(extend_sensor_DRIVE_MODE_IND_MASK << (extend_sensor_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (extend_sensor_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: extend_sensor_Write
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
void extend_sensor_Write(uint8 value) 
{
    uint8 drVal = (uint8)(extend_sensor_DR & (uint8)(~extend_sensor_MASK));
    drVal = (drVal | ((uint8)(value << extend_sensor_SHIFT) & extend_sensor_MASK));
    extend_sensor_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: extend_sensor_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  extend_sensor_DM_STRONG     Strong Drive 
*  extend_sensor_DM_OD_HI      Open Drain, Drives High 
*  extend_sensor_DM_OD_LO      Open Drain, Drives Low 
*  extend_sensor_DM_RES_UP     Resistive Pull Up 
*  extend_sensor_DM_RES_DWN    Resistive Pull Down 
*  extend_sensor_DM_RES_UPDWN  Resistive Pull Up/Down 
*  extend_sensor_DM_DIG_HIZ    High Impedance Digital 
*  extend_sensor_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void extend_sensor_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(extend_sensor__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: extend_sensor_Read
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
*  Macro extend_sensor_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 extend_sensor_Read(void) 
{
    return (uint8)((extend_sensor_PS & extend_sensor_MASK) >> extend_sensor_SHIFT);
}


/*******************************************************************************
* Function Name: extend_sensor_ReadDataReg
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
uint8 extend_sensor_ReadDataReg(void) 
{
    return (uint8)((extend_sensor_DR & extend_sensor_MASK) >> extend_sensor_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(extend_sensor_INTSTAT) 

    /*******************************************************************************
    * Function Name: extend_sensor_ClearInterrupt
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
    uint8 extend_sensor_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(extend_sensor_INTSTAT & extend_sensor_MASK);
		extend_sensor_INTSTAT = maskedStatus;
        return maskedStatus >> extend_sensor_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */