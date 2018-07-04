// ShowDlgMov.cpp : 实现文件
//
//#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS  
#include "stdafx.h"
#include "SplitSDI.h"
#include "ShowDlgMov.h"
#include "SplitSDIDoc.h"

void CharToTchar(const char * _char, TCHAR * tchar)
{
	int iLength;

	iLength = MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, NULL, 0);
	MultiByteToWideChar(CP_ACP, 0, _char, strlen(_char) + 1, tchar, iLength);
}

// CShowDlgMov

IMPLEMENT_DYNCREATE(CShowDlgMov, CFormView)

CShowDlgMov::CShowDlgMov()
	: CFormView(IDD_DIALOG_MOV)
	, m_no(1)
	, m_display_x(0)
	, m_display_y(0)
	, m_display_z(0)
	, m_current_x(0)
	, m_current_y(0)
	, m_current_z(0)
{

}

CShowDlgMov::~CShowDlgMov()
{
}

void CShowDlgMov::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CHOOSENUM, m_no);
	DDX_Text(pDX, IDC_EDIT_XDIS, m_display_x);
	DDX_Text(pDX, IDC_EDIT_YDIS, m_display_y);
	DDX_Text(pDX, IDC_EDIT_ZDIS, m_display_z);
	DDX_Control(pDX, IDC_SLIDER_X, m_slider_x);
	DDX_Control(pDX, IDC_SLIDER_Y, m_slider_y);
	DDX_Control(pDX, IDC_SLIDER_Z, m_slider_z);
}

BEGIN_MESSAGE_MAP(CShowDlgMov, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CShowDlgMov::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_SHOW_ALL, &CShowDlgMov::OnBnClickedButtonShowAll)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_ALL, &CShowDlgMov::OnBnClickedButtonCloseAll)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CShowDlgMov::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_CLR, &CShowDlgMov::OnBnClickedButtonClr)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON_CLOSE_SEARCH, &CShowDlgMov::OnBnClickedButtonCloseSearch)
END_MESSAGE_MAP()


// CShowDlgMov 诊断

#ifdef _DEBUG
void CShowDlgMov::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CShowDlgMov::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CShowDlgMov 消息处理程序


void CShowDlgMov::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	m_sliderX = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_X);
	m_sliderY = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_Y);
	m_sliderZ = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_Z);
	m_editFont.CreatePointFont(90, _T("微软雅黑"));
	GetDlgItem(IDC_BUTTON_SHOW_ALL)->SetFont(&m_editFont);
	GetDlgItem(IDC_BUTTON_CLOSE_ALL)->SetFont(&m_editFont);
	GetDlgItem(IDC_BUTTON_CLR)->SetFont(&m_editFont);
	GetDlgItem(IDC_BUTTON_SEARCH)->SetFont(&m_editFont);
	GetDlgItem(IDC_BUTTON_CLOSE_SEARCH)->SetFont(&m_editFont);
	GetDlgItem(IDC_BUTTON_DELETE)->SetFont(&m_editFont);
	GetDlgItem(IDC_EDIT_XDIS)->SetFont(&m_editFont);
	GetDlgItem(IDC_EDIT_YDIS)->SetFont(&m_editFont);
	GetDlgItem(IDC_EDIT_ZDIS)->SetFont(&m_editFont);
	GetDlgItem(IDC_EDIT_CHOOSENUM)->SetFont(&m_editFont);
	GetDlgItem(IDC_STATIC1)->SetFont(&m_editFont);
	GetDlgItem(IDC_STATIC2)->SetFont(&m_editFont);
	GetDlgItem(IDC_STATIC3)->SetFont(&m_editFont);
	GetDlgItem(IDC_STATIC4)->SetFont(&m_editFont);
	//GetDlgItem(IDC_EDIT_ZDIS)->SetFont(&m_editFont);
}


