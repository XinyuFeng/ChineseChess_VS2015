
// ChineseChess.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CChineseChessApp: 
// �йش����ʵ�֣������ ChineseChess.cpp
//

class CChineseChessApp : public CWinApp
{
public:
	CChineseChessApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CChineseChessApp theApp;