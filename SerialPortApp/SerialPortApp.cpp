#include <iostream>
#include "SerialPortLib.h"

#define PRINTER_PORT "\\\\.\\COM6"


int main() {

    char data[100];

    if (serial_open(PRINTER_PORT) == false)
    {
        std::cout << "Porta serial falhou para abrir" << std::endl;
        return -1;
    }
    std::cout << "Porta serial conectada com sucesso" << std::endl;

    // init default
    data[0] = 0x1B;
    data[1] = '@';

    // set mode (BEMA)
    data[2] = 0x1D;
    data[3] = 0xf9;
    data[4] = 0x35;
    data[5] = 0x00;
    if (serial_write(data, 6) == false)
    {
        std::cout << "Porta serial falhou para escrever" << std::endl;
        return -1;
    }
    std::cout << "Porta serial comando INIT enviado com sucesso" << std::endl;

    // send data
    strcpy_s(data, "teste impressao");
    if (serial_write(data, 15) == false)
    {
        std::cout << "Porta serial falhou para escrever" << std::endl;
        return -1;
    }
    std::cout << "Porta serial comando WRITE enviado com sucesso" << std::endl;

    // skip paper
    data[0] = 0x1B;
    data[1] = 0x66;
    data[2] = 0x31;
    data[3] = 0x05;
    if (serial_write(data, 4) == false)
    {
        std::cout << "Porta serial falhou para escrever" << std::endl;
        return -1;
    }
    std::cout << "Porta serial comando CUT enviado com sucesso" << std::endl;

    // cut paper
    data[0] = 0x1B;
    data[1] = 0x69;
    if (serial_write(data, 2) == false)
    {
        std::cout << "Porta serial falhou para escrever" << std::endl;
        return -1;
    }
    std::cout << "Porta serial comando CUT enviado com sucesso" << std::endl;

    if (serial_close() == false)
    {
        std::cout << "Porta serial falhou para fechar" << std::endl;
        return -1;
    }
    std::cout << "Porta serial fechada com sucesso" << std::endl;

    return 0;
}