#pragma once


// CClient ��ȭ �����Դϴ�.

class CClient : public CDialogEx
{
	DECLARE_DYNAMIC(CClient)

public:
	CClient(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CClient();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CLIENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
