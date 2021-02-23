/*****************************************************************//**
 * \file   shell.h
 * \brief  the RDMTest shell
 * 
 * Classes/functions/definitions for the command line UI are contained
 * in this header.
 * 
 * \author janderson
 * \date   February 2021
 *********************************************************************/

#ifndef RDMTEST_SHELL_H
#define RDMTEST_SHELL_H

#include "etcpal/timer.h"
#include "etcpal/log.h"

void InitializeShell();
void LogShell(int priority, const char* format, ...);

#endif
