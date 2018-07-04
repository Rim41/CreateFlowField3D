
// SplitSDIView.h : CSplitSDIView ��Ľӿ�
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
protected: // �������л�����
	CSplitSDIView();
	DECLARE_DYNCREATE(CSplitSDIView)

// ����
public:
	CSplitSDIDoc* GetDocument() const;

	int plusNum;//����ɵ�����
	int minusNum;//����ɵ�����
	int totalNum;//���е����Ŀ
	CString vectorData;//���������ļ�����
	void setPoint(myVertex p);
// ����
public:

// ��д
public:
	//virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:

	CPoint MouseDownPoint;
	double X_Angle;
	double Y_Angle;
	CString myText;//�ϲ�����
	CString myInfo;//������ʾ����
	void OnDrawGL(CDC* pDC);//���ƺ���
	void drawMyText();	//��ʾ��ʾ����,���Ը���

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

// ���ɵ���Ϣӳ�亯��
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
	CWinThread* m_pThread;     // �̶߳���ָ��
	HANDLE h1, h2; //�����߳̾��
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

#ifndef _DEBUG  // SplitSDIView.cpp �еĵ��԰汾
inline CSplitSDIDoc* CSplitSDIView::GetDocument() const
   { return reinterpret_cast<CSplitSDIDoc*>(m_pDocument); }
#endif

