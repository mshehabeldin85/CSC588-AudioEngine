//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "XAudio2Wrapper.h"

#include "AudioEngine.h"
#include "ASnd.h"
#include "ASndMan.h"


ASndMan* ASndMan::pInstance = nullptr;

//---------------------------------------------------------------------------------------------------------
// Design Notes:
//
//  Singleton class - use only public static methods for customers
//
//  * One single compare node is owned by this singleton - used for find, prevent extra news
//  * Create one - NULL Object 
//
//---------------------------------------------------------------------------------------------------------

ASndMan::ASndMan(int reserveNum, int reserveGrow)
//	: Manager() // <--- Kick the can (delegate)
{
	this->QuitFlag = false;

	// At this point Man is created, now initialize the reserve
	this->BaseInitialize(reserveNum, reserveGrow);

	// initialize derived data here
	this->poNodeCompare = new ASnd();
	assert(this->poNodeCompare != nullptr);
}

ASndMan::~ASndMan()
{
	assert(ASndMan::IsQuit() == true);

	// We created it... so we delete it
	delete this->poNodeCompare;

	//Trace::out("---> ~ASndMan()\n");

	// Next stop - base class
}

//----------------------------------------------------------------------
// Static Methods
//----------------------------------------------------------------------
void ASndMan::Create(int reserveNum, int reserveGrow)
{
	// make sure values are ressonable 
	assert(reserveNum > 0);
	assert(reserveGrow > 0);

	// initialize the singleton here
	assert(pInstance == nullptr);

	// Do the initialization
	if (pInstance == nullptr)
	{
		pInstance = new ASndMan(reserveNum, reserveGrow);
	}

}

void ASndMan::Destroy()
{
	//Trace::out("\n");
	//Trace::out("---- Destroy() ----\n");

	// Get the instance
	ASndMan* pMan = ASndMan::privGetInstance();
	assert(pMan != nullptr);

	// Clean up what it current owns reserve and active
	pMan->BaseDestroy();

	// bye bye singleton
	delete pMan->pInstance;
}

void ASndMan::SetQuit()
{
	ASndMan* pMan = ASndMan::privGetInstance();
	assert(pMan != nullptr);

	pMan->QuitFlag = true;
}

bool  ASndMan::IsQuit()
{
	ASndMan* pMan = ASndMan::privGetInstance();
	assert(pMan != nullptr);

	return pMan->QuitFlag;
}

ASnd* ASndMan::Add(SndID snd_id)
{
	ASndMan* pMan = ASndMan::privGetInstance();
	assert(pMan != nullptr);

	ASnd* pNode = (ASnd*)pMan->BaseAdd();
	assert(pNode != nullptr);

	// Create a new one given a wash
	pNode->Set(snd_id);

	return pNode;
}

ASnd* ASndMan::Find(SndID id)
{
	ASndMan* pMan = ASndMan::privGetInstance();
	assert(pMan != nullptr);

	// Compare functions only compares two Nodes

	// So:  Use the Compare Node - as a reference
	//      use in the Compare() function
	pMan->poNodeCompare->SetId(id);

	ASnd* pData = (ASnd*)pMan->BaseFind(pMan->poNodeCompare);
	return pData;
}

void ASndMan::Remove(ASnd* pNode)
{
	ASndMan* pMan = ASndMan::privGetInstance();
	assert(pMan != nullptr);

	assert(pNode != nullptr);
	pMan->BaseRemove(pNode);
}

void ASndMan::Dump()
{
	ASndMan* pMan = ASndMan::privGetInstance();
	assert(pMan != nullptr);

	pMan->BaseDump();
}

//----------------------------------------------------------------------
// Override Abstract methods
//----------------------------------------------------------------------
DLink* ASndMan::DerivedCreateNode()
{
	DLink* pNode = new ASnd();
	assert(pNode != nullptr);

	return pNode;
}

bool ASndMan::DerivedCompare(DLink* pLinkA, DLink* pLinkB)
{
	// This is used in baseFind() 
	assert(pLinkA != nullptr);
	assert(pLinkB != nullptr);

	ASnd* pDataA = (ASnd*)pLinkA;
	ASnd* pDataB = (ASnd*)pLinkB;

	bool status = false;

	SndID A;
	SndID B;

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

void ASndMan::DerivedWash(DLink* pLink)
{
	assert(pLink != nullptr);
	ASnd* pNode = (ASnd*)pLink;
	pNode->Wash();
}

void ASndMan::DerivedDumpNode(DLink* pLink)
{
	assert(pLink != nullptr);
	ASnd* pData = (ASnd*)pLink;
	pData->Dump();
}

void ASndMan::DerivedDestroyNode(DLink* pLink)
{
	assert(pLink);
	ASnd* pData = (ASnd*)pLink;
	delete pData;
}


//----------------------------------------------------------------------
// Private methods
//----------------------------------------------------------------------
ASndMan* ASndMan::privGetInstance()
{
	// Safety - this forces users to call Create() first before using class
	assert(pInstance != nullptr);

	return pInstance;
}

// --- End of File ---

