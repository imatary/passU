
// PassUDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "PassU.h"
#include "PassUDlg.h"
#include "afxdialogex.h"
#include "PassUClientSocket.h"
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
	ON_WM_DESTROY()
	ON_WM_COPYDATA()
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
	whereisPoint = 5;
	UpdateData(FALSE);

	// �ڽ��� ȭ�� ���ϱ�
	nWidth = GetSystemMetrics(SM_CXSCREEN);
	nHeight = GetSystemMetrics(SM_CYSCREEN);

	// ó������ Ŭ���̾�Ʈ�� ������ ������ �ʴ´�.
	m_allowSend = FALSE;

	//Scroll_lock �ȴ������ִ� ���·� �����.
	if(::GetKeyState(VK_SCROLL) < 0){
		keybd_event(VK_SCROLL, 0, 0, 0);
		keybd_event(VK_SCROLL, 0, KEYEVENTF_KEYUP, 0);
	}

	//���콺 Ŀ�� �ε�
	hcur_UPARROW = LoadCursor(NULL,IDC_UPARROW);
	hcur_UPARROW = CopyCursor(hcur_UPARROW);
	hcur_SIZEWE = LoadCursor(NULL, IDC_SIZEWE);
	hcur_SIZEWE = CopyCursor(hcur_SIZEWE);
	hcur_SIZENWSE = LoadCursor(NULL, IDC_SIZENWSE);
	hcur_SIZENWSE = CopyCursor(hcur_SIZENWSE);
	hcur_SIZENS = LoadCursor(NULL, IDC_SIZENS);
	hcur_SIZENS = CopyCursor(hcur_SIZENS);
	hcur_SIZENESW = LoadCursor(NULL, IDC_SIZENESW);
	hcur_SIZENESW = CopyCursor(hcur_SIZENESW);
	hcur_SIZEALL = LoadCursor(NULL, IDC_SIZEALL);
	hcur_SIZEALL = CopyCursor(hcur_SIZEALL);
	hcur_SIZE = LoadCursor(NULL, IDC_SIZE);
	hcur_SIZE = CopyCursor(hcur_SIZE);
	hcur_NO = LoadCursor(NULL, IDC_NO);
	hcur_NO = CopyCursor(hcur_NO);
	hcur_ICON = LoadCursor(NULL, IDC_ICON);
	hcur_ICON = CopyCursor(hcur_ICON);
	hcur_IBEAM = LoadCursor(NULL, IDC_IBEAM);
	hcur_IBEAM = CopyCursor(hcur_IBEAM);
	hcur_HELP = LoadCursor(NULL, IDC_HELP);
	hcur_HELP = CopyCursor(hcur_HELP);
	hcur_CROSS = LoadCursor(NULL, IDC_CROSS);
	hcur_CROSS = CopyCursor(hcur_CROSS);
	hcur_ARROW = LoadCursor(NULL, IDC_ARROW);
	hcur_ARROW = CopyCursor(hcur_ARROW);
	hcur_APPSTARTING = LoadCursor(NULL, IDC_APPSTARTING);
	hcur_APPSTARTING = CopyCursor(hcur_APPSTARTING); 
	hcur_WAIT = LoadCursor(NULL, IDC_WAIT);
	hcur_WAIT = CopyCursor(hcur_WAIT);

	m_changeWindow = FALSE;

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
		m_SorC = TRUE;
		break;

	case 1:
		m_tab2.ShowWindow(SW_SHOW);
		m_pwndShow = &m_tab2;
		m_SorC = FALSE;
		break;
	}


	*pResult = 0;
}

void CPassUDlg::ReceiveData(CPassUChildSocket * s)
{
	char buf[4096];
	ZeroMemory(buf, sizeof(buf));

	int len = s->Receive(&buf, sizeof(buf));

	if(ParseData(buf, len) < 0)
		AfxMessageBox("Parsing Error\n");
}

int CPassUDlg::ParseData(char *buf, int len)
{
	int msgType;
	char msgTypeBuf[4];
	memcpy(msgTypeBuf, buf, sizeof(msgTypeBuf));
	msgType = byteToint(msgTypeBuf, 4);

	if(msgType == MSG_KEYBOARD) {
		KPACKET packet;

		ParseKeyboardData(buf, &packet);

		COPYDATASTRUCT CDS;

		CDS.dwData = 2; // receiveData
		CDS.cbData = sizeof(KPACKET);
		CDS.lpData = &packet;
		::SendMessage(m_tab1.GetSafeHwnd(), WM_COPYDATA, 0, (LPARAM)(VOID *)&CDS);
	} else if(msgType == MSG_MOUSE) {
		MPACKET packet;

		ParseMouseData(buf, &packet);

		COPYDATASTRUCT CDS;

		CDS.dwData = 2; // receiveData
		CDS.cbData = sizeof(MPACKET);
		CDS.lpData = &packet;
		::SendMessage(m_tab1.GetSafeHwnd(), WM_COPYDATA, 0, (LPARAM)(VOID *)&CDS);
	} else if(msgType == MSG_CLIENT) {
		CPACKET packet;

		ParseClientData(buf, &packet);

		COPYDATASTRUCT CDS;

		CDS.dwData = 2; // receiveData
		CDS.cbData = sizeof(CPACKET);
		CDS.lpData = &packet;
		::SendMessage(m_tab1.GetSafeHwnd(), WM_COPYDATA, 0, (LPARAM)(VOID *)&CDS);
	} else if(msgType == MSG_DATA) {
		DPACKET packet;
		ZeroMemory(&packet, sizeof(DPACKET));

		memcpy(&packet.usbdesc, buf + sizeof(packet.msgType) + sizeof(packet.len), packet.len);

		COPYDATASTRUCT CDS;

		CDS.dwData = 2; // receiveData
		CDS.cbData = sizeof(DPACKET);
		CDS.lpData = &packet;
		::SendMessage(m_tab1.GetSafeHwnd(), WM_COPYDATA, 0, (LPARAM)(VOID *)&CDS);
	} else {
		return -1;
	}
	return 0;
}

