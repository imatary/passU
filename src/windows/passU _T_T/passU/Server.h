#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "PassUServerSocket.h"
#include "PassUChildSocket.h"
#include "packet.h"
#include "ClientInfo.h"

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
	CString strIpAddress;
	CButton m_cBtn[9];

	CClientInfo clientInfo[9]; // ������ index�� client ID
	
	// Ŭ���̾�Ʈ�� ��ũ�� ũ�ⱸ��, ������ index�� client ID
	int client_nWidth[9];
	int client_nHeight[9];

	HWND dllWnd;

	BOOL m_keyBoardHook;
	BOOL m_mouseHook;
	BOOL m_bDrag;          

	int m_nOldTarget;   
	int m_nSource;      
	// for listctrl

	CImageList m_imgList;
	CListCtrl m_waiting_client;
	CImageList *m_pDragImage;
	CObList m_pSockList;

	//LBUTTONDOWN ���� �� ���� Device���� �÷���
	BOOL m_deviceFlag; // -1 : Nothing // 0 : Computer // 1 : Android
	// LBUtton UP ���� �� ��ư�� �׸� �׷��ֱ�
	WINDOWPLACEMENT getCoord[9];
	CWnd *btnControl[9];

	static int STATUS_IDLE;
	static int STATUS_ON_FOR_SERVER;
	static int STATUS_ON_FOR_CLIENT;
	static int STATUS_OFF;

	int m_status;
	int m_x;
	int m_y;

	typedef struct tagHEVENT{
		int type;
		int keyCode;
		int updown;
		WPARAM data;
		LPARAM lParam;
	}HEVENT;

	//Button�� Ŭ���̾�Ʈ�� Binding�ϴ� �迭
	int btn_Bind[9]; // ������ index�� ��ư ��ȣ, �� ���� ���� ClientID

	// bmp load
	CBitmap m_bmp_monitor;
	CBitmap m_bmp_phone;

	void OnChangeLocationInfo(int index);
	void bindWatingClient(int btn_index, int client_index);
	void OnDisconnectedClient(int client_index);
	
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	virtual BOOL OnInitDialog();
	afx_msg void OnLvnBegindragList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	int GetHitIndex(CPoint);
	void MoveListItem(const INT _nSource, const INT _nDest);
	void OnButtonClick(int position);

	afx_msg void OnDestroy();
};
