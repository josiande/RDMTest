#include "RDMTestClass.h"
#include "etcpal/timer.h"

RDMTestClass::RDMTestClass() 
{

}

int RDMTestClass::TestAllPIDS(uint16_t ManfID, uint32_t DeviceID)
{
	TestDeviceInfo(ManfID, DeviceID);
	return 0;
}

int RDMTestClass::TestDeviceInfo(uint16_t ManfID, uint32_t DeviceID)
{
	EtcPalTimer timer;
	RDM_CmdC* response = nullptr;
	int timeout = 0;
	Gadget2_SendRDMCommand(0, 1, E120_GET_COMMAND, E120_DEVICE_INFO, 0, 0, nullptr, ManfID, DeviceID);
	etcpal_timer_start(&timer, 1000);
	do {
		response = Gadget2_GetResponse(0);
		timeout = etcpal_timer_is_expired(&timer);
	} while (response == nullptr && !timeout);
//	if (response != nullptr)
//		std::cout << ResponseToStringHelper("DEVICE_INFO", E120_DEVICE_INFO, E120_GET_COMMAND, nullptr, response);
	return 0;
}

std::string RDMTestClass::ResponseToStringHelper(std::string ParamName, uint32_t PID, uint8_t Cmd, uint8_t* Data, RDM_CmdC Response)
{
	std::string outputString = "";
	outputString += ParamName;
	std::cout << outputString;
	return outputString;
}