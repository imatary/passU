// Server.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "PassU.h"
#include "Server.h"
#include "afxdialogex.h"
#include "PassUDlg.h"


#define WM_RECEIVEMSG	(WM_USER + 1000)


// ��ŷ�� ���� �Լ� ������
typedef HHOOK (*InstallKeyboardHook)();
typedef HHOOK (*InstallMouseHook)();

typedef void (*UnInstallKeyboardHook)();
typedef void  (*UnInstallMouseHook)();

InstallKeyboardHook installKeyhook;
InstallMouseHook installMousehook;

UnInstallKeyboardHook uninstallKeyhook;
UnInstallMouseHook uninstallMousehook;


// CServer ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CServer, CDialogEx)

	CServer::CServer(CWnd* pParent /*=NULL*/)
	: CDialogEx(CServer::IDD, pParent)
	, serverIPAddress(_T(""))
{

}

CServer::~CServer()
{

}

void CServer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_IPADDRESS, serverIPAddress);
	DDX_Control(pDX, IDC_BUTTON1, m_cBtn[0]);
	DDX_Control(pDX, IDC_BUTTON2, m_cBtn[1]);
	DDX_Control(pDX, IDC_BUTTON3, m_cBtn[2]);
	DDX_Control(pDX, IDC_BUTTON4, m_cBtn[3]);
	DDX_Control(pDX, IDC_BUTTON5, m_cBtn[4]);
	DDX_Control(pDX, IDC_BUTTON6, m_cBtn[5]);
	DDX_Control(pDX, IDC_BUTTON7, m_cBtn[6]);
	DDX_Control(pDX, IDC_BUTTON8, m_cBtn[7]);
	DDX_Control(pDX, IDC_BUTTON9, m_cBtn[8]);
	DDX_Control(pDX, IDC_LIST1, m_waiting_client);
	DDX_Control(pDX, IDC_BUTTON10, m_CBtn_ServerStart);
}


BEGIN_MESSAGE_MAP(CServer, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON10, &CServer::OnBnClickedServerStart)
	ON_BN_CLICKED(IDC_BUTTON11, &CServer::OnBnClickedServerStop)
	ON_BN_CLICKED(IDC_BUTTON1, &CServer::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CServer::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CServer::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CServer::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON6, &CServer::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CServer::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CServer::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CServer::OnBnClickedButton9)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_COPYDATA()
	ON_MESSAGE(WM_RECEIVEMSG, &CServer::OnABC)
	ON_NOTIFY(LVN_BEGINDRAG, IDC_LIST1, &CServer::OnLvnBegindragList1)
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

BOOL CServer::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	TRACE("CServer Init\n");

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

	serverIPAddress.Append(strIpAddress);


	hinstDLL = LoadLibrary(_T("KeyHook.dll"));
	if(!hinstDLL)
		AfxMessageBox(_T("KeyHook.dll �ε� ����!"));

	installKeyhook = (InstallKeyboardHook)GetProcAddress(hinstDLL, "InstallKeyboardHook");
	installMousehook = (InstallMouseHook)GetProcAddress(hinstDLL, "InstallMouseHook");

	uninstallKeyhook = (UnInstallKeyboardHook)GetProcAddress(hinstDLL, "UnInstallKeyboardHook");
	uninstallMousehook = (UnInstallMouseHook)GetProcAddress(hinstDLL, "UnInstallMouseHook");


	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}
	
	for(int i = 0 ; i < 9 ; i ++){
		ZeroMemory(&clientInfo[i], sizeof(clientInfo[i]));
		ZeroMemory(&btnControl[i], sizeof(btnControl[i]));
		ZeroMemory(&m_imgList[i], sizeof(m_imgList[i]));

	}

	m_keyBoardHook = FALSE;
	m_mouseHook = FALSE;
	m_bDrag = FALSE;

	m_nOldTarget = 0;
	m_nSource = 0;

	m_status = STATUS_EMPTY;
	m_x = 0;
	m_y = 0;
	p = NULL;
	k = NULL;
	m = NULL;
	c = NULL;

	m_bmp_monitor.LoadBitmapA(IDB_MONITOR);
	m_bmp_phone.LoadBitmapA(IDB_PHONE);


	m_imgList[8].Create(60, 60, ILC_COLOR24 | ILC_MASK, 1, 1);
	m_waiting_client.SetImageList(&m_imgList[8], LVSIL_NORMAL);

	m_imgList[8].Add(&m_bmp_monitor, RGB(0, 0, 0));
	
	LVITEM lvitem = {0};

	lvitem.mask = LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM;
	lvitem.iItem = 0;
	lvitem.pszText = "127.0.0.1";
	lvitem.lParam = (LPARAM)STATUS_PC;
	lvitem.iImage = 0;

	m_waiting_client.InsertItem(&lvitem);


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

	m_pDragImage = NULL;


	return TRUE;
}
// CServer �޽��� ó�����Դϴ�.




