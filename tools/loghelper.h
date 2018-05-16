
#pragma once

#include <stdio.h>
#include <string>
#include <stdarg.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <sys/time.h>

using namespace std;

#define LOG_INFO(b,s,...)  LogHelper::writeLog(LogHelper::LogLevel::L_INFO,b,s,__VA_ARGS__);
#define LOG_WARNING(b,s,...)  LogHelper::writeLog(LogHelper::LogLevel::L_WARNING,b,s,__VA_ARGS__);
#define LOG_ERROR(b,s,...)  LogHelper::writeLog(LogHelper::LogLevel::L_ERROR,b,s,__VA_ARGS__);

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
    static void writeLog(LogLevel lev, bool isdebug, const char *format, ...);


private:
    static std::once_flag flag;
    static std::string CurrentPath;
    static FILE *file;
    static void writeLog(LogLevel lev, bool isdebug,const char *format, va_list &arg);
    static void Init();
    static void GetTimestamp(char *buff,int len);
    static std::mutex lock;
};

