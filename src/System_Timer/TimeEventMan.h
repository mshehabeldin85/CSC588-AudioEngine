//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef TIME_EVENT_MAN_H
#define	TIME_EVENT_MAN_H


#include "Manager.h"
#include "Command.h"
#include "TimeEvent.h"
#include "Timer.h"

// This class is only there for pretty UML
class TimeEventMan_MLink : public Manager
{
public:
	TimeEvent_Link* poActive;
	TimeEvent_Link* poReserve;
};

class TimeEventMan : public TimeEventMan_MLink
{
	//----------------------------------------------------------------------
	// Big four
	//----------------------------------------------------------------------
private:
	TimeEventMan(int reserveNum = 3, int reserveGrow = 1);
	TimeEventMan(const TimeEventMan&) = delete;
	TimeEventMan& operator = (const TimeEventMan&) = delete;
	TimeEventMan() = delete;
	~TimeEventMan();

public:

	//----------------------------------------------------------------------
	// Static Methods
	//----------------------------------------------------------------------
	static void Create(int reserveNum = 1, int reserveGrow = 1);
	static void Destroy();

	static TimeEvent* Add(Command* pCommand, Time deltaTimeToTrigger);
	static TimeEvent* Find(TimeEvent::ID event_id);
	static Time GetTimeCurrent();

	static void Remove(TimeEvent* pNode);
	static void Dump();

	static void Update();


protected:
	virtual DLink* DerivedCreateNode() override;
	virtual bool DerivedCompare(DLink* pLinkA, DLink* pLinkB) override;
	virtual void DerivedWash(DLink* pLink) override;
	virtual void DerivedDumpNode(DLink* pLink) override;
	virtual void DerivedDestroyNode(DLink* pLink) override;

	//----------------------------------------------------------------------
	// Private methods
	//----------------------------------------------------------------------
private:
	static TimeEventMan* privGetInstance();

	//----------------------------------------------------------------------
	// Data - unique data for this manager 
	//----------------------------------------------------------------------
	static TimeEventMan* poInstance;

	TimeEvent* poNodeCompare;
	Time		mCurrTime;
	Timer		GameTime;
};

#endif

// --- End of File ---
