
#pragma once

#include <stdio.h>
#include <time.h>
#include <string>

using namespace std;

#define DEBUG_MOD 1

void FormattTime(time_t t, char *formstr, size_t size, const char*formatt);
void writeLog(const char *format, ...);