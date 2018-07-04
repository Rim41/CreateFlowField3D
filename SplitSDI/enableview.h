#pragma once
#include "atltypes.h"
#include "afxmt.h"


// enableview ��ͼ

class enableview : public CView
{
	DECLARE_DYNCREATE(enableview)

protected:
	enableview();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~enableview();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
private:
	// Windows�豸������
	CDC* m_pDC;
	// OpenGL��Ⱦ������
	HGLRC m_hRC;
	// �ͻ�����С
	CRect m_ClientRect;
	// ���ڵı���
	double m_dAspectRatio;
	// ��ɫ��
	HPALETTE m_hPalette;
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	virtual void OnDrawGL(CDC* pDC);
	virtual void drawMyText();
	BOOL SetupPixelFormat();
	BOOL InitializeOpenGL(CDC* pDC);
	void SetupLogicalPalette();

	CCriticalSection m_Sec;

	//�����Ʊ���
	float PI = 3.1415926;
	float c = PI / 180.0f;						//���ȺͽǶ�ת������
	int du = 90, oldmy = -1, oldmx = -1;		//du���ӵ���y��ĽǶ�,opengl��Ĭ��y�����Ϸ���
	float r = 5.0f, h = 3.0f;					//r���ӵ���y��İ뾶,h���ӵ�߶ȼ���y���ϵ�����
	GLfloat rotate_x = 0.0;
	GLfloat rotate_y = 0.0;
	GLfloat rotate_z = 0.0;
	//����
	GLfloat scale = 0.5;
	// ���̿���	��Ӧx,y,z������ת
};


