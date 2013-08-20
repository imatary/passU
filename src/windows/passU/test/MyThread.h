#pragma once

#include "MySocket.h"

// CMyThread

class CMyThread : public CWinThread
{
	DECLARE_DYNCREATE(CMyThread)

protected:
	CMyThread();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CMyThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	SOCKET m_hSocket;
	CMySocket *m_mySocket;
	
	typedef CTypedPtrArray<CObArray, CMySocket *> CSocketList;
	CSocketList m_clientSocks;

protected:
	DECLARE_MESSAGE_MAP()
};


