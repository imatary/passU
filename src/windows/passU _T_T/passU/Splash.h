#pragma once


// CSplash ��ȭ �����Դϴ�.

class CSplash : public CDialog
{
	DECLARE_DYNAMIC(CSplash)

public:
	CSplash(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CSplash();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_SPLASH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
