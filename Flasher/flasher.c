#include "flasher.h"

void flash_prog_init(flash_progrssbar_t *prog, uint8_t *prg_name, uint32_t total_size, uint32_t step_size);
void flash_prog_reset(flash_progrssbar_t *prog);
void flash_progress_print(const char *format, uint16_t count, char tag);
void flash_progressbar_update(flash_progrssbar_t *prg, uint32_t now_size);

result_t flash_connect(flash_data_t *flash);
result_t flash_da_start(flash_data_t *flash);
result_t flash_send_flashinfo(flash_data_t *flash, uint32_t offset);
result_t flash_da_changebuad(flash_data_t *flash, serial_buad bd);
result_t flash_upload_firmware(flash_data_t *flash);
result_t flash_open_firmware(flash_data_t *flash, char *path);
result_t flash_da_mem(flash_data_t *flash, uint32_t address, uint32_t filesize, uint16_t filetype, uint16_t filecount, uint8_t fota);
result_t flash_da_write(flash_data_t *flash, uint32_t block);
result_t flash_da_write_data(flash_data_t *flash, uint8_t *data, uint32_t block);
uint16_t flash_crc_16(uint8_t *data, uint32_t len_data);
result_t flash_format_fat(flash_data_t *flash);
result_t flash_da_finish(flash_data_t *flash);
result_t flash_da_reset(flash_data_t *flash);

uint16_t get_system_Time_s(void);
void flash_get_da(flash_data_t *flash, uint8_t *buf, uint32_t offset, uint32_t size);
uint8_t *flash_send(flash_data_t *flash, uint8_t *data, uint16_t len_data, uint32_t sz, uint16_t timeout_ms);
uint8_t *flash_cmd(flash_data_t *flash, uint8_t *data, uint16_t len_data, uint32_t size);
uint8_t *flash_da_read_16(flash_data_t *flash, uint32_t Address, uint32_t size);
void flash_da_write16(flash_data_t *flash, uint32_t Address, uint32_t val);
void flash_da_write32(flash_data_t *flash, uint32_t Address, uint32_t val);
void flash_da_send_da(flash_data_t *flash, uint32_t address, uint32_t size, uint8_t *data, uint32_t block);

void flash_Error(void *msg)
{
    debug("\nError %s", (char *)msg);
    exit(0);
}

void flash_Assert(int err_id, void *msg)
{
    if (err_id == FALSE)
    {
        flash_Error("\nAssert !");
    }
}

bool flash_load_da_frimware(flash_data_t *flash, char *path)
{
    flash->ffs = flash_fopen(path, "r+b"); // r+b for bin add : b
    if (flash->ffs == NULL)
    {
        flash->ffs = NULL;
        return FALSE;
    }
    return TRUE;
}

uint8_t *flash_send(flash_data_t *flash, uint8_t *data, uint16_t len_data, uint32_t sz, uint16_t timeout_ms)
{
    static uint8_t buf[250];
    flash_memset(buf, 0, sizeof(buf));
    if (len_data)
    {
        debug("\n--> ");
        for (int k = 0; k < len_data; k++)
        {
            debug("%02X", data[k]);
        }
        serial_write(&flash->serial, data, len_data);
    }
    if (sz)
    {
        if (timeout_ms > 0)
            flash_sleep(timeout_ms);

        uint32_t rlen = serial_read(&flash->serial, &buf[0], sz);
        debug("\n<<-- ");
        for (int j = 0; j < rlen; j++)
        {
            debug("%02X", buf[j]);
        }
    }
    return &buf[0];
}

uint8_t *flash_cmd(flash_data_t *flash, uint8_t *data, uint16_t len_data, uint32_t sz)
{
    static uint8_t rbuf[250];
    uint8_t *sbuf = NULL;
    debug("\n");
    if (len_data)
    {
        sbuf = flash_send(flash, data, len_data, len_data, 0);
    }
    if (sz)
    {
        flash_memset(rbuf, 0, sizeof(rbuf));
        uint16_t rlen = serial_read(&flash->serial, &rbuf[0], sz);
        debug("\n<<<-- ");
        for (int j = 0; j < rlen; j++)
        {
            debug("%02X", rbuf[j]);
        }
    }

    return &rbuf[0];
}

uint8_t *flash_da_read_16(flash_data_t *flash, uint32_t Address, uint32_t size)
{
    uint8_t *rp = NULL;
    uint8_t d[10];
    uint16_t idx = 0;
    flash_memset(d, 0, sizeof(d));
    d[idx++] = CMD_READ_16;
    d[idx++] = (uint8_t)((Address >> 24) & 0xFF);
    d[idx++] = (uint8_t)((Address >> 16) & 0xFF);
    d[idx++] = (uint8_t)((Address >> 8) & 0xFF);
    d[idx++] = (uint8_t)((Address)&0xFF);
    d[idx++] = (uint8_t)((size >> 24) & 0xFF);
    d[idx++] = (uint8_t)((size >> 16) & 0xFF);
    d[idx++] = (uint8_t)((size >> 8) & 0xFF);
    d[idx++] = (uint8_t)((size)&0xFF);

    rp = flash_cmd(flash, &d[0], idx, size * 2);

    return &rp[0];
}

