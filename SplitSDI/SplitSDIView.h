
// SplitSDIView.h : CSplitSDIView 类的接口
//

#pragma once
#include "enableview.h"
#include "stdafx.h"
#include "MyVertex.h"
#include <stdlib.h>
#include <cmath>
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <vector>
using namespace std;



class CSplitSDIView : public enableview
{
protected: // 仅从序列化创建
	CSplitSDIView();
	DECLARE_DYNCREATE(CSplitSDIView)

// 特性
public:
	CSplitSDIDoc* GetDocument() const;

	int plusNum;//正电荷的数量
	int minusNum;//负电荷的数量
	int totalNum;//所有点的数目
	CString vectorData;//存放输出的文件向量
	void setPoint(myVertex p);
// 操作
public:

// 重写
public:
	//virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:

	CPoint MouseDownPoint;
	double X_Angle;
	double Y_Angle;
	CString myText;//上部文字
	CString myInfo;//下面提示文字
	void OnDrawGL(CDC* pDC);//绘制函数
	void drawMyText();	//显示提示文字,来自父类

	virtual ~CSplitSDIView();

	typedef struct MyStorage {
		double xx;
		double yy;
		double zz;
	}myStorage;
	//typedef struct MyStorage myStorage;


#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	BOOL read_block = false;
	CWinThread* m_pThread;     // 线程对象指针
	HANDLE h1, h2; //定义线程句柄
	BOOL stopSmooth = FALSE;
	void ordination();
	float worldx, worldy, worldz;
//	afx_msg void OnUpdateUIState(UINT /*nAction*/, UINT /*nUIElement*/);
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	afx_msg void OnGenerate();
	afx_msg void OnSaveCoor();
	afx_msg void OnReadCoor();
	void ReadFile(char* Filename);
	int mul;
};

#ifndef _DEBUG  // SplitSDIView.cpp 中的调试版本
inline CSplitSDIDoc* CSplitSDIView::GetDocument() const
   { return reinterpret_cast<CSplitSDIDoc*>(m_pDocument); }
#endif

