#pragma once

// CPassUListen ��� ����Դϴ�.

#pragma once

#include "PassUSocket.h"
#include "PassUThread.h"

class CPassUListen : public CAsyncSocket
{
public:
	CPassUListen();
	virtual ~CPassUListen();

	virtual void OnAccept(int nErrorCode);
};


