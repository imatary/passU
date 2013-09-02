// PassUServerThread.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "PassU.h"
#include "PassUServerThread.h"


// CPassUServerThread

IMPLEMENT_DYNCREATE(CPassUServerThread, CWinThread)

CPassUServerThread::CPassUServerThread()
{
	
}

CPassUServerThread::~CPassUServerThread()
{
}

BOOL CPassUServerThread::InitInstance()
{
	// TODO: ���⿡�� �� �����忡 ���� �ʱ�ȭ�� �����մϴ�.
	m_hWnd = NULL;
	TRACE("Before passUsocket\n");
	TRACE(_T("Thread������ m_hwnd : %p\n", m_hWnd));
	m_passUSocket = new CPassUServerSocket(m_hWnd);

	TRY{
		m_passUSocket -> Attach(m_hSocket); 
		m_passUSocket -> AsyncSelect(FD_READ | FD_CLOSE);
		
		/* Nagle �˰����� �����ϴ� �ڵ�, �츮 ���α׷������� Nagle �˰��� �ʿ���� */
	
		const char opt_val = true;
		setsockopt(*m_passUSocket, IPPROTO_TCP, TCP_NODELAY, &opt_val, sizeof(opt_val));


	} CATCH_ALL(e){
		DWORD dwErrorCode = GetLastError();
		AfxMessageBox(dwErrorCode, 0, 0);
	}
	END_CATCH_ALL

	return TRUE;
}

int CPassUServerThread::ExitInstance()
{
	// TODO: ���⿡�� �� �����忡 ���� ������ �����մϴ�.
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CPassUServerThread, CWinThread)
END_MESSAGE_MAP()


// CPassUServerThread �޽��� ó�����Դϴ�.


void CPassUServerThread::setClientID(int clientID)
{
	c_id = clientID;
}


int CPassUServerThread::getClientID(void)
{
	return c_id;
}
