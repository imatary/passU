#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "packet.h"
#include "ClientSocket.h"

// ClientConf 대화 상자입니다.

class ClientConf : public CDialogEx
{
	DECLARE_DYNAMIC(ClientConf)

public:
	ClientConf(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~ClientConf();
	CString m_address;
	CIPAddressCtrl m_ip;
	CString m_PortNum;
	
	CClientSocket clientSock;
	
	bool m_connectFlag; // 접속중인가를 판별하는 플래그
	bool m_portFlag; // 포트번호를 입력받았나 판별하는 플래그
	bool m_ipFlag; // ip 주소가 입력되었나 판별하는 플래그
	bool m_exitFlag;

	KPACKET keyboard;
	MPACKET mouse;
	CPACKET client;
	DPACKET data;

	int clientID;



// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnIpnFieldchangedIpaddress(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();

	void receiveData(CClientSocket *s);
	KPACKET packMessage(int msgType, int sendDev, int recvDev, int devType, int relativeField, int updownFlag, int pad1, int keyCode, int pad2, int pad3);
	void unpackMessage(KPACKET p);

	CButton m_CBtn_ClientConnect;
	CButton m_CBtn_ClientCancel;
	afx_msg void OnBnClickedCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void connect(int nPort);
	void cleanUp(void);
	void closeSock(void);
	void sendData(void);
};
