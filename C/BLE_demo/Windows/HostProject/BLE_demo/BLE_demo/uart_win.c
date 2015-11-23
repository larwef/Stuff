/**
 * uart_win.c
 *
 * Copyright © 2013 Bluegiga Technologies Inc. <support@bluegiga.com>
 * This source code is licensed under Bluegiga Source Code License.
 */

#include <windows.h>
#include <stdint.h>
#include <stdio.h>
#include "uart.h"

#ifdef _MSC_VER
#define snprintf _snprintf
#endif /* _MSC_VER */

/** Handle of the serial port. INVALID_HANDLE_VALUE if none. */
static HANDLE uart_handle = INVALID_HANDLE_VALUE;

int uart_open(unsigned char* port, uint32_t baudrate)
{
    char str[60];
    DCB settings;

    int n=_snprintf_s(str, sizeof(str) - 1,sizeof(str)-1, "\\\\.\\%s", port);
    uart_handle = CreateFileA(str,
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL);
    
    if(uart_handle == INVALID_HANDLE_VALUE)
    {
        return -1;
    }

    memset(&settings, 0, sizeof(settings));
    settings.DCBlength = sizeof(settings);
    if(!GetCommState(uart_handle, &settings))
    {
        return -1;
    }
    settings.DCBlength = sizeof(DCB);

    settings.BaudRate = baudrate;               // Setup the baud rate.
    settings.Parity = NOPARITY;              // Setup the parity.
    settings.ByteSize = 8;                   // Setup the data bits.
    settings.StopBits = ONESTOPBIT;                   // Setup the stop bits.
    settings.fRtsControl = RTS_CONTROL_HANDSHAKE;
    settings.fOutxCtsFlow = TRUE;

    if(!SetCommState(uart_handle, &settings))
    {
        printf("SetCommState failed\n");
        return -1;
    }
    
    return 0;
}

void uart_close()
{
    CloseHandle(uart_handle);
}

int uart_rx(uint16_t data_length, uint8_t* data)
{
    /** Variable for storing function return values. */
    DWORD ret;
    /** The amount of bytes still needed to be read. */
    DWORD data_to_read = data_length;
    /** The amount of bytes read. */
    DWORD data_read;

    while(data_to_read)
    {
        ret = ReadFile(
            uart_handle,
            data,
            data_to_read,
            &data_read,
            NULL);            
        if(!ret)
        {
            ret = GetLastError();
            if(ret == ERROR_SUCCESS)
            {
                continue;
            }
            return -1;
        } else
        {
            if(!data_read)
            {
                continue;
            }
        }
        data_to_read -= data_read;
        data += data_read;
    }

    return data_length;
}

int uart_tx(uint16_t data_length, uint8_t* data)
{
    /** Variable for storing function return values. */
    DWORD ret;
    /** The amount of bytes written. */
    DWORD data_written;
    /** The amount of bytes still needed to be written. */
    DWORD data_to_write = data_length;

     while(data_to_write)
     {
         ret = WriteFile(
             uart_handle,
             data,
             data_to_write,
             &data_written,
             NULL);
         if(!ret)
         {
             return -1;
         }
         data_to_write -= data_written;
         data += data_written;
     }
     FlushFileBuffers(uart_handle);

     return data_length;
}

int uart_peek(void)
{
    DWORD dwErrorFlags;
    COMSTAT ComStat;

    ClearCommError(uart_handle, &dwErrorFlags, &ComStat);

    return((int)ComStat.cbInQue);
}
