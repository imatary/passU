// PassUClientSocket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "PassU.h"
#include "PassUClientSocket.h"
#include "PassUDlg.h"

// CPassUClientSocket

CPassUClientSocket::CPassUClientSocket()
{
}

CPassUClientSocket::~CPassUClientSocket()
{
}


// CPassUClientSocket ��� �Լ�


void CPassUClientSocket::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
		CPassUDlg* pDlg = (CPassUDlg*)::AfxGetMainWnd();
	pDlg->ReceiveClientData(this);
	CSocket::OnReceive(nErrorCode);
}


void CPassUClientSocket::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
		CPassUDlg* pDlg = (CPassUDlg*)::AfxGetMainWnd();
		pDlg->CloseClient(this);
	CSocket::OnClose(nErrorCode);
}
