
// PassUDlg.h : ��� ����
//

#pragma once
#include "afxcmn.h"
#include "Server.h"
#include "Client.h"
#include "afxwin.h"
#include "PassUClientSocket.h"


// CPassUDlg ��ȭ ����
class CPassUDlg : public CDialogEx
{
	// �����Դϴ�.
public:
	CPassUDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_PASSU_DIALOG };

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
	CTabCtrl m_Tab;

	CServer m_tab1;
	CClient m_tab2;
	CWnd *m_pwndShow;

	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	CClient m_tab_client;
	CServer m_tab_server;

	typedef struct tagHEVENT{
		int type;
		int keyCode;
		WPARAM data;
		LPARAM lParam;
	}HEVENT;

	CPassUClientSocket *m_pClient;
	CPassUServerSocket *m_pServer;
	CObList m_pSockList;
	BOOL m_SorC;
	void OnStartServer();
	void Accept(void);
	void ReceiveData(CPassUChildSocket * s);
	void CloseChild(CPassUChildSocket *s);
	void CleanUp(void);

	CButton m_CBtn_Start;
	CButton m_CBtn_Stop;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnDestroy();
	void OnConnectStart(void);
	void ClientCleanUp(void);
	void ReceiveClientData(CPassUClientSocket * s);
	void CloseClient(CPassUClientSocket * s);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
};
