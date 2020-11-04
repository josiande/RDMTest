#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

#include "RDMTestClass.h"
#include "RDMDevice.h"
#include "etcpal/timer.h"

RDMTestClass::RDMTestClass(std::string outputFileName = "RDMTestResults.csv")
{
	RDMTestClass::outputFileName = outputFileName;
	RDMTestClass::testLog = "";
}

int RDMTestClass::TestAllPIDS(RDMDevice device)
{
	uint8_t sentData[0xE6];
	uint16_t manfId = device.GetManfId();
	uint32_t deviceId = device.GetDeviceId();
	testLog += "Parameter Name,PID,Get/Set,Data,Result,ManfID,DeviceID,Transaction #,Response Type,Message Count,Command Class,PID,Length,Data,\n";
	PIDTest("DEVICE_INFO", manfId, deviceId, E120_DEVICE_INFO, E120_GET_COMMAND, 0, 0, nullptr, device);
	PIDTest("DEVICE_INFO", manfId, deviceId, E120_DEVICE_INFO, E120_GET_COMMAND, 1, 0, nullptr, device);
	PIDTest("DEVICE_INFO", manfId, deviceId, E120_DEVICE_INFO, E120_SET_COMMAND, 0, 0, nullptr, device);
	PIDTest("DEVICE_INFO", manfId, deviceId, E120_DEVICE_INFO, E120_SET_COMMAND, 1, 0, nullptr, device);
	sentData[0] = 0;
	sentData[1] = 13;
	PIDTest("DMX_START_ADDRESS", manfId, deviceId, E120_DMX_START_ADDRESS, E120_GET_COMMAND, 0, 0, nullptr, device);
	PIDTest("DMX_START_ADDRESS", manfId, deviceId, E120_DMX_START_ADDRESS, E120_GET_COMMAND, 0, 1, sentData, device);
	PIDTest("DMX_START_ADDRESS", manfId, deviceId, E120_DMX_START_ADDRESS, E120_SET_COMMAND, 0, 2, sentData, device);
	sentData[0] = E120_STATUS_GET_LAST_MESSAGE;
	PIDTest("QUEUED_MESSAGE", manfId, deviceId, E120_QUEUED_MESSAGE, E120_GET_COMMAND, 0, 1, sentData, device);
	sentData[0] = 0;
	sentData[1] = 1;
	PIDTest("DMX_START_ADDRESS", manfId, deviceId, E120_DMX_START_ADDRESS, E120_SET_COMMAND, 0, 2, sentData, device);
	PIDTest("DMX_START_ADDRESS", manfId, deviceId, E120_DMX_START_ADDRESS, E120_GET_COMMAND, 0, 0, nullptr, device);
	PIDTest("SOFTWARE_VERSION_LABEL", manfId, deviceId, E120_SOFTWARE_VERSION_LABEL, E120_GET_COMMAND, 0, 0, nullptr, device);
//	PIDTest("SUPPORTED_PARAMETERS", manfId, deviceId, E120_DEVICE_INFO, E120_GET_COMMAND, 0, 0, nullptr, device);
	PIDTest("DEVICE_MODEL_DESCRIPTION", manfId, deviceId, E120_DEVICE_INFO, E120_GET_COMMAND, 0, 0, nullptr, device);
	std::cout << testLog;
	return 0;
}

