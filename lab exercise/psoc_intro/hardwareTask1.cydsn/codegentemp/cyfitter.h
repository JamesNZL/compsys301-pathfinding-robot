/*******************************************************************************
* File Name: cyfitter.h
* 
* PSoC Creator  4.2
*
* Description:
* 
* This file is automatically generated by PSoC Creator.
*
********************************************************************************
* Copyright (c) 2007-2018 Cypress Semiconductor.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
********************************************************************************/

#ifndef INCLUDED_CYFITTER_H
#define INCLUDED_CYFITTER_H
#include "cydevice.h"
#include "cydevice_trm.h"

/* Pin_1 */
#define Pin_1__0__INTTYPE CYREG_PICU2_INTTYPE5
#define Pin_1__0__MASK 0x20u
#define Pin_1__0__PC CYREG_PRT2_PC5
#define Pin_1__0__PORT 2u
#define Pin_1__0__SHIFT 5u
#define Pin_1__AG CYREG_PRT2_AG
#define Pin_1__AMUX CYREG_PRT2_AMUX
#define Pin_1__BIE CYREG_PRT2_BIE
#define Pin_1__BIT_MASK CYREG_PRT2_BIT_MASK
#define Pin_1__BYP CYREG_PRT2_BYP
#define Pin_1__CTL CYREG_PRT2_CTL
#define Pin_1__DM0 CYREG_PRT2_DM0
#define Pin_1__DM1 CYREG_PRT2_DM1
#define Pin_1__DM2 CYREG_PRT2_DM2
#define Pin_1__DR CYREG_PRT2_DR
#define Pin_1__INP_DIS CYREG_PRT2_INP_DIS
#define Pin_1__INTTYPE_BASE CYDEV_PICU_INTTYPE_PICU2_BASE
#define Pin_1__LCD_COM_SEG CYREG_PRT2_LCD_COM_SEG
#define Pin_1__LCD_EN CYREG_PRT2_LCD_EN
#define Pin_1__MASK 0x20u
#define Pin_1__PORT 2u
#define Pin_1__PRT CYREG_PRT2_PRT
#define Pin_1__PRTDSI__CAPS_SEL CYREG_PRT2_CAPS_SEL
#define Pin_1__PRTDSI__DBL_SYNC_IN CYREG_PRT2_DBL_SYNC_IN
#define Pin_1__PRTDSI__OE_SEL0 CYREG_PRT2_OE_SEL0
#define Pin_1__PRTDSI__OE_SEL1 CYREG_PRT2_OE_SEL1
#define Pin_1__PRTDSI__OUT_SEL0 CYREG_PRT2_OUT_SEL0
#define Pin_1__PRTDSI__OUT_SEL1 CYREG_PRT2_OUT_SEL1
#define Pin_1__PRTDSI__SYNC_OUT CYREG_PRT2_SYNC_OUT
#define Pin_1__PS CYREG_PRT2_PS
#define Pin_1__SHIFT 5u
#define Pin_1__SLW CYREG_PRT2_SLW

/* Pin_2 */
#define Pin_2__0__INTTYPE CYREG_PICU2_INTTYPE1
#define Pin_2__0__MASK 0x02u
#define Pin_2__0__PC CYREG_PRT2_PC1
#define Pin_2__0__PORT 2u
#define Pin_2__0__SHIFT 1u
#define Pin_2__AG CYREG_PRT2_AG
#define Pin_2__AMUX CYREG_PRT2_AMUX
#define Pin_2__BIE CYREG_PRT2_BIE
#define Pin_2__BIT_MASK CYREG_PRT2_BIT_MASK
#define Pin_2__BYP CYREG_PRT2_BYP
#define Pin_2__CTL CYREG_PRT2_CTL
#define Pin_2__DM0 CYREG_PRT2_DM0
#define Pin_2__DM1 CYREG_PRT2_DM1
#define Pin_2__DM2 CYREG_PRT2_DM2
#define Pin_2__DR CYREG_PRT2_DR
#define Pin_2__INP_DIS CYREG_PRT2_INP_DIS
#define Pin_2__INTTYPE_BASE CYDEV_PICU_INTTYPE_PICU2_BASE
#define Pin_2__LCD_COM_SEG CYREG_PRT2_LCD_COM_SEG
#define Pin_2__LCD_EN CYREG_PRT2_LCD_EN
#define Pin_2__MASK 0x02u
#define Pin_2__PORT 2u
#define Pin_2__PRT CYREG_PRT2_PRT
#define Pin_2__PRTDSI__CAPS_SEL CYREG_PRT2_CAPS_SEL
#define Pin_2__PRTDSI__DBL_SYNC_IN CYREG_PRT2_DBL_SYNC_IN
#define Pin_2__PRTDSI__OE_SEL0 CYREG_PRT2_OE_SEL0
#define Pin_2__PRTDSI__OE_SEL1 CYREG_PRT2_OE_SEL1
#define Pin_2__PRTDSI__OUT_SEL0 CYREG_PRT2_OUT_SEL0
#define Pin_2__PRTDSI__OUT_SEL1 CYREG_PRT2_OUT_SEL1
#define Pin_2__PRTDSI__SYNC_OUT CYREG_PRT2_SYNC_OUT
#define Pin_2__PS CYREG_PRT2_PS
#define Pin_2__SHIFT 1u
#define Pin_2__SLW CYREG_PRT2_SLW

