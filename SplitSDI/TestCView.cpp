// TestCView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SplitSDI.h"
#include "TestCView.h"


// CTestCView

IMPLEMENT_DYNCREATE(CTestCView, CView)

CTestCView::CTestCView()
{

}

CTestCView::~CTestCView()
{
}

BEGIN_MESSAGE_MAP(CTestCView, CView)
END_MESSAGE_MAP()


// CTestCView ��ͼ

void CTestCView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO:  �ڴ���ӻ��ƴ���
}


// CTestCView ���

#ifdef _DEBUG
void CTestCView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CTestCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CTestCView ��Ϣ�������
