#include <algorithm>
#include "RDMDevice.h"
#include "RDMSupportedParameters.h"

RDMDevice::RDMDevice(int deviceIndex, uint16_t deviceModelId, uint16_t manfId, uint32_t deviceId)
{
	SetDeviceIndex(deviceIndex);
	RDMDevice::deviceModelId = deviceModelId;
	SetDeviceInfo(manfId, deviceId);
}

int RDMDevice::GetDeviceIndex()
{
	return RDMDevice::deviceIndex;
}

void RDMDevice::SetDeviceIndex(int deviceIndex)
{
	RDMDevice::deviceIndex = deviceIndex;
}

uint16_t RDMDevice::GetManfId()
{
	return RDMDevice::deviceInfo.manufacturer_id;
}

uint32_t RDMDevice::GetDeviceId()
{
	return RDMDevice::deviceInfo.device_id;
}

RDM_CmdC RDMDevice::GetExpectedResponse(RDM_CmdC cmdToSend)
{
	RDM_CmdC response;
	if (cmdToSend.getCommand() == E120_GET_COMMAND) 
		response.setCommand(E120_GET_COMMAND_RESPONSE);
	else if (cmdToSend.getCommand() == E120_SET_COMMAND) 
		response.setCommand(E120_SET_COMMAND_RESPONSE);
	response.setParameter(cmdToSend.getParameter());
	if (cmdToSend.getSubdevice() > RDMDevice::deviceInfo.subdevice_count)
		response.setSubdevice(0);
	else 
		response.setSubdevice(cmdToSend.getSubdevice());
	response.setManufacturerId(cmdToSend.getManufacturerId());
	response.setDeviceId(cmdToSend.getDeviceId());
	response.setResponseType(E120_RESPONSE_TYPE_NACK_REASON);
	response.setLength(2);

    /* if (cmdToSend.getSubdevice() > RDMDevice::deviceInfo.subdevice_count)
	{
		uint8_t expectedData[] = { 0, E120_NR_SUB_DEVICE_OUT_OF_RANGE};
		response.setBuffer(expectedData);
		return response;
	} */
	if (!IsSupportedParam(cmdToSend.getParameter()))
	{
		uint8_t expectedData[] = { 0, E120_NR_UNKNOWN_PID };
		response.setBuffer(expectedData);
		return response;
	}
	switch (cmdToSend.getParameter())
	{
		case E120_QUEUED_MESSAGE:
			break;
		case E120_STATUS_MESSAGES:
			break;
		case E120_SUPPORTED_PARAMETERS:
			if (cmdToSend.getCommand() == E120_GET_COMMAND)
			{
				if (cmdToSend.getLength() == 0)
				{
					uint8_t expectedData[0xE6];
					memcpy(expectedData, supportedParams, numSupportedParams);
					response.setBuffer(expectedData);
					response.setResponseType(E120_RESPONSE_TYPE_ACK);
				}
				else
				{
					uint8_t expectedData[] = { 0, E120_NR_FORMAT_ERROR };
					response.setBuffer(expectedData);
				}
			}
			else
			{
				uint8_t expectedData[] = { 0, E120_NR_UNSUPPORTED_COMMAND_CLASS };
				response.setBuffer(expectedData);
			}
			break;
		case E120_PARAMETER_DESCRIPTION:
			break;
		case E120_DEVICE_INFO:
			if (cmdToSend.getCommand() != E120_GET_COMMAND && cmdToSend.getCommand() != E120_DISCOVERY_COMMAND)
			{
				uint8_t expectedData[] = { 0, E120_NR_UNSUPPORTED_COMMAND_CLASS };
				response.setBuffer(expectedData);
			}
			else if (cmdToSend.getLength() > 0)
			{
				uint8_t expectedData[] = { 0, E120_NR_FORMAT_ERROR };
				response.setBuffer(expectedData);
			}
			else
			{
				response.setResponseType(E120_RESPONSE_TYPE_ACK);
				response.setLength(0x13);
				uint8_t expectedData[] = {
					RDMDevice::deviceInfo.rdm_protocol_version >> 8 & 0xFF,
					RDMDevice::deviceInfo.rdm_protocol_version & 0xFF,
					RDMDevice::deviceInfo.device_model_id >> 8 & 0xFF,
					RDMDevice::deviceInfo.device_model_id & 0xFF,
					RDMDevice::deviceInfo.product_category_type >> 8 & 0xFF,
					RDMDevice::deviceInfo.product_category_type & 0xFF,
					RDMDevice::deviceInfo.software_version_id >> 24 & 0xFF,
					RDMDevice::deviceInfo.software_version_id >> 16 & 0xFF,
					RDMDevice::deviceInfo.software_version_id >> 8 & 0xFF,
					RDMDevice::deviceInfo.software_version_id & 0xFF,
					RDMDevice::deviceInfo.dmx_footprint >> 8 & 0xFF,
					RDMDevice::deviceInfo.dmx_footprint & 0xFF,
					RDMDevice::deviceInfo.dmx_personality >> 8 & 0xFF,
					RDMDevice::deviceInfo.dmx_personality & 0xFF,
					RDMDevice::deviceInfo.dmx_start_address >> 8 & 0xFF,
					RDMDevice::deviceInfo.dmx_start_address & 0xFF,
					RDMDevice::deviceInfo.subdevice_count >> 8 & 0xFF,
					RDMDevice::deviceInfo.subdevice_count & 0xFF,
					RDMDevice::deviceInfo.sensor_count & 0xFF
				};
				response.setBuffer(expectedData);
			}
			break;
		case E120_DEVICE_MODEL_DESCRIPTION:
			if (cmdToSend.getCommand() == E120_GET_COMMAND)
			{
				if (cmdToSend.getLength() == 0)
				{
					uint8_t expectedData[33];
					memcpy(expectedData, RDMDevice::deviceModelDescription, sizeof(RDMDevice::deviceModelDescription));
					response.setBuffer(expectedData);
					response.setResponseType(E120_RESPONSE_TYPE_ACK);
				}
				else
				{
					uint8_t expectedData[] = { 0, E120_NR_FORMAT_ERROR };
					response.setBuffer(expectedData);
				}
			}
			else
			{
				uint8_t expectedData[] = { 0, E120_NR_UNSUPPORTED_COMMAND_CLASS };
				response.setBuffer(expectedData);
			}
			break;
		case E120_MANUFACTURER_LABEL:
		case E120_DEVICE_LABEL:
		case E120_FACTORY_DEFAULTS:
			break;
		case E120_SOFTWARE_VERSION_LABEL:
			if (cmdToSend.getCommand() == E120_GET_COMMAND)
			{
				if (cmdToSend.getLength() == 0)
				{
					uint8_t expectedData[33];
					memcpy(expectedData, RDMDevice::deviceInfo.software_version_label, sizeof(RDMDevice::deviceInfo.software_version_label));
					response.setBuffer(expectedData);
					response.setResponseType(E120_RESPONSE_TYPE_ACK);
				}
				else
				{
					uint8_t expectedData[] = { 0, E120_NR_FORMAT_ERROR };
					response.setBuffer(expectedData);
				}
			}
			else
			{
				uint8_t expectedData[] = { 0, E120_NR_UNSUPPORTED_COMMAND_CLASS };
				response.setBuffer(expectedData);
			}
			break;
		case E120_DMX_PERSONALITY:
		case E120_DMX_PERSONALITY_DESCRIPTION:
			break;
		case E120_DMX_START_ADDRESS:
			if (cmdToSend.getCommand() == E120_GET_COMMAND)
			{
				if (cmdToSend.getLength() == 0)
				{
					uint8_t expectedData[] = { RDMDevice::deviceInfo.dmx_start_address >> 8 & 0xFF, RDMDevice::deviceInfo.dmx_start_address & 0xFF };
					response.setBuffer(expectedData);
					response.setResponseType(E120_RESPONSE_TYPE_ACK);
				}
				else
				{
					uint8_t expectedData[] = { 0, E120_NR_FORMAT_ERROR };
					response.setBuffer(expectedData);
				}
			}
			else if (cmdToSend.getCommand() == E120_SET_COMMAND)
			{
				if (cmdToSend.getLength() != 2)
				{
					uint8_t expectedData[] = { 0, E120_NR_FORMAT_ERROR };
					response.setBuffer(expectedData);
					return response;
				}
				uint8_t *sendBuffer = (uint8_t*)cmdToSend.getBuffer();
				uint16_t startAddress = (sendBuffer[0] << 8 & 0xFF00) + (sendBuffer[1] & 0xFF);
				if (startAddress > 512)
				{
					uint8_t expectedData[] = { 0, E120_NR_DATA_OUT_OF_RANGE };
					response.setBuffer(expectedData);
				}
				else 
				{
					response.setResponseType(E120_RESPONSE_TYPE_ACK);
					response.setLength(0);
					response.setBuffer(nullptr);
					response.setMessageCount(1);
				}
			}
			break;
		case E120_SLOT_INFO:
		case E120_SLOT_DESCRIPTION:
		case E120_DEFAULT_SLOT_VALUE:
		case E120_SENSOR_DEFINITION:
		case E120_SENSOR_VALUE:
		case E120_IDENTIFY_DEVICE:
		case E120_RESET_DEVICE:
		case E120_CAPTURE_PRESET:
		case E120_PRESET_PLAYBACK:
		case E120_ETC_SEQUENCE_PLAYBACK:
		case E120_ETC_SEQUENCE_CONFIG:
		case E120_ETC_LOW_POWER_TIMEOUT:
		case E120_ETC_LOW_POWER_TIMEOUT_DESCRIPTION:
		case E120_ETC_LED_ENUM_FREQUENCY:
		case E120_ETC_LED_ENUM_FREQUENCY_DESCRIPTION:
		case E120_ETC_RGBI_PRESETCONFIG:
		case E120_ETC_PREPAREFORSOFTWAREDOWNLOAD:
			break;
	}
	return response;
}

