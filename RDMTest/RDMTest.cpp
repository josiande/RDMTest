// RDMTest.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <iostream>
#include "GadgetDLL.h"
#include "etcpal/timer.h"
#include "RDMTestClass.h"

int main()
{
    
    int success = 0, timeout = 0;
   EtcPalTimer timer;
    std::cout << "RDMTest\n";
    Gadget2_Connect();
    etcpal_timer_start(&timer, 1000);
    do {
        success = Gadget2_GetNumGadgetDevices();
        timeout = etcpal_timer_is_expired(&timer);
    } while (!success && !timeout);
    if (timeout)
        std::cout << "could not find any connected Gadget II devices";
    else
    {
        Gadget2_DoFullDiscovery(0, 1);
        Sleep(1000);
        if (Gadget2_GetDiscoveredDevices() >= 1)
        {
            RDMTestClass RDMTestObj;
            RdmDeviceInfo* DeviceInfo = Gadget2_GetDeviceInfo(0);
            RDMTestObj.TestAllPIDS(DeviceInfo->manufacturer_id, DeviceInfo->device_id);
        }
        
        
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
