#pragma once

// CPassUServerSocket ��� ����Դϴ�.

class CPassUServerSocket : public CSocket
{
public:
	CPassUServerSocket();
	virtual ~CPassUServerSocket();
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};


