//const uint32_t nBits = 486604799;
//const uint32_t startNonce=0; //= 2083236893;
//const uint32_t unixtime=0; //= 1231006505;
//const char timestamp[]="The Times 03/Jan/2009 Chancellor on brink of second bailout for banks";
//const char pubkey[131]="04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f";


// MainFrm.h : interface of the CMainFrame class
//

#pragma once
const uint64_t CENT = 1000000;
const uint64_t COIN = 100000000;
const uint32_t OP_CHECKSIG = 172; // This is expressed as 0xAC


class CMainFrame : public CWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// Attributes
public:
private:

// Operations
public:

// Overrides
public:

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG

#endif



// Generated message map functions
protected:

	DECLARE_MESSAGE_MAP()

public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void tr();
	afx_msg void w();
	afx_msg void uw();
	afx_msg void OnDestroy();
protected:
public:
	afx_msg void OnClose();
};
extern HINSTANCE h;

