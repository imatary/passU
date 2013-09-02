// Server.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "PassU.h"
#include "Server.h"
#include "afxdialogex.h"


// ��ŷ�� ���� �Լ� ������
typedef HHOOK (*InstallKeyboardHook)();
typedef HHOOK (*InstallMouseHook)();

typedef void (*UnInstallKeyboardHook)();
typedef void  (*UnInstallMouseHook)();

InstallKeyboardHook installKeyhook;
InstallMouseHook installMousehook;

UnInstallKeyboardHook uninstallKeyhook;
UnInstallMouseHook uninstallMousehook;


// CServer ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CServer, CDialogEx)

	CServer::CServer(CWnd* pParent /*=NULL*/)
	: CDialogEx(CServer::IDD, pParent)
	, serverIPAddress(_T(""))
{
	TRACE("CServer Init\n");

	/* ���� ������ �� ��ǻ���� IP�� �˾Ƴ��� �ڵ� */
	WORD wVersionRequested;
	WSADATA wsaData;
	char name[255];
	PHOSTENT hostinfo;
	CString strIpAddress;
	wVersionRequested = MAKEWORD(2, 0);
	if(WSAStartup(wVersionRequested, &wsaData) == 0)
	{
		if(gethostname(name, sizeof(name)) == 0)
		{
			if((hostinfo = gethostbyname(name)) != NULL)
				strIpAddress = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
		} 
		WSACleanup();
	}

	serverIPAddress.Append(strIpAddress);


	hinstDLL = LoadLibrary(_T("KeyHook.dll"));
	if(!hinstDLL)
		AfxMessageBox(_T("KeyHook.dll �ε� ����!"));

	installKeyhook = (InstallKeyboardHook)GetProcAddress(hinstDLL, "InstallKeyboardHook");
	installMousehook = (InstallMouseHook)GetProcAddress(hinstDLL, "InstallMouseHook");

	uninstallKeyhook = (UnInstallKeyboardHook)GetProcAddress(hinstDLL, "UnInstallKeyboardHook");
	uninstallMousehook = (UnInstallMouseHook)GetProcAddress(hinstDLL, "UnInstallMouseHook");


	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return ;
	}
	CBitmap bitmap;

	bitmap.LoadBitmapA(IDB_BITMAP2);
	m_imgList.Create(15, 15, ILC_COLOR8, 1, 1);
	m_imgList.Add(&bitmap, RGB(255, 0, 255));
	m_wating_client.SetImageList(&m_imgList, LVSIL_SMALL);
	m_wating_client.InsertItem(0, "tmp", 0);

}

CServer::~CServer()
{
}

void CServer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_IPADDRESS, serverIPAddress);
	DDX_Control(pDX, IDC_BUTTON1, m_location_info[0]);
	DDX_Control(pDX, IDC_BUTTON2, m_location_info[1]);
	DDX_Control(pDX, IDC_BUTTON3, m_location_info[2]);
	DDX_Control(pDX, IDC_BUTTON4, m_location_info[3]);
	DDX_Control(pDX, IDC_BUTTON5, m_location_info[4]);
	DDX_Control(pDX, IDC_BUTTON6, m_location_info[5]);
	DDX_Control(pDX, IDC_BUTTON7, m_location_info[6]);
	DDX_Control(pDX, IDC_BUTTON8, m_location_info[7]);
	DDX_Control(pDX, IDC_BUTTON9, m_location_info[8]);
	DDX_Control(pDX, IDC_LIST1, m_wating_client);
	DDX_Control(pDX, IDC_BUTTON10, m_CBtn_ServerStart);
}


BEGIN_MESSAGE_MAP(CServer, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON10, &CServer::OnBnClickedServerStart)
	ON_BN_CLICKED(IDC_BUTTON11, &CServer::OnBnClickedServerStop)
	ON_BN_CLICKED(IDC_BUTTON1, &CServer::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CServer::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CServer::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CServer::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &CServer::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CServer::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CServer::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CServer::OnBnClickedButton9)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_COPYDATA()
