/*******************************************************************************
* File Name: Timer_Speed_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Timer_Speed.h"

static Timer_Speed_backupStruct Timer_Speed_backup;


/*******************************************************************************
* Function Name: Timer_Speed_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Speed_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timer_Speed_SaveConfig(void) 
{
    #if (!Timer_Speed_UsingFixedFunction)
        Timer_Speed_backup.TimerUdb = Timer_Speed_ReadCounter();
        Timer_Speed_backup.InterruptMaskValue = Timer_Speed_STATUS_MASK;
        #if (Timer_Speed_UsingHWCaptureCounter)
            Timer_Speed_backup.TimerCaptureCounter = Timer_Speed_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timer_Speed_UDB_CONTROL_REG_REMOVED)
            Timer_Speed_backup.TimerControlRegister = Timer_Speed_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timer_Speed_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Speed_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Speed_RestoreConfig(void) 
{   
    #if (!Timer_Speed_UsingFixedFunction)

        Timer_Speed_WriteCounter(Timer_Speed_backup.TimerUdb);
        Timer_Speed_STATUS_MASK =Timer_Speed_backup.InterruptMaskValue;
        #if (Timer_Speed_UsingHWCaptureCounter)
            Timer_Speed_SetCaptureCount(Timer_Speed_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timer_Speed_UDB_CONTROL_REG_REMOVED)
            Timer_Speed_WriteControlRegister(Timer_Speed_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timer_Speed_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Speed_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timer_Speed_Sleep(void) 
{
    #if(!Timer_Speed_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timer_Speed_CTRL_ENABLE == (Timer_Speed_CONTROL & Timer_Speed_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timer_Speed_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timer_Speed_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timer_Speed_Stop();
    Timer_Speed_SaveConfig();
}


/*******************************************************************************
* Function Name: Timer_Speed_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  Timer_Speed_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timer_Speed_Wakeup(void) 
{
    Timer_Speed_RestoreConfig();
    #if(!Timer_Speed_UDB_CONTROL_REG_REMOVED)
        if(Timer_Speed_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timer_Speed_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
