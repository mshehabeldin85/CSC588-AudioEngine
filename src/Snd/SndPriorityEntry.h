//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SND_PRIORITY_ENTRY_H
#define SND_PRIORITY_ENTRY_H

#include "Handle.h"
#include "SndID.h"

class SndPriorityEntry
{
public:
	SndPriorityEntry();

	void Clear();

// Data:
	Handle::ID	handleID;
	SndID		sndID;
	int			priority;
	Time		startTime;
};

#endif


// End of File 
