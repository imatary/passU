
// passUTestServer.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CpassUTestServerApp:
// �� Ŭ������ ������ ���ؼ��� passUTestServer.cpp�� �����Ͻʽÿ�.
//

class CpassUTestServerApp : public CWinApp
{
public:
	CpassUTestServerApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CpassUTestServerApp theApp;