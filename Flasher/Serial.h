/*
    serial communiction layer for [win & linux]
    Date: 2022/11/18
    autor: hard phoenix
*/

#ifndef serial_H
#define serial_H

#include <stdint.h>
#include <stdbool.h>

/*debug 1:0 ------------------------------------------------------------*/
#define _Serial_Debug 1
/*----------------------------------------------------------------------*/
#if _Serial_Debug == 1
#define sdebug(...) printf(__VA_ARGS__)
#else
#define sdebug(...)
#endif
/*end debug 1:0 ------------------------------------------------------------*/

#ifdef _WIN32
#include <windows.h>
#endif
#ifdef linux

#endif

typedef enum
{
    serial_buad_921600 = 1,
    serial_buad_460800 = 2,
    serial_buad_230400 = 3,
    serial_buad_115200 = 4,
} serial_buad;

typedef enum
{
    ser_ok = 0,
    ser_err = 1,
    ser_handle_err,
    ser_not_open,
} serial_result;

typedef struct
{
    char com_name[32];
    bool com_open;
#ifdef _WIN32
    HANDLE handle_port;
#endif

} serial_data_t;

uint32_t serial_convert_buad_toInt(serial_buad bd);
serial_result serial_change_buad(serial_data_t *serial,serial_buad bd);
serial_result serial_init(serial_data_t *serial, char *com_name, serial_buad buadrate);
serial_result serial_close(serial_data_t *serial);
uint32_t serial_write(serial_data_t *serial, uint8_t *buffer, uint32_t len_buffer);
uint32_t serial_read(serial_data_t *serial, uint8_t *read_buffer, uint32_t len_buffer);

#endif /*serial_H*/
