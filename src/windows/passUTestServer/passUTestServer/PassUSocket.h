#pragma once

// CPassUSocket ��� ����Դϴ�.

#pragma once

class CPassUSocket : public CSocket
{
public:
	CPassUSocket();
	virtual ~CPassUSocket();

	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
};


