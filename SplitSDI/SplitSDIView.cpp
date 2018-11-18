
// SplitSDIView.cpp : CSplitSDIView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "SplitSDI.h"
#endif

#include "SplitSDIDoc.h"
#include "SplitSDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "enableview.h"
#include <vector>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>
#include <string.h>
#include <math.h>
#define random(x) (rand()%x)
using namespace std;



static int m_ord = 0;
static int flag = 0;

static int flag_show_num=1;
static int show_stress_no = 0;
static int flag_show_stress = 0;

int ran = 5;
int xnum, ynum, znum;
double constant = 1;

// CSplitSDIView

IMPLEMENT_DYNCREATE(CSplitSDIView, enableview)

BEGIN_MESSAGE_MAP(CSplitSDIView, enableview)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CSplitSDIView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
//	ON_WM_UPDATEUISTATE()
ON_COMMAND(ID_GENERATE, &CSplitSDIView::OnGenerate)
ON_COMMAND(ID_SAVE_COOR, &CSplitSDIView::OnSaveCoor)
ON_COMMAND(ID_READ_COOR, &CSplitSDIView::OnReadCoor)
END_MESSAGE_MAP()

// CSplitSDIView ����/����

CSplitSDIView::CSplitSDIView()
	: mul(0)
{
	// TODO: �ڴ˴���ӹ������
	m_ord = 1;
	mul = 1;
	totalNum = 0;
	constant = 11e-11;
	xnum = ynum = znum = 10;

}

void CSplitSDIView::OnDrawGL(CDC * pDC)
{
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, scale);		//��������
	
	gluLookAt(r*cos(c*du), h, r*sin(c*du), 0, 0, 0, 0, 1, 0); //���ӵ㿴Զ��,y�᷽��(0,1,0)���Ϸ�������϶�
															  //�����������Ϊ���Լ����Դ���
															  //��һ�����ݾ����Դ���λ��
															  //�ڶ������ݾ����۾����������λ��
															  //���������ͷ������ķ�����Ϊ���������ͷ��ͬһ�����壩��
	glRotatef(this->rotate_x, 1.0, 0.0, 0.0);
	glRotatef(this->rotate_y, 0.0, 1.0, 0.0);
	glRotatef(this->rotate_z, 0.0, 0.0, 1.0);
	if (m_ord) ordination();
	//���m_ord=1˵���û�Ҫ����ʾ��������������ordination�����������ͷ����ͷ

	CSplitSDIDoc* pDoc = (CSplitSDIDoc*)GetDocument();
	myVertex* temp = pDoc->HeadPoint;
	//����ͷ����Ƿ�Ϊ�����ж��Ƿ��е���Ҫ����
	if(temp!=NULL)
	{
		while (temp->next != NULL)
		{
			temp = temp->next;
			glTranslatef(temp->x/mul, temp->y/mul, temp->z/mul);

			//���������Ǳ�ǵĵ㣬������Ҫ��ʾ��ǣ���ô��������ʾһ�����ĵ��ص��
			if (temp->num == pDoc->m_stress_point_no && pDoc->flag_show_stress )
			{
				glColor3f(0.5f, 0.5f, 1.0f);
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				glutSolidCube(0.2);
			}

			//����ʵ�ĵĵ�
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			if (temp->sign)	glColor3f(0.0f, 0.0f, 0.0f);//��ɫ��ʾ�����
			else glColor3f(1.0f, 0.0f, 0.0f);			//��ɫ��ʾ�����
			glutSolidCube(0.1);
			

			//���Ƶ�ı��
			string str_s = to_string(temp->num);
			const char * str = str_s.data();
			int n = strlen(str);
			if (pDoc->flag_show_all_num)
			{
				//�����Ҫ��ʾ��ţ���ô������
				glColor3f(0.0f, 0.0f, 0.0f);
				glRasterPos3f(0, 0, 0);
				for(int i=0;i<n;i++)
				glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *(str+i));
			}
			//�ָ����Ա���һ����Ļ���
			glTranslatef(-temp->x/mul, -temp->y/mul, -temp->z/mul);
		}
	}
	glPopMatrix();
	this->OnDraw(this->GetDC());
}

void CSplitSDIView::drawMyText()
{
	CDC *pDC = GetWindowDC();
	pDC->DrawText(myText, CRect(6, 6, 160, 420), DT_WORDBREAK); ReleaseDC(pDC);
	pDC->DrawText(myInfo, CRect(160, 420, 320, 840), DT_WORDBREAK); ReleaseDC(pDC);
}