/* Timer_1 */
#define Timer_1_TimerHW__CAP0 CYREG_TMR0_CAP0
#define Timer_1_TimerHW__CAP1 CYREG_TMR0_CAP1
#define Timer_1_TimerHW__CFG0 CYREG_TMR0_CFG0
#define Timer_1_TimerHW__CFG1 CYREG_TMR0_CFG1
#define Timer_1_TimerHW__CFG2 CYREG_TMR0_CFG2
#define Timer_1_TimerHW__CNT_CMP0 CYREG_TMR0_CNT_CMP0
#define Timer_1_TimerHW__CNT_CMP1 CYREG_TMR0_CNT_CMP1
#define Timer_1_TimerHW__PER0 CYREG_TMR0_PER0
#define Timer_1_TimerHW__PER1 CYREG_TMR0_PER1
#define Timer_1_TimerHW__PM_ACT_CFG CYREG_PM_ACT_CFG3
#define Timer_1_TimerHW__PM_ACT_MSK 0x01u
#define Timer_1_TimerHW__PM_STBY_CFG CYREG_PM_STBY_CFG3
#define Timer_1_TimerHW__PM_STBY_MSK 0x01u
#define Timer_1_TimerHW__RT0 CYREG_TMR0_RT0
#define Timer_1_TimerHW__RT1 CYREG_TMR0_RT1
#define Timer_1_TimerHW__SR0 CYREG_TMR0_SR0

