// ServerConf.cpp : ���� �����Դϴ�.
//

#include <afxwin.h>
#include "stdafx.h"
#include "test.h"
#include "ServerConf.h"
#include "afxdialogex.h"
#include "MyThread.h"
#include "packet.h"

// ServerConf ��ȭ �����Դϴ�.

typedef HHOOK (*InstallKeyboardHook)();
typedef HHOOK (*InstallMouseHook)();

typedef void (*UnInstallKeyboardHook)();
typedef void  (*UnInstallMouseHook)();

InstallKeyboardHook installKeyhook;
InstallMouseHook installMousehook;

UnInstallKeyboardHook uninstallKeyhook;
UnInstallMouseHook uninstallMousehook;
IMPLEMENT_DYNAMIC(ServerConf, CDialogEx)

	ServerConf::ServerConf(CWnd* pParent /*=NULL*/)
	: CDialogEx(ServerConf::IDD, pParent)
	, m_serverPortEdit(_T(""))
	, serverIPAddress(_T(""))
{
	TRACE("�ʱ�ȭ �ڵ� - ������\n");
	/* ���� ������ �� ��ǻ���� IP�� �˾Ƴ��� �ڵ� */
	WORD wVersionRequested;
	WSADATA wsaData;
	char name[255];
	PHOSTENT hostinfo;
	CString strIpAddress;
	wVersionRequested = MAKEWORD(2, 0);
	if(WSAStartup(wVersionRequested, &wsaData) == 0)
	{
		if(gethostname(name, sizeof(name)) == 0)
		{
			if((hostinfo = gethostbyname(name)) != NULL)
				strIpAddress = inet_ntoa (*(struct in_addr *)*hostinfo->h_addr_list);
		} 
		WSACleanup();
	}
	serverIPAddress.Append(strIpAddress); // static control�� ���� IP �ּҸ� �ٿ�����
	initFlag(); // ���� Flag �ʱ�ȭ

	hinstDLL = NULL;
	hHook = NULL;
	cThread = NULL;
	tmp = NULL;

	hinstDLL = LoadLibrary(_T("KeyHook.dll"));
	if(!hinstDLL)
		AfxMessageBox(_T("KeyHook.dll �ε� ����!"));

	installKeyhook = (InstallKeyboardHook)GetProcAddress(hinstDLL, "InstallKeyboardHook");
	installMousehook = (InstallMouseHook)GetProcAddress(hinstDLL, "InstallMouseHook");

	uninstallKeyhook = (UnInstallKeyboardHook)GetProcAddress(hinstDLL, "UnInstallKeyboardHook");
	uninstallMousehook = (UnInstallMouseHook)GetProcAddress(hinstDLL, "UnInstallMouseHook");


	AfxSocketInit(); // ���� �ʱ�ȭ
}

ServerConf::~ServerConf()
{

}

void ServerConf::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, m_serverPortEdit);
	DDX_Control(pDX, IDC_BUTTON1, m_CButton_one);
	DDX_Control(pDX, IDC_BUTTON2, m_CButton_two);
	DDX_Control(pDX, IDC_BUTTON3, m_CButton_three);
	DDX_Control(pDX, IDC_BUTTON4, m_CButton_four);
	DDX_Control(pDX, IDC_BUTTON5, m_CButton_five);
	DDX_Control(pDX, IDC_BUTTON6, m_CButton_six);
	DDX_Control(pDX, IDC_BUTTON7, m_CButton_seven);
	DDX_Control(pDX, IDC_BUTTON8, m_CButton_eight);
	DDX_Control(pDX, IDC_BUTTON9, m_CButton_nine);

	DDX_Control(pDX, IDC_BUTTON12, m_CButton_portApply);
	DDX_Control(pDX, IDC_BUTTON13, m_CButton_portCancel);
	DDX_Control(pDX, IDC_EDIT2, m_portEditControl);
	DDX_Text(pDX, IDC_IPTEXT, serverIPAddress);
	DDX_Control(pDX, IDOK, m_CBtn_Start);
	DDX_Control(pDX, IDCANCEL, m_CBtn_stop);
}


BEGIN_MESSAGE_MAP(ServerConf, CDialogEx)
	ON_BN_CLICKED(IDOK, &ServerConf::OnBnClickedStart)
	ON_BN_CLICKED(IDCANCEL, &ServerConf::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON12, &ServerConf::OnBnClickedPortApply)
	ON_BN_CLICKED(IDC_BUTTON13, &ServerConf::OnBnClickedPortCancel)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON1, &ServerConf::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &ServerConf::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &ServerConf::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &ServerConf::OnBnClickedButton4)
	//ON_BN_CLICKED(IDC_BUTTON5, &ServerConf::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &ServerConf::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &ServerConf::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &ServerConf::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &ServerConf::OnBnClickedButton9)
	//	ON_WM_KEYDOWN()
	ON_WM_COPYDATA()
	ON_BN_CLICKED(IDC_BUTTON14, &ServerConf::OnBnClickedButton14)
END_MESSAGE_MAP()


// ServerConf �޽��� ó�����Դϴ�.