CSplitSDIView::~CSplitSDIView()
{
}

BOOL CSplitSDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	if (!enableview::PreCreateWindow(cs)) {
		return FALSE;
	}

	return TRUE;
}

// CSplitSDIView ����

//void CSplitSDIView::OnDraw(CDC* /*pDC*/)
//{
//	CSplitSDIDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
//	if (!pDoc)
//		return;
//
//	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
//}


// CSplitSDIView ��ӡ


void CSplitSDIView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CSplitSDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CSplitSDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CSplitSDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CSplitSDIView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSplitSDIView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CSplitSDIView ���

#ifdef _DEBUG
void CSplitSDIView::AssertValid() const
{
	CView::AssertValid();
}

void CSplitSDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSplitSDIDoc* CSplitSDIView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSplitSDIDoc)));
	return (CSplitSDIDoc*)m_pDocument;
}
#endif //_DEBUG


// CSplitSDIView ��Ϣ�������


BOOL CSplitSDIView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	//return enableview::PreTranslateMessage(pMsg);
	if (pMsg->message == WM_KEYDOWN)  // If a keydown message
	{

		if (pMsg->wParam == _T('W'))
		{

			this->rotate_x -= 6.0;
			if (this->rotate_x > 360)this->rotate_x = -360;
			this->InvalidateRect(NULL, FALSE);
		}
		if (pMsg->wParam == _T('S'))
		{

			this->rotate_x += 6.0;
			if (this->rotate_x < -360)this->rotate_x = 360;
			this->InvalidateRect(NULL, FALSE);
		}
		if (pMsg->wParam == _T('A'))
		{

			this->rotate_y -= 6.0;
			if (this->rotate_y < -360)this->rotate_y = 360;
			this->InvalidateRect(NULL, FALSE);
		}
		if (pMsg->wParam == _T('D'))
		{

			this->rotate_y += 6.0;
			if (this->rotate_y > 360)this->rotate_y = -360;
			this->InvalidateRect(NULL, FALSE);
		}
		if (pMsg->wParam == _T('Q'))
		{
			if ((scale + 2)  <  10)
				scale += 2;

			this->InvalidateRect(NULL, FALSE);
		}
		if (pMsg->wParam == _T('E'))
		{
			scale -= 2;

			this->InvalidateRect(NULL, FALSE);
		}
	}

	return CView::PreTranslateMessage(pMsg);
}

int CSplitSDIView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (enableview::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}

void CSplitSDIView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	enableview::OnKeyDown(nChar, nRepCnt, nFlags);
}

void GLGrid(float pt1x, float pt1y, float pt1z, float pt2x, float pt2y, float pt2z, int numx,int numy,int numz)
//��������ǰ������������㣬���������յ㣬num�ǻ����ٶ�
{

	const float _xLen = (pt2x - pt1x) / numx;
	const float _yLen = (pt2y - pt1y) / numy;
	const float _zLen = (pt2z - pt1z) / numz;
	glLineWidth(1.f);
	glLineStipple(1, 0x0303);//������ʽ

	glBegin(GL_LINES);
	glEnable(GL_LINE_SMOOTH);

	int xi = 0;
	int yi = 0;
	int zi = 0;

	//����ƽ����X��ֱ��
	for (zi = 0; zi <= numz; zi++)
	{
		float z = _zLen * zi + pt1z;
		for (yi = 0; yi <= numy; yi++)
		{
			float y = _yLen * yi + pt1y;
			glVertex3f(pt1x, y, z);
			glVertex3f(pt2x, y, z);
		}
	}


	//����ƽ����Y��ֱ��
	for (zi = 0; zi <= numz; zi++)
	{
		float z = _zLen * zi + pt1z;
		for (xi = 0; xi <= numx; xi++)
		{
			float x = _xLen * xi + pt1x;
			glVertex3f(x, pt1y, z);
			glVertex3f(x, pt2y, z);
		}
	}
	//����ƽ����Z��ֱ��
	for (yi = 0; yi <= numy; yi++)
	{
		float y = _yLen * yi + pt1y;
		for (xi = 0; xi <= numx; xi++)
		{
			float x = _xLen * xi + pt1x;
			glVertex3f(x, y, pt1z);
			glVertex3f(x, y, pt2z);
		}
	}
	glEnd();
}


