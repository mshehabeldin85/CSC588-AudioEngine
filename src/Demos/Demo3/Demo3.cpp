//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "TimeEventMan.h"

#include "Demo3.h"
#include "Demo3_0.h"
#include "Demo3_1.h"
#include "Demo3_2.h"
#include "Demo3_3.h"
#include "Demo3_4.h"
#include "Demo3_5.h"
#include "Demo3_6.h"
#include "Demo3_7.h"
#include "Demo3_8.h"
#include "Demo3_9.h"

void Demo3()
{
	Demo3_0 *p_0 = new Demo3_0();
	assert(p_0);
	TimeEventMan::Add(p_0, 0 * Time(Duration::TIME_ONE_SECOND));

	Demo3_1 *p_1 = new Demo3_1();
	assert(p_1);
	TimeEventMan::Add(p_1, 1 * Time(Duration::TIME_ONE_SECOND));

	Demo3_2 *p_2 = new Demo3_2();
	assert(p_2);
	TimeEventMan::Add(p_2, 2 * Time(Duration::TIME_ONE_SECOND));

	Demo3_3 *p_3 = new Demo3_3();
	assert(p_3);
	TimeEventMan::Add(p_3, 3 * Time(Duration::TIME_ONE_SECOND));

	Demo3_4 *p_4 = new Demo3_4();
	assert(p_4);
	TimeEventMan::Add(p_4, 4 * Time(Duration::TIME_ONE_SECOND));

	Demo3_5* p_5 = new Demo3_5();
	assert(p_5);
	TimeEventMan::Add(p_5, 5 * Time(Duration::TIME_ONE_SECOND));

	Demo3_6* p_6 = new Demo3_6();
	assert(p_6);
	TimeEventMan::Add(p_6, 6 * Time(Duration::TIME_ONE_SECOND));

	Demo3_7* p_7 = new Demo3_7();
	assert(p_7);
	TimeEventMan::Add(p_7, 7 * Time(Duration::TIME_ONE_SECOND));

	Demo3_8* p_8 = new Demo3_8();
	assert(p_8);
	TimeEventMan::Add(p_8, 8 * Time(Duration::TIME_ONE_SECOND));

	Demo3_9* p_9 = new Demo3_9();
	assert(p_9);
	TimeEventMan::Add(p_9, 13 * Time(Duration::TIME_ONE_SECOND));

	//TimeEventMan::Dump();
	
}

// --- End of File ---
