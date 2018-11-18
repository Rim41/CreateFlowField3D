// ShowDlgInput.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SplitSDI.h"
#include "ShowDlgInput.h"
#include "MyVertex.h"
#include "SplitSDIDoc.h"
#include "tchar.h"

int FindMax(int a, int b, int c)
{
	return max(a, max(b, c));
}

int FindMin(int a, int b, int c)
{
	return min(a, min(b, c));
}

int cntnum = 1;
// CShowDlgInput

IMPLEMENT_DYNCREATE(CShowDlgInput, CFormView)

CShowDlgInput::CShowDlgInput()
	: CFormView(IDD_DIALOG_INPUT)
	, m_rangeX(10)
	, m_rangeY(10)
	, m_rangeZ(10)
	, m_chargeType(0)
	, m_coorX(5.0)
	, m_coorY(5.0)
	, m_coorZ(5.0)
	, m_quan(1)
{
	
}

CShowDlgInput::~CShowDlgInput()
{
}

void CShowDlgInput::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_XRANGE, m_rangeX);
	DDV_MinMaxInt(pDX, m_rangeX, 1, 1000);
	DDX_Text(pDX, IDC_EDIT_YRANGE, m_rangeY);
	DDV_MinMaxInt(pDX, m_rangeY, 1, 1000);
	DDX_Text(pDX, IDC_EDIT_ZRANGE, m_rangeZ);
	DDV_MinMaxInt(pDX, m_rangeY, 1, 1000);
	DDX_Control(pDX, IDC_RADIO_PLUS, m_ctrlRadio);
	DDX_Radio(pDX, IDC_RADIO_PLUS, m_chargeType);
	DDX_Text(pDX, IDC_EDIT_XCOOR, m_coorX);
	DDX_Text(pDX, IDC_EDIT_YCOOR, m_coorY);
	DDX_Text(pDX, IDC_EDIT_ZCOOR, m_coorZ);
	DDX_Text(pDX, IDC_EDIT_QUAN, m_quan);
	DDV_MinMaxInt(pDX, m_quan, 1, 10000000);
}

BEGIN_MESSAGE_MAP(CShowDlgInput, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CShowDlgInput::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_UPDATECOOR, &CShowDlgInput::OnBnClickedButtonUpdatecoor)
END_MESSAGE_MAP()


// CShowDlgInput ���

#ifdef _DEBUG
void CShowDlgInput::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CShowDlgInput::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CShowDlgInput ��Ϣ�������


void CShowDlgInput::OnBnClickedButtonAdd()
{
	UpdateData(TRUE);//ˢ�¿ؼ���ֵ����Ӧ�ı��������ⲿ�����ֵ�����ڲ�����
	CSplitSDIDoc* pDoc = (CSplitSDIDoc*)GetDocument();
	myVertex* p=new myVertex;
	p->x = m_coorX;
	p->y = m_coorY;
	p->z = m_coorZ;
	p->sign = (m_chargeType + 1) % 2;
	p->quan = m_quan;
	p->next = NULL;
	myVertex* q = new myVertex;
	
	if (pDoc->CurPoint != NULL)
	{
		q = pDoc->HeadPoint;
		while (q->next != NULL)
		{
			q = q->next;
			if (q->x == p->x &&
				q->y == p->y &&
				q->z == p->z)
			{
				MessageBox(_T("��λ���ѱ����ǣ�����ɾ���õ�"));
				UpdateData(FALSE);
				return;
			}
		}
	}

	if (p->x > pDoc->m_range_x ||
		p->y > pDoc->m_range_y ||
		p->z > pDoc->m_range_z)
	{
		MessageBox(_T("���õĵ㳬����Χ�����޸ĵ����ֵ"));
		UpdateData(FALSE);
		return;
	}
	
	pDoc->AddPoint(p);
	pDoc->UpdateAllViews(NULL);
	UpdateData(FALSE);//������������ؼ���ʾ
}


void CShowDlgInput::OnBnClickedButtonUpdatecoor()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	CSplitSDIDoc* pDoc = (CSplitSDIDoc *)GetDocument();
	int max = 0, min = 0;
	max = FindMax(m_rangeX, m_rangeY, m_rangeZ);
	min = FindMin(m_rangeX, m_rangeY, m_rangeZ);
	//if (max / min > 10)
	//{
	//	MessageBox(_T("�����õ�������������ʣ����޸�"));
	//	UpdateData(FALSE);
	//	return;
	//}
	pDoc->m_range_x = m_rangeX;
	pDoc->m_range_y = m_rangeY;
	pDoc->m_range_z = m_rangeZ;
	pDoc->UpdateAllViews(NULL);
	UpdateData(FALSE);
}


void CShowDlgInput::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: �ڴ����ר�ô����/����û���
	m_editControl.CreatePointFont(90, _T("΢���ź�"));
	GetDlgItem(IDC_EDIT_XRANGE)->SetFont(&m_editControl);
	GetDlgItem(IDC_EDIT_YRANGE)->SetFont(&m_editControl);
	GetDlgItem(IDC_EDIT_ZRANGE)->SetFont(&m_editControl);
	GetDlgItem(IDC_EDIT_XCOOR)->SetFont(&m_editControl);
	GetDlgItem(IDC_EDIT_YCOOR)->SetFont(&m_editControl);
	GetDlgItem(IDC_EDIT_ZCOOR)->SetFont(&m_editControl);
	GetDlgItem(IDC_EDIT_QUAN)->SetFont(&m_editControl);
	GetDlgItem(IDC_BUTTON_UPDATECOOR)->SetFont(&m_editControl);
	GetDlgItem(IDC_BUTTON_ADD)->SetFont(&m_editControl);
	GetDlgItem(IDC_RADIO_PLUS)->SetFont(&m_editControl);
	GetDlgItem(IDC_RADIO_MINUS)->SetFont(&m_editControl);
	GetDlgItem(IDC_STATIC1)->SetFont(&m_editControl);
	GetDlgItem(IDC_STATIC2)->SetFont(&m_editControl);
	GetDlgItem(IDC_STATIC3)->SetFont(&m_editControl);
	GetDlgItem(IDC_STATIC4)->SetFont(&m_editControl);
	GetDlgItem(IDC_STATIC5)->SetFont(&m_editControl);
	GetDlgItem(IDC_STATIC6)->SetFont(&m_editControl);
	GetDlgItem(IDC_STATIC7)->SetFont(&m_editControl);
	GetDlgItem(IDC_STATIC8)->SetFont(&m_editControl);
	GetDlgItem(IDC_STATIC9)->SetFont(&m_editControl);
	GetDlgItem(IDC_STATIC10)->SetFont(&m_editControl);
}


