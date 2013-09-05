// adddevice.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <windows.h>

#include <initguid.h>
#include <setupapi.h>
#include <stdio.h>
#include <usbioctl.h>

DEFINE_GUID(SampleGuid, 0x5665dec0, 0xa40a, 0x11d1, 0xb9, 0x84, 0x0, 0x20, 0xaf, 0xd7, 0x97, 0x70);
// SampleGuid�� ����մϴ�. �̷� GUID�� ���� ��������� ���ǵ��� ���� �����μ�, ���÷� �����Ͽ� ����մϴ�

#define MAXDEVICENUMBER 10 // 10�� ������ ���� Guid�� ����ϴ� ��ġ�� �����Ѵٴ� �ǹ��Դϴ�

#include <winioctl.h>

// �������α׷��� �ְ���� ControlCode�� �����մϴ�
#define IOCTL_BUSDRIVER_ADDDEVICE		CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0800, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_BUSDRIVER_REMOVEDEVICE	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x0801, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_BUSDRIVER_INSERTDATA		CTL_CODE(FILE_DEVICE_UNKNOWN, 0x4000, METHOD_BUFFERED, FILE_ANY_ACCESS)

typedef struct
{
	USB_DEVICE_DESCRIPTOR			 DeviceDescriptor;
    USB_CONFIGURATION_DESCRIPTOR	 ConfigDesc;
	USB_INTERFACE_DESCRIPTOR	     InterfaceDesc;
	USB_ENDPOINT_DESCRIPTOR	         EndpointDescriptor[2];
	CHAR DeviceId[50];
	WCHAR DeviceDesc[20];
	CHAR HwId[40];
	CHAR Service[20];
	CHAR DeviceClass[20];

} USBSENDDEVICEDESC, *PUSBSENDDEVICEDESC;

// ���� �����Ǵ� GUID�� �����ϴ� DeviceStack�� ������ �˷��ݴϴ�
int GetDeviceStackNameCount( struct _GUID * pGuid )
{
	SP_INTERFACE_DEVICE_DATA interfaceData;
	int index=0;
	HDEVINFO Info = SetupDiGetClassDevs( pGuid, 0, 0, DIGCF_PRESENT|DIGCF_INTERFACEDEVICE );

	if( Info == (HDEVINFO) -1 )
		return 0; // �ý����� �̷� ����� �������� ���Ѵ�

	interfaceData.cbSize = sizeof(SP_INTERFACE_DEVICE_DATA);
	
	while( 1 )
	{
		BOOLEAN bl;
		bl = SetupDiEnumDeviceInterfaces( Info, 0, pGuid, index, &interfaceData );
		if( bl == FALSE )
			break;
		index++;
	}

	SetupDiDestroyDeviceInfoList( Info );

	return index;
}

// ���� �����Ǵ� GUID�� �����ϴ� DeviceStack�� �̸����� �˷��ݴϴ�
BOOLEAN GetDeviceStackName( struct _GUID * pGuid, char ** ppDeviceName, int index )
{
	DWORD size;
	BOOLEAN bl;
	SP_INTERFACE_DEVICE_DATA interfaceData;
	PSP_INTERFACE_DEVICE_DETAIL_DATA pData;
	HDEVINFO Info = SetupDiGetClassDevs( pGuid, 0, 0, DIGCF_PRESENT|DIGCF_INTERFACEDEVICE );
	char *pDeviceName;
	*ppDeviceName = (char *)0;

	if( Info == (HANDLE) -1 )
		return FALSE;

	interfaceData.cbSize = sizeof(SP_INTERFACE_DEVICE_DATA);
	
	bl = SetupDiEnumDeviceInterfaces( Info, 0, pGuid, index, &interfaceData );
	if( bl == FALSE )
		return bl;

	SetupDiGetDeviceInterfaceDetail( Info, &interfaceData, 0, 0, &size, 0 );
	pData = (PSP_INTERFACE_DEVICE_DETAIL_DATA)malloc( size );
	pData->cbSize = sizeof(SP_INTERFACE_DEVICE_DETAIL_DATA);
	SetupDiGetDeviceInterfaceDetail( Info, &interfaceData, pData, size, 0, 0 );

	pDeviceName = (char *)malloc( strlen(pData->DevicePath) + 1 );
	memset( pDeviceName, 0, strlen(pData->DevicePath) );
	strcpy( pDeviceName, pData->DevicePath );
	free( pData );

	SetupDiDestroyDeviceInfoList( Info );
	*ppDeviceName = pDeviceName;
	return TRUE;
}

