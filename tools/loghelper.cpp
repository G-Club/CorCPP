
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

void LogHelper::writeLog(bool isdebug,const char *timestr, const char *logstr)
{
    std::lock_guard<std::mutex> locker(lock);
    if (isdebug)
    {
        std::cout<<timestr<<" "<<logstr << std::endl;
        return;
    }

    Init();
    if (file == NULL)
    {
        std::cout<<"file is NULL"<<std::endl;
        return;
    }
    // fwrite(timestr, strlen(timestr), 1, file);
    //参数的值不能正常显示，原因是参数传递错误，fprintf不能正确处理va_list类型的参数
    fprintf(file, "%s %s\n",timestr,logstr);
    fflush(file);
    fclose(file);
    file=NULL;
}

void LogHelper::Error(bool isdebug,const char *format,...)
{
    char pbString[2048]={0};
    va_list	arg;
    va_start(arg, format);
    vsprintf(pbString, format, arg);
    va_end(arg);

    char timestr[256] = { 0 };
    const char *levstr="[ERROR]";
    GetTimestamp(timestr,sizeof(timestr));
    strcat(timestr, " ");
    strcat(timestr,levstr);

    writeLog(isdebug,timestr,pbString);
}

void LogHelper::Info(bool isdebug, const char *format,...)
{
    char pbString[2048]={0};
    va_list	arg;
    va_start(arg, format);
    vsprintf(pbString, format, arg);
    va_end(arg);

    char timestr[256] = { 0 };
    const char *levstr="[INFO]";
    GetTimestamp(timestr,sizeof(timestr));
    strcat(timestr, " ");
    strcat(timestr,levstr);

    writeLog(isdebug,timestr,pbString);
}

void LogHelper::Warning(bool isdebug,const char *format,...)
{
    char pbString[2048]={0};
    va_list	arg;
    va_start(arg, format);
    vsprintf(pbString, format, arg);
    va_end(arg);

    char timestr[256] = { 0 };
    const char *levstr="[WARNING]";
    GetTimestamp(timestr,sizeof(timestr));
    strcat(timestr, " ");
    strcat(timestr,levstr);
    writeLog(isdebug,timestr,pbString);
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
    struct tm *ptm =NULL;
    /*
当我们使用localtime(timestamp)的时候返回是一个指针。
这个指针的指向是共用的，这时如果有其他线程执行了localtime。。。。会覆盖之前的值！！
可以考虑localtime_r
*/
    ptm=localtime_r(&t,ptm);

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
