//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "TimeEventMan.h"

#include "Demo5.h"
#include "Demo5_0.h"
#include "Demo5_1.h"
#include "Demo5_2.h"


void Demo5()
{
	Demo5_0 *p_0 = new Demo5_0();
	assert(p_0);
	TimeEventMan::Add(p_0, 0 * Time(Duration::TIME_ONE_SECOND));

	Demo5_1* p_1_0 = new Demo5_1();
	assert(p_1_0);
	TimeEventMan::Add(p_1_0, 5 * Time(Duration::TIME_ONE_SECOND));

	Demo5_1* p_1_1 = new Demo5_1();
	assert(p_1_1);
	TimeEventMan::Add(p_1_1, 10 * Time(Duration::TIME_ONE_SECOND));

	Demo5_1* p_1_2 = new Demo5_1();
	assert(p_1_2);
	TimeEventMan::Add(p_1_2, 15 * Time(Duration::TIME_ONE_SECOND));

	Demo5_1* p_1_3 = new Demo5_1();
	assert(p_1_3);
	TimeEventMan::Add(p_1_3, 20 * Time(Duration::TIME_ONE_SECOND));

	Demo5_1* p_1_4 = new Demo5_1();
	assert(p_1_4);
	TimeEventMan::Add(p_1_4, 25 * Time(Duration::TIME_ONE_SECOND));

	Demo5_2* p_2 = new Demo5_2();
	assert(p_2);
	TimeEventMan::Add(p_2, 60 * Time(Duration::TIME_ONE_SECOND));
}


// --- End of File ---
