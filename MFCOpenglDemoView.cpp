
// MFCOpenglDemoView.cpp : CMFCOpenglDemoView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCOpenglDemo.h"
#endif

#include "MFCOpenglDemoDoc.h"
#include "MFCOpenglDemoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCOpenglDemoView

IMPLEMENT_DYNCREATE(CMFCOpenglDemoView, CView)

BEGIN_MESSAGE_MAP(CMFCOpenglDemoView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CMFCOpenglDemoView 构造/析构

CMFCOpenglDemoView::CMFCOpenglDemoView()
{
	// TODO:  在此处添加构造代码
    this->m_GLPixelIndex = 0;
    this->m_hGLContext = NULL;

}

CMFCOpenglDemoView::~CMFCOpenglDemoView()
{
}

BOOL CMFCOpenglDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式
    cs.style |= (WS_CLIPCHILDREN|WS_CLIPSIBLINGS);

	return CView::PreCreateWindow(cs);
}

BOOL CMFCOpenglDemoView::SetWindowPixelFormat(HDC hDC)
{
    PIXELFORMATDESCRIPTOR pixelDesc = 
    {
    sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW|PFD_SUPPORT_OPENGL|
        PFD_DOUBLEBUFFER|PFD_SUPPORT_GDI,
        PFD_TYPE_RGBA,
        24,
        0,0,0,0,0,0,
        0,
        0,
        0,
        0,0,0,0,
        32,
        0,
        0,
        PFD_MAIN_PLANE,
        0,
        0,0,0
    };

    this->m_GLPixelIndex = ChoosePixelFormat(hDC,&pixelDesc);
    if(this->m_GLPixelIndex == 0)
    {
        this->m_GLPixelIndex = 1;
        if(DescribePixelFormat(hDC,this->m_GLPixelIndex,sizeof(PIXELFORMATDESCRIPTOR),&pixelDesc) == 0)
        {
            return FALSE;
        }
    }

    if(SetPixelFormat(hDC,this->m_GLPixelIndex,&pixelDesc) == FALSE)
    {
        return FALSE;
    }
    return TRUE;
}

BOOL CMFCOpenglDemoView::CreateViewGLContext(HDC hDC)
{
    this->m_hGLContext = wglCreateContext(hDC);
    if(this->m_hGLContext == NULL)
    {
        return FALSE;
    }

    if(wglMakeCurrent(hDC,this->m_hGLContext) == FALSE)
    {
        return FALSE;
    }

    return TRUE;
}

// CMFCOpenglDemoView 绘制

void CMFCOpenglDemoView::OnDraw(CDC* /*pDC*/)
{
	CMFCOpenglDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
}


// CMFCOpenglDemoView 打印

BOOL CMFCOpenglDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCOpenglDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CMFCOpenglDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CMFCOpenglDemoView 诊断

#ifdef _DEBUG
void CMFCOpenglDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCOpenglDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCOpenglDemoDoc* CMFCOpenglDemoView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCOpenglDemoDoc)));
	return (CMFCOpenglDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCOpenglDemoView 消息处理程序


int CMFCOpenglDemoView::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if (CView::OnCreate( lpCreateStruct ) == -1)
		return -1;
    
    HWND hWnd = this->GetSafeHwnd();
    HDC hDC = ::GetDC(this->m_hWnd);

    if(this->SetWindowPixelFormat(hDC) == FALSE)
    {
        return 0;
    }

    if(this->CreateViewGLContext(hDC) == FALSE)
    {
        return 0;
    }
	// TODO:  在此添加您专用的创建代码

	return 0;
}


void CMFCOpenglDemoView::OnDestroy()
{
	CView::OnDestroy();

	// TODO:  在此处添加消息处理程序代码
    if(wglGetCurrentContext() != NULL)
    {
        wglMakeCurrent(NULL,NULL);
    }

    if(this->m_hGLContext != NULL)
    {
        wglDeleteContext(this->m_hGLContext);
        this->m_hGLContext = NULL;
    }
}


void CMFCOpenglDemoView::OnSize( UINT nType, int cx, int cy )
{
	CView::OnSize( nType, cx, cy );

	// TODO:  在此处添加消息处理程序代码
    GLsizei width,height;
    GLdouble aspect;
    width = cx;
    height = cy;

    if(cy == 0)
    {
        aspect = (GLdouble)width;
    }
    else
    {
        aspect = (GLdouble)width/(GLdouble)height;
    }

    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,500.0*aspect,0.0,500.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void CMFCOpenglDemoView::OnPaint()
{
	CPaintDC dc( this ); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CView::OnPaint()

	glLoadIdentity();
	glClear( GL_COLOR_BUFFER_BIT );
	glBegin( GL_POLYGON );
	glColor4f( 1.0f, 0.0f, 0.0f, 1.0f );
	glVertex2f( 100.0f, 50.0f );
	glColor4f( 0.0f, 1.0f, 0.0f, 1.0f );
	glVertex2f( 450.0f, 400.0f );
	glColor4f( 0.0f, 0.0f, 1.0f, 1.0f );
	glVertex2f( 450.0f, 50.0f );
	glEnd();
	glFlush();
	SwapBuffers( wglGetCurrentDC() );
}
