// AcceptSock.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "test.h"
#include "AcceptSock.h"
#include "ServerConf.h"

// CAcceptSock

CAcceptSock::CAcceptSock()
{
}

CAcceptSock::~CAcceptSock()
{
}


// CAcceptSock ��� �Լ�


void CAcceptSock::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	((ServerConf *) AfxGetApp)->closeAcceptSock();
	CAsyncSocket::OnClose(nErrorCode);
}
