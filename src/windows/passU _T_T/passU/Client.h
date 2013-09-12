#pragma once
#include "PassUServerSocket.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "packet.h"

// CClient ��ȭ �����Դϴ�.

class CClient : public CDialogEx
{
	DECLARE_DYNAMIC(CClient)

public:
	CClient(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CClient();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CLIENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	void OnConnectServer(void);
	void OnDisconnect(void);
	CPassUServerSocket m_clientSock;
	CIPAddressCtrl m_IpAddressCtrl;
	afx_msg void OnBnClickedConnect();
	CButton m_cBtn_connect;
	afx_msg void OnBnClickedCancel();
	bool m_connectFlag;
	int client_ID;

	CString m_address;
	BYTE ipFirst, ipSecond, ipThird, ipForth;
	PACKET *p;
	afx_msg BOOL OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct);
	BOOL ExecuteProcess(CString FilePath, CString Parameter);
	BOOL OSVersionXPOver();
	CButton m_CBtn_Cancel;
};
