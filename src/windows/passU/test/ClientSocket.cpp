// ClientSocket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "test.h"
#include "ClientSocket.h"


// ClientSocket

ClientSocket::ClientSocket()
{
}

ClientSocket::~ClientSocket()
{
}


// ClientSocket ��� �Լ�


void ClientSocket::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	((CtestApp *)AfxGetApp()) -> clientcloseChild();
	CSocket::OnClose(nErrorCode);
}
