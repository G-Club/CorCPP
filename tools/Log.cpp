
void writeLog(const char *format, va_list arg);


void writeLog(const char *format,...)
{
	int count = 0;
	va_list	arg;
	va_start(arg, format);
	writeLog(format, arg);
	va_end(arg);
	
}

void writeLog(const char *format, va_list arg)
{
	char pbString[1024]={0};

	vsprintf_s(pbString, format, arg);

#if DEBUG_MOD

	std::cout << pbString << std::endl;

	return;

#else 

	std::string CurrentPath;
	char chpath[MAX_PATH];
	GetModuleFileNameA(NULL, chpath, sizeof(chpath));
	CurrentPath = chpath;
	int index = CurrentPath.rfind('\\');
	CurrentPath = CurrentPath.substr(0, index + 1);
	CurrentPath += "servicelog.log";

	FILE *file = NULL;
	fopen_s(&file, CurrentPath.c_str(), "ab");
	if (file == NULL)
	{
		fopen_s(&file, CurrentPath.c_str(), "ab");
	}
	int count = 0;

	char timestr[64] = { 0 };
	FormattTime(time(NULL), timestr, sizeof(timestr), NULL);
	strcat_s(timestr, " ");
	fwrite(timestr, strlen(timestr), 1, file);
	//参数的值不能正常显示，原因是参数传递错误，fprintf不能正确处理va_list类型的参数
	count = fprintf(file, pbString);

	fflush(file);
	fclose(file);

#endif

}

void FormattTime(time_t t, char *formstr, size_t size, const char*formatt)
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
