#pragma once

// ServerChildSocket ��� ����Դϴ�.

class ServerChildSocket : public CSocket
{
public:
	ServerChildSocket();
	virtual ~ServerChildSocket();
	virtual void OnClose(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};


