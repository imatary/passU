
// PassUDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "PassU.h"
#include "PassUDlg.h"
#include "afxdialogex.h"
#include "PassUClientSocket.h"
#include <Dbt.h>

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
	ShowCursorAll();

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

	m_SorC = TRUE;
	m_pwndShow = &m_tab1;
	whereisPoint = 5;
	UpdateData(FALSE);

	// �ڽ��� ȭ�� ���ϱ�
	nWidth = GetSystemMetrics(SM_CXSCREEN);
	nHeight = GetSystemMetrics(SM_CYSCREEN);

	// ó������ Ŭ���̾�Ʈ�� ������ ������ �ʴ´�.
	m_allowSend = FALSE;

	currentPoint.x = 0;
	currentPoint.y = 0;
	oldPoint.x = 0;
	oldPoint.y = 0;

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
}

void CPassUDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}

	// if((nID & 0xFFF0) == SC_MINIMIZE) ShowWindow(SW_HIDE);

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

void CPassUDlg::ShowCursorAll() {
	SystemParametersInfo(SPI_SETCURSORS, 0, NULL, 0);
}

void CPassUDlg::HideCursorAll() {
	::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32512);    // IDC_ARROW
	::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32513);    // IDC_IBEAM
	::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32514);    // IDC_WAIT
	::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32515);    // IDC_CROSS
	::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32516);    // IDC_UPARROW
	::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32640);    // IDC_SIZE        
	::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32641);    // IDC_ICON
	::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32642);    // IDC_SIZENWSE
	::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32644);    // IDC_SIZEWE
	::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32645);    // IDC_SIZENS
	::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32643);    // IDC_SIZENESW            
	::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32646);    // IDC_SIZEALL
	::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32648);    // IDC_NO    
	::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32650);    // IDC_APPSTARTING
	::SetSystemCursor(::LoadCursorFromFile("trans.cur"), 32651);    // IDC_HELP
}

void CPassUDlg::DestroyCursorAll() {
	SystemParametersInfo(SPI_SETCURSORS, 0, NULL, 0);
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

	ParseData(buf, len);

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

		if(oldPoint.x == 0 && oldPoint.y == 0) {
			oldPoint.x = packet.xCoord;
			oldPoint.y = packet.yCoord;
		} else if( abs(oldPoint.x - packet.xCoord) > nWidth / 2 ||
			abs(oldPoint.y - packet.yCoord) > nHeight / 2 ) {
				return -1;
		}

		oldPoint.x = packet.xCoord;
		oldPoint.y = packet.yCoord;
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
	if(m_SorC){
		m_pServer->Close();
		if(m_pServer)	delete m_pServer;

		m_tab1.m_waiting_client.DeleteAllItems();

		for(int i = 0 ; i < 9 ; i ++){
			int tmp = m_tab1.btn_Bind[i];
			m_tab1.btn_Bind[i] = 0;
			m_tab1.m_cBtn[i].SetBitmap(NULL);
			m_tab1.client_nWidth[i] = 0;
			m_tab1.client_nHeight[i] = 0;
			m_tab1.clientInfo[i].clientID = 0;
			m_tab1.clientInfo[i].setIP("0.0.0.0");
			m_tab1.clientInfo[i].setPosition(0);
			m_tab1.clientInfo[i].setStatus(STATUS_EMPTY);
		}

		UpdateData();
		Invalidate();

		CPassUChildSocket *pChild;

		while(!m_pSockList.IsEmpty()){
			pChild = (CPassUChildSocket *)m_pSockList.RemoveHead();
			delete pChild;
		}

		m_pSockList.RemoveAll();

		if(m_pServer)	delete m_pServer;

	} else{
		CPACKET tmp;

		tmp.bye = 1;
		tmp.c_id = m_tab2.client_ID;
		tmp.hello = 0;
		tmp.msgType = 3;

		char buf[1024];
		ZeroMemory(buf, sizeof(buf));
		sprintf_s(buf, "%4d%4d%4d%1d%1d%4d%4d%4d%4d%5d%5d",
			MSG_CLIENT, m_tab2.client_ID, STATUS_PC, 0, 1, 0, 0, 0, 0, 0, 0);

		COPYDATASTRUCT CDS;

		CDS.dwData = 2;
		CDS.cbData = sizeof(CPACKET);
		CDS.lpData = &tmp;


		::SendMessage(m_tab2.GetSafeHwnd(), WM_COPYDATA, 0, (LPARAM)(VOID *)&CDS);

		if(m_pClient)	delete m_pClient;
	}
}