int CPassUDlg::ParseKeyboardData(char *buf, KPACKET *packet)
{
	char msgTypeBuf[4];

	memcpy(msgTypeBuf, buf, sizeof(msgTypeBuf));
	packet->msgType = byteToint(msgTypeBuf, 4);

	char sendDevBuf[4];
	memcpy(sendDevBuf, buf + sizeof(msgTypeBuf), sizeof(sendDevBuf));
	packet->sendDev = byteToint(sendDevBuf, 4);

	char recvDevBuf[4];
	memcpy(recvDevBuf, buf + sizeof(msgTypeBuf) + sizeof(sendDevBuf), sizeof(recvDevBuf));
	packet->recvDev = byteToint(recvDevBuf, 4);

	char deviceTypeBuf[1];
	memcpy(deviceTypeBuf, buf + sizeof(msgTypeBuf) + sizeof(sendDevBuf) + sizeof(recvDevBuf), sizeof(deviceTypeBuf));
	packet->deviceType = byteToint(deviceTypeBuf, 1);

	char relativeFieldBuf[1];
	memcpy(relativeFieldBuf, buf + sizeof(msgTypeBuf) + sizeof(sendDevBuf) + sizeof(recvDevBuf) + sizeof(deviceTypeBuf), sizeof(relativeFieldBuf));
	packet->relativeField = byteToint(relativeFieldBuf, 1);

	char updownFlagBuf[1];
	memcpy(updownFlagBuf, buf + sizeof(msgTypeBuf) + sizeof(sendDevBuf) + sizeof(recvDevBuf) + sizeof(deviceTypeBuf) + sizeof(relativeFieldBuf), sizeof(updownFlagBuf));
	packet->updownFlag = byteToint(updownFlagBuf, 1);

	char keyCodeBuf[4];
	memcpy(keyCodeBuf, buf + sizeof(msgTypeBuf) + sizeof(sendDevBuf) + sizeof(recvDevBuf) + sizeof(deviceTypeBuf) + sizeof(relativeFieldBuf) + sizeof(updownFlagBuf)
		, sizeof(keyCodeBuf));
	packet->keyCode = byteToint(keyCodeBuf, 4);

	return 0;
}

int CPassUDlg::ParseMouseData(char *buf, MPACKET *packet)
{
	char msgTypeBuf[4];

	memcpy(msgTypeBuf, buf, sizeof(msgTypeBuf));
	packet->msgType = byteToint(msgTypeBuf, 4);

	char sendDevBuf[4];
	memcpy(sendDevBuf, buf + sizeof(msgTypeBuf), sizeof(sendDevBuf));
	packet->sendDev = byteToint(sendDevBuf, 4);

	char recvDevBuf[4];
	memcpy(recvDevBuf, buf + sizeof(msgTypeBuf) + sizeof(sendDevBuf), sizeof(recvDevBuf));
	packet->recvDev = byteToint(recvDevBuf, 4);

	char deviceTypeBuf[1];
	memcpy(deviceTypeBuf, buf + sizeof(msgTypeBuf) + sizeof(sendDevBuf) + sizeof(recvDevBuf), sizeof(deviceTypeBuf));
	packet->deviceType = byteToint(deviceTypeBuf, 1);

	char relativeFieldBuf[1];
	memcpy(relativeFieldBuf, buf + sizeof(msgTypeBuf) + sizeof(sendDevBuf) + sizeof(recvDevBuf) + sizeof(deviceTypeBuf), sizeof(relativeFieldBuf));
	packet->relativeField = byteToint(relativeFieldBuf, 1);

	char updownFlagBuf[1];
	memcpy(updownFlagBuf, buf + sizeof(msgTypeBuf) + sizeof(sendDevBuf) + sizeof(recvDevBuf) + sizeof(deviceTypeBuf) + sizeof(relativeFieldBuf), sizeof(updownFlagBuf));
	packet->updownFlag = byteToint(updownFlagBuf, 1);

	char leftRightBuf[1];
	memcpy(leftRightBuf, buf + sizeof(msgTypeBuf) + sizeof(sendDevBuf) + sizeof(recvDevBuf) + sizeof(deviceTypeBuf) + sizeof(relativeFieldBuf) + sizeof(updownFlagBuf)
		, sizeof(leftRightBuf));
	packet->leftRight = byteToint(leftRightBuf, 1);

	char wheelFlagBuf[4];
	memcpy(wheelFlagBuf, buf + sizeof(msgTypeBuf) + sizeof(sendDevBuf) + sizeof(recvDevBuf) + sizeof(deviceTypeBuf) + sizeof(relativeFieldBuf) + sizeof(updownFlagBuf)
		+ sizeof(leftRightBuf) , sizeof(wheelFlagBuf));
	packet->wheelFlag = byteToint(wheelFlagBuf, 4);

	char xCoordBuf[4];
	memcpy(xCoordBuf, buf + sizeof(msgTypeBuf) + sizeof(sendDevBuf) + sizeof(recvDevBuf) + sizeof(deviceTypeBuf) + sizeof(relativeFieldBuf) + sizeof(updownFlagBuf)
		+ sizeof(leftRightBuf) + sizeof(wheelFlagBuf), sizeof(xCoordBuf));
	packet->xCoord = byteToint(xCoordBuf, 4);

	char yCoordBuf[4];
	memcpy(yCoordBuf, buf + sizeof(msgTypeBuf) + sizeof(sendDevBuf) + sizeof(recvDevBuf) + sizeof(deviceTypeBuf) + sizeof(relativeFieldBuf) + sizeof(updownFlagBuf)
		+ sizeof(leftRightBuf) + sizeof(wheelFlagBuf) + sizeof(xCoordBuf), sizeof(yCoordBuf));
	packet->yCoord = byteToint(yCoordBuf, 4);

	return 0;
}

