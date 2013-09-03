
// PassUDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "PassU.h"
#include "PassUDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

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


// CPassUDlg ��ȭ ����



CPassUDlg::CPassUDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPassUDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPassUDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
	DDX_Control(pDX, IDC_BUTTON1, m_CBtn_Start);
	DDX_Control(pDX, IDC_BUTTON2, m_CBtn_Stop);
}

BEGIN_MESSAGE_MAP(CPassUDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CPassUDlg::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDC_BUTTON1, &CPassUDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CPassUDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CPassUDlg �޽��� ó����

BOOL CPassUDlg::OnInitDialog()
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

	CString tmp;
	tmp.Format(_T("SERVER"));
	m_Tab.InsertItem(0, tmp);
	tmp.Format(_T("CLIENT"));
	m_Tab.InsertItem(1, tmp);

	CRect rect;

	m_Tab.GetClientRect(&rect);
	m_tab1.Create(IDD_SERVER, &m_Tab);
	m_tab1.SetWindowPos(NULL, 5, 25, rect.Width() - 10 , rect.Height() - 30, SWP_SHOWWINDOW|SWP_NOZORDER);
	m_tab2.Create(IDD_CLIENT, &m_Tab);
	m_tab2.SetWindowPos(NULL, 5, 25, rect.Width() - 10, rect.Height() - 30, SWP_NOZORDER);


	m_pwndShow = &m_tab1;

	UpdateData(FALSE);


	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CPassUDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPassUDlg::OnPaint()
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
HCURSOR CPassUDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPassUDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	if(m_pwndShow != NULL){
		m_pwndShow->ShowWindow(SW_HIDE);
		m_pwndShow = NULL;
	}
	int nIndex = m_Tab.GetCurSel();

	switch(nIndex){
	case 0:
		m_tab1.ShowWindow(SW_SHOW);
		m_pwndShow = &m_tab1;
	//	m_SorC = TRUE;
		break;

	case 1:
		m_tab2.ShowWindow(SW_SHOW);
		m_pwndShow = &m_tab2;
	//	m_SorC = FALSE;
		break;
	}
	

	*pResult = 0;
}

void CPassUDlg::ReceiveData(CPassUChildSocket * s)
{
	PACKET tmp;
	s->Receive(&tmp, sizeof(PACKET));
	COPYDATASTRUCT CDS;

	CDS.dwData = 2; // receiveData
	CDS.cbData = sizeof(PACKET);
	CDS.lpData = &tmp;

	
	::SendMessage(m_tab1.GetSafeHwnd(), WM_COPYDATA, 0, (LPARAM)(VOID *)&CDS);

}

void CPassUDlg::Accept(void)
{
	CPassUChildSocket *pChild = new CPassUChildSocket();

	BOOL check = m_pServer->Accept(*pChild);

	if(check == FALSE){
		AfxMessageBox(_T("Accept Failed"));
		return ;
	}

	m_pSockList.AddTail(pChild);

	AfxMessageBox(_T("Accept COmplete!!"));
}

void CPassUDlg::CleanUp(void)
{
	if(m_pServer)	delete m_pServer;

	CPassUChildSocket *pChild;

	while(!m_pSockList.IsEmpty()){
		pChild = (CPassUChildSocket *)m_pSockList.RemoveHead();
		delete pChild;
	}
	AfxMessageBox(_T("Clean Up!"));
}

void CPassUDlg::CloseChild(CPassUChildSocket *s){

	CPassUChildSocket *pChild;
	POSITION pos = m_pSockList.GetHeadPosition();
	while(pos != NULL){
		pChild = (CPassUChildSocket *)m_pSockList.GetAt(pos);

		if(pChild == s){
			m_pSockList.RemoveAt(pos);
			delete	pChild;
			break;
		}
		m_pSockList.GetNext(pos);
	}
}

void CPassUDlg::OnStartServer()
{
	m_pServer = new CPassUServerSocket();
	m_pServer->Create(30000);
	m_pServer->Listen();

	AfxMessageBox(_T("InitServer"));
}

void CPassUDlg::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(m_SorC){
		OnStartServer();
	}

	m_CBtn_Start.EnableWindow(FALSE);
}


void CPassUDlg::OnBnClickedButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	
	m_CBtn_Start.EnableWindow(TRUE);
	CleanUp();
	//CDialog::OnCancel();
}
