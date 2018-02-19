// mount.cpp : implementation file
//

#include "stdafx.h"
#include "tool3.h"
#include "mount.h"
#include "afxdialogex.h"


// mount dialog

IMPLEMENT_DYNAMIC(mount, CDialogEx)

mount::mount(CWnd* pParent /*=NULL*/)
	: CDialogEx(mount::IDD, pParent)
{
	m_nonce = 0;
	m_ut = 0;
	m_nb = 0;
	m_timestamp = _T("");
	m_pubkey = _T("");
}

mount::~mount()
{
}

void mount::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CDialogEx::OnFinalRelease();
}

void mount::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT5, m_nonce);
	DDX_Text(pDX, IDC_EDIT4, m_ut);
	DDX_Text(pDX, IDC_EDIT3, m_nb);
	DDX_Text(pDX, IDC_EDIT2, m_timestamp);
	DDV_MaxChars(pDX, m_timestamp, 254);
	DDX_Text(pDX, IDC_EDIT1, m_pubkey);
	DDV_MaxChars(pDX, m_pubkey, 130);
}

BEGIN_MESSAGE_MAP(mount, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &mount::OnBnClickedButton1)
END_MESSAGE_MAP()

// mount message handlers

void mount::OnBnClickedButton1()
{
	this->OnOK();
}