int main(int argc, char* argv[])
{
	HANDLE handle;
	int count;
	char *pDeviceName;
	BOOLEAN bl;
	ULONG ret;
	//WCHAR *pID;
	USBSENDDEVICEDESC sendDescData;

	count = GetDeviceStackNameCount( (struct _GUID *)&SampleGuid );

	if( count == 0 )
		return 0; // �ý����� SampleGuid�� �����ϴ� ��ġ�� ��ġ���� �ʾҽ��ϴ�

	bl = GetDeviceStackName( (struct _GUID *)&SampleGuid, &pDeviceName, 0 ); // �翬�� 1���̻��� ��ġ�� ��ġ�Ǿ������Ƿ�..0�� ����Ѵ�
	// pDeviceName�� �Լ������� �Ҵ�Ǵ� �޸��̹Ƿ�, ����� ������ �ݵ�� �����Ͽ��� �Ѵ�

	if( bl == FALSE )
		return 0; // �̷����� ����� �Ѵ�

	handle = CreateFile( pDeviceName, GENERIC_READ|GENERIC_WRITE
						   , 0, 0, OPEN_ALWAYS, 0
						   , 0 );
	if( handle == (HANDLE)-1 )
	{
		free( pDeviceName );
		return 0; // Stack�� ������, ���� ������ �����Ǿ� �ִ�
	}
	
	// �� �ִ� ��

	//pID = (WCHAR *)calloc( 1, sizeof(CHILDDEVICEDEVICEID)+2 );
	//RtlMoveMemory( pID, CHILDDEVICEDEVICEID, sizeof(CHILDDEVICEDEVICEID) );

	// Ŀ�ο� ȣ���ϱ� ���� ��ũ���� ����
	/*
	// DeviceDescriptor
	sendDescData.DeviceDescriptor.bLength = 0x12;
	sendDescData.DeviceDescriptor.bDescriptorType = 0x01;
	sendDescData.DeviceDescriptor.bcdUSB = 0x0200;
	sendDescData.DeviceDescriptor.bDeviceClass = 0x00;
	sendDescData.DeviceDescriptor.bDeviceSubClass = 0x00;
	sendDescData.DeviceDescriptor.bDeviceProtocol = 0x00;
	sendDescData.DeviceDescriptor.bMaxPacketSize0 = 0x40; // 64
	sendDescData.DeviceDescriptor.idVendor = 0x3538 ;
	sendDescData.DeviceDescriptor.idProduct = 0x0901;
	sendDescData.DeviceDescriptor.bcdDevice = 0x0100;
	sendDescData.DeviceDescriptor.iManufacturer = 0x01;
	sendDescData.DeviceDescriptor.iProduct = 0x02;
	sendDescData.DeviceDescriptor.iSerialNumber = 0x03;
	sendDescData.DeviceDescriptor.bNumConfigurations = 0x01;

	// ConfigurationDescriptor
	sendDescData.ConfigDesc.bLength = 0x09;
	sendDescData.ConfigDesc.bDescriptorType = 0x02;
	sendDescData.ConfigDesc.wTotalLength = 0x0020;
	sendDescData.ConfigDesc.bNumInterfaces = 0x01;
	sendDescData.ConfigDesc.bConfigurationValue = 0x01;
	sendDescData.ConfigDesc.iConfiguration = 0x00;
	sendDescData.ConfigDesc.bmAttributes = 0x80; // BusPowered
	sendDescData.ConfigDesc.MaxPower = 0x32; // 500mA

	// InterfaceDescriptor
	sendDescData.InterfaceDesc.bLength = 0x09;
	sendDescData.InterfaceDesc.bDescriptorType = 0x04;
	sendDescData.InterfaceDesc.bInterfaceNumber = 0x00;
	sendDescData.InterfaceDesc.bAlternateSetting = 0x00;
	sendDescData.InterfaceDesc.bNumEndpoints = 0x02;
	sendDescData.InterfaceDesc.bInterfaceClass = 0x08;
	sendDescData.InterfaceDesc.bInterfaceSubClass = 0x06;
	sendDescData.InterfaceDesc.bInterfaceProtocol = 0x50;
	sendDescData.InterfaceDesc.iInterface = 0x00;

	// EndpointDescriptor
	sendDescData.EndpointDescriptor[0].bLength = 0x07;
	sendDescData.EndpointDescriptor[0].bDescriptorType = 0x05;
	sendDescData.EndpointDescriptor[0].bEndpointAddress = 0x01;
	sendDescData.EndpointDescriptor[0].bmAttributes = 0x02;
	sendDescData.EndpointDescriptor[0].wMaxPacketSize = 0x200; // 512
	sendDescData.EndpointDescriptor[0].bInterval = 0x00;

	sendDescData.EndpointDescriptor[1].bLength = 0x07;
	sendDescData.EndpointDescriptor[1].bDescriptorType = 0x05;
	sendDescData.EndpointDescriptor[1].bEndpointAddress = 0x82;
	sendDescData.EndpointDescriptor[1].bmAttributes = 0x02;
	sendDescData.EndpointDescriptor[1].wMaxPacketSize = 0x200; // 512
	sendDescData.EndpointDescriptor[1].bInterval = 0x00;

	strcpy(sendDescData.DeviceId, "USB\\VID_3538&PID_0901");
	wcscpy(sendDescData.DeviceDesc, L"USB ��뷮 ������ġ");
	strcpy(sendDescData.HwId, "USB\\VID_3538&PID_0901&REV_0100");
	strcpy(sendDescData.Service, "USBSTOR");
	strcpy(sendDescData.DeviceClass, "USB");
	*/
	//DeviceIoControl( handle, IOCTL_BUSDRIVER_INSERTDATA, &(sendDescData.DeviceDescriptor), sizeof(sendDescData.DeviceDescriptor), NULL, 0, &ret, NULL );
	DeviceIoControl( handle, IOCTL_BUSDRIVER_INSERTDATA, &sendDescData, sizeof(sendDescData) + 2, NULL, 0, &ret, NULL );

	DeviceIoControl( handle, IOCTL_BUSDRIVER_ADDDEVICE, NULL, 0, NULL, 0, &ret, NULL );

	CloseHandle( handle );

	free( pDeviceName );
	return 0;
}
