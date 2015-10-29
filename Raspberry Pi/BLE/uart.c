/**
 * uart_win.c
 *
 * Copyright © 2013 Bluegiga Technologies Inc. <support@bluegiga.com>
 * This source code is licensed under Bluegiga Source Code License.
 */

#include <stdint.h>
#include <stdio.h>
#include <wiringPi.h>
#include <wiringSerial.h>
#include "uart.h"

int uart_conn;

int uart_open(void)
{
    if ((uart_conn = serialOpen ("/dev/ttyAMA0", 115200)) < 0){
        printf("Error opening serial device\n");
        return 1 ;
    }
    else {
        return 0;
    }
}

void uart_close(void)
{
    serialClose(uart_conn);
}

int uart_rx(uint16_t data_length, uint8_t* data)
{
    for(int i = 0; i < data_length; i++){
        *data = serialGetchar(uart_conn);
        data++;
    }

    return data_length;
}

int uart_tx(uint16_t data_length, uint8_t* data)
{
    for(int i = 0; i < data_length; i++){
        serialPutchar(uart_conn,*data);
        data++;
    }
    
    return data_length;
}

int uart_peek(void)
{
    return serialDataAvail(uart_conn); 
}