void CShowDlgMov::OnBnClickedButtonSearch()
{
	UpdateData(TRUE);
	CSplitSDIDoc* pDoc = (CSplitSDIDoc*)GetDocument();

	myVertex*p = pDoc->HeadPoint;
	if (pDoc->HeadPoint == NULL)
	{
		MessageBox(_T("还没有输入点"));
		UpdateData(FALSE);
		return;
	}
	else
	{	
		//查找这个编号
		while (p->next != NULL)
		{
			p = p->next;
			if (p->num == m_no) break;
		}
		if (p == NULL)
		{
			MessageBox(_T("找不到这个点"));
			pDoc->flag_show_stress = 0;
			pDoc->m_stress_point_no = 0;
			UpdateData(FALSE);
			return;
		}
		else
		{
			//flag_show_stress表示是否显示重点
			pDoc->flag_show_stress = 1;
			//m_stress_point_no用于存放重点的序号
			pDoc->m_stress_point_no = m_no;
			pDoc->UpdateAllViews(NULL);
			UpdateData(FALSE);
		}
	}

	//设置滑块的位置
	m_sliderX->SetPos(p->x*(100 / pDoc->m_range_x));
	m_sliderY->SetPos(p->y*(100 / pDoc->m_range_y));
	m_sliderZ->SetPos(p->z*(100 / pDoc->m_range_z));
	
	
	
	//编辑框显示坐标值
	TCHAR tx[30], ty[30], tz[30];
	char cx[30], cy[30], cz[30];
	double mx = p->x, my = p->y, mz = p->z;
	sprintf_s(cx, sizeof(cx),"%.1lf", mx);
	sprintf_s(cy, sizeof(cy),"%.1lf", my);
	sprintf_s(cz, sizeof(cz),"%.1lf", mz);

#ifdef UNICODE
	MultiByteToWideChar(CP_ACP, 0, cx, -1, tx, 30);
	MultiByteToWideChar(CP_ACP, 0, cy, -1, ty, 30);
	MultiByteToWideChar(CP_ACP, 0, cz, -1, tz, 30);
#else
	strcpy(tx, cx);
	strcpy(ty, cy);
	strcpy(tz, cz);
#endif

	GetDlgItem(IDC_EDIT_XDIS)->SetWindowText(tx);
	GetDlgItem(IDC_EDIT_YDIS)->SetWindowText(ty);
	GetDlgItem(IDC_EDIT_ZDIS)->SetWindowText(tz);

}


void CShowDlgMov::OnBnClickedButtonShowAll()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CSplitSDIDoc* pDoc = (CSplitSDIDoc*)GetDocument();
	pDoc->flag_show_all_num = 1;
	pDoc->UpdateAllViews(NULL);
	UpdateData(FALSE);
}


void CShowDlgMov::OnBnClickedButtonCloseAll()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CSplitSDIDoc* pDoc = (CSplitSDIDoc*)GetDocument();
	pDoc->flag_show_all_num = 0;
	pDoc->UpdateAllViews(NULL);
	UpdateData(FALSE);
}


void CShowDlgMov::OnBnClickedButtonDelete()
{
	CSplitSDIDoc* pDoc = (CSplitSDIDoc*)GetDocument();
	if (pDoc->m_stress_point_no == 0)
	{
		MessageBox(_T("请先查找点再删除！"));
		return;
	}
	pDoc->DeletePoint();
	pDoc->UpdateAllViews(NULL);
}


void CShowDlgMov::OnBnClickedButtonClr()
{
	CSplitSDIDoc* pDoc = (CSplitSDIDoc*)GetDocument();
	if (pDoc->HeadPoint == NULL) {
		MessageBox(_T("当前没有添加任何点"));
	}
	else
	{
		pDoc->DeleteVertex();
		MessageBox(_T("已经成功清除了全部点"));
		pDoc->UpdateAllViews(NULL);
	}
}



