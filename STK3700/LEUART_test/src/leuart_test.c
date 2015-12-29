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
#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "em_leuart.h"
#include "segmentlcd.h"

volatile uint32_t msTicks; /* counts 1ms timeTicks */

void Delay(uint32_t dlyTicks);

void SysTick_Handler(void)
{
  msTicks++;
}

void Delay(uint32_t dlyTicks)
{
  uint32_t curTicks;

  curTicks = msTicks;
  while ((msTicks - curTicks) < dlyTicks) ;
}

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

char text[] = "test1";
char text2[] = "test2";

int main(void)
{
  /* Chip errata */
  CHIP_Init();

  CMU_ClockSelectSet(cmuClock_LFB, cmuSelect_LFXO); // LFXO for LEUART

  CMU_ClockEnable(cmuClock_CORELE, true); // Enable CORELE clock
  CMU_ClockEnable(cmuClock_GPIO, true); // Enable GPIO clock
  CMU_ClockEnable(cmuClock_LEUART0, true); // Enable LEUART1 clock

  if (SysTick_Config(CMU_ClockFreqGet(cmuClock_CORE) / 1000)) while (1) ;

  LEUART_Reset(LEUART0);
  LEUART_Init(LEUART0, &leuart0Init);
  LEUART0->ROUTE = LEUART_ROUTE_TXPEN | LEUART_ROUTE_LOCATION_LOC0;
  GPIO_PinModeSet(gpioPortD, 4, gpioModePushPull, 1);

  SegmentLCD_Init(false);

  LEUART_Tx(LEUART0, 254);
  LEUART_Tx(LEUART0, 128);
  for(int i = 0; i < 2*16; i++){
	  LEUART_Tx(LEUART0, ' ');
  }

  while (1) {
	  LEUART_Tx(LEUART0, 254);
	  LEUART_Tx(LEUART0, 128);
	  SegmentLCD_Write(text);
	  for(int i = 0; i < 5; i++){
		  LEUART_Tx(LEUART0, text[i]);
	  }
	  Delay(1000);
	  LEUART_Tx(LEUART0, 254);
	  LEUART_Tx(LEUART0, 128);
	  SegmentLCD_Write(text2);
	  for(int i = 0; i < 5; i++){
		  LEUART_Tx(LEUART0, text2[i]);
	  }
	  Delay(1000);

  }
}
