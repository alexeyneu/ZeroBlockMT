
// ZeroBlockMT.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "ZeroBlockMT.h"
#include "MainFrm.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CZeroBlockMTApp




BEGIN_MESSAGE_MAP(CZeroBlockMTApp, CWinApp)

END_MESSAGE_MAP()


// CZeroBlockMTApp construction

CZeroBlockMTApp::CZeroBlockMTApp()
{
	// TODO: replace application ID string below with unique ID string; recommended
	// format for string is CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("ZeroBlockMT.AppID.NoVersion"));
	start=0;
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

// The one and only CZeroBlockMTApp object

CZeroBlockMTApp theApp;

// CZeroBlockMTApp initialization
CMainFrame* pFrame;
HINSTANCE h;
HANDLE b;
BOOL CZeroBlockMTApp::InitInstance()
{

	CWinApp::InitInstance();
	h=this->m_hInstance;
	AfxInitRichEdit2();
	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	EnableTaskbarInteraction(FALSE);

	 b=LoadLibrary(L"MSFTEDIT.DLL"); //richedit
	
	//SetRegistryKey(_T("Local AppWizard-Generated Applications"));

;

	pFrame= new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	WNDCLASSEX w;
	ZeroMemory(&w,sizeof(WNDCLASSEX));

	w.hbrBackground=(HBRUSH)(COLOR_WINDOW+1);
	w.lpszClassName=L"t";
	w.style=CS_OWNDC|CS_BYTEALIGNCLIENT|CS_BYTEALIGNWINDOW|CS_HREDRAW|CS_VREDRAW;
	w.hCursor=this->LoadStandardCursor(IDC_ARROW);
	w.lpfnWndProc=AfxWndProc;
	w.lpszMenuName=NULL;
	w.hInstance=this->m_hInstance;
	w.cbSize=sizeof(WNDCLASSEX);

	RegisterClassEx(&w);
	
	pFrame->CreateEx( WS_EX_APPWINDOW|WS_EX_COMPOSITED,L"t",L"ZeroBlockMT",WS_OVERLAPPEDWINDOW,CRect(20,0,487,592),NULL,0);
	// The one and only window has been initialized, so show and update it
	pFrame->ShowWindow(SW_SHOW);
	// call DragAcceptFiles only if there's a suffix
	//  In an SDI app, this should occur after ProcessShellCommand
	return TRUE;
}

int CZeroBlockMTApp::ExitInstance()
{
	FreeLibrary((HMODULE)b);
	delete pFrame;
	return CWinApp::ExitInstance();
}

// CZeroBlockMTApp message handlers



// CZeroBlockMTApp message handlers