void CShowDlgMov::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//当下列情况发生时，SliderCtrl的父窗口都会收到 WM_HSCROLL(水平方向控件) 或者 WM_VSCROLL(竖直方向控件) 通知消息。
	//	<1>.用鼠标点击滑杆，点击一次收到一条通知消息.
	//	<2>.按下鼠标拖动滑杆，拖动时会不断收到通知消息.
	//	<3>.按下方向键，按一次，收到一条通知消息.
	//	<4>.按下 PageUp, PageDown 键，同上.
	//	<5>.按下 Home, End 键，同上.

	CSplitSDIDoc* pDoc = (CSplitSDIDoc *)GetDocument();

	CFormView::OnHScroll(nSBCode, nPos, pScrollBar);

	if (pScrollBar == NULL)
	{
		return;
	}

	if (pDoc->flag_show_stress)
	{
		m_current_x = m_sliderX->GetPos();
		m_current_y = m_sliderY->GetPos();
		m_current_z = m_sliderZ->GetPos();

		TCHAR tx[30], ty[30], tz[30];
		char cx[30], cy[30], cz[30];
		double mx = (float)m_current_x*(float)(pDoc->m_range_x)/ 100, my = (float)m_current_y*(float)(pDoc->m_range_y) / 100, mz = (float)m_current_z*(float)(pDoc->m_range_z) / 100;
		sprintf_s(cx, sizeof(cx), "%.1lf", mx);
		sprintf_s(cy, sizeof(cy), "%.1lf", my);
		sprintf_s(cz, sizeof(cz), "%.1lf", mz);
#ifdef UNICODE
		MultiByteToWideChar(CP_ACP, 0, cx, -1, tx, 30);
		MultiByteToWideChar(CP_ACP, 0, cy, -1, ty, 30);
		MultiByteToWideChar(CP_ACP, 0, cz, -1, tz, 30);
#else
		strcpy(tx, cx);
		strcpy(ty, cy);
		strcpy(tz, cz);
#endif
		GetDlgItem(IDC_EDIT_XDIS)->SetWindowText(tx);
		GetDlgItem(IDC_EDIT_YDIS)->SetWindowText(ty);
		GetDlgItem(IDC_EDIT_ZDIS)->SetWindowText(tz);

		UpdateData(TRUE);
		myVertex* p = pDoc->HeadPoint;
		while (p->next != NULL)
		{
			p = p->next;
			if (p->num == pDoc->m_stress_point_no)
			{
				p->x = mx;
				p->y = my;
				p->z = mz;
				break;
			}
		}
		pDoc->UpdateAllViews(NULL);
		UpdateData(FALSE);
	}
	else
	{
		MessageBox(_T("您还没查找需要的点"));
		m_sliderX->SetPos(0);
		m_sliderY->SetPos(0);
		m_sliderZ->SetPos(0);
		return;
	}
}


void CShowDlgMov::OnBnClickedButtonCloseSearch()
{
	// TODO: 在此添加控件通知处理程序代码
	
	CSplitSDIDoc* pDoc = (CSplitSDIDoc*)GetDocument();
	pDoc->flag_show_stress = 0;
	pDoc->m_stress_point_no = 0;
	pDoc->UpdateAllViews(NULL);
	m_sliderX->SetPos(0);
	m_sliderY->SetPos(0);
	m_sliderZ->SetPos(0);
	TCHAR tx[30], ty[30], tz[30];
	char cx[30], cy[30], cz[30];
	double mx = 0.0, my = 0.0, mz = 0.0;
	sprintf_s(cx, sizeof(cx), "%.1lf", mx);
	sprintf_s(cy, sizeof(cy), "%.1lf", my);
	sprintf_s(cz, sizeof(cz), "%.1lf", mz);
#ifdef UNICODE
	MultiByteToWideChar(CP_ACP, 0, cx, -1, tx, 30);
	MultiByteToWideChar(CP_ACP, 0, cy, -1, ty, 30);
	MultiByteToWideChar(CP_ACP, 0, cz, -1, tz, 30);
#else
	strcpy(tx, cx);
	strcpy(ty, cy);
	strcpy(tz, cz);
#endif
	UpdateData(FALSE);
	GetDlgItem(IDC_EDIT_XDIS)->SetWindowText(tx);
	GetDlgItem(IDC_EDIT_YDIS)->SetWindowText(ty);
	GetDlgItem(IDC_EDIT_ZDIS)->SetWindowText(tz);
	
}

