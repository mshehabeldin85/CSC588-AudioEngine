//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO3_2_H
#define DEMO3_2_H

#include "Command.h"
#include "SndMan.h"

class Demo3_2 : public Command
{
public:
	Demo3_2() = default;
	~Demo3_2() = default;
	Demo3_2(const Demo3_2 &) = delete;
	Demo3_2 & operator = (const Demo3_2 &) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo3 part: 2s \n");

		// Play E

		Snd *pSndE = nullptr;

		pSndE = SndMan::Add(SndID::Coma, nullptr, 75);
		assert(pSndE);

		// Vol & Pan
		assert(pSndE->Vol(0.10f) == Handle::Status::SUCCESS);
		assert(pSndE->Pan(0.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndE->Play() == Handle::Status::SUCCESS);

		// Print snd priority table

		Snd::PrintPriorityTable();
	}

};

#endif

// --- End of File ---
