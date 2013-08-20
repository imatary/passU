#pragma once
#include "afxcmn.h"
#include "afxwin.h"


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
	CSocket clientSock;
	bool m_connectFlag; // �������ΰ��� �Ǻ��ϴ� �÷���
	bool m_portFlag; // ��Ʈ��ȣ�� �Է¹޾ҳ� �Ǻ��ϴ� �÷���
	bool m_ipFlag; // ip �ּҰ� �ԷµǾ��� �Ǻ��ϴ� �÷���
// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnIpnFieldchangedIpaddress(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();

	void sendData(CString strData);
	void receiveData(void);
	CButton m_CBtn_ClientConnect;
	CButton m_CBtn_ClientCancel;
	afx_msg void OnBnClickedCancel();
};
