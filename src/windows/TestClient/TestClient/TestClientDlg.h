
// TestClientDlg.h : ��� ����
//

#pragma once


// CTestClientDlg ��ȭ ����
class CTestClientDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CTestClientDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

	CSocket socket;
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TESTCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedConnect();
	afx_msg void OnClose();
};
