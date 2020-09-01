//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "TimeEventMan.h"

#include "Demo4.h"
#include "Demo4_0.h"

void Demo4()
{
	Demo4_0 *p_0 = new Demo4_0();
	assert(p_0);
	TimeEventMan::Add(p_0, 0 * Time(Duration::TIME_ONE_SECOND));

	//TimeEventMan::Dump();
}

// --- End of File ---
