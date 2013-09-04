
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
	nWidth = GetSystemMetrics(SM_CXSCREEN);
	nHeight = GetSystemMetrics(SM_CYSCREEN);

	m_pwndShow = &m_tab1;
	whereisPoint = 5;
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
			/* Nagle �˰����� �����ϴ� �ڵ�, �츮 ���α׷������� Nagle �˰��� �ʿ���� */
	
	const char opt_val = true;
	setsockopt(*pChild, IPPROTO_TCP, TCP_NODELAY, &opt_val, sizeof(opt_val));

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
	const char opt_val = true;
	setsockopt(*m_pServer, IPPROTO_TCP, TCP_NODELAY, &opt_val, sizeof(opt_val));
	AfxMessageBox(_T("InitServer"));
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
	CPACKET tmp;

	m_pClient = new CPassUClientSocket();
	m_pClient->Create();
	m_pClient->Connect(m_tab2.m_address, 30000);

	tmp.msgType = 3;
	tmp.bye = 0;
	tmp.c_id = 0;
	tmp.hello = 1;

	tmp.pad3 = STATUS_PC;

	tmp.pad6 = m_tab2.ipFirst;
	tmp.pad7 = m_tab2.ipSecond;
	tmp.pad8 = m_tab2.ipThird;
	tmp.pad9 = m_tab2.ipForth;

	m_pClient->Send((LPCSTR *)&tmp, sizeof(CPACKET)); // ��� ��Ŷ ����


}


void CPassUDlg::ClientCleanUp(void)
{
	if(m_pClient)	delete m_pClient;
}


void CPassUDlg::ReceiveClientData(CPassUClientSocket * s)
{
	PACKET tmp;

	s->Receive(&tmp, sizeof(PACKET));

	if(tmp.msgType == MSG_KEYBOARD){
		if(tmp.updownFlag == 1) // up
			keybd_event(tmp.keyCode, 0, KEYEVENTF_KEYUP, 0);

		else if(tmp.updownFlag == 0) // down
			keybd_event(tmp.keyCode, 0, 0, 0);

		TRACE("Keybd_event success\n");
		return ;
	} else if(tmp.msgType == MSG_MOUSE){
		if(tmp.pad2 > nWidth)
			tmp.pad2 = nWidth;
		if(tmp.pad3 > nHeight)
			tmp.pad3 = nHeight;

		mouse_Move(tmp.pad2, tmp.pad3);

		if(tmp.pad1 == 1 && tmp.updownFlag== 0){ // right up
			mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
		} else if(tmp.pad1 == 1 && tmp.updownFlag == 1){ // right down
			mouse_event(MOUSEEVENTF_RIGHTDOWN,  0, 0, 0, 0);
		} else if(tmp.pad1 == 0 && tmp.updownFlag == 0){ // left up
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		} else if(tmp.pad1 == 0 && tmp.updownFlag == 1){ // left down
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
		}
		if(tmp.keyCode == 2){ // wheel btn up
			mouse_event(MOUSEEVENTF_MIDDLEUP,  0, 0, 0, 0);
		} else if(tmp.keyCode == 2){ // wheel btn down
			mouse_event(MOUSEEVENTF_MIDDLEDOWN, 0, 0, 0, 0);
		} else if(tmp.keyCode == 3){ // wheel move
			mouse_event(MOUSEEVENTF_WHEEL,  0, 0, 120, 0);
		}
		TRACE("mouse_event success\n");
		return ;
	}

	COPYDATASTRUCT CDS;

	CDS.dwData = 0; // Client receiveData
	CDS.cbData = sizeof(PACKET);
	CDS.lpData = &tmp;


	::SendMessage(m_tab2.GetSafeHwnd(), WM_COPYDATA, 0, (LPARAM)(VOID *)&CDS);

}


void CPassUDlg::CloseClient(CPassUClientSocket * s)
{
	CPACKET tmp;
	tmp.msgType = 3;
	tmp.c_id = m_tab2.client_ID;
	tmp.bye = 1;
	tmp.hello = 0;


	s->Send((LPCSTR *)&tmp, sizeof(CPACKET)); // bye ��Ŷ ����

	ClientCleanUp();
}


BOOL CPassUDlg::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	HEVENT *hEVENT;
	MPACKET *mEVENT;

	

	// Client���� ������ ����ü(K,M : ��ŷ�ڷ�)
	KPACKET keyP;
	MPACKET mouseP;

	COPYDATASTRUCT CDS;
	POSITION pos = m_pSockList.GetHeadPosition();
	TRACE("WhereisPoint : %d\n", whereisPoint);
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	switch(pCopyDataStruct->dwData){
	case KEYBOARD_DATA:
		hEVENT = (tagHEVENT *) pCopyDataStruct->lpData; // hEvent ����ü ����(��ŷ�� �ڷ�)

		if(hEVENT->lParam >= 0){ // Ű�� ������ ��
			TRACE("KEY CODE ����\n");

			for(int i = 0 ; i < 9 ; i ++){
				//TRACE("m_tab1.btn_Bind[i] : %d\n", m_tab1.btn_Bind[i]);
				if((m_tab1.btn_Bind[i]) != 0){
					keyP.deviceType = 1;
					keyP.msgType = MSG_KEYBOARD;
					keyP.keyCode = hEVENT->keyCode;
					keyP.updownFlag = hEVENT->updown;
					((CPassUClientSocket *)m_pSockList.GetAt(pos))->Send((LPCSTR *)&keyP, sizeof(KPACKET));
					break;
				} 
			}
		}
		break;

	case MOUSE_DATA:
		mEVENT = (MPACKET *)pCopyDataStruct->lpData; // mEvent ����ü ����(��ŷ�� �ڷ�)
		TRACE("MOUSE DATA ����\n");
		for(int i = 0 ; i < 9 ; i ++){
			//TRACE("m_tab1.btn_Bind[i] : %d\n", m_tab1.btn_Bind[i]);
			if((m_tab1.btn_Bind[i]) != 0){
				if(mEVENT->xCoord <= 2){ // ȭ�� ���ʿ� ���� ��
					if(whereisPoint == 5){ // ���ε��� 3�� �Ǿ� ���� ��(4�� ��ư)
						mEVENT->xCoord = nWidth - 15;
						mouse_Move(mEVENT->xCoord, mEVENT->yCoord);
				//		whereisPoint = 4;
						//SetCursor(NULL);
					//	ShowCursor(FALSE);

						// m_tab1.btn_bind[4] = 1; -> ������ �ƴ� �ٸ� ���� Ŀ���� ����.
						// mouseevent ���������� ���̻� �׳� �������ְ� �׷��� �ϵ���
						// ��ǥ���̶� �̺�Ʈ�� ������ �״�� ���ְ�.
					} else if(whereisPoint == 6){//mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, (nWidth - 15)* 65535 / nWidth, mEVENT->yCoord * 65535 / nHeight, 0, 0);
						mEVENT->xCoord = nWidth - 15;
						mouse_Move(mEVENT->xCoord, mEVENT->yCoord);
				//		whereisPoint = 5;
						//	SetCursor();
					//	ShowCursor(TRUE);		
					}
				}

				if(mEVENT->yCoord<= 2) { // ȭ�� ������ ���� ��
					if(whereisPoint == 5){ // ���ε��� 2����ư��������
						mEVENT->yCoord = nHeight - 15;
						mouse_Move(mEVENT->xCoord, mEVENT->yCoord);
						//			mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, mEVENT->xCoord * 65535 / nWidth, (nHeight - 15) * 65535 / nHeight, 0, 0);
					//	whereisPoint = 2;
					//	ShowCursor(FALSE);
					} else if(whereisPoint == 8){
						mEVENT->yCoord = nHeight - 15;
						mouse_Move(mEVENT->xCoord, mEVENT->yCoord);
						//			mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, mEVENT->xCoord * 65535 / nWidth, (nHeight - 15) * 65535 / nHeight, 0, 0);
				//		whereisPoint = 5;
				//		ShowCursor(TRUE);

					}
				} 

				if(mEVENT->xCoord >= nWidth - 2){	 // ȭ�� ���� �ʿ� ���� ��
					//	m_whereisPoint = 6;
					if(whereisPoint == 5){ // ���ε��� 6����ư�� ���� ��
						mEVENT->xCoord = 15;
						mouse_Move(mEVENT->xCoord, mEVENT->yCoord);
					//	whereisPoint = 6;
						//ShowCursor(FALSE);
					} else if(whereisPoint == 4){
						mEVENT->xCoord = 15;
						mouse_Move(mEVENT->xCoord, mEVENT->yCoord);
					//	whereisPoint = 5;
						//ShowCursor(TRUE);

					}
				}

				if(mEVENT->yCoord >= nHeight - 2){ // ȭ�� �Ʒ��ʿ� ���� ��
					if(whereisPoint == 5){ // ���ε��� 8�� ��ư�� ���� ��
						mEVENT->yCoord = 15;
						mouse_Move(mEVENT->xCoord, mEVENT->yCoord);
					//	whereisPoint = 8;
					//	ShowCursor(FALSE);
					} else if(whereisPoint == 2){
						mEVENT->yCoord = 15;
						mouse_Move(mEVENT->xCoord, mEVENT->yCoord);
					//	whereisPoint = 5;
					//	ShowCursor(TRUE);

					}
				}

				TRACE("%d %d\n", mEVENT->xCoord, mEVENT->yCoord);


				mouseP.msgType = MSG_MOUSE;
				mouseP.deviceType = mEVENT->deviceType;
				mouseP.leftRight = mEVENT->leftRight;
				mouseP.wheelFlag = mEVENT->wheelFlag;
				mouseP.updownFlag = mEVENT->updownFlag;
				mouseP.xCoord = mEVENT->xCoord;
				mouseP.yCoord = mEVENT->yCoord;

				((CPassUClientSocket *)m_pSockList.GetAt(pos))->Send((LPCSTR *)&mouseP, sizeof(MPACKET));
				break;
			} 
		}
		break;
	}
	return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}


BOOL CPassUDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	if(pMsg->message  == WM_KEYDOWN)
		return TRUE;



	return CDialogEx::PreTranslateMessage(pMsg);
}


void CPassUDlg::mouse_Move(int x, int y)
{
   x = (65535 * x / GetSystemMetrics(SM_CXSCREEN));

   y = (65535 * y / GetSystemMetrics(SM_CYSCREEN));

   

   mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE,x,y,0,NULL);

}
