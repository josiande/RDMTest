#pragma once
#include "GadgetDll.h"
#include "RDM_CmdC.h"
#include "rdm/defs.h"

class RDMDevice 
{
	uint8_t deviceIndex;
	uint16_t deviceModelId;
	unsigned char deviceModelDescription[32];
	unsigned char manfLabel[32];
	unsigned char deviceLabel[32];

	uint8_t numSupportedParams;
	uint16_t supportedParams[0xE6];

	uint8_t isFactoryDefaults;
public:
	RdmDeviceInfo deviceInfo;

	RDMDevice(int deviceIndex, uint16_t deviceModelId, uint16_t manfId, uint32_t deviceId);
	int GetDeviceIndex();
	void SetDeviceIndex(int deviceIndex);
	uint16_t GetManfId();
	uint32_t GetDeviceId();
	RDM_CmdC GetExpectedResponse(RDM_CmdC cmdToSend);

	uint16_t GetDMXAddress();
	void SetDMXAddress(uint16_t dmxAddress);
	uint8_t GetIsFactoryDefaults();
	void SetIsFactoryDefaults(uint8_t isFactoryDefaults);
	void SetDeviceLabel(unsigned char* deviceLabel);
private:
	void SetDeviceInfo(uint16_t manfId, uint32_t deviceId);
	bool IsSupportedParam(uint16_t PID);
	
};