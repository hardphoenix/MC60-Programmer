#ifndef FLASHER_H
#define FLASHER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "Serial.h"

#ifdef _WIN32
#include <time.h>
#include <sysinfoapi.h> //for get time system
#endif

#ifdef linux
//..in next time
#endif

/*version of library----------------------------------------------------*/
#define _FlasherVersion "0.2.0"

/*debug 1:0 ------------------------------------------------------------*/
#define _DEBUG 1
/*----------------------------------------------------------------------*/
#if _DEBUG == 1
#define debug(...) printf(__VA_ARGS__)
#else
#define debug(...)
#endif
/*end debug 1:0 ------------------------------------------------------------*/

/*file work function-----------------------*/
#define flash_file FILE
#define flash_fopen(p, mode) fopen(p, mode)
#define flash_fclose(fd) fclose(fd)
#define flash_fseek(fd, offset, orgin) fseek(fd, offset, orgin)
#define flash_fflush(fd) fflush(fd)
#define flash_fwrite(fd, ptr, sz) fwrite(ptr, sz, 1, fd)
#define flash_fread(fd, ptr, sz) fread(ptr, sz, 1, fd)
#define flash_ftell(fd) ftell(fd)
/*end file work function-----------------------*/

/*config------------------------------------------*/
#define flash_memset memset
#define flash_memcpy memcpy

#define flash_malloc(j) malloc(j)
#define flash_free(j) free(j)

#define flash_sleep(x) Sleep(x)
/*end config------------------------------------------*/

/*MT6261 flash param------------------------------*/
typedef enum
{
    MT6261_DA_1_OFFSET = 0x00000,
    MT6261_DA_1_SIZE = 0x00718,
    MT6261_DA_1_ADDRESS = 0x70007000,

    MT6261_DA_2_OFFSET = 0x00718,
    MT6261_DA_2_SIZE = 0x1e5c8,
    MT6261_DA_2_ADDRESS = 0x10020000,
} MT6261_DA_Param;
/*end MT6261 flash param------------------------------*/

/*cmd general define--------------------------*/
#define CMD_READ_16 0xA2
#define CMD_READ16 0xD0
#define CMD_READ32 0xD1
#define CMD_WRITE16 0xD2
#define CMD_WRITE32 0xD4
#define CMD_JUMP_DA 0xD5
#define CMD_SEND_DA 0xD7
#define CMD_SEND_EPP 0xD9
/*end cmd general define--------------------------*/

/*DA define-----------------------------------*/
#define DA_SYNC 0xC0
#define DA_FORMAT_FAT 0xB8
#define DA_CONFIG_EMI 0xD0
#define DA_POST_PROCESS 0xD1
#define DA_SPEED 0xD2
#define DA_MEM 0xD3
#define DA_FORMAT 0xD4
#define DA_WRITE 0xD5
#define DA_READ 0xD6
#define DA_WRITE_REG16 0xD7
#define DA_READ_REG16 0xD8
#define DA_FINISH 0xD9
#define DA_GET_DSP_VER 0xDA
#define DA_ENABLE_WATCHDOG 0xDB
#define DA_NFB_WRITE_BLOADER 0xDC
#define DA_NAND_IMAGE_LIST 0xDD
#define DA_NFB_WRITE_IMAGE 0xDE
#define DA_NAND_READPAGE 0xDF
/*end DA define-----------------------------------*/

/*other define---------------------------------*/
#define DA_CLEAR_POWERKEY_IN_META_MODE_CMD 0xB9
#define DA_ENABLE_WATCHDOG_CMD 0xDB
#define DA_GET_PROJECT_ID_CMD 0xEF

#define RD_CONF 0x69
#define RD_STOP 0x96
#define RD_ACK 0x5A
#define RD_NACK 0xA5
/*end other define---------------------------------*/

typedef enum
{
    f_res_ok = 0,
    f_res_err,
    f_res_com_open_err,
    f_res_com_open_succes,
    f_res_com_close_err,
    f_res_com_close_succes,
    f_res_connect_fail,
    f_res_connect_timeout,
    f_res_fremware_da_err,
    f_res_flashinfo,
    f_res_buadrate_err,
    f_res_change_buad_ack,
    f_res_da_sync_err,
    f_res_loadfrimware_err,
    f_res_file_sizedismach,
    f_res_file_siezeerr,
    f_res_file_invalidHeader,
    f_res_file_noinfo,
    f_res_da_mem_err,
    f_res_da_write_err,
    f_res_download_firm_err,
} result_t;

typedef struct
{
    uint8_t *prog_name;
    uint32_t total_size;
    uint32_t step_size;
    uint32_t count;
    uint16_t percent;
} flash_progrssbar_t;

typedef struct
{
    char CPU_NAME[8];
    char *filedata;
    uint32_t fileaddress;
    uint32_t filesize;
    uint16_t timeout;
    uint16_t filetype;

    flash_progrssbar_t *fprog;
    flash_file *ffirm;
    flash_file *ffs;
    serial_data_t serial;

} flash_data_t;

void flash_Error(void *msg);
void flash_Assert(int err_id, void *msg);


result_t flash_upload_app(flash_data_t *flash, const char *com_name, serial_buad select_buadrate, uint16_t timeout, bool reset_after_flash, uint8_t *path_fw);

#endif /*FLASHER_H*/
