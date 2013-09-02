// PassUServerSocket.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "PassU.h"
#include "PassUServerSocket.h"
#include "Server.h"

// CPassUServerSocket

CPassUServerSocket::CPassUServerSocket(){}

CPassUServerSocket::CPassUServerSocket(HWND hWnd)
{
	TRACE(_T("Socket������ �ޱ� �� m_hwnd : %p, hWnd : %p\n", m_hWnd, hWnd));
	m_hWnd = hWnd;
	TRACE(_T("Socket������ �ް��� m_hwnd : %p, hWnd : %p\n", m_hWnd, hWnd));
}

CPassUServerSocket::~CPassUServerSocket()
{
}

// CPassUServerSocket ��� �Լ�


void CPassUServerSocket::OnClose(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	CSocket::OnClose(nErrorCode);
}


void CPassUServerSocket::OnReceive(int nErrorCode)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	
	PACKET p;
	COPYDATASTRUCT CDS;
	Receive(&p, sizeof(PACKET));

	HWND hWnd = ::FindWindow(NULL, TEXT("PassU - Pass Your USB via Network"));
	
	
	TRACE(_T("Socket������ m_hwnd : %p\n", m_hWnd));

	::SendMessage(m_hWnd, WM_COPYDATA, 0, (LPARAM)(VOID *)&CDS);
	
 //	((CServer *)AfxGetApp())->ReceiveData(this);
	CSocket::OnReceive(nErrorCode);
}
