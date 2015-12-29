/**************************************************************************//**
 * @file
 * @brief Empty Project
 * @author Energy Micro AS
 * @version 3.20.2
 ******************************************************************************
 * @section License
 * <b>(C) Copyright 2014 Silicon Labs, http://www.silabs.com</b>
 *******************************************************************************
 *
 * This file is licensed under the Silicon Labs Software License Agreement. See 
 * "http://developer.silabs.com/legal/version/v11/Silicon_Labs_Software_License_Agreement.txt"  
 * for details. Before using this software for any purpose, you must agree to the 
 * terms of that agreement.
 *
 ******************************************************************************/
#include "em_device.h"
#include "em_chip.h"
#include "em_emu.h"

#define LED_PORT E
#define BUTTON_PORT B
#define LED0 2
#define LED1 3
#define PB0 9
#define PB1 10

enum {
  A,
  B,
  C,
  D,
  E
};

void handleGPIO(void);

void GPIO_EVEN_IRQHandler(void) {
	handleGPIO();
}

void GPIO_ODD_IRQHandler(void) {
	handleGPIO();
}

int main(void){
	/* Chip errata */
	CHIP_Init();

	CMU->HFPERCLKEN0 = (1 << 13); // Enable GPIO clock
	// LED setup
	GPIO->P[LED_PORT].MODEL |= (5 << 8); // PE2 push-pull with drive-strength set by DRIVEMODE
	GPIO->P[LED_PORT].MODEL |= (5 << 12); // PE3 push-pull with drive-strength set by DRIVEMODE
	GPIO->P[LED_PORT].CTRL = 1; // Set DRIVEMODE to lowest setting (0.5 mA) for all LEDs configured with alternate drive strength
	// Button Setup
	GPIO->P[BUTTON_PORT].MODEH |= (2 << 4); // PB9 Input enabled. DOUT determines pull direction
	GPIO->P[BUTTON_PORT].MODEH |= (2 << 8); // PB10 Input enabled. DOUT determines pull direction
	GPIO->P[BUTTON_PORT].DOUT = (1 << PB1) | (1 << PB0); // Enable Pull-ups on PB0 and PB1
	// Interrupt Setup
	GPIO->EXTIPSELH = (1 << 4) | (1 << 8); // Set port B pin 9 and 10 as interrupt source
	GPIO->EXTIFALL = (1 << PB0) | (1 << PB1); // Trigger interrupt on falling edges
	//GPIO->EXTIRISE = (1 << PB0) | (1 << PB1); // Trigger interrupt on rising edges
	GPIO->IEN = (1 << PB0) | (1 << PB1); // Enable interrupt generation
	NVIC->ISER[0] = (1 << 1) | (1 << 11); // Enable interrupt on even and odd pins

	while(1){
		EMU_EnterEM3(false);
		__asm__("wfi");
	}
}

void handleGPIO(void) {
	GPIO->IFC = GPIO->IF; // Clear interrupt flag (IFC set to 1 clears, IF is set to 1 on interrupt)
	// Doesnt handle if both buttons are pressed at once
	if(GPIO->P[BUTTON_PORT].DIN & (1 << PB1)){
		GPIO->P[LED_PORT].DOUTTGL = 1 << LED1;
	}
	if(GPIO->P[BUTTON_PORT].DIN & (1 << PB0)){
		GPIO->P[LED_PORT].DOUTTGL = 1 << LED0;
	}
}
