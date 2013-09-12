
// PassUDlg.h : 헤더 파일
//

#pragma once
#include "afxcmn.h"
#include "Server.h"
#include "Client.h"
#include "afxwin.h"
#include "PassUClientSocket.h"


// CPassUDlg 대화 상자
class CPassUDlg : public CDialogEx
{
	// 생성입니다.
public:
	CPassUDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

	// 대화 상자 데이터입니다.
	enum { IDD = IDD_PASSU_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


	// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
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

	// 전체 스크린 구함
	int nWidth;
	int nHeight;
	
	POINT oldPoint;
	POINT currentPoint;

	BOOL m_allowSend; // 클라이언트에 정보를 보낼지 말지를 결정하는 FLAG
	
	void ShowCursorAll();
	void HideCursorAll();
	void DestroyCursorAll();
	
	//dll의 handle
	HWND dllWnd;


	typedef struct tagHEVENT{
		int type;
		int keyCode;
		int updown;
		WPARAM data;
		LPARAM lParam;
	}HEVENT;

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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnDestroy();
	void OnConnectStart(void);
	void ClientCleanUp(void);
	void ReceiveClientData(CPassUClientSocket * s);
	void CloseClient(CPassUClientSocket * s);
	void OnArrivedScreenEdge(MPACKET *packet, BOOL bClient, int position);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnTraymenuOpen();
	afx_msg void OnTraymenuAbout();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTraymenuClose();
};
