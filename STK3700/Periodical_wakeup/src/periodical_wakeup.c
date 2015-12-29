#include <stdio.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_rmu.h"
#include "em_burtc.h"
#include "segmentlcd.h"


#define LED_PORT E
#define BUTTON_PORT B
#define LED0 2
#define LED1 3
#define PB0 9
#define PB1 10

#define LFRCO_FREQUENCY 32768
#define WAKEUP_INTERVAL_MS 1000
#define BURTC_COUNT_BETWEEN_WAKEUP (((LFRCO_FREQUENCY * WAKEUP_INTERVAL_MS) / 1000)-1)

enum {
  A,
  B,
  C,
  D,
  E
};

static volatile int counter;
static volatile int countDown;
static volatile int screenOn;

void handleGPIO(void);

void GPIO_EVEN_IRQHandler(void){
	handleGPIO();
}

void GPIO_ODD_IRQHandler(void){
	handleGPIO();
}

void BURTC_IRQHandler(void){
	BURTC_IntClear(BURTC_IFC_COMP0); // Clear flag
	counter++;
	if(screenOn){
		SegmentLCD_Number(counter);
	}
}

void LETIMER0_IRQHandler(void){
	LETIMER0->IFC = LETIMER0->IF; // Clear flag
	char str[4];
	sprintf(str, "%d", countDown);
	SegmentLCD_Write(str);
	if(countDown <= 0){
		SegmentLCD_AllOff();
		screenOn = 0;
		LETIMER0->CMD = 0b10; //Stop LETIMER0
	}
	countDown--;
}

int main(void){
	/* Chip errata */
	CHIP_Init();

	/* Enable Low energy clocking module clock. */
	CMU_ClockEnable(cmuClock_CORELE, true);

	/* Starting LFRCO and waiting until it is stable */
	CMU_OscillatorEnable(cmuOsc_LFRCO, true, true);

	/* Enable access to BURTC registers */
	RMU_ResetControl(rmuResetBU, false);

	CMU->HFPERCLKEN0 |= (1 << 13); // Enable GPIO clock
	// Button Setup
	GPIO->P[BUTTON_PORT].MODEH |= (2 << 4); // PB9 Input enabled. DOUT determines pull direction
	GPIO->P[BUTTON_PORT].MODEH |= (2 << 8); // PB10 Input enabled. DOUT determines pull direction
	GPIO->P[BUTTON_PORT].DOUT = (1 << PB1) | (1 << PB0); // Enable Pull-ups on PB0 and PB1
	GPIO->EXTIPSELH = (1 << 4) | (1 << 8); // Set port B pin 9 and 10 as interrupt source
	GPIO->EXTIFALL = (1 << PB0) | (1 << PB1); // Trigger interrupt on falling edges
	//GPIO->EXTIRISE = (1 << PB0) | (1 << PB1); // Trigger interrupt on rising edges
	GPIO->IEN = (1 << PB0) | (1 << PB1); // Enable interrupt generation
	// LED setup
	GPIO->P[LED_PORT].MODEL |= (5 << 8); // PE2 push-pull with drive-strength set by DRIVEMODE
 	GPIO->P[LED_PORT].MODEL |= (5 << 12); // PE3 push-pull with drive-strength set by DRIVEMODE
 	GPIO->P[LED_PORT].CTRL = 1; // Set DRIVEMODE to lowest setting (0.5 mA) for all LEDs configured with alternate drive strength

 	/**************************************************************************//**
 	 * @brief  Setup BURTC
 	 * Using LFRCO clock source and enabling interrupt on COMP0 match
 	 *****************************************************************************/
 	BURTC_Init_TypeDef burtcInit = BURTC_INIT_DEFAULT;

 	burtcInit.enable       = true;                /* Enable BURTC after initialization  */
 	burtcInit.mode         = burtcModeEM3;        /* BURTC is enabled in EM0-EM3 */
 	burtcInit.debugRun     = false;               /* Counter shall keep running during debug halt. */
 	burtcInit.clkSel       = burtcClkSelLFRCO;    /* Select LFRCO as clock source */
 	burtcInit.clkDiv       = burtcClkDiv_1;       /* Clock prescaler             */
 	burtcInit.lowPowerComp = 0;                   /* Number of least significantt clock bits to ignore in low power mode */
 	burtcInit.timeStamp    = true;                /* Enable time stamp on entering backup power domain */
 	burtcInit.compare0Top  = true;                /* Clear counter on compare match */
 	burtcInit.lowPowerMode = burtcLPDisable;      /* Low power operation mode, requires LFXO or LFRCO */

 	BURTC_CompareSet(0, BURTC_COUNT_BETWEEN_WAKEUP);  /* Set top value for comparator */

 	/* Enabling Interrupt from BURTC */
 	NVIC_EnableIRQ(BURTC_IRQn);
 	BURTC_IntEnable(BURTC_IF_COMP0);    /* Enable compare interrupt flag */

 	/* Initialize BURTC */
 	BURTC_Init(&burtcInit);

 	// LETIMER0
 	CMU->LFCLKSEL = 1; // LFRCO selected as LFACLK
 	CMU->HFCORECLKEN0 = 1 << 4; //Enable LE timer
 	CMU->LFACLKEN0 = 1 << 2; // Enable the clock for LETIMER0
 	LETIMER0->CTRL = (1 << 9);  // Reset on COMP0
 	LETIMER0->COMP0 = 32768;
 	LETIMER0->IEN = 1;  // Trigger interrupt on COMP0TOP

 	NVIC->ISER[0] |= (1 << 1) | (1 << 11) | (1 << 26); // Enable interrupt on even and odd pins, and LETIMER

 	SegmentLCD_Init(false);

 	counter = 0;
 	countDown = 0;
 	screenOn = 0;

  	while (1){
  		EMU_EnterEM2(false);
  	}
}

void handleGPIO(void) {
	GPIO->IFC = GPIO->IF; // Clear interrupt flag (IFC set to 1 clears, IF is set to 1 on interrupt)
	screenOn = 1;
	SegmentLCD_Number(counter);
	SegmentLCD_Write("3");
	countDown = 2;
	LETIMER0->CMD = 0b01; //Start LETIMER0
}
