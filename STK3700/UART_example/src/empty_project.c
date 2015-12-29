#include "em_device.h"
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_usart.h"
#include "em_system.h"
#include "em_chip.h"    // required for CHIP_Init() function
#include <string.h>     // required for strlen() function

#define COM_PORT gpioPortD // USART location #1: PD0 and PD1
#define UART_TX_pin 0      // PD0
#define UART_RX_pin 1      // PD1

int main() {
  CHIP_Init(); // This function addresses some chip errata and should be called at the start of every EFM32 application (need em_system.c)

  uint8_t i;
  char test_string[] = "\n\rHello World!\n\r";     // Test string
  char rx_char = 0;                                // Temp variable for storing received characters

  CMU_ClockDivSet(cmuClock_HF, cmuClkDiv_2);       // Set HF clock divider to /2 to keep core frequency < 32MHz
  CMU_OscillatorEnable(cmuOsc_HFXO, true, true);   // Enable XTAL Osc and wait to stabilize
  CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFXO); // Select HF XTAL osc as system clock source. 48MHz XTAL, but we divided the system clock by 2, therefore our HF clock will be 24MHz

  CMU_ClockEnable(cmuClock_GPIO, true);            // Enable GPIO peripheral clock
  CMU_ClockEnable(cmuClock_USART1, true);          // Enable USART1 peripheral clock

  GPIO_PinModeSet(COM_PORT, UART_TX_pin, gpioModePushPull, 1); // Configure UART TX pin as digital output, initialize high since UART TX idles high (otherwise glitches can occur)
  GPIO_PinModeSet(COM_PORT, UART_RX_pin, gpioModeInput, 0);    // Configure UART RX pin as input (no filter)

  USART_InitAsync_TypeDef uartInit =
  {
    .enable       = usartDisable,   // Wait to enable the transmitter and receiver
    .refFreq      = 0,              // Setting refFreq to 0 will invoke the CMU_ClockFreqGet() function and measure the HFPER clock
    .baudrate     = 115200,          // Desired baud rate
    .oversampling = usartOVS16,     // Set oversampling value to x16
    .databits     = usartDatabits8, // 8 data bits
    .parity       = usartNoParity,  // No parity bits
    .stopbits     = usartStopbits1, // 1 stop bit
    .mvdis        = false,          // Use majority voting
    .prsRxEnable  = false,          // Not using PRS input
    .prsRxCh      = usartPrsRxCh0,  // Doesn't matter which channel we select
  };
  USART_Reset(USART1);
  USART_InitAsync(USART1, &uartInit);                                              // Apply configuration struct to USART1
  USART1->ROUTE = UART_ROUTE_RXPEN | UART_ROUTE_TXPEN | USART_ROUTE_LOCATION_LOC1; // Clear RX/TX buffers and shift regs, enable transmitter and receiver pins

  USART_IntClear(USART1, _UART_IF_MASK); // Clear any USART interrupt flags
  NVIC_ClearPendingIRQ(UART1_RX_IRQn);   // Clear pending RX interrupt flag in NVIC
  NVIC_ClearPendingIRQ(UART1_TX_IRQn);   // Clear pending TX interrupt flag in NVIC

  USART_Enable(USART1, usartEnable);     // Enable transmitter and receiver

  SegmentLCD_Init(false);

  uint8_t rx;
  uint8_t tx = 0x04;

  while(1) {
	  rx = USART_Rx(USART1);
	  SegmentLCD_Number(rx);
	  USART_Tx(USART1, tx);
  }
}