void CSplitSDIView::ordination()
{
	char text[] = { 'X','Y','Z' };
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	glEnable(GL_POINT_SMOOTH);                   //���÷�����
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);       //���÷�����
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	//�������һ�����������ת
	glRotatef(-45, 0.0, 1.0, 0.0);

	CSplitSDIDoc* pDoc = (CSplitSDIDoc*)GetDocument();

	
	int viewX, viewY, viewZ;
	//Ĭ�������ʾ10x10x10���������񣬱������Χ���������͹�Լ���������֮��
	viewX = pDoc->m_range_x;
	viewY = pDoc->m_range_y;
	viewZ = pDoc->m_range_z;

	if ((viewX > 100 && viewX <= 1000) ||
		(viewY > 100 && viewY <= 1000) ||
		(viewZ > 100 && viewZ <= 1000))
	{
		viewX = ceil((double)viewX / 100);
		viewY = ceil((double)viewY / 100);
		viewZ = ceil((double)viewZ / 100);
		mul = 100;
	}
	else
	{
		if ((viewX > 10 && viewX <= 100) ||
			(viewY > 10 && viewY <= 100) ||
			(viewZ > 10 && viewZ <= 100))
		{
			viewX = ceil((double)viewX / 10);
			viewY = ceil((double)viewY / 10);
			viewZ = ceil((double)viewZ / 10);
			mul = 10;
		}
	}

	string str_s_x = to_string(pDoc->m_range_x);
	string str_s_y = to_string(pDoc->m_range_y);
	string str_s_z = to_string(pDoc->m_range_z);
	const char * str_x = str_s_x.data();
	const char * str_y = str_s_y.data();
	const char * str_z = str_s_z.data();
	int nx, ny, nz;
	nx = strlen(str_x);
	ny = strlen(str_y);
	nz = strlen(str_z);


	//����
	//XOZƽ��
	glPushMatrix();
	glColor3f(0.5f, 0.5f, 0.5f);
	glTranslatef(-viewX / 2, -viewX / 2, -viewX / 2);
	GLGrid(0, 0, 0, viewX, 0, viewZ, viewX,viewY,viewZ);
	this->OnDraw(this->GetDC());
	glPopMatrix();

	//XOYƽ��
	glPushMatrix();
	glTranslatef(-viewX / 2, -viewX / 2, -viewX / 2);
	glColor3f(0.5f, 0.5f, 0.5f);
	GLGrid(0, 0, 0, viewX, viewY, 0, viewX, viewY, viewZ);
	this->OnDraw(this->GetDC());
	glPopMatrix();

	//YOZƽ��
	glPushMatrix();
	glTranslatef(-viewX / 2, -viewX / 2, -viewX / 2);
	glColor3f(0.5f, 0.5f, 0.5f);

	GLGrid(0, 0, 0, 0, viewY, viewZ, viewX, viewY, viewZ);
	this->OnDraw(this->GetDC());
	glPopMatrix();

	//x��ɫ
	glTranslatef(-viewX / 2, -viewX / 2, -viewX / 2);
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(1.2*viewX, 0.0f, 0.0f);
	glEnd();

	glPushMatrix();
	glTranslatef(viewX, 0.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glRasterPos3f(0, 0, 0);
	for (int i = 0; i < nx; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *(str_x + i));
	}

	glTranslatef(0.2*viewX, 0.0f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glutWireCone(0.027, 0.09, 10, 10);//���Ƽ�ͷ
	glColor3f(0.0f, 0.0f, 0.0f);
	glRasterPos3f(0, 0, 0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[0]);
	glTranslatef(-0.2*viewX, 0.0f, 0.0f);

	glPopMatrix();


	//y��ɫ
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0, 1.2*viewY, 0.0f);
	glEnd();

	glPushMatrix();
	glTranslatef(0.0f, viewY, 0.0f);
	glColor3f(0.0f, 0.0f, 0.0f);
	glRasterPos3f(0, 0, 0);
	for (int i = 0; i < ny; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *(str_y + i));
	}
	glTranslatef(0.0, 0.2*viewY, 0.0f);
	glRotatef(90.0f, -1.0f, 0.0f, 0.0f);
	glutWireCone(0.027, 0.09, 10, 10);
	glColor3f(0.0f, 0.0f, 0.0f);
	glRasterPos3f(0, 0, 0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[1]);


	glPopMatrix();


	//z��ɫ
	glColor3f(0.0f, 0.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0, 0.0f, 1.2*viewZ);
	glEnd();

	glPushMatrix();
	glTranslatef(0.0, 0.0f, viewZ);
	glColor3f(0.0f, 0.0f, 0.0f);
	glRasterPos3f(0, 0, 0);
	for (int i = 0; i < nz; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *(str_z + i));
	}
	glTranslatef(0.0, 0.0f, 0.2*viewZ);
	glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
	glutWireCone(0.027, 0.09, 10, 10);
	glColor3f(0.0f, 0.0f, 0.0f);
	glRasterPos3f(0, 0, 0);
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, text[2]);

	glPopMatrix();


	glDisable(GL_BLEND);
	glDisable(GL_LINE_SMOOTH);
	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_POLYGON_SMOOTH);
}



