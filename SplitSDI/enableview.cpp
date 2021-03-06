// enableview.cpp : 实现文件
//

#include "stdafx.h"
#include "SplitSDI.h"
#include "enableview.h"


// enableview

IMPLEMENT_DYNCREATE(enableview, CView)

enableview::enableview()
{
	scale = -20.0;
}

enableview::~enableview()
{
}

BEGIN_MESSAGE_MAP(enableview, CView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// enableview 绘图

void enableview::OnDraw(CDC* pDC)
{
	
	// TODO:  在此添加绘制代码
	CDocument* pDoc = GetDocument();



	static BOOL   bBusy = FALSE;				// 准备一个标志信号
	if (bBusy) return;							// 如果忙，则返回
	bBusy = TRUE;								// 置标志为忙，下面开始场景绘制
	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC); // 获取设备描述表

	m_Sec.Lock();
	// 清除颜色缓冲区和深度缓冲区
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	OnDrawGL(pDC);								// 调用场景绘制函数
	glFinish();									// 完成图形的绘制
	SwapBuffers(m_pDC->GetSafeHdc());			// 启用双缓冲
	bBusy = FALSE;								// 绘制完毕，置标志为空闲
	wglMakeCurrent(NULL, NULL);					// 释放OpenGL绘制描述表

	drawMyText();	//显示自定义的文字
	m_Sec.Unlock();
}


// enableview 诊断

#ifdef _DEBUG
void enableview::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void enableview::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// enableview 消息处理程序


int enableview::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	m_pDC = new CClientDC(this);

	// 初始化OpenGL

	InitializeOpenGL(m_pDC);

	// 释放OpenGL绘制描述表

	wglMakeCurrent(NULL, NULL);
	return 0;
}


void enableview::OnDestroy()
{
	wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);

	// 释放绘制描述表
	if (m_hRC != NULL) ::wglDeleteContext(m_hRC);

	if (m_hPalette)

		DeleteObject(m_hPalette);//释放调色板

								 // 释放Windows设备描述表
	if (m_pDC) delete m_pDC;
	CView::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}


void enableview::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	OutputDebugString(_T("onsize \n"));
	if (0 < cx && 0 < cy)
	{
		// 更新客户区，计算窗口的比例
		m_ClientRect.right = cx;
		m_ClientRect.bottom = cy;
		m_dAspectRatio = double(cx) / double(cy);
		// 获取OpenGL绘制描述表
		wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);

		// 设置视口变换
		glViewport(0, 0, cx, cy);
		// 设置透视变换
		glPushMatrix();
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluPerspective(40.0, m_dAspectRatio, 0.1f, 100.0f);		//把深度调大
		glTranslatef(0.0f, 0.0f, -4.f);
		glMatrixMode(GL_MODELVIEW);

		glPopMatrix();
		// 释放OpenGL绘制描述表

		wglMakeCurrent(NULL, NULL);
		// 更新窗口内容

		//Invalidate(TRUE);

	};

	Invalidate(TRUE);
	//this->OnDraw(this->GetDC());	//重绘界面
	OutputDebugString(_T("onsize over\n"));
}


BOOL enableview::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此添加专用代码和/或调用基类
	cs.style |= WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	//多文档应用程序要求

	cs.lpszClass = AfxRegisterWndClass(CS_OWNDC | CS_HREDRAW | CS_VREDRAW);
	return CView::PreCreateWindow(cs);
}


