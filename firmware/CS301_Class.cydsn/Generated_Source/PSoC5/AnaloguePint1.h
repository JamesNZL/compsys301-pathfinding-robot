/*******************************************************************************
* File Name: AnaloguePint1.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_AnaloguePint1_H) /* Pins AnaloguePint1_H */
#define CY_PINS_AnaloguePint1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "AnaloguePint1_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 AnaloguePint1__PORT == 15 && ((AnaloguePint1__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    AnaloguePint1_Write(uint8 value);
void    AnaloguePint1_SetDriveMode(uint8 mode);
uint8   AnaloguePint1_ReadDataReg(void);
uint8   AnaloguePint1_Read(void);
void    AnaloguePint1_SetInterruptMode(uint16 position, uint16 mode);
uint8   AnaloguePint1_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the AnaloguePint1_SetDriveMode() function.
     *  @{
     */
        #define AnaloguePint1_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define AnaloguePint1_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define AnaloguePint1_DM_RES_UP          PIN_DM_RES_UP
        #define AnaloguePint1_DM_RES_DWN         PIN_DM_RES_DWN
        #define AnaloguePint1_DM_OD_LO           PIN_DM_OD_LO
        #define AnaloguePint1_DM_OD_HI           PIN_DM_OD_HI
        #define AnaloguePint1_DM_STRONG          PIN_DM_STRONG
        #define AnaloguePint1_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define AnaloguePint1_MASK               AnaloguePint1__MASK
#define AnaloguePint1_SHIFT              AnaloguePint1__SHIFT
#define AnaloguePint1_WIDTH              1u

/* Interrupt constants */
#if defined(AnaloguePint1__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in AnaloguePint1_SetInterruptMode() function.
     *  @{
     */
        #define AnaloguePint1_INTR_NONE      (uint16)(0x0000u)
        #define AnaloguePint1_INTR_RISING    (uint16)(0x0001u)
        #define AnaloguePint1_INTR_FALLING   (uint16)(0x0002u)
        #define AnaloguePint1_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define AnaloguePint1_INTR_MASK      (0x01u) 
#endif /* (AnaloguePint1__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define AnaloguePint1_PS                     (* (reg8 *) AnaloguePint1__PS)
/* Data Register */
#define AnaloguePint1_DR                     (* (reg8 *) AnaloguePint1__DR)
/* Port Number */
#define AnaloguePint1_PRT_NUM                (* (reg8 *) AnaloguePint1__PRT) 
/* Connect to Analog Globals */                                                  
#define AnaloguePint1_AG                     (* (reg8 *) AnaloguePint1__AG)                       
/* Analog MUX bux enable */
#define AnaloguePint1_AMUX                   (* (reg8 *) AnaloguePint1__AMUX) 
/* Bidirectional Enable */                                                        
#define AnaloguePint1_BIE                    (* (reg8 *) AnaloguePint1__BIE)
/* Bit-mask for Aliased Register Access */
#define AnaloguePint1_BIT_MASK               (* (reg8 *) AnaloguePint1__BIT_MASK)
/* Bypass Enable */
#define AnaloguePint1_BYP                    (* (reg8 *) AnaloguePint1__BYP)
/* Port wide control signals */                                                   
#define AnaloguePint1_CTL                    (* (reg8 *) AnaloguePint1__CTL)
/* Drive Modes */
#define AnaloguePint1_DM0                    (* (reg8 *) AnaloguePint1__DM0) 
#define AnaloguePint1_DM1                    (* (reg8 *) AnaloguePint1__DM1)
#define AnaloguePint1_DM2                    (* (reg8 *) AnaloguePint1__DM2) 
/* Input Buffer Disable Override */
#define AnaloguePint1_INP_DIS                (* (reg8 *) AnaloguePint1__INP_DIS)
/* LCD Common or Segment Drive */
#define AnaloguePint1_LCD_COM_SEG            (* (reg8 *) AnaloguePint1__LCD_COM_SEG)
/* Enable Segment LCD */
#define AnaloguePint1_LCD_EN                 (* (reg8 *) AnaloguePint1__LCD_EN)
/* Slew Rate Control */
#define AnaloguePint1_SLW                    (* (reg8 *) AnaloguePint1__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define AnaloguePint1_PRTDSI__CAPS_SEL       (* (reg8 *) AnaloguePint1__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define AnaloguePint1_PRTDSI__DBL_SYNC_IN    (* (reg8 *) AnaloguePint1__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define AnaloguePint1_PRTDSI__OE_SEL0        (* (reg8 *) AnaloguePint1__PRTDSI__OE_SEL0) 
#define AnaloguePint1_PRTDSI__OE_SEL1        (* (reg8 *) AnaloguePint1__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define AnaloguePint1_PRTDSI__OUT_SEL0       (* (reg8 *) AnaloguePint1__PRTDSI__OUT_SEL0) 
#define AnaloguePint1_PRTDSI__OUT_SEL1       (* (reg8 *) AnaloguePint1__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define AnaloguePint1_PRTDSI__SYNC_OUT       (* (reg8 *) AnaloguePint1__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(AnaloguePint1__SIO_CFG)
    #define AnaloguePint1_SIO_HYST_EN        (* (reg8 *) AnaloguePint1__SIO_HYST_EN)
    #define AnaloguePint1_SIO_REG_HIFREQ     (* (reg8 *) AnaloguePint1__SIO_REG_HIFREQ)
    #define AnaloguePint1_SIO_CFG            (* (reg8 *) AnaloguePint1__SIO_CFG)
    #define AnaloguePint1_SIO_DIFF           (* (reg8 *) AnaloguePint1__SIO_DIFF)
#endif /* (AnaloguePint1__SIO_CFG) */

/* Interrupt Registers */
#if defined(AnaloguePint1__INTSTAT)
    #define AnaloguePint1_INTSTAT            (* (reg8 *) AnaloguePint1__INTSTAT)
    #define AnaloguePint1_SNAP               (* (reg8 *) AnaloguePint1__SNAP)
    
	#define AnaloguePint1_0_INTTYPE_REG 		(* (reg8 *) AnaloguePint1__0__INTTYPE)
#endif /* (AnaloguePint1__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_AnaloguePint1_H */


/* [] END OF FILE */
