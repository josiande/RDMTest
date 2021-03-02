/*****************************************************************//**
 * \file   rdm_controller.h
 * \brief  RDM interface definitions
 * 
 * All of the classes/functions/definitions for the RDM interface are
 * in this header.
 * 
 * \author janderson
 * \date   February 2021
 *********************************************************************/

#ifndef RDMTEST_RDMCONTROLLER_H
#define RDMTEST_RDMCONTROLLER_H

#include "GadgetDll.h"
#include "etcpal/timer.h"
#include "dmxrdm/rdm_device.h"



class RDMController
{
public:
  RDMController();
  void Discover();
  void SendRDM(unsigned int device_index, RDM_CmdC cmd);

  int GetNumConnectedDevices();
  RDMDevice* GetConnectedDevice(int device_index);
private:
  int num_gadgets_;
  int num_connected_devices_;
  RDMDevice connected_devices_[64];

  int SearchForGadgetsBlocking();
  int SearchForGadgetsNonBlocking();

};


RDMController* GetRDMControllerInstance();

#endif