void CPassUDlg::CloseChild(CPassUChildSocket *s){ // Ŭ���̾�Ʈ�ʿ��� �����Ͽ��� �� ȣ��Ǵ� �Լ�

	CPassUChildSocket *pChild;
	POSITION pos = m_pSockList.GetHeadPosition();

	CString tmpStr;
	DestroyCursorAll();
	m_allowSend = FALSE;
	::SendMessage(m_tab1.dllWnd, WM_KEYBOARD_TRUE, 0, 0);
	::SendMessage(m_tab1.dllWnd, WM_MOUSE_TRUE, 0, 0);

	for(int i = 0 ; i < 9 ; i ++){
		if(m_tab1.clientInfo[i].clientID == s->c_id){

			m_tab1.m_cBtn[((m_tab1.clientInfo[i]).getPosition())].SetBitmap(NULL);

			UpdateData();
			Invalidate();

			m_tab1.btn_Bind[(m_tab1.clientInfo[i]).getPosition()] = 0;


			tmpStr.Format(_T("%d , IP : %s"), m_tab1.clientInfo[i].clientID, m_tab1.clientInfo[i].m_address);
			// ����Ʈ ��Ʈ�ѿ��� ����
			LVFINDINFO find_item;
			find_item.flags = LVFI_STRING;
			find_item.psz = tmpStr;

			int index = m_tab1.m_waiting_client.FindItem(&find_item);
			if(-1 != index)	m_tab1.m_waiting_client.DeleteItem(index);

			m_tab1.clientInfo[i].setID(0);
			m_tab1.clientInfo[i].setIP("0.0.0.0");
			m_tab1.clientInfo[i].setPosition(0);
			m_tab1.clientInfo[i].setStatus(STATUS_EMPTY);
			break;
		}
	}

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

	//Nagle �˰��� ����
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

	m_CBtn_Stop.EnableWindow(TRUE);
}

void CPassUDlg::OnBnClickedButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	m_CBtn_Start.EnableWindow(TRUE);
	m_CBtn_Stop.EnableWindow(FALSE);

	CleanUp();
	//CDialog::OnCancel();
}

void CPassUDlg::OnDestroy()
{
	if(m_SorC){ // Server�� ��
		CleanUp();
	} else{
		CleanUp();
	}
	DestroyCursorAll();
	CDialogEx::OnDestroy();
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}

void CPassUDlg::OnConnectStart(void)
{
	m_pClient = new CPassUClientSocket();
	m_pClient->Create();
	m_pClient->Connect(m_tab2.m_address, 30000);

	m_tab1.strIpAddress;

	int ipFirst = 0, ipSecond = 0, ipThird = 0, ipForth = 0;
	int i = 0;

	while(m_tab1.strIpAddress.GetAt(i) != '.' ){
		ipFirst = ipFirst * 10 + (m_tab1.strIpAddress.GetAt(i) - '0');
		i ++ ;
	}

	i ++ ;

	while(m_tab1.strIpAddress.GetAt(i) != '.'){
		ipSecond = ipSecond * 10 + (m_tab1.strIpAddress.GetAt(i) - '0');
		i ++ ;
	}

	i ++ ;

	while(m_tab1.strIpAddress.GetAt(i) != '.'){
		ipThird = ipThird * 10 + (m_tab1.strIpAddress.GetAt(i) - '0');
		i ++ ;
	}

	i ++ ;

	while(m_tab1.strIpAddress.GetAt(i) != '.' && (m_tab1.strIpAddress.GetLength() != i)){
		ipForth = ipForth * 10 + (m_tab1.strIpAddress.GetAt(i) - '0');
		i ++ ;
	}


	char buf[1024];
	ZeroMemory(buf, sizeof(buf));
	sprintf_s(buf, "%4d%4d%4d%1d%1d%4d%4d%4d%4d%5d%5d",
		MSG_CLIENT, 0, STATUS_PC, 1, 0, ipFirst, ipSecond, ipThird, ipForth, nWidth, nHeight);

	m_pClient->Send((LPCSTR *)&buf, SIZEOFPACKET); // ��� ��Ŷ ����
}

