
// MyDailyPlan.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMyDailyPlanApp: 
// �йش����ʵ�֣������ MyDailyPlan.cpp
//

class CMyDailyPlanApp : public CWinApp
{
public:
	CMyDailyPlanApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMyDailyPlanApp theApp;