void CServer::OnChangeLocationInfo(int index)
{
}


void CServer::bindWatingClient(int client_index)
{
	// Ŭ���̾�Ʈ index�� �־��༭ ��ư�ϰ� binding��Ű�� ��
}

void CServer::OnArrivedScreenEdge(int position)
{

}


void CServer::OnBnClickedServerStart()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_CBtn_ServerStart.EnableWindow(FALSE);
//	OnStartServer();
}


void CServer::OnBnClickedServerStop()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	m_CBtn_ServerStart.EnableWindow(TRUE);
//	CleanUp();

}


void CServer::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

}


void CServer::OnBnClickedButton2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CServer::OnBnClickedButton3()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CServer::OnBnClickedButton4()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CServer::OnBnClickedButton6()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CServer::OnBnClickedButton7()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CServer::OnBnClickedButton8()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CServer::OnBnClickedButton9()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void CServer::OnLButtonUp(UINT nFlags, CPoint point)
{
	CPoint m_tmpPoint;
	CBitmap m_tmpBitmap;
	HBITMAP m_hBitmap;

	LVITEM Item; 


	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (m_bDrag)
	{
		if (NULL == m_pDragImage)
			return ;

		m_waiting_client.SetItemState(m_nOldTarget, 0, LVIS_DROPHILITED);

		//�巡������   
		m_pDragImage->DragLeave(NULL);
		ReleaseCapture();                
		m_pDragImage->EndDrag();       

		m_bDrag = false;
		delete m_pDragImage;
		m_pDragImage = NULL;       
		// ��������ġ����
		INT nDest = GetHitIndex(point);       

		TCHAR Name[256 + 1] = {0,}; 

		Item.iItem = m_nSource;   
		Item.mask = LVIF_IMAGE | LVIF_TEXT | LVIF_PARAM | LVIF_STATE;   
		Item.stateMask = LVIS_FOCUSED | LVIS_SELECTED | LVIS_STATEIMAGEMASK | LVIS_OVERLAYMASK;    
		Item.pszText = Name;   
		Item.cchTextMax = 256;   
		Item.iSubItem = 0;   
		m_waiting_client.GetItem(&Item);   

		Item.iItem = nDest;   
		m_waiting_client.InsertItem(&Item);   

		for(int i = 0; i < sizeof(m_cBtn)/sizeof(m_cBtn[0]); i++) {
			if(point.x >= getCoord[i].rcNormalPosition.left &&
				point.x <= getCoord[i].rcNormalPosition.right &&
				point.y <= getCoord[i].rcNormalPosition.bottom &&
				point.y >= getCoord[i].rcNormalPosition.top){ // �巡�� ���� ���� ��ư 1�� ��

				// ó���� Ŭ���� �׸��� ����Ʈ������ ��ǻ������ �ɷ�����
				// ��ǻ���̸� ��ư�� ��ǻ�� ����, ����Ʈ���̸� ��ư�� ����Ʈ�� ����
				if(Item.lParam == STATUS_PC){
					m_cBtn[i].SetBitmap(HBITMAP(m_bmp_monitor));
				} else{
					m_cBtn[i].SetBitmap(HBITMAP(m_bmp_phone));
				}

				UpdateData();
				Invalidate();
				RedrawWindow();
				break;
			}
		}
	}   
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CServer::MoveListItem(const INT _nSource, const INT _nDest)
{
	if ((_nSource == _nDest) || (0 > _nDest))
		return ;

	INT nSource = _nSource;   
	INT nColumn = m_waiting_client.GetHeaderCtrl()->GetItemCount();   
	TCHAR Name[256 + 1] = {0,};   

	LVITEM Item;   
	Item.iItem = nSource;   
	Item.mask = LVIF_IMAGE | LVIF_TEXT | LVIF_PARAM | LVIF_STATE;   
	Item.stateMask = LVIS_FOCUSED | LVIS_SELECTED | LVIS_STATEIMAGEMASK | LVIS_OVERLAYMASK;    
	Item.pszText = Name;   
	Item.cchTextMax = 256;   
	Item.iSubItem = 0;   
	m_waiting_client.GetItem(&Item);   

	Item.iItem = _nDest;   
	m_waiting_client.InsertItem(&Item);   



	if (nSource > _nDest)
		nSource ++;       

	for (INT i= 1; i<nColumn; i++)
	{   
		CString sText = m_waiting_client.GetItemText(nSource, i);       
		m_waiting_client.SetItemText(_nDest, i, sText);       
	}   
	m_waiting_client.DeleteItem(nSource);   
}

void CServer::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	CDialogEx::OnLButtonDown(nFlags, point);
}