void RDMDevice::SetDeviceInfo(uint16_t manfId, uint32_t deviceId)
{
	switch (RDMDevice::deviceModelId) {
		case 0x0802:
			RDMDevice::deviceInfo.manufacturer_id = manfId;
			RDMDevice::deviceInfo.device_id = deviceId;
			RDMDevice::deviceModelId = RDMDevice::deviceModelId;
			memcpy(RDMDevice::deviceModelDescription, "S4WRD Color", sizeof("S4WRD Color"));
			memcpy(RDMDevice::deviceInfo.software_version_label, "1.0.0.20", sizeof("1.0.0.20"));

			RDMDevice::deviceInfo.rdm_protocol_version = 0x0100;
			RDMDevice::deviceInfo.device_model_id = RDMDevice::deviceModelId;
			RDMDevice::deviceInfo.product_category_type = 0x0101;
			RDMDevice::deviceInfo.software_version_id = 0x01000010; //1.0.0.16

			RDMDevice::deviceInfo.dmx_footprint = 0x0006;
			RDMDevice::deviceInfo.dmx_personality = 0x0101;
			RDMDevice::deviceInfo.dmx_start_address = 0x0001;

			RDMDevice::deviceInfo.subdevice_count = 0;
			RDMDevice::deviceInfo.sensor_count = 2;

			RDMDevice::deviceInfo.software_version_label_valid = true;
			RDMDevice::deviceInfo.e120_device_info_valid = true;

			RDMDevice::numSupportedParams = sizeof(S4WRD_COLOR_PARAMS);
			memcpy(RDMDevice::supportedParams, S4WRD_COLOR_PARAMS, sizeof(S4WRD_COLOR_PARAMS));
			break;
		case 0x0281:
			RDMDevice::deviceInfo.manufacturer_id = manfId;
			RDMDevice::deviceInfo.device_id = deviceId;
			RDMDevice::deviceModelId = RDMDevice::deviceModelId;
			memcpy(RDMDevice::deviceModelDescription, "ColorSource Par Zoom", sizeof("ColorSource Par Zoom"));
			memcpy(RDMDevice::deviceInfo.software_version_label, "0.0.0.29", sizeof("0.0.0.29"));

			RDMDevice::deviceInfo.rdm_protocol_version = 0x0100;
			RDMDevice::deviceInfo.device_model_id = RDMDevice::deviceModelId;
			RDMDevice::deviceInfo.product_category_type = 0x0101;
			RDMDevice::deviceInfo.software_version_id = 0x0000001D; //0.0.0.29

			RDMDevice::deviceInfo.dmx_footprint = 0x0006;
			RDMDevice::deviceInfo.dmx_personality = 0x0205;
			RDMDevice::deviceInfo.dmx_start_address = 0x0001;

			RDMDevice::deviceInfo.subdevice_count = 0;
			RDMDevice::deviceInfo.sensor_count = 0;

			RDMDevice::deviceInfo.software_version_label_valid = true;
			RDMDevice::deviceInfo.e120_device_info_valid = true;
			
			RDMDevice::numSupportedParams = sizeof(CS_PAR_ZOOM_PARAMS);
			memcpy(RDMDevice::supportedParams, CS_PAR_ZOOM_PARAMS, sizeof(CS_PAR_ZOOM_PARAMS));
			break;
	}
}


bool RDMDevice::IsSupportedParam(uint16_t PID)
{
	uint16_t* i = std::find(RDMDevice::supportedParams, RDMDevice::supportedParams + RDMDevice::numSupportedParams, PID);
	if (i != RDMDevice::supportedParams + RDMDevice::numSupportedParams)
		return true;
	else
		return false;
}