void flash_da_write16(flash_data_t *flash, uint32_t Address, uint32_t val)
{
    uint8_t *rp = NULL;
    uint8_t d[10];
    uint32_t s = 0x0001;
    uint16_t idx = 0;

    flash_memset(d, 0, sizeof(d));
    d[idx++] = CMD_WRITE16;
    d[idx++] = (uint8_t)((Address >> 24) & 0xFF);
    d[idx++] = (uint8_t)((Address >> 16) & 0xFF);
    d[idx++] = (uint8_t)((Address >> 8) & 0xFF);
    d[idx++] = (uint8_t)((Address)&0xFF);
    d[idx++] = (uint8_t)((s >> 24) & 0xFF);
    d[idx++] = (uint8_t)((s >> 16) & 0xFF);
    d[idx++] = (uint8_t)((s >> 8) & 0xFF);
    d[idx++] = (uint8_t)((s)&0xFF);

    rp = flash_cmd(flash, &d[0], idx, 2);
    // flash_Assert(*rp,"Write16 CMD");
    idx = 0;
    d[idx++] = (uint8_t)((val >> 8) & 0xFF);
    d[idx++] = (uint8_t)(val & 0xFF);
    rp = flash_cmd(flash, &d[0], idx, 2);
    // flash_Assert(*rp,"Write16 VAL");
}

void flash_da_write32(flash_data_t *flash, uint32_t Address, uint32_t val)
{
    uint8_t *rp = NULL;
    uint8_t d[10];
    uint32_t s = 0x0001;
    uint16_t idx = 0;

    flash_memset(d, 0, sizeof(d));
    d[idx++] = CMD_WRITE32;
    d[idx++] = (uint8_t)((Address >> 24) & 0xFF);
    d[idx++] = (uint8_t)((Address >> 16) & 0xFF);
    d[idx++] = (uint8_t)((Address >> 8) & 0xFF);
    d[idx++] = (uint8_t)((Address)&0xFF);
    d[idx++] = (uint8_t)((s >> 24) & 0xFF);
    d[idx++] = (uint8_t)((s >> 16) & 0xFF);
    d[idx++] = (uint8_t)((s >> 8) & 0xFF);
    d[idx++] = (uint8_t)((s)&0xFF);

    rp = flash_cmd(flash, &d[0], idx, 2);
    // flash_Assert(*rp,"Write16 CMD");
    idx = 0;
    d[idx++] = (uint8_t)((val >> 24) & 0xFF);
    d[idx++] = (uint8_t)((val >> 16) & 0xFF);
    d[idx++] = (uint8_t)((val >> 8) & 0xFF);
    d[idx++] = (uint8_t)(val & 0xFF);

    rp = flash_cmd(flash, &d[0], idx, 2);
    // flash_Assert(*rp,"Write16 VAL");
}

void flash_da_send_da(flash_data_t *flash, uint32_t address, uint32_t size, uint8_t *data, uint32_t block)
{
    uint8_t *rp = NULL;
    uint8_t d[15];
    uint16_t time = 0, time_cnt = 0;
    uint16_t idx = 0;
    flash_memset(d, 0, sizeof(d));
    d[idx++] = CMD_SEND_DA;
    d[idx++] = (uint8_t)((address >> 24) & 0xFF);
    d[idx++] = (uint8_t)((address >> 16) & 0xFF);
    d[idx++] = (uint8_t)((address >> 8) & 0xFF);
    d[idx++] = (uint8_t)((address)&0xFF);
    d[idx++] = (uint8_t)((size >> 24) & 0xFF);
    d[idx++] = (uint8_t)((size >> 16) & 0xFF);
    d[idx++] = (uint8_t)((size >> 8) & 0xFF);
    d[idx++] = (uint8_t)((size)&0xFF);
    d[idx++] = (uint8_t)((block >> 24) & 0xFF);
    d[idx++] = (uint8_t)((block >> 16) & 0xFF);
    d[idx++] = (uint8_t)((block >> 8) & 0xFF);
    d[idx++] = (uint8_t)((block)&0xFF);

    rp = flash_cmd(flash, &d[0], idx, 2);

    if (rp[0] != 0x00 && rp[1] != 0x00)
    {
        flash_Error("Send DA CMD");
    }

    debug("\nStart Da");
    uint32_t index = 0;
    uint32_t rem = (size % block);
    // TAG here <=
    while (index <= (size - block))
    {
        uint32_t r = serial_write(&flash->serial, data, block);
        data += block;
        index += block;
        flash_progressbar_update(flash->fprog, block);
    }
    if (rem)
    {
        uint32_t r = serial_write(&flash->serial, data, rem);
        flash_progressbar_update(flash->fprog, rem);
    }
    rp = NULL;
    while (time_cnt < 5)
    {
        rp = flash_cmd(flash, "", 0, 4); // get checksum
        if (*rp != 0)
        {

            break;
        }
        if ((get_system_Time_s()) != time)
        {
            time = get_system_Time_s();
            time_cnt++;
        }
    }
    debug("\nEnd Da");
}

