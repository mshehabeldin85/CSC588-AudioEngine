//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Demo1.h"
#include "TimeEventMan.h"

void Demo1()
{
	// Center
	Demo1A_0 *p1A_0 = new Demo1A_0();
	assert(p1A_0);

	// Left
	Demo1A_1 *p1A_1 = new Demo1A_1();
	assert(p1A_1);

	// Right
	Demo1A_2 *p1A_2 = new Demo1A_2();
	assert(p1A_2);

	TimeEventMan::Add(p1A_0, 0 * Time(Duration::TIME_ONE_SECOND));
    TimeEventMan::Add(p1A_1, 3 * Time(Duration::TIME_ONE_SECOND));
	TimeEventMan::Add(p1A_2, 6 * Time(Duration::TIME_ONE_SECOND));

	Demo1B_0* p1B_0 = new Demo1B_0();
	assert(p1B_0);

	TimeEventMan::Add(p1B_0, 10 * Time(Duration::TIME_ONE_SECOND));

	Demo1B_1* p1B_1 = new Demo1B_1();
	assert(p1B_1);

	TimeEventMan::Add(p1B_1, 15 * Time(Duration::TIME_ONE_SECOND));

	Demo1C_0* p1C_0 = new Demo1C_0();
	assert(p1C_0);

	TimeEventMan::Add(p1C_0, 20 * Time(Duration::TIME_ONE_SECOND));

	Demo1C_1* p1C_1 = new Demo1C_1();
	assert(p1C_1);

	TimeEventMan::Add(p1C_1, 25 * Time(Duration::TIME_ONE_SECOND));

	Demo1D_0* p1D_0 = new Demo1D_0();
	assert(p1D_0);

	Demo1D_1* p1D_1 = new Demo1D_1();
	assert(p1D_1);

	TimeEventMan::Add(p1D_1, 30 * Time(Duration::TIME_ONE_SECOND));
	TimeEventMan::Add(p1D_0, 30 * Time(Duration::TIME_ONE_SECOND));

	Demo1E_0* p1E_0 = new Demo1E_0();
	assert(p1E_0);

	TimeEventMan::Add(p1E_0, 80 * Time(Duration::TIME_ONE_SECOND));
}

// --- End of File ---