void CSplitSDIView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	//��ӦUpdateAllViews
	//ȫ�����ܶ�ʹ���ػ漴���������
	CDC* ppDC = GetWindowDC();
	OnDrawGL(ppDC);
	this->OnDraw(this->GetDC());
}


void CSplitSDIView::OnGenerate()
{
	CSplitSDIDoc* pDoc = (CSplitSDIDoc*)GetDocument();
	xnum = pDoc->m_range_x;
	ynum = pDoc->m_range_y;
	znum = pDoc->m_range_z;
	CString str = _T("");//���������
	str += "# topofea DataFile Version 3.0  XYZ field \n";
	str += "DIMENSIONS ";
	CString s_xnum, s_ynum, s_znum;
	s_xnum.Format(_T("%d "), xnum);
	s_ynum.Format(_T("%d "), ynum);
	s_znum.Format(_T("%d "), znum);
	str += s_xnum;
	str += s_ynum;
	str += s_znum;

	//if (xnum == 1 || ynum == 1 || znum == 1)
	//{

	//}
	//else
	{
		str += "\n";
		str += "X_COORDINATES\n";
		for (int x = 0; x < xnum; x++)
		{
			CString tem;
			tem.Format(_T("%d "), x);
			str += tem;
		}
		str += "\n";
		str += "Y_COORDINATES\n";
		for (int y = 0; y < ynum; y++)
		{
			CString tem;
			tem.Format(_T("%d "), y);
			str += tem;
		}
		str += "\n";
		str += "Z_COORDINATES\n";
		for (int z = 0; z < znum; z++)
		{
			CString tem;
			tem.Format(_T("%d "), z);
			str += tem;
		}
		str += "\n";
		CString temp = _T("");
		int total = (xnum)*(ynum)*(znum);
		struct MyStorage *output = new MyStorage[total];
		memset(output, 0, total * sizeof(MyStorage));
		//һ��Ҫʹ��memset��ʼ��


		myVertex* pTemp = pDoc->CurPoint;
		if (pTemp == NULL)
		{
			if (pTemp == NULL)
			{
				MessageBox(_T("����û�������"), _T("������ʾ"), MB_OK);
				return;
			}
			else
			{
				pTemp = pTemp->next->next;
			}
		}
		else
		{
			pTemp = pDoc->HeadPoint->next;
		}

		int cnt = 0;
		int cnt_roll = 0;
		while (pTemp != NULL)
		{
			//�����ļ��Ķ�ȡ˳�����ȱ�X��Y��Z
			for (double i = 0.5; i <= znum - 0.5; i++)
			{
				for (double j = 0.5; j <= ynum - 0.5; j++)
				{
					for (double k = 0.5; k <= xnum - 0.5; k++)
					{
						//double tempCon = pow(i - pTemp->x, 2.0) + pow(j - pTemp->y, 2.0) + pow(k - pTemp->z, 2.0);
						//tempCon = (pTemp->quan)*constant / pow(tempCon, 3);
						//if (pTemp->sign)
						//{
						//	output[cnt].xx += (tempCon*(k - pTemp->x));
						//	output[cnt].yy += (tempCon*(j - pTemp->y));
						//	output[cnt].zz += (tempCon*(i - pTemp->z));
						//}
						//else
						//{
						//	output[cnt].xx += (-1)*(tempCon*(k - pTemp->x));
						//	output[cnt].yy += (-1)*(tempCon*(j - pTemp->y));
						//	output[cnt].zz += (-1)*(tempCon*(i - pTemp->z));
						//}

						double temp = 0.0;
						double temp2 = 0.0;
						temp2 = pow(k - pTemp->x, 2.0) + pow(j - pTemp->y, 2.0) + pow(i - pTemp->z, 2.0);
						temp2 = pow(temp2, 0.5);
						temp2 = abs(temp2);

						if (pTemp->sign)
						{
							temp = pTemp->quan / (constant*pow(temp2, 3));
						}
						else
						{
							temp = (-1.0)*pTemp->quan / (constant*pow(temp2, 3));
						}

						output[cnt].xx += temp * (k - pTemp->x);
						output[cnt].yy += temp * (j - pTemp->y);
						output[cnt].zz += temp * (i - pTemp->z);

						cnt++;
					}
				}
			}
			cnt = 0;
			pTemp = pTemp->next;
		}

		for (int i = 0; i < total; i++)
		{
			temp.Format(_T("%f"), output[i].xx);
			str += temp;
			str += " ";
			temp.Format(_T("%f"), output[i].yy);
			str += temp;
			str += " ";
			temp.Format(_T("%f"), output[i].zz);
			str += temp;
			str += "\n";
		}
	}


	
	//delete output;
	CString m_txtName = _T("myField");
	CStdioFile file;
	CString filepath;
	TCHAR szFilter[] = _T("�����ļ�(*.tpf)|*.tpf|�����ļ�(*.*)|*.*||");
	CFileDialog filedlg(FALSE, _T("tpf"), m_txtName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	if (IDOK == filedlg.DoModal())
	{
		filepath = filedlg.GetPathName();
		file.Open(filepath, CFile::modeCreate | CFile::modeWrite | CFile::typeText);
		file.WriteString(str);
		file.Close();
	}
}


void CSplitSDIView::OnSaveCoor()
{
	// TODO: �ڴ���������������
	CString str = _T("");
	CSplitSDIDoc* pDoc = (CSplitSDIDoc*)GetDocument();
	myVertex* pTemp = pDoc->HeadPoint;
	if (pTemp == NULL)
	{
		MessageBox(_T("����û�������"), _T("������ʾ"), MB_OK);
		return;
	}
	pTemp = pTemp->next;
	str += "Point Infomation:\n";
	str += "No\tx\ty\tz\n";
	while (pTemp != NULL)
	{
		CString s_no, s_x, s_y, s_z, s_q, s_sign;
		s_no.Format(_T("%d\t"), pTemp->num);
		s_x.Format(_T("%.2f\t"), pTemp->x);
		s_y.Format(_T("%.2f\t"), pTemp->y);
		s_z.Format(_T("%.2f\t"), pTemp->z);
		s_q.Format(_T("%.2f\t"), pTemp->quan);
		s_sign.Format(_T("%d"), pTemp->sign);
		str += s_no;
		str += s_x;
		str += s_y;
		str += s_z;
		str += s_q;
		str += s_sign;
		str += "\n";
		pTemp = pTemp->next;
	}

	CString m_txtName = _T("myCoor");
	CStdioFile file;
	CString filepath;
	TCHAR szFilter[] = _T("�����ļ�(*.mf)|*.mf|�����ļ�(*.*)|*.*||");
	CFileDialog filedlg(FALSE, _T("mf"), m_txtName, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, this);
	if (IDOK == filedlg.DoModal())
	{
		filepath = filedlg.GetPathName();
		file.Open(filepath, CFile::modeCreate | CFile::modeWrite | CFile::typeText);
		file.WriteString(str);
		file.Close();
		MessageBox(_T("���ݵ���Ϣ����ɹ���"));
	}
}


void CSplitSDIView::OnReadCoor()
{
	// TODO: �ڴ���������������
	wchar_t filters[] = L"���������ļ�(*.mf)|*.mf|�����ļ�(*.*)|*.*||";
	CFileDialog fileDlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, filters);
	if (fileDlg.DoModal() == IDOK)
	{
		CString strbuf = fileDlg.GetPathName();
		USES_CONVERSION;
		char *Filename = T2A(strbuf.GetBuffer(0));
		ReadFile(Filename);
		MessageBox(_T("��ȡ�ļ��ɹ�"));
	}
	
	CSplitSDIDoc* pDoc =(CSplitSDIDoc*) GetDocument();
	pDoc->UpdateAllViews(NULL);	
}


void CSplitSDIView::ReadFile(char* Filename)
{
	CSplitSDIDoc* pDoc = (CSplitSDIDoc*)GetDocument();
	pDoc->DeleteVertex();
	int cnt = 0;
	ifstream in(Filename);
	string aline;//���ж��뱣�浽aline
	while (getline(in, aline))
	{
		cnt++;
		myVertex* temp = new myVertex;
		if (cnt<=2)
		{
			continue;
		}
		istringstream sin(aline);
		sin >> temp->num >> temp->x >> temp->y >> temp->z >> temp->quan >> temp->sign;
		pDoc->AddPoint(temp);
	}
}
