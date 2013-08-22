
// TestServer.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "TestServer.h"
#include "TestServerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestServerApp

BEGIN_MESSAGE_MAP(CTestServerApp, CWinApp)
	//ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CTestServerApp ����

CTestServerApp::CTestServerApp()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CTestServerApp ��ü�Դϴ�.

CTestServerApp theApp;


// CTestServerApp �ʱ�ȭ

BOOL CTestServerApp::InitInstance()
{
	CWinApp::InitInstance();

	bClientConnected = FALSE;

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}



	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ
	// ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));

	CTestServerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ���⿡ [Ȯ��]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ���⿡ [���]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "���: ��ȭ ���ڸ� ������ �������Ƿ� ���� ���α׷��� ����ġ �ʰ� ����˴ϴ�.\n");
	}

	// ��ȭ ���ڰ� �������Ƿ� ���� ���α׷��� �޽��� ������ �������� �ʰ�  ���� ���α׷��� ���� �� �ֵ��� FALSE��
	// ��ȯ�մϴ�.
	return FALSE;
}

void CTestServerApp::initServer(int port)
{
	if(!server.Create(port))  
	{            
		AfxMessageBox(_T("Socket Create Failed\n"));
		return;
	}

	if(!server.Listen())                                          //����
	{            
		AfxMessageBox(_T("Socket Listen Failed\n"));
		return;        
	}

	if(!server.Accept(client))      //Ŭ���̾�Ʈ ���� ��ٸ� (���ӵɶ��������!!)
	{          
		AfxMessageBox(_T("Socket Accept Failed\n"));
		return;
	}

	MPACKET packet;
	packet.sendDev = 5;
	packet.recvDev = 6;
	packet.deviceType = 1;
	packet.relativeField = 0;
	packet.updownFlag = -1;
	packet.wheelFlag = 0;
	packet.xCoord = 100;
	packet.yCoord = 200;

	sendMouseData(&packet);
	bClientConnected = TRUE;
	bMouseDown = FALSE;
}

void CTestServerApp::sendMouseMove(int x, int y)
{
	if(bClientConnected) {
		MPACKET packet;
		packet.sendDev = 5;
		packet.recvDev = 6;
		packet.deviceType = 1;
		packet.relativeField = 0;
		packet.updownFlag = (bMouseDown == TRUE)?0:1;
		packet.wheelFlag = 0;
		packet.xCoord = x;
		packet.yCoord = y;

		sendMouseData(&packet);
	}
}

void CTestServerApp::sendMouseDown(int x, int y)
{
	if(bClientConnected) {
		bMouseDown = TRUE;
		MPACKET packet;
		packet.sendDev = 5;
		packet.recvDev = 6;
		packet.deviceType = 1;
		packet.relativeField = 0;
		packet.updownFlag = (bMouseDown == TRUE)?0:1;
		packet.wheelFlag = 0;
		packet.xCoord = x;
		packet.yCoord = y;

		sendMouseData(&packet);
	}
}


void CTestServerApp::sendMouseUp(int x, int y)
{
	if(bClientConnected) {
		bMouseDown = FALSE;
		MPACKET packet;
		packet.sendDev = 5;
		packet.recvDev = 6;
		packet.deviceType = 1;
		packet.relativeField = 0;
		packet.updownFlag = (bMouseDown == TRUE)?0:1;
		packet.wheelFlag = 0;
		packet.xCoord = x;
		packet.yCoord = y;

		sendMouseData(&packet);
	}
}


void CTestServerApp::sendMouseData(MPACKET *pPacket)
{
	char buf2[100];

	sprintf_s(buf2, "%4d%4d%1d%1d%1d%1d%4d%4d%4d", pPacket->sendDev, pPacket->recvDev, pPacket->deviceType, 
		pPacket->relativeField, pPacket->updownFlag,
		pPacket->wheelFlag, pPacket->xCoord, pPacket->yCoord, 0);
	MPACKET buf;
	if(bClientConnected) {
		int bytes = client.Send((void*)buf2, sizeof(MPACKET));    //����������

		CString str;
		str.Format(_T("real[%d] want[%d]"), bytes, sizeof(MPACKET));

		ZeroMemory(&buf, sizeof(MPACKET));
		bytes = client.Receive((void*)&buf, sizeof(MPACKET)); 
	}
}

void CTestServerApp::sendKeyDown(UINT keyCode)
{
	if(bClientConnected) {
		bKeyDown = TRUE;
		KPACKET packet;
		packet.sendDev = 5;
		packet.recvDev = 6;
		packet.deviceType = 0;
		packet.relativeField = 0;
		packet.updownFlag = (bKeyDown == TRUE)?0:1;
		packet.keyCode = keyCode;

		sendKeyData(&packet);
	}
}


void CTestServerApp::sendKeyUp(UINT keyCode)
{
	if(bClientConnected) {
		bKeyDown = FALSE;
		KPACKET packet;
		packet.sendDev = 5;
		packet.recvDev = 6;
		packet.deviceType = 0;
		packet.relativeField = 0;
		packet.updownFlag = (bKeyDown == TRUE)?0:1;
		packet.keyCode = keyCode;

		sendKeyData(&packet);
	}
}


void CTestServerApp::sendKeyData(KPACKET *pPacket)
{
	char buf2[100];

	sprintf_s(buf2, "%4d%4d%1d%1d%1d%4d%9d", pPacket->sendDev, pPacket->recvDev, pPacket->deviceType, 
		pPacket->relativeField, pPacket->updownFlag,
		pPacket->keyCode, 0);
	KPACKET buf;
	if(bClientConnected) {
		int bytes = client.Send((void*)buf2, sizeof(KPACKET));    //����������

		CString str;
		str.Format(_T("real[%d] want[%d]"), bytes, sizeof(KPACKET));

		ZeroMemory(&buf, sizeof(KPACKET));
		bytes = client.Receive((void*)&buf, sizeof(KPACKET));
	}
}