void ServerConf::OnBnClickedStart()
{
	TRACE("---------------------------Start Button Click---------------------------\n");
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(m_applyFlag == FALSE){
		AfxMessageBox(_T("Plz Enter Port Number !!"));
		return ;
	}

	int nPort;

	nPort = _ttoi(m_serverPortEdit);

	AfxMessageBox(_T("Start!!"));

	m_startFlag = TRUE;

	initServer(nPort);

	m_CBtn_Start.EnableWindow(FALSE);


}
void ServerConf::initServer(int nPort)
 {
	TRACE("---------------------------initServer---------------------------\n");
	listen.Create(nPort);
	listen.Listen();

	m_startFlag = TRUE; // ���� ���� �÷��� True
	AfxMessageBox(_T("Accept Complete"));
}

void ServerConf::OnBnClickedCancel()
{
	TRACE("---------------------------OnBnClickedCancel---------------------------\n");
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	initFlag();

	uninstallKeyhook();
	uninstallMousehook();

	//tmp = &listen.m_sockList; // ������ ����Ʈ ������
	//int count = tmp->GetCount();
	//POSITION pos = tmp->GetHeadPosition(); // �� ó�� ��带 ��������

	//clientP.msgType = 3;
	//clientP.hello = 0;
	//clientP.bye = 1; // bye ��Ŷ

	//while(pos != NULL){
	//	cThread = (CMyThread *)tmp->GetAt(pos);

	//	cThread->m_mySocket->Send((LPCSTR)&clientP, sizeof(CPACKET));


	//	tmp->GetNext(pos);
	//}

	//tmp->RemoveAll();

	//tmp = NULL;
	CDialogEx::OnCancel();
}


void ServerConf::OnBnClickedPortApply()
{
	TRACE("---------------------------OnBnClickedPortApply---------------------------\n");
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UpdateData();
	CString str;

	GetDlgItemText(IDC_EDIT2, str);

	if(str.GetLength() == 0){
		AfxMessageBox(_T("��Ʈ ��ȣ�� �Է��ϼ���."));
		return ;
	}

	m_applyFlag = TRUE;
	m_portEditControl.EnableWindow(FALSE);
	m_CButton_portApply.EnableWindow(FALSE);
	//AfxMessageBox(m_serverPortEdit);
}


void ServerConf::OnBnClickedPortCancel()
{
	TRACE("---------------------------OnBnClickedPortCancel---------------------------\n");
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_CButton_portApply.EnableWindow(TRUE);
	m_portEditControl.EnableWindow(TRUE);
}


void ServerConf::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	TRACE("---------------------------OnLButtonDown---------------------------\n");
	picControl[0] = this->GetDlgItem(IDC_PICCOM);
	picControl[1] = this->GetDlgItem(IDC_PICPHN);

	picControl[0]->GetWindowPlacement(&getCoord[9]);
	picControl[1]->GetWindowPlacement(&getCoord[10]);

	if(point.x >= getCoord[9].rcNormalPosition.left && 
		point.x <= getCoord[9].rcNormalPosition.right && 
		point.y >= getCoord[9].rcNormalPosition.top && 
		point.y <= getCoord[9].rcNormalPosition.bottom){ // �����
			m_deviceFlag = 0;
			SetCapture();
			m_bDragFlag = true;
			//	AfxMessageBox(_T("Monitor"));
			RedrawWindow(); 
	} else if (point.x >= getCoord[10].rcNormalPosition.left && 
		point.x <= getCoord[10].rcNormalPosition.right && 
		point.y >= getCoord[10].rcNormalPosition.top && 
		point.y <= getCoord[10].rcNormalPosition.bottom){ // ����Ʈ��
			m_deviceFlag = 1;
			SetCapture();
			m_bDragFlag = true;
			//	AfxMessageBox(_T("Smart Phone"));
			RedrawWindow(); 
	} else{
		m_deviceFlag = -1;
		m_bDragFlag = false;
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}


