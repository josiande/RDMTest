// RDMTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include "GadgetDLL.h"
#include "etcpal/timer.h"
#include "RDMTestClass.h"
#include "RDMDevice.h"

int main()
{
    
    int success = 0, timeout = 0, numGadgets = 0, numDiscoveredDevices = 0;
   EtcPalTimer timer;
    std::cout << "RDMTest\n";
    Gadget2_Connect();
    etcpal_timer_start(&timer, 1000);
    do {
        numGadgets = Gadget2_GetNumGadgetDevices();
        timeout = etcpal_timer_is_expired(&timer);
    } while (!numGadgets && !timeout);
    if (timeout)
        std::cout << "could not find any connected Gadget devices";
    else
    {
        std::cout << "Connected Gadget Devices:\n";
        for (int i = 0; i < numGadgets; i++)
            std::cout << Gadget2_GetGadgetSerialNumber(i);
        std::cout << "\n";
        Gadget2_DoFullDiscovery(0, 1);
        etcpal_timer_reset(&timer);
        timeout = 0;
        do {
            numDiscoveredDevices = Gadget2_GetDiscoveredDevices();
            timeout = etcpal_timer_is_expired(&timer);
        } while (!numDiscoveredDevices && !timeout);
        if (numDiscoveredDevices >= 1)
        {
            std::cout << "Discovered RDM Devices:\n";
            RDMTestClass RDMTestObj("testResults.csv");
            for (int i = 0; i < numDiscoveredDevices; i++)
            {

                RdmDeviceInfo* DeviceInfo = Gadget2_GetDeviceInfo(i);
                std::cout << std::setfill('0') << std::setw(4);
                std::cout << std::hex << DeviceInfo->manufacturer_id;
                std::cout << std::setfill('0') << std::setw(8);
                std::cout << DeviceInfo->device_id;
                std::cout << "\n";
                RDMDevice device(i, DeviceInfo->device_model_id, DeviceInfo->manufacturer_id, DeviceInfo->device_id);
                RDMTestObj.TestAllPIDS(device);
                RDMTestObj.PrintTestLog();
            }

        }
        else if (timeout)
            std::cout << "could not discover any devices";
        
    }
        
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
