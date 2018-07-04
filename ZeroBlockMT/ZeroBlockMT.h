
// ZeroBlockMT.h : main header file for the ZeroBlockMT application
const uint8_t pubscriptlength = 67; // 2 + 65 ,  if unknown at compile time ... 

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif
#include "resource.h"       // main symbols

/*structures to represent all that. defines're there so to make it compatible with hash functions. transaction structure 
doesn't need that.same define statements there to ensure that nothing more is in memory  so first : it can be copied as memory block wo care (not a big deal) ,
second : if structure has alignment you can copy it as block too but it gives nothing in this case.*/




// CZeroBlockMTApp:
// See ZeroBlockMT.cpp for the implementation of this class
//

class CZeroBlockMTApp : public CWinApp
{
public:
	CZeroBlockMTApp();
	int start;

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:

	DECLARE_MESSAGE_MAP()
};

extern CZeroBlockMTApp theApp;
