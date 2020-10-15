#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

#include "RDMTestClass.h"
#include "etcpal/timer.h"

RDMTestClass::RDMTestClass(std::string outputFileName) 
{
	RDMTestClass::outputFileName = outputFileName;
	RDMTestClass::testLog = "";
}

int RDMTestClass::TestAllPIDS(uint16_t ManfID, uint32_t DeviceID)
{
	testLog += "Parameter Name,PID,Get/Set,Data,ManfID,DeviceID,Transaction #,Response Type,Message Count,Command Class,PID,Length,Data,\n";
	TestDeviceInfo(ManfID, DeviceID);
	return 0;
}

int RDMTestClass::TestDeviceInfo(uint16_t ManfID, uint32_t DeviceID)
{
	RDM_CmdC ExpResponse(E120_GET_COMMAND_RESPONSE, E120_DEVICE_INFO, 0, 0, nullptr, ManfID, DeviceID);
	PIDTest("DEVICE_INFO", ManfID, DeviceID, E120_DEVICE_INFO, E120_GET_COMMAND, 0, nullptr, ExpResponse);
	std::cout << testLog;
	return 0;
}

std::string RDMTestClass::ResponseToStringHelper(std::string ParamName, uint32_t PID, uint8_t Cmd, uint8_t* Data, uint8_t DataSize, RDM_CmdC Response)
{
	std::string outputString = "";
	std::string dataString = "";
	uint8_t returnData;
	outputString += ParamName + ",";
	outputString += "0x" + IntToHexString(PID, 2) + ",";
	outputString += "0x" + IntToHexString(Cmd, 1) + ",";
	if (Data != nullptr)
		dataString.assign((char*)Data, DataSize);
	outputString += dataString + ",";
	outputString += "0x" + IntToHexString(Response.getManufacturerId(), 2) + ",";
	outputString += "0x" + IntToHexString(Response.getDeviceId(), 4) + ",";
	outputString += "0x" + IntToHexString(Response.getTransactionNum(), 1) + ",";
	outputString += "0x" + IntToHexString(Response.getResponseType(), 1) + ",";
	outputString += "0x" + IntToHexString(Response.getMessageCount(), 1) + ",";
	outputString += "0x" + IntToHexString(Response.getCommand(), 1) + ",";
	outputString += "0x" + IntToHexString(Response.getParameter(), 2) + ",";
	outputString += "0x" + IntToHexString(Response.getLength(), 1) + ",";
	outputString += "0x" + BufferToHexString((uint8_t *)Response.getBuffer(), Response.getLength()) + ",";

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
	stream	<< std::setfill('0') << std::setw((uint64_t)numBytes * 2)
			<< std::hex << x;
	return stream.str();
}

int RDMTestClass::PIDTest(std::string ParamName, uint16_t ManfID, uint32_t DeviceID, uint32_t PID, uint8_t Cmd, uint8_t DataLength, uint8_t* Data, RDM_CmdC ExpResponse)
{
	int responseTime = 0, timeout = 0, success = 0;
	EtcPalTimer timer;
	RDM_CmdC* response = nullptr;

	Gadget2_SendRDMCommand(0, 1, E120_GET_COMMAND, E120_DEVICE_INFO, 0, 0, nullptr, ManfID, DeviceID);
	etcpal_timer_start(&timer, 1000);
	do {
		response = Gadget2_GetResponse(0);
		timeout = etcpal_timer_is_expired(&timer);
	} while (response == nullptr && !timeout);
	std::cout << std::dec << etcpal_timer_elapsed(&timer) << "\n";
	if (response == nullptr)
	{
		std::cout << "No response.\n";
	}
	else
	{
		success = CompareResponseHelper(ExpResponse, *response);
		RDMTestClass::testLog += ResponseToStringHelper(ParamName, PID, Cmd, Data, DataLength, *response);
	}
	Gadget2_ClearResponse(0);

	return success;
}

int RDMTestClass::CompareResponseHelper(RDM_CmdC ExpResponse, RDM_CmdC ActResponse)
{
	if (ExpResponse.isValid() != ActResponse.isValid())
		return -1;
	else if (ExpResponse.getTransactionNum() != ActResponse.getTransactionNum())
		return -1;
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