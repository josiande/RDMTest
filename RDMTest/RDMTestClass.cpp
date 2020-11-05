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
	if (PIDTest("FACTORY_DEFAULTS", manfId, deviceId, E120_FACTORY_DEFAULTS, E120_SET_COMMAND, 0, 0, nullptr, device))
		device.SetIsFactoryDefaults(1);
	PIDTest("FACTORY_DEFAULTS", manfId, deviceId, E120_FACTORY_DEFAULTS, E120_GET_COMMAND, 0, 0, nullptr, device);

	PIDTest("DEVICE_INFO", manfId, deviceId, E120_DEVICE_INFO, E120_GET_COMMAND, 0, 0, nullptr, device);
	PIDTest("DEVICE_INFO", manfId, deviceId, E120_DEVICE_INFO, E120_GET_COMMAND, 1, 0, nullptr, device);
	PIDTest("DEVICE_INFO", manfId, deviceId, E120_DEVICE_INFO, E120_SET_COMMAND, 0, 0, nullptr, device);
	PIDTest("DEVICE_INFO", manfId, deviceId, E120_DEVICE_INFO, E120_SET_COMMAND, 1, 0, nullptr, device);

	sentData[0] = 0;
	sentData[1] = 13;
	if (PIDTest("DMX_START_ADDRESS", manfId, deviceId, E120_DMX_START_ADDRESS, E120_SET_COMMAND, 0, 2, sentData, device))
	{
		device.SetDMXAddress(13);
		if (device.GetIsFactoryDefaults())
			device.SetIsFactoryDefaults(0);
	}

	sentData[0] = 0;
	sentData[1] = 1;
	
	if (PIDTest("DMX_START_ADDRESS", manfId, deviceId, E120_DMX_START_ADDRESS, E120_SET_COMMAND, 0, 2, sentData, device))
	{
		device.SetDMXAddress(1);
		if (device.GetIsFactoryDefaults())
			device.SetIsFactoryDefaults(0);
	}
	PIDTest("DMX_START_ADDRESS", manfId, deviceId, E120_DMX_START_ADDRESS, E120_GET_COMMAND, 0, 0, nullptr, device);
	PIDTest("DMX_START_ADDRESS", manfId, deviceId, E120_DMX_START_ADDRESS, E120_GET_COMMAND, 0, 0, nullptr, device);
	PIDTest("SOFTWARE_VERSION_LABEL", manfId, deviceId, E120_SOFTWARE_VERSION_LABEL, E120_GET_COMMAND, 0, 0, nullptr, device);
	PIDTest("SUPPORTED_PARAMETERS", manfId, deviceId, E120_SUPPORTED_PARAMETERS, E120_GET_COMMAND, 0, 0, nullptr, device);
	PIDTest("DEVICE_MODEL_DESCRIPTION", manfId, deviceId, E120_DEVICE_MODEL_DESCRIPTION, E120_GET_COMMAND, 0, 0, nullptr, device);
	PIDTest("MANUFACTURER_LABEL", manfId, deviceId, E120_MANUFACTURER_LABEL, E120_GET_COMMAND, 0, 0, nullptr, device);
	PIDTest("DEVICE_LABEL", manfId, deviceId, E120_DEVICE_LABEL, E120_GET_COMMAND, 0, 0, nullptr, device);
	std::cout << testLog;
	return 0;
}

int RDMTestClass::TestDeviceInfo(RDMDevice device)
{
	uint16_t manfId = device.GetManfId();
	uint32_t deviceId = device.GetDeviceId();
	PIDTest("DEVICE_INFO", manfId, deviceId, E120_DEVICE_INFO, E120_GET_COMMAND, 0, 0, nullptr, device);
	PIDTest("DEVICE_INFO", manfId, deviceId, E120_DEVICE_INFO, E120_GET_COMMAND, 1, 0, nullptr, device);
	PIDTest("DEVICE_INFO", manfId, deviceId, E120_DEVICE_INFO, E120_SET_COMMAND, 0, 0, nullptr, device);
	PIDTest("DEVICE_INFO", manfId, deviceId, E120_DEVICE_INFO, E120_SET_COMMAND, 1, 0, nullptr, device);
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
	outputString += CommandToString(Cmd) + "(0x" + IntToHexString(Cmd, 1) + "),";
	if (Data != nullptr) dataString = RDMTestClass::BufferToHexString(Data, DataSize);
	outputString += dataString + ",";
	if (success <= 0) outputString += "FAIL,"; else outputString += "PASS,";
	outputString += "0x" + IntToHexString(Response.getManufacturerId(), 2) + ",";
	outputString += "0x" + IntToHexString(Response.getDeviceId(), 4) + ",";
	outputString += "0x" + IntToHexString(Response.getTransactionNum(), 1) + ",";
	if (Response.getResponseType() == E120_RESPONSE_TYPE_ACK) outputString += "ACK,";
	else if (Response.getResponseType() == E120_RESPONSE_TYPE_NACK_REASON) outputString += "NACK,";
	outputString += "0x" + IntToHexString(Response.getMessageCount(), 1) + ",";
	outputString += CommandToString(Response.getCommand()) + "(0x" + IntToHexString(Response.getCommand(), 1) + "),";
	outputString += "0x" + IntToHexString(Response.getParameter(), 2) + ",";
	outputString += "0x" + IntToHexString(Response.getLength(), 1) + ",";
	if (PIDDataType(PID) == E120_DS_ASCII) outputString += std::string((char*)Response.getBuffer(), Response.getLength());	
	else if (Response.getLength()) outputString += "0x" + BufferToHexString((uint8_t*)Response.getBuffer(), Response.getLength()) + ",";

	outputString += "\n";
	return outputString;
}

