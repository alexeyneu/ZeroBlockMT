
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


//here are PODs coz there is no constructors and others
struct Transaction {
#pragma pack(1)
/* +0 */uint32_t version;   	/* vs bitcoin-api tx block : merkleHash[32] removed */
	uint8_t  numInputs; 
	uint8_t  prevOutput[32];
	uint32_t prevoutIndex; // +41
/* +0 */uint32_t sequence;
	uint8_t  numOutputs; 
	uint64_t outValue; 
	uint8_t  pubscriptlength; //it isn't in the bitcoin-api tx block also
	uint8_t  pubkeyScript[::pubscriptlength];
	uint32_t locktime;   // +85
} ;
struct blockheader {
#pragma pack(1)
	uint32_t blockversion;
	unsigned char hashPrevBlock[32];
	unsigned char merk[32];
	uint32_t unixtime;
	uint32_t nBits;
	uint32_t startNonce;
};


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