LRESULT CServer::OnABC( WPARAM wParam, LPARAM lParam) {
	AfxMessageBox("OnABC");
	return 0;

}

BOOL CServer::OnCopyData(CWnd* pWnd, COPYDATASTRUCT* pCopyDataStruct)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	
	CPassUDlg * pMainDlg = (CPassUDlg *)::AfxGetMainWnd();
	POSITION pos = pMainDlg->m_pSockList.GetHeadPosition();
	TRACE("OnCopyData\n");
	PACKET pack;
	switch(pCopyDataStruct->dwData){
	case 0: // keyboard

		break;


	case 1: // mouse

		break;


	case 2: // receiveData
		p = (PACKET *) pCopyDataStruct->lpData; // ����ü ����

		switch(p->msgType){
		case 1: // keyboard

			break;

		case 2: // mouse
			break;


		case 3: // client
			if(p->deviceType == 1){ // hello packet
				// ��� ��Ŷ�̸� Ŭ���̾�Ʈ ���� ����
				// ��ư�� Ŭ���̾�Ʈ �������ְ�, ù��° Ŭ���̾�Ʈ�� ��ŷ �����ϰ�
				// Ŭ���̾�Ʈ�� �ڽ��� id �˷��ְ�
				// ����Ʈ ��Ʈ�ѿ� ������ �ϳ� �߰�
				TRACE("client\n");
				for(int i = 0 ; i < 9 ; i ++){
					if(clientInfo[i].clientID == 0){
						// client ID Setting
						clientInfo[i].setID(i);
						
						pack = packMessage(3, (i + 1) , 0 , 1, 0, 0, 0, 0, 0, 0, 0); // client id : �� ���� index + 1 �� ��


						// Client IP Address Setting
						CString m_add;
						m_add.Format(_T("%d.%d.%d.%d", p->keyCode, p->pad2, p->pad3, p->pad4));
					
						//clientInfo[i].setIP(m_add);
						//clientInfo[i].m_address.Format(_T("%d.%d.%d.%d", p->keyCode, p->pad2, p->pad3, p->pad4));

						TRACE("?\n");
						if(p->recvDev == STATUS_PC){ // PC �̸�
							// Status ����
							clientInfo[i].setStatus(STATUS_PC);
							
						TRACE("Status Setting\n");
							// ������ ����
							m_imgList[i].Create(60, 60, ILC_COLOR24 | ILC_MASK, 1, 1);
							m_waiting_client.SetImageList(&m_imgList[i], LVSIL_NORMAL);
							m_imgList[i].Add(&m_bmp_monitor, RGB(0, 0, 0));

							// ���� ������ LVITEM ����
							ZeroMemory(&lvitem[i], sizeof(lvitem));
							lvitem[i].mask = LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM;
							lvitem[i].iItem = 0;
							lvitem[i].pszText = _T("%s",clientInfo[i].m_address);
							lvitem[i].lParam = (LPARAM)STATUS_PC;
							lvitem[i].iImage = 0;

							m_waiting_client.InsertItem(&lvitem[i]);
							break;
						} else if(p->recvDev == STATUS_MOBILE){

							// Status ����
							clientInfo[i].setStatus(STATUS_MOBILE);
							// ������ ����
							m_imgList[i].Create(60, 60, ILC_COLOR24 | ILC_MASK, 1, 1);
							m_waiting_client.SetImageList(&m_imgList[i], LVSIL_NORMAL);
							m_imgList[i].Add(&m_bmp_phone, RGB(0, 0, 0));

							//���� ������ LVITEM ����
							ZeroMemory(&lvitem[i], sizeof(lvitem));
							lvitem[i].mask = LVIF_TEXT|LVIF_IMAGE|LVIF_PARAM;
							lvitem[i].iItem = 0;
							lvitem[i].pszText = _T("%s",clientInfo[i].m_address);
							lvitem[i].lParam = (LPARAM)STATUS_MOBILE;
							lvitem[i].iImage = 0;
							m_waiting_client.InsertItem(&lvitem[i]);
							break;
						} else{
							AfxMessageBox(_T("status nothing!!"));
							m_imgList[i].DeleteImageList();
							clientInfo[i].setID(0);
							clientInfo[i].setStatus(STATUS_EMPTY);
							return FALSE;
						}

					}

					else
						pMainDlg->m_pSockList.GetNext(pos);
				}


				if(pMainDlg->m_pSockList.GetCount() == 1){
					installKeyhook();
					installMousehook();
				}

				((CPassUChildSocket *)pMainDlg->m_pSockList.GetAt(pos))->Send((LPCSTR *)&pack, sizeof(PACKET));

			} else if(k->relativeField == 1){ // bye packet
				// �¹�����Ŷ�̸�
				// ��ư�� Ŭ���̾�Ʈ ����

			}
			break;

		case 4:

			break;

		}

		break;
	}
	return CDialogEx::OnCopyData(pWnd, pCopyDataStruct);
}


