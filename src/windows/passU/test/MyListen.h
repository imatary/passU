#pragma once

// CMyListen ��� ����Դϴ�.

class CMyListen : public CAsyncSocket
{
public:
	CMyListen();
	virtual ~CMyListen();
	virtual void OnAccept(int nErrorCode);
};


