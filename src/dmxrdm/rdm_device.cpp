#include "dmxrdm/rdm_device.h"

RDMDevice::RDMDevice()
{
  gadget_index_ = -1;
  gadget_serial_ = 0;
}

RDMDevice::RDMDevice(RdmDeviceInfo device_info, int gadget_index, int gadget_serial)
{
  device_info_ = device_info;
  gadget_index_ = gadget_index;
  gadget_serial_ = gadget_serial;
}
