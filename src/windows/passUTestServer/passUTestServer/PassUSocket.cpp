// PassUSocket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "passUTestServer.h"
#include "PassUSocket.h"


// CPassUSocket

CPassUSocket::CPassUSocket()
{
}

CPassUSocket::~CPassUSocket()
{
}


// CPassUSocket ��� �Լ�
void CPassUSocket::OnReceive(int nErrorCode)
{
	printf("Hello");
}

void CPassUSocket::OnClose(int nErrorCode)
{
}