BOOL enableview::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	double a = zDelta / 120;
	if ((scale + a * 0.6)  <  10)
		scale += a * 0.6;

	this->InvalidateRect(NULL, FALSE);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void enableview::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if (nFlags & (MK_LBUTTON == TRUE)) {

		//MessageBox("mouse move function triggered!", "attentino", MB_OK);
		du += point.x - oldmx;				//鼠标在窗口x轴方向上的增量加到视点绕y轴的角度上，这样就左右转了
		h += 0.03f*(point.y - oldmy);		//鼠标在窗口y轴方向上的改变加到视点的y坐标上，就上下转了
		if (h>15.0f) h = 15.0f;				//视点y坐标作一些限制，不会使视点太奇怪
		else if (h<-5.0f) h = -5.0f;
		oldmx = point.x, oldmy = point.y;	//把此时的鼠标坐标作为旧值，为下一次计算增量做准备
											/*CString debug;
											debug.Format(_T("h,du= %0.3f %3d\n"), h, du);
											OutputDebugString(debug);*/
											//OnPaint();
		this->OnDraw(this->GetDC());	//重绘界面
	}
	else if (nFlags & (MK_RBUTTON == TRUE))
	{
		oldmx += point.x - oldmx;
		oldmy += point.y - oldmy;
		glTranslatef(oldmx, oldmy, -0.1f);
		this->OnDraw(this->GetDC());
		oldmx = point.x, oldmy = point.y;
	}
	else {
		oldmx = point.x, oldmy = point.y;
		//OutputDebugString(_T("mouse up\n"));
	}
	//CView::OnMouseMove(nFlags, point);
}


void enableview::OnDrawGL(CDC* pDC)
{
}


void enableview::drawMyText()
{
}


BOOL enableview::SetupPixelFormat()
{
	PIXELFORMATDESCRIPTOR pfd = {

		sizeof(PIXELFORMATDESCRIPTOR),    // pfd结构的大小
		1,                                // 版本号
		PFD_DRAW_TO_WINDOW |              // 支持在窗口中绘图
		PFD_SUPPORT_OPENGL |              // 支持 OpenGL
		PFD_DOUBLEBUFFER,                 // 双缓存模式
		PFD_TYPE_RGBA,                    // RGBA 颜色模式
		24,                               // 24 位颜色深度
		0, 0, 0, 0, 0, 0,                 // 忽略颜色位
		0,                                // 没有非透明度缓存
		0,                                // 忽略移位位
		0,                                // 无累加缓存
		0, 0, 0, 0,                       // 忽略累加位
		32,                               // 32 位深度缓存    
		0,                                // 无模板缓存
		0,                                // 无辅助缓存
		PFD_MAIN_PLANE,                   // 主层
		0,                                // 保留
		0, 0, 0                           // 忽略层,可见性和损毁掩模
	};

	int pixelformat;

	pixelformat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd);	//选择像素格式
	::SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd);		//设置像素格式

	if (pfd.dwFlags & PFD_NEED_PALETTE)

		SetupLogicalPalette();										//设置逻辑调色板

	return TRUE;
}


BOOL enableview::InitializeOpenGL(CDC* pDC)
{
	m_pDC = pDC;
	SetupPixelFormat();

	//生成绘制描述表
	m_hRC = ::wglCreateContext(m_pDC->GetSafeHdc());

	//置当前绘制描述表
	::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC);
	return TRUE;
}


void enableview::SetupLogicalPalette()
{
	struct
	{
		WORD Version;
		WORD NumberOfEntries;
		PALETTEENTRY aEntries[256];
	} logicalPalette = { 0x300, 256 };

	BYTE reds[] = { 0, 36, 72, 109, 145, 182, 218, 255 };
	BYTE greens[] = { 0, 36, 72, 109, 145, 182, 218, 255 };
	BYTE blues[] = { 0, 85, 170, 255 };

	for (int colorNum = 0; colorNum<256; ++colorNum)
	{
		logicalPalette.aEntries[colorNum].peRed =
			reds[colorNum & 0x07];

		logicalPalette.aEntries[colorNum].peGreen =
			greens[(colorNum >> 0x03) & 0x07];

		logicalPalette.aEntries[colorNum].peBlue =
			blues[(colorNum >> 0x06) & 0x03];

		logicalPalette.aEntries[colorNum].peFlags = 0;
	}
	m_hPalette = CreatePalette((LOGPALETTE*)&logicalPalette);
}
