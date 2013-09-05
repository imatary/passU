// MyThread.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "test.h"
#include "MyThread.h"
#include "ServerConf.h"

#include "packet.h"
// CMyThread

IMPLEMENT_DYNCREATE(CMyThread, CWinThread)

CMyThread::CMyThread()
{
}

CMyThread::~CMyThread()
{
}

BOOL CMyThread::InitInstance()
{
	// TODO: ���⿡�� �� �����忡 ���� �ʱ�ȭ�� �����մϴ�.
	m_mySocket = new CMySocket();

	TRY{
		m_mySocket -> Attach(m_hSocket); 
		m_mySocket -> AsyncSelect(FD_READ | FD_CLOSE);
		
		/* Nagle �˰������� �����ϴ� �ڵ�, �츮 ���α׷������� Nagle �˰����� �ʿ���� */
	
		const char opt_val = true;
		setsockopt(*m_mySocket, IPPROTO_TCP, TCP_NODELAY, &opt_val, sizeof(opt_val));


	} CATCH_ALL(e){
		DWORD dwErrorCode = GetLastError();
		AfxMessageBox(dwErrorCode, 0, 0);
	}
	END_CATCH_ALL

	return TRUE;
}

int CMyThread::ExitInstance()
{
	// TODO: ���⿡�� �� �����忡 ���� ������ �����մϴ�.
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CMyThread, CWinThread)
END_MESSAGE_MAP()


// CMyThread �޽��� ó�����Դϴ�.