uint16_t get_system_Time_s(void)
{
#ifdef _WIN32
    //
    uint32_t second = 0;
    clock_t nt;
    nt = clock();
    second = ((float)nt) / CLOCKS_PER_SEC;
    // debug("\nnt:%d",second);
    return second;
#endif
#ifdef linux

#endif
}

void flash_prog_init(flash_progrssbar_t *prog, uint8_t *prg_name, uint32_t total_size, uint32_t step_size)
{
    prog->prog_name = prg_name;
    prog->total_size = total_size;
    prog->step_size = step_size;
}

void flash_prog_reset(flash_progrssbar_t *prog)
{
    prog = NULL;
}

void flash_progress_print(const char *format, uint16_t count, char tag)
{
    while (count--)
    {
        debug(format, tag);
    }
}

void flash_progressbar_update(flash_progrssbar_t *prg, uint32_t now_size)
{
    if (prg->step_size == 0 || prg->total_size == 0)
        return;

    if (prg->count >= prg->total_size)
        return;

    prg->count += now_size;
    uint32_t hashtag = (prg->count * prg->step_size) / prg->total_size;
    prg->percent = (uint16_t)((prg->count * 100) / prg->total_size);

    debug("\n%s ->[", prg->prog_name);
    flash_progress_print("%c", prg->percent, '#');
    flash_progress_print("%c", (100 - prg->percent), '.');
    debug("] %d%%", prg->percent);
}

result_t flash_connect(flash_data_t *flash)
{
    uint8_t buf[5], rxbuf[5];
    uint32_t send_len = 0, rx_len = 0;
    uint16_t t_now = 0, t_last = 0;
    uint16_t one_second = 0;

    flash_memset(rxbuf, 0, sizeof(rxbuf));
    debug("\nPlease Reset the Device.\nWaiting...");

    while (1)
    {
        buf[0] = 0xA0;
        send_len = serial_write(&flash->serial, &buf[0], 1);
        // debug("\n-->[%d]:%s",send_len,(char*)buf);
        rx_len = serial_read(&flash->serial, &rxbuf[0], 1);
        // debug("\n<--[%d]:%s",rx_len,(char*)rxbuf);

        if (rxbuf[0] == 0x5F)
        {
            debug("\nRead F5");
            buf[0] = 0x0A;
            buf[1] = 0x50;
            buf[2] = 0x05;
            send_len = serial_write(&flash->serial, &buf[0], 3);
            debug("\n-->[%d]:0x%02X,0x%02X,0x%02X", send_len, buf[0], buf[1], buf[2]);
            rx_len = serial_read(&flash->serial, &rxbuf[0], 3);
            debug("\n<--[%d]:0x%02X,0x%02X,0x%02X", rx_len, rxbuf[0], rxbuf[1], rxbuf[2]);
            if (rxbuf[0] == 0xF5 && rxbuf[1] == 0xAF && rxbuf[2] == 0xFA)
            {
                debug("\n##Connect Success");
                break; // from local while
            }
            else
            {
                flash_Error("in BOOT \n");
                flash_memset(rxbuf, 0, sizeof(rxbuf));
                flash_memset(buf, 0, sizeof(buf));
            }
        }

        t_now = get_system_Time_s();
        if (t_now != t_last)
        {
            t_last = t_now;
            one_second++;
            debug("\nTime:%d", one_second);
        }
        if (one_second >= flash->timeout)
        {
            debug("\nTimeout Connection after %d", flash->timeout);
            return f_res_connect_timeout;
            // break; // from local while
        }
    }

    uint8_t BB_CPU_HW[2];
    uint8_t BB_CPU_SW[2];
    uint8_t BB_CPU_ID[2];
    uint8_t BB_CPU_SB[2];
    uint8_t *p;
    p = flash_da_read_16(flash, 0x80000000, 1); // BB_CPU_HW CA02
    memcpy(BB_CPU_HW, p, 2);
    p = flash_da_read_16(flash, 0x80000004, 1); // BB_CPU_SW 0001
    memcpy(BB_CPU_SW, p, 2);
    p = flash_da_read_16(flash, 0x80000008, 1); // BB_CPU_ID 6261
    memcpy(BB_CPU_ID, p, 2);
    p = flash_da_read_16(flash, 0x8000000C, 1); // BB_CPU_SB 8000
    memcpy(BB_CPU_SB, p, 2);
    flash_da_write16(flash, 0xa0700a28, 0x4010);     // 01
    flash_da_write16(flash, 0xa0700a00, 0xF210);     // 02
    flash_da_write16(flash, 0xa0030000, 0x2200);     // 03
    flash_da_write16(flash, 0xa071004c, 0x1a57);     // 04
    flash_da_write16(flash, 0xa0700a28, 0x2b68);     // 05
    flash_da_write16(flash, 0xa071004c, 0x042e);     // 06
    flash_da_write16(flash, 0xa0710068, 0x586a);     // 07
    flash_da_write16(flash, 0xa0710074, 0x0001);     // 08
    flash_da_write16(flash, 0xa0710068, 0x9136);     // 09
    flash_da_write16(flash, 0xa0710074, 0x0001);     // 10
    flash_da_write16(flash, 0xa0710000, 0x430e);     // 11
    flash_da_write16(flash, 0xa0710074, 0x0001);     // 12
    flash_da_write32(flash, 0xa0510000, 0x00000002); //

    if (BB_CPU_ID[0] == 0x62 && BB_CPU_ID[1] == 0x61)
    {
        sprintf(&flash->CPU_NAME[0], "MT6261");
        debug("\nSoc ID:[%s] Read Success", (char *)flash->CPU_NAME);
        if (flash_load_da_frimware(flash, "mt6261_da.bin") == FALSE)
        {
            return f_res_fremware_da_err;
        }
    }
    else
    {
        debug("\nError :Soc[%02X%02X] Not Support", BB_CPU_ID[1], BB_CPU_ID[0]);
        return f_res_err;
    }
    return f_res_ok;
}

