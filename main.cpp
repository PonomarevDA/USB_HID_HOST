//#include "hidlibrary.h"
#include <iostream>
#include "hidapi.h"

using namespace std;

 #define MAX_STR 255

int main(int argc, _TCHAR* argv[])
{
	int res;
	unsigned char buf[65];
	wchar_t wstr[MAX_STR];
	hid_device* handle;
	int i;

	hid_device_info *deviceList, *cur_dev;

	// Initialize the hidapi library
	if(hid_init())
	{
		cout << "Init error" << endl;
	}

	// Enumerate the HID Devices: args = 0 means all devices:
	deviceList = hid_enumerate(0x00, 0x00);
	if(deviceList == nullptr)
	{
		cout << "There is no device" << endl;
		return 0;
	}

	// Get full info about all devices:
	uint16_t vendorId;
	uint16_t productId;
	while(deviceList != nullptr)
	{
		cout << "Interface_number: " << deviceList->interface_number << endl;
		cout << "Path: " << deviceList->path << endl;
		vendorId = deviceList->vendor_id;
		productId = deviceList->product_id;
		cout << "Vendor_id: " << vendorId << endl;
		cout << "Product_id: " << productId << endl;
		cout << "Serial_number: " << deviceList->serial_number << endl;
		cout << "Release_number: " << deviceList->release_number << endl;
		cout << "Nanufacturer_string: " << deviceList->manufacturer_string << endl;
		cout << "Product_string: " << deviceList->product_string << endl;
		cout << "Usage_page: " << deviceList->usage_page << endl;
		cout << "Usage: " << deviceList->usage << endl;
		cout << endl;
		
		deviceList = deviceList->next;
	}
	hid_free_enumeration(deviceList);
	
	// Open the device using the VID, PID,
	// and optionally the Serial number.
	//const wchar_t serialNumber = "01DD42C0\0";
	//handle = hid_open(vendorId, productId, (wchar_t*)"01DE42E0\0");
	handle = hid_open(vendorId, productId, NULL);
	cout << hid_error(handle) << endl;
	res = hid_read(handle, buf, 65);

	// Print out the returned buffer.
	for (i = 0; i < 4; i++)
		printf("buf[%d]: %d\n", i, buf[i]);
	
	/*
	// Read Indexed String 1
	res = hid_get_indexed_string(handle, 1, wstr, MAX_STR);
	wprintf(L"Indexed String 1: %s\n", wstr);

	// Toggle LED (cmd 0x80). The first byte is the report number (0x0).
	buf[0] = 0x0;
	buf[1] = 0x80;
	res = hid_write(handle, buf, 65);

	// Request state (cmd 0x81). The first byte is the report number (0x0).
	buf[0] = 0x0;
	buf[1] = 0x81;
	res = hid_write(handle, buf, 65);

	// Read requested state
	res = hid_read(handle, buf, 65);

	// Print out the returned buffer.
	for (i = 0; i < 4; i++)
		printf("buf[%d]: %d\n", i, buf[i]);

	// Finalize the hidapi library
	res = hid_exit();
	*/

	/*
	// Создаем экземпляр класса с типом нашей структуры:
	HIDLibrary<int> hid;

	// Кажется, получаем количество Hid устройств
	// От первоисточника: узнаем все Hid устройства vid_16c0&pid_05df
	// vid и pid указаны в hidlibrary.h константой idstring
	int n;
	n = hid.EnumerateHIDDevices();

	// Проверяем доступность либы
	if (hid.IsAvailableLib())
	{
		cout << "Lib Is Available :)\n\n";
	}
	else
	{
		cout << "Lib Is not Available :(\n\n";
	}


	// Выводим имена всех Hid устройств
	for (uint8_t i=0; i<n; i++)
	{
		cout << "Hid " << i + 0 << ".\n";
		cout << "IsItConnected = " << hid.Connect(i) << endl;
		cout << "GetConnectedDevicePath: " << hid.GetConnectedDevicePath() << endl;
		cout << "GetConnectedDeviceName: " << hid.GetConnectedDeviceName() << endl;
		cout << "IsConnectedDevice: " << hid.IsConnectedDevice() << "\n\n";
	}
	*/

	hid_exit();
	
	cout << res << endl;
	char ch;
	cin >> ch;
	return 0;
}