void ServerConf::OnLButtonUp(UINT nFlags, CPoint point)
{
	TRACE("---------------------------OnLButtonUp---------------------------\n");
	CPoint m_tmpPoint;
	CBitmap m_tmpBitmap;

	btnControl[0] = this->GetDlgItem(IDC_BUTTON1);
	btnControl[1] = this->GetDlgItem(IDC_BUTTON2);
	btnControl[2] = this->GetDlgItem(IDC_BUTTON3);
	btnControl[3] = this->GetDlgItem(IDC_BUTTON4);
	btnControl[4] = this->GetDlgItem(IDC_BUTTON5);
	btnControl[5] = this->GetDlgItem(IDC_BUTTON6);
	btnControl[6] = this->GetDlgItem(IDC_BUTTON7);
	btnControl[7] = this->GetDlgItem(IDC_BUTTON8);
	btnControl[8] = this->GetDlgItem(IDC_BUTTON9);

	for(int i = 0 ; i < 9 ; i ++)
		btnControl[i]->GetWindowPlacement(&getCoord[i]);


	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if(m_bDragFlag == TRUE){
		m_bDragFlag = FALSE;

		m_ptltemText = point;
		RedrawWindow();
		ReleaseCapture();

		if(point.x >= getCoord[0].rcNormalPosition.left &&
			point.x <= getCoord[0].rcNormalPosition.right &&
			point.y <= getCoord[0].rcNormalPosition.bottom &&
			point.y >= getCoord[0].rcNormalPosition.top){ // �巡�� ���� ���� ��ư 1�� ��

				// ó���� Ŭ���� �׸��� ����Ʈ������ ��ǻ������ �ɷ�����
				// ��ǻ���̸� ��ư�� ��ǻ�� ����, ����Ʈ���̸� ��ư�� ����Ʈ�� ����


				if(m_deviceFlag == 0){ // ��ǻ��
					m_tmpBitmap.LoadBitmapW(IDB_BITMAP1);
					m_settingFlag[0] = 0;
				} else if(m_deviceFlag == 1){ // ����Ʈ��
					m_tmpBitmap.LoadBitmapW(IDB_BITMAP2);
					m_settingFlag[0] =  1;
				} else{ // �� �� �ƴϸ� �׳� ����6
					m_settingFlag[0] = -1;
					return;
				}

				m_CButton_one.SetBitmap(m_tmpBitmap); // ��ư�� �̹��� �ε�

				UpdateData();Invalidate();RedrawWindow();
				// 
		} else if(point.x >= getCoord[1].rcNormalPosition.left &&
			point.x <= getCoord[1].rcNormalPosition.right &&
			point.y <= getCoord[1].rcNormalPosition.bottom &&
			point.y >= getCoord[1].rcNormalPosition.top){ // �巡�� ���� ���� ��ư 2�� ��
				if(m_deviceFlag == 0){ // ��ǻ��
					m_tmpBitmap.LoadBitmapW(IDB_BITMAP1);


					m_settingFlag[1] = 0;
				} else if(m_deviceFlag == 1){ // ����Ʈ��
					m_tmpBitmap.LoadBitmapW(IDB_BITMAP2);
					m_settingFlag[1] = 1;
				} else{ // �� �� �ƴϸ� �׳� ����

					m_settingFlag[1] = -1;
					return;
				}

				m_CButton_two.SetBitmap(m_tmpBitmap); // ��ư�� �̹��� �ε�				

				UpdateData();Invalidate();RedrawWindow();
		} else if(point.x >= getCoord[2].rcNormalPosition.left &&
			point.x <= getCoord[2].rcNormalPosition.right &&
			point.y <= getCoord[2].rcNormalPosition.bottom &&
			point.y >= getCoord[2].rcNormalPosition.top){ // �巡�� ���� ���� ��ư 3�� ��
				if(m_deviceFlag == 0){ // ��ǻ��
					m_tmpBitmap.LoadBitmapW(IDB_BITMAP1);

					m_settingFlag[2] = 0;
				} else if(m_deviceFlag == 1){ // ����Ʈ��
					m_tmpBitmap.LoadBitmapW(IDB_BITMAP2);

					m_settingFlag[2] = 1;
				} else{ // �� �� �ƴϸ� �׳� ����

					m_settingFlag[2] = -1;
					return;
				}
				m_CButton_three.SetBitmap(m_tmpBitmap); // ��ư�� �̹��� �ε�


				UpdateData();Invalidate();RedrawWindow();
		} else if(point.x >= getCoord[3].rcNormalPosition.left &&
			point.x <= getCoord[3].rcNormalPosition.right &&
			point.y <= getCoord[3].rcNormalPosition.bottom &&
			point.y >= getCoord[3].rcNormalPosition.top){ // �巡�� ���� ���� ��ư 4�� ��
				if(m_deviceFlag == 0){ // ��ǻ��
					m_tmpBitmap.LoadBitmapW(IDB_BITMAP1);

					m_settingFlag[3] = 0;
				} else if(m_deviceFlag == 1){ // ����Ʈ��

					m_settingFlag[3] = 1;
					m_tmpBitmap.LoadBitmapW(IDB_BITMAP2);
				} else{ // �� �� �ƴϸ� �׳� ����

					m_settingFlag[3] = -1;
					return;
				}

				m_CButton_four.SetBitmap(m_tmpBitmap); // ��ư�� �̹��� �ε�


				UpdateData();Invalidate();RedrawWindow();
		} /*else if(point.x >= getCoord[4].rcNormalPosition.left &&
		  //	point.x <= getCoord[4].rcNormalPosition.right &&
		  //	point.y <= getCoord[4].rcNormalPosition.bottom &&
		  //	point.y >= getCoord[4].rcNormalPosition.top){ // �巡�� ���� ���� ��ư 5�� ��
		  //		if(m_deviceFlag == 0){ // ��ǻ��
		  //			m_tmpBitmap.LoadBitmapW(IDB_BITMAP1);

		  //			m_settingFlag[4] = 0;
		  //		} else if(m_deviceFlag == 1){ // ����Ʈ��

		  //			m_settingFlag[4] = 1;
		  //			m_tmpBitmap.LoadBitmapW(IDB_BITMAP2);
		  //		} else{ // �� �� �ƴϸ� �׳� ����

		  //			m_settingFlag[4] = -1;
		  //			return;
		  //		}
		  //		//	m_CButton_five.SetWindowText(NULL);

		  //		m_CButton_five.SetBitmap(m_tmpBitmap); // ��ư�� �̹��� �ε�


		  //		UpdateData();Invalidate();RedrawWindow();
		  }*/ else if(point.x >= getCoord[5].rcNormalPosition.left &&
		  point.x <= getCoord[5].rcNormalPosition.right &&
		  point.y <= getCoord[5].rcNormalPosition.bottom &&
		  point.y >= getCoord[5].rcNormalPosition.top){ // �巡�� ���� ���� ��ư 6�� ��
			  if(m_deviceFlag == 0){ // ��ǻ��
				  m_tmpBitmap.LoadBitmapW(IDB_BITMAP1);

				  m_settingFlag[5] = 0;
			  } else if(m_deviceFlag == 1){ // ����Ʈ��
				  m_tmpBitmap.LoadBitmapW(IDB_BITMAP2);

				  m_settingFlag[5] = 1;
			  } else{ // �� �� �ƴϸ� �׳� ����

				  m_settingFlag[5] = -1;
				  return;
			  }
			  m_CButton_six.SetBitmap(m_tmpBitmap); // ��ư�� �̹��� �ε�

			  UpdateData();Invalidate();RedrawWindow();
		} else if(point.x >= getCoord[6].rcNormalPosition.left &&
			point.x <= getCoord[6].rcNormalPosition.right &&
			point.y <= getCoord[6].rcNormalPosition.bottom &&
			point.y >= getCoord[6].rcNormalPosition.top){ // �巡�� ���� ���� ��ư 7�� ��
				if(m_deviceFlag == 0){ // ��ǻ��
					m_tmpBitmap.LoadBitmapW(IDB_BITMAP1);

					m_settingFlag[6] = 0;
				} else if(m_deviceFlag == 1){ // ����Ʈ��
					m_tmpBitmap.LoadBitmapW(IDB_BITMAP2);

					m_settingFlag[6] = 1;

				} else{ // �� �� �ƴϸ� �׳� ����

					m_settingFlag[6] = -1;
					return;
				}
				m_CButton_seven.SetBitmap(m_tmpBitmap); // ��ư�� �̹��� �ε�

				UpdateData();Invalidate();RedrawWindow();
		} else if(point.x >= getCoord[7].rcNormalPosition.left &&
			point.x <= getCoord[7].rcNormalPosition.right &&
			point.y <= getCoord[7].rcNormalPosition.bottom &&
			point.y >= getCoord[7].rcNormalPosition.top){ // �巡�� ���� ���� ��ư 8�� ��
				if(m_deviceFlag == 0){ // ��ǻ��
					m_tmpBitmap.LoadBitmapW(IDB_BITMAP1);

					m_settingFlag[7] = 0;
				} else if(m_deviceFlag == 1){ // ����Ʈ��
					m_tmpBitmap.LoadBitmapW(IDB_BITMAP2);

					m_settingFlag[7] = 1;

				} else{ // �� �� �ƴϸ� �׳� ����

					m_settingFlag[7] = -1;
					return;

				}
				m_CButton_eight.SetBitmap(m_tmpBitmap); // ��ư�� �̹��� �ε�


				UpdateData();
				Invalidate();RedrawWindow();
		} else if(point.x >= getCoord[8].rcNormalPosition.left &&
			point.x <= getCoord[8].rcNormalPosition.right &&
			point.y <= getCoord[8].rcNormalPosition.bottom &&
			point.y >= getCoord[8].rcNormalPosition.top){ // �巡�� ���� ���� ��ư 9�� ��
				if(m_deviceFlag == 0){ // ��ǻ��
					m_tmpBitmap.LoadBitmapW(IDB_BITMAP1);

					m_settingFlag[8] = 0;
				} else if(m_deviceFlag == 1){ // ����Ʈ��
					m_tmpBitmap.LoadBitmapW(IDB_BITMAP2);

					m_settingFlag[8] = 1;
				} else{ // �� �� �ƴϸ� �׳� ����

					m_settingFlag[8] = -1;
					return;
				}

				m_CButton_nine.SetBitmap(m_tmpBitmap); // ��ư�� �̹��� �ε�


				UpdateData();
				Invalidate();RedrawWindow();
		} else { // �簢��(��ư) �Ʒ��� �ƴϸ� �׳� ����

			return ; 
		}

	}
	CDialogEx::OnLButtonUp(nFlags, point);
}