void flash_get_da(flash_data_t *flash, uint8_t *buf, uint32_t offset, uint32_t size)
{
    // TODO Get Alloc in heap
    // uint8_t *buf = flash_malloc(size + 1); // alloc from heap
    // //flash_memset(buf, 0, size);
    flash_fseek(flash->ffs, offset, SEEK_SET);
    flash_fread(flash->ffs, buf, size);
    // return &buf[0];
}

result_t flash_da_start(flash_data_t *flash)
{
    uint8_t sb[15];
    uint8_t *dbuf = NULL;
    uint16_t idx = 0;
    flash_memset(sb, 0, sizeof(sb));
    flash_progrssbar_t fprog = {0};
    flash->fprog = &fprog;
    flash_prog_init(flash->fprog, "DA Start", (uint32_t)(MT6261_DA_1_SIZE + MT6261_DA_2_SIZE), 50);
    flash_progressbar_update(&fprog, 0);
    /*SEND_DA_1-------------------------------------------------------*/
    uint32_t offset = MT6261_DA_1_OFFSET;
    uint32_t size = MT6261_DA_1_SIZE;
    uint32_t addr_1 = MT6261_DA_1_ADDRESS;
    dbuf = flash_malloc(size);
    flash_memset(dbuf, 0, size);
    flash_get_da(flash, &dbuf[0], offset, size);
    flash_da_send_da(flash, addr_1, size, dbuf, 0x400); // checksum DAF0000
    /*end SEND_DA_1-------------------------------------------------------*/
    flash_free(dbuf);
    dbuf = NULL;
    /*SEND_DA_2-------------------------------------------------------*/
    offset = MT6261_DA_2_OFFSET;
    size = MT6261_DA_2_SIZE;
    uint32_t addr_2 = MT6261_DA_2_ADDRESS;
    dbuf = flash_malloc(size);
    flash_memset(dbuf, 0, size);
    flash_get_da(flash, &dbuf[0], offset, size);
    flash_da_send_da(flash, addr_2, size, dbuf, 0x800); // checksum E4230000
    /*end SEND_DA_2-------------------------------------------------------*/
    flash_free(dbuf);
    dbuf = NULL;
    offset += size;

    sb[idx++] = CMD_JUMP_DA;
    sb[idx++] = (uint8_t)((addr_1 >> 24) & 0xFF);
    sb[idx++] = (uint8_t)((addr_1 >> 16) & 0xFF);
    sb[idx++] = (uint8_t)((addr_1 >> 8) & 0xFF);
    sb[idx++] = (uint8_t)(addr_1 & 0xFF);

    dbuf = flash_cmd(flash, &sb[0], idx, 2);
    if (dbuf[0] != 0x00 || dbuf[1] != 0x00) // TODO assert ret buf
    {
        flash_Error("CMD Checksum Jump DA");
    }
    dbuf = flash_cmd(flash, "", 0, 4); // C003028E
    idx = 0;
    dbuf = NULL;
    flash_memset(sb, 0, sizeof(sb));
    sb[idx++] = 0xA5;
    sb[idx++] = 0x05;
    sb[idx++] = 0xFE;
    sb[idx++] = 0x00;
    sb[idx++] = 0x08;
    sb[idx++] = 0x00;
    sb[idx++] = 0x70;
    sb[idx++] = 0x07;
    sb[idx++] = 0xFF;
    sb[idx++] = 0xff;
    sb[idx++] = 0x02;
    sb[idx++] = 0x00;
    sb[idx++] = 0x00;
    sb[idx++] = 0x01;
    sb[idx++] = 0x08;
    dbuf = flash_send(flash, &sb[0], idx, 1, 0); // 5A
    /*send flash info*/
    flash_send_flashinfo(flash, offset);
    flash_memset(sb, 0, sizeof(sb));
    flash_send(flash, &sb[0], 4, 256, 0);
    flash_prog_reset(flash->fprog); // clear progress
    return f_res_ok;
}

