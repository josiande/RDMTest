/*****************************************************************//**
 * \file   rdm_device.h
 * \brief  RDM device class
 * 
 * Class/function/definitions for the RDM device class are in here?
 * 
 * \author janderson
 * \date   February 2021
 *********************************************************************/

#include "GadgetDll.h"

class RDMDevice
{
public:
  RdmDeviceInfo device_info_;
  int gadget_index_;
  int gadget_serial_;

  RDMDevice();
  RDMDevice(RdmDeviceInfo device_info, int gadget_index, int gadget_serial);

private:

};
