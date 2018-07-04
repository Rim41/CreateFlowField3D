// SetRan.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SplitSDI.h"
#include "SetRan.h"
#include "afxdialogex.h"


// CSetRan �Ի���

IMPLEMENT_DYNAMIC(CSetRan, CDialogEx)

CSetRan::CSetRan(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_RANDOM, pParent)
	, m_ran_num(0)
{

}

CSetRan::~CSetRan()
{
}

void CSetRan::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NUM, m_ran_num);
	DDV_MinMaxInt(pDX, m_ran_num, 0, 10000000);
}


BEGIN_MESSAGE_MAP(CSetRan, CDialogEx)
END_MESSAGE_MAP()


// CSetRan ��Ϣ�������
