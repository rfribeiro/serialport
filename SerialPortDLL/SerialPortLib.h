// SerialPortLib.h - Contains declarations of math functions
#pragma once

#ifdef SERIALPORTLIB_EXPORTS
#define SERIALPORTLIB_API __declspec(dllexport)
#else
#define SERIALPORTLIB_API __declspec(dllimport)
#endif

struct PrinterStatus
{
	bool connected;
	bool online;
	bool ready;
	bool busy;
	int buffer_status;
	int paper;
	int cover;
	int error;
	bool overheat;
};

extern "C" SERIALPORTLIB_API bool printer_open(const char* com_port);

extern "C" SERIALPORTLIB_API bool printer_close();

extern "C" SERIALPORTLIB_API bool printer_write(const char* data, int len);

extern "C" SERIALPORTLIB_API bool printer_cut();

#pragma once