void CPassUDlg::ClientCleanUp(void)
{

}

void CPassUDlg::ReceiveClientData(CPassUClientSocket * s)
{
	char buf[4096];
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
	} else if(msgType == MSG_CLIENT){
		CPACKET packet;
		ZeroMemory( &packet, sizeof(CPACKET));
		ParseClientData(buf, &packet);

		COPYDATASTRUCT CDS;

		CDS.dwData = 3; // client
		CDS.cbData = sizeof(CPACKET);
		CDS.lpData = &packet;
		::SendMessage(m_tab2.GetSafeHwnd(), WM_COPYDATA, 0, (LPARAM)(VOID *)&CDS);

	} else if(msgType == MSG_DATA) {
		DPACKET packet;
		ZeroMemory(&packet, sizeof(DPACKET));

		packet.msgType = msgType;

		char lenBuf[4];
		memcpy(lenBuf, buf + sizeof(packet.msgType), sizeof(lenBuf));
		packet.len = byteToint(lenBuf, 4);

		memcpy(&packet.usbdesc, buf + sizeof(packet.msgType) + sizeof(packet.len), packet.len);

		COPYDATASTRUCT CDS;

		CDS.dwData = 4; // receiveData
		CDS.cbData = sizeof(DPACKET);
		CDS.lpData = &packet;
		::SendMessage(m_tab2.GetSafeHwnd(), WM_COPYDATA, 0, (LPARAM)(VOID *)&CDS);
	} else if(msgType == MSG_REMOVE_USB) {
		DPACKET packet;
		ZeroMemory(&packet, sizeof(DPACKET));

		COPYDATASTRUCT CDS;

		CDS.dwData = 2; // receiveData
		CDS.cbData = sizeof(DPACKET);
		CDS.lpData = &packet;
		::SendMessage(m_tab2.GetSafeHwnd(), WM_COPYDATA, 0, (LPARAM)(VOID *)&CDS);
	}
}

void CPassUDlg::CloseClient(CPassUClientSocket * s)
{
	COPYDATASTRUCT CDS;
	CPACKET tmp;

	CDS.dwData = 2;
	CDS.cbData = sizeof(CPACKET);
	CDS.lpData = &tmp;

	::SendMessage(m_tab2.GetSafeHwnd(), WM_COPYDATA, 0, (LPARAM)(VOID *)&CDS);

	m_pClient->Close();
	if(m_pClient)	delete m_pClient;
	m_tab2.m_cBtn_connect.EnableWindow(TRUE);
	m_tab2.ipFirst = 0;
	m_tab2.ipSecond = 0;
	m_tab2.ipThird = 0;
	m_tab2.ipForth = 0;
	m_tab2.m_IpAddressCtrl.ClearAddress();

	m_tab2.m_connectFlag = false;
	m_CBtn_Start.EnableWindow(TRUE);
	m_CBtn_Stop.EnableWindow(TRUE);
}

