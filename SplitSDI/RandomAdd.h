#pragma once


// CRandomAdd 对话框

class CRandomAdd : public CDialogEx
{
	DECLARE_DYNAMIC(CRandomAdd)

public:
	CRandomAdd(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRandomAdd();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_ran_num;
//	afx_msg void OnBnClickedButtonSubmit();
	afx_msg void OnRandom();
	// 决定是否提交
	int m_type;
	afx_msg void OnBnClickedButtonSubmit();
};
