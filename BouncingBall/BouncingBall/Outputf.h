#pragma once

#include <Windows.h>
#include <iostream>

//Function for printing to Output console. Uses winapi.
int outputf(const char *fmt, ...) {
	va_list va;
	va_start(va, fmt);

	char buffer[4096];

	int len = vsprintf(buffer, fmt, va);
	buffer[len] = '\n';
	buffer[len + 1] = '\0';

	OutputDebugString(buffer);

	va_end(va);
}