BOOL CPassUDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	HEVENT *hEVENT;
	MPACKET *mEVENT;

	POSITION pos = m_pSockList.GetHeadPosition();
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	switch(pCopyDataStruct->dwData){
	case KEYBOARD_DATA:
		hEVENT = (tagHEVENT *) pCopyDataStruct->lpData; // hEvent ����ü ����(��ŷ�� �ڷ�)

		if(hEVENT->lParam >= 0){ // Ű�� ������ ��
			if(m_allowSend == TRUE){
				char buf[1024];
				ZeroMemory(buf, sizeof(buf));
				sprintf_s(buf, "%4d%4d%4d%1d%1d%1d%4d%8d",
					MSG_KEYBOARD, 0, 0, 0,
					0, hEVENT->updown, hEVENT->keyCode, 0);

				CPassUChildSocket *s = (CPassUChildSocket *)m_pSockList.GetAt(pos);

				while((m_tab1.btn_Bind[whereisPoint - 1] != s->c_id) && (pos != NULL)){
					(CPassUChildSocket *)m_pSockList.GetNext(pos);
					s = (CPassUChildSocket *)m_pSockList.GetAt(pos);
				}

				((CPassUChildSocket *)m_pSockList.GetAt(pos))->Send(buf, SIZEOFPACKET);
				break;
			}
		}
		break;

	case MOUSE_DATA:
		mEVENT = (MPACKET *)pCopyDataStruct->lpData; // mEvent ����ü ����(��ŷ�� �ڷ�)
		int i = 0;

		if(mEVENT->xCoord <= 2){ // ȭ�� ���ʿ� ���� ��
			if((whereisPoint == 5) && (m_tab1.btn_Bind[3] != 0)){ // ���ε��� 3�� �Ǿ� ���� ��(4�� ��ư)
				mEVENT->xCoord = nWidth - 20;
				OnArrivedScreenEdge(mEVENT, TRUE, 4);
				m_allowSend = TRUE;
			} else if((whereisPoint == 6) && (m_tab1.btn_Bind[5] != 0)){ // 6����ư�� ���ε��Ǿ����� ��
				m_allowSend = FALSE;
				mEVENT->xCoord = nWidth - 20;
				OnArrivedScreenEdge(mEVENT, FALSE, 5);
			}
		} else if(mEVENT->yCoord <= 2) { // ȭ�� ���ʿ� ���� ��
			if((whereisPoint == 5) && (m_tab1.btn_Bind[1] != 0)){ // ���ε��� 2����ư��������
				mEVENT->yCoord = nHeight - 20;
				OnArrivedScreenEdge(mEVENT, TRUE, 2);
				m_allowSend = TRUE;
			} else if((whereisPoint == 8) && (m_tab1.btn_Bind[7] != 0)){ // 8�� ��ư�� ���ε��Ǿ����� ��
				m_allowSend = FALSE;
				mEVENT->yCoord = nHeight - 20;
				OnArrivedScreenEdge(mEVENT, FALSE, 5);
			}
		} else if(mEVENT->xCoord >= nWidth - 2){	 // ȭ�� ���� �ʿ� ���� ��
			if((whereisPoint == 5) && (m_tab1.btn_Bind[5] != 0)){ // ���ε��� 6����ư�� ���� ��
				mEVENT->xCoord = 20;
				OnArrivedScreenEdge(mEVENT, TRUE, 6);
				m_allowSend = TRUE;
			} else if((whereisPoint == 4) && (m_tab1.btn_Bind[3] != 0)){ // ���ε��� 4�� ��ư�� ���� ��
				m_allowSend = FALSE;
				mEVENT->xCoord = 20;
				OnArrivedScreenEdge(mEVENT, FALSE, 5);
			}
		} else if(mEVENT->yCoord >= nHeight - 2){ // ȭ�� �Ʒ��ʿ� ���� ��
			if((whereisPoint == 5) && (m_tab1.btn_Bind[7] != 0)){ // ���ε��� 8�� ��ư�� ���� ��
				m_allowSend = TRUE;
				mEVENT->yCoord = 20;
				OnArrivedScreenEdge(mEVENT, TRUE, 8);
			} else if((whereisPoint == 2) && (m_tab1.btn_Bind[1] != 0)){ // ���ε��� 2�� ��ư�� �Ǿ� ���� ��
				mEVENT->yCoord = 20;
				OnArrivedScreenEdge(mEVENT, FALSE, 5);
				m_allowSend = FALSE;
			}
		}

		if(m_allowSend == TRUE){ // ��ҿ��� Ŭ���̾�Ʈ�� ������ ���ϴٰ� ������ �ƴ� �ٸ������� �������� �Ѵ�.
			// Ŭ���̾�Ʈ ��ǥ ��ȯ. 
			// ���� �ػ� : Ŭ���̾�Ʈ �ػ� = ������ǥ : Ŭ���̾�Ʈ ��ǥ �������� ��ȯ
			// Client ��ǥ = (������ǥ * Ŭ���̾�Ʈ �ػ�[ Client ID ]) / �����ػ�
			//											   Client ID = btn_Bind[ ��ư�ε��� ]
			mEVENT->xCoord = (mEVENT->xCoord * m_tab1.client_nWidth[m_tab1.btn_Bind[whereisPoint - 1]]) / nWidth;
			mEVENT->yCoord = (mEVENT->yCoord * m_tab1.client_nHeight[m_tab1.btn_Bind[whereisPoint - 1]]) / nHeight;

			char buf[1024];
			ZeroMemory(buf, sizeof(buf));
			sprintf_s(buf, "%4d%4d%4d%1d%1d%1d%1d%4d%4d%4d%8d",
				MSG_MOUSE, mEVENT->sendDev, mEVENT->recvDev, mEVENT->deviceType,
				mEVENT->relativeField, mEVENT->updownFlag, mEVENT->leftRight, mEVENT->wheelFlag, mEVENT->xCoord, mEVENT->yCoord, 0);
			TRACE("x : %d, y : %d\n", mEVENT->xCoord, mEVENT->yCoord);
			CPassUChildSocket * s = (CPassUChildSocket *)m_pSockList.GetAt(pos);

			while((m_tab1.btn_Bind[whereisPoint - 1] != s->c_id) && (pos != NULL)){
				(CPassUChildSocket *)m_pSockList.GetNext(pos);
				s =  ((CPassUChildSocket *)m_pSockList.GetAt(pos));
			}

			((CPassUChildSocket *)m_pSockList.GetAt(pos))->Send(buf, SIZEOFPACKET);
		}

		break;
	}
	return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}

