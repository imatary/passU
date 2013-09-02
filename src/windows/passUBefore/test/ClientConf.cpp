// ClientConf.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "test.h"
#include "ClientConf.h"
#include "afxdialogex.h"
#include "MyThread.h"

#include <afxsock.h> // sock �Լ� �����ϴ� ���̺귯��


// ClientConf ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(ClientConf, CDialogEx)

	ClientConf::ClientConf(CWnd* pParent /*=NULL*/)
	: CDialogEx(ClientConf::IDD, pParent)
	, m_PortNum(_T(""))
{

	AfxSocketInit();
	clientID = 0;
	m_exitFlag = false;
}

ClientConf::~ClientConf()
{

}

void ClientConf::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ip);
	DDX_Text(pDX, IDC_EDIT1, m_PortNum);
	DDV_MaxChars(pDX, m_PortNum, 5);
	DDX_Control(pDX, IDOK, m_CBtn_ClientConnect);
	DDX_Control(pDX, IDCANCEL, m_CBtn_ClientCancel);
}


BEGIN_MESSAGE_MAP(ClientConf, CDialogEx)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS1, &ClientConf::OnIpnFieldchangedIpaddress)
	ON_BN_CLICKED(IDOK, &ClientConf::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &ClientConf::OnBnClickedCancel)
END_MESSAGE_MAP()


// ClientConf �޽��� ó�����Դϴ�.


void ClientConf::OnIpnFieldchangedIpaddress(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);

	*pResult = 0;
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
}


void ClientConf::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BYTE ipFirst, ipSecond, ipThird, ipForth;


	UpdateData();

	m_ip.GetAddress(ipFirst, ipSecond, ipThird, ipForth);
	m_address.Format(_T("%d.%d.%d.%d"), ipFirst, ipSecond, ipThird, ipForth);

	int nPort;


	nPort = _ttoi(m_PortNum);


	connect(nPort);

	CPACKET c;

	c.msgType =3 ; // hello packet
	c.hello = 1;

	clientSock.Send((LPCSTR *)&c, sizeof(CPACKET)); // hello Packet

}


void ClientConf::receiveData(CClientSocket *s)
{
	KPACKET tmp; // ����ü �ӽ� ����

	s->Receive((LPCSTR *)&tmp, sizeof(KPACKET));

	
	TRACE("msgType : %d\n xCoord : %d, yCoord : %d\n%d, %d, %d", tmp.msgType, tmp.pad2, tmp.pad3, tmp.keyCode, tmp.pad1, tmp.updownFlag);

	unpackMessage(tmp); // �޽��� ����

}

void ClientConf::OnBnClickedCancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CPACKET c;
	c.c_id = clientID;
	c.msgType = 3;
	c.hello = 0;
	c.bye = 1;

	clientSock.Send((LPCSTR *)&c, sizeof(CPACKET)); // ���� ���� ��Ŷ ����


	m_connectFlag = false;
	m_CBtn_ClientConnect.EnableWindow(TRUE);



	CDialogEx::OnCancel();
}

