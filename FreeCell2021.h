
// FreeCell2021.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CFreeCell2021App:
// See FreeCell2021.cpp for the implementation of this class
//

class CFreeCell2021App : public CWinApp
{
public:
	CFreeCell2021App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CFreeCell2021App theApp;
