#pragma once

// CPassUClientSocket ��� ����Դϴ�.

class CPassUClientSocket : public CSocket
{
public:
	CPassUClientSocket();
	virtual ~CPassUClientSocket();
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


