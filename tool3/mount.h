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
	UINT m_nonce;
	afx_msg void OnBnClickedButton1();
	UINT m_ut;
	UINT m_nb;
	CString m_timestamp;
	CString m_pubkey;
};