void CServer::OnLvnBegindragList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	*pResult = 0;

	if (0 >= m_waiting_client.GetSelectedCount())
		return ;

	m_nSource = pNMLV->iItem;

	//�巡���̹�������Ʈ����
	POINT ptImg;
	m_pDragImage = m_waiting_client.CreateDragImage(m_nSource, &ptImg);
	if (NULL == m_pDragImage)
		return ;

	//�ֽ���
	CPoint ptSpot;
	ptSpot.x = pNMLV->ptAction.x - ptImg.x;
	ptSpot.y = pNMLV->ptAction.y - ptImg.y;
	m_pDragImage->BeginDrag(0, ptSpot);

	//���縶�콺Ŀ����ġ���巡���̹����׸�
	ptImg.x = pNMLV->ptAction.x;
	ptImg.y = pNMLV->ptAction.y;
	ClientToScreen(&ptImg);
	m_pDragImage->DragEnter(NULL, ptImg);

	m_nOldTarget = m_nSource;
	m_bDrag = true;
	SetCapture();
}


void CServer::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if (m_bDrag)
	{
		if (NULL == m_pDragImage)
			return ;

		// �巡���̹����̵�
		CPoint ptCursor(point);
		ClientToScreen(&ptCursor);
		m_pDragImage->DragMove(ptCursor);

		// Ŀ����ġ�Ǹ���Ʈ������ã�Ƽ�����ǥ�ø����ش�.
		INT nTarget = GetHitIndex(point);
		if (-1 != nTarget)
		{
			if (m_nOldTarget != nTarget)
			{
				m_pDragImage->DragLeave(NULL);
				m_waiting_client.SetItemState(nTarget, 
					LVIS_DROPHILITED, LVIS_DROPHILITED);

				m_waiting_client.SetItemState(m_nOldTarget, 0, 
					LVIS_DROPHILITED);
				m_nOldTarget = nTarget;

				m_pDragImage->DragEnter(NULL, ptCursor);
				m_waiting_client.UpdateWindow();
			}
		}
	}

	CDialogEx::OnMouseMove(nFlags, point);
}
int CServer::GetHitIndex(CPoint point) // Ŀ�� ��ġ�� ����Ʈ������ �ε����� ã�´�.
{

	CRect rcList;
	m_waiting_client.GetWindowRect(&rcList);
	ScreenToClient(reinterpret_cast<LPPOINT>(&rcList));

	LVHITTESTINFO HitInfo;
	HitInfo.pt.x = point.x - rcList.left;
	HitInfo.pt.y = point.y - rcList.top;

	return m_waiting_client.HitTest(&HitInfo);
}

PACKET CServer::packMessage(int msgType, int sendDev, int recvDev, int deviceType, int relativeField, int updownFlag, int pad1, int keyCode, int pad2, int pad3, int pad4)
{
	PACKET tmp;

	tmp.msgType = msgType;
	tmp.sendDev = sendDev;
	tmp.recvDev = recvDev;
	tmp.deviceType = deviceType;
	tmp.relativeField = relativeField;
	tmp.updownFlag = updownFlag;
	tmp.pad1 = pad1;
	tmp.keyCode = keyCode;
	tmp.pad2 = pad2;
	tmp.pad3 = pad3;
	tmp.pad4 = pad4;

	return tmp;
}
