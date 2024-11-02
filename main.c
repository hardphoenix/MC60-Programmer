#include "Flasher/flasher.h"
// #include <unistd.h>

int main(void)
{
    // char cwd[500];
    // flash_memset(cwd,0,sizeof(cwd));
    // if(getcwd(&cwd ,sizeof(cwd)) != NULL)
    // {
    //     debug("\nActive Dir: %s",cwd);
    // }

    flash_data_t flash={0};
    flash_upload_app(&flash, (const char *)"COM14", (serial_buad)serial_buad_921600, 15, TRUE,"C:\\Users\\Taheri\\Desktop\\V111\\V111\\MC60_AVLHDR.bin");
    uint32_t tx_sended=0, rx_recived=0;

    // char buffer[128];
    // char rx_buffer[128];
    // uint32_t rx_index = (sizeof(rx_buffer) - 1);
    // buffer[0]= RD_CONF;
    //if (flash.serial.com_open)
    //{
        //for(uint16_t i=0;i<1000;i++)
        //{
            // memset(buffer,0,sizeof(buffer));
            // sprintf(buffer,"Flash com Write %d\r\n",i);
            // tx_sended = serial_write(&flash.serial,&buffer[0],1);   //&buffer[0]
            // // debug("\nSended: %d",tx_sended);
            //debug("\nSend %d :%s",tx_sended,buffer);
            // rx_recived = serial_read(&flash.serial,rx_buffer,1);
            // debug("\nRx %d :%s",rx_recived,rx_buffer);
            //Sleep(1);
        //}
        // flash_com_read(&flash,rx_buffer,3);

        // while (1)
        // {
        //     memset(rx_buffer, 0, sizeof(rx_buffer));
        //     rx_recived = serial_read((serial_data_t*)&flash.serial, rx_buffer, 3);
        //     debug("\nrx [%d]:%s",rx_recived,rx_buffer);
        // }
    //}
    // serial_close(&flash.serial);
    // getchar();
    //exit(10);

    return 10;
}