int CPassUDlg::ParseClientData(char *buf, CPACKET *packet)
{
	char msgTypeBuf[4];

	memcpy(msgTypeBuf, buf, sizeof(msgTypeBuf));
	packet->msgType = byteToint(msgTypeBuf, 4);

	char c_idBuf[4];
	memcpy(c_idBuf, buf + sizeof(msgTypeBuf), sizeof(c_idBuf));
	packet->c_id = byteToint(c_idBuf, 4);

	char pad3Buf[4];
	memcpy(pad3Buf, buf + sizeof(msgTypeBuf) + sizeof(c_idBuf), sizeof(pad3Buf));
	packet->pad3 = byteToint(pad3Buf, 4);

	char helloBuf[1];
	memcpy(helloBuf, buf + sizeof(msgTypeBuf) + sizeof(c_idBuf) + sizeof(pad3Buf), sizeof(helloBuf));
	packet->hello = byteToint(helloBuf, 1);

	char byeBuf[1];
	memcpy(byeBuf, buf + sizeof(msgTypeBuf) + sizeof(c_idBuf) + sizeof(pad3Buf) + sizeof(helloBuf), sizeof(byeBuf));
	packet->bye = byteToint(byeBuf, 1);

	char ipFirstBuf[4];
	memcpy(ipFirstBuf, buf + sizeof(msgTypeBuf) + sizeof(c_idBuf) + sizeof(pad3Buf) + sizeof(helloBuf) + sizeof(byeBuf), 
		sizeof(ipFirstBuf));
	packet->ipFirst = byteToint(ipFirstBuf, 4);

	char ipSecondBuf[4];
	memcpy(ipSecondBuf, buf + sizeof(msgTypeBuf) + sizeof(c_idBuf) + sizeof(pad3Buf) + sizeof(helloBuf) + sizeof(byeBuf) 
		+ sizeof(ipFirstBuf), sizeof(ipSecondBuf));
	packet->ipSecond = byteToint(ipSecondBuf, 4);

	char ipThirdBuf[4];
	memcpy(ipThirdBuf, buf + sizeof(msgTypeBuf) + sizeof(c_idBuf) + sizeof(pad3Buf) + sizeof(helloBuf) + sizeof(byeBuf) 
		+ sizeof(ipFirstBuf) + sizeof(ipSecondBuf), sizeof(ipThirdBuf));
	packet->ipThird = byteToint(ipThirdBuf, 4);

	char ipForthBuf[4];
	memcpy(ipForthBuf, buf + sizeof(msgTypeBuf) + sizeof(c_idBuf) + sizeof(pad3Buf) + sizeof(helloBuf) + sizeof(byeBuf) 
		+ sizeof(ipFirstBuf) + sizeof(ipSecondBuf) + sizeof(ipThirdBuf), sizeof(ipForthBuf));
	packet->ipForth = byteToint(ipForthBuf, 4);

	char nWidth[5];
	memcpy(nWidth, buf + sizeof(msgTypeBuf) + sizeof(c_idBuf) + sizeof(pad3Buf) + sizeof(helloBuf) + sizeof(byeBuf) 
		+ sizeof(ipFirstBuf) + sizeof(ipSecondBuf) + sizeof(ipThirdBuf) + sizeof(ipForthBuf), sizeof(nWidth));
	packet->nWidth = byteToint(nWidth, 5);

	char nHeight[5];
	memcpy(nHeight, buf + sizeof(msgTypeBuf) + sizeof(c_idBuf) + sizeof(pad3Buf) + sizeof(helloBuf) + sizeof(byeBuf) 
		+ sizeof(ipFirstBuf) + sizeof(ipSecondBuf) + sizeof(ipThirdBuf) + sizeof(ipForthBuf) + sizeof(nWidth), sizeof(nHeight));
	packet->nHeight = byteToint(nHeight, 5);
	return 0;
}

int CPassUDlg::byteToint(char *data, int len) 
{
	int result = 0;
	for(int i = 0; i < len; i++) {
		if(data[i] == ' ')
			continue;
		result = result * 10 + (data[i] - '0');
	}
	return result;
}

