// Splash.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "PassU.h"
#include "Splash.h"
#include "afxdialogex.h"


// CSplash ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CSplash, CDialog)

CSplash::CSplash(CWnd* pParent /*=NULL*/)
	: CDialog(CSplash::IDD, pParent)
{

}

CSplash::~CSplash()
{
}

void CSplash::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSplash, CDialog)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CSplash �޽��� ó�����Դϴ�.


BOOL CSplash::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	SetTimer(0, 2000, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void CSplash::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	EndDialog(0);

	CDialog::OnTimer(nIDEvent);
}
