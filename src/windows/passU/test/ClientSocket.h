#pragma once

// ClientSocket ��� ����Դϴ�.

class ClientSocket : public CSocket
{
public:
	ClientSocket();
	virtual ~ClientSocket();
	virtual void OnClose(int nErrorCode);
};


