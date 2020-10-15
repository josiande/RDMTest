#pragma once
#include <iostream>
#include <fstream>
#include <string>

#include "rdm/defs.h"
#include "GadgetDLL.h"
#include "RDM_CmdC.h"

class RDMTestClass
{
	std::string outputFileName;
	std::string testLog;
public:
	RDMTestClass(std::string outputFileName);
	int TestAllPIDS(uint16_t ManfID, uint32_t DeviceID);
	int TestDeviceInfo(uint16_t ManfID, uint32_t DeviceID);
	int PIDTest(std::string ParamName, uint16_t ManfID, uint32_t DeviceID, uint32_t PID, uint8_t Cmd, uint8_t DataLength, uint8_t* Data, RDM_CmdC ExpResponse);
	void PrintTestLog();
private:
	std::string ResponseToStringHelper(std::string ParamName, uint32_t PID, uint8_t Cmd, uint8_t* Data, uint8_t DataSize, RDM_CmdC Response);
	std::string IntToHexString(uint64_t x, uint8_t numBytes);
	std::string BufferToHexString(uint8_t* buffer, uint8_t length);
	int CompareResponseHelper(RDM_CmdC ExpResponse, RDM_CmdC ActResponse);
};