/* USBUART */
#define USBUART_arb_int__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define USBUART_arb_int__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define USBUART_arb_int__INTC_MASK 0x400000u
#define USBUART_arb_int__INTC_NUMBER 22u
#define USBUART_arb_int__INTC_PRIOR_NUM 7u
#define USBUART_arb_int__INTC_PRIOR_REG CYREG_NVIC_PRI_22
#define USBUART_arb_int__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define USBUART_arb_int__INTC_SET_PD_REG CYREG_NVIC_SETPEND0
#define USBUART_bus_reset__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define USBUART_bus_reset__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define USBUART_bus_reset__INTC_MASK 0x800000u
#define USBUART_bus_reset__INTC_NUMBER 23u
#define USBUART_bus_reset__INTC_PRIOR_NUM 7u
#define USBUART_bus_reset__INTC_PRIOR_REG CYREG_NVIC_PRI_23
#define USBUART_bus_reset__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define USBUART_bus_reset__INTC_SET_PD_REG CYREG_NVIC_SETPEND0
#define USBUART_Dm__0__INTTYPE CYREG_PICU15_INTTYPE7
#define USBUART_Dm__0__MASK 0x80u
#define USBUART_Dm__0__PC CYREG_IO_PC_PRT15_7_6_PC1
#define USBUART_Dm__0__PORT 15u
#define USBUART_Dm__0__SHIFT 7u
#define USBUART_Dm__AG CYREG_PRT15_AG
#define USBUART_Dm__AMUX CYREG_PRT15_AMUX
#define USBUART_Dm__BIE CYREG_PRT15_BIE
#define USBUART_Dm__BIT_MASK CYREG_PRT15_BIT_MASK
#define USBUART_Dm__BYP CYREG_PRT15_BYP
#define USBUART_Dm__CTL CYREG_PRT15_CTL
#define USBUART_Dm__DM0 CYREG_PRT15_DM0
#define USBUART_Dm__DM1 CYREG_PRT15_DM1
#define USBUART_Dm__DM2 CYREG_PRT15_DM2
#define USBUART_Dm__DR CYREG_PRT15_DR
#define USBUART_Dm__INP_DIS CYREG_PRT15_INP_DIS
#define USBUART_Dm__INTTYPE_BASE CYDEV_PICU_INTTYPE_PICU15_BASE
#define USBUART_Dm__LCD_COM_SEG CYREG_PRT15_LCD_COM_SEG
#define USBUART_Dm__LCD_EN CYREG_PRT15_LCD_EN
#define USBUART_Dm__MASK 0x80u
#define USBUART_Dm__PORT 15u
#define USBUART_Dm__PRT CYREG_PRT15_PRT
#define USBUART_Dm__PRTDSI__CAPS_SEL CYREG_PRT15_CAPS_SEL
#define USBUART_Dm__PRTDSI__DBL_SYNC_IN CYREG_PRT15_DBL_SYNC_IN
#define USBUART_Dm__PRTDSI__OE_SEL0 CYREG_PRT15_OE_SEL0
#define USBUART_Dm__PRTDSI__OE_SEL1 CYREG_PRT15_OE_SEL1
#define USBUART_Dm__PRTDSI__OUT_SEL0 CYREG_PRT15_OUT_SEL0
#define USBUART_Dm__PRTDSI__OUT_SEL1 CYREG_PRT15_OUT_SEL1
#define USBUART_Dm__PRTDSI__SYNC_OUT CYREG_PRT15_SYNC_OUT
#define USBUART_Dm__PS CYREG_PRT15_PS
#define USBUART_Dm__SHIFT 7u
#define USBUART_Dm__SLW CYREG_PRT15_SLW
#define USBUART_Dp__0__INTTYPE CYREG_PICU15_INTTYPE6
#define USBUART_Dp__0__MASK 0x40u
#define USBUART_Dp__0__PC CYREG_IO_PC_PRT15_7_6_PC0
#define USBUART_Dp__0__PORT 15u
#define USBUART_Dp__0__SHIFT 6u
#define USBUART_Dp__AG CYREG_PRT15_AG
#define USBUART_Dp__AMUX CYREG_PRT15_AMUX
#define USBUART_Dp__BIE CYREG_PRT15_BIE
#define USBUART_Dp__BIT_MASK CYREG_PRT15_BIT_MASK
#define USBUART_Dp__BYP CYREG_PRT15_BYP
#define USBUART_Dp__CTL CYREG_PRT15_CTL
#define USBUART_Dp__DM0 CYREG_PRT15_DM0
#define USBUART_Dp__DM1 CYREG_PRT15_DM1
#define USBUART_Dp__DM2 CYREG_PRT15_DM2
#define USBUART_Dp__DR CYREG_PRT15_DR
#define USBUART_Dp__INP_DIS CYREG_PRT15_INP_DIS
#define USBUART_Dp__INTSTAT CYREG_PICU15_INTSTAT
#define USBUART_Dp__INTTYPE_BASE CYDEV_PICU_INTTYPE_PICU15_BASE
#define USBUART_Dp__LCD_COM_SEG CYREG_PRT15_LCD_COM_SEG
#define USBUART_Dp__LCD_EN CYREG_PRT15_LCD_EN
#define USBUART_Dp__MASK 0x40u
#define USBUART_Dp__PORT 15u
#define USBUART_Dp__PRT CYREG_PRT15_PRT
#define USBUART_Dp__PRTDSI__CAPS_SEL CYREG_PRT15_CAPS_SEL
#define USBUART_Dp__PRTDSI__DBL_SYNC_IN CYREG_PRT15_DBL_SYNC_IN
#define USBUART_Dp__PRTDSI__OE_SEL0 CYREG_PRT15_OE_SEL0
#define USBUART_Dp__PRTDSI__OE_SEL1 CYREG_PRT15_OE_SEL1
#define USBUART_Dp__PRTDSI__OUT_SEL0 CYREG_PRT15_OUT_SEL0
#define USBUART_Dp__PRTDSI__OUT_SEL1 CYREG_PRT15_OUT_SEL1
#define USBUART_Dp__PRTDSI__SYNC_OUT CYREG_PRT15_SYNC_OUT
#define USBUART_Dp__PS CYREG_PRT15_PS
#define USBUART_Dp__SHIFT 6u
#define USBUART_Dp__SLW CYREG_PRT15_SLW
#define USBUART_Dp__SNAP CYREG_PICU_15_SNAP_15
#define USBUART_dp_int__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define USBUART_dp_int__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define USBUART_dp_int__INTC_MASK 0x1000u
#define USBUART_dp_int__INTC_NUMBER 12u
#define USBUART_dp_int__INTC_PRIOR_NUM 7u
#define USBUART_dp_int__INTC_PRIOR_REG CYREG_NVIC_PRI_12
#define USBUART_dp_int__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define USBUART_dp_int__INTC_SET_PD_REG CYREG_NVIC_SETPEND0
#define USBUART_ep_0__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define USBUART_ep_0__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define USBUART_ep_0__INTC_MASK 0x1000000u
#define USBUART_ep_0__INTC_NUMBER 24u
#define USBUART_ep_0__INTC_PRIOR_NUM 7u
#define USBUART_ep_0__INTC_PRIOR_REG CYREG_NVIC_PRI_24
#define USBUART_ep_0__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define USBUART_ep_0__INTC_SET_PD_REG CYREG_NVIC_SETPEND0
#define USBUART_ep_1__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define USBUART_ep_1__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define USBUART_ep_1__INTC_MASK 0x02u
#define USBUART_ep_1__INTC_NUMBER 1u
#define USBUART_ep_1__INTC_PRIOR_NUM 7u
#define USBUART_ep_1__INTC_PRIOR_REG CYREG_NVIC_PRI_1
#define USBUART_ep_1__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define USBUART_ep_1__INTC_SET_PD_REG CYREG_NVIC_SETPEND0
#define USBUART_ep_2__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define USBUART_ep_2__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define USBUART_ep_2__INTC_MASK 0x04u
#define USBUART_ep_2__INTC_NUMBER 2u
#define USBUART_ep_2__INTC_PRIOR_NUM 7u
#define USBUART_ep_2__INTC_PRIOR_REG CYREG_NVIC_PRI_2
#define USBUART_ep_2__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define USBUART_ep_2__INTC_SET_PD_REG CYREG_NVIC_SETPEND0
#define USBUART_ep_3__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define USBUART_ep_3__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define USBUART_ep_3__INTC_MASK 0x08u
#define USBUART_ep_3__INTC_NUMBER 3u
#define USBUART_ep_3__INTC_PRIOR_NUM 7u
#define USBUART_ep_3__INTC_PRIOR_REG CYREG_NVIC_PRI_3
#define USBUART_ep_3__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define USBUART_ep_3__INTC_SET_PD_REG CYREG_NVIC_SETPEND0
#define USBUART_sof_int__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define USBUART_sof_int__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define USBUART_sof_int__INTC_MASK 0x200000u
#define USBUART_sof_int__INTC_NUMBER 21u
#define USBUART_sof_int__INTC_PRIOR_NUM 7u
#define USBUART_sof_int__INTC_PRIOR_REG CYREG_NVIC_PRI_21
#define USBUART_sof_int__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define USBUART_sof_int__INTC_SET_PD_REG CYREG_NVIC_SETPEND0
#define USBUART_USB__ARB_CFG CYREG_USB_ARB_CFG
#define USBUART_USB__ARB_EP1_CFG CYREG_USB_ARB_EP1_CFG
#define USBUART_USB__ARB_EP1_INT_EN CYREG_USB_ARB_EP1_INT_EN
#define USBUART_USB__ARB_EP1_SR CYREG_USB_ARB_EP1_SR
#define USBUART_USB__ARB_EP2_CFG CYREG_USB_ARB_EP2_CFG
#define USBUART_USB__ARB_EP2_INT_EN CYREG_USB_ARB_EP2_INT_EN
#define USBUART_USB__ARB_EP2_SR CYREG_USB_ARB_EP2_SR
#define USBUART_USB__ARB_EP3_CFG CYREG_USB_ARB_EP3_CFG
#define USBUART_USB__ARB_EP3_INT_EN CYREG_USB_ARB_EP3_INT_EN
#define USBUART_USB__ARB_EP3_SR CYREG_USB_ARB_EP3_SR
#define USBUART_USB__ARB_EP4_CFG CYREG_USB_ARB_EP4_CFG
#define USBUART_USB__ARB_EP4_INT_EN CYREG_USB_ARB_EP4_INT_EN
#define USBUART_USB__ARB_EP4_SR CYREG_USB_ARB_EP4_SR
#define USBUART_USB__ARB_EP5_CFG CYREG_USB_ARB_EP5_CFG
#define USBUART_USB__ARB_EP5_INT_EN CYREG_USB_ARB_EP5_INT_EN
#define USBUART_USB__ARB_EP5_SR CYREG_USB_ARB_EP5_SR
#define USBUART_USB__ARB_EP6_CFG CYREG_USB_ARB_EP6_CFG
#define USBUART_USB__ARB_EP6_INT_EN CYREG_USB_ARB_EP6_INT_EN
#define USBUART_USB__ARB_EP6_SR CYREG_USB_ARB_EP6_SR
#define USBUART_USB__ARB_EP7_CFG CYREG_USB_ARB_EP7_CFG
#define USBUART_USB__ARB_EP7_INT_EN CYREG_USB_ARB_EP7_INT_EN
#define USBUART_USB__ARB_EP7_SR CYREG_USB_ARB_EP7_SR
#define USBUART_USB__ARB_EP8_CFG CYREG_USB_ARB_EP8_CFG
#define USBUART_USB__ARB_EP8_INT_EN CYREG_USB_ARB_EP8_INT_EN
#define USBUART_USB__ARB_EP8_SR CYREG_USB_ARB_EP8_SR
#define USBUART_USB__ARB_INT_EN CYREG_USB_ARB_INT_EN
#define USBUART_USB__ARB_INT_SR CYREG_USB_ARB_INT_SR
#define USBUART_USB__ARB_RW1_DR CYREG_USB_ARB_RW1_DR
#define USBUART_USB__ARB_RW1_RA CYREG_USB_ARB_RW1_RA
#define USBUART_USB__ARB_RW1_RA_MSB CYREG_USB_ARB_RW1_RA_MSB
#define USBUART_USB__ARB_RW1_WA CYREG_USB_ARB_RW1_WA
#define USBUART_USB__ARB_RW1_WA_MSB CYREG_USB_ARB_RW1_WA_MSB
#define USBUART_USB__ARB_RW2_DR CYREG_USB_ARB_RW2_DR
#define USBUART_USB__ARB_RW2_RA CYREG_USB_ARB_RW2_RA
#define USBUART_USB__ARB_RW2_RA_MSB CYREG_USB_ARB_RW2_RA_MSB
#define USBUART_USB__ARB_RW2_WA CYREG_USB_ARB_RW2_WA
#define USBUART_USB__ARB_RW2_WA_MSB CYREG_USB_ARB_RW2_WA_MSB
#define USBUART_USB__ARB_RW3_DR CYREG_USB_ARB_RW3_DR
#define USBUART_USB__ARB_RW3_RA CYREG_USB_ARB_RW3_RA
#define USBUART_USB__ARB_RW3_RA_MSB CYREG_USB_ARB_RW3_RA_MSB
#define USBUART_USB__ARB_RW3_WA CYREG_USB_ARB_RW3_WA
#define USBUART_USB__ARB_RW3_WA_MSB CYREG_USB_ARB_RW3_WA_MSB
#define USBUART_USB__ARB_RW4_DR CYREG_USB_ARB_RW4_DR
#define USBUART_USB__ARB_RW4_RA CYREG_USB_ARB_RW4_RA
#define USBUART_USB__ARB_RW4_RA_MSB CYREG_USB_ARB_RW4_RA_MSB
#define USBUART_USB__ARB_RW4_WA CYREG_USB_ARB_RW4_WA
#define USBUART_USB__ARB_RW4_WA_MSB CYREG_USB_ARB_RW4_WA_MSB
#define USBUART_USB__ARB_RW5_DR CYREG_USB_ARB_RW5_DR
#define USBUART_USB__ARB_RW5_RA CYREG_USB_ARB_RW5_RA
#define USBUART_USB__ARB_RW5_RA_MSB CYREG_USB_ARB_RW5_RA_MSB
#define USBUART_USB__ARB_RW5_WA CYREG_USB_ARB_RW5_WA
#define USBUART_USB__ARB_RW5_WA_MSB CYREG_USB_ARB_RW5_WA_MSB
#define USBUART_USB__ARB_RW6_DR CYREG_USB_ARB_RW6_DR
#define USBUART_USB__ARB_RW6_RA CYREG_USB_ARB_RW6_RA
#define USBUART_USB__ARB_RW6_RA_MSB CYREG_USB_ARB_RW6_RA_MSB
#define USBUART_USB__ARB_RW6_WA CYREG_USB_ARB_RW6_WA
#define USBUART_USB__ARB_RW6_WA_MSB CYREG_USB_ARB_RW6_WA_MSB
#define USBUART_USB__ARB_RW7_DR CYREG_USB_ARB_RW7_DR
#define USBUART_USB__ARB_RW7_RA CYREG_USB_ARB_RW7_RA
#define USBUART_USB__ARB_RW7_RA_MSB CYREG_USB_ARB_RW7_RA_MSB
#define USBUART_USB__ARB_RW7_WA CYREG_USB_ARB_RW7_WA
#define USBUART_USB__ARB_RW7_WA_MSB CYREG_USB_ARB_RW7_WA_MSB
#define USBUART_USB__ARB_RW8_DR CYREG_USB_ARB_RW8_DR
#define USBUART_USB__ARB_RW8_RA CYREG_USB_ARB_RW8_RA
#define USBUART_USB__ARB_RW8_RA_MSB CYREG_USB_ARB_RW8_RA_MSB
#define USBUART_USB__ARB_RW8_WA CYREG_USB_ARB_RW8_WA
#define USBUART_USB__ARB_RW8_WA_MSB CYREG_USB_ARB_RW8_WA_MSB
#define USBUART_USB__BUF_SIZE CYREG_USB_BUF_SIZE
#define USBUART_USB__BUS_RST_CNT CYREG_USB_BUS_RST_CNT
#define USBUART_USB__CR0 CYREG_USB_CR0
#define USBUART_USB__CR1 CYREG_USB_CR1
#define USBUART_USB__CWA CYREG_USB_CWA
#define USBUART_USB__CWA_MSB CYREG_USB_CWA_MSB
#define USBUART_USB__DMA_THRES CYREG_USB_DMA_THRES
#define USBUART_USB__DMA_THRES_MSB CYREG_USB_DMA_THRES_MSB
#define USBUART_USB__DYN_RECONFIG CYREG_USB_DYN_RECONFIG
#define USBUART_USB__EP_ACTIVE CYREG_USB_EP_ACTIVE
#define USBUART_USB__EP_TYPE CYREG_USB_EP_TYPE
#define USBUART_USB__EP0_CNT CYREG_USB_EP0_CNT
#define USBUART_USB__EP0_CR CYREG_USB_EP0_CR
#define USBUART_USB__EP0_DR0 CYREG_USB_EP0_DR0
#define USBUART_USB__EP0_DR1 CYREG_USB_EP0_DR1
#define USBUART_USB__EP0_DR2 CYREG_USB_EP0_DR2
#define USBUART_USB__EP0_DR3 CYREG_USB_EP0_DR3
#define USBUART_USB__EP0_DR4 CYREG_USB_EP0_DR4
#define USBUART_USB__EP0_DR5 CYREG_USB_EP0_DR5
#define USBUART_USB__EP0_DR6 CYREG_USB_EP0_DR6
#define USBUART_USB__EP0_DR7 CYREG_USB_EP0_DR7
#define USBUART_USB__MEM_DATA CYREG_USB_MEM_DATA_MBASE
#define USBUART_USB__PM_ACT_CFG CYREG_PM_ACT_CFG5
#define USBUART_USB__PM_ACT_MSK 0x01u
#define USBUART_USB__PM_STBY_CFG CYREG_PM_STBY_CFG5
#define USBUART_USB__PM_STBY_MSK 0x01u
#define USBUART_USB__SIE_EP_INT_EN CYREG_USB_SIE_EP_INT_EN
#define USBUART_USB__SIE_EP_INT_SR CYREG_USB_SIE_EP_INT_SR
#define USBUART_USB__SIE_EP1_CNT0 CYREG_USB_SIE_EP1_CNT0
#define USBUART_USB__SIE_EP1_CNT1 CYREG_USB_SIE_EP1_CNT1
#define USBUART_USB__SIE_EP1_CR0 CYREG_USB_SIE_EP1_CR0
#define USBUART_USB__SIE_EP2_CNT0 CYREG_USB_SIE_EP2_CNT0
#define USBUART_USB__SIE_EP2_CNT1 CYREG_USB_SIE_EP2_CNT1
#define USBUART_USB__SIE_EP2_CR0 CYREG_USB_SIE_EP2_CR0
#define USBUART_USB__SIE_EP3_CNT0 CYREG_USB_SIE_EP3_CNT0
#define USBUART_USB__SIE_EP3_CNT1 CYREG_USB_SIE_EP3_CNT1
#define USBUART_USB__SIE_EP3_CR0 CYREG_USB_SIE_EP3_CR0
#define USBUART_USB__SIE_EP4_CNT0 CYREG_USB_SIE_EP4_CNT0
#define USBUART_USB__SIE_EP4_CNT1 CYREG_USB_SIE_EP4_CNT1
#define USBUART_USB__SIE_EP4_CR0 CYREG_USB_SIE_EP4_CR0
#define USBUART_USB__SIE_EP5_CNT0 CYREG_USB_SIE_EP5_CNT0
#define USBUART_USB__SIE_EP5_CNT1 CYREG_USB_SIE_EP5_CNT1
#define USBUART_USB__SIE_EP5_CR0 CYREG_USB_SIE_EP5_CR0
#define USBUART_USB__SIE_EP6_CNT0 CYREG_USB_SIE_EP6_CNT0
#define USBUART_USB__SIE_EP6_CNT1 CYREG_USB_SIE_EP6_CNT1
#define USBUART_USB__SIE_EP6_CR0 CYREG_USB_SIE_EP6_CR0
#define USBUART_USB__SIE_EP7_CNT0 CYREG_USB_SIE_EP7_CNT0
#define USBUART_USB__SIE_EP7_CNT1 CYREG_USB_SIE_EP7_CNT1
#define USBUART_USB__SIE_EP7_CR0 CYREG_USB_SIE_EP7_CR0
#define USBUART_USB__SIE_EP8_CNT0 CYREG_USB_SIE_EP8_CNT0
#define USBUART_USB__SIE_EP8_CNT1 CYREG_USB_SIE_EP8_CNT1
#define USBUART_USB__SIE_EP8_CR0 CYREG_USB_SIE_EP8_CR0
#define USBUART_USB__SOF0 CYREG_USB_SOF0
#define USBUART_USB__SOF1 CYREG_USB_SOF1
#define USBUART_USB__USB_CLK_EN CYREG_USB_USB_CLK_EN
#define USBUART_USB__USBIO_CR0 CYREG_USB_USBIO_CR0
#define USBUART_USB__USBIO_CR1 CYREG_USB_USBIO_CR1

