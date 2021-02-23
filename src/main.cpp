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
#include "ui/shell.h"
#include "dmxrdm/rdm_controller.h"

using namespace std;



int main()
{
  RDMController my_rdm_controller;
  int num_connected_devices;

  InitializeShell();

  my_rdm_controller.Discover();
  num_connected_devices = my_rdm_controller.GetNumConnectedDevices();
  LogShell(ETCPAL_LOG_DEBUG, "num connected devices: %d\r\n", num_connected_devices);
}
