#pragma once
#include "afxwin.h"



// CShowDlgInput ������ͼ

class CShowDlgInput : public CFormView
{
	DECLARE_DYNCREATE(CShowDlgInput)

protected:
	CShowDlgInput();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CShowDlgInput();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_INPUT };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_rangeX;
	int m_rangeY;
	int m_rangeZ;
	CButton m_ctrlRadio;
	int m_chargeType;
	double m_coorX;
	double m_coorY;
	double m_coorZ;
	int m_quan;
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonUpdatecoor();
	CFont m_editControl;
	virtual void OnInitialUpdate();
};


