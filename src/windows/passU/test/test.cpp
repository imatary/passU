
// test.cpp : ���� ���α׷��� ���� Ŭ���� ������ �����մϴ�.
//

#include "stdafx.h"
#include "test.h"
#include "testDlg.h"
#include "ClientConf.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtestApp

BEGIN_MESSAGE_MAP(CtestApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CtestApp ����

CtestApp::CtestApp()
{
	// �ٽ� ���� ������ ����
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
	m_pServer = NULL;
	m_pClient = NULL;
	m_pChild = NULL;
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.
	// InitInstance�� ��� �߿��� �ʱ�ȭ �۾��� ��ġ�մϴ�.
}


// ������ CtestApp ��ü�Դϴ�.

CtestApp theApp;


// CtestApp �ʱ�ȭ

BOOL CtestApp::InitInstance()
{
	// ���� ���α׷� �Ŵ��佺Ʈ�� ComCtl32.dll ���� 6 �̻��� ����Ͽ� ���־� ��Ÿ����
	// ����ϵ��� �����ϴ� ���, Windows XP �󿡼� �ݵ�� InitCommonControlsEx()�� �ʿ��մϴ�.
	// InitCommonControlsEx()�� ������� ������ â�� ���� �� �����ϴ�.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ���� ���α׷����� ����� ��� ���� ��Ʈ�� Ŭ������ �����ϵ���
	// �� �׸��� �����Ͻʽÿ�.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	
	

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ��ȭ ���ڿ� �� Ʈ�� �� �Ǵ�
	// �� ��� �� ��Ʈ���� ���ԵǾ� �ִ� ��� �� �����ڸ� ����ϴ�.
	CShellManager *pShellManager = new CShellManager;

	// MFC ��Ʈ���� �׸��� ����ϱ� ���� "Windows ����" ���־� ������ Ȱ��ȭ
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ
	// ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));

	CtestDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: ���⿡ [Ȯ��]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
		
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: ���⿡ [���]�� Ŭ���Ͽ� ��ȭ ���ڰ� ������ �� ó����
		//  �ڵ带 ��ġ�մϴ�.
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "���: ��ȭ ���ڸ� ������ �������Ƿ� ���� ���α׷��� ����ġ �ʰ� ����˴ϴ�.\n");
		TRACE(traceAppMsg, 0, "���: ��ȭ ���ڿ��� MFC ��Ʈ���� ����ϴ� ��� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS�� ������ �� �����ϴ�.\n");
	}

	// ������ ���� �� �����ڸ� �����մϴ�.
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ��ȭ ���ڰ� �������Ƿ� ���� ���α׷��� �޽��� ������ �������� �ʰ�  ���� ���α׷��� ���� �� �ֵ��� FALSE��
	// ��ȯ�մϴ�.
	return FALSE;
}



void CtestApp::initServer(int nPort)
{
	m_pServer = new ServerSocket();
	m_pServer->Create(nPort);
	m_pServer->Listen();

}


void CtestApp::cleanUp(void)
{
	if(m_pServer)	delete m_pServer;
	if(m_pChild)	delete m_pChild;
}


void CtestApp::sendData(CString strData)
{
	if(m_pChild){
		strData.Insert(strData.GetLength(), _T("\0"));
		m_pChild->Send(strData, 100);
		CString strIP, strText;
		UINT nPort;
		m_pChild->GetSockName(strIP, nPort);
		strText.Format(_T("[ %s ] %s "), strIP, strData);

	}
}


void CtestApp::receiveData(void)
{
	char temp[1024];

	m_pChild->Receive(temp, sizeof(temp));
	CString strIP, strText;

	UINT nPort;

	m_pChild->GetPeerName(strIP, nPort);
	
	strText.Format(_T("[ %s ] %s "), strIP, temp);
	
}


void CtestApp::accept(void)
{
	m_pChild = new ServerChildSocket();

	BOOL check = m_pServer->Accept(*m_pChild);

	if(check == FALSE){
		AfxMessageBox(_T("���� ��� ����"));
		return ;
	}

}


void CtestApp::closeChild(void)
{
	m_pChild->Close();
	delete m_pChild;

}


void CtestApp::clientConnect(void)
{
	ClientConf dlg;
	UINT nPort;

	nPort = _ttoi(m_portNum);

	if(dlg.DoModal() == IDOK)
	{
		m_pClient = new ClientSocket();
		m_pClient->Create();
		m_pClient->Connect(dlg.m_address, nPort);
	}


}


void CtestApp::clientCleanUp(void)
{
	if(m_pClient)	delete m_pClient;
}


void CtestApp::clientSendData(CString strData)
{
}


void CtestApp::clientReceiveData(void)
{
}


void CtestApp::clientcloseChild(void)
{
}
