// PassUServerSocket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "PassU.h"
#include "PassUServerSocket.h"
#include "Server.h"

// CPassUServerSocket

CPassUServerSocket::CPassUServerSocket()
{
}

CPassUServerSocket::~CPassUServerSocket()
{
}


// CPassUServerSocket ��� �Լ�


void CPassUServerSocket::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	CSocket::OnClose(nErrorCode);
}


void CPassUServerSocket::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	((CServer *)AfxGetApp())->ReceiveData(this);
	CSocket::OnReceive(nErrorCode);
}
