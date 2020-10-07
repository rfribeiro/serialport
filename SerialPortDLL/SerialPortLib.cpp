#include "pch.h"
#include <windows.h>
#include "SerialPortLib.h"

HANDLE hPort = NULL;

bool serial_open(const char* com_port)
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

    return true;
}

bool serial_close()
{
    bool ret = CloseHandle(hPort);
    hPort = NULL;
    return ret;
}

bool serial_write(const char* data, const int len)
{
    if (hPort == NULL)
        return false;

    DWORD byteswritten;
    bool retVal = WriteFile(hPort, data, len, &byteswritten, NULL);

    if (len != byteswritten)
        return false;

    return retVal;
}