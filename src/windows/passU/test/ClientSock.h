#pragma once

// CClientSock ��� ����Դϴ�.

class CClientSock : public CAsyncSocket
{
public:
	CClientSock();
	virtual ~CClientSock();
	virtual void OnClose(int nErrorCode);
};


