#pragma once


// CSetRan 对话框

class CSetRan : public CDialogEx
{
	DECLARE_DYNAMIC(CSetRan)

public:
	CSetRan(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetRan();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RANDOM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_ran_num;
};
