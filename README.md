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
- **CMake** (version 3.10 or higher)
- A compatible **C compiler** (e.g., GCC, Clang, or MSVC)

### Building the Project
1. Clone the repository:
   ```bash
   git clone https://github.com/hardphoenix/MC60_Programmer_C.git
   cd MC60_Programmer
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

### Running the Program
1. Connect your device with the **MT6261 processor** to your PC.
2. Execute the program:
   ```bash
   ./mc60_programmer
   ```
3. Follow the on-screen instructions to program and configure the device.


# Help 
## The "mt6261_da.bin"  file must be in the path of the executable file

## Contribution
We welcome contributions to this project! Feel free to fork the repository, make changes, and submit a pull request. Suggestions for improvements or feature requests are also appreciated.

## License
This project is licensed under the MIT License.

## Contact
For any inquiries or support, please reach out:
- Email: etatosel@gmail.com
