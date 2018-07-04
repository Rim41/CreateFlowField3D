
// SplitSDIDoc.cpp : CSplitSDIDoc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "SplitSDI.h"
#endif

#include "SplitSDIDoc.h"

#include "tchar.h"
#include <propkey.h>
#include "RandomAdd.h"
#include "SetRan.h"
#include <time.h>
#define random(x) (rand()%x)

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSplitSDIDoc

IMPLEMENT_DYNCREATE(CSplitSDIDoc, CDocument)

BEGIN_MESSAGE_MAP(CSplitSDIDoc, CDocument)
	ON_BN_CLICKED(IDC_BUTTON_SUBMIT, &CSplitSDIDoc::OnBnClickedButtonSubmit)
	ON_COMMAND(ID_RANDOM, &CSplitSDIDoc::OnRandom)
	ON_COMMAND(ID_GENERATE, &CSplitSDIDoc::OnGenerate)
END_MESSAGE_MAP()


// CSplitSDIDoc 构造/析构

CSplitSDIDoc::CSplitSDIDoc()
	: flag_show_all_num(0)
	, m_range_x(10)
	, m_range_y(10)
	, m_range_z(10)
	, m_stress_point_no(0)
	, flag_show_stress(0)
	, m_point_num_cnt(1)
	, m_random(0)
{
	HeadPoint = NULL;
	CurPoint = NULL;
}

CSplitSDIDoc::~CSplitSDIDoc()
{
}

BOOL CSplitSDIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)
	SetTitle(_T("流场生成程序3D"));
	return TRUE;
}




// CSplitSDIDoc 序列化

void CSplitSDIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CSplitSDIDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CSplitSDIDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CSplitSDIDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CSplitSDIDoc 诊断

#ifdef _DEBUG
void CSplitSDIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSplitSDIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CSplitSDIDoc 命令


void CSplitSDIDoc::DeleteVertex()
{
	if (HeadPoint == NULL)
		return;
	myVertex* p1=HeadPoint;
	myVertex* p2=p1;
	while (p2->next != NULL)
	{
		p1 = p2->next;
		delete p2;
		p2 = p1;
	}
	p2 = p1 = NULL;
	HeadPoint = NULL;
	CurPoint = HeadPoint;
	m_point_num_cnt = 1;
}



void CSplitSDIDoc::DeletePoint()
{
	if (HeadPoint == NULL||m_stress_point_no==0)
		return;
	myVertex* pPre, *pCurrent;
	pPre = HeadPoint;
	pCurrent = pPre->next;
	while (pCurrent)
	{
		if (pCurrent->num == m_stress_point_no)
		{
			break;
		}
		pPre = pCurrent;
		pCurrent = pCurrent->next;
	}
	if (pCurrent == NULL)
	{
		//MessageBox(("找不到这个点"));
		//这个MessageBox是封装在对话框中的，只能在对话框中被调用
		MessageBox(NULL, _T("查找这个点失败"), _T("提示"), MB_OK);
	}
	else
	{
		pPre->next = pCurrent->next;
		delete pCurrent;
		//删除后，重点编号就不存在了，所以无法继续显示
		m_stress_point_no = 0;
		flag_show_stress = 0;
		MessageBox(NULL, _T("删除成功"), _T("提示"), MB_OK);
	}
	//删除完成后对它之后的编号进行序号减一操作
	myVertex*temp = pPre->next;
	while (temp!= NULL)
	{
		temp->num-=1;
		temp = temp->next;
	}
	//计数器也要减一
	m_point_num_cnt -= 1;
	//如果没有点了，进行清零操作
	if (m_point_num_cnt == 1)
	{
		HeadPoint = NULL;
		CurPoint = HeadPoint;
	}
}


void CSplitSDIDoc::AddPoint(myVertex* p)
{
	if (CurPoint == NULL)
	{
		HeadPoint = new myVertex;
		HeadPoint->next = new myVertex;
		CurPoint = HeadPoint->next;
		CurPoint->num = m_point_num_cnt++;
		CurPoint->x = p->x;
		CurPoint->y = p->y;
		CurPoint->z = p->z;
		CurPoint->sign = p->sign;
		CurPoint->quan = p->quan;
		CurPoint->next = NULL;
	}
	else
	{
		CurPoint->next = new myVertex;
		CurPoint = CurPoint->next;
		CurPoint->num = m_point_num_cnt++;
		CurPoint->x = p->x;
		CurPoint->y = p->y;
		CurPoint->z = p->z;
		CurPoint->sign = p->sign;
		CurPoint->quan = p->quan;
		CurPoint->next = NULL;
	}

}


void CSplitSDIDoc::OnBnClickedButtonSubmit()
{

}


void CSplitSDIDoc::OnRandom()
{
	CSetRan setran;
	DeleteVertex();
	if (IDOK == setran.DoModal())
	{
		m_random = setran.m_ran_num;
		srand((int)time(0));
		for (int i = 0; i < m_random; i++)
		{
			myVertex* point = new myVertex;
			//do
			//{
			//	point->x = (float)((float)rand() / RAND_MAX)*m_range_x;
			//} while (point->x ==0.0 || point->x == m_range_x);
			//do
			//{
			//	point->y = (float)((float)rand() / RAND_MAX)*m_range_y;
			//} while (point->y == 0.0 || point->y == m_range_y);			
			//do
			//{
			//	point->z = (float)((float)rand() / RAND_MAX)*m_range_z;
			//} while (point->z == 0.0 || point->z == m_range_z);
			//point->y=  (float)((float)rand() / RAND_MAX)*m_range_y;
			//point->z = (float)((float)rand() / RAND_MAX)*m_range_z;
			//point->y = rand()%(m_range_y)+1;
			//point->z = rand()%(m_range_z)+1;
			do
			{
				//point->x = random(m_range_x) + 1;
				point->x = rand() % 100 / (double)101;
				point->x *= m_range_x;
			} while (point->x == 0 || point->x == m_range_x);
			do
			{
				//point->y = random(m_range_y) + 1;
				point->y = rand() % 100 / (double)101;
				point->y *= m_range_y;
			} while (point->y == 0 || point->y == m_range_y);
			do
			{
				//point->z = random(m_range_z) + 1;
				point->z = rand() % 100 / (double)101;
				point->z *= m_range_z;
			} while (point->z == 0 || point->z == m_range_z);
			point->quan = 1;
			int temp = random(100);
			if (temp > 50) point->sign = 0;
			else point->sign = 1;
			point->next = NULL;
			AddPoint(point);
		}
		UpdateAllViews(NULL);
	}
}



void CSplitSDIDoc::OnGenerate()
{
	// TODO: 在此添加命令处理程序代码
	
	
}
