
// test.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.

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


	// �������Դϴ�.
public:
	virtual BOOL InitInstance();

	// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CtestApp theApp;