
// passUTestServerDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "passUTestServer.h"
#include "passUTestServerDlg.h"
#include "PassUListen.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define ECHOMAX 1024

// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.
UINT ReceiveData(LPVOID pParam);

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	// �����Դϴ�.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CpassUTestServerDlg ��ȭ ����


HANDLE thr;
unsigned long id1;

CpassUTestServerDlg::CpassUTestServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CpassUTestServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CpassUTestServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
}

BEGIN_MESSAGE_MAP(CpassUTestServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// CpassUTestServerDlg �޽��� ó����

BOOL CpassUTestServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	CPassUListen listen;
	CSocket client;
	// �ʱ�ȭ
	if(!AfxSocketInit()) {
		AfxMessageBox(_T("Socket �ʱ�ȭ ����"));
	}
	// ��Ʈ ���� : 9000��
	if(!listen.Create(9000)) {
		AfxMessageBox(_T("Port ���� ����"));
	}
	// Listen 
	if(!listen.Listen())  {
		AfxMessageBox(_T("Listen ����"));
	}
	// Aceept
	if(!listen.Accept(client)) {
		AfxMessageBox(_T("Accept ����"));
	}
	int bytes, i=0;
	char buf[20];
	ZeroMemory(buf, sizeof(buf));
	strcpy_s(buf, "250 Conect OK. Start Message!");
	// Send�� ������ ���� 
	bytes = client.Send(buf, strlen(buf));
	while( i != 10) {                          
		ZeroMemory(buf, sizeof(buf));
		// ������ �ޱ� ����
		bytes = client.Receive(buf, sizeof(buf));
		// ������ ���
		TRACE(buf);
	}
	client.Close();
	listen.Close();

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CpassUTestServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CpassUTestServerDlg::OnPaint()
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
HCURSOR CpassUTestServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CpassUTestServerDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if(pMsg->message == WM_KEYDOWN)    { // if message is key down
		CString key;

		switch (pMsg->wParam){
		case VK_UP:     // if Up arrow  
			key = "1";
			break;
		case VK_DOWN:   // if down arrow 
			key = "2";
			break;
		case VK_LEFT:   // if down arrow 
			key = "3";
			break;
		case VK_RIGHT:   // if down arrow 
			key = "4";
			break;
		} // end of switch

		CSocket passUClient;  

		if (passUClient.Create(0,SOCK_DGRAM,NULL) == 0) {
			AfxMessageBox(_T("Create() failed"));
		}

		if (passUClient.SendTo((void *)&key, sizeof(key),3737,
			(LPCTSTR)_T("223.62.180.126"), 0) != sizeof(key)) {
				AfxMessageBox(_T("SendTo() sent a different number of bytes than expected"));
		}
		passUClient.Close();
	} // end of if
	return CDialogEx::PreTranslateMessage(pMsg);
}