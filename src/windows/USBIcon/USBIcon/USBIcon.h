
// USBIcon.h : PROJECT_NAME ���� ���α׷��� ���� �� ��� �����Դϴ�.
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"		// �� ��ȣ�Դϴ�.


// CUSBIconApp:
// �� Ŭ������ ������ ���ؼ��� USBIcon.cpp�� �����Ͻʽÿ�.
//

class CUSBIconApp : public CWinApp
{
public:
	CUSBIconApp();

// �������Դϴ�.
public:
	virtual BOOL InitInstance();

// �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};

extern CUSBIconApp theApp;