
// TestClient.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.
#include "packet.h"


// CTestClientApp:
// �� Ŭ������ ������ ���ؼ��� TestClient.cpp�� �����Ͻʽÿ�.
//

class CTestClientApp : public CWinApp
{
public:
	CTestClientApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CTestClientApp theApp;