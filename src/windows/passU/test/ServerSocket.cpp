// ServerSocket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "test.h"
#include "ServerSocket.h"


// ServerSocket

ServerSocket::ServerSocket()
{
}

ServerSocket::~ServerSocket()
{

}

void ServerSocket::OnAccept(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	((CtestApp *)AfxGetApp())->accept();
	CSocket::OnAccept(nErrorCode);
}
