#pragma once

#include <afxsock.h>
#include "MySocket.h"
#include "MyListen.h"
#include "packet.h"
// ServerConf ��ȭ �����Դϴ�.

class ServerConf : public CDialogEx
{
	DECLARE_DYNAMIC(ServerConf)

public:
	ServerConf(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~ServerConf();
	
	int m_deviceFlag; // ������ΰ�, ����Ʈ�� �׸��ΰ��� �Ǻ��ϴ� �÷��� ( -1 : �ʱⰪ, 0 : �����, 1 : ����Ʈ�� )
	int m_settingFlag[9]; // ��ư�� ����� or ����Ʈ�� or �� ĭ���� �Ǻ��ϴ� �÷��� ( -1 : �ʱⰪ, 0 : �����, 1 : ����Ʈ�� )
	bool m_bDragFlag; // �巡�� �Ǻ� �÷���
	bool m_applyFlag; // apply ������ �Ǻ��ϴ� �÷���
	bool m_startFlag; // ���� �������ΰ� �ƴѰ��� �Ǻ��ϴ� �÷���
	
	CPoint m_ptltemText; // Ư�� ������ �ؽ�Ʈ�� ��ǥ
	
	int nSocket; // Ŭ���̾�Ʈ ���� �ϳ��ϳ��� ��ȣ �ο�. ���� : 0����

	//typedef CTypedPtrArray<CObArray, CMySocket *> CSocketList;
	
	HINSTANCE hinstDLL;
	HHOOK hHook;

	BOOL m_keyBoardHook;
	BOOL m_mouseHook;

	CMyListen listen;

	WINDOWPLACEMENT getCoord[11];

	CWnd *btnControl[9];
	CWnd *picControl[2];

	typedef struct tagHEVENT{
		int type;
		int keyCode;
		WPARAM data;
		LPARAM lParam;
	}HEVENT;

	CObList sockList;

	KPACKET keyP;
	MPACKET mouseP;
	CPACKET clientP;
	DPACKET dataP;
	CWnd *pWnd ;
	HWND hWnd;
	bool m_sendFlag;

	CMyThread *currentThread;
	
	virtual BOOL PreTranslateMessage(MSG* pMsg);
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedStop();
	CButton m_CButton_one;
	CButton m_CButton_two;
	CButton m_CButton_three;
	CButton m_CButton_four;
	CButton m_CButton_five;
	CButton m_CButton_six;
	CButton m_CButton_seven;
	CButton m_CButton_eight;
	CButton m_CButton_nine;
	CString m_serverPortEdit;
	afx_msg void OnBnClickedPortApply();
	CButton m_CButton_portApply;
	afx_msg void OnBnClickedPortCancel();
	CButton m_CButton_portCancel;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	CEdit m_portEditControl;
	CString serverIPAddress;
	void initServer(int nPort);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	//afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	void closeClient(CMySocket *s);
	void receiveData(CMySocket *s);
	CButton m_CBtn_Start;
	CButton m_CBtn_stop;
	void initFlag(void);
//	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void sendData(CMySocket * s);
	KPACKET packMessage(int msgType, int sendDev, int recvDev, int devType, int relativeField, int updownFlag, int pad1, int keyCode, int pad2, int pad3);
	KPACKET unpackMessage(KPACKET p);
	//afx_msg BOOL OnCopyData(CWnd *pWnd, COPYDATASTRUCT *pCopyDataStruct);
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
};