/* VDAC8_1 */
#define VDAC8_1_viDAC8__CR0 CYREG_DAC2_CR0
#define VDAC8_1_viDAC8__CR1 CYREG_DAC2_CR1
#define VDAC8_1_viDAC8__D CYREG_DAC2_D
#define VDAC8_1_viDAC8__PM_ACT_CFG CYREG_PM_ACT_CFG8
#define VDAC8_1_viDAC8__PM_ACT_MSK 0x04u
#define VDAC8_1_viDAC8__PM_STBY_CFG CYREG_PM_STBY_CFG8
#define VDAC8_1_viDAC8__PM_STBY_MSK 0x04u
#define VDAC8_1_viDAC8__STROBE CYREG_DAC2_STROBE
#define VDAC8_1_viDAC8__SW0 CYREG_DAC2_SW0
#define VDAC8_1_viDAC8__SW2 CYREG_DAC2_SW2
#define VDAC8_1_viDAC8__SW3 CYREG_DAC2_SW3
#define VDAC8_1_viDAC8__SW4 CYREG_DAC2_SW4
#define VDAC8_1_viDAC8__TR CYREG_DAC2_TR
#define VDAC8_1_viDAC8__TRIM__M1 CYREG_FLSHID_CUST_TABLES_DAC2_M1
#define VDAC8_1_viDAC8__TRIM__M2 CYREG_FLSHID_CUST_TABLES_DAC2_M2
#define VDAC8_1_viDAC8__TRIM__M3 CYREG_FLSHID_CUST_TABLES_DAC2_M3
#define VDAC8_1_viDAC8__TRIM__M4 CYREG_FLSHID_CUST_TABLES_DAC2_M4
#define VDAC8_1_viDAC8__TRIM__M5 CYREG_FLSHID_CUST_TABLES_DAC2_M5
#define VDAC8_1_viDAC8__TRIM__M6 CYREG_FLSHID_CUST_TABLES_DAC2_M6
#define VDAC8_1_viDAC8__TRIM__M7 CYREG_FLSHID_CUST_TABLES_DAC2_M7
#define VDAC8_1_viDAC8__TRIM__M8 CYREG_FLSHID_CUST_TABLES_DAC2_M8
#define VDAC8_1_viDAC8__TST CYREG_DAC2_TST

