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
	int nClient; // Ŭ���̾�Ʈ ����
	virtual void OnAccept(int nErrorCode);
	HWND m_hWnd;
};


