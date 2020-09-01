//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "WaveMan.h"

WaveMan* WaveMan::pInstance = nullptr;

//---------------------------------------------------------------------------------------------------------
// Design Notes:
//
//  Singleton class - use only public static methods for customers
//
//  * One single compare node is owned by this singleton - used for find, prevent extra news
//  * Create one - NULL Object 
//---------------------------------------------------------------------------------------------------------

WaveMan::WaveMan(int reserveNum, int reserveGrow)
//	: Manager() // <--- Kick the can (delegate)
{
	// At this point Man is created, now initialize the reserve
	this->BaseInitialize(reserveNum, reserveGrow);

	// initialize derived data here
	this->poNodeCompare = new Wave();
	assert(this->poNodeCompare != nullptr);
}

WaveMan::~WaveMan()
{
	// We created it... so we delete it
	delete this->poNodeCompare;

	//Trace::out("---> ~WaveMan()\n");

	// Next stop - base class
}

//----------------------------------------------------------------------
// Static Methods
//----------------------------------------------------------------------
void WaveMan::Create(int reserveNum, int reserveGrow)
{
	// make sure values are ressonable 
	assert(reserveNum > 0);
	assert(reserveGrow > 0);

	// initialize the singleton here
	assert(pInstance == nullptr);

	// Do the initialization
	if (pInstance == nullptr)
	{
		pInstance = new WaveMan(reserveNum, reserveGrow);
	}

}

void WaveMan::Destroy()
{
	Trace::out("\n");
	//Trace::out("---- Destroy() ----\n");

	// Get the instance
	WaveMan* pMan = WaveMan::privGetInstance();
	assert(pMan != nullptr);

	// Clean up what it current owns reserve and active
	pMan->BaseDestroy();

	// bye bye singleton
	delete pMan->pInstance;
}

Wave* WaveMan::Add(const char* const pWaveName, Wave::ID id, FileUserCallback* pFileUserCB)
{
	WaveMan* pMan = WaveMan::privGetInstance();
	assert(pMan != nullptr);

	Wave* pNode = (Wave*)pMan->BaseAdd();
	assert(pNode != nullptr);

	pNode->Set(pWaveName, id, pFileUserCB);

	return pNode;
}

Wave* WaveMan::Find(Wave::ID id)
{
	WaveMan* pMan = WaveMan::privGetInstance();
	assert(pMan != nullptr);

	// Compare functions only compares two Nodes

	// So:  Use the Compare Node - as a reference
	//      use in the Compare() function
	pMan->poNodeCompare->SetId( id );

	Wave * pData = (Wave*)pMan->BaseFind(pMan->poNodeCompare);
	return pData;
}

void WaveMan::Remove(Wave* pNode)
{
	WaveMan* pMan = WaveMan::privGetInstance();
	assert(pMan != nullptr);

	assert(pNode != nullptr);
	pMan->BaseRemove(pNode);
}

void WaveMan::Dump()
{
	WaveMan* pMan = WaveMan::privGetInstance();
	assert(pMan != nullptr);

	pMan->BaseDump();
}

//----------------------------------------------------------------------
// Override Abstract methods
//----------------------------------------------------------------------
DLink* WaveMan::DerivedCreateNode()
{
	DLink* pNode = new Wave();
	assert(pNode != nullptr);

	return pNode;
}

bool WaveMan::DerivedCompare(DLink* pLinkA, DLink* pLinkB)
{
	// This is used in baseFind() 
	assert(pLinkA != nullptr);
	assert(pLinkB != nullptr);

	Wave* pDataA = (Wave*)pLinkA;
	Wave* pDataB = (Wave*)pLinkB;

	bool status = false;

	Wave::ID A;
	Wave::ID B;

	if (pDataA->GetId(A) != Handle::Status::SUCCESS)
	{
		assert(false);
	}

	if (pDataB->GetId(B) != Handle::Status::SUCCESS)
	{
		assert(false);
	}

	if (A == B)
	{
		status = true;
	}

	return status;
}

void WaveMan::DerivedWash(DLink* pLink)
{
	assert(pLink != nullptr);
	Wave* pNode = (Wave*)pLink;
	pNode->Wash();
}

void WaveMan::DerivedDumpNode(DLink* pLink)
{
	assert(pLink != nullptr);
	Wave* pData = (Wave*)pLink;
	pData->Dump();
}

void WaveMan::DerivedDestroyNode(DLink* pLink)
{
	assert(pLink);
	Wave* pData = (Wave*)pLink;
	delete pData;
}


//----------------------------------------------------------------------
// Private methods
//----------------------------------------------------------------------
WaveMan* WaveMan::privGetInstance()
{
	// Safety - this forces users to call Create() first before using class
	assert(pInstance != nullptr);

	return pInstance;
}

// --- End of File ---
