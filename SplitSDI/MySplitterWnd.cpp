// MySplitterWnd.cpp : 实现文件
//

#include "stdafx.h"
#include "SplitSDI.h"
#include "MySplitterWnd.h"


// CMySplitterWnd

IMPLEMENT_DYNAMIC(CMySplitterWnd, CSplitterWnd)

CMySplitterWnd::CMySplitterWnd()
{
	//自定义分割线条样式
	m_cxSplitterGap = 2;
	m_cxSplitter = 5;
	m_cySplitterGap = 2;
	m_cySplitter = 5;
}

CMySplitterWnd::~CMySplitterWnd()
{
}


BEGIN_MESSAGE_MAP(CMySplitterWnd, CSplitterWnd)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CMySplitterWnd 消息处理程序




void CMySplitterWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//把这两个函数的功能注释掉，就不会拖动了
	//CSplitterWnd::OnLButtonDown(nFlags, point);
}


void CMySplitterWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//CSplitterWnd::OnMouseMove(nFlags, point);
}


void CMySplitterWnd::OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rect)
{
	// TODO: 在此添加专用代码和/或调用基类

	CSplitterWnd::OnDrawSplitter(pDC, nType, rect);

}
