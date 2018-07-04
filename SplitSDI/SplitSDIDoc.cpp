
// SplitSDIDoc.cpp : CSplitSDIDoc ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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


// CSplitSDIDoc ����/����

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

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)
	SetTitle(_T("�������ɳ���3D"));
	return TRUE;
}




// CSplitSDIDoc ���л�

void CSplitSDIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}

#ifdef SHARED_HANDLERS

// ����ͼ��֧��
void CSplitSDIDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �޸Ĵ˴����Ի����ĵ�����
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

// ������������֧��
void CSplitSDIDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ���ĵ����������������ݡ�
	// ���ݲ���Ӧ�ɡ�;���ָ�

	// ����:     strSearchContent = _T("point;rectangle;circle;ole object;")��
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

// CSplitSDIDoc ���

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


// CSplitSDIDoc ����


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
		//MessageBox(("�Ҳ��������"));
		//���MessageBox�Ƿ�װ�ڶԻ����еģ�ֻ���ڶԻ����б�����
		MessageBox(NULL, _T("���������ʧ��"), _T("��ʾ"), MB_OK);
	}
	else
	{
		pPre->next = pCurrent->next;
		delete pCurrent;
		//ɾ�����ص��žͲ������ˣ������޷�������ʾ
		m_stress_point_no = 0;
		flag_show_stress = 0;
		MessageBox(NULL, _T("ɾ���ɹ�"), _T("��ʾ"), MB_OK);
	}
	//ɾ����ɺ����֮��ı�Ž�����ż�һ����
	myVertex*temp = pPre->next;
	while (temp!= NULL)
	{
		temp->num-=1;
		temp = temp->next;
	}
	//������ҲҪ��һ
	m_point_num_cnt -= 1;
	//���û�е��ˣ������������
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
	// TODO: �ڴ���������������
	
	
}
