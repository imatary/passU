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
	ON_WM_COPYDATA()
END_MESSAGE_MAP()


// CClient �޽��� ó�����Դϴ�.


void CClient::OnConnectServer(void)
{
}

void CClient::OnDisconnect(void)
{
	//CPACKET tmp;

	//tmp.msgType = 3;
	//tmp.c_id = client_ID;

	//m_clientSock.Send((LPCSTR *)&tmp, sizeof(CPACKET));
	//// BYE ��Ŷ�� ����
	//m_clientSock.Close();
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
	OnConnectServer();
}


void CClient::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_cBtn_connect.EnableWindow(TRUE);

	m_connectFlag = false;
}

BOOL CClient::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	switch(pCopyDataStruct->dwData){

	case 0: // receiveData
		p = (PACKET *) pCopyDataStruct->lpData; // ����ü ����
		switch(p->msgType){
		case 1: // keyboard event�� �޾��� ��
			keybd_event(p->keyCode, 0, 0, 0);
			TRACE("Keybd_event success\n");
			break;
		case 2: // mouse event�� �޾��� ��
			TRACE("Mouse Event\n");
			SetCursorPos(p->pad2, p->pad3);

			if(p->pad1 == 1 && p->updownFlag== 0){ // right up
				mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
			} else if(p->pad1 == 1 && p->updownFlag == 1){ // right down
				mouse_event(MOUSEEVENTF_RIGHTDOWN,  0, 0, 0, 0);
			} else if(p->pad1 == 0 && p->updownFlag == 0){ // left up
				mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
			} else if(p->pad1 == 0 && p->updownFlag == 1){ // left down
				mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			}
			if(p->keyCode == 2){ // wheel btn up
				mouse_event(MOUSEEVENTF_MIDDLEUP,  0, 0, 0, 0);
			} else if(p->keyCode == 2){ // wheel btn down
				mouse_event(MOUSEEVENTF_MIDDLEDOWN, 0, 0, 0, 0);
			} else if(p->keyCode == 3){ // wheel move
				mouse_event(MOUSEEVENTF_WHEEL,  0, 0, 0, 5);
			}

			break;
		case 3: // client
			if(p->deviceType == 1){ // hello packet�� ���� ACK�� ���� ��
				// Client ID�� �ο��޴´�.
				client_ID = p->sendDev;

			} else if(p->deviceType == 2){ // bye ��Ŷ�� �޾��� ��

				OnDisconnect();
				m_connectFlag = false;

			}

			break;
		case 4:
			break;

		default:
			break;
		}

		break;

	}
	return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}
