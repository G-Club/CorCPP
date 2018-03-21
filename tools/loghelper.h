
#pragma once

#include <stdio.h>
#include <time.h>
#include <string>
#include <varargs.h>
#include <iostream>
#include <stdarg.h>

using namespace std;

class LogHelper
{
public:
	LogHelper();
	~LogHelper();

public:
	enum LogLevel
	{
		L_INFO = 0,
		L_WARNING = 1,
		L_ERROR = 2
	};
	static void FormattTime(time_t t, char *formstr, size_t size, const char*formatt);

	static void writeLog(LogLevel lev, const char *format, ...);

public:
	static int DEBUG_MOD;

private:
	static void writeLog(LogLevel lev, const char *format, va_list arg);
};

