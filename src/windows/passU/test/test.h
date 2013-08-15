
// test.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.
#include "ServerSocket.h"
#include "ClientSocket.h"
#include "ServerChildSocket.h"


// CtestApp:
// �� Ŭ������ ������ ���ؼ��� test.cpp�� �����Ͻʽÿ�.
//

class CtestApp : public CWinApp
{
public:
	CtestApp();
	int flag;
	CString m_ipAddress;
	CString m_portNum;

	CSocket *m_serverSock;
	CSocket *m_serverRecvSock;

	ServerSocket *m_pServer;
	ServerChildSocket *m_pChild;
	ClientSocket *m_pClient;
	
	void initServer(UINT nPort);
	void cleanUp(void);
	void sendData(CString strData);
	void receiveData(void);
	void accept(void);
	void closeChild(void);
	
	void clientConnect(void);
	void clientCleanUp(void);
	void clientSendData(CString strData);
	void clientReceiveData(void);
	void clientcloseChild(void);

	// �������Դϴ�.
public:
	virtual BOOL InitInstance();

	// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CtestApp theApp;