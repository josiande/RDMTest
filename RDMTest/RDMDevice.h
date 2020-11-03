#pragma once
#include "GadgetDll.h"
#include "RDM_CmdC.h"
#include "rdm/defs.h"

class RDMDevice 
{
	int deviceIndex;
	int deviceModelId;
	RdmDeviceInfo deviceInfo;

public:
	RDMDevice(int deviceIndex, uint16_t deviceModelId, uint16_t manfId, uint32_t deviceId);
	int GetDeviceIndex();
	void SetDeviceIndex(int deviceIndex);
	uint16_t GetManfId();
	uint32_t GetDeviceId();
	RDM_CmdC GetExpectedResponse(RDM_CmdC cmdToSend);
private:
	void SetDeviceInfo(uint16_t manfId, uint32_t deviceId);
};