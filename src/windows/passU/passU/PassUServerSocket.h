#pragma once

// CPassUServerSocket 명령 대상입니다.

class CPassUServerSocket : public CSocket
{
public:
	CPassUServerSocket();
	virtual ~CPassUServerSocket();
	virtual void OnAccept(int nErrorCode);
};


