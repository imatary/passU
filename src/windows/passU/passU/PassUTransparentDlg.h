#pragma once


// CPassUTransparentDlg ��ȭ �����Դϴ�.

class CPassUTransparentDlg : public CDialog
{
	DECLARE_DYNAMIC(CPassUTransparentDlg)

public:
	CPassUTransparentDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CPassUTransparentDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_TRANSPARENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
