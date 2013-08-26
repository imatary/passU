
// testDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "USBIconDlg.h"

// CtestDlg ��ȭ ����
class CtestDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CtestDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TEST_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedServerConfiguration();
	afx_msg void OnBnClickedClientConfiguration();
	afx_msg void OnBnClickedServerRadio();
	afx_msg void OnBnClickedClientRadio();
	afx_msg void OnBnClickedExitButton();
	CButton CButton_clientconfiguration;
	CButton CButton_ServerConfig;
	bool CRadioButton_Server;
	bool CRadioButton_Client;
	CUSBIconDlg *usbIcon;
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
};
