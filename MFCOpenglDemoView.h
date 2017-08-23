
// MFCOpenglDemoView.h : CMFCOpenglDemoView 类的接口
//

#pragma once


class CMFCOpenglDemoView : public CView
{
protected: // 仅从序列化创建
	CMFCOpenglDemoView();
	DECLARE_DYNCREATE(CMFCOpenglDemoView)

// 特性
public:
	CMFCOpenglDemoDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMFCOpenglDemoView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
    BOOL SetWindowPixelFormat(HDC hDC);
    BOOL CreateViewGLContext(HDC hDC);

    int m_GLPixelIndex;
    HGLRC m_hGLContext;

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
	afx_msg void OnDestroy();
	afx_msg void OnSize( UINT nType, int cx, int cy );
	afx_msg void OnPaint();
};

#ifndef _DEBUG  // MFCOpenglDemoView.cpp 中的调试版本
inline CMFCOpenglDemoDoc* CMFCOpenglDemoView::GetDocument() const
   { return reinterpret_cast<CMFCOpenglDemoDoc*>(m_pDocument); }
#endif

