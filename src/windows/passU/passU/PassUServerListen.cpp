// PassUServerListen.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "PassU.h"
#include "PassUServerListen.h"


// CPassUServerListen

CPassUServerListen::CPassUServerListen()
{
}

CPassUServerListen::~CPassUServerListen()
{
}


// CPassUServerListen ��� �Լ�


CObList * CPassUServerListen::getSockList(void)
{
	return &m_sockList;
}


void CPassUServerListen::OnAccept(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CSocket tmp;

	if(Accept(tmp)){
		pThread = (CPassUServerThread *)AfxBeginThread(RUNTIME_CLASS(CPassUServerThread), 0, 0, CREATE_SUSPENDED);

		if(pThread){
			pThread->m_hSocket = tmp.Detach();
			m_sockList.AddTail(pThread);
			pThread->c_id = m_sockList.GetCount();
			pThread->ResumeThread();
			TRACE("m_sockList Add Tail Success, pThread Sucess !\n");

		}

		AfxMessageBox(_T("������ ����, Accept �Ϸ�!"));
	}
	CAsyncSocket::OnAccept(nErrorCode);
}