/* isr_EOC */
#define isr_EOC__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define isr_EOC__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define isr_EOC__INTC_MASK 0x10u
#define isr_EOC__INTC_NUMBER 4u
#define isr_EOC__INTC_PRIOR_NUM 7u
#define isr_EOC__INTC_PRIOR_REG CYREG_NVIC_PRI_4
#define isr_EOC__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define isr_EOC__INTC_SET_PD_REG CYREG_NVIC_SETPEND0

/* ADC_SAR_1 */
#define ADC_SAR_1_ADC_SAR__CLK CYREG_SAR0_CLK
#define ADC_SAR_1_ADC_SAR__CSR0 CYREG_SAR0_CSR0
#define ADC_SAR_1_ADC_SAR__CSR1 CYREG_SAR0_CSR1
#define ADC_SAR_1_ADC_SAR__CSR2 CYREG_SAR0_CSR2
#define ADC_SAR_1_ADC_SAR__CSR3 CYREG_SAR0_CSR3
#define ADC_SAR_1_ADC_SAR__CSR4 CYREG_SAR0_CSR4
#define ADC_SAR_1_ADC_SAR__CSR5 CYREG_SAR0_CSR5
#define ADC_SAR_1_ADC_SAR__CSR6 CYREG_SAR0_CSR6
#define ADC_SAR_1_ADC_SAR__PM_ACT_CFG CYREG_PM_ACT_CFG11
#define ADC_SAR_1_ADC_SAR__PM_ACT_MSK 0x01u
#define ADC_SAR_1_ADC_SAR__PM_STBY_CFG CYREG_PM_STBY_CFG11
#define ADC_SAR_1_ADC_SAR__PM_STBY_MSK 0x01u
#define ADC_SAR_1_ADC_SAR__SW0 CYREG_SAR0_SW0
#define ADC_SAR_1_ADC_SAR__SW2 CYREG_SAR0_SW2
#define ADC_SAR_1_ADC_SAR__SW3 CYREG_SAR0_SW3
#define ADC_SAR_1_ADC_SAR__SW4 CYREG_SAR0_SW4
#define ADC_SAR_1_ADC_SAR__SW6 CYREG_SAR0_SW6
#define ADC_SAR_1_ADC_SAR__TR0 CYREG_SAR0_TR0
#define ADC_SAR_1_ADC_SAR__WRK0 CYREG_SAR0_WRK0
#define ADC_SAR_1_ADC_SAR__WRK1 CYREG_SAR0_WRK1
#define ADC_SAR_1_IRQ__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define ADC_SAR_1_IRQ__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define ADC_SAR_1_IRQ__INTC_MASK 0x01u
#define ADC_SAR_1_IRQ__INTC_NUMBER 0u
#define ADC_SAR_1_IRQ__INTC_PRIOR_NUM 7u
#define ADC_SAR_1_IRQ__INTC_PRIOR_REG CYREG_NVIC_PRI_0
#define ADC_SAR_1_IRQ__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define ADC_SAR_1_IRQ__INTC_SET_PD_REG CYREG_NVIC_SETPEND0
#define ADC_SAR_1_theACLK__CFG0 CYREG_CLKDIST_ACFG0_CFG0
#define ADC_SAR_1_theACLK__CFG1 CYREG_CLKDIST_ACFG0_CFG1
#define ADC_SAR_1_theACLK__CFG2 CYREG_CLKDIST_ACFG0_CFG2
#define ADC_SAR_1_theACLK__CFG2_SRC_SEL_MASK 0x07u
#define ADC_SAR_1_theACLK__CFG3 CYREG_CLKDIST_ACFG0_CFG3
#define ADC_SAR_1_theACLK__CFG3_PHASE_DLY_MASK 0x0Fu
#define ADC_SAR_1_theACLK__INDEX 0x00u
#define ADC_SAR_1_theACLK__PM_ACT_CFG CYREG_PM_ACT_CFG1
#define ADC_SAR_1_theACLK__PM_ACT_MSK 0x01u
#define ADC_SAR_1_theACLK__PM_STBY_CFG CYREG_PM_STBY_CFG1
#define ADC_SAR_1_theACLK__PM_STBY_MSK 0x01u

