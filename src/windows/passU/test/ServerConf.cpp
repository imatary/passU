// ServerConf.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "test.h"
#include "ServerConf.h"
#include "afxdialogex.h"
#include "MyThread.h"

// ServerConf ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(ServerConf, CDialogEx)

	ServerConf::ServerConf(CWnd* pParent /*=NULL*/)
	: CDialogEx(ServerConf::IDD, pParent)
	, m_serverPortEdit(_T(""))
	, serverIPAddress(_T(""))
{

	m_applyFlag = FALSE;
	m_bDragFlag = FALSE;

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
	ON_BN_CLICKED(IDCANCEL, &ServerConf::OnBnClickedStop)
	ON_BN_CLICKED(IDC_BUTTON12, &ServerConf::OnBnClickedPortApply)
	ON_BN_CLICKED(IDC_BUTTON13, &ServerConf::OnBnClickedPortCancel)
	ON_STN_CLICKED(IDC_PICCOM, &ServerConf::OnStnClickedPiccom)
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
END_MESSAGE_MAP()


// ServerConf �޽��� ó�����Դϴ�.


void ServerConf::OnBnClickedStart()
{
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
	//CDialogEx::OnOK();

}


void ServerConf::OnBnClickedStop()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	initFlag();
	closeClient();


	CDialogEx::OnCancel();
}


void ServerConf::OnBnClickedPortApply()
{
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_CButton_portApply.EnableWindow(TRUE);
	m_portEditControl.EnableWindow(TRUE);
	


}


void ServerConf::OnStnClickedPiccom()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void ServerConf::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

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

	/*CString str;

	str.Format(_T("��ġ : (%d, %d)"), point.x, point.y);

	CClientDC dc(this);

	dc.TextOutW(point.x, point.y, str);*/



	//AfxMessageBox(_T("hello"));


	CDialogEx::OnLButtonDown(nFlags, point);
}


void ServerConf::OnLButtonUp(UINT nFlags, CPoint point)
{
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
				} else{ // �� �� �ƴϸ� �׳� ����

					m_settingFlag[0] = -1;
					return;
				}
				//	m_CButton_one.SetWindowTextW(NULL);

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
				//	m_CButton_two.SetWindowTextW(NULL);

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
				//	m_CButton_three.SetWindowTextW(NULL);

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
				//	m_CButton_four.SetWindowTextW(NULL);

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
		//		//	m_CButton_five.SetWindowTextW(NULL);

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
				//	m_CButton_six.SetWindowTextW(NULL);

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
				//	m_CButton_seven.SetWindowTextW(NULL);

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
				//m_CButton_eight.SetWindowTextW(NULL);

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

				//m_CButton_nine.SetWindowTextW(_T(""));

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

void ServerConf::initServer(int nPort)
{
	
	listen.Create(nPort);
	listen.Listen();

	/* Nagle �˰����� �����ϴ� �ڵ�, �츮 ���α׷������� Nagle �˰��� �ʿ���� */
	const char opt_val = true;
//	setsockopt(realSock, IPPROTO_TCP, TCP_NODELAY, &opt_val, sizeof(opt_val));

	m_startFlag = TRUE; // ���� ���� �÷��� True
	AfxMessageBox(_T("Accept Complete"));
}

void ServerConf::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(m_settingFlag[0] != -1){
		if(AfxMessageBox(_T("�����Ͻðڽ��ϱ�?"), MB_YESNO | MB_ICONQUESTION)==IDYES)
		{
			m_CButton_one.SetBitmap(NULL);
			m_CButton_one.SetWindowTextW(_T("1"));
			m_deviceFlag = -1;
			m_settingFlag[0] = -1;
			RedrawWindow();
		}
	}
}


void ServerConf::OnBnClickedButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(m_settingFlag[1] != -1){
		if(AfxMessageBox(_T("�����Ͻðڽ��ϱ�?"), MB_YESNO | MB_ICONQUESTION)==IDYES)
		{
			m_CButton_two.SetBitmap(NULL);
			m_CButton_two.SetWindowTextW(_T("2"));
			m_deviceFlag = -1;
			m_settingFlag[1] = -1;
			RedrawWindow();
		}
	}
}


