// PassUListen.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "passUTestServer.h"
#include "PassUListen.h"



// CPassUListen

CPassUListen::CPassUListen()
{
}

CPassUListen::~CPassUListen()
{
}


// CPassUListen ��� �Լ�
void CPassUListen::OnAccept(int nErrorCode)
{
	CSocket tmp;

	if(Accept(tmp))
	{
		CPassUThread* pThread = (CPassUThread *)AfxBeginThread(RUNTIME_CLASS(CPassUThread), 0, 0, CREATE_SUSPENDED);

		if (pThread)
		{
			pThread->m_hSocket = tmp.Detach();
			pThread->ResumeThread();
		}
	}
	CAsyncSocket::OnAccept(nErrorCode);
}