END_MESSAGE_MAP()


// CServer �޽��� ó�����Դϴ�.


void CServer::OnStartServer()
{
	listen.Create(30000);
	listen.Listen();

	AfxMessageBox(_T("InitServer"));
}


void CServer::OnChangeLocationInfo(int index)
{

}


void CServer::bindWatingClient(int client_index)
{

}


void CServer::OnDisconnectedClient(int client_index)
{
	POSITION pos = listen.m_sockList.GetHeadPosition();

	CPACKET tmp;
	tmp.msgType = 3;
	tmp.c_id = client_index;
	tmp.hello = 0;
	tmp.bye = 1;

	// ���� ����Ʈ���� client_index��ŭ �����ͼ� �� �������� ����
	int cindex = client_index;

	while(cindex != 0){
		listen.m_sockList.GetNext(pos);
		cindex -= 1;
	}

	cThread = (CPassUServerThread *)listen.m_sockList.GetAt(pos);

	cThread->m_passUSocket->Send((LPCSTR *)&tmp, sizeof(CPACKET)); // BYE ��Ŷ ����

	//socket list���� ����
	listen.m_sockList.RemoveAt(pos);

}


void CServer::OnArrivedScreenEdge(int position)
{

}


void CServer::OnBnClickedServerStart()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_CBtn_ServerStart.EnableWindow(FALSE);
	OnStartServer();
}


void CServer::OnBnClickedServerStop()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	m_CBtn_ServerStart.EnableWindow(TRUE);

}


void CServer::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

}


void CServer::OnBnClickedButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CServer::OnBnClickedButton3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CServer::OnBnClickedButton4()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CServer::OnBnClickedButton6()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CServer::OnBnClickedButton7()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CServer::OnBnClickedButton8()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CServer::OnBnClickedButton9()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CServer::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CServer::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CServer::ReceiveData(CPassUServerSocket * s)
{
	KPACKET tmp;
	s->Receive(&tmp, sizeof(KPACKET));
	COPYDATASTRUCT CDS;

	CDS.dwData = 0; // receiveData
	CDS.cbData = sizeof(KPACKET);
	CDS.lpData = &tmp;
	SendMessage(WM_COPYDATA, 0, (LPARAM)(VOID *)&CDS);
}


BOOL CServer::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	POSITION pos = listen.m_sockList.GetHeadPosition();

	switch(pCopyDataStruct->dwData){
	case 0: // receiveData
		k = (KPACKET *) pCopyDataStruct->lpData; // ����ü ����

		switch(k->msgType){
		case 1: // keyboard
			break;

		case 2: // mouse
			break;


		case 3: // client
			if(k->deviceType == 1){ // hello packet
				// ��� ��Ŷ�̸�
				// ��ư�� Ŭ���̾�Ʈ �������ְ�, ù��° Ŭ���̾�Ʈ�� ��ŷ �����ϰ�
				// Ŭ���̾�Ʈ�� �ڽ��� id �˷��ְ�
				// ����Ʈ ��Ʈ�ѿ� ������ �ϳ� �߰�
				CBitmap bitmap;

				bitmap.LoadBitmapA(IDB_BITMAP2);
				m_imgList.Create(15, 15, ILC_COLOR8, 1, 1);
				m_imgList.Add(&bitmap, RGB(255, 0, 255));
				m_wating_client.SetImageList(&m_imgList, LVSIL_SMALL);

				m_wating_client.InsertItem(0, "tmp", 0);



				cThread = (CPassUServerThread *)listen.m_sockList.GetAt(pos);




			} else if(k->relativeField == 1){ // bye packet
				// �¹�����Ŷ�̸�
				// ��ư�� Ŭ���̾�Ʈ ����


				OnDisconnectedClient(k->sendDev); // Ŭ���̾�Ʈ ��Ŀ��Ʈ
			}
			break;

		case 4:

			break;

		}

		break;
	}
	return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}
