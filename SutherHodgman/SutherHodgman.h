
// SutherHodgman.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSutherHodgmanApp: 
// �йش����ʵ�֣������ SutherHodgman.cpp
//

class CSutherHodgmanApp : public CWinApp
{
public:
	CSutherHodgmanApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSutherHodgmanApp theApp;