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
	
	CMyListen();
	virtual ~CMyListen();

	typedef CTypedPtrArray<CObArray, CMyThread *> m_cSocketList;

public:
	CObList m_sockList;
	int m_AcceptCount;
	
	CMyThread * pThread;
	virtual void OnAccept(int nErrorCode);
	
	CObList * getList(void);
};


