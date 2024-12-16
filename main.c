#include "Flasher/flasher.h"


int main(void)
{
    flash_data_t flash={0};

    /**
     * @Help
     * COM5 Is a simple Test You Can Input Your Input
     * 
     * SerialBuad Rate 921600 You Can Select From This List:
     *          serial_buad_921600
     *          serial_buad_460800
     *          serial_buad_230400
     *          serial_buad_115200
     * 
     * TimeOut :15 Second (From 1 to 200 Second)
     * Reset After End Programmed Flash : True
     * Path Of Yout MT6261(MC60) BinaryFile: "C:\\Desktop\\MC60_AVLHDR.bin" (You Must be input Your *Bin path)
     */
    flash_upload_app(&flash, (const char *)"COM5", (serial_buad)serial_buad_921600, 15, TRUE,"C:\\Desktop\\MC60_AVLHDR.bin");
    uint32_t tx_sended=0, rx_recived=0;

    return 10;
}
