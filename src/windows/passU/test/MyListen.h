#pragma once

#include <list>
#include "MySocket.h"
#include "MyThread.h"

// CMyListen ��� ����Դϴ�.
using namespace std;

class CMyListen : public CAsyncSocket
{
public:
	//CObList m_sockList;
//	std::list<CMyThread>  
/*
	typedef CTypedPtrArray<CObArray, CMyThread *> CSocketList;

	CSocketList m_clientSock;
*/
	CMyListen();
	
	virtual ~CMyListen();
	virtual void OnAccept(int nErrorCode);

	CObList getSockList(void);
};