int RDMTestClass::TestDeviceInfo(RDMDevice device)
{
	uint8_t expectedData[0x13];
	uint8_t sentData[100];
	uint16_t manfId = device.GetManfId();
	uint32_t deviceId = device.GetDeviceId();
//	RDMDevice device(0, 0x0281);
//	RDM_CmdC sendCmd(E120_GET_COMMAND, E120_DEVICE_INFO, 0, 0, nullptr, ManfID, DeviceID);
	// Test ACK //
	/*if (RDMTestClass::deviceInfo.e120_device_info_valid)
	{
		expectedData[0] = deviceInfo.rdm_protocol_version >> 8 & 0xFF;
		expectedData[1] = deviceInfo.rdm_protocol_version & 0xFF;
		expectedData[2] = deviceInfo.device_model_id >> 8 & 0xFF;
		expectedData[3] = deviceInfo.device_model_id & 0xFF;
		expectedData[4] = deviceInfo.product_category_type >> 8 & 0xFF;
		expectedData[5] = deviceInfo.product_category_type & 0xFF;
		expectedData[6] = deviceInfo.software_version_id >> 24 & 0xFF;
		expectedData[7] = deviceInfo.software_version_id >> 16 & 0xFF;
		expectedData[8] = deviceInfo.software_version_id >> 8 & 0xFF;
		expectedData[9] = deviceInfo.software_version_id & 0xFF;
		expectedData[10] = deviceInfo.dmx_footprint >> 8 & 0xFF;
		expectedData[11] = deviceInfo.dmx_footprint & 0xFF;
		expectedData[12] = deviceInfo.dmx_personality >> 8 & 0xFF;
		expectedData[13] = deviceInfo.dmx_personality & 0xFF;
		expectedData[14] = deviceInfo.dmx_start_address >> 8 & 0xFF;
		expectedData[15] = deviceInfo.dmx_start_address & 0xFF;
		expectedData[16] = deviceInfo.subdevice_count >> 8 & 0xFF;
		expectedData[17] = deviceInfo.subdevice_count & 0xFF;
		expectedData[18] = deviceInfo.sensor_count & 0xFF;
		RDM_CmdC ExpResponse(E120_GET_COMMAND_RESPONSE, E120_DEVICE_INFO, 0, 0x13, expectedData, ManfID, DeviceID);
		ExpResponse.setResponseType(E120_RESPONSE_TYPE_ACK);
		PIDTest("DEVICE_INFO", ManfID, DeviceID, E120_DEVICE_INFO, E120_GET_COMMAND, 0, nullptr, ExpResponse);
	}

	// Test NACK //
	expectedData[0] = 0x00;
	expectedData[1] = E120_NR_FORMAT_ERROR;
	sentData[0] = 0x01;
	RDM_CmdC ExpResponse(E120_GET_COMMAND_RESPONSE, E120_DEVICE_INFO, 0, 0x02, expectedData, ManfID, DeviceID);
	ExpResponse.setResponseType(E120_RESPONSE_TYPE_NACK_REASON);
	PIDTest("DEVICE_INFO", ManfID, DeviceID, E120_DEVICE_INFO, E120_GET_COMMAND, 1, sentData, ExpResponse);
	expectedData[1] = E120_NR_UNSUPPORTED_COMMAND_CLASS;
	ExpResponse.setBuffer(expectedData);
	ExpResponse.setCommand(E120_SET_COMMAND_RESPONSE);
	PIDTest("DEVICE_INFO", ManfID, DeviceID, E120_DEVICE_INFO, E120_SET_COMMAND, 0, nullptr, ExpResponse);
	PIDTest("DEVICE_INFO", ManfID, DeviceID, E120_DEVICE_INFO, E120_SET_COMMAND, 1, sentData, ExpResponse);
	ExpResponse.~RDM_CmdC();
	std::cout << testLog;*/
	PIDTest("DEVICE_INFO", manfId, deviceId, E120_DEVICE_INFO, E120_GET_COMMAND, 0, 0, nullptr, device);
	PIDTest("DEVICE_INFO", manfId, deviceId, E120_DEVICE_INFO, E120_GET_COMMAND, 1, 0, nullptr, device);
	PIDTest("DEVICE_INFO", manfId, deviceId, E120_DEVICE_INFO, E120_SET_COMMAND, 0, 0, nullptr, device);
	PIDTest("DEVICE_INFO", manfId, deviceId, E120_DEVICE_INFO, E120_SET_COMMAND, 1, 0, nullptr, device);
	sentData[0] = 0;
	sentData[1] = 13;
	PIDTest("DMX_START_ADDRESS", manfId, deviceId, E120_DEVICE_INFO, E120_GET_COMMAND, 0, 0, nullptr, device);
	PIDTest("DMX_START_ADDRESS", manfId, deviceId, E120_DEVICE_INFO, E120_GET_COMMAND, 0, 1, sentData, device);
	PIDTest("DMX_START_ADDRESS", manfId, deviceId, E120_DEVICE_INFO, E120_SET_COMMAND, 0, 2, sentData, device);
	std::cout << testLog;
	return 0;
}

int RDMTestClass::CheckForQueuedMessages(RDMDevice device)
{
	
	return 0;
}

void RDMTestClass::SetDeviceToTest(RdmDeviceInfo newDeviceInfo)
{
	RDMTestClass::deviceInfo = newDeviceInfo;
}

RdmDeviceInfo RDMTestClass::GetDeviceToTest()
{
	return RDMTestClass::deviceInfo;
}

