
// SplitSDIDoc.h : CSplitSDIDoc ��Ľӿ�
//


#pragma once
#include "MyVertex.h"

class CSplitSDIDoc : public CDocument
{
protected: // �������л�����
	CSplitSDIDoc();
	DECLARE_DYNCREATE(CSplitSDIDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ʵ��
public:
	virtual ~CSplitSDIDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ����Ϊ����������������������ݵ� Helper ����
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	myVertex* CurPoint;
	myVertex* HeadPoint;

	int m_range_x;
	int m_range_y;
	int m_range_z;
	int m_stress_point_no;

	int flag_show_stress;
	int flag_show_all_num;

	void DeleteVertex();
	void DeletePoint();
	// �������������ж��ٸ���
	int m_point_num_cnt;
	void AddPoint(myVertex* p);
	afx_msg void OnBnClickedButtonSubmit();
	// ������ɵĵ������
	int m_random;
	afx_msg void OnRandom();
	afx_msg void OnGenerate();
};
