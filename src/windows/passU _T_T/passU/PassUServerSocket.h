#pragma once

// CPassUServerSocket ��� ����Դϴ�.

class CPassUServerSocket : public CSocket
{
public:
	CPassUServerSocket();
	virtual ~CPassUServerSocket();
	virtual void OnAccept(int nErrorCode);
};


