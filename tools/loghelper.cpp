
#include "loghelper.h"
#include <limits.h>
#include <unistd.h>
#include <string.h>

std::once_flag LogHelper::flag;
FILE *LogHelper::file=NULL;

LogHelper::LogHelper()
{
}

LogHelper::~LogHelper()
{

}


static std::string GetCurPath()
{
#ifdef __linux__
   char *path_name=get_current_dir_name();
   std::string path(path_name);
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

void LogHelper::writeLog(LogLevel lev,bool isdebug, const char *format, ...)
{
    char pbString[1024]={0};
    FILE *file = NULL;
    va_list	arg;
    va_start(arg, format);
    vsprintf(pbString, format, arg);
    va_end(arg);


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

    if (isdebug)
    {
        std::cout<<timestr<<
         pbString << std::endl;

        return;
    }

   std::call_once(flag,[](){

   });

    file = fopen( CurrentPath.c_str(), "ab");
    if (file == NULL)
    {
      file =  fopen(CurrentPath.c_str(), "ab");
    }

    fwrite(timestr, strlen(timestr), 1, file);

    //参数的值不能正常显示，原因是参数传递错误，fprintf不能正确处理va_list类型的参数
     fprintf(file, "%s\n",pbString);

    fflush(file);
    fclose(file);

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
