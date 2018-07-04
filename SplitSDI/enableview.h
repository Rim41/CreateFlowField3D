#pragma once
#include "atltypes.h"
#include "afxmt.h"


// enableview 视图

class enableview : public CView
{
	DECLARE_DYNCREATE(enableview)

protected:
	enableview();           // 动态创建所使用的受保护的构造函数
	virtual ~enableview();

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
private:
	// Windows设备描述表
	CDC* m_pDC;
	// OpenGL渲染描述表
	HGLRC m_hRC;
	// 客户区大小
	CRect m_ClientRect;
	// 窗口的比例
	double m_dAspectRatio;
	// 调色板
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

	//鼠标控制变量
	float PI = 3.1415926;
	float c = PI / 180.0f;						//弧度和角度转换参数
	int du = 90, oldmy = -1, oldmx = -1;		//du是视点绕y轴的角度,opengl里默认y轴是上方向
	float r = 5.0f, h = 3.0f;					//r是视点绕y轴的半径,h是视点高度即在y轴上的坐标
	GLfloat rotate_x = 0.0;
	GLfloat rotate_y = 0.0;
	GLfloat rotate_z = 0.0;
	//缩放
	GLfloat scale = 0.5;
	// 键盘控制	对应x,y,z方向旋转
};


