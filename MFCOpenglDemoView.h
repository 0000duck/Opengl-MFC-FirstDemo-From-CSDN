
// MFCOpenglDemoView.h : CMFCOpenglDemoView ��Ľӿ�
//

#pragma once


class CMFCOpenglDemoView : public CView
{
protected: // �������л�����
	CMFCOpenglDemoView();
	DECLARE_DYNCREATE(CMFCOpenglDemoView)

// ����
public:
	CMFCOpenglDemoDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
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

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
	afx_msg void OnDestroy();
	afx_msg void OnSize( UINT nType, int cx, int cy );
	afx_msg void OnPaint();
};

#ifndef _DEBUG  // MFCOpenglDemoView.cpp �еĵ��԰汾
inline CMFCOpenglDemoDoc* CMFCOpenglDemoView::GetDocument() const
   { return reinterpret_cast<CMFCOpenglDemoDoc*>(m_pDocument); }
#endif

