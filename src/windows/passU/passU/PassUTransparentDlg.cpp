// PassUTransparentDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "PassU.h"
#include "PassUTransparentDlg.h"
#include "afxdialogex.h"


// PassUTransparentDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CPassUTransparentDlg, CDialog)

CPassUTransparentDlg::CPassUTransparentDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPassUTransparentDlg::IDD, pParent)
{

}

CPassUTransparentDlg::~CPassUTransparentDlg()
{
}

void CPassUTransparentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPassUTransparentDlg, CDialog)
END_MESSAGE_MAP()


// CPassUTransparentDlg �޽��� ó�����Դϴ�.


BOOL CPassUTransparentDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	LONG ExtendedStyle = GetWindowLong( GetSafeHwnd(), GWL_EXSTYLE);
	ExtendedStyle &= ~WS_CAPTION;
	ExtendedStyle &= ~WS_SYSMENU;
	SetWindowLong( GetSafeHwnd(), GWL_EXSTYLE, ExtendedStyle | WS_EX_LAYERED );

	double TransparencyPercentage = 1;

	double fAlpha = TransparencyPercentage * ( 255.0 / 100 );
	BYTE byAlpha = static_cast<BYTE>( fAlpha );
	SetLayeredWindowAttributes( 0, byAlpha, LWA_ALPHA );

	int screenx = GetSystemMetrics( SM_CXSCREEN );
	int screeny = GetSystemMetrics( SM_CYSCREEN );

	SetWindowPos( NULL, -4, -4, screenx + 8, screeny + 4, SWP_NOZORDER );
	::SetWindowPos(this->GetSafeHwnd(), HWND_TOPMOST, 0,0,0,0,SWP_NOMOVE | SWP_NOSIZE);
	::SetForegroundWindow(this->GetSafeHwnd());
	::SetActiveWindow(this->GetSafeHwnd());
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
