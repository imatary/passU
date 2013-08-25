#pragma once
#include "afxcmn.h"
#include "afxwin.h"
#include "packet.h"
#include "ClientSocket.h"

// ClientConf ��ȭ �����Դϴ�.

class ClientConf : public CDialogEx
{
	DECLARE_DYNAMIC(ClientConf)

public:
	ClientConf(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~ClientConf();
	CString m_address;
	CIPAddressCtrl m_ip;
	CString m_PortNum;
	
	CClientSocket clientSock;
	
	bool m_connectFlag; // �������ΰ��� �Ǻ��ϴ� �÷���
	bool m_portFlag; // ��Ʈ��ȣ�� �Է¹޾ҳ� �Ǻ��ϴ� �÷���
	bool m_ipFlag; // ip �ּҰ� �ԷµǾ��� �Ǻ��ϴ� �÷���
	bool m_exitFlag;

	KPACKET keyboard;
	MPACKET mouse;
	CPACKET client;
	DPACKET data;

	int clientID;



// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnIpnFieldchangedIpaddress(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();

	void receiveData(CClientSocket *s);
	KPACKET packMessage(int msgType, int sendDev, int recvDev, int devType, int relativeField, int updownFlag, int pad1, int keyCode, int pad2, int pad3);
	KPACKET unpackMessage(KPACKET p);

	CButton m_CBtn_ClientConnect;
	CButton m_CBtn_ClientCancel;
	afx_msg void OnBnClickedCancel();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void connect(int nPort);
	void cleanUp(void);
	void closeSock(void);
	void sendData(void);
};
