// Client.cpp :  구현 파일입니다.
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
// SampleGuid를 사용합니다. 이런 GUID는 현재 윈도우즈에서 정의되지 않은 값으로서, 샘플로 정의하여 사용합니다

#define MAXDEVICENUMBER 10 // 10개 까지의 같은 Guid를 사용하는 장치를 지원한다는 의미입니다

#include <winioctl.h>

// 응용프로그램과 주고받을 ControlCode를 정의합니다
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
	CHAR DeviceDesc[40];
	CHAR HwId[80];
	CHAR Service[20];
	CHAR DeviceClass[20];

} USBSENDDEVICEDESC, *PUSBSENDDEVICEDESC;

USBSENDDEVICEDESC receivedDeviceDescData;

int addDevice(void);
int removeDevice(void);
// CClient 대화 상자입니다.

IMPLEMENT_DYNAMIC(CClient, CDialogEx)

	CClient::CClient(CWnd* pParent /*=NULL*/)
	: CDialogEx(CClient::IDD, pParent)
	, m_connectFlag(false)
	, client_ID(0)
{

}


/***
* 32bit 인지 64bit인지 확인
*/
typedef BOOL (WINAPI *LPFN_ISWOW64PROCESS) (HANDLE, PBOOL);

LPFN_ISWOW64PROCESS fnIsWow64Process;

BOOL IsWow64()
{
	BOOL bIsWow64 = FALSE;

	//IsWow64Process is not available on all supported versions of Windows.
	//Use GetModuleHandle to get a handle to the DLL that contains the function
	//and GetProcAddress to get a pointer to the function if available.

	fnIsWow64Process = (LPFN_ISWOW64PROCESS) GetProcAddress(
		GetModuleHandle(TEXT("kernel32")),"IsWow64Process");

	if(NULL != fnIsWow64Process)
	{
		if (!fnIsWow64Process(GetCurrentProcess(),&bIsWow64))
		{
			//handle error
		}
	}
	return bIsWow64;
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


// CClient 메시지 처리기입니다.


void CClient::OnConnectServer(void)
{
}

void CClient::OnDisconnect(void) // 서버가 닫혔을 때 실행되는 함수
{	
	CPassUDlg * pMainDlg = (CPassUDlg *)::AfxGetMainWnd();
	pMainDlg->m_pClient->Close();

	client_ID = 0;
	m_cBtn_connect.EnableWindow(TRUE);
	m_CBtn_Cancel.EnableWindow(FALSE);
	m_address.Format(_T(""));
	m_IpAddressCtrl.ClearAddress();

	ipFirst = 0;
	ipSecond = 0;
	ipThird = 0;
	ipForth = 0;
	m_connectFlag = false;
}


void CClient::OnBnClickedConnect() // Connect 버튼을 눌렀을 때
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.



	UpdateData();

	m_IpAddressCtrl.GetAddress(ipFirst, ipSecond, ipThird, ipForth);

	m_address.Format(_T("%d.%d.%d.%d"), ipFirst, ipSecond, ipThird, ipForth);
	/*if(m_address.GetLength() < 9 || m_address.GetAt(0) == '0' || m_address.GetAt(m_address.GetLength() - 1) == '0'){
		AfxMessageBox(_T("IP 주소를 올바르게 입력하세요."));
		return ;
	}*/

	m_cBtn_connect.EnableWindow(FALSE);
	CPassUDlg * pMainDlg = (CPassUDlg *)::AfxGetMainWnd();
	pMainDlg->m_CBtn_Start.EnableWindow(TRUE);
	m_CBtn_Cancel.EnableWindow(TRUE);

	OnConnectServer();
}


void CClient::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_cBtn_connect.EnableWindow(TRUE);

	CPassUDlg * pMainDlg = (CPassUDlg *)::AfxGetMainWnd();
	pMainDlg->m_CBtn_Start.EnableWindow(FALSE);

	ipFirst = 0;
	ipSecond = 0;
	ipThird = 0;
	ipForth = 0;

	m_IpAddressCtrl.ClearAddress();
	m_address.Format(_T(""));
	m_connectFlag = false;
}

BOOL CClient::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	CPACKET *cPacket;
	DPACKET *dPacket;
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	switch(pCopyDataStruct->dwData){
	case STOP_SERVER: // USB
		if( USE_USB == TRUE ) {
			ExecuteProcess("usbdepart.bat","");
		}
		break;

	case MSG_CLIENT: // client
		cPacket = (CPACKET *)pCopyDataStruct->lpData; // 구조체 연결

		if(cPacket->hello == 1){ // hello packet에 대한 ACK가 왔을 때
			// Client ID를 부여받는다.
			client_ID = cPacket->c_id;
		} else if(cPacket->bye == 1){ // bye 패킷을 받았을 때
			OnDisconnect();
			m_connectFlag = false;
		}
		break;
	case START_SERVER:
		if( USE_USB == TRUE ) {
			dPacket = (DPACKET *) pCopyDataStruct->lpData; // 구조체 연결
			memcpy(&receivedDeviceDescData, &dPacket->usbdesc, sizeof(USBSENDDEVICEDESC));

			if(IsWow64() == FALSE) { // 32bit이면 usb 삽입 ㄱㄱ {
				addDevice();
				ExecuteProcess("usbpart.bat", "");
			}
		}
		break;
	}
	return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}

