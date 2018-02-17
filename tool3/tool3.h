
// tool3.h : main header file for the tool3 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif
#include <cstdint>

#include "resource.h"       // main symbols

/*structures to represent all that. defines're there so to make it compatible with hash functions. transaction structure 
doesn't need that.same define statements there to ensure that nothing more is in memory  so first : it can be copied as memory block wo care (not a big deal) ,
second : if structure has alignment you can copy it as block too but it gives nothing in this case.*/

struct Transaction{
#ifdef _MSC_VER
#pragma pack(1)
#endif
	/* Hash of Tx */
	uint8_t merkleHash[32];
	
	/* Tx serialization before hashing */
	uint8_t *serializedData;
	
	/* Tx version */
	uint32_t version;    
	
	/* Input */
	uint8_t numInputs; // Program assumes one input
	uint8_t prevOutput[32];
	uint32_t prevoutIndex;
	uint8_t *scriptSig;
	uint32_t sequence;
	
	/* Output */
	uint8_t numOutputs; // Program assumes one output
	uint64_t outValue;
	uint8_t *pubkeyScript;
	
	/* Final */
	uint32_t locktime;
#ifdef _MSC_VER
} ;
#else
} __attribute__((packed));
#endif

		//here is POD coz there is no constructors and others

struct blockheader {
#ifdef _MSC_VER
#pragma pack(1)
#endif
	uint32_t blockversion;
	unsigned char hashPrevBlock[32];
	unsigned char merk[32];
	uint32_t unixtime;
	uint32_t nBits;
	uint32_t startNonce;
#ifdef _MSC_VER
};
#else
} __attribute__((packed));
#endif


struct blockhash {
#ifdef _MSC_VER
#pragma pack(1)
#endif
	unsigned char bl[28];
	uint32_t checkbytes;
#ifdef _MSC_VER
};
#else
} __attribute__((packed));
#endif


// Ctool3App:
// See tool3.cpp for the implementation of this class
//

class Ctool3App : public CWinApp
{
public:
	Ctool3App();
	int start;

// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:

	DECLARE_MESSAGE_MAP()
};

extern Ctool3App theApp;
