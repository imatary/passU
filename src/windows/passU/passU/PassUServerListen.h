#pragma once

#include "PassUServerThread.h"
// CPassUServerListen ��� ����Դϴ�.

class CPassUServerListen : public CAsyncSocket
{
public:
	CPassUServerListen();
	virtual ~CPassUServerListen();
	CObList * getSockList(void);
	CObList m_sockList;
	CPassUServerThread *pThread;

	virtual void OnAccept(int nErrorCode);
};


