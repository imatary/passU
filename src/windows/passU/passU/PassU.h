
// PassU.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CPassUApp:
// �� Ŭ������ ������ ���ؼ��� PassU.cpp�� �����Ͻʽÿ�.
//

class CPassUApp : public CWinApp
{
public:
	CPassUApp();
	static int m_screen_width;
	static int m_screen_height;

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CPassUApp theApp;