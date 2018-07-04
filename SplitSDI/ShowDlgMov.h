#pragma once
#include "afxcmn.h"
#include "afxwin.h"



// CShowDlgMov 窗体视图

class CShowDlgMov : public CFormView
{
	DECLARE_DYNCREATE(CShowDlgMov)

protected:
	CShowDlgMov();           // 动态创建所使用的受保护的构造函数
	virtual ~CShowDlgMov();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_MOV };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	int m_no;
	double m_display_x;
	double m_display_y;
	double m_display_z;
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonShowAll();
	afx_msg void OnBnClickedButtonCloseAll();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonClr();

	CSliderCtrl m_slider_x;
	CSliderCtrl m_slider_y;
	CSliderCtrl m_slider_z;
	afx_msg

	void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	int m_current_x;
	int m_current_y;
	int m_current_z;
	afx_msg void OnBnClickedButtonCloseSearch();
	CSliderCtrl* m_sliderX;
	CSliderCtrl* m_sliderY;
	CSliderCtrl* m_sliderZ;
	CFont m_editFont;
};


