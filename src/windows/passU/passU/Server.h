#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CServer ��ȭ �����Դϴ�.

class CServer : public CDialogEx
{
	DECLARE_DYNAMIC(CServer)

public:
	CServer(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CServer();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SERVER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CString serverIPAddress;
	HINSTANCE hinstDLL; // DLL �ε�
	HHOOK hHook; // HHOOK

	BOOL m_keyBoardHook;
	BOOL m_mouseHook;
	CButton m_cBtn_one;
	CButton m_cBtn_two;
	CButton m_cBtn_three;
	CButton m_cBtn_four;
	CButton m_cBtn_server;
	CButton m_cBtn_six;
	CButton m_cBtn_seven;
	CButton m_cBtn_eight;
	CButton m_cBtn_nine;
	CListCtrl m_cListCtrl;
};
