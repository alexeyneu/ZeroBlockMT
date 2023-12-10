
// MainFrm.cpp : implementation of the CMainFrame class
//
#include "stdafx.h"
#include "ZeroBlockMT.h"
#include <Richedit.h>
#include "MainFrm.h"
#include <openssl/sha.h>
#include <iomanip>

#include "mount.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CWnd)
	ON_WM_CREATE()
	ON_BN_CLICKED(2133, tr)
	ON_BN_CLICKED(233, w)
	ON_BN_CLICKED(2233, uw)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_CTLCOLORSTATIC, &CMainFrame::OnCtlcolorstatic)
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}
// CMainFrame message handlers
mount *mount_tx;
HWND hc, hz;
CButton *bh;
CButton *q;
CStatic *b7[3];
HANDLE cl;
CButton *finA;

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	mount_tx = NULL;
	cl = CreateEvent(NULL, 1, 0, NULL);
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	bh = new CButton();
	b7[0] = new CStatic();
	b7[1] = new CStatic();
	b7[2] = new CStatic();
	q = new CButton();
	CBitmap wq[2];
	finA = new CButton();
	wq[0].LoadBitmap(IDB_BITMAP1);
	wq[1].LoadBitmap(IDB_BITMAP4);

	bh->Create(L"start", BS_BITMAP | WS_CHILD | WS_VISIBLE | WS_DISABLED, CRect(50, 50, 170, 100), this, 2133);
	bh->SetBitmap(wq[0]);
	q->Create(L"stop", BS_BITMAP | WS_CHILD | WS_VISIBLE | WS_DISABLED, CRect(50 + 170, 50, 170 + 170, 100), this, 233);
	q->SetBitmap(wq[1]);
	b7[0]->Create(L"to go :", WS_CHILD | WS_VISIBLE | SS_WHITEFRAME | SS_SIMPLE, CRect(3, 290, 473, 320), this);
	b7[1]->Create(L"to go :", WS_CHILD | WS_VISIBLE | SS_WHITEFRAME | SS_SIMPLE, CRect(3, 290 - 70, 473, 320 - 70), this);
	b7[2]->Create(L"to go :", WS_CHILD | WS_VISIBLE | SS_WHITEFRAME | SS_SIMPLE, CRect(3, 290 - 35, 473, 320 - 35), this);
	finA->Create(L"init", BS_TEXT | WS_CHILD | WS_VISIBLE, CRect(0 + 280, 20 + 292, 59 + 280, 48 + 292), this, 2233);
	hc = CreateWindowEx(WS_EX_NOPARENTNOTIFY, MSFTEDIT_CLASS, NULL,
		ES_MULTILINE | ES_AUTOVSCROLL | WS_VISIBLE | WS_CHILD | WS_TABSTOP | WS_VSCROLL,
		1, 350, 450, 201, this->m_hWnd, NULL, h, NULL);
	HFONT newFont = CreateFont(22, 0, 0, 0, 0, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
		OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY,
		DEFAULT_PITCH | FF_DECORATIVE, L"Lucida Console");

	::PostMessage(hc, WM_SETFONT, (WPARAM)newFont, (LPARAM)0);
	hz = this->m_hWnd;
	::PostMessage(b7[0]->m_hWnd, WM_SETFONT, (WPARAM)newFont, (LPARAM)0);
	::PostMessage(b7[1]->m_hWnd, WM_SETFONT, (WPARAM)newFont, (LPARAM)0);
	::PostMessage(b7[2]->m_hWnd, WM_SETFONT, (WPARAM)newFont, (LPARAM)0);
	return 0;
}

const	std::wstring bin2hex(const unsigned char *p, size_t len)
{
	std::wstringstream f;
	f << std::hex << std::setfill(L'0');
	for (int i = 0; i < len; i++)
		f << std::setw(2) << (int)p[i];
	return f.str();
}

size_t hex2bin(unsigned char *p, const char *hexstr, const size_t length) {
	size_t wcount = 0;
	while (wcount++ < length && *hexstr && *(hexstr + 1)) {    //last condition cause np if check fails on middle one.thats coz of short-circuit evaluation
		sscanf(hexstr, "%2hhx", p++);  //7x slower than tables but doesnt metter 
		hexstr = hexstr + 2;
	}
	return  --wcount;     // error check here is a waste  
}

