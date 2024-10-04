
// MFCApplication11.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCApplication11App:
// See MFCApplication11.cpp for the implementation of this class
//

class CMFCApplication11App : public CWinApp
{
public:
	CMFCApplication11App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication11App theApp;
