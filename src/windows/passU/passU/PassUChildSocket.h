#pragma once

// CPassUChildSocket ��� ����Դϴ�.

class CPassUChildSocket : public CSocket
{
public:
	CPassUChildSocket();
	virtual ~CPassUChildSocket();
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	int c_id;
};


