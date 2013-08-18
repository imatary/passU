#pragma once

#include <afxsock.h>
#include "afxwin.h"
#include "MySocket.h"
#include "MyListen.h"
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
//	CAsyncSocket serverSock;
	//CAsyncSocket realSock;
	
	CMySocket realSock;
	CMyListen listen;

	WINDOWPLACEMENT getCoord[11];

	CWnd *btnControl[9];
	CWnd *picControl[2];

	

	//CTrackWnd m_wndTrack;

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
	afx_msg void OnStnClickedPiccom();
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
	void closeClient(void);
	void receiveData(void);
};
