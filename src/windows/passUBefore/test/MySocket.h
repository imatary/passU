#pragma once

// CMySocket ��� ����Դϴ�.

class CMySocket : public CSocket
{
public:
	CMySocket();
	virtual ~CMySocket();
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};


