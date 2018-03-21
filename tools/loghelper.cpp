
#include "loghelper.h"
#include <direct.h>

int LogHelper::DEBUG_MOD=0;

LogHelper::LogHelper()
{
}

LogHelper::~LogHelper()
{

}


void LogHelper::writeLog(LogLevel lev, const char *format, ...)
{
	int count = 0;
	va_list	arg;
	va_start(arg, format);
	writeLog(lev,format, arg);
	va_end(arg);
	
}

#define MAX_PATH 266

void LogHelper::writeLog(LogLevel lev, const char *format, va_list arg)
{
	char pbString[1024]={0};

	vsprintf_s(pbString, format, arg);

#if DEBUG_MOD

	std::cout << pbString << std::endl;

	return;

#else 
	
	std::string CurrentPath;
	char chpath[MAX_PATH];
	getcwd(chpath, sizeof(chpath));
	CurrentPath = chpath;
	int index = CurrentPath.rfind('\\');
	CurrentPath = CurrentPath.substr(0, index + 1);
	CurrentPath += "monlog.log";

	FILE *file = NULL;
	fopen_s(&file, CurrentPath.c_str(), "ab");
	if (file == NULL)
	{
		fopen_s(&file, CurrentPath.c_str(), "ab");
	}
	int count = 0;

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
	strcat_s(timestr, " ");
	strcat_s(timestr,levstr);
	strcat_s(timestr, " ");
	fwrite(timestr, strlen(timestr), 1, file);
	//参数的值不能正常显示，原因是参数传递错误，fprintf不能正确处理va_list类型的参数
	count = fprintf(file, "%s\n",pbString);

	fflush(file);
	fclose(file);

#endif

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
	struct tm ptm ;
	localtime_s(&ptm,&t);
	strftime(formstr, size, formatt, &ptm);
}
