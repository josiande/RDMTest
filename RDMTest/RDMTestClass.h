#pragma once
#include <iostream>
#include <fstream>
#include <string>

#include "rdm/defs.h"
#include "GadgetDLL.h"
#include "RDM_CmdC.h"
#include "RDMDevice.h"

class RDMTestClass
{
	std::string outputFileName;
	std::string testLog;
	RdmDeviceInfo deviceInfo;
public:
	RDMTestClass(std::string outputFileName);
	int TestAllPIDS(RDMDevice device);
	int TestDeviceInfo(RDMDevice device);
	//int TestDMXStartAddress()
	int PIDTest(std::string ParamName, uint16_t ManfID, uint32_t DeviceID, uint32_t PID, uint8_t Cmd, uint16_t subdevice, uint8_t DataLength, uint8_t* Data, RDMDevice device);
	int CheckForQueuedMessages(RDMDevice device);
	void PrintTestLog();
	void SetDeviceToTest(RdmDeviceInfo newDeviceInfo);
	RdmDeviceInfo GetDeviceToTest();
private:
	std::string ResponseToStringHelper(std::string ParamName, uint32_t PID, uint8_t Cmd, uint8_t* Data, uint8_t DataSize, RDM_CmdC Response, int success);
	std::string StatusMessageToStringHelper(RDM_CmdC Response);
	std::string IntToHexString(uint64_t x, uint8_t numBytes);
	std::string BufferToHexString(uint8_t* buffer, uint8_t length);
	std::string CommandToString(uint8_t Cmd);
	uint8_t PIDDataType(uint32_t PID);
	int CompareResponseHelper(RDM_CmdC ExpResponse, RDM_CmdC ActResponse);
};

