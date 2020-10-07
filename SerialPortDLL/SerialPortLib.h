// SerialPortLib.h - Contains declarations of math functions
#pragma once

#ifdef SERIALPORTLIB_EXPORTS
#define SERIALPORTLIB_API __declspec(dllexport)
#else
#define SERIALPORTLIB_API __declspec(dllimport)
#endif

extern "C" SERIALPORTLIB_API bool serial_open(
    const char* com_port);

extern "C" SERIALPORTLIB_API bool serial_close();

extern "C" SERIALPORTLIB_API bool serial_write(const char* data, int len);

#pragma once
