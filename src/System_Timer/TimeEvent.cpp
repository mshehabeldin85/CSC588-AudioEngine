//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "TimeEvent.h"
#include "TimeEventMan.h"
#include "Time.h"


TimeEvent::TimeEvent()
{
	this->id = TimeEvent::Uninitialized;
	this->pCommand = nullptr;
	this->TriggerTime = Time(Duration::TIME_ZERO);
	this->DeltaTime = Time(Duration::TIME_ZERO);
}

void TimeEvent::Process()
{
	// make sure the command is valid
	assert(this->pCommand);

	// fire off command
	this->pCommand->Execute();
}

Time TimeEvent::GetTriggerTime()
{
	return this->TriggerTime;
}

void TimeEvent::SetID(ID event_id)
{
	this->id = event_id;
}

TimeEvent::ID TimeEvent::GetID()
{
	return this->id;
}

void TimeEvent::Wash()
{
	// Wash - clear the entire hierarchy
	DLink::Clear();

	// Sub class clear
	this->PrivClear();
}

void TimeEvent::Set(Command* pCmd, Time deltaTimeToTrigger)
{
	assert(pCmd);
	this->pCommand = pCmd;

	this->DeltaTime = deltaTimeToTrigger;

	this->TriggerTime = TimeEventMan::GetTimeCurrent() + this->DeltaTime;
}

void TimeEvent::PrivClear()
{
	this->id = TimeEvent::Uninitialized;
	delete this->pCommand;
	this->pCommand = nullptr;

	this->TriggerTime = Time(Duration::TIME_ZERO);
	this->DeltaTime = Time(Duration::TIME_ZERO);

}

void TimeEvent::Dump()
{
	// Dump - Print contents to the debug output window
	int ms = Time::quotient(this->GetTriggerTime(), Time(Duration::TIME_ONE_MILLISECOND));

	Trace::out("   Name: %d (%p) %f s\n", this->GetID(), this, ms / 1000.0f);
}

TimeEvent::~TimeEvent()
{
	delete this->pCommand;
}


// --- End of File ---
