// PassULoactionInfo.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "PassU.h"
#include "PassULoactionInfo.h"


// CPassULoactionInfo

IMPLEMENT_DYNAMIC(CPassULoactionInfo, CWnd)

CPassULoactionInfo::CPassULoactionInfo()
{

}

CPassULoactionInfo::~CPassULoactionInfo()
{
}


BEGIN_MESSAGE_MAP(CPassULoactionInfo, CWnd)
END_MESSAGE_MAP()



// CPassULoactionInfo �޽��� ó�����Դϴ�.


int CPassULoactionInfo::getStatus(void)
{
	return m_status;
}


int CPassULoactionInfo::getPosition(void)
{
	return m_position;
}


void CPassULoactionInfo::setStatus(int status)
{
	m_status = status;
}


void CPassULoactionInfo::setPosition(int position)
{
	m_position = position;
}
