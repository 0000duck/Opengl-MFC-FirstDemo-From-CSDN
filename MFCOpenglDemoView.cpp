
// MFCOpenglDemoView.cpp : CMFCOpenglDemoView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_PAINT()
END_MESSAGE_MAP()

// CMFCOpenglDemoView ����/����

CMFCOpenglDemoView::CMFCOpenglDemoView()
{
	// TODO:  �ڴ˴���ӹ������
    this->m_GLPixelIndex = 0;
    this->m_hGLContext = NULL;

}

CMFCOpenglDemoView::~CMFCOpenglDemoView()
{
}

BOOL CMFCOpenglDemoView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
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

// CMFCOpenglDemoView ����

void CMFCOpenglDemoView::OnDraw(CDC* /*pDC*/)
{
	CMFCOpenglDemoDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMFCOpenglDemoView ��ӡ

BOOL CMFCOpenglDemoView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMFCOpenglDemoView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMFCOpenglDemoView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CMFCOpenglDemoView ���

#ifdef _DEBUG
void CMFCOpenglDemoView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCOpenglDemoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCOpenglDemoDoc* CMFCOpenglDemoView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCOpenglDemoDoc)));
	return (CMFCOpenglDemoDoc*)m_pDocument;
}
#endif //_DEBUG


// CMFCOpenglDemoView ��Ϣ�������


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
	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}


void CMFCOpenglDemoView::OnDestroy()
{
	CView::OnDestroy();

	// TODO:  �ڴ˴������Ϣ����������
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

	// TODO:  �ڴ˴������Ϣ����������
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
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CView::OnPaint()

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
