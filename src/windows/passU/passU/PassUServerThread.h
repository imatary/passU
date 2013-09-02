#pragma once

#include "PassUServerSocket.h"


// CPassUServerThread

class CPassUServerThread : public CWinThread
{
	DECLARE_DYNCREATE(CPassUServerThread)

protected:
	CPassUServerThread();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CPassUServerThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	SOCKET m_hSocket;
	CPassUServerSocket *m_passUSocket;
	int c_id;

protected:
	DECLARE_MESSAGE_MAP()
};


