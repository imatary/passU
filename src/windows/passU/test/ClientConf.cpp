// ClientConf.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "test.h"
#include "ClientConf.h"
#include "afxdialogex.h"
	
#include <afxsock.h> // sock �Լ� �����ϴ� ���̺귯��


// ClientConf ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(ClientConf, CDialogEx)

ClientConf::ClientConf(CWnd* pParent /*=NULL*/)
	: CDialogEx(ClientConf::IDD, pParent)
	, m_PortNum(_T(""))
{

}

ClientConf::~ClientConf()
{

}

void ClientConf::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ip);
	DDX_Text(pDX, IDC_EDIT1, m_PortNum);
	DDV_MaxChars(pDX, m_PortNum, 5);
}


BEGIN_MESSAGE_MAP(ClientConf, CDialogEx)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS1, &ClientConf::OnIpnFieldchangedIpaddress)
	ON_BN_CLICKED(IDOK, &ClientConf::OnBnClickedOk)
END_MESSAGE_MAP()


// ClientConf �޽��� ó�����Դϴ�.


void ClientConf::OnIpnFieldchangedIpaddress(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);

		*pResult = 0;
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;
}


void ClientConf::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	BYTE ipFirst, ipSecond, ipThird, ipForth;
	

	UpdateData();

	m_ip.GetAddress(ipFirst, ipSecond, ipThird, ipForth);
	m_address.Format(_T("%d.%d.%d.%d"), ipFirst, ipSecond, ipThird, ipForth);

	//nPort.Format(_T("%s"), m_PortNum);

	//AfxMessageBox(nPort);
	AfxMessageBox(m_address);

	int nPort;

	nPort = _ttoi(m_PortNum);

	((CtestApp *) AfxGetApp )->clientConnect(nPort, m_address);
	
	//flag = 1;
	
	CDialogEx::OnOK();

}