void ServerConf::OnMouseMove(UINT nFlags, CPoint point)
{
	//	TRACE("---------------------------OnMouseMove---------------------------\n");
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	CClientDC dc(this);
	CString str;

	//	str.Format(_T("��ġ : %d %d"), point.x, point.y);
	//	AfxMessageBox(str);
	if(m_bDragFlag == true){

		//RedrawWindow();

		//dc.TextOutW(point.x, point.y, str);
	}
	CDialogEx::OnMouseMove(nFlags, point);
}



void ServerConf::OnBnClickedButton1()
{
	TRACE("---------------------------OnBnClickedButton1---------------------------");
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(m_settingFlag[0] != -1){
		if(AfxMessageBox(_T("�����Ͻðڽ��ϱ�?"), MB_YESNO | MB_ICONQUESTION)==IDYES)
		{
			m_CButton_one.SetBitmap(NULL);
			m_CButton_one.SetWindowText(_T("1"));
			m_deviceFlag = -1;
			m_settingFlag[0] = -1;
			RedrawWindow();
		}
	}
}


void ServerConf::OnBnClickedButton2()
{TRACE("---------------------------OnBnClickedButton2---------------------------");
// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
if(m_settingFlag[1] != -1){
	if(AfxMessageBox(_T("�����Ͻðڽ��ϱ�?"), MB_YESNO | MB_ICONQUESTION)==IDYES)
	{
		m_CButton_two.SetBitmap(NULL);
		m_CButton_two.SetWindowText(_T("2"));
		m_deviceFlag = -1;
		m_settingFlag[1] = -1;
		RedrawWindow();
	}
}
}