int bren = 5;
int b, terminator;
Transaction transaction;
VOID c(VOID *x)
{
	const byte c = (byte)x;

	std::wstringstream t;
	SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_AWAYMODE_REQUIRED | ES_DISPLAY_REQUIRED);
	SETTEXTEX fw;
	fw.flags = 4;
	fw.codepage = 1200;
	std::string  timestamp = CW2A((LPCWSTR)mount_tx->m_timestamp);
	std::string  pubkey = CW2A((LPCWSTR)mount_tx->m_pkey);
	uint32_t nBits = mount_tx->m_nb;

	unsigned char hash1[32], serializedData[857];

	transaction.pubkeyScript[0] = 0x41;
	hex2bin(transaction.pubkeyScript + 1, pubkey.c_str(), pubkey.length() / 2); 	// pubkey to bytes ,  then append the OP_CHECKSIG byte	
	transaction.pubkeyScript[pubscriptlength - 1] = OP_CHECKSIG;
	short sizeone = offsetof(Transaction, sequence);  /*, OK output :  41  */
	short sizetwo = sizeof transaction - sizeone;/* OK output :  85  */
	memcpy(serializedData, &transaction, sizeone);
	uint32_t serializedData_pos = sizeone + 1;// 42nd byte reserved
	BYTE pl = 0x01 + (nBits >> 8 > 0) + (nBits >> 16 > 0) + (nBits >> 24 > 0);  // size of nbits , not neccesary same as sizeof(nbits)   
	memcpy(serializedData + serializedData_pos, &nBits, serializedData[serializedData_pos++]/*a:1*/ = pl); // scriptSig {
	serializedData_pos = serializedData_pos + pl;
	*(short*)(serializedData + serializedData_pos) = 0x0401/*b:2*/; // {0x01,0x04} ,script op's 
	serializedData_pos = serializedData_pos + 2;
	memcpy(serializedData + serializedData_pos, timestamp.c_str(), serializedData[serializedData_pos++]/*c:1*/ = timestamp.length());  // scriptSig end
	memcpy(serializedData + serializedData_pos + timestamp.length(), &transaction.sequence, sizetwo);
	uint32_t  scriptSig_length = serializedData[sizeone] = pl + 4/*abc round-up*/ + timestamp.length();
	SHA256(serializedData, sizeof transaction + 1 + scriptSig_length, hash1);  /* + 1 coz of serializedData[sizeone]*/
	blockheader block_header = { 1/*version*/, {}/*hprev*/, {}/*merk*/, mount_tx->m_ut == 0 ? time(NULL) + c : mount_tx->m_ut + c, nBits, mount_tx->m_nonce };
	SHA256(hash1, 32, block_header.merk);// hash it with SHA256 and then hash that result to get merkle hash
	std::wstring merkleHash = bin2hex(block_header.merk, 32);
	std::reverse(block_header.merk, block_header.merk + 32);
	std::wstring merkleHashSw = bin2hex(block_header.merk, 32);
	std::reverse(block_header.merk, block_header.merk + 32);
	std::wstring txScriptSig = bin2hex(serializedData + sizeone + 1/*same*/, scriptSig_length);
	std::wstring pubScriptSig = bin2hex(transaction.pubkeyScript, pubscriptlength);
	t << L"Coinbase: " << txScriptSig << L"\n\nPubkeyScript: " << pubScriptSig << L"\n\nMerkle Hash: " << merkleHash << L"\nByteswapped: " << merkleHashSw << std::endl << L"Generating block...\n";

	SendMessage(hc, EM_SETTEXTEX, (WPARAM)&fw, (LPARAM)(LPCWSTR)t.str().c_str());
	PostMessage(hc, WM_VSCROLL, SB_BOTTOM, 0);
	unsigned int counter = 0, start = time(NULL);
	std::wstringstream w;
	std::ios_base::iostate xh = 0;
	unsigned char  block_hash1[32];
	_declspec(align(16))	unsigned char  block_hashfp[32];
	int drift = 4;
	__m128i r, m, b, camp;
	__m128i zero = _mm_setzero_si128();

	USHORT turt;
	while (1)
	{

		SHA256((unsigned char*)&block_header, 80, block_hash1);
		SHA256(block_hash1, 32, block_hashfp);

		r = _mm_load_si128((__m128i *)block_hashfp);
		m = _mm_load_si128((__m128i *)(block_hashfp + 16));
		switch (drift)
		{
		case 0:
			break;
		case 1:
			b = _mm_alignr_epi8(m, r, 23);

			break;
		case 2:
			b = _mm_alignr_epi8(m, r, 22);

			break;
		case 3:
			b = _mm_alignr_epi8(m, r, 21);

			break;
		case 4:
			b = _mm_alignr_epi8(m, r, 20);

			break;
		case 5:
			b = _mm_alignr_epi8(m, r, 19);

			break;
		case 6:
			b = _mm_alignr_epi8(m, r, 18);

			break;
		case 7:
			b = _mm_alignr_epi8(m, r, 17);

			break;
		case 8:
			b = _mm_alignr_epi8(m, r, 16);

			break;
		case 9:

			break;
		case 10:

			break;
		case 11:

			break;
		case 12:

			break;
		case 13:

			break;
		default:

			break;
		}

		camp = _mm_cmpeq_epi8(b ,zero);
		turt = _mm_movemask_epi8(camp);
		if (turt == 0xffff)
		{

				std::reverse(block_hashfp, block_hashfp + 32);
				std::wstring blockHash = bin2hex(block_hashfp, 32);
				t << L"\nBlock found!\nHash: " << blockHash << L"\nNonce: " << block_header.startNonce << L"\nUnix time: " << block_header.unixtime << std::endl;
				SendMessage(hc, EM_SETTEXTEX, (WPARAM)&fw, (LPARAM)(LPCWSTR)t.str().c_str());
				PostMessage(hc, WM_VSCROLL, SB_BOTTOM, 0);
				::b = 9;
			}

			if (time(NULL) - start > 0)
			{
				w << std::setw(7) << counter << L" Hashes/s, Nonce " << std::setw(10.10) << block_header.startNonce;
				counter = 0;
				start = time(NULL);
				b7[c]->SetWindowTextW((LPCWSTR)w.str().c_str());
				w.clear(xh, 0);
				w.str(L"");
			}

			if (++block_header.startNonce == 0) block_header.unixtime = block_header.unixtime + 3;//trick is that to change pre-start time to find a block(really it's smth else) faster than nonce wraps
			counter++;

			if (::b)
			{
				if (c == 0)
				{
					q->EnableWindow(0);
					bh->EnableWindow();
					if (terminator) { PostMessage(hz, WM_CLOSE, NULL, NULL); }
				}
				::b -= 3;
				bren = 5;
				break;
			}
		}

	
}


