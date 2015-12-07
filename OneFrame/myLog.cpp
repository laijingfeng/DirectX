#include <Windows.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>
#include "myLog.h"

MyLog::MyLog()
{

}

MyLog::~MyLog()
{

}

void MyLog::Log(const char *format, ...)
{
    char buf[4096], *p = buf;
    va_list args;
    va_start(args, format);
    p += _vsnprintf(p, sizeof buf - 1, format, args);
    va_end(args);
    OutputDebugString(buf);
}

