#pragma once

// ServerSocket ��� ����Դϴ�.

class ServerSocket : public CSocket
{
public:
	ServerSocket();
	virtual ~ServerSocket();
	virtual void OnAccept(int nErrorCode);
};


