#ifndef __mylogH__
#define  __mylogH__

#include <Windows.h>
#include <stdio.h>
#include <stdarg.h>
#include <ctype.h>

class MyLog
{
public:
    MyLog();
    ~MyLog();
    static void Log(const char *format, ...);
};

#endif __mylogH__