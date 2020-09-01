//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Demo2.h"
#include "TimeEventMan.h"

void Demo2()
{
	Demo2A_0* p2A_0 = new Demo2A_0();
	assert(p2A_0);

	TimeEventMan::Add(p2A_0, 0 * Time(Duration::TIME_ONE_SECOND));
}

// --- End of File ---
