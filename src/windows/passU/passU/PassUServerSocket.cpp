// PassUServerSocket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "PassU.h"
#include "PassUServerSocket.h"
#include "Server.h"
#include "PassUDlg.h"

// CPassUServerSocket

CPassUServerSocket::CPassUServerSocket()
{
}

CPassUServerSocket::~CPassUServerSocket()
{
}


// CPassUServerSocket ��� �Լ�


void CPassUServerSocket::OnAccept(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CPassUDlg* pDlg = (CPassUDlg*)::AfxGetMainWnd();
	pDlg->Accept();
	CSocket::OnAccept(nErrorCode);
}