result_t flash_send_flashinfo(flash_data_t *flash, uint32_t offset)
{
    uint32_t in_offset = offset;
    uint16_t time_cnt = 0, time = 0;
    uint8_t *data = flash_malloc(40);
    uint8_t *rb = NULL;
    for (uint32_t i = 0; i < 512; i++)
    {
        flash_get_da(flash, &data[0], in_offset, 36);
        // TODO assert buff FFFF0000
        in_offset += 36;
        rb = flash_send(flash, &data[0], 36, 1, 0);
        if (rb[0] == RD_ACK)
        {
            while (time_cnt < 2)
            {
                flash_sleep(500);
                rb = NULL;
                rb = flash_cmd(flash, "", 0, 2); // get checksum
                if (rb[0] == 0xA5 && rb[1] == 0x69)
                {
                    break;
                }
                if ((get_system_Time_s()) != time)
                {
                    time = get_system_Time_s();
                    time_cnt++;
                }
            }
            break; // grom local for
        }
        else if (rb[0] != RD_CONF)
        {
            return f_res_ok;
        }
    }
    return f_res_ok;
}

result_t flash_da_changebuad(flash_data_t *flash, serial_buad bd)
{
    if (bd == serial_buad_115200)
        return f_res_buadrate_err;

    uint16_t idx = 0;
    uint8_t buf[10];
    uint8_t *rb = NULL;
    flash_memset(buf, 0, sizeof(buf));
    uint8_t in_buad = bd;
    buf[idx++] = DA_SPEED;
    buf[idx++] = in_buad;
    buf[idx++] = 0x01;
    rb = flash_send(flash, &buf[0], idx, 1, 0);
    if (rb[0] != RD_ACK) // TODO Assert rb
    {
        return f_res_change_buad_ack;
    }
    flash_memset(buf, 0, sizeof(buf));
    buf[0] = RD_ACK;
    flash_send(flash, &buf[0], 1, 0, 0);

    if (serial_change_buad(&flash->serial, bd) != ser_ok)
    {
        return f_res_err;
    }
    rb = NULL;
    flash_memset(buf, 0, sizeof(buf));
    buf[0] = DA_SYNC;
    flash_sleep(200); // Sleep 0.2 s
    for (int i = 0; i < 10; i++)
    {
        rb = flash_send(flash, &buf[0], 1, 1, 0);
        if (rb[0] == DA_SYNC)
        {
            break;
        }
        flash_sleep(200); // Sleep 0.2s
    }
    if (rb[0] != DA_SYNC)
    {
        return f_res_da_sync_err;
    }
    buf[0] = RD_ACK;
    rb = NULL;
    rb = flash_send(flash, &buf[0], 1, 1, 0);
    if (rb[0] != RD_ACK)
    {
        return f_res_da_sync_err;
    }
    rb = NULL;
    for (int i = 0; i < 256; i++)
    {
        buf[0] = i;
        rb = flash_send(flash, &buf[0], 1, 1, 0);
        if (rb[0] != i)
        {
            return f_res_da_sync_err;
        }
    }

    return f_res_ok;
}

