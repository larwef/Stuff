#include <stdio.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "em_leuart.h"

#define BUTTON_PORT B
#define PB0 9
#define PB1 10

enum {
  A,
  B,
  C,
  D,
  E
};

/* Defining the LEUART1 initialization data */
LEUART_Init_TypeDef leuart0Init =
{
    .enable   = leuartEnableTx, /* Activate data reception on   LEUn_TX pin. */
    .refFreq  = 0, /* Inherit the clock frequency from the LEUART clock source */
    .baudrate = 9600, /* Baudrate = 9600 bps */
    .databits = leuartDatabits8, /* Each LEUART frame contains 8 databits */
    .parity   = leuartNoParity, /* No parity bits in use */
    .stopbits = leuartStopbits1, /* Setting the number of stop bits in a frame to 1 bitperiods */
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

	CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_LFXO); // LFXO for LEUART

	CMU_ClockEnable(cmuClock_CORELE, true); // Enable CORELE clock
	CMU_ClockEnable(cmuClock_GPIO, true); // Enable GPIO clock
	CMU_ClockEnable(cmuClock_LEUART0, true); // Enable LEUART1 clock

	LEUART_Reset(LEUART0);
	LEUART_Init(LEUART0, &leuart0Init);
	LEUART0->ROUTE = LEUART_ROUTE_TXPEN | LEUART_ROUTE_LOCATION_LOC0;
	GPIO_PinModeSet(gpioPortD, 4, gpioModePushPull, 1);

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

	//Clear screen
	LEUART_Tx(LEUART0, 254);
	LEUART_Tx(LEUART0, 128);
	for(int i = 0; i < 2*16; i++){
		LEUART_Tx(LEUART0, ' ');
	}
	LEUART_Tx(LEUART0, '0');
	while (1){
		EMU_EnterEM2(false);
	}
}

void handleGPIO(void) {
	static int8_t counter = 0;
	GPIO->IFC = GPIO->IF; // Clear interrupt flag (IFC set to 1 clears, IF is set to 1 on interrupt)
	if(GPIO->P[BUTTON_PORT].DIN & (1 << PB1)){
		counter--;
	}
	if(GPIO->P[BUTTON_PORT].DIN & (1 << PB0)){
		counter++;
	}
	char str[4];
	sprintf(str, "%d", counter);
	LEUART_Tx(LEUART0, 254);
	LEUART_Tx(LEUART0, 128);
	for(int i = 0; i < 4; i++){
		LEUART_Tx(LEUART0, ' ');
	}
	LEUART_Tx(LEUART0, 254);
	LEUART_Tx(LEUART0, 128);
	for(int i = 0; i < 4; i++){
		if(str[i] == '\0') {
			break;
		}
		else{
			LEUART_Tx(LEUART0, str[i]);
		}
	}
}