CWinThread *rew[3];
int terminator2;

void CMainFrame::tr()
{   
			bren=0;
			rew[0]=AfxBeginThread((AFX_THREADPROC)c,(LPVOID)0);
			rew[1]=AfxBeginThread((AFX_THREADPROC)c,(LPVOID)1);
			rew[2]=AfxBeginThread((AFX_THREADPROC)c,(LPVOID)2);
			q->EnableWindow();
			bh->EnableWindow(0);
}

void CMainFrame::w()
{
	b=9;
}

HBRUSH hbrBkgnd;
void CMainFrame::OnDestroy()
{
	CWnd::OnDestroy();
	delete bh;
	delete q;
	delete b7[0];
	delete b7[1];
	delete b7[2];
//	delete rew;
	delete finA;
	DeleteObject(hbrBkgnd);

	if(mount_tx) delete mount_tx;
}

void CMainFrame::OnClose()
{
	wchar_t w[140], ferrum[198];
	if(terminator2)
	{
		HANDLE t[]={rew[0]->m_hThread, rew[1]->m_hThread, rew[2]->m_hThread};    
		DWORD c = WaitForMultipleObjects(3, t, 1, 2000); // 2 seconds
	//	if(c==WAIT_TIMEOUT) 
		CWnd::OnClose();
	}
	terminator2++;

	if((!b)&&(bren))	
	{
		CWnd::OnClose();
	}
	else
	{
		terminator = 1;
		if(!b) this->w();
	}
}

void CMainFrame::uw()
{
	mount *mount_txn=NULL;
	if(mount_tx) mount_txn=mount_tx;
	mount_tx=new mount();
	if(mount_txn)
	{
		mount_tx->m_nb=mount_txn->m_nb;
		mount_tx->m_nonce=mount_txn->m_nonce;
		mount_tx->m_pkey=mount_txn->m_pkey;
		mount_tx->m_timestamp=mount_txn->m_timestamp;
		mount_tx->m_ut=mount_txn->m_ut;
		delete mount_txn;
	}
	int c = mount_tx->DoModal();
	
	if(c!=IDOK) { delete mount_tx ; mount_tx = NULL; bh->EnableWindow(0); return;}
	bh->EnableWindow(); 
}

afx_msg LRESULT CMainFrame::OnCtlcolorstatic(WPARAM wParam, LPARAM lParam)
{
	HDC hdcStatic = (HDC)wParam;
	SetTextColor(hdcStatic, RGB(2, 5, 55));
	SetBkColor(hdcStatic, RGB(255, 255, 255));
        if (hbrBkgnd == NULL)
        {
            hbrBkgnd = CreateSolidBrush(RGB(255, 255, 255));
        }
        return (INT_PTR)hbrBkgnd;
}