std::string RDMTestClass::StatusMessageToStringHelper(RDM_CmdC Response)
{
	std::string outputString = "";
	outputString += ",,,,,";
	outputString += "0x" + IntToHexString(Response.getManufacturerId(), 2) + ",";
	outputString += "0x" + IntToHexString(Response.getDeviceId(), 4) + ",";
	outputString += "0x" + IntToHexString(Response.getTransactionNum(), 1) + ",";
	if (Response.getResponseType() == E120_RESPONSE_TYPE_ACK) outputString += "ACK,";
	else if (Response.getResponseType() == E120_RESPONSE_TYPE_NACK_REASON) outputString += "NACK,";
	outputString += "0x" + IntToHexString(Response.getMessageCount(), 1) + ",";
	outputString += CommandToString(Response.getCommand()) + "(0x" + IntToHexString(Response.getCommand(), 1) + "),";
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

std::string RDMTestClass::CommandToString(uint8_t Cmd)
{
	switch (Cmd)
	{
		case E120_GET_COMMAND:
			return "GET";
		case E120_GET_COMMAND_RESPONSE:
			return "GETr";
		case E120_SET_COMMAND:
			return "SET";
		case E120_SET_COMMAND_RESPONSE:
			return "SETr";
		default:
			return "";
	}
}

int RDMTestClass::PIDTest(std::string ParamName, uint16_t ManfID, uint32_t DeviceID, uint32_t PID, uint8_t Cmd, uint16_t subdevice, uint8_t DataLength, uint8_t* Data, RDMDevice device)
{
	int responseTime = 0, timeout = 0, success = 0, numResponses = 0;
	EtcPalTimer timer;
	RDM_CmdC* response = nullptr;
	RDM_CmdC expectedResponse = device.GetExpectedResponse(RDM_CmdC(Cmd, PID, subdevice, DataLength, Data, ManfID, DeviceID));

	Gadget2_SendRDMCommand(0, 1, Cmd, PID, 0, DataLength, (char*)Data, ManfID, DeviceID);
	etcpal_timer_start(&timer, 250);
	do {
		numResponses = Gadget2_GetNumResponses();
		timeout = etcpal_timer_is_expired(&timer);
	} while (!timeout);
	std::cout << "unofficial response time: " << std::dec << etcpal_timer_elapsed(&timer) << "ms\n";
	if (!numResponses)
	{
		std::cout << "No response.\n";
	}
	else
	{
		std::cout << numResponses << "responses.\n";
		for (int i = 0; i < numResponses; i++)
		{
			response = Gadget2_GetResponse(0);
			success = CompareResponseHelper(expectedResponse, *response);
			if (i == 0)
				RDMTestClass::testLog += ResponseToStringHelper(ParamName, PID, Cmd, Data, DataLength, *response, success);
			else
				RDMTestClass::testLog += StatusMessageToStringHelper(*response);
			Gadget2_ClearResponse(0);
		}
	}
	

	return success;
}

int RDMTestClass::CompareResponseHelper(RDM_CmdC ExpResponse, RDM_CmdC ActResponse)
{
	if (ExpResponse.isValid() != ActResponse.isValid())
		return 0;
	//else if (ExpResponse.getTransactionNum() != ActResponse.getTransactionNum())
	//	return 0;
	else if (ExpResponse.getSubdevice() != ActResponse.getSubdevice())
		return 0;
	else if (ExpResponse.getResponseType() != ActResponse.getResponseType())
		return 0;
	else if (ExpResponse.getParameter() != ActResponse.getParameter())
		return 0;
//	else if (ExpResponse.getMessageCount() != ActResponse.getMessageCount())
//		return 0;
	else if (ExpResponse.getManufacturerId() != ActResponse.getManufacturerId())
		return 0;
	else if (ExpResponse.getDeviceId() != ActResponse.getDeviceId())
		return 0;
	else if (ExpResponse.getLength() != ActResponse.getLength())
		return 0;
	else if (ExpResponse.getCommand() != ActResponse.getCommand())
		return 0;

	uint8_t* ExpData = (uint8_t*)ExpResponse.getBuffer();
	uint8_t* ActData = (uint8_t*)ActResponse.getBuffer();
	for (int i = 0; i < ActResponse.getLength(); i++)
		if (ExpData[i] != ActData[i]) return 0;
	return 1;
}


void RDMTestClass::PrintTestLog()
{
	std::ofstream myFile;
	myFile.open(RDMTestClass::outputFileName);
	myFile << RDMTestClass::testLog;
	myFile.close();
}

uint8_t RDMTestClass::PIDDataType(uint32_t PID)
{
	uint8_t dataType = E120_DS_NOT_DEFINED;
	switch (PID)
	{
		case E120_DEVICE_MODEL_DESCRIPTION:
		case E120_MANUFACTURER_LABEL:
		case E120_DEVICE_LABEL:
		case E120_SOFTWARE_VERSION_LABEL:
			dataType = E120_DS_ASCII;
			break;
		default:
			dataType = E120_DS_UNSIGNED_WORD;
			break;
	}
	return dataType;
}