void CPassUDlg::Accept(void)
{
	CPassUChildSocket *pChild = new CPassUChildSocket();

	BOOL check = m_pServer->Accept(*pChild);
	/* Nagle �˰����� �����ϴ� �ڵ�, �츮 ���α׷������� Nagle �˰��� �ʿ���� */

	const char opt_val = true;
	setsockopt(*pChild, IPPROTO_TCP, TCP_NODELAY, &opt_val, sizeof(opt_val));

	if(check == FALSE){
		AfxMessageBox(_T("Accept Failed"));
		return ;
	}

	m_pSockList.AddTail(pChild);
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
	const char opt_val = true;
	setsockopt(*m_pServer, IPPROTO_TCP, TCP_NODELAY, &opt_val, sizeof(opt_val));
	//AfxMessageBox(_T("InitServer"));
}

void CPassUDlg::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(m_SorC){
		OnStartServer();
	} else{
		OnConnectStart();
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


void CPassUDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}


void CPassUDlg::OnConnectStart(void)
{
	m_pClient = new CPassUClientSocket();
	m_pClient->Create();
	m_pClient->Connect(m_tab2.m_address, 30000);

	char buf[1024];
	ZeroMemory(buf, sizeof(buf));
	sprintf_s(buf, "%4d%4d%4d%1d%1d%4d%4d%4d%4d%5d%5d",
		MSG_CLIENT, 0, STATUS_PC, 1, 0, m_tab2.ipFirst, m_tab2.ipSecond, m_tab2.ipThird, m_tab2.ipForth, nWidth, nHeight);

	m_pClient->Send((LPCSTR *)&buf, SIZEOFPACKET); // ��� ��Ŷ ����
}


void CPassUDlg::ClientCleanUp(void)
{
	if(m_pClient)	delete m_pClient;
}


void CPassUDlg::ReceiveClientData(CPassUClientSocket * s)
{
	char buf[1024];
	ZeroMemory(buf, sizeof(buf));
	s->Receive(&buf, sizeof(buf));


	int msgType;
	char msgTypeBuf[4];
	memcpy(msgTypeBuf, buf, sizeof(msgTypeBuf));
	msgType = byteToint(msgTypeBuf, 4);

	if(msgType == MSG_KEYBOARD) {
		KPACKET packet;

		ParseKeyboardData(buf, &packet);

		if(packet.updownFlag == 1)
			keybd_event(packet.keyCode, 0, KEYEVENTF_KEYUP, 0);
		else if(packet.updownFlag == 0){ // down
			keybd_event(packet.keyCode, 0, 0, 0);
		}
	} else if(msgType == MSG_MOUSE) {
		MPACKET packet;

		ParseMouseData(buf, &packet);

		SetCursorPos(packet.xCoord, packet.yCoord);

		if(packet.leftRight == 1 && packet.updownFlag== 0){ // right up
			mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
		} else if(packet.leftRight == 1 && packet.updownFlag == 1){ // right down
			mouse_event(MOUSEEVENTF_RIGHTDOWN,  0, 0, 0, 0);
		} else if(packet.leftRight == 0 && packet.updownFlag == 0){ // left up
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		} else if(packet.leftRight == 0 && packet.updownFlag == 1){ // left down
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		}
		if(packet.wheelFlag == 1){ // wheel btn up
			mouse_event(MOUSEEVENTF_MIDDLEUP,  0, 0, 0, 0);
		} else if(packet.wheelFlag == 2){ // wheel btn down
			mouse_event(MOUSEEVENTF_MIDDLEDOWN, 0, 0, 0, 0);
		} else if(packet.wheelFlag == 3){ // wheel move
			mouse_event(MOUSEEVENTF_WHEEL,  0, 0, 0, 5);
		}
	} else if(msgType == MSG_DATA) {
		DPACKET packet;
		ZeroMemory(&packet, sizeof(DPACKET));

		memcpy(&packet.usbdesc, buf + sizeof(packet.msgType) + sizeof(packet.len), packet.len);

		COPYDATASTRUCT CDS;

		CDS.dwData = 4; // receiveData
		CDS.cbData = sizeof(DPACKET);
		CDS.lpData = &packet;
		::SendMessage(m_tab2.GetSafeHwnd(), WM_COPYDATA, 0, (LPARAM)(VOID *)&CDS);
	}
}


void CPassUDlg::CloseClient(CPassUClientSocket * s)
{
	char buf[1024];
	ZeroMemory(buf, sizeof(buf));
	sprintf_s(buf, "%4d%4d%4d%1d%1d%4d%4d%4d%4d%5d%5d",
		MSG_CLIENT, m_tab2.client_ID, STATUS_PC, 0, 1, 0, 0, 0, 0, 0, 0);

	s->Send(buf, SIZEOFPACKET); // bye ��Ŷ ����

	ClientCleanUp();
}


