
// MainFrm.cpp : implementation of the CMainFrame class
//
const int fzc=5; 
const uint64_t COIN = 100000000;
#include "stdafx.h"
#include "tool3.h"
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
	ON_BN_CLICKED(2133,tr)
	ON_BN_CLICKED(233,w)
	ON_BN_CLICKED(2233,uw)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
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
HWND hc,hz;
CButton *bh;
CButton *q;
CStatic *b7[3];
HANDLE cl;
CButton *finA;

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{	
	mount_tx=NULL;
	cl=CreateEvent(NULL,1,0,NULL);
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	bh=new CButton();
	b7[0]=new CStatic();
	b7[1]=new CStatic();
	b7[2]=new CStatic();
	q=new CButton();
	CBitmap wq[2];
	finA=new CButton();
	wq[0].LoadBitmap(IDB_BITMAP1);
	wq[1].LoadBitmap(IDB_BITMAP4);

	bh->Create(L"start",BS_BITMAP|WS_CHILD|WS_VISIBLE|WS_DISABLED,CRect(50,50,170,100),this,2133);
	bh->SetBitmap(wq[0]);
	q->Create(L"stop",BS_BITMAP|WS_CHILD|WS_VISIBLE|WS_DISABLED,CRect(50+170,50,170+170,100),this,233);
	q->SetBitmap(wq[1]);
	b7[0]->Create(L"to go :",WS_CHILD|WS_VISIBLE|SS_WHITEFRAME|SS_SIMPLE,CRect(3,290,473,320),this);
	b7[1]->Create(L"to go :",WS_CHILD|WS_VISIBLE|SS_WHITEFRAME|SS_SIMPLE,CRect(3,290-70,473,320-70),this);
	b7[2]->Create(L"to go :",WS_CHILD|WS_VISIBLE|SS_WHITEFRAME|SS_SIMPLE,CRect(3,290-35,473,320-35),this);
	finA->Create(L"init",BS_TEXT|WS_CHILD|WS_VISIBLE,CRect(0+280,20+292,59+280,48+292),this,2233);
	hc=CreateWindowEx(WS_EX_NOPARENTNOTIFY, MSFTEDIT_CLASS,NULL, 
		ES_MULTILINE|ES_AUTOVSCROLL| WS_VISIBLE | WS_CHILD |WS_TABSTOP|WS_VSCROLL, 
        1, 350, 450, 201, this->m_hWnd, NULL, h, NULL);
	HFONT newFont = CreateFont(22, 0, 0, 0,0 , FALSE, FALSE, FALSE, DEFAULT_CHARSET,
    OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_NATURAL_QUALITY,
	DEFAULT_PITCH | FF_DECORATIVE, L"Lucida Console");
	
	::PostMessage(hc,WM_SETFONT,(WPARAM)newFont,(LPARAM)0);
	hz=this->m_hWnd;
	::PostMessage(b7[0]->m_hWnd,WM_SETFONT,(WPARAM)newFont,(LPARAM)0);
	::PostMessage(b7[1]->m_hWnd,WM_SETFONT,(WPARAM)newFont,(LPARAM)0);
	::PostMessage(b7[2]->m_hWnd,WM_SETFONT,(WPARAM)newFont,(LPARAM)0);
	return 0;
}

const	std::wstring bin2hex(const unsigned char *p, size_t len)
{
	std::wstringstream f; 
	f<< std::hex << std::setfill(L'0');
	for (int i = 0; i < len; i++)
		f << std::setw(2) << (int)p[i];
	return f.str();
}

size_t hex2bin(unsigned char *p , const char *hexstr, size_t len)
{
	size_t wlen = 0;
	while ((wlen<len) && *hexstr && *(hexstr+1))    //last condition cause np if check fails on middle one.thats coz of short-circuit evaluation
        {
		len*=sscanf(hexstr, "%2hhx",p++);   // 0 or 1 (maybe smth else too) . Slow stuff , np  		
		hexstr += 2;
		wlen++;
	}
	return  (wlen == len - 1)*len;     // zero if error .had enough 
}

int bren=5;
int b,terminator;