result_t flash_da_mem(flash_data_t *flash, uint32_t address, uint32_t filesize, uint16_t filetype, uint16_t filecount, uint8_t fota)
{
    // TAG: fota:NACK -> disable FOTA feature
    uint8_t buf[15];
    uint32_t idx = 0;
    flash_memset(buf, 0, sizeof(buf));
    buf[idx++] = DA_MEM;
    buf[idx++] = fota;
    buf[idx++] = filecount;
    flash_send(flash, &buf[0], idx, 0, 0); // D3A501

    uint32_t start_address = (address & 0x07FFFFFF);
    uint32_t end_address = start_address + filesize - 1;
    uint8_t *rb = NULL;
    flash_memset(buf, 0, sizeof(buf));
    idx = 0;
    buf[idx++] = (uint8_t)((start_address >> 24) & 0xFF);
    buf[idx++] = (uint8_t)((start_address >> 16) & 0xFF);
    buf[idx++] = (uint8_t)((start_address >> 8) & 0xFF);
    buf[idx++] = (uint8_t)((start_address)&0xFF);
    buf[idx++] = (uint8_t)((end_address >> 24) & 0xFF);
    buf[idx++] = (uint8_t)((end_address >> 16) & 0xFF);
    buf[idx++] = (uint8_t)((end_address >> 8) & 0xFF);
    buf[idx++] = (uint8_t)((end_address)&0xFF);
    buf[idx++] = (uint8_t)(((uint32_t)filetype >> 24) & 0xFF);
    buf[idx++] = (uint8_t)(((uint32_t)filetype >> 16) & 0xFF);
    buf[idx++] = (uint8_t)(((uint32_t)filetype >> 8) & 0xFF);
    buf[idx++] = (uint8_t)(((uint32_t)filetype) & 0xFF);

    rb = flash_send(flash, &buf[0], idx, 1, 0);
    if (*rb != RD_ACK) // TAG: Assert DA_MEM ack
        return f_res_da_mem_err;

    flash_send(flash, "", 0, 2, 0); // get :file count + ack
    rb = NULL;
    rb = flash_send(flash, "", 0, 4, 0);
    // uint32_t format_ack_cnt = atoi(rb);
    uint32_t format_ack_cnt = 0;
    format_ack_cnt |= (uint32_t)(((uint32_t)rb[0] << 24) & 0xFF000000);
    format_ack_cnt |= (uint32_t)(((uint32_t)rb[1] << 16) & 0x00FF0000);
    format_ack_cnt |= (uint32_t)(((uint32_t)rb[2]++ << 8) & 0x0000FF00);
    format_ack_cnt |= (uint32_t)(((uint32_t)rb[3]++) & 0x000000FF);
    flash_progrssbar_t da_prg = {0};
    flash_prog_init(&da_prg, (uint8_t *)"Pre-Format", (format_ack_cnt + 1), 1);
    flash_progressbar_update(&da_prg, 0);
    for (int i = 0; i < format_ack_cnt; i++)
    {
        rb = NULL;
        rb = flash_send(flash, "", 0, 1, 200);
        if (rb[0] != RD_ACK)
        {
            debug("\nError memory Format Failed 1");
            return f_res_da_mem_err;
        }
        flash_progressbar_update(&da_prg, 1);
    }
    flash_progressbar_update(&da_prg, 1);
    rb = NULL;
    rb = flash_send(flash, "", 0, 1, 200);
    if (rb[0] != RD_ACK)
    {
        debug("\nError memory Format Failed 2");
        return f_res_da_mem_err;
    }
    return f_res_ok;
}

result_t flash_da_write(flash_data_t *flash, uint32_t block)
{
    uint8_t buf[6];
    uint32_t idx = 0;
    uint8_t *rd = NULL;
    flash_memset(buf, 0, sizeof(buf));
    buf[0] = DA_WRITE;
    rd = flash_send(flash, &buf[0], 1, 1, 0);
    if (rd[0] != RD_ACK)
        return f_res_da_write_err;

    rd = NULL;
    buf[idx++] = 0;
    buf[idx++] = (uint8_t)((block >> 24) & 0xFF);
    buf[idx++] = (uint8_t)((block >> 16) & 0xFF);
    buf[idx++] = (uint8_t)((block >> 8) & 0xFF);
    buf[idx++] = (uint8_t)((block)&0xFF);
    rd = flash_send(flash, &buf[0], idx, 2, 20);
    if (rd[0] != RD_ACK && rd[1] != RD_ACK)
        return f_res_da_write_err;

    return f_res_ok;
}

