//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "TimeEventMan.h"
#include "TimeEvent.h"

TimeEventMan* TimeEventMan::poInstance = nullptr;


TimeEventMan::TimeEventMan(int reserveNum, int reserveGrow)
{
	// At this point ImageMan is created, now initialize the reserve
	this->BaseInitialize(reserveNum, reserveGrow);

	// initialize derived data here
	this->poNodeCompare = new TimeEvent();
	assert(this->poNodeCompare != nullptr);

	this->GameTime.tic();
	this->mCurrTime = this->GameTime.toc();

}

TimeEventMan::~TimeEventMan()
{
	// We created it... so we delete it
	delete this->poNodeCompare;

	//Trace::out("---> ~TimeEventMan()\n");

	// Next stop - base class
}


//----------------------------------------------------------------------
// Static Methods
//----------------------------------------------------------------------

void TimeEventMan::Update()
{
	// Get the instance
	TimeEventMan* pMan = TimeEventMan::privGetInstance();
	assert(pMan != nullptr);

	// squirrel away
	pMan->mCurrTime = pMan->GameTime.toc();

	// walk the list
	TimeEvent* pEvent = (TimeEvent*)pMan->BaseGetActive();
	TimeEvent* pNextEvent = nullptr;

	// Walk the list until there is no more list OR currTime is greater than timeEvent 
	// ToDo Fix: List needs to be sorted
	while (pEvent != nullptr)
	{
		// Difficult to walk a list and remove itself from the list
		// so squirrel away the next event now, use it at bottom of while
		pNextEvent = (TimeEvent*)pEvent->pNext;

		if (pMan->mCurrTime >= (pEvent->GetTriggerTime()) ) 
		{
			// call it
			pEvent->Process();

			// remove from list
			pMan->BaseRemove(pEvent);
		}

		// advance the pointer
		pEvent = pNextEvent;
	}
}



void TimeEventMan::Create(int reserveNum, int reserveGrow)
{
	// make sure values are ressonable 
	assert(reserveNum > 0);
	assert(reserveGrow > 0);

	// initialize the singleton here
	assert(poInstance == nullptr);

	// Do the initialization
	if (poInstance == nullptr)
	{
		poInstance = new TimeEventMan(reserveNum, reserveGrow);
	}

}

void TimeEventMan::Destroy()
{
	//Trace::out("\n");
	//Trace::out("---- Destroy() ----\n");

	// Get the instance
	TimeEventMan* pMan = TimeEventMan::privGetInstance();
	assert(pMan != nullptr);

	// Clean up what it current owns reserve and active
	pMan->BaseDestroy();

	// bye bye singleton
	delete pMan->poInstance;
}

Time TimeEventMan::GetTimeCurrent()
{
	// Get the instance
	TimeEventMan* pMan = TimeEventMan::privGetInstance();
	assert(pMan != nullptr);

	return pMan->mCurrTime;
}

TimeEvent* TimeEventMan::Add(Command* pCommand, Time deltaTimeToTrigger)
{
	TimeEventMan* pMan = TimeEventMan::privGetInstance();
	assert(pMan != nullptr);

	TimeEvent* pNode = (TimeEvent*)pMan->BaseAdd();
	assert(pNode != nullptr);

	// Create a new one given a wash
	assert(pCommand);
	pNode->Set(pCommand, deltaTimeToTrigger);

	return pNode;
}

TimeEvent* TimeEventMan::Find(TimeEvent::ID event_id)
{
	TimeEventMan* pMan = TimeEventMan::privGetInstance();
	assert(pMan != nullptr);

	// Compare functions only compares two Nodes

	// So:  Use the Compare Node - as a reference
	//      use in the Compare() function
	pMan->poNodeCompare->SetID(event_id);

	TimeEvent* pData = (TimeEvent*)pMan->BaseFind(pMan->poNodeCompare);
	return pData;
}

void TimeEventMan::Remove(TimeEvent* pNode)
{
	TimeEventMan* pMan = TimeEventMan::privGetInstance();
	assert(pMan != nullptr);

	assert(pNode != nullptr);
	pMan->BaseRemove(pNode);
}

void TimeEventMan::Dump()
{
	TimeEventMan* pMan = TimeEventMan::privGetInstance();
	assert(pMan != nullptr);

	pMan->BaseDump();
}

//----------------------------------------------------------------------
// Override Abstract methods
//----------------------------------------------------------------------
DLink* TimeEventMan::DerivedCreateNode()
{
	DLink* pNode = new TimeEvent();
	assert(pNode != nullptr);

	return pNode;
}

bool TimeEventMan::DerivedCompare(DLink* pLinkA, DLink* pLinkB)
{
	// This is used in baseFind() 
	assert(pLinkA != nullptr);
	assert(pLinkB != nullptr);

	TimeEvent* pDataA = (TimeEvent*)pLinkA;
	TimeEvent* pDataB = (TimeEvent*)pLinkB;

	bool status = false;

	if (pDataA->GetID() == pDataB->GetID())
	{
		status = true;
	}

	return status;
}

void TimeEventMan::DerivedWash(DLink* pLink)
{
	assert(pLink != nullptr);
	TimeEvent* pNode = (TimeEvent*)pLink;
	pNode->Wash();
}

void TimeEventMan::DerivedDumpNode(DLink* pLink)
{
	assert(pLink != nullptr);
	TimeEvent* pData = (TimeEvent*)pLink;
	pData->Dump();
}

void TimeEventMan::DerivedDestroyNode(DLink* pLink)
{
	assert(pLink);
	TimeEvent* pData = (TimeEvent*)pLink;
	delete pData;
}

//----------------------------------------------------------------------
// Private methods
//----------------------------------------------------------------------
TimeEventMan* TimeEventMan::privGetInstance()
{
	// Safety - this forces users to call Create() first before using class
	assert(poInstance != nullptr);

	return poInstance;
}


// --- End of File ---