std::string RDMTestClass::ResponseToStringHelper(std::string ParamName, uint32_t PID, uint8_t Cmd, uint8_t* Data, uint8_t DataSize, RDM_CmdC Response, int success)
{
	std::string outputString = "";
	std::string dataString = "";
	uint8_t returnData;
	outputString += ParamName + ",";
	outputString += "0x" + IntToHexString(PID, 2) + ",";
	outputString += "0x" + IntToHexString(Cmd, 1) + ",";
	if (Data != nullptr) dataString = RDMTestClass::BufferToHexString(Data, DataSize);
	outputString += dataString + ",";
	if (success < 0) outputString += "FAIL,"; else outputString += "PASS,";
	outputString += "0x" + IntToHexString(Response.getManufacturerId(), 2) + ",";
	outputString += "0x" + IntToHexString(Response.getDeviceId(), 4) + ",";
	outputString += "0x" + IntToHexString(Response.getTransactionNum(), 1) + ",";
	outputString += "0x" + IntToHexString(Response.getResponseType(), 1) + ",";
	outputString += "0x" + IntToHexString(Response.getMessageCount(), 1) + ",";
	outputString += "0x" + IntToHexString(Response.getCommand(), 1) + ",";
	outputString += "0x" + IntToHexString(Response.getParameter(), 2) + ",";
	outputString += "0x" + IntToHexString(Response.getLength(), 1) + ",";
	outputString += "0x" + BufferToHexString((uint8_t*)Response.getBuffer(), Response.getLength()) + ",";

	outputString += "\n";
	return outputString;
}

std::string RDMTestClass::BufferToHexString(uint8_t* buffer, uint8_t length)
{
	std::string tempString = "";
	for (int i = 0; i < length; i++)
		tempString += IntToHexString(buffer[i], 1) + " ";
	return tempString;
}

std::string RDMTestClass::IntToHexString(uint64_t x, uint8_t numBytes)
{
	std::stringstream stream;
	stream << std::setfill('0') << std::setw((uint64_t)numBytes * 2)
		<< std::hex << x;
	return stream.str();
}

int RDMTestClass::PIDTest(std::string ParamName, uint16_t ManfID, uint32_t DeviceID, uint32_t PID, uint8_t Cmd, uint16_t subdevice, uint8_t DataLength, uint8_t* Data, RDMDevice device)
{
	int responseTime = 0, timeout = 0, success = 0, numResponses = 0;
	EtcPalTimer timer;
	RDM_CmdC* response = nullptr;
	RDM_CmdC expectedResponse = device.GetExpectedResponse(RDM_CmdC(Cmd, PID, subdevice, DataLength, Data, ManfID, DeviceID));

	Gadget2_SendRDMCommand(0, 1, Cmd, PID, 0, DataLength, (char*)Data, ManfID, DeviceID);
	etcpal_timer_start(&timer, 1000);
	do {
		numResponses = Gadget2_GetNumResponses();
		timeout = etcpal_timer_is_expired(&timer);
	} while (!numResponses && !timeout);
	std::cout << "unofficial response time: " << std::dec << etcpal_timer_elapsed(&timer) << "ms\n";
	if (!numResponses)
	{
		std::cout << "No response.\n";
	}
	else
	{
		response = Gadget2_GetResponse(0);
		success = CompareResponseHelper(expectedResponse, *response);
		RDMTestClass::testLog += ResponseToStringHelper(ParamName, PID, Cmd, Data, DataLength, *response, success);
	}
	Gadget2_ClearResponse(0);

	return success;
}

int RDMTestClass::CompareResponseHelper(RDM_CmdC ExpResponse, RDM_CmdC ActResponse)
{
	if (ExpResponse.isValid() != ActResponse.isValid())
		return -1;
	//else if (ExpResponse.getTransactionNum() != ActResponse.getTransactionNum())
	//	return -1;
	else if (ExpResponse.getSubdevice() != ActResponse.getSubdevice())
		return -1;
	else if (ExpResponse.getResponseType() != ActResponse.getResponseType())
		return -1;
	else if (ExpResponse.getParameter() != ActResponse.getParameter())
		return -1;
	else if (ExpResponse.getMessageCount() != ActResponse.getMessageCount())
		return -1;
	else if (ExpResponse.getManufacturerId() != ActResponse.getManufacturerId())
		return -1;
	else if (ExpResponse.getDeviceId() != ActResponse.getDeviceId())
		return -1;
	else if (ExpResponse.getLength() != ActResponse.getLength())
		return -1;
	else if (ExpResponse.getCommand() != ActResponse.getCommand())
		return -1;

	uint8_t* ExpData = (uint8_t*)ExpResponse.getBuffer();
	uint8_t* ActData = (uint8_t*)ActResponse.getBuffer();
	for (int i = 0; i < ActResponse.getLength(); i++)
		if (ExpData[i] != ActData[i]) return -1;
	return 0;
}


void RDMTestClass::PrintTestLog()
{
	std::ofstream myFile;
	myFile.open(RDMTestClass::outputFileName);
	myFile << RDMTestClass::testLog;
	myFile.close();
}