void ServerConf::OnBnClickedButton3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(m_settingFlag[2] != -1){
		if(AfxMessageBox(_T("�����Ͻðڽ��ϱ�?"), MB_YESNO | MB_ICONQUESTION)==IDYES)
		{
			m_CButton_three.SetBitmap(NULL);
			m_CButton_three.SetWindowTextW(_T("3"));
			m_deviceFlag = -1;
			m_settingFlag[2] = -1;
			RedrawWindow();
		}
	}
}


void ServerConf::OnBnClickedButton4()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(m_settingFlag[3] != -1){
		if(AfxMessageBox(_T("�����Ͻðڽ��ϱ�?"), MB_YESNO | MB_ICONQUESTION)==IDYES)
		{
			m_CButton_four.SetBitmap(NULL);
			m_CButton_four.SetWindowTextW(_T("4"));
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
//			m_CButton_five.SetWindowTextW(_T("5"));
//			m_deviceFlag = -1;
//			m_settingFlag[4] = -1;
//			RedrawWindow();
//		}
//	}
//}


void ServerConf::OnBnClickedButton6()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(m_settingFlag[5] != -1){
		if(AfxMessageBox(_T("�����Ͻðڽ��ϱ�?"), MB_YESNO | MB_ICONQUESTION)==IDYES)
		{
			m_CButton_six.SetBitmap(NULL);
			m_CButton_six.SetWindowTextW(_T("6"));
			m_deviceFlag = -1;
			m_settingFlag[5] = -1;
			RedrawWindow();
		}
	}
}


void ServerConf::OnBnClickedButton7()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(m_settingFlag[6] != -1){
		if(AfxMessageBox(_T("�����Ͻðڽ��ϱ�?"), MB_YESNO | MB_ICONQUESTION)==IDYES)
		{
			m_CButton_seven.SetBitmap(NULL);
			m_CButton_seven.SetWindowTextW(_T("7"));
			m_deviceFlag = -1;
			m_settingFlag[6] = -1;
			RedrawWindow();
		}
	}
}


void ServerConf::OnBnClickedButton8()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(m_settingFlag[7] != -1){
		if(AfxMessageBox(_T("�����Ͻðڽ��ϱ�?"), MB_YESNO | MB_ICONQUESTION)==IDYES)
		{
			m_CButton_eight.SetBitmap(NULL);
			m_CButton_eight.SetWindowTextW(_T("8"));
			m_deviceFlag = -1;
			m_settingFlag[7] = -1;
			RedrawWindow();
		}
	}
}


void ServerConf::OnBnClickedButton9()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(m_settingFlag[8] != -1){
		if(AfxMessageBox(_T("�����Ͻðڽ��ϱ�?"), MB_YESNO | MB_ICONQUESTION)==IDYES)
		{
			m_CButton_nine.SetBitmap(NULL);
			m_CButton_nine.SetWindowTextW(_T("9"));
			m_deviceFlag = -1;
			m_settingFlag[8] = -1;
			RedrawWindow();
		}
	}
}

void ServerConf::closeClient(void)
{
	if(m_startFlag == TRUE){
		m_startFlag = FALSE;
//		realSock.Close();
		AfxMessageBox(_T("Close Success!!"));
		
		m_CBtn_Start.EnableWindow(TRUE);
	}


}


void ServerConf::receiveData(CMySocket *s)
{
	char temp[1024];
	//memset(temp, 0, sizeof(temp));
	ZeroMemory(temp, sizeof(temp));

	char saveStr[1024];

	ZeroMemory( saveStr, sizeof(saveStr));

	int t = 0;
	t = s->Receive(temp, sizeof(temp));
	
	s->Send(temp, sizeof(temp));

	AfxMessageBox(_T("receive Success!!"));

	 
}


void ServerConf::initFlag(void)
{
	m_applyFlag = FALSE;
	m_bDragFlag = FALSE;
	m_deviceFlag = -1;
	for(int i = 0 ; i < 9 ; i++ )
		m_settingFlag[i] = -1;
	m_startFlag = TRUE;

}