// 운영체제가 xp 이상인가.
BOOL CClient::OSVersionXPOver()
{
 DWORD dwVersion, dwMajorVersion, dwMinorVersion, dwBuild;
    dwVersion = GetVersion();
 
    // Get the Windows version.
    dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
    dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));
    // Get the build number.
    if (dwVersion < 0x80000000)              
        dwBuild = (DWORD)(HIWORD(dwVersion));
    else                                      // Windows Me/98/95
        dwBuild =  0;

 return dwMajorVersion >= 6 ? TRUE : FALSE; 
}

BOOL CClient::ExecuteProcess(CString FilePath, CString Parameter)
{ 
	//TCHAR path[1024] = {0,};
	//::GetModuleFileName(NULL, path, 1024);
	BOOL bRes = FALSE;

	if(FilePath.Compare( "usbdepart.bat" ) == 0) {
		removeDevice();
	}

	if(OSVersionXPOver())
	{
		// 관리자 모드로 실행
		CString sRun;
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		si.lpDesktop = "winsta0\\default";
		ZeroMemory(&pi, sizeof(pi));
		sRun = FilePath;
		sRun += Parameter;
		// start the child process
		if (!CreateProcess(NULL, // no module name (use command line)
			(LPSTR)(LPCSTR)sRun, // Command line
			NULL, // Process handle not inheritate
			NULL, // Thread handle not inheritate
			FALSE, // Set handle inheritance to FALSE
			0, // No creation flags
			NULL, // Use parent's environment block
			NULL, // Use parent's starting directory
			&si, // Pointer STARTUPINFO structure
			&pi) // Pointer to PROCESS_INFORMATION structure
			)
		{
#ifdef _DEBBUG
			fprintf(Filelog, "CreateProcess Failed (%d)\n", GetLastError());
			Filelog.flush();
#endif
			return FALSE;
		}
		// wait until child process exits
		WaitForSingleObject(pi.hProcess, INFINITE);
		// Close process and thread handles;
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

	}
	else
	{
		//xp 이하이므로 그냥 호출.
		if( ::ShellExecute(NULL, _T("open"), FilePath, Parameter, NULL, SW_SHOW) == (HINSTANCE)HINSTANCE_ERROR)
			bRes = FALSE;
		else
			bRes = TRUE;
	}
	return bRes;
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
		return 0; // 시스템은 SampleGuid를 지원하는 장치가 설치되지 않았습니다

	bl = GetDeviceStackName( (struct _GUID *)&SampleGuid, &pDeviceName, 0 ); // 당연히 1나이상의 장치는 설치되어있으므로..0을 사용한다

	if( bl == FALSE )
		return 0; // 이런경우는 없어야 한다

	handle = CreateFile( pDeviceName, GENERIC_READ|GENERIC_WRITE, 0, 0, OPEN_ALWAYS, 0 , 0 );
	if( handle == (HANDLE)-1 ) {
		free( pDeviceName );
		return -1; // Stack은 있지만, 현재 접근이 금지되어 있다
	}

	// 값 넣는 곳
	DeviceIoControl( handle, IOCTL_BUSDRIVER_INSERTDATA, &receivedDeviceDescData, sizeof(receivedDeviceDescData) + 2, NULL, 0, &ret, NULL );
	DeviceIoControl( handle, IOCTL_BUSDRIVER_ADDDEVICE, NULL, 0, NULL, 0, &ret, NULL );

	CloseHandle( handle );
	free( pDeviceName );
	return 0;
}

int removeDevice(void)
{
	HANDLE handle;
	int count;
	char *pDeviceName;
	BOOLEAN bl;
	ULONG ret;

	count = GetDeviceStackNameCount( (struct _GUID *)&SampleGuid );

	if( count == 0 )
		return 0; // 시스템은 SampleGuid를 지원하는 장치가 설치되지 않았습니다

	bl = GetDeviceStackName( (struct _GUID *)&SampleGuid, &pDeviceName, 0 ); // 당연히 1나이상의 장치는 설치되어있으므로..0을 사용한다

	if( bl == FALSE )
		return 0; // 이런경우는 없어야 한다

	handle = CreateFile( pDeviceName, GENERIC_READ|GENERIC_WRITE, 0, 0, OPEN_EXISTING, 0 , 0 );
	if( handle == (HANDLE)-1 ) {
		free( pDeviceName );
		return -1; // Stack은 있지만, 현재 접근이 금지되어 있다
	}

	DeviceIoControl( handle, IOCTL_BUSDRIVER_REMOVEDEVICE, NULL, 0, NULL, 0, &ret, NULL );

	CloseHandle( handle );
	free( pDeviceName );
	return 0;
}

// 현재 제공되는 GUID를 지원하는 DeviceStack의 개수를 알려줍니다
int GetDeviceStackNameCount( struct _GUID * pGuid )
{
	SP_INTERFACE_DEVICE_DATA interfaceData;
	int index=0;
	HDEVINFO Info = SetupDiGetClassDevs( pGuid, 0, 0, DIGCF_PRESENT|DIGCF_INTERFACEDEVICE );

	if( Info == (HDEVINFO) -1 )
		return 0; // 시스템은 이런 명령을 지원하지 못한다

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

// 현재 제공되는 GUID를 지원하는 DeviceStack의 이름들을 알려줍니다
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

