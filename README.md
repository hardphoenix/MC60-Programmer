# MC60 Programmer and MediaTek MT6261 Flasher
![image](https://github.com/user-attachments/assets/f2cdafed-d895-4ad9-b5c4-fc48b89dbccf)
![image](https://github.com/user-attachments/assets/07c1d4b4-b329-42da-83d4-785646ec9178)

## Description
**MC60 Programmer** is a tool designed for programming **MT6261 processors**, which are widely used in various modules and mobile phones. This project is implemented in **C** and utilizes **CMake** for building and management. It is cross-platform, supporting both **Linux** and **Windows** operating systems.

## Features
- Programming and configuring **MT6261 processors**.
- Cross-platform support: works on **Linux** and **Windows**.
- Lightweight and efficient, written in **C**.
- Built using **CMake** for ease of compilation and integration.

## Getting Started

### Prerequisites
Ensure the following tools are installed on your system:
- **CMake** (version 3.0 or higher)
- A compatible **C compiler** (e.g., GCC, Clang, or MSVC)

### Building the Project
1. Clone the repository:
   ```bash
   git clone https://github.com/hardphoenix/MC60_Programmer_C.git
   cd MC60_Programmer_C
   ```
2. Create a build directory and configure the project using CMake:
   ```bash
   mkdir build
   cd build
   cmake ..
   ```
3. Compile the project:
   ```bash
   cmake --build .
   ```
4. Copy mt6261_da.bin from MT6261_DA Directory Into: build Directory.
   ```bash
   cp MT6261_DA/mt6261_da.bin build/
   ```

### Running the Program
1. Connect your device with the **MT6261 processor** to your PC.
2. Execute the program:
   ```bash
   ./mc60_programmer
   ```
3. Follow the on-screen instructions to program and configure the device.

## Example Usage
The following example demonstrates how to use the library in your `main.c` file:

```c
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
     * Path Of Your MT6261(MC60) BinaryFile: "C:\\Desktop\\MC60_AVLHDR.bin" (You Must input Your *Bin path)
     */
    flash_upload_app(&flash, (const char *)"COM5", (serial_buad)serial_buad_921600, 15, TRUE, "C:\\Desktop\\MC60_AVLHDR.bin");
    uint32_t tx_sended=0, rx_recived=0;

    return 10;
}
```

## Contribution
We welcome contributions to this project! Feel free to fork the repository, make changes, and submit a pull request. Suggestions for improvements or feature requests are also appreciated.

## License
This project is licensed under the MIT License.

## Contact
For any inquiries or support, please reach out:
- Email: etatosel@gmail.com
