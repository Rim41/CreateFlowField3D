#pragma once


// CSetRan �Ի���

class CSetRan : public CDialogEx
{
	DECLARE_DYNAMIC(CSetRan)

public:
	CSetRan(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetRan();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_RANDOM };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int m_ran_num;
};
