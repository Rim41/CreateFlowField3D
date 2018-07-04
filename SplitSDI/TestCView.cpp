// TestCView.cpp : 实现文件
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


// CTestCView 绘图

void CTestCView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO:  在此添加绘制代码
}


// CTestCView 诊断

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


// CTestCView 消息处理程序
