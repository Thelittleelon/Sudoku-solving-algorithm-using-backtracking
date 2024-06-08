
// sudoku_gui_trial.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Csudoku_gui_trialApp:
// See sudoku_gui_trial.cpp for the implementation of this class
//

class Csudoku_gui_trialApp : public CWinApp
{
public:
	Csudoku_gui_trialApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Csudoku_gui_trialApp theApp;