VOID c(VOID *x)
{	
    const byte c=(byte)x; 
    q->EnableWindow();
    bh->EnableWindow(0);
	std::wstringstream t;
    SetThreadExecutionState(ES_CONTINUOUS | ES_SYSTEM_REQUIRED | ES_AWAYMODE_REQUIRED | ES_DISPLAY_REQUIRED);
	SETTEXTEX fw;
	fw.flags=4;
	fw.codepage=1200;
	
	unsigned char hash1[32];
	uint32_t timestamp_length = wcslen(mount_tx->m_timestamp);
	CW2A timestamp((LPCWSTR)mount_tx->m_timestamp);
	CW2A pubkey((LPCWSTR)mount_tx->m_pubkey);
	Transaction transaction={ {},/* version */1 ,1 , {},0xFFFFFFFF ,/* sequ */0xFFFFFFFF ,1 ,50*COIN , pubscriptlength , {} ,0 };

	// Encode pubkey to binary and prepend pubkey size, then append the OP_CHECKSIG byte	
	transaction.pubkeyScript[0] = 0x41; //   A public key is 32 bytes X coordinate, 32 bytes Y coordinate and one byte 0x04, so 65 bytes i.e 0x41 in Hex.
	hex2bin(transaction.pubkeyScript + 1, pubkey ,65 ); // No error checking, yeah.   
	transaction.pubkeyScript[66] = OP_CHECKSIG;
	
	/*  nbits related stuff , first is real size of value in bytes , next is value with 
	   null bytes on the left removed  */
	uint8_t serializedData[500]; 
	uint32_t serializedData_pos = 0;
	memcpy(serializedData, &transaction.version, 41);  
	serializedData_pos = serializedData_pos + 41;
	/* fo' sho' */ 
//	std::cout << offsetof(Transaction,prevoutIndex) + 4 /* size of prevoutIndex */ - offsetof(Transaction,version);/* OK output : " 41 " */	
	serializedData_pos++;  // +41 byte reserved 

	short pl= 0x01+(mount_tx->m_nb >> 8 > 0)+(mount_tx->m_nb >> 16 > 0)+(mount_tx->m_nb >> 24 > 0);	
	serializedData[serializedData_pos++] =pl;     // statement (smth > 0) returns 0 or 1
	memcpy(serializedData + serializedData_pos, &mount_tx->m_nb, pl);
	serializedData_pos = serializedData_pos + pl;
	
	// It should essentially mean PUSH 1 byte on the stack which in this case is 0x04 or just 4
	serializedData[serializedData_pos++] = 0x01;
	serializedData[serializedData_pos++] = 0x04;
	serializedData[serializedData_pos++] = timestamp_length; 
	uint32_t  scriptSig_length = serializedData_pos  - 42 + timestamp_length; // serializedData_pos inc'ed already to go as size
	serializedData[41] = scriptSig_length;

	uint32_t serializedLength = 
	4    // tx version  
	+1   // number of inputs
	+32  // hash of previous output
	+4   // previous output's index
	+1   // 1 byte for the size of scriptSig (?)
	+scriptSig_length
	+4   // size of sequence
	+1   // number of outputs
	+8   // 8 bytes for coin value
	+1   // 1 byte to represent size of the pubkey Script
	+pubscriptlength
	+4;   // 4 bytes for lock time

	memcpy(serializedData + serializedData_pos, timestamp, timestamp_length);
	serializedData_pos = serializedData_pos + timestamp_length;
	/*scriptsig is done*/
	
	memcpy(serializedData + serializedData_pos, &transaction.sequence, 85);

	// hash it with SHA256 and then hash that result to get merkle hash
	SHA256(serializedData, serializedLength, hash1);
	SHA256(hash1, 32, transaction.merkleHash);
	
	std::wstring merkleHash = bin2hex(transaction.merkleHash, 32);
	std::reverse(transaction.merkleHash,transaction.merkleHash + 32); 
	std::wstring merkleHashSwapped = bin2hex(transaction.merkleHash, 32);
	std::wstring txScriptSig = bin2hex(serializedData + 42, scriptSig_length);
	std::wstring pubScriptSig = bin2hex(transaction.pubkeyScript, pubscriptlength);

	t<<L"Coinbase: "<< txScriptSig <<L"\n\nPubkeyScript: "<<pubScriptSig <<L"\n\nMerkle Hash: "<<merkleHash<<L"\nByteswapped: "<< merkleHashSwapped << std::endl;
	t<<L"Generating block...\n";

	SendMessage(hc,EM_SETTEXTEX,(WPARAM)&fw,(LPARAM)(LPCWSTR)t.str().c_str());
	PostMessage(hc, WM_VSCROLL, SB_BOTTOM, 0);					                   
	
		unsigned char  block_hash1[32];
		blockheader block_header={/* drift */ 1 , {} , {} , mount_tx->m_ut == 0 ? time(NULL) + c : mount_tx->m_ut + c,   mount_tx->m_nb , mount_tx->m_nonce };
		blockhash block_hashf;
		unsigned char* block_headerp=(unsigned char*)&block_header;
		unsigned char* block_hashfp=(unsigned char*)&block_hashf;
		std::reverse(transaction.merkleHash,transaction.merkleHash + 32); 
		memcpy(&block_header.merk, transaction.merkleHash, 32);
		unsigned int counter=0, start = time(NULL);
		std::wstringstream w;
		std::ios_base::iostate xh=0;
    while (1) {
		{
			SHA256(block_headerp, 80, block_hash1);
			SHA256(block_hash1, 32, block_hashfp);
			
			 // The hash is in little-endian, so we check the last 4 bytes.
			if(block_hashf.checkbytes == 0) // { .. , 0x00, 0x00, 0x00, 0x00 }
			{
				std::reverse(block_hashfp,block_hashfp +32);
				std::wstring blockHash = bin2hex(block_hashfp, 32);
				t<<L"\nBlock found!\nHash: " << blockHash  <<L"\nNonce: " << block_header.startNonce << L"\nUnix time: "<< block_header.unixtime << std::endl;
				SendMessage(hc,EM_SETTEXTEX,(WPARAM)&fw,(LPARAM)(LPCWSTR)t.str().c_str());
				PostMessage(hc, WM_VSCROLL, SB_BOTTOM, 0);					                   
				b=9;
			}
			
			if(time(NULL)-start > 0)
			{
				w<<std::setw(7)<< counter<<L" Hashes/s, Nonce "<< std::setw(10.10)<< block_header.startNonce;
				counter = 0;
				start = time(NULL);
				b7[c]->SetWindowTextW((LPCWSTR)w.str().c_str());
				w.clear(xh, 0);
				w.str(L"");
			}
			
			if(block_header.startNonce == 0x100000000 - 1)
			{
				block_header.unixtime=block_header.unixtime + 3;//trick is that to change pre-start time to find a block(really it's smth else) faster then nonce wraps
			}
			block_header.startNonce++;	//see what happens on out-bounds
			counter++;
		}
	
	if (b) {
	    q->EnableWindow(0);
	    bh->EnableWindow();
	    if (terminator) { PostMessage(hz, WM_CLOSE, NULL, NULL);}
	    else {	    }
	    b -= 3;
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
}

void CMainFrame::w()
{
	b=9;
}

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
	if(mount_tx) delete mount_tx;
}

void CMainFrame::OnClose()
{
	wchar_t w[140],ferrum[198];
	if(terminator2)
	{
	HANDLE t[]={rew[0]->m_hThread,rew[1]->m_hThread,rew[2]->m_hThread};    
	DWORD c = WaitForMultipleObjects(3,t,1,20000); // 20 seconds
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
		terminator =1;
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
		mount_tx->m_pubkey=mount_txn->m_pubkey;
		mount_tx->m_timestamp=mount_txn->m_timestamp;
		mount_tx->m_ut=mount_txn->m_ut;
		delete mount_txn;
	}
	int c=mount_tx->DoModal();
	
	if(c!=IDOK) { delete mount_tx ; mount_tx = NULL; bh->EnableWindow(0); return;}
	bh->EnableWindow();
}
