
// PassUDlg.h : ��� ����
//

#pragma once
#include "afxcmn.h"
#include "Server.h"
#include "Client.h"
#include "afxwin.h"
#include "PassUClientSocket.h"
#include "PassUTransparentDlg.h"


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
	int whereisPoint;
	CServer m_tab1;
	CClient m_tab2;
	CWnd *m_pwndShow;

	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	CClient m_tab_client;
	CServer m_tab_server;
	CPassUTransparentDlg *tdlg;
	BOOL tdlgIsCreated;
	// ��ü ��ũ�� ����
	int nWidth;
	int nHeight;

	BOOL m_allowSend; // Ŭ���̾�Ʈ�� ������ ������ ������ �����ϴ� FLAG
	BOOL bWait;
	void ShowCursorAll();
	void HideCursorAll();
	void DestroyCursorAll();
	
	// Ŀ�� �̹��� ���� Flag
	BOOL CursorFlag;
	BOOL isCursorShow;
    // Ÿ�̸� ������ ���� ����
    UINT htimer;
	CTime cT; 

	//dll�� handle
	HWND dllWnd;

	typedef struct tagHEVENT{
		int type;
		int keyCode;
		int updown;
		WPARAM data;
		LPARAM lParam;
	} HEVENT;

	CPassUClientSocket *m_pClient;
	CPassUServerSocket *m_pServer;
	CObList m_pSockList;
	BOOL m_SorC;
	BOOL USBDeviceChange(UINT uEvent, DWORD dwEventData);
	void OnStartServer();
	void Accept(void);
	void ReceiveData(CPassUChildSocket * s);
	int ParseData(char *buf, int len);
	int ParseKeyboardData(char *buf, KPACKET *packet);
	int ParseMouseData(char *buf, MPACKET *packet);
	int ParseClientData(char *buf, CPACKET *packet);

	int byteToint(char *data, int len);
	void CloseChild(CPassUChildSocket *s);
	void CleanUp(void);

	CButton m_CBtn_Start;
	CButton m_CBtn_Stop;
	afx_msg LRESULT OnTrayNotification(WPARAM wParam, LPARAM lParam);
	afx_msg void OnDestroy();
	void OnConnectStart(void);
	void ClientCleanUp(void);
	void ReceiveClientData(CPassUClientSocket * s);
	void CloseClient(CPassUClientSocket * s);
	afx_msg LRESULT OnArrivedScreenEdge(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnTraymenuOpen();
	afx_msg void OnTraymenuAbout();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTraymenuClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedStop();
//	afx_msg void OnRawInput(UINT nInputcode, HRAWINPUT hRawInput);
};
