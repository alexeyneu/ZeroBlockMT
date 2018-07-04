#pragma once


// mount dialog

class mount : public CDialogEx
{
	DECLARE_DYNAMIC(mount)

public:
	mount(CWnd* pParent = NULL);   // standard constructor
	virtual ~mount();

// Dialog Data
	enum { IDD = IDD_DIALOGBAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	CString m_pkey;
	CString m_timestamp;
	UINT m_nb;
	UINT m_ut;
	UINT m_nonce;
};
