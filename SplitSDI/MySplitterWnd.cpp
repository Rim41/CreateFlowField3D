// MySplitterWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SplitSDI.h"
#include "MySplitterWnd.h"


// CMySplitterWnd

IMPLEMENT_DYNAMIC(CMySplitterWnd, CSplitterWnd)

CMySplitterWnd::CMySplitterWnd()
{
	//�Զ���ָ�������ʽ
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



// CMySplitterWnd ��Ϣ�������




void CMySplitterWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//�������������Ĺ���ע�͵����Ͳ����϶���
	//CSplitterWnd::OnLButtonDown(nFlags, point);
}


void CMySplitterWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//CSplitterWnd::OnMouseMove(nFlags, point);
}


void CMySplitterWnd::OnDrawSplitter(CDC* pDC, ESplitType nType, const CRect& rect)
{
	// TODO: �ڴ����ר�ô����/����û���

	CSplitterWnd::OnDrawSplitter(pDC, nType, rect);

}