KPACKET ClientConf::packMessage(int msgType, int sendDev, int recvDev, int devType, int relativeField, int updownFlag, int pad1, int keyCode, int pad2, int pad3){
	keyboard.msgType = 0;
	keyboard.sendDev = 0;
	keyboard.recvDev = 0;
	keyboard.deviceType = 0;
	keyboard.relativeField = 0;
	keyboard.updownFlag = 0;
	keyboard.pad1 = 0;
	keyboard.keyCode = 0;
	keyboard.pad2 = 0;
	keyboard.pad3 = 0;

	switch(msgType){
	case 1: // Keyboard
		keyboard.msgType = msgType;
		keyboard.sendDev = sendDev;
		keyboard.recvDev = recvDev;
		keyboard.deviceType = devType;
		keyboard.relativeField = relativeField;
		keyboard.updownFlag = updownFlag;;
		keyboard.pad1 = pad1;
		keyboard.keyCode = keyCode;
		keyboard.pad2 = pad2;
		keyboard.pad3 = pad3;

		break;

	case 2: // Mouse
		mouse.msgType = msgType;
		mouse.sendDev = sendDev;
		mouse.recvDev = recvDev;
		mouse.deviceType = devType;
		mouse.relativeField = relativeField;
		mouse.updownFlag = updownFlag;
		mouse.leftRight = pad1;
		mouse.wheelFlag = keyCode;
		mouse.xCoord = pad2;
		mouse.yCoord = pad3;

		memcpy(&keyboard, &mouse, sizeof(KPACKET));

		break;

	case 3: // Client
		client.msgType = msgType;
		client.c_id = sendDev;
		client.pad3 = recvDev;
		client.hello = devType;
		client.bye = relativeField;
		client.pad4 = updownFlag;
		client.pad5 = pad1;
		client.pad6 = keyCode;
		client.pad7 = pad2;
		client.pad8 = pad3;

		memcpy(&keyboard, &client, sizeof(KPACKET));
		break;

	case 4: // Data Pack
		data.msgType = msgType;
		data.len = sendDev;

		memcpy(&keyboard, &data, sizeof(KPACKET));

		break;
	}
	return keyboard;

}

void ClientConf::unpackMessage(KPACKET p){
	switch(p.msgType){
	case 1: // Keyboard
		TRACE("p.updownFlag : %d\n", p.updownFlag);
		TRACE("keyCode : %d\n", p.keyCode);
		
		//if(p.updownFlag == 1){
		//	keybd_event(p.keyCode, 0, KEYEVENTF_EXTENDEDKEY, 0);
		//} else if(p.updownFlag == 0){
		//	keybd_event(p.keyCode, 0 , KEYEVENTF_KEYUP , 0); // ���޹��� keyCode�� �״�� �Է��Ѵ�.
		//	
		//}
		
		keybd_event(p.keyCode, 0, 0, 0);


		TRACE("keybd_event success\n");
		break;
	case 2: // Mouse
	
		TRACE("Mouse Event\n");
		TRACE("x : %d, y : %d\n", p.pad2, p.pad3);
		SetCursorPos(p.pad2, p.pad3); // ���콺 Ŀ�� �״�� �̵�

		TRACE("p.pad1 : %d, p.updownFlag : %d, p.keyCode = %d", p.pad1, p.updownFlag, p.keyCode);
		if(p.pad1 == 1 && p.updownFlag== 0){ // right up
			mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
		} else if(p.pad1 == 1 && p.updownFlag == 1){ // right down
			mouse_event(MOUSEEVENTF_RIGHTDOWN,  0, 0, 0, 0);
		} else if(p.pad1 == 0 && p.updownFlag == 0){ // left up
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		} else if(p.pad1 == 0 && p.updownFlag == 1){ // left down
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		}
		if(p.keyCode == 2){ // wheel btn up
			mouse_event(MOUSEEVENTF_MIDDLEUP,  0, 0, 0, 0);
		} else if(p.keyCode == 2){ // wheel btn down
			mouse_event(MOUSEEVENTF_MIDDLEDOWN, 0, 0, 0, 0);
		} else if(p.keyCode == 3){ // wheel move
			mouse_event(MOUSEEVENTF_WHEEL,  0, 0, 0, 5);
		}
		
		break;

	case 3: // Client

		if(p.deviceType == 1){ // hello packet�� ���� �亯�� �޾��� ��
			clientID = p.sendDev;
			m_connectFlag = true;
		} else if(p.deviceType == 1){ // bye ��Ŷ�� �޾��� ��
			AfxMessageBox(_T("Server�� �������ϴ�!"));
			clientSock.Close();
			m_connectFlag = false;
		}


	case 4: // Data
		data.msgType = p.msgType;
		data.len = p.sendDev;

	}

	return ;
}


BOOL ClientConf::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	return CDialogEx::PreTranslateMessage(pMsg);
}


void ClientConf::connect(int nPort)
{
	clientSock.Create();

	clientSock.Connect(m_address, nPort);


}


void ClientConf::cleanUp(void)
{

}

void ClientConf::closeSock(void)
{
	clientSock.Close();
}