/* timer_clock */
#define timer_clock__CFG0 CYREG_CLKDIST_DCFG0_CFG0
#define timer_clock__CFG1 CYREG_CLKDIST_DCFG0_CFG1
#define timer_clock__CFG2 CYREG_CLKDIST_DCFG0_CFG2
#define timer_clock__CFG2_SRC_SEL_MASK 0x07u
#define timer_clock__INDEX 0x00u
#define timer_clock__PM_ACT_CFG CYREG_PM_ACT_CFG2
#define timer_clock__PM_ACT_MSK 0x01u
#define timer_clock__PM_STBY_CFG CYREG_PM_STBY_CFG2
#define timer_clock__PM_STBY_MSK 0x01u

/* Miscellaneous */
#define BCLK__BUS_CLK__HZ 48000000U
#define BCLK__BUS_CLK__KHZ 48000U
#define BCLK__BUS_CLK__MHZ 48U
#define CY_PROJECT_NAME "hardwareTask1"
#define CY_VERSION "PSoC Creator  4.2"
#define CYDEV_CHIP_DIE_LEOPARD 1u
#define CYDEV_CHIP_DIE_PSOC4A 18u
#define CYDEV_CHIP_DIE_PSOC5LP 2u
#define CYDEV_CHIP_DIE_PSOC5TM 3u
#define CYDEV_CHIP_DIE_TMA4 4u
#define CYDEV_CHIP_DIE_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_FM0P 5u
#define CYDEV_CHIP_FAMILY_FM3 6u
#define CYDEV_CHIP_FAMILY_FM4 7u
#define CYDEV_CHIP_FAMILY_PSOC3 1u
#define CYDEV_CHIP_FAMILY_PSOC4 2u
#define CYDEV_CHIP_FAMILY_PSOC5 3u
#define CYDEV_CHIP_FAMILY_PSOC6 4u
#define CYDEV_CHIP_FAMILY_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_USED CYDEV_CHIP_FAMILY_PSOC5
#define CYDEV_CHIP_JTAG_ID 0x2E161069u
#define CYDEV_CHIP_MEMBER_3A 1u
#define CYDEV_CHIP_MEMBER_4A 18u
#define CYDEV_CHIP_MEMBER_4D 13u
#define CYDEV_CHIP_MEMBER_4E 6u
#define CYDEV_CHIP_MEMBER_4F 19u
#define CYDEV_CHIP_MEMBER_4G 4u
#define CYDEV_CHIP_MEMBER_4H 17u
#define CYDEV_CHIP_MEMBER_4I 23u
#define CYDEV_CHIP_MEMBER_4J 14u
#define CYDEV_CHIP_MEMBER_4K 15u
#define CYDEV_CHIP_MEMBER_4L 22u
#define CYDEV_CHIP_MEMBER_4M 21u
#define CYDEV_CHIP_MEMBER_4N 10u
#define CYDEV_CHIP_MEMBER_4O 7u
#define CYDEV_CHIP_MEMBER_4P 20u
#define CYDEV_CHIP_MEMBER_4Q 12u
#define CYDEV_CHIP_MEMBER_4R 8u
#define CYDEV_CHIP_MEMBER_4S 11u
#define CYDEV_CHIP_MEMBER_4T 9u
#define CYDEV_CHIP_MEMBER_4U 5u
#define CYDEV_CHIP_MEMBER_4V 16u
#define CYDEV_CHIP_MEMBER_5A 3u
#define CYDEV_CHIP_MEMBER_5B 2u
#define CYDEV_CHIP_MEMBER_6A 24u
#define CYDEV_CHIP_MEMBER_FM3 28u
#define CYDEV_CHIP_MEMBER_FM4 29u
#define CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE1 25u
#define CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE2 26u
#define CYDEV_CHIP_MEMBER_PDL_FM0P_TYPE3 27u
#define CYDEV_CHIP_MEMBER_UNKNOWN 0u
#define CYDEV_CHIP_MEMBER_USED CYDEV_CHIP_MEMBER_5B
#define CYDEV_CHIP_DIE_EXPECT CYDEV_CHIP_MEMBER_USED
#define CYDEV_CHIP_DIE_ACTUAL CYDEV_CHIP_DIE_EXPECT
#define CYDEV_CHIP_REV_LEOPARD_ES1 0u
#define CYDEV_CHIP_REV_LEOPARD_ES2 1u
#define CYDEV_CHIP_REV_LEOPARD_ES3 3u
#define CYDEV_CHIP_REV_LEOPARD_PRODUCTION 3u
#define CYDEV_CHIP_REV_PSOC4A_ES0 17u
#define CYDEV_CHIP_REV_PSOC4A_PRODUCTION 17u
#define CYDEV_CHIP_REV_PSOC5LP_ES0 0u
#define CYDEV_CHIP_REV_PSOC5LP_PRODUCTION 0u
#define CYDEV_CHIP_REV_PSOC5TM_ES0 0u
#define CYDEV_CHIP_REV_PSOC5TM_ES1 1u
#define CYDEV_CHIP_REV_PSOC5TM_PRODUCTION 1u
#define CYDEV_CHIP_REV_TMA4_ES 17u
#define CYDEV_CHIP_REV_TMA4_ES2 33u
#define CYDEV_CHIP_REV_TMA4_PRODUCTION 17u
#define CYDEV_CHIP_REVISION_3A_ES1 0u
#define CYDEV_CHIP_REVISION_3A_ES2 1u
#define CYDEV_CHIP_REVISION_3A_ES3 3u
#define CYDEV_CHIP_REVISION_3A_PRODUCTION 3u
#define CYDEV_CHIP_REVISION_4A_ES0 17u
#define CYDEV_CHIP_REVISION_4A_PRODUCTION 17u
#define CYDEV_CHIP_REVISION_4D_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4E_CCG2_NO_USBPD 0u
#define CYDEV_CHIP_REVISION_4E_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4F_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4F_PRODUCTION_256DMA 0u
#define CYDEV_CHIP_REVISION_4F_PRODUCTION_256K 0u
#define CYDEV_CHIP_REVISION_4G_ES 17u
#define CYDEV_CHIP_REVISION_4G_ES2 33u
#define CYDEV_CHIP_REVISION_4G_PRODUCTION 17u
#define CYDEV_CHIP_REVISION_4H_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4I_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4J_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4K_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4L_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4M_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4N_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4O_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4P_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4Q_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4R_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4S_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4T_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4U_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4V_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_5A_ES0 0u
#define CYDEV_CHIP_REVISION_5A_ES1 1u
#define CYDEV_CHIP_REVISION_5A_PRODUCTION 1u
#define CYDEV_CHIP_REVISION_5B_ES0 0u
#define CYDEV_CHIP_REVISION_5B_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_6A_ES 17u
#define CYDEV_CHIP_REVISION_6A_NO_UDB 33u
#define CYDEV_CHIP_REVISION_6A_PRODUCTION 33u
#define CYDEV_CHIP_REVISION_FM3_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_FM4_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_PDL_FM0P_TYPE1_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_PDL_FM0P_TYPE2_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_PDL_FM0P_TYPE3_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_USED CYDEV_CHIP_REVISION_5B_PRODUCTION
#define CYDEV_CHIP_REV_EXPECT CYDEV_CHIP_REVISION_USED
#define CYDEV_CONFIG_FASTBOOT_ENABLED 1
#define CYDEV_CONFIG_UNUSED_IO_AllowButWarn 0
#define CYDEV_CONFIG_UNUSED_IO CYDEV_CONFIG_UNUSED_IO_AllowButWarn
#define CYDEV_CONFIG_UNUSED_IO_AllowWithInfo 1
#define CYDEV_CONFIG_UNUSED_IO_Disallowed 2
#define CYDEV_CONFIGURATION_COMPRESSED 1
#define CYDEV_CONFIGURATION_DMA 0
#define CYDEV_CONFIGURATION_ECC 1
#define CYDEV_CONFIGURATION_IMOENABLED CYDEV_CONFIG_FASTBOOT_ENABLED
#define CYDEV_CONFIGURATION_MODE_COMPRESSED 0
#define CYDEV_CONFIGURATION_MODE CYDEV_CONFIGURATION_MODE_COMPRESSED
#define CYDEV_CONFIGURATION_MODE_DMA 2
#define CYDEV_CONFIGURATION_MODE_UNCOMPRESSED 1
#define CYDEV_DEBUG_ENABLE_MASK 0x20u
#define CYDEV_DEBUG_ENABLE_REGISTER CYREG_MLOGIC_DEBUG
#define CYDEV_DEBUGGING_DPS_Disable 3
#define CYDEV_DEBUGGING_DPS_JTAG_4 1
#define CYDEV_DEBUGGING_DPS_JTAG_5 0
#define CYDEV_DEBUGGING_DPS_SWD 2
#define CYDEV_DEBUGGING_DPS_SWD_SWV 6
#define CYDEV_DEBUGGING_DPS CYDEV_DEBUGGING_DPS_SWD_SWV
#define CYDEV_DEBUGGING_ENABLE 1
#define CYDEV_DEBUGGING_XRES 0
#define CYDEV_DMA_CHANNELS_AVAILABLE 24u
#define CYDEV_ECC_ENABLE 0
#define CYDEV_HEAP_SIZE 0x80
#define CYDEV_INSTRUCT_CACHE_ENABLED 1
#define CYDEV_INTR_RISING 0x00000011u
#define CYDEV_IS_EXPORTING_CODE 0
#define CYDEV_IS_IMPORTING_CODE 0
#define CYDEV_PROJ_TYPE 0
#define CYDEV_PROJ_TYPE_BOOTLOADER 1
#define CYDEV_PROJ_TYPE_LAUNCHER 5
#define CYDEV_PROJ_TYPE_LOADABLE 2
#define CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER 4
#define CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER 3
#define CYDEV_PROJ_TYPE_STANDARD 0
#define CYDEV_PROTECTION_ENABLE 0
#define CYDEV_STACK_SIZE 0x0800
#define CYDEV_USB_CLK_OSC_LOCKING_ENABLED_AT_PWR_UP 
#define CYDEV_USE_BUNDLED_CMSIS 1
#define CYDEV_VARIABLE_VDDA 0
#define CYDEV_VDDA 5.0
#define CYDEV_VDDA_MV 5000
#define CYDEV_VDDD 5.0
#define CYDEV_VDDD_MV 5000
#define CYDEV_VDDIO0 5.0
#define CYDEV_VDDIO0_MV 5000
#define CYDEV_VDDIO1 5.0
#define CYDEV_VDDIO1_MV 5000
#define CYDEV_VDDIO2 5.0
#define CYDEV_VDDIO2_MV 5000
#define CYDEV_VDDIO3 5.0
#define CYDEV_VDDIO3_MV 5000
#define CYDEV_VIO0 5.0
#define CYDEV_VIO0_MV 5000
#define CYDEV_VIO1 5.0
#define CYDEV_VIO1_MV 5000
#define CYDEV_VIO2 5.0
#define CYDEV_VIO2_MV 5000
#define CYDEV_VIO3 5.0
#define CYDEV_VIO3_MV 5000
#define CYIPBLOCK_ARM_CM3_VERSION 0
#define CYIPBLOCK_P3_ANAIF_VERSION 0
#define CYIPBLOCK_P3_CAN_VERSION 0
#define CYIPBLOCK_P3_CAPSENSE_VERSION 0
#define CYIPBLOCK_P3_COMP_VERSION 0
#define CYIPBLOCK_P3_DECIMATOR_VERSION 0
#define CYIPBLOCK_P3_DFB_VERSION 0
#define CYIPBLOCK_P3_DMA_VERSION 0
#define CYIPBLOCK_P3_DRQ_VERSION 0
#define CYIPBLOCK_P3_DSM_VERSION 0
#define CYIPBLOCK_P3_EMIF_VERSION 0
#define CYIPBLOCK_P3_I2C_VERSION 0
#define CYIPBLOCK_P3_LCD_VERSION 0
#define CYIPBLOCK_P3_LPF_VERSION 0
#define CYIPBLOCK_P3_OPAMP_VERSION 0
#define CYIPBLOCK_P3_PM_VERSION 0
#define CYIPBLOCK_P3_SCCT_VERSION 0
#define CYIPBLOCK_P3_TIMER_VERSION 0
#define CYIPBLOCK_P3_USB_VERSION 0
#define CYIPBLOCK_P3_VIDAC_VERSION 0
#define CYIPBLOCK_P3_VREF_VERSION 0
#define CYIPBLOCK_S8_GPIO_VERSION 0
#define CYIPBLOCK_S8_IRQ_VERSION 0
#define CYIPBLOCK_S8_SAR_VERSION 0
#define CYIPBLOCK_S8_SIO_VERSION 0
#define CYIPBLOCK_S8_UDB_VERSION 0
#define DMA_CHANNELS_USED__MASK0 0x00000000u
#define CYDEV_BOOTLOADER_ENABLE 0

#endif /* INCLUDED_CYFITTER_H */
