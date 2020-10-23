#include "pch.h"
#include <windows.h>
#include "SerialPortLib.h"

HANDLE hPort = NULL;

bool printer_open(const char* com_port)
{
    DCB dcb = { 0 };
    hPort = CreateFileA(
        com_port,
        GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if (hPort == NULL)
        return false;

    if (!GetCommState(hPort, &dcb))
        return false;

    dcb.BaudRate = CBR_9600;     //9600 Baud
    dcb.ByteSize = 8;            //8 data bits
    dcb.Parity = NOPARITY;      //no parity
    dcb.StopBits = ONESTOPBIT;  //1 stop
    if (!SetCommState(hPort, &dcb))
        return false;

    char data[100];
    // init default
    data[0] = 0x1B;
    data[1] = '@';

    // set mode (BEMA)
    data[2] = 0x1D;
    data[3] = 0xf9;
    data[4] = 0x35;
    data[5] = 0x00;
    if (printer_write(data, 6) == false)
        return false;

    return true;
}

bool printer_close()
{
    bool ret = CloseHandle(hPort);
    hPort = NULL;
    return ret;
}

bool printer_write(const char* data, const int len)
{
    if (hPort == NULL)
        return false;

    DWORD byteswritten;
    bool retVal = WriteFile(hPort, data, len, &byteswritten, NULL);

    if (len != byteswritten)
        return false;

    return retVal;
}

bool printer_read(const char* data, const int len)
{
    if (hPort == NULL)
        return false;

    DWORD bytesread;
    bool retVal = ReadFile(hPort, (LPVOID)data, len, &bytesread, NULL);

    if (len != bytesread)
        return false;

    return retVal;
}

bool printer_read_status(char* output, int& len)
{
    char data[10];
    data[0] = 0x1D;
    data[1] = 0xF8;
    data[2] = 0x31;

    printer_write(data, 3);

    if (printer_read(output, 5) == false)
        return false;
    len = 5;
    return true;
}

bool printer_cut()
{
    if (hPort == NULL)
        return false;

    char data[100];
    // skip paper
    data[0] = 0x1B;
    data[1] = 0x66;
    data[2] = 0x31;
    data[3] = 0x05;
    if (printer_write(data, 4) == false)
    {
        return false;
    }

    // cut paper
    data[0] = 0x1B;
    data[1] = 0x69;
    if (printer_write(data, 2) == false)
    {
        return false;
    }

    return true;
}