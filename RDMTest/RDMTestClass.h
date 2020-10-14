#pragma once
#include <iostream>
#include <string>

#include "rdm/defs.h"
#include "GadgetDLL.h"
#include "RDM_CmdC.h"

class RDMTestClass
{
	std::string outputFileName;
public:
	RDMTestClass();
	int TestAllPIDS(uint16_t ManfID, uint32_t DeviceID);
	int TestDeviceInfo(uint16_t ManfID, uint32_t DeviceID);
private:
	std::string ResponseToStringHelper(std::string ParamName, uint32_t PID, uint8_t Cmd, uint8_t* Data, RDM_CmdC Response);
};

