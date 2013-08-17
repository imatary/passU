
// TestServerDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "TestServer.h"
#include "TestServerDlg.h"
#include "afxdialogex.h"
#include "Mmsystem.h"

#define _WIN32_WINNT 0x0400

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestServerDlg ��ȭ ����



CTestServerDlg::CTestServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestServerDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SERVERON, &CTestServerDlg::OnBnClickedServeron)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CTestServerDlg �޽��� ó����

BOOL CTestServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	prevTime = 0;

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CTestServerDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CTestServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTestServerDlg::OnBnClickedServeron()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	((CTestServerApp *)AfxGetApp())->initServer(3737);
}

void CTestServerDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	DWORD curTime = timeGetTime();
	
	if(curTime - prevTime > 40) {
		CString str;
		str.Format(_T("x: %d y: %d"), point.x, point.y);
		SetDlgItemText(IDC_LOC, str);

		prevTime = curTime;

		((CTestServerApp *)AfxGetApp())->sendMouseMove(point.x, point.y);
	}

	CDialog::OnMouseMove(nFlags, point);
}


void CTestServerDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	DWORD curTime = timeGetTime();
	
	if(curTime - prevTime > 20) {
		CString str;
		str.Format(_T("x: %d y: %d"), point.x, point.y);
		SetDlgItemText(IDC_LOC, str);

		prevTime = curTime;

		((CTestServerApp *)AfxGetApp())->sendMouseDown(point.x, point.y);
	}

	CDialog::OnLButtonDown(nFlags, point);
}


void CTestServerDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	DWORD curTime = timeGetTime();
	
	if(curTime - prevTime > 40) {
		CString str;
		str.Format(_T("x: %d y: %d"), point.x, point.y);
		SetDlgItemText(IDC_LOC, str);

		prevTime = curTime;

		((CTestServerApp *)AfxGetApp())->sendMouseUp(point.x, point.y);
	}

	CDialog::OnLButtonUp(nFlags, point);
}
