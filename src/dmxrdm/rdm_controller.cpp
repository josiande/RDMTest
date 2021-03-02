#include "dmxrdm/rdm_controller.h"
#include "ui/console.h"

RDMController::RDMController()
{
  num_gadgets_ = 0;
  num_connected_devices_ = 0;
  Gadget2_Connect();
}

void RDMController::Discover()
{
  EtcPalTimer timer;
  int num_discovered_devices = 0;
  num_gadgets_ = SearchForGadgetsBlocking();
  num_connected_devices_ = 0;
  for (int cur_gadget = 0; cur_gadget < num_gadgets_; cur_gadget++)
  {
    int serial_num = Gadget2_GetGadgetSerialNumber(cur_gadget);
    for (int cur_port = 1; cur_port <= 2; cur_port++)
    {
      Gadget2_DoFullDiscovery(cur_gadget, cur_port);
      etcpal_timer_start(&timer, 1000);
      while (!etcpal_timer_is_expired(&timer))
      {
      }
      num_discovered_devices = Gadget2_GetDiscoveredDevices();
      for (int cur_device = 0; cur_device < num_discovered_devices; cur_device++)
      {
        RdmDeviceInfo* new_device_info = Gadget2_GetDeviceInfo(cur_device);
        RDMDevice new_device(*new_device_info, cur_gadget, serial_num);
        connected_devices_[num_connected_devices_] = new_device;
        num_connected_devices_++;
        LogConsole(ETCPAL_LOG_DEBUG, "\r\nconnected device: %04X%08X\r\nport number: %d\r\n",
                   new_device.device_info_.manufacturer_id, new_device.device_info_.device_id,
                   new_device.device_info_.port_number);
      }
    }
  }
}

void RDMController::SendRDM(unsigned int device_index, RDM_CmdC cmd)
{
  // RDM_CmdC *cmd = Gadget2_GetResponse(0);

  Gadget2_SendRDMCommand(connected_devices_[device_index].gadget_index_,
                         connected_devices_[device_index].device_info_.port_number, cmd.getCommand(),
                         cmd.getParameter(), cmd.getSubdevice(), cmd.getLength(), (const char*)cmd.getBuffer(),
                         connected_devices_[device_index].device_info_.manufacturer_id,
                         connected_devices_[device_index].device_info_.device_id);
}

int RDMController::GetNumConnectedDevices()
{
  return num_connected_devices_;
}

RDMDevice* RDMController::GetConnectedDevice(int device_index)
{
  if (device_index < num_connected_devices_)
    return &connected_devices_[device_index];
  else
    return nullptr;
}

int RDMController::SearchForGadgetsBlocking()
{
  int found_gadgets = 0, timeout = 0;
  EtcPalTimer timer;
  etcpal_timer_start(&timer, 1000);
  do
  {
    found_gadgets = Gadget2_GetNumGadgetDevices();
    timeout = etcpal_timer_is_expired(&timer);
  } while (!timeout && !found_gadgets);
  return found_gadgets;
}

RDMController my_rdm_controller;

void InitRDMControllerInstance()
{
  ;
}

RDMController* GetRDMControllerInstance()
{
  return &my_rdm_controller;
}
