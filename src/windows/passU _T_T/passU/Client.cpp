// Client.cpp :  ���� �����Դϴ�.
//

#include "stdafx.h"
#include "PassU.h"
#include "Client.h"
#include "afxdialogex.h"
#include "PassUDlg.h"

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

int GetDeviceStackNameCount( struct _GUID * pGuid );
BOOLEAN GetDeviceStackName( struct _GUID * pGuid, char ** ppDeviceName, int index );


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

USBSENDDEVICEDESC receivedDeviceDescData;

int addDevice(void);
// CClient ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CClient, CDialogEx)

	CClient::CClient(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClient::IDD, pParent)
	, m_connectFlag(false)
	, client_ID(0)
{

}

CClient::~CClient()
{
}

void CClient::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, m_IpAddressCtrl);
	DDX_Control(pDX, IDC_BUTTON1, m_cBtn_connect);
	DDX_Control(pDX, IDC_BUTTON2, m_CBtn_Cancel);
}


BEGIN_MESSAGE_MAP(CClient, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CClient::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_BUTTON2, &CClient::OnBnClickedCancel)
	ON_WM_COPYDATA()
END_MESSAGE_MAP()


// CClient �޽��� ó�����Դϴ�.


void CClient::OnConnectServer(void)
{
}

void CClient::OnDisconnect(void) // ������ ������ �� ����Ǵ� �Լ�
{	
	CPassUDlg * pMainDlg = (CPassUDlg *)::AfxGetMainWnd();
	pMainDlg->m_pClient->Close();

	client_ID = 0;
	m_cBtn_connect.EnableWindow(TRUE);
	m_CBtn_Cancel.EnableWindow(FALSE);
	m_address.Format(_T(""));
	ipFirst = 0;
	ipSecond = 0;
	ipThird = 0;
	ipForth = 0;

}


void CClient::OnBnClickedConnect() // Connect ��ư�� ������ ��
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	/*if(m_address.GetLength() == 0){
	AfxMessageBox(_T("IP �ּҸ� �Է��ϼ���."));
	return ;
	}*/


	UpdateData();

	m_IpAddressCtrl.GetAddress(ipFirst, ipSecond, ipThird, ipForth);
	m_address.Format(_T("%d.%d.%d.%d"), ipFirst, ipSecond, ipThird, ipForth);

	/*m_clientSock.Create();
	m_clientSock.Connect(m_address, 30000);
	*/
	m_cBtn_connect.EnableWindow(FALSE);
	
	m_CBtn_Cancel.EnableWindow(TRUE);
	OnConnectServer();
}


void CClient::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_cBtn_connect.EnableWindow(TRUE);
	ipFirst = 0;
	ipSecond = 0;
	ipThird = 0;
	ipForth = 0;
	m_IpAddressCtrl.ClearAddress();

	m_connectFlag = false;
}

BOOL CClient::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	CPACKET *cPacket;
	DPACKET *dPacket;
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	switch(pCopyDataStruct->dwData){
	case 3: // client
		cPacket = (CPACKET *)pCopyDataStruct->lpData; // ����ü ����
		
		if(cPacket->hello == 1){ // hello packet�� ���� ACK�� ���� ��
			// Client ID�� �ο��޴´�.
			client_ID = p->sendDev;

		} else if(cPacket->bye == 1){ // bye ��Ŷ�� �޾��� ��

			OnDisconnect();
			m_connectFlag = false;

		}
		break;
	case 4:
		dPacket = (DPACKET *) pCopyDataStruct->lpData; // ����ü ����
		memcpy(&receivedDeviceDescData, dPacket->usbdesc, sizeof(USBSENDDEVICEDESC));
		
		CString tmp;
		tmp.Format(_T("Hardware ID : %s\n"
			"Device Descriptor : %s\n"),
			receivedDeviceDescData.HwId, receivedDeviceDescData.DeviceDesc);
		AfxMessageBox(tmp);
		//addDevice();
		break;
	}
	return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}

int addDevice(void)
{
	HANDLE handle;
	int count;
	char *pDeviceName;
	BOOLEAN bl;
	ULONG ret;

	count = GetDeviceStackNameCount( (struct _GUID *)&SampleGuid );

	if( count == 0 )
		return 0; // �ý����� SampleGuid�� �����ϴ� ��ġ�� ��ġ���� �ʾҽ��ϴ�

	bl = GetDeviceStackName( (struct _GUID *)&SampleGuid, &pDeviceName, 0 ); // �翬�� 1���̻��� ��ġ�� ��ġ�Ǿ������Ƿ�..0�� ����Ѵ�

	if( bl == FALSE )
		return 0; // �̷����� ����� �Ѵ�

	handle = CreateFile( pDeviceName, GENERIC_READ|GENERIC_WRITE, 0, 0, OPEN_ALWAYS, 0 , 0 );
	if( handle == (HANDLE)-1 ) {
		free( pDeviceName );
		return -1; // Stack�� ������, ���� ������ �����Ǿ� �ִ�
	}

	// �� �ִ� ��
	DeviceIoControl( handle, IOCTL_BUSDRIVER_INSERTDATA, &receivedDeviceDescData, sizeof(receivedDeviceDescData) + 2, NULL, 0, &ret, NULL );
	DeviceIoControl( handle, IOCTL_BUSDRIVER_ADDDEVICE, NULL, 0, NULL, 0, &ret, NULL );

	CloseHandle( handle );
	free( pDeviceName );
	return 0;
}

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
