

#include <iostream>
#include <ctime>
#include <stdarg.h>

#include "ui/shell.h"

using namespace std;

static void TimeCallback(void* context, EtcPalLogTimestamp* timestamp)
{
  // Fill in timestamp with the current time...
  time_t now = time(0);
  tm* gmtm = gmtime(&now);
  timestamp->year = gmtm->tm_year + 1900;
  timestamp->month = gmtm->tm_mon + 1;
  timestamp->day = gmtm->tm_mday;
  timestamp->hour = gmtm->tm_hour;
  timestamp->minute = gmtm->tm_min;
  timestamp->second = gmtm->tm_sec;
}

static void LogCallback(void* context, const EtcPalLogStrings* log_strings)
{
  cout << log_strings->human_readable;
}

EtcPalLogParams log_params;

void InitializeShell()
{
  etcpal_init(ETCPAL_FEATURE_LOGGING);
  log_params = ETCPAL_LOG_PARAMS_INIT;
  log_params.action = ETCPAL_LOG_CREATE_HUMAN_READABLE;
  log_params.log_mask = ETCPAL_LOG_UPTO(ETCPAL_LOG_DEBUG);
  log_params.log_fn = LogCallback;
  log_params.time_fn = TimeCallback;
}

void LogShell(int priority, const char* format, ...)
{
  va_list args;
  va_start(args, format);
  etcpal_vlog(&log_params, priority, format, args);
  va_end(args);
}


