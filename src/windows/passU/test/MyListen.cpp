// MyListen.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "test.h"
#include "MyListen.h"
#include "MyThread.h"


// CMyListen

CMyListen::CMyListen()
{
}

CMyListen::~CMyListen()
{
}


// CMyListen ��� �Լ�


void CMyListen::OnAccept(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	CSocket tmp;

	if(Accept(tmp)){
		CMyThread *pThread = (CMyThread *)AfxBeginThread(RUNTIME_CLASS(CMyThread), 0, 0, CREATE_SUSPENDED);

		if(pThread){
			pThread->m_hSocket = tmp.Detach();
			pThread->ResumeThread();
		}
	}
	CAsyncSocket::OnAccept(nErrorCode);
}
