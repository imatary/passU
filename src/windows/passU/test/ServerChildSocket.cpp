// ServerChildSocket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "test.h"
#include "ServerChildSocket.h"


// ServerChildSocket

ServerChildSocket::ServerChildSocket()
{
}

ServerChildSocket::~ServerChildSocket()
{
}


// ServerChildSocket ��� �Լ�


void ServerChildSocket::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	((CtestApp *)AfxGetApp)->closeChild();
	CSocket::OnClose(nErrorCode);
}


void ServerChildSocket::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	((CtestApp *)AfxGetApp)->receiveData();
	CSocket::OnReceive(nErrorCode);
}
