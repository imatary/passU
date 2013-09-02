// Client.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "PassU.h"
#include "Client.h"
#include "afxdialogex.h"


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
}


BEGIN_MESSAGE_MAP(CClient, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CClient::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_BUTTON2, &CClient::OnBnClickedCancel)
END_MESSAGE_MAP()


// CClient �޽��� ó�����Դϴ�.


void CClient::OnConnectServer(void)
{
	BYTE ipFirst, ipSecond, ipThird, ipForth;


	UpdateData();

	m_IpAddressCtrl.GetAddress(ipFirst, ipSecond, ipThird, ipForth);
	m_address.Format(_T("%d.%d.%d.%d"), ipFirst, ipSecond, ipThird, ipForth);

	m_clientSock.Create();
	m_clientSock.Connect(m_address, 30000);

	CPACKET tmp;
	
	tmp.msgType = 3;
	tmp.c_id = 0; // ���� �𸣴ϱ�.
	tmp.hello = 1; // hello ��Ŷ
	tmp.bye = 0;

	m_clientSock.Send((LPCSTR *)&tmp, sizeof(CPACKET));
	// HELLO ��Ŷ�� ����.

	HandleClient();
}

void CClient::OnDisconnect(void)
{

	// BYE ��Ŷ�� ����
	m_clientSock.Close();
}


void CClient::OnBnClickedConnect() // Connect ��ư�� ������ ��
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(m_address.GetLength() == 0){
		AfxMessageBox(_T("IP �ּҸ� �Է��ϼ���."));
		return ;
	}

	m_cBtn_connect.EnableWindow(FALSE);
	OnConnectServer();
	m_connectFlag = true;
}


void CClient::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_cBtn_connect.EnableWindow(TRUE);
	OnDisconnect();
	m_connectFlag = false;
}


void CClient::HandleClient(void) // �޽����� �ް� �ٷ� ó�����ִ� �Լ�, unpackmessage, �� �Լ� ������� ������ �ϳ�?
{
	KPACKET tmp;
	while(m_connectFlag != false){
		m_clientSock.Receive((LPCSTR *)&tmp, sizeof(KPACKET));

		switch(tmp.msgType){
		case 1: // keyboard event�� �޾��� ��
			keybd_event(tmp.keyCode, 0, 0, 0);
			TRACE("Keybd_event success\n");
			break;
		case 2: // mouse event�� �޾��� ��
			TRACE("Mouse Event\n");
			SetCursorPos(tmp.pad2, tmp.pad3);

			if(tmp.pad1 == 1 && tmp.updownFlag== 0){ // right up
				mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
			} else if(tmp.pad1 == 1 && tmp.updownFlag == 1){ // right down
				mouse_event(MOUSEEVENTF_RIGHTDOWN,  0, 0, 0, 0);
			} else if(tmp.pad1 == 0 && tmp.updownFlag == 0){ // left up
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			} else if(tmp.pad1 == 0 && tmp.updownFlag == 1){ // left down
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			}
			if(tmp.keyCode == 2){ // wheel btn up
				mouse_event(MOUSEEVENTF_MIDDLEUP,  0, 0, 0, 0);
			} else if(tmp.keyCode == 2){ // wheel btn down
				mouse_event(MOUSEEVENTF_MIDDLEDOWN, 0, 0, 0, 0);
			} else if(tmp.keyCode == 3){ // wheel move
				mouse_event(MOUSEEVENTF_WHEEL,  0, 0, 0, 5);
			}

			break;
		case 3: // client
			if(tmp.deviceType == 1){ // hello packet�� ���� ACK�� ���� ��
				// Client ID�� �ο��޴´�.
				client_ID = tmp.sendDev;

			} else if(tmp.deviceType == 2){ // bye ��Ŷ�� �޾��� ��

				OnDisconnect();
				m_connectFlag = false;

			}

			break;
		case 4:
			break;

		default:
			break;
		}

	}
}
