// USBIconDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "USBIconDlg.h"
#include "afxdialogex.h"
#include "test.h"


IMPLEMENT_DYNAMIC(CUSBIconDlg, CDialogEx)

CUSBIconDlg::CUSBIconDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUSBIconDlg::IDD, pParent)
{
	Transparent = RGB(255, 255, 255);

	// ������ 50
	SetTransparency(90);

	m_background.LoadBitmapW(IDB_PASSU);
	m_bMouseDown = FALSE;

	// ������ 50
	SetTransparency(90);

}

CUSBIconDlg::~CUSBIconDlg()
{

}

void CUSBIconDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
} 

BEGIN_MESSAGE_MAP(CUSBIconDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

typedef BOOL(WINAPI * SLWA)(HWND, COLORREF, BYTE, DWORD);

void CUSBIconDlg::SetTransparency(int percent)
{
	SLWA pSetLayeredWindowAttributes = NULL;														// �Լ������� ����, �ʱ�ȭ.
	HINSTANCE hmodUSER32 = LoadLibraryA("USER32.DLL");												// �ν��Ͻ� ����.
	pSetLayeredWindowAttributes = (SLWA)GetProcAddress(hmodUSER32,"SetLayeredWindowAttributes");	//�Լ������� ����.
	HWND hwnd = this->m_hWnd;																		//���̾�α��� �ڵ� ����.
	SetWindowLong(hwnd, GWL_EXSTYLE,GetWindowLong(hwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	pSetLayeredWindowAttributes(hwnd, 0, (255 * percent) / 100, LWA_ALPHA);
	pSetLayeredWindowAttributes(hwnd, RGB(255, 255, 255), 0, LWA_COLORKEY);
}


// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CUSBIconDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CUSBIconDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CUSBIconDlg::OnEraseBkgnd(CDC* pDC)
{
	CDialog::OnEraseBkgnd(pDC);
	
	if(!m_background.m_hObject)
		return true;

	CRect rect;
	GetClientRect(&rect);

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = memDC.SelectObject(&m_background);

	BITMAP bmap;
	m_background.GetBitmap(&bmap);
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, bmap.bmWidth, bmap.bmHeight, SRCCOPY);

	memDC.SelectObject(pOldBitmap);
	
	return true;
}


void CUSBIconDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_bMouseDown = TRUE;
	SetCapture();
	m_mouseDownPoint = point;
	CDialog::OnLButtonDown(nFlags, point);
}


void CUSBIconDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	m_bMouseDown = FALSE;
	ReleaseCapture();
	CDialog::OnLButtonUp(nFlags, point);
}


void CUSBIconDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if( m_bMouseDown )
	{
		CSize size = m_mouseDownPoint - point;
		CRect rect;
		GetWindowRect(&rect);
		rect = size - &rect;
		MoveWindow(rect);
	}

	CDialogEx::OnMouseMove(nFlags, point);
}