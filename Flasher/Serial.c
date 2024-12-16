/*
 * flasher.c
 *
 *  Created on: 2022/11/18
 *
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This File Part Of MC60 [MT6261] Flasher Library For Control Serial 
 * Interface.
 * Port For Windows and You can use For Linux Or Other System.
 *
 *	Author: Mohammad Hosein Taheri
 *	gmail: etatosel@gmail.com
 *
 *  Version: 0.9
 */

#include "Serial.h"
#include <stdio.h>

uint32_t serial_convert_buad_toInt(serial_buad bd)
{
    uint32_t sbuad = 115200;
    switch (bd)
    {
    case serial_buad_115200:
        sbuad = 115200;
        break;
    case serial_buad_230400:
        sbuad = 230400;
        break;
    case serial_buad_460800:
        sbuad = 460800;
        break;
    case serial_buad_921600:
        sbuad = 921600;
        break;
    }
    return sbuad;
}

serial_result serial_change_buad(serial_data_t *serial, serial_buad bd)
{
#ifdef _WIN32
    DCB dcd;
    if (!GetCommState(serial->handle_port, &dcd))
    {
        sdebug("\nError in get port state");
        return ser_err;
    }
    dcd.BaudRate = serial_convert_buad_toInt(bd); // 115200 , 460800 , 921600 ,2900000 ,3200000
    dcd.ByteSize = 8;
    dcd.Parity = NOPARITY;
    dcd.StopBits = ONESTOPBIT;

    if (!SetCommState(serial->handle_port, &dcd))
    {
        sdebug("\nError in set port state");
        return ser_err;
    }
    sdebug("\nCom Init with Buadrate:%8d,Bsize:%d", dcd.BaudRate, dcd.ByteSize);
    return ser_ok;
#endif
}

serial_result serial_init(serial_data_t *serial, char *com_name, serial_buad buadrate)
{
    memset(serial->com_name, 0, sizeof(serial->com_name));

#ifdef _WIN32
    sprintf(serial->com_name, "\\\\.\\%s", com_name);

    serial->handle_port = CreateFileA(serial->com_name, GENERIC_WRITE | GENERIC_READ, 0, NULL, OPEN_EXISTING, 0,
                                      NULL);

    if (serial->handle_port == INVALID_HANDLE_VALUE)
    {
        sdebug("\ncan not make new com port handle file");
        serial->com_open = FALSE;
        return ser_handle_err;
    }
    sdebug("\nCom Port : %s Open", com_name);

    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (SetCommTimeouts(serial->handle_port, &timeouts) == FALSE)
    {
        sdebug("\n error serial time out");
    }

    if (SetCommMask(serial->handle_port, EV_RXCHAR) == FALSE)
    {
        sdebug("\n error in set Com mask");
        return ser_err;
    }
    if (!FlushFileBuffers(serial->handle_port))
    {
        sdebug("\nfail to flush serial port");
        CloseHandle(serial->handle_port);
        return ser_err;
    }
    /*config com port*/
    serial_change_buad(serial, buadrate);

    // todo: gpio set
    // EscapeCommFunction(flash->hport,CLRRTS);
    // Sleep(1000);
    serial->com_open = TRUE;
    return ser_ok;
#endif

#ifdef linux

#endif
}

serial_result serial_close(serial_data_t *serial)
{
    if (!serial->com_open)
    {
        sdebug("\nCom not open");
        return ser_err;
    }
    sdebug("\nclosing com Port");
#ifdef _WIN32
    CloseHandle(serial->handle_port);
    sdebug("\nclose port: %s Success", serial->com_name);
    return ser_ok;

#endif

#ifdef linux
//..
#endif
}

uint32_t serial_write(serial_data_t *serial, uint8_t *buffer, uint32_t len_buffer)
{
#ifdef _WIN32
    uint32_t writen_buffer = 0;
    OVERLAPPED txOverlaped;
    bool st = WriteFile(serial->handle_port, buffer, len_buffer, (LPDWORD)&writen_buffer, NULL);
    if (st == false)
    {
        return 0;
    }
    return writen_buffer;
#endif

#ifdef linux
//..
#endif
}

uint32_t serial_read(serial_data_t *serial, uint8_t *read_buffer, uint32_t len_buffer)
{
    uint32_t len_read = 0;
#ifdef _WIN32

    DWORD dwRead;
    BOOL fWaitingOnRead = FALSE;
    OVERLAPPED osReader = {0};
    osReader.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (osReader.hEvent == NULL)
    {
        sdebug("\nerror Create Event");
    }
    if (!fWaitingOnRead)
    {
        if (!ReadFile(serial->handle_port, read_buffer, len_buffer, &dwRead, &osReader))
        {
            // sdebug("\nerr No Rx Data");
        }
        else
        {
            // debug("Read %d data: %s",(int)dwRead,read_buffer);
            fWaitingOnRead = TRUE;
            return (uint32_t)dwRead;
        }
    }
    else
    {
        // HandleASuccessfulRead(rx_buffer,dwRead);
    }
#endif

#ifdef linux

#endif
}
