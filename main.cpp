#include "hidlibrary.h"
#include <iostream>

using namespace std;

int main(int argc, _TCHAR* argv[])
{
	// ������� ��������� ������ � ����� ����� ���������:
	HIDLibrary<int> hid;

	// �������, �������� ���������� Hid ���������
	// �� ��������������: ������ ��� Hid ���������� vid_16c0&pid_05df
	// vid � pid ������� � hidlibrary.h ���������� idstring
	int n;
	n = hid.EnumerateHIDDevices();

	// ��������� ����������� ����
	if (hid.IsAvailableLib())
	{
		cout << "Lib Is Available :)\n\n";
	}
	else
	{
		cout << "Lib Is not Available :(\n\n";
	}


	// ������� ����� ���� Hid ���������
	for (uint8_t i=0; i<n; i++)
	{
		cout << "Hid " << i + 0 << ".\n";
		cout << "IsItConnected = " << hid.Connect(i) << endl;
		cout << "GetConnectedDevicePath: " << hid.GetConnectedDevicePath() << endl;
		cout << "GetConnectedDeviceName: " << hid.GetConnectedDeviceName() << endl;
		cout << "IsConnectedDevice: " << hid.IsConnectedDevice() << "\n\n";
	}

	cout << n << endl;
	char ch;
	cin >> ch;
	return 0;
}