void ServerConf::OnBnClickedButton3()
{TRACE("---------------------------OnBnClickedButton3---------------------------");
// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
if(m_settingFlag[2] != -1){
	if(AfxMessageBox(_T("�����Ͻðڽ��ϱ�?"), MB_YESNO | MB_ICONQUESTION)==IDYES)
	{
		m_CButton_three.SetBitmap(NULL);
		m_CButton_three.SetWindowText(_T("3"));
		m_deviceFlag = -1;
		m_settingFlag[2] = -1;
		RedrawWindow();
	}
}
}


void ServerConf::OnBnClickedButton4()
{TRACE("---------------------------OnBnClickedButton4---------------------------");
// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
if(m_settingFlag[3] != -1){
	if(AfxMessageBox(_T("�����Ͻðڽ��ϱ�?"), MB_YESNO | MB_ICONQUESTION)==IDYES)
	{
		m_CButton_four.SetBitmap(NULL);
		m_CButton_four.SetWindowText(_T("4"));
		m_deviceFlag = -1;
		m_settingFlag[3] = -1;
		RedrawWindow();
	}
}
}


//void ServerConf::OnBnClickedButton5()
//{
//	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
//	if(m_settingFlag[4] != -1){
//		if(AfxMessageBox(_T("�����Ͻðڽ��ϱ�?"), MB_YESNO | MB_ICONQUESTION)==IDYES)
//		{
//			m_CButton_five.SetBitmap(NULL);
//			m_CButton_five.SetWindowText(_T("5"));
//			m_deviceFlag = -1;
//			m_settingFlag[4] = -1;
//			RedrawWindow();
//		}
//	}
//}


void ServerConf::OnBnClickedButton6()
{TRACE("---------------------------OnBnClickedButton6---------------------------");
// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
if(m_settingFlag[5] != -1){
	if(AfxMessageBox(_T("�����Ͻðڽ��ϱ�?"), MB_YESNO | MB_ICONQUESTION)==IDYES)
	{
		m_CButton_six.SetBitmap(NULL);
		m_CButton_six.SetWindowText(_T("6"));
		m_deviceFlag = -1;
		m_settingFlag[5] = -1;
		RedrawWindow();
	}
}
}


void ServerConf::OnBnClickedButton7()
{TRACE("---------------------------OnBnClickedButton7---------------------------");
// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
if(m_settingFlag[6] != -1){
	if(AfxMessageBox(_T("�����Ͻðڽ��ϱ�?"), MB_YESNO | MB_ICONQUESTION)==IDYES)
	{
		m_CButton_seven.SetBitmap(NULL);
		m_CButton_seven.SetWindowText(_T("7"));
		m_deviceFlag = -1;
		m_settingFlag[6] = -1;
		RedrawWindow();
	}
}
}


void ServerConf::OnBnClickedButton8()
{TRACE("---------------------------OnBnClickedButton8---------------------------");
// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
if(m_settingFlag[7] != -1){
	if(AfxMessageBox(_T("�����Ͻðڽ��ϱ�?"), MB_YESNO | MB_ICONQUESTION)==IDYES)
	{
		m_CButton_eight.SetBitmap(NULL);
		m_CButton_eight.SetWindowText(_T("8"));
		m_deviceFlag = -1;
		m_settingFlag[7] = -1;
		RedrawWindow();
	}
}
}


void ServerConf::OnBnClickedButton9()
{TRACE("---------------------------OnBnClickedButton9---------------------------");
// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
if(m_settingFlag[8] != -1){
	if(AfxMessageBox(_T("�����Ͻðڽ��ϱ�?"), MB_YESNO | MB_ICONQUESTION)==IDYES)
	{
		m_CButton_nine.SetBitmap(NULL);
		m_CButton_nine.SetWindowText(_T("9"));
		m_deviceFlag = -1;
		m_settingFlag[8] = -1;
		RedrawWindow();
	}
}
}

void ServerConf::closeClient(CMySocket *s)
{
	TRACE("---------------------------closeClient---------------------------");
	if(m_startFlag == TRUE){
		m_startFlag = FALSE;

		AfxMessageBox(_T("Close Success!!"));

		//m_CBtn_Start.EnableWindow(TRUE);
	}
}

