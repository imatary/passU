#pragma once

// CAcceptSock ��� ����Դϴ�.

class CAcceptSock : public CAsyncSocket
{
public:
	CAcceptSock();
	virtual ~CAcceptSock();
	virtual void OnClose(int nErrorCode);
};


