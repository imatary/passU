// ClientSock.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "test.h"
#include "ClientSock.h"
#include "ClientConf.h"


// CClientSock

CClientSock::CClientSock()
{
}

CClientSock::~CClientSock()
{
}


// CClientSock ��� �Լ�


void CClientSock::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	((ClientConf *)AfxGetApp)->closeClientSock();

	CAsyncSocket::OnClose(nErrorCode);
}
