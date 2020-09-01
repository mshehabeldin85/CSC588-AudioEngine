//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "SndPriorityEntry.h"

SndPriorityEntry::SndPriorityEntry()
{
	this->Clear();
}

void SndPriorityEntry::Clear()
{
	this->priority = -1;
	this->sndID = SndID::Uninitialized;
	this->handleID = 0;
	this->startTime = Time(Duration::TIME_ZERO);
}

// End of File 
