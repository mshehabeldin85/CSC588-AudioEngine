//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO3_1_H
#define DEMO3_1_H

#include "Command.h"
#include "SndMan.h"

class Demo3_1 : public Command
{
public:
	Demo3_1() = default;
	~Demo3_1() = default;
	Demo3_1(const Demo3_1 &) = delete;
	Demo3_1 & operator = (const Demo3_1 &) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo3 part: 1s \n");

		// Play D

		Snd *pSndD = nullptr;

		pSndD = SndMan::Add(SndID::Coma, nullptr, 50);
		assert(pSndD);

		// Vol & Pan
		assert(pSndD->Vol(0.10f) == Handle::Status::SUCCESS);
		assert(pSndD->Pan(0.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndD->Play() == Handle::Status::SUCCESS);

		// Print snd priority table

		Snd::PrintPriorityTable();
	}

};


#endif

// --- End of File ---
