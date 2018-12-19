#include <iostream>
#include "hidapi.h"

using namespace std;

// ��������� ���������
enum
{
	STR_MAX_SIZE = 255,
	BUFFER_MAX_SIZE = 65,
};

int main(int argc, _TCHAR* argv[])
{
    // ������������� ��������
	int res;
	unsigned char buf[BUFFER_MAX_SIZE];
	wchar_t wstr[STR_MAX_SIZE];
	hid_device* handle;
	int i;
	hid_device_info *deviceList, *cur_dev;

	// ������������� ���� hidapi
	if(hid_init())
	{
		cout << "Init error" << endl;
	}

	// ������������ ���� HID ��������� (��������� 0x00 �������� "��� ����������")
	deviceList = hid_enumerate(0x00, 0x00);
	if(deviceList == nullptr)
	{
		cout << "There is no device." << endl;
		return 0;
	}

	// ��������� ������ ���������� ��� ���� �����������:
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
	
	// ������� ���������� � ������� VID � PID, ����������� �������� �����
	vendorId = 1155;
	productId = 22352;
	handle = hid_open(vendorId, productId, NULL);

	// ����� ������ ������   ��� �������� (0 - ������ ������ ���)
	cout << "Error number: "<< hid_error(handle) << endl;

	// ��������� ������ � ���������
	res = hid_read(handle, buf, 4);

	// ������� ������ ����������� ������.
	for (i = 0; i < 4; i++)
		cout << "buf[" << i << "]" << buf[i] << endl;
	cout << endl;

	//// ������ ������ � ����������
	//buf[0] = 0x0;
	//buf[1] = 0x80;
	//res = hid_write(handle, buf, 65);

	// Finalize the hidapi library
	hid_exit();

	// �������� ���������� ������� ����� ��������� �������
	char ch;
	cin >> ch;
	return 0;
}