BOOL CPassUDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	HEVENT *hEVENT;
	MPACKET *mEVENT;

	POSITION pos = m_pSockList.GetHeadPosition();
	TRACE("WhereisPoint : %d\n", whereisPoint);
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	switch(pCopyDataStruct->dwData){
	case KEYBOARD_DATA:
		hEVENT = (tagHEVENT *) pCopyDataStruct->lpData; // hEvent ����ü ����(��ŷ�� �ڷ�)

		if(hEVENT->lParam >= 0){ // Ű�� ������ ��
			TRACE("KEY CODE ����\n");
			if(m_allowSend == TRUE){
				char buf[1024];
				ZeroMemory(buf, sizeof(buf));
				sprintf_s(buf, "%4d%4d%4d%1d%1d%1d%4d%8d",
					MSG_KEYBOARD, 0, 0, 0,
					0, hEVENT->updown, hEVENT->keyCode, 0);
				TRACE("Key Code : %d\n", hEVENT->keyCode);
				((CPassUClientSocket *)m_pSockList.GetAt(pos))->Send(buf, SIZEOFPACKET);
				break;
			}

		}
		break;

	case MOUSE_DATA:
		mEVENT = (MPACKET *)pCopyDataStruct->lpData; // mEvent ����ü ����(��ŷ�� �ڷ�)
		TRACE("MOUSE DATA ����\n");
		int i = 0;
		
				
		if(mEVENT->xCoord <= 2){ // ȭ�� ���ʿ� ���� ��
			if((whereisPoint == 5) && (m_tab1.btn_Bind[3] != 0)){ // ���ε��� 3�� �Ǿ� ���� ��(4�� ��ư)
				if(m_changeWindow == FALSE){ // scroll lock�� �ȴ����� ������
					mEVENT->xCoord = nWidth - 15;

					SetCursorPos(mEVENT->xCoord, mEVENT->yCoord);
					/*keybd_event(VK_SCROLL, 0, 0, 0);
					keybd_event(VK_SCROLL, 0, KEYEVENTF_KEYUP, 0);*/
					m_changeWindow = TRUE;
					whereisPoint = 4;
					//		currentID = 4;
					::SendMessage(m_tab1.dllWnd, WM_KEYBOARD_FALSE, 0, 0); // �� �޽����� ������ ���� Ű���� �̺�Ʈ ó���� �ȵǰ�, ������ �޾Ƹ� �´�.
					::SendMessage(m_tab1.dllWnd, WM_MOUSE_FALSE, 0, 0); // �� �޽����� ������ ���� ���콺 �̺�Ʈ ó���� �ȵǰ�, ������ �޾Ƹ� �´�.

					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32512);    // IDC_ARROW
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32513);    // IDC_IBEAM
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32514);    // IDC_WAIT
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32515);    // IDC_CROSS
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32516);    // IDC_UPARROW
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32640);    // IDC_SIZE
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32641);    // IDC_ICON
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32642);    // IDC_SIZENWSE
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32643);    // IDC_SIZENESW
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32644);    // IDC_SIZEWE
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32645);    // IDC_SIZENS
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32646);    // IDC_SIZEALL
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32648);    // IDC_NO
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32650);    // IDC_APPSTARTING
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32651);    // IDC_HELP
					m_allowSend = TRUE;
					TRACE("�����ʿ� �ִٰ� �������� ����, ���ε��� 4�� ��ư�� �Ǿ�����\n");
				}
			} else if((whereisPoint == 6) && (m_tab1.btn_Bind[5] != 0)){ // 6����ư�� ���ε��Ǿ����� ��
				if(m_changeWindow == FALSE){
					return TRUE;

				} else if(m_changeWindow == TRUE){ // scroll lock�� ������ ������
					mEVENT->xCoord = nWidth - 15;

					Sleep(1000);
					SetCursorPos(mEVENT->xCoord, mEVENT->yCoord);
					Sleep(1000);

					/*keybd_event(VK_SCROLL, 0, 0, 0);
					keybd_event(VK_SCROLL, 0, KEYEVENTF_KEYUP, 0);*/
					m_changeWindow = FALSE;
					whereisPoint = 5;
					//		currentID = 6;
					::SendMessage(m_tab1.dllWnd, WM_KEYBOARD_TRUE, 0, 0);
					::SendMessage(m_tab1.dllWnd, WM_MOUSE_TRUE, 0, 0);

					m_allowSend = FALSE;
					TRACE("6�� ��ư�� �ִٰ� �������� �پ ������ ���ƿ�, ���ε��� 6����ư�� �Ǿ� ����\n");
					// ������� ���콺 Ŀ�� ������

					//hcur_ARROW = CopyCursor(LoadCursor(NULL, IDC_ARROW));

					//::SetSystemCursor(::SetCursor(hcur_ARROW), 32512);    // IDC_ARROW
					//::SetSystemCursor(::SetCursor(hcur_IBEAM), 32513);    // IDC_IBEAM
					//::SetSystemCursor(::SetCursor(hcur_WAIT), 32514);    // IDC_WAIT
					//::SetSystemCursor(::SetCursor(hcur_CROSS), 32515);    // IDC_CROSS
					//::SetSystemCursor(::SetCursor(hcur_UPARROW), 32516);    // IDC_UPARROW
					//::SetSystemCursor(::SetCursor(hcur_SIZE), 32640);    // IDC_SIZE        
					//::SetSystemCursor(::SetCursor(hcur_ICON), 32641);    // IDC_ICON
					//::SetSystemCursor(::SetCursor(hcur_SIZENWSE), 32642);    // IDC_SIZENWSE
					//::SetSystemCursor(::SetCursor(hcur_SIZEWE), 32644);    // IDC_SIZEWE
					//::SetSystemCursor(::SetCursor(hcur_SIZENS), 32645);    // IDC_SIZENS
					//::SetSystemCursor(::SetCursor(hcur_SIZENESW), 32643);    // IDC_SIZENESW            
					//::SetSystemCursor(::SetCursor(hcur_SIZEALL), 32646);    // IDC_SIZEALL
					//::SetSystemCursor(::SetCursor(hcur_NO), 32648);    // IDC_NO    
					//::SetSystemCursor(::SetCursor(hcur_APPSTARTING), 32650);    // IDC_APPSTARTING
					//::SetSystemCursor(::SetCursor(hcur_HELP), 32651);    // IDC_HELP
				}
			}
		}

		if(mEVENT->yCoord <= 2) { // ȭ�� ���ʿ� ���� ��
			if((whereisPoint == 5) && (m_tab1.btn_Bind[1] != 0)){ // ���ε��� 2����ư��������
				if(m_changeWindow == FALSE){

					// scroll lock�� �ȴ����� ������
					mEVENT->yCoord = nHeight - 15;

					SetCursorPos(mEVENT->xCoord, mEVENT->yCoord);
					/*keybd_event(VK_SCROLL, 0, 0, 0);
					keybd_event(VK_SCROLL, 0, KEYEVENTF_KEYUP, 0);*/
				m_changeWindow = TRUE;
					
					::SendMessage(m_tab1.dllWnd, WM_KEYBOARD_FALSE, 0, 0); // �� �޽����� ������ ���� Ű���� �̺�Ʈ ó���� �ȵǰ�, ������ �޾Ƹ� �´�.
					::SendMessage(m_tab1.dllWnd, WM_MOUSE_FALSE, 0, 0); // �� �޽����� ������ ���� ���콺 �̺�Ʈ ó���� �ȵǰ�, ������ �޾Ƹ� �´�.
					whereisPoint = 2;
					//	currentID = 2;
					m_allowSend = TRUE;
					TRACE("�����ʿ� �ִٰ� �������� ����, ���ε��� 2�� ��ư�� �Ǿ� ����\n");
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32512);    // IDC_ARROW
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32513);    // IDC_IBEAM
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32514);    // IDC_WAIT
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32515);    // IDC_CROSS
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32516);    // IDC_UPARROW
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32640);    // IDC_SIZE
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32641);    // IDC_ICON
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32642);    // IDC_SIZENWSE
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32643);    // IDC_SIZENESW
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32644);    // IDC_SIZEWE
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32645);    // IDC_SIZENS
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32646);    // IDC_SIZEALL
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32648);    // IDC_NO
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32650);    // IDC_APPSTARTING
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32651);    // IDC_HELP
				}
			} else if((whereisPoint == 8) && (m_tab1.btn_Bind[7] != 0)){ // 8�� ��ư�� ���ε��Ǿ����� ��
				if(m_changeWindow == TRUE) // scroll lock�� ������ ������
				{
					mEVENT->yCoord = nHeight - 15;

					SetCursorPos(mEVENT->xCoord, mEVENT->yCoord);
				/*	keybd_event(VK_SCROLL, 0, 0, 0);
					keybd_event(VK_SCROLL, 0, KEYEVENTF_KEYUP, 0);*/
					m_changeWindow = FALSE;
					::SendMessage(m_tab1.dllWnd, WM_KEYBOARD_TRUE, 0, 0);
					::SendMessage(m_tab1.dllWnd, WM_MOUSE_TRUE, 0, 0);
					whereisPoint = 5;
					//	currentID = 8;
					m_allowSend = FALSE;
					TRACE("8�� ��ư�� �ִٰ� �������� �پ ������ ���ƿ�, ���ε��� 8����ư�� �Ǿ� ����\n");
					// ������� ���콺 Ŀ�� ������
					//::SetSystemCursor(::SetCursor(hcur_ARROW), 32512);    // IDC_ARROW
					//::SetSystemCursor(::SetCursor(hcur_IBEAM), 32513);    // IDC_IBEAM
					//::SetSystemCursor(::SetCursor(hcur_WAIT), 32514);    // IDC_WAIT
					//::SetSystemCursor(::SetCursor(hcur_CROSS), 32515);    // IDC_CROSS
					//::SetSystemCursor(::SetCursor(hcur_UPARROW), 32516);    // IDC_UPARROW
					//::SetSystemCursor(::SetCursor(hcur_SIZE), 32640);    // IDC_SIZE        
					//::SetSystemCursor(::SetCursor(hcur_ICON), 32641);    // IDC_ICON
					//::SetSystemCursor(::SetCursor(hcur_SIZENWSE), 32642);    // IDC_SIZENWSE
					//::SetSystemCursor(::SetCursor(hcur_SIZEWE), 32644);    // IDC_SIZEWE
					//::SetSystemCursor(::SetCursor(hcur_SIZENS), 32645);    // IDC_SIZENS
					//::SetSystemCursor(::SetCursor(hcur_SIZENESW), 32643);    // IDC_SIZENESW            
					//::SetSystemCursor(::SetCursor(hcur_SIZEALL), 32646);    // IDC_SIZEALL
					//::SetSystemCursor(::SetCursor(hcur_NO), 32648);    // IDC_NO    
					//::SetSystemCursor(::SetCursor(hcur_APPSTARTING), 32650);    // IDC_APPSTARTING
					//::SetSystemCursor(::SetCursor(hcur_HELP), 32651);    // IDC_HELP
				}
			}
		}

		if(mEVENT->xCoord >= nWidth - 10){	 // ȭ�� ���� �ʿ� ���� ��
			if((whereisPoint == 5) && (m_tab1.btn_Bind[5] != 0)){ // ���ε��� 6����ư�� ���� ��
				if(m_changeWindow == TRUE){
					return TRUE;
				} else if(m_changeWindow == FALSE) // scroll lock�� �ȴ����� ������
				{
					mEVENT->xCoord = 15;

					SetCursorPos(mEVENT->xCoord, mEVENT->yCoord);


					/*keybd_event(VK_SCROLL, 0, 0, 0);
					keybd_event(VK_SCROLL, 0, KEYEVENTF_KEYUP, 0);*/
					m_changeWindow = TRUE;

					::SendMessage(m_tab1.dllWnd, WM_KEYBOARD_FALSE, 0, 0); // �� �޽����� ������ ���� Ű���� �̺�Ʈ ó���� �ȵǰ�, ������ �޾Ƹ� �´�.
					::SendMessage(m_tab1.dllWnd, WM_MOUSE_FALSE, 0, 0); // �� �޽����� ������ ���� ���콺 �̺�Ʈ ó���� �ȵǰ�, ������ �޾Ƹ� �´�.
					whereisPoint = 6;
					//	currentID = 6;
					m_allowSend = TRUE;

					TRACE("�����ʿ� �ִٰ� ���������� ����, ���ε��� 6�� ��ư�� �Ǿ� ����\n");
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32512);    // IDC_ARROW
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32513);    // IDC_IBEAM
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32514);    // IDC_WAIT
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32515);    // IDC_CROSS
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32516);    // IDC_UPARROW
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32640);    // IDC_SIZE
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32641);    // IDC_ICON
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32642);    // IDC_SIZENWSE
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32643);    // IDC_SIZENESW
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32644);    // IDC_SIZEWE
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32645);    // IDC_SIZENS
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32646);    // IDC_SIZEALL
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32648);    // IDC_NO
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32650);    // IDC_APPSTARTING
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32651);    // IDC_HELP
				}

			} else if((whereisPoint == 4) && (m_tab1.btn_Bind[3] != 0)){ // ���ε��� 4�� ��ư�� ���� ��
				if(m_changeWindow == TRUE) // scroll lock�� ������ ������
				{
					mEVENT->xCoord = 15;
					SetCursorPos(mEVENT->xCoord, mEVENT->yCoord);
					/*keybd_event(VK_SCROLL, 0, 0, 0);
					keybd_event(VK_SCROLL, 0, KEYEVENTF_KEYUP, 0);*/
					m_changeWindow = FALSE;
					::SendMessage(m_tab1.dllWnd, WM_KEYBOARD_TRUE, 0, 0);
					::SendMessage(m_tab1.dllWnd, WM_MOUSE_TRUE, 0, 0);
					whereisPoint = 5;
					//	currentID = 4;
					m_allowSend = FALSE;

					// ������� ���콺 Ŀ�� ������
					//::SetSystemCursor(::SetCursor(hcur_ARROW), 32512);    // IDC_ARROW
					//::SetSystemCursor(::SetCursor(hcur_IBEAM), 32513);    // IDC_IBEAM
					//::SetSystemCursor(::SetCursor(hcur_WAIT), 32514);    // IDC_WAIT
					//::SetSystemCursor(::SetCursor(hcur_CROSS), 32515);    // IDC_CROSS
					//::SetSystemCursor(::SetCursor(hcur_UPARROW), 32516);    // IDC_UPARROW
					//::SetSystemCursor(::SetCursor(hcur_SIZE), 32640);    // IDC_SIZE        
					//::SetSystemCursor(::SetCursor(hcur_ICON), 32641);    // IDC_ICON
					//::SetSystemCursor(::SetCursor(hcur_SIZENWSE), 32642);    // IDC_SIZENWSE
					//::SetSystemCursor(::SetCursor(hcur_SIZEWE), 32644);    // IDC_SIZEWE
					//::SetSystemCursor(::SetCursor(hcur_SIZENS), 32645);    // IDC_SIZENS
					//::SetSystemCursor(::SetCursor(hcur_SIZENESW), 32643);    // IDC_SIZENESW            
					//::SetSystemCursor(::SetCursor(hcur_SIZEALL), 32646);    // IDC_SIZEALL
					//::SetSystemCursor(::SetCursor(hcur_NO), 32648);    // IDC_NO    
					//::SetSystemCursor(::SetCursor(hcur_APPSTARTING), 32650);    // IDC_APPSTARTING
					//::SetSystemCursor(::SetCursor(hcur_HELP), 32651);    // IDC_HELP        

				}

				TRACE("4�� ��ư�� �ִٰ� ���������� ���ƿ�, ���ε��� 4����ư�� �Ǿ� ����\n");
			}
		}

		if(mEVENT->yCoord >= nHeight - 10){ // ȭ�� �Ʒ��ʿ� ���� ��
			if((whereisPoint == 5) && (m_tab1.btn_Bind[7] != 0)){ // ���ε��� 8�� ��ư�� ���� ��
				if(m_changeWindow == FALSE) // scroll lock�� �ȴ����� ������
				{
					mEVENT->yCoord = 15;
					SetCursorPos(mEVENT->xCoord, mEVENT->yCoord);
					/*keybd_event(VK_SCROLL, 0, 0, 0);
					keybd_event(VK_SCROLL, 0, KEYEVENTF_KEYUP, 0);*/
					m_changeWindow = TRUE;
					whereisPoint = 8;
					//	currentID = 8;
					::SendMessage(m_tab1.dllWnd, WM_KEYBOARD_FALSE, 0, 0); // �� �޽����� ������ ���� Ű���� �̺�Ʈ ó���� �ȵǰ�, ������ �޾Ƹ� �´�.
					::SendMessage(m_tab1.dllWnd, WM_MOUSE_FALSE, 0, 0); // �� �޽����� ������ ���� ���콺 �̺�Ʈ ó���� �ȵǰ�, ������ �޾Ƹ� �´�.
					m_allowSend = TRUE;
					TRACE("�����ʿ� �ִٰ� �Ʒ������� ����, ���ε��� 8�� ��ư�� �Ǿ� ����\n");
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32512);    // IDC_ARROW
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32513);    // IDC_IBEAM
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32514);    // IDC_WAIT
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32515);    // IDC_CROSS
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32516);    // IDC_UPARROW
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32640);    // IDC_SIZE
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32641);    // IDC_ICON
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32642);    // IDC_SIZENWSE
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32643);    // IDC_SIZENESW
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32644);    // IDC_SIZEWE
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32645);    // IDC_SIZENS
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32646);    // IDC_SIZEALL
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32648);    // IDC_NO
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32650);    // IDC_APPSTARTING
					//::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32651);    // IDC_HELP
				}

			} else if((whereisPoint == 2) && (m_tab1.btn_Bind[1] != 0)){ // ���ε��� 2�� ��ư�� �Ǿ� ���� ��


				if(m_changeWindow = TRUE){ // scroll lock�� ������ ������
					mEVENT->yCoord = 15;
					SetCursorPos(mEVENT->xCoord, mEVENT->yCoord);
					/*keybd_event(VK_SCROLL, 0, 0, 0);
					keybd_event(VK_SCROLL, 0, KEYEVENTF_KEYUP, 0);*/
					m_changeWindow = FALSE;
					whereisPoint = 5;
					//		currentID = 2;
					::SendMessage(m_tab1.dllWnd, WM_KEYBOARD_TRUE, 0, 0);
					::SendMessage(m_tab1.dllWnd, WM_MOUSE_TRUE, 0, 0);
					// ������� ���콺 Ŀ�� ������
					//::SetSystemCursor(::SetCursor(hcur_ARROW), 32512);    // IDC_ARROW
					//::SetSystemCursor(::SetCursor(hcur_IBEAM), 32513);    // IDC_IBEAM
					//::SetSystemCursor(::SetCursor(hcur_WAIT), 32514);    // IDC_WAIT
					//::SetSystemCursor(::SetCursor(hcur_CROSS), 32515);    // IDC_CROSS
					//::SetSystemCursor(::SetCursor(hcur_UPARROW), 32516);    // IDC_UPARROW
					//::SetSystemCursor(::SetCursor(hcur_SIZE), 32640);    // IDC_SIZE        
					//::SetSystemCursor(::SetCursor(hcur_ICON), 32641);    // IDC_ICON
					//::SetSystemCursor(::SetCursor(hcur_SIZENWSE), 32642);    // IDC_SIZENWSE
					//::SetSystemCursor(::SetCursor(hcur_SIZEWE), 32644);    // IDC_SIZEWE
					//::SetSystemCursor(::SetCursor(hcur_SIZENS), 32645);    // IDC_SIZENS
					//::SetSystemCursor(::SetCursor(hcur_SIZENESW), 32643);    // IDC_SIZENESW            
					//::SetSystemCursor(::SetCursor(hcur_SIZEALL), 32646);    // IDC_SIZEALL
					//::SetSystemCursor(::SetCursor(hcur_NO), 32648);    // IDC_NO    
					//::SetSystemCursor(::SetCursor(hcur_APPSTARTING), 32650);    // IDC_APPSTARTING
					//::SetSystemCursor(::SetCursor(hcur_HELP), 32651);    // IDC_HELP
					m_allowSend = FALSE;
					TRACE("2���� �ִٰ� �Ʒ������� ����, ���ε��� 2�� ��ư�� �Ǿ� ����\n");
				}


			}
		}

		if(m_allowSend == TRUE){ // ��ҿ��� Ŭ���̾�Ʈ�� ������ ���ϴٰ� ������ �ƴ� �ٸ������� �������� �Ѵ�.
			// Ŭ���̾�Ʈ ��ǥ ��ȯ. 
			// ���� �ػ� : Ŭ���̾�Ʈ �ػ� = ������ǥ : Ŭ���̾�Ʈ ��ǥ �������� ��ȯ
			// Client ��ǥ = (������ǥ * Ŭ���̾�Ʈ �ػ�[ Client ID ]) / �����ػ�
			//											   Client ID = btn_Bind[ ��ư�ε��� ]

			mEVENT->xCoord = (mEVENT->xCoord * m_tab1.client_nWidth[m_tab1.btn_Bind[i]]) / nWidth;
			mEVENT->yCoord = (mEVENT->yCoord * m_tab1.client_nHeight[m_tab1.btn_Bind[i]]) / nHeight;

			char buf[1024];
			ZeroMemory(buf, sizeof(buf));
			sprintf_s(buf, "%4d%4d%4d%1d%1d%1d%1d%4d%4d%4d%8d",
				MSG_MOUSE, mEVENT->sendDev, mEVENT->recvDev, mEVENT->deviceType,
				mEVENT->relativeField, mEVENT->updownFlag, mEVENT->leftRight, mEVENT->wheelFlag, mEVENT->xCoord, mEVENT->yCoord, 0);
			TRACE("x : %d, y : %d\n", mEVENT->xCoord, mEVENT->yCoord);

			((CPassUClientSocket *)m_pSockList.GetAt(pos))->Send(buf, SIZEOFPACKET);
		}

		break;
	}
	return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}


BOOL CPassUDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_ESCAPE) return TRUE;
		if(pMsg->wParam == VK_RETURN) return TRUE;
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}