void CPassUDlg::OnArrivedScreenEdge(MPACKET *packet, BOOL bClient, int position)
{
	if(bClient == TRUE) {
		::SendMessage(m_tab1.dllWnd, WM_KEYBOARD_FALSE, 0, 0);
		::SendMessage(m_tab1.dllWnd, WM_MOUSE_FALSE, 0, 0);

		HideCursorAll();
	} else {
		::SendMessage(m_tab1.dllWnd, WM_KEYBOARD_TRUE, 0, 0);
		::SendMessage(m_tab1.dllWnd, WM_MOUSE_TRUE, 0, 0);

		ShowCursorAll();
	}

	whereisPoint = position;		
}

BOOL CPassUDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if(pMsg->message == WM_KEYDOWN)
	{
		if(pMsg->wParam == VK_ESCAPE) return TRUE;
		if(pMsg->wParam == VK_RETURN) return TRUE;
	} 

	return CDialogEx::PreTranslateMessage(pMsg);
}


LRESULT CPassUDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
		if(m_SorC == TRUE && message == WM_DEVICECHANGE /*&& m_pSockList.GetCount() != 0*/){
			TRACE("USB �Ⱦ���\n");
			USBDeviceChange(wParam, lParam);
		}
	return CDialogEx::DefWindowProc(message, wParam, lParam);
}

BOOL CPassUDlg::USBDeviceChange(UINT uEvent, DWORD dwEventData)
{
	COPYDATASTRUCT CDS;
	CPACKET packet;

	switch (uEvent)
	{
	case DBT_DEVICEARRIVAL:
		// ���ο� ��ġ �߻�
		CDS.dwData = 5; // Send New Device
		CDS.cbData = sizeof(CPACKET);
		CDS.lpData = &packet;
		::SendMessage(m_tab1.GetSafeHwnd(), WM_COPYDATA, 0, (LPARAM)(VOID *)&CDS);
		break;
	case DBT_DEVICEREMOVECOMPLETE:
		// ��ġ ���� ����
		CPACKET packet;
		CDS.dwData = 6; // Remove Device
		CDS.cbData = sizeof(CPACKET);
		CDS.lpData = &packet;
		::SendMessage(m_tab1.GetSafeHwnd(), WM_COPYDATA, 0, (LPARAM)(VOID *)&CDS);
		break;
	default:
		break;
	}
	return TRUE;
}