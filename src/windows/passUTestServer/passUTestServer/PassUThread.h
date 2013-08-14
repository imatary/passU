#pragma once



// CPassUThread
#pragma once

#include "PassUSocket.h"

class CPassUThread : public CWinThread
{
	DECLARE_DYNCREATE(CPassUThread)

protected:
	CPassUThread();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CPassUThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	SOCKET m_hSocket;
	CPassUSocket* m_passuSocket;

protected:
	DECLARE_MESSAGE_MAP()
};