result_t flash_da_write_data(flash_data_t *flash, uint8_t *data, uint32_t block)
{
    uint8_t buf[4];
    uint8_t *rp = NULL;
    uint32_t index = 0;
    uint16_t crc = 0;
    uint16_t cw = 0;
    uint16_t remind = (flash->filesize % block);

    while (index < (flash->filesize - remind))
    {
        buf[0] = RD_ACK;
        serial_write(&flash->serial, &buf[0], 1);
        serial_write(&flash->serial, data, block);
        crc = flash_crc_16(data, block);
        rp = NULL;
        buf[0] = (uint8_t)((crc >> 8) & 0xFF);
        buf[1] = (uint8_t)((crc)&0xFF);
        rp = flash_send(flash, &buf[0], 2, 1, 50);

        if (rp[0] == RD_CONF)
        {
            flash_progressbar_update(flash->fprog, block);
            cw += crc;
            data += block;
            index += block;
        }
        else if (rp[0] == RD_NACK)
        {
            uint16_t time_cnt = 0;
            uint16_t now_time = get_system_Time_s();
            // TAG need wait to get ack and start new sending packet
            while (time_cnt < 60)
            {
                rp = NULL;
                rp = flash_send(flash, "", 0, 1, 0);
                if (rp[0] == RD_ACK)
                {
                    buf[0] = RD_ACK;
                    serial_write(&flash->serial, &buf[0], 1);
                    break;
                }
                if ((get_system_Time_s()) != now_time)
                {
                    now_time = get_system_Time_s();
                    time_cnt++;
                }
            }
            // TAG Assert timeout ack
            if (time_cnt >= 60)
                return f_res_download_firm_err;
        }
        else
        {
            debug("\nAssert In While index [%d]", index);
            flash_Assert(0, "Download Firmware Fail");
        }
    }
    if (remind)
    {
        buf[0] = RD_ACK;
        serial_write(&flash->serial, &buf[0], 1);
        serial_write(&flash->serial, data, remind);
        crc = flash_crc_16(data, remind);
        rp = NULL;
        buf[0] = (uint8_t)((crc >> 8) & 0xFF);
        buf[1] = (uint8_t)((crc)&0xFF);
        rp = flash_send(flash, &buf[0], 2, 1, 50);

        if (rp[0] == RD_CONF)
        {
            flash_progressbar_update(flash->fprog, remind);
            cw += crc;
            // data += remind;
            // index += remind;
        }
        else if (rp[0] == RD_NACK)
        {
            uint16_t time_cnt = 0;
            uint16_t now_time = get_system_Time_s();
            // TAG need wait to get ack and start new sending packet
            while (time_cnt < 60)
            {
                rp = NULL;
                rp = flash_send(flash, "", 0, 1, 0);
                if (rp[0] == RD_ACK)
                {
                    buf[0] = RD_ACK;
                    serial_write(&flash->serial, &buf[0], 1);
                    break;
                }
                if ((get_system_Time_s()) != now_time)
                {
                    now_time = get_system_Time_s();
                    time_cnt++;
                }
            }
            // TAG Assert timeout ack
            if (time_cnt >= 60)
                return f_res_download_firm_err;
        }
        else
        {
            debug("\nAssert In rem");
            flash_Assert(0, "Download Firmware Fail");
        }
    }

    uint8_t ack_count = 0;
    uint16_t start_time = get_system_Time_s();
    uint16_t time_cnt = 0;

    while (time_cnt < 10)
    {
        rp = NULL;
        rp = flash_send(flash, "", 0, 1, 0);
        if (rp[0] == RD_ACK)
        {
            ack_count++;
            if (ack_count == 3)
                break;
        }
        // if ((get_system_Time_s()) != start_time)
        // {
        //     start_time = get_system_Time_s();
        //     time_cnt++;
        // }
    }
    if (time_cnt > 10)
    {
        debug("\nError Firmware Write");
    }

    rp = NULL;
    cw = cw & 0xFFFF;
    buf[0] = (uint8_t)((cw >> 8) & 0xFF);
    buf[1] = (uint8_t)(cw & 0xFF);
    rp = flash_send(flash, &buf[0], 2, 1, 100);
    if (rp[0] != RD_ACK)
    {
        return f_res_download_firm_err;
    }

    return f_res_ok;
}

uint16_t flash_crc_16(uint8_t *data, uint32_t len_data)
{
    uint32_t ch = 0;
    for (uint32_t i = 0; i < len_data; i++)
    {
        ch += data[i] & 0xFF;
    }
    ch = ch & 0xFFFF;
    // debug("\nCH:[%d], 0x%02X",ch, ch);
    return ch;
}

