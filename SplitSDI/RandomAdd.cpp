// RandomAdd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SplitSDI.h"
#include "RandomAdd.h"
#include "afxdialogex.h"
#include "SplitSDIDoc.h"


// CRandomAdd �Ի���

IMPLEMENT_DYNAMIC(CRandomAdd, CDialogEx)

CRandomAdd::CRandomAdd(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_ran_num(0)
	, m_type(0)
{

}

CRandomAdd::~CRandomAdd()
{
}

void CRandomAdd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NUM, m_ran_num);
	DDV_MinMaxInt(pDX, m_ran_num, 0, 100000);
}


BEGIN_MESSAGE_MAP(CRandomAdd, CDialogEx)
//	ON_BN_CLICKED(IDC_BUTTON_SUBMIT, &CRandomAdd::OnBnClickedButtonSubmit)
ON_COMMAND(ID_RANDOM, &CRandomAdd::OnRandom)
ON_BN_CLICKED(IDC_BUTTON_SUBMIT, &CRandomAdd::OnBnClickedButtonSubmit)
END_MESSAGE_MAP()


// CRandomAdd ��Ϣ�������


//void CRandomAdd::OnBnClickedButtonSubmit()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//	CRandomAdd ran;
//	if (IDOK==ran.DoModal())
//	{
//		
//	}
//}


void CRandomAdd::OnRandom()
{
	//// TODO: �ڴ���������������
	//CRandomAdd randomadd;
	//if (IDOK == randomadd.DoModal())
	//{
	//	m_random = randomadd.m_ran_num;
	//}
	//else
	//	return;
	//srand((int)time(0));
	//for (int i = 0; i < m_random; i++)
	//{
	//	myVertex* point = new myVertex;;
	//	point->num = m_point_num_cnt++;
	//	point->x = random(m_range_x);
	//	point->y = random(m_range_y);
	//	point->z = random(m_range_z);
	//	point->quan = 1;
	//	int temp = random(100);
	//	if (temp > 50) point->sign = 0;
	//	else point->sign = 1;
	//	point->next = NULL;
	//	AddPoint(point);
	//}
}


void CRandomAdd::OnBnClickedButtonSubmit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_type = 1;
}
