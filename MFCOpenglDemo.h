
// MFCOpenglDemo.h : MFCOpenglDemo Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMFCOpenglDemoApp:
// �йش����ʵ�֣������ MFCOpenglDemo.cpp
//

class CMFCOpenglDemoApp : public CWinApp
{
public:
	CMFCOpenglDemoApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCOpenglDemoApp theApp;
