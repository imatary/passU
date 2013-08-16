
// TestServer.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.
#include "packet.h"

// CTestServerApp:
// �� Ŭ������ ������ ���ؼ��� TestServer.cpp�� �����Ͻʽÿ�.
//
;

class CTestServerApp : public CWinApp
{
public:
	CTestServerApp();
	CSocket server;
	CSocket client;
	BOOL bClientConnected;

	void initServer(int port);
	void sendKeyboardData(KPACKET *packet);
	void sendMouseData(MPACKET *packet);
	void sendMouseMove(int x, int y);
	void sendMouseUp(int x, int y);
	void sendMouseDown(int x, int y);
// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CTestServerApp theApp;