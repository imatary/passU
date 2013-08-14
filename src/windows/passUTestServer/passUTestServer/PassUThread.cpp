// PassUThread.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "passUTestServer.h"
#include "PassUThread.h"


// CPassUThread

IMPLEMENT_DYNCREATE(CPassUThread, CWinThread)

CPassUThread::CPassUThread()
{
}

CPassUThread::~CPassUThread()
{
}

BOOL CPassUThread::InitInstance()
{
	// TODO: ���⿡�� �� �����忡 ���� �ʱ�ȭ�� �����մϴ�.
	m_passuSocket = new CPassUSocket();

	TRY
	{
		m_passuSocket->Attach(m_hSocket);
		m_passuSocket->AsyncSelect(FD_READ | FD_CLOSE);
	}
	CATCH_ALL(e)
	{
		DWORD dwErrorCode = GetLastError();
		AfxMessageBox(dwErrorCode, 0, 0);
	}
	END_CATCH_ALL
	return TRUE;
}

int CPassUThread::ExitInstance()
{
	// TODO: ���⿡�� �� �����忡 ���� ������ �����մϴ�.
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CPassUThread, CWinThread)
END_MESSAGE_MAP()


// CPassUThread �޽��� ó�����Դϴ�.
