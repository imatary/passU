// MySocket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "test.h"
#include "MySocket.h"
#include "ServerConf.h"

// CMySocket

CMySocket::CMySocket()
{
}

CMySocket::~CMySocket()
{
}


// CMySocket ��� �Լ�


void CMySocket::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	((ServerConf *)AfxGetApp())->closeClient(this);
	CSocket::OnClose(nErrorCode);
}


void CMySocket::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	((ServerConf *)AfxGetApp())->receiveData(this);

	CSocket::OnReceive(nErrorCode);
}
