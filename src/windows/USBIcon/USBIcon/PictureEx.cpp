// PictureEx.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "PictureEx.h"

// CPictureEx

IMPLEMENT_DYNAMIC(CPictureEx, CStatic)

	CPictureEx::CPictureEx()
{
	Transparent = RGB(255, 255, 255);
}

CPictureEx::~CPictureEx()
{
}

BEGIN_MESSAGE_MAP(CPictureEx, CStatic)
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CPictureEx �޽��� ó�����Դϴ�.

void CPictureEx::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	HBITMAP old,bmp  = GetBitmap();
	BITMAP bminfo;
	CDC memDC;

	memDC.CreateCompatibleDC(&dc);
	old = (HBITMAP)::SelectObject(memDC.m_hDC,bmp);
	::GetObject(bmp,sizeof(BITMAP),&bminfo);
	::TransparentBlt(dc.m_hDC,0,0,bminfo.bmWidth,bminfo.bmHeight, memDC.m_hDC,0,0,bminfo.bmWidth,bminfo.bmHeight,Transparent);
	::SelectObject(memDC.m_hDC,old);
	memDC.DeleteDC();
	// �׸��� �޽����� ���ؼ��� CStatic::OnPaint()��(��) ȣ������ ���ʽÿ�.
}