// PassUChildSocket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "PassU.h"
#include "PassUChildSocket.h"
#include "Server.h"
#include "PassUDlg.h"


// CPassUChildSocket

CPassUChildSocket::CPassUChildSocket()
{
}

CPassUChildSocket::~CPassUChildSocket()
{
}


// CPassUChildSocket ��� �Լ�


void CPassUChildSocket::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CPassUDlg* pDlg = (CPassUDlg*)::AfxGetMainWnd();
	pDlg->ReceiveData(this);
	CSocket::OnReceive(nErrorCode);
}


void CPassUChildSocket::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CPassUDlg* pDlg = (CPassUDlg*)::AfxGetMainWnd();
	pDlg->CloseChild(this);
	CSocket::OnClose(nErrorCode);
}
