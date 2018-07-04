
// SplitSDIDoc.h : CSplitSDIDoc 类的接口
//


#pragma once
#include "MyVertex.h"

class CSplitSDIDoc : public CDocument
{
protected: // 仅从序列化创建
	CSplitSDIDoc();
	DECLARE_DYNCREATE(CSplitSDIDoc)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CSplitSDIDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
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
	// 计数器，计算有多少个点
	int m_point_num_cnt;
	void AddPoint(myVertex* p);
	afx_msg void OnBnClickedButtonSubmit();
	// 随机生成的点的数量
	int m_random;
	afx_msg void OnRandom();
	afx_msg void OnGenerate();
};
