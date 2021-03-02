/*****************************************************************//**
 * \file   main.cpp
 * \brief  RDMTest main
 * 
 * \author janderson
 * \date   February 2021
 *********************************************************************/

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "ui/console.h"
#include "dmxrdm/rdm_controller.h"
#include "etcpal/thread.h"

using namespace std;

void console_thread(void* arg)
{
  InitializeConsole();

  for (;;)
  {
    ServiceConsole();
  }
}


int main()
{



  RDMController my_rdm_controller;
  int num_connected_devices;

  //EtcPalThreadParams params = ETCPAL_THREAD_PARAMS_INIT;
  //etcpal_thread_t console_thread_handle;
  //etcpal_error_t result;
  //int arg = 0;
  //result = etcpal_thread_create(&console_thread_handle, &params, console_thread, &my_rdm_controller);
  //if (result == kEtcPalErrOk)
  //{
  //  etcpal_thread_join(&console_thread_handle);
  //}

  InitializeConsole();

  for (;;)
  {
    ServiceConsole();
  }

  my_rdm_controller.Discover();
  num_connected_devices = my_rdm_controller.GetNumConnectedDevices();
  LogConsole(ETCPAL_LOG_DEBUG, "num connected devices: %d\r\n", num_connected_devices);
}
