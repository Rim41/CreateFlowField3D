#pragma once


// CRandomAdd �Ի���

class CRandomAdd : public CDialogEx
{
	DECLARE_DYNAMIC(CRandomAdd)

public:
	CRandomAdd(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRandomAdd();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_ran_num;
//	afx_msg void OnBnClickedButtonSubmit();
	afx_msg void OnRandom();
	// �����Ƿ��ύ
	int m_type;
	afx_msg void OnBnClickedButtonSubmit();
};
