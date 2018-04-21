#define _CRT_SECURE_NO_WARNINGS
#include "loghelper.h"
#include <limits.h>
#ifdef __linux__
#include <unistd.h>
#endif

#ifdef _WIN32
#include <direct.h>
#endif

#include <string.h>


int LogHelper::DEBUG_MOD = 0;

LogHelper::LogHelper()
{
}

LogHelper::~LogHelper()
{

}


static std::string GetCurPath()
{
	std::string path = "";
#ifdef __linux__

	char *path_name = get_current_dir_name();
	path = path_name;

#endif

#ifdef _WIN32
	char chpath[_MAX_PATH] = { 0 };
	getcwd(chpath, sizeof(chpath));
	path = chpath;

#endif

	return path;
}

void LogHelper::writeLog(LogLevel lev, const char *format, ...)
{
	va_list	arg;
	va_start(arg, format);
	writeLog(lev, format, arg);
	va_end(arg);

}

void LogHelper::writeLog(LogLevel lev, const char *format, va_list arg)
{
	char pbString[1024] = { 0 };

	vsprintf(pbString, format, arg);

if (DEBUG_MOD==1)
{
	std::cout << pbString << std::endl;
	return;
}
	std::string CurrentPath;
	CurrentPath = GetCurPath();
	CurrentPath += "/mylog.log";

	FILE *file = NULL;
	file = fopen(CurrentPath.c_str(), "ab");
	if (file == NULL)
	{
		file = fopen(CurrentPath.c_str(), "ab");
	}

	char timestr[64] = { 0 };
	const char *levstr = "[INFO]";
	if (lev == LogLevel::L_ERROR)
	{
		levstr = "[ERROR]";
	}
	if (lev == LogLevel::L_WARNING)
	{
		levstr = "[WARNING]";
	}
	FormattTime(time(NULL), timestr, sizeof(timestr), NULL);
	strcat(timestr, " ");
	strcat(timestr, levstr);
	strcat(timestr, " ");
	fwrite(timestr, strlen(timestr), 1, file);

	//参数的值不能正常显示，原因是参数传递错误，fprintf不能正确处理va_list类型的参数
	fprintf(file, "%s\n", pbString);

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
	struct tm *ptm;
	ptm = localtime(&t);

	strftime(formstr, size, formatt, ptm);
}
