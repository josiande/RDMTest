/*****************************************************************//**
 * \file   console.h
 * \brief  the RDMTest console
 * 
 * Classes/functions/definitions for the command line UI are contained
 * in this header.
 * 
 * \author janderson
 * \date   February 2021
 *********************************************************************/

#ifndef RDMTEST_CONSOLE_H
#define RDMTEST_CONSOLE_H

#include <iostream>
#include <sstream>
#include <ctime>
#include <stdarg.h>

#include "etcpal/timer.h"
#include "etcpal/log.h"

constexpr int kConnectedDevice = 1;

enum class ConsoleCmds
{
  kPrintDevices,
  kDoDiscovery
};

void InitializeConsole();
void ServiceConsole();
void LogConsole(int priority, const char* format, ...);
void ParseInput(char* input_buffer);
void ExecuteCmd(std::string cmd, int param1, int param2, int param3, int param4);

#endif
