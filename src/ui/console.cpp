
#include "ui/console.h"

#include "dmxrdm/rdm_controller.h"

using namespace std;

static void TimeCallback(void* context, EtcPalLogTimestamp* timestamp)
{
  // Fill in timestamp with the current time...
  time_t now = time(0);
  tm* gmtm = gmtime(&now);
  timestamp->year = gmtm->tm_year + 1900;
  timestamp->month = gmtm->tm_mon + 1;
  timestamp->day = gmtm->tm_mday;
  timestamp->hour = gmtm->tm_hour;
  timestamp->minute = gmtm->tm_min;
  timestamp->second = gmtm->tm_sec;
}

static void LogCallback(void* context, const EtcPalLogStrings* log_strings)
{
  cout << log_strings->human_readable;
}

EtcPalLogParams log_params;

void InitializeConsole()
{
  etcpal_init(ETCPAL_FEATURE_LOGGING);
  log_params = ETCPAL_LOG_PARAMS_INIT;
  log_params.action = ETCPAL_LOG_CREATE_HUMAN_READABLE;
  log_params.log_mask = ETCPAL_LOG_UPTO(ETCPAL_LOG_DEBUG);
  log_params.log_fn = LogCallback;
  log_params.time_fn = TimeCallback;
}

void ServiceConsole()
{
  char input[50];
  char x = ' ';
  cout << "RDMTest>>";
  cin.getline(input, 50);
  ParseInput(input);
}

void LogConsole(int priority, const char* format, ...)
{
  va_list args;
  va_start(args, format);
  etcpal_vlog(&log_params, priority, format, args);
  va_end(args);
}

void ParseInput(char* input_buffer)
{
  if (input_buffer != nullptr)
  {
    string input_str(input_buffer);
    size_t pos = input_str.find(" ");
    string cmd;
    int params[] = {-1, -1, -1, -1};
    if (pos == string::npos)
      cmd = input_str;
    else
    {
      string param;
      int count = 0;
      cmd = input_str.substr(0, pos);
      input_str.erase(0, pos + 1);

      do
      {
        param = input_str.substr(0, pos);
        params[count] = stoi(param);
        count++;
      } while ((pos = input_str.find(" ")) != std::string::npos && count < 4);
    }
    ExecuteCmd(cmd, params[0], params[1], params[2], params[3]);
  }
}

void ExecuteCmd(string cmd, int param1, int param2, int param3, int param4)
{
  RDMController* my_controller = GetRDMControllerInstance();
  if (cmd.compare("exit") == 0)
  {
    LogConsole(ETCPAL_LOG_INFO, "exit the program");
  }
  else if (cmd.compare("device") == 0)
  {
    RDMDevice* my_device = my_controller->GetConnectedDevice(param1);
    LogConsole(ETCPAL_LOG_INFO, "\r\nconnected device: %04X%08X\r\nport number: %d\r\n",
               my_device->device_info_.manufacturer_id, my_device->device_info_.device_id,
               my_device->device_info_.port_number);
  }
  else if (cmd.compare("discover") == 0)
  {
    my_controller->Discover();
  }
  else if (cmd.compare("help") == 0)
  {
    LogConsole(
        ETCPAL_LOG_INFO,
        "\r\n::::console commands::::\r\nexit: close the console program\r\ndevices: print the connected devices\r\n");

  }
}