result_t flash_open_firmware(flash_data_t *flash, char *path)
{
    flash->ffirm = flash_fopen(path, "r+b"); // r+b for bin add : b
    if (flash->ffirm == NULL)
    {
        flash->ffirm = NULL;
        return f_res_loadfrimware_err;
    }
    uint8_t tmp_ftype[2];
    uint8_t tmp_addr[4];
    uint8_t tmp_size[4];
    // char *tmp_app_data;
    flash_fseek(flash->ffirm, 0x18, SEEK_SET);
    flash_fread(flash->ffirm, &tmp_ftype[0], 2);
    flash->filetype |= (uint16_t)(((uint16_t)tmp_ftype[1] << 8) & 0xFF00);
    flash->filetype |= (uint16_t)(((uint16_t)tmp_ftype[0]) & 0x00FF);
    flash_fseek(flash->ffirm, 0x1C, SEEK_SET);
    flash_fread(flash->ffirm, &tmp_addr[0], 4);
    flash_fread(flash->ffirm, &tmp_size[0], 4);
    flash->fileaddress |= (uint32_t)(((uint32_t)tmp_addr[3] << 24) & 0xFF000000);
    flash->fileaddress |= (uint32_t)(((uint32_t)tmp_addr[2] << 16) & 0x00FF0000);
    flash->fileaddress |= (uint32_t)(((uint32_t)tmp_addr[1] << 8) & 0x0000FF00);
    flash->fileaddress |= (uint32_t)(((uint32_t)tmp_addr[0]) & 0x000000FF);
    flash->filesize |= (uint32_t)(((uint32_t)tmp_size[3] << 24) & 0xFF000000);
    flash->filesize |= (uint32_t)(((uint32_t)tmp_size[2] << 16) & 0x00FF0000);
    flash->filesize |= (uint32_t)(((uint32_t)tmp_size[1] << 8) & 0x0000FF00);
    flash->filesize |= (uint32_t)(((uint32_t)tmp_size[0]) & 0x000000FF);

    flash_fseek(flash->ffirm, 0, SEEK_END);
    uint32_t size_of_file = flash_ftell(flash->ffirm);

    if (size_of_file != flash->filesize)
        return f_res_file_sizedismach;

    if (flash->filesize < 0x40)
        return f_res_file_siezeerr;

    // TAG alooc from memorry
    char *tmp_app_data = flash_malloc(flash->filesize);
    flash_memset(tmp_app_data, 0, sizeof(flash->filesize));
    flash_fseek(flash->ffirm, 0, SEEK_SET);
    flash_fread(flash->ffirm, &tmp_app_data[0], flash->filesize);
    char *pt = strstr(tmp_app_data, "MMM");
    if (pt == NULL)
        return f_res_file_invalidHeader;

    // TAG In Binary File strstr with a little jump!
    pt = strstr(&tmp_app_data[8], "FILE_INFO");
    if (pt == NULL)
        return f_res_file_noinfo;

    flash->filedata = &tmp_app_data[0];
    debug("\nRead [%d]KB File Firmware in [%s]", (uint32_t)(flash->filesize / 1024), path);

    return f_res_ok;
}

result_t flash_upload_firmware(flash_data_t *flash)
{
    result_t fres = f_res_ok;
    fres = flash_da_mem(flash, flash->fileaddress, flash->filesize, flash->filetype, 1, RD_NACK);
    if (fres != f_res_ok)
        return fres;

    flash_progrssbar_t firm_prg = {0};
    flash->fprog = &firm_prg;
    flash_prog_init(flash->fprog, (uint8_t *)"Download Firmware", flash->filesize, 50);
    fres = flash_da_write(flash, 4096);
    if (fres != f_res_ok)
        return fres;

    fres = flash_da_write_data(flash, &flash->filedata[0], 4096);
    if (fres != f_res_ok)
        return fres;

    flash_prog_reset(flash->fprog);
    // TODO Free Read file buffer
    flash_free(flash->filedata);

    return f_res_ok;
}

result_t flash_da_finish(flash_data_t *flash)
{
    uint8_t buf[4];
    flash_memset(buf, 0, sizeof(buf));
    buf[0] = DA_FINISH;
    flash_send(flash, &buf[0], 1, 1, 0); // ack
    buf[0] = 0;
    flash_send(flash, &buf[0], 4, 1, 0); // nack

    return f_res_ok;
}

result_t flash_format_fat(flash_data_t *flash)
{
}

result_t flash_da_reset(flash_data_t *flash)
{
}

result_t flash_upload_app(flash_data_t *flash, const char *com_name, serial_buad select_buadrate, uint16_t timeout, bool opt, bool reset_after_flash, uint8_t *path_fw)
{
    result_t fres;
    serial_result sres;
    serial_buad flash_buad;

    fres = flash_open_firmware(flash, (char *)path_fw);
    if (fres != ser_ok)
        return f_res_loadfrimware_err;

    sres = serial_init(&flash->serial, (char *)com_name, serial_buad_115200); // for start buadrate is (serial_buad_115200)
    if (sres != ser_ok)
        return f_res_err;

    flash->timeout = timeout;
    fres = flash_connect(flash);
    if (fres != f_res_ok)
        return fres;

    fres = flash_da_start(flash);
    if (fres != f_res_ok)
        return fres;

    flash_buad = select_buadrate;
    fres = flash_da_changebuad(flash, flash_buad);
    if (fres != f_res_ok)
        return fres;

    fres = flash_upload_firmware(flash);
    if (fres != f_res_ok)
        return fres;

    if (opt == 0)
    {
        fres = flash_format_fat(flash);
        if (fres != f_res_ok)
            return fres;
    }
    if (!reset_after_flash) // TAG No Need reset cpu after flash done
    {
        fres = flash_da_finish(flash);
        if (fres != f_res_ok)
            return fres;
    }
    else
    {
        // TAG reset cpu after flash done
        fres = flash_da_reset(flash);
        if (fres != f_res_ok)
            return fres;
    }
    debug("\n[Flash Complate]");

    // TODO: after complate code upload close com port
    sres = serial_close(&flash->serial);
    if (sres != ser_ok)
        return f_res_com_close_err;
}