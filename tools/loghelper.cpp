
#include "loghelper.h"
#include <limits.h>
#include <unistd.h>
#include <string.h>

std::once_flag LogHelper::flag;
FILE *LogHelper::file=NULL;
std::string LogHelper::CurrentPath="";
std::mutex LogHelper::lock;

LogHelper::LogHelper()
{
}

LogHelper::~LogHelper()
{
    if(file !=NULL)
    {
        fclose(file);
    }
}


static std::string GetCurPath()
{
#ifdef __linux__
    char *path_name=get_current_dir_name();
    std::string path(path_name);
#ifdef CURRENT_PATH_MACRO
    path= CURRENT_PATH_MACRO;
#endif
    return path;
#else


#endif
}
/*
void LogHelper::writeLog(LogLevel lev, const char *format, ...)
{
    va_list	arg;
    va_start(arg, format);
    writeLog(lev,format, arg);
    va_end(arg);

}
*/
static const char *lvstr[]={
    "[INFO]",
    "[WARNING]",
    "[ERROR]"
};

void LogHelper::writeLog(LogLevel lev,bool isdebug, const char *format, ...)
{
    char pbString[1024]={0};
    va_list	arg;
    va_start(arg, format);
    vsprintf(pbString, format, arg);
    va_end(arg);

    char timestr[256] = { 0 };
    const char *levstr=lvstr[lev];
    GetTimestamp(timestr,sizeof(timestr));
    strcat(timestr, " ");
    strcat(timestr,levstr);

    if (isdebug)
    {
        std::lock_guard<std::mutex> locker(lock);
        std::cout<<timestr<<" "<<pbString << std::endl;
        return;
    }
    /*
    try
    {
        std::call_once(flag,Init);
    }catch (std::exception &ex)
    {
        std::cout<<"exception:"<<ex.what()<<std::endl;
    }
    */
    Init();
    if (file == NULL)
    {
        std::cout<<"file is NULL"<<std::endl;
        return;
    }
    // fwrite(timestr, strlen(timestr), 1, file);
    //参数的值不能正常显示，原因是参数传递错误，fprintf不能正确处理va_list类型的参数
    std::lock_guard<std::mutex> locker(lock);
    fprintf(file, "%s %s\n",timestr,pbString);
    fflush(file);
    fclose(file);
    file=NULL;
}


#define MAX_PATH 266

void LogHelper::writeLog(LogLevel lev, bool isdebug, const char *format, va_list &arg)
{
    char pbString[1024]={0};
    FILE *file = NULL;

    vsprintf(pbString, format, arg);

    std::string CurrentPath;
    CurrentPath = GetCurPath();
    CurrentPath += "/mylog.log";

    char timestr[64] = { 0 };
    const char *levstr="[INFO]";
    if(lev==LogLevel::L_ERROR)
    {
        levstr="[ERROR]";
    }
    if (lev == LogLevel::L_WARNING)
    {
        levstr="[WARNING]";
    }
    FormattTime(time(NULL), timestr, sizeof(timestr), NULL);
    strcat(timestr, " ");
    strcat(timestr,levstr);
    strcat(timestr, " ");
    fwrite(timestr, strlen(timestr), 1, file);

    if (isdebug)
    {
        std::cout << pbString << std::endl;

        return;
    }

    file = fopen( CurrentPath.c_str(), "ab");
    if (file == NULL)
    {
        file =  fopen(CurrentPath.c_str(), "ab");
    }

    //参数的值不能正常显示，原因是参数传递错误，fprintf不能正确处理va_list类型的参数
    fprintf(file, "%s\n",pbString);

    fflush(file);
    fclose(file);
    file=NULL;
}

void LogHelper::FormattTime(time_t t, char *formstr, size_t size, const char*formatt)
{
    if (formstr == NULL)
    {
        return;
    }
    if (formatt == NULL)
    {
        formatt = "%Y-%m-%d %H:%M:%S";
    }
    struct tm *ptm ;
    ptm= localtime(&t);
    strftime(formstr, size, formatt, ptm);
}

void LogHelper::Init()
{
    CurrentPath = GetCurPath();
    CurrentPath += "/mylog.log";
    file = fopen(CurrentPath.c_str(), "ab");
    if (file == NULL)
    {
        file = fopen(CurrentPath.c_str(), "w");
        if (file == NULL)
        {
            return;
        }
        fclose(file);
        file = fopen(CurrentPath.c_str(), "ab+");
    }

}


void LogHelper::GetTimestamp(std::string *result)
{
    char sdate[256]={0};
    GetTimestamp(sdate,sizeof(sdate));
    *result=sdate;
}

void LogHelper::GetTimestamp(char *buff, int len)
{
    struct timeval tv;
    struct tm *dc=NULL;
    char sdate[128]={0};

    gettimeofday(&tv,NULL);
    memset(sdate,0,sizeof(sdate));
    dc = localtime(&tv.tv_sec);
    strftime(sdate,sizeof(sdate),"%Y-%m-%d %H:%M:%S",dc);
    sprintf(buff,"%s.%.3lu.%.3lu",sdate,tv.tv_usec/1000,tv.tv_usec%1000);

}
