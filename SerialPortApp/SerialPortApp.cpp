#include <iostream>
#include "SerialPortLib.h"

#define PRINTER_PORT "\\\\.\\COM6"


int main() {

    char data[100];

    if (printer_open(PRINTER_PORT) == false)
    {
        std::cout << "Porta serial falhou para abrir" << std::endl;
        return -1;
    }
    std::cout << "Porta serial conectada com sucesso" << std::endl;

    // send data
    strcpy_s(data, "teste impressao");
    if (printer_write(data, 15) == false)
    {
        std::cout << "Porta serial falhou para escrever" << std::endl;
        return -1;
    }
    std::cout << "Porta serial comando WRITE enviado com sucesso" << std::endl;

    if (printer_cut() == false)
    {
        std::cout << "Porta serial falhou para escrever" << std::endl;
        return -1;
    }
    std::cout << "Porta serial comando CUT enviado com sucesso" << std::endl;

    if (printer_close() == false)
    {
        std::cout << "Porta serial falhou para fechar" << std::endl;
        return -1;
    }
    std::cout << "Porta serial fechada com sucesso" << std::endl;

    return 0;
}