void ServerConf::receiveData(CMySocket *s) // ���⼭ ���ڱ� m_settingFlag, nSocket, client_id �� ���� �ٲ��. ��? ���� �ٲ��� ��Ȳ�� ���µ�...
{

	TRACE("%d\n", nSocket);
	TRACE("---------------------------receiveData---------------------------\n");
	KPACKET tmp;
	//initFlag();
	s->Receive((LPCSTR *)&tmp, sizeof(KPACKET));

	unpackMessage(tmp, s);

	AfxMessageBox(_T("receive Success!!")); 
}


void ServerConf::initFlag(void)
{
	TRACE("---------------------------initFlag---------------------------");
	nSocket = 0;
	m_applyFlag = FALSE;
	m_bDragFlag = FALSE;
	m_deviceFlag = -1;
	for(int i = 0 ; i < 9 ; i++ ){
		m_settingFlag[i] = -1;
		client_id[i] = 0;
	}
	m_settingFlag[4] = 0;

	m_startFlag = TRUE;
	m_whereisPoint = 5; // �⺻�� 5 ( ������ ��ġ )
	m_keyBoardHook = FALSE;
	m_mouseHook = FALSE;

	tmp = NULL;
	cThread = NULL;
}




BOOL ServerConf::PreTranslateMessage(MSG* pMsg) // PostMessage�� �޾� Parsing�ϴ� �Լ�.......................................................
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	return CDialogEx::PreTranslateMessage(pMsg);
}


//void ServerConf::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
//{
//	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
//
//	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
//}



KPACKET ServerConf::packMessage(int msgType, int sendDev, int recvDev, int devType, int relativeField, int updownFlag, int pad1, int keyCode, int pad2, int pad3){
	TRACE("---------------------------packMessage---------------------------");
	KPACKET k;
	k.msgType = 0;
	k.sendDev = 0;
	k.recvDev = 0;
	k.deviceType = 0;
	k.relativeField = 0;
	k.updownFlag = 0;;
	k.pad1 = 0;
	k.keyCode = 0;
	k.pad2 = 0;
	k.pad3 = 0;
	switch(msgType){
	case 1: // Keyboard
		k.msgType = msgType;
		k.sendDev = sendDev;
		k.recvDev = recvDev;
		k.deviceType = devType;
		k.relativeField = relativeField;
		k.updownFlag = updownFlag;;
		k.pad1 = pad1;
		k.keyCode = keyCode;
		k.pad2 = pad2;
		k.pad3 = pad3;

	case 2: // Mouse
		MPACKET m;
		m.msgType = msgType;
		m.sendDev = sendDev;
		m.recvDev = recvDev;
		m.deviceType = devType;
		m.relativeField = relativeField;
		m.updownFlag = updownFlag;
		m.leftRight = pad1;
		m.wheelFlag = keyCode;
		m.xCoord = pad2;
		m.yCoord = pad3;

		memcpy(&k, &m, sizeof(KPACKET));


	case 3: // Client
		CPACKET c;
		c.msgType = msgType;
		c.c_id = sendDev;
		c.pad3 = recvDev;
		c.hello = devType;
		c.bye = relativeField;
		c.pad4 = updownFlag;
		c.pad5 = pad1;
		c.pad6 = keyCode;
		c.pad7 = pad2;
		c.pad8 = pad3;

		memcpy(&k, &c, sizeof(KPACKET));

		break;

	case 4: // Server
		DPACKET d;
		d.msgType = msgType;
		d.len = sendDev;

		memcpy(&k, &d, sizeof(KPACKET));
		break;

	default: // packing ����
		AfxMessageBox(_T("Msg Packing Failed"));
		break;
	}

	return k;


}

void ServerConf::unpackMessage(KPACKET p, CMySocket *s){
	TRACE("---------------------------unpackMessage---------------------------\n");
	switch(p.msgType){
	case 1: // Keyboard
		/*		k.deviceType = p.deviceType;
		k.keyCode = p.keyCode;
		k.msgType = p.msgType;
		k.sendDev = p.sendDev;
		k.recvDev = p.recvDev;
		k.updownFlag = p.updownFlag;
		k.relativeField = p.relativeField;*/

		break;

	case 2: // Mouse

		//m.deviceType = p.deviceType;
		//m.msgType = p.msgType;
		//m.sendDev = p.sendDev;
		//m.recvDev = p.recvDev;
		//m.relativeField = p.relativeField;
		//m.updownFlag = p.updownFlag;
		//m.wheelFlag = p.pad1;
		//m.xCoord = p.keyCode;
		//m.yCoord = p.pad2;

		break;

	case 3: // Client
		CPACKET c;

		c.c_id = p.sendDev;
		c.msgType = p.msgType;
		c.hello = p.deviceType;
		c.bye = p.relativeField;

		if(c.hello == 1){ // ��� ��Ŷ�� ��� �� Ŭ���̾�Ʈ id�� �˷��ش�.

			nSocket += 1;

			for(int i = 0 ; i < 9 ; i ++){ // Ŭ���̾�Ʈ id�� ��ư ����
				if((m_settingFlag[i] != -1) && (i != 4) && (client_id[i] == 0)){
					if(nSocket > 4){
						client_id[i] = (nSocket + 1); //server(5) ������ Ŭ���̾�Ʈ ������ �ϳ� ���� ���� Ŭ���̾�Ʈ id�� �ȴ�.
						break;
					} else if(nSocket <= 4){
						client_id[i] = nSocket;
						break;
					}
				}
			}
			TRACE("after nSocket : %d\n", nSocket);
			c.hello = 0;
			keyP = packMessage(3, nSocket, 0, 1, 0, 0, 0, 0, 0, 0);
			TRACE("unpackMessage nSocket : %d\n", nSocket);

			s->Send((LPCSTR)&keyP, sizeof(KPACKET));

			if(nSocket == 1){
				installKeyhook();
				installMousehook();
			}
		}

		if(c.bye == 1){ // bye ��Ŷ�� ���
			nSocket -= 1;

			client_id[c.c_id - 1] = 0;

			if(nSocket == 0){
				initFlag();
				uninstallKeyhook();
				uninstallMousehook();
			}
		}

		//	PostMessage(WM_CLIENT_MESSAGE, 0, 0);

		break;

	case 4: // Server
		DPACKET d;

		d.msgType = p.msgType;
		d.len = p.sendDev;
		//		PostMessage(WM_SERVER_MESSAGE, 0, 0);

		break;

	default: // unpacking ����
		AfxMessageBox(_T("Unpacking Failed!"));
	}

	return ;
}

BOOL ServerConf::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	TRACE("---------------------------OnCopyData---------------------------\n");
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	HEVENT *hEVENT; 
	MPACKET *mEVENT;
	int nWidth = GetSystemMetrics(SM_CXSCREEN);
	int nHeight = GetSystemMetrics(SM_CYSCREEN);
	HWND dllWnd = FindWindowA(NULL, "MsgWnd");
	TRACE("nWidth : %d, nHeight : %d\n", nWidth, nHeight);

	tmp = &listen.m_sockList; // ������ ����Ʈ ������
	int count = tmp->GetCount();
	POSITION pos = tmp->GetHeadPosition(); // �� ó�� ��带 ��������
	//TRACE("count : %d\n", count);
	switch(pCopyDataStruct -> dwData){

	case 0: // keyboard
		hEVENT = (tagHEVENT *) pCopyDataStruct->lpData; // hEvent ����ü ����(��ŷ�� �ڷ�)

		if(hEVENT->lParam >= 0){ // Ű�� ������ ��

			keyP.deviceType = 1;
			keyP.msgType = 1;
			keyP.keyCode = hEVENT->keyCode;

			//for(int i = 0 ; i < 9 ; i ++){
			//	tmp->GetNext(pos);
			//	if((m_whereisPoint == i) && (i != 5)){ // 
			//		cThread = (CMyThread *)tmp->GetAt(pos);
			//		cThread->m_mySocket->Send((LPCSTR)&keyP, sizeof(KPACKET));
			//	}
			//}
		}
		break;
	case 1: // ���콺 ������ ������
		mEVENT = (MPACKET *)pCopyDataStruct->lpData; // mEvent ����ü ����(��ŷ�� �ڷ�)
		if(mEVENT->xCoord <= 2){ // ȭ�� ���ʿ� ���� ��
			TRACE("m_whereisPoint : %d, client_id[3] : %d, m_settingflag[3] : %d\n", m_whereisPoint, m_settingFlag[3], client_id[3]);

			if(m_whereisPoint == 5 && m_settingFlag[3] != -1 && client_id[3] != 0){ // 4�� ��ư�� ���� �ʾҰ�, ���� �ʿ� ����Ʈ�� ������,
				m_whereisPoint = 4; // 4�� ��ư���� ����Ʈ�� �ű� �� ���콺 �̵� 
				mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, (nWidth - 15)* 65535 / nWidth, mEVENT->yCoord * 65535 / nHeight, 0, 0);

				// ���콺 Ŀ�� ���ְ� Ű����, ���콺 �̺�Ʈ ó�� ���� �����ϰ� ����



			} else if(m_whereisPoint == 6){ // ���� 6���� �����Ͱ� �־��ٸ�
				m_whereisPoint = 5; // ���������� ����Ʈ�� �ű� �� ���콺 �̵�
				mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, (nWidth - 15)* 65535 / nWidth, mEVENT->yCoord * 65535 / nHeight, 0, 0);

				// ���콺 Ŀ�� ����ϰ� ���콺, Ű���� ���� �ٽ� �̺�Ʈ �޵��� ��


			} else
				return true;
			//for(int i = 0 ; i < client_id[3] - 1; i ++){ // �̰�... 0���� �����ϴ°Ŵϱ� id�� ������ 1��ŭ �۰� for���� ���ƾ� ��Ȯ�� pos�� ���´�.
			//	tmp->GetNext(pos);
			//}

			//cThread = (CMyThread *)tmp->GetAt(pos);
			//cThread->m_mySocket->Send((LPCSTR)&keyP, sizeof(KPACKET));
		} 

		if(mEVENT->yCoord<= 2) { // ȭ�� ������ ���� ��
			TRACE("m_whereisPoint : %d, client_id[1] : %d, m_settingflag[1] : %d\n", m_whereisPoint, m_settingFlag[1], client_id[1]);

			if(m_whereisPoint == 5 && m_settingFlag[1] != -1 && client_id[1] != 0){ // 2�� ��ư�� ���� �ʾҰ�, ���� �ʿ� ����Ʈ�� ������,
				m_whereisPoint = 2; // 2�� ��ư���� �ű� �� ���콺 �̵�
				mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, mEVENT->xCoord * 65535 / nWidth, (nHeight - 15) * 65535 / nHeight, 0, 0);

				// ���콺 Ŀ�� ���ְ� Ű����, ���콺 �̺�Ʈ ó�� ���� �����ϰ� ����


			} else if(m_whereisPoint == 8){ // 8���� �����Ͱ� �־��ٸ�
				m_whereisPoint = 5; // ������ư���� �ű� �� ���콺 �̵�
				mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, mEVENT->xCoord * 65535 / nWidth, (nHeight - 15) * 65535 / nHeight, 0, 0);


				// ���콺 Ŀ�� ����ϰ� ���콺, Ű���� ���� �ٽ� �̺�Ʈ �޵��� ��



			} else
				return true;

			//for(int i = 0 ; i < client_id[1] - 1; i ++){ // �̰�... 0���� �����ϴ°Ŵϱ� id�� ������ 1��ŭ �۰� for���� ���ƾ� ��Ȯ�� pos�� ���´�.
			//	tmp->GetNext(pos);
			//}
			//cThread = (CMyThread *)tmp->GetAt(pos);
			//cThread->m_mySocket->Send((LPCSTR)&keyP, sizeof(KPACKET));

		} 

		if(mEVENT->xCoord >= nWidth - 2){	 // ȭ�� ���� �ʿ� ���� ��
			TRACE("m_whereisPoint : %d, client_id[5] : %d, m_settingflag[5] : %d\n", m_whereisPoint, m_settingFlag[5], client_id[5]);

			if(m_whereisPoint == 5 && m_settingFlag[5] != -1 && client_id[5] != 0){ // 6�� ��ư�� ���� �ʾҰ�, ���� �ʿ� ����Ʈ�� ������,
				m_whereisPoint = 6;
				mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, 15 * 65535 / nWidth, mEVENT->yCoord * 65535 / nHeight, 0, 0);

				// ���콺 Ŀ�� ���ְ� Ű����, ���콺 �̺�Ʈ ó�� ���� �����ϰ� ����
				


			} else if(m_whereisPoint == 4){
				m_whereisPoint = 5;
				mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, 15 * 65535 / nWidth, mEVENT->yCoord * 65535 / nHeight, 0, 0);

				// ���콺 Ŀ�� ����ϰ� ���콺, Ű���� ���� �ٽ� �̺�Ʈ �޵��� ��


			}else
				return true;

			//for(int i = 0 ; i < client_id[5] - 1; i ++){ // �̰�... 0���� �����ϴ°Ŵϱ� id�� ������ 1��ŭ �۰� for���� ���ƾ� ��Ȯ�� pos�� ���´�.
			//	tmp->GetNext(pos);
			//}
			//cThread = (CMyThread *)tmp->GetAt(pos);
			//cThread->m_mySocket->Send((LPCSTR)&keyP, sizeof(KPACKET));
		} 

		if(mEVENT->yCoord >= nHeight - 2){ // ȭ�� �Ʒ��ʿ� ���� ��
			TRACE("m_whereisPoint : %d, client_id[7] : %d, m_settingflag[7] : %d\n", m_whereisPoint, m_settingFlag[7], client_id[7]);

			if(m_whereisPoint == 5 && m_settingFlag[7] != -1 && client_id[7] != 0){ // 8�� ��ư�� ���� �ʾҰ�, ���� �ʿ� ����Ʈ�� ������,
				m_whereisPoint = 8;
				mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, mEVENT->xCoord * 65535 / nWidth, 15 * 65535 / nHeight, 0, 0);

				// ���콺 Ŀ�� ���ְ� Ű����, ���콺 �̺�Ʈ ó�� ���� �����ϰ� ����


			} else if(m_whereisPoint == 2){
				m_whereisPoint = 5;
				mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, mEVENT->xCoord * 65535 / nWidth, 15 * 65535 / nHeight, 0, 0);


				// ���콺 Ŀ�� ����ϰ� ���콺, Ű���� ���� �ٽ� �̺�Ʈ �޵��� ��


			}else
				return true;


			//for(int i = 0 ; i < client_id[7] - 1; i ++){ // �̰�... 0���� �����ϴ°Ŵϱ� id�� ������ 1��ŭ �۰� for���� ���ƾ� ��Ȯ�� pos�� ���´�.
			//	tmp->GetNext(pos);
			//}	
			//cThread = (CMyThread *)tmp->GetAt(pos);
			//cThread->m_mySocket->Send((LPCSTR)&keyP, sizeof(KPACKET));

		}
		break;
	}

	tmp = NULL;
	cThread = NULL;


	return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}

void ServerConf::OnBnClickedButton14() // ���� Stop�ϴ� �Լ�
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	initFlag();
	m_CBtn_Start.EnableWindow(TRUE);
	uninstallKeyhook();
	uninstallMousehook();

}
