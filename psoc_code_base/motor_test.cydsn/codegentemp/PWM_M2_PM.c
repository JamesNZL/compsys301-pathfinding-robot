/*******************************************************************************
* File Name: PWM_M2_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWM_M2.h"

static PWM_M2_backupStruct PWM_M2_backup;


/*******************************************************************************
* Function Name: PWM_M2_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_M2_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_M2_SaveConfig(void) 
{

    #if(!PWM_M2_UsingFixedFunction)
        #if(!PWM_M2_PWMModeIsCenterAligned)
            PWM_M2_backup.PWMPeriod = PWM_M2_ReadPeriod();
        #endif /* (!PWM_M2_PWMModeIsCenterAligned) */
        PWM_M2_backup.PWMUdb = PWM_M2_ReadCounter();
        #if (PWM_M2_UseStatus)
            PWM_M2_backup.InterruptMaskValue = PWM_M2_STATUS_MASK;
        #endif /* (PWM_M2_UseStatus) */

        #if(PWM_M2_DeadBandMode == PWM_M2__B_PWM__DBM_256_CLOCKS || \
            PWM_M2_DeadBandMode == PWM_M2__B_PWM__DBM_2_4_CLOCKS)
            PWM_M2_backup.PWMdeadBandValue = PWM_M2_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_M2_KillModeMinTime)
             PWM_M2_backup.PWMKillCounterPeriod = PWM_M2_ReadKillTime();
        #endif /* (PWM_M2_KillModeMinTime) */

        #if(PWM_M2_UseControl)
            PWM_M2_backup.PWMControlRegister = PWM_M2_ReadControlRegister();
        #endif /* (PWM_M2_UseControl) */
    #endif  /* (!PWM_M2_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_M2_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_M2_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_M2_RestoreConfig(void) 
{
        #if(!PWM_M2_UsingFixedFunction)
            #if(!PWM_M2_PWMModeIsCenterAligned)
                PWM_M2_WritePeriod(PWM_M2_backup.PWMPeriod);
            #endif /* (!PWM_M2_PWMModeIsCenterAligned) */

            PWM_M2_WriteCounter(PWM_M2_backup.PWMUdb);

            #if (PWM_M2_UseStatus)
                PWM_M2_STATUS_MASK = PWM_M2_backup.InterruptMaskValue;
            #endif /* (PWM_M2_UseStatus) */

            #if(PWM_M2_DeadBandMode == PWM_M2__B_PWM__DBM_256_CLOCKS || \
                PWM_M2_DeadBandMode == PWM_M2__B_PWM__DBM_2_4_CLOCKS)
                PWM_M2_WriteDeadTime(PWM_M2_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_M2_KillModeMinTime)
                PWM_M2_WriteKillTime(PWM_M2_backup.PWMKillCounterPeriod);
            #endif /* (PWM_M2_KillModeMinTime) */

            #if(PWM_M2_UseControl)
                PWM_M2_WriteControlRegister(PWM_M2_backup.PWMControlRegister);
            #endif /* (PWM_M2_UseControl) */
        #endif  /* (!PWM_M2_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_M2_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_M2_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_M2_Sleep(void) 
{
    #if(PWM_M2_UseControl)
        if(PWM_M2_CTRL_ENABLE == (PWM_M2_CONTROL & PWM_M2_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_M2_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_M2_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_M2_UseControl) */

    /* Stop component */
    PWM_M2_Stop();

    /* Save registers configuration */
    PWM_M2_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_M2_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_M2_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_M2_Wakeup(void) 
{
     /* Restore registers values */
    PWM_M2_RestoreConfig();

    if(PWM_M2_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_M2_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
