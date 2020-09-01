//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO3_4_H
#define DEMO3_4_H

#include "Command.h"
#include "SndMan.h"

class Demo3_4 : public Command
{
public:
	Demo3_4() = default;
	~Demo3_4() = default;
	Demo3_4(const Demo3_4 &) = delete;
	Demo3_4 & operator = (const Demo3_4 &) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo3 part: 4s \n");

		// Play G

		Snd *pSndG = nullptr;

		pSndG = SndMan::Add(SndID::Coma, nullptr, 150);
		assert(pSndG);

		// Vol & Pan
		assert(pSndG->Vol(0.10f) == Handle::Status::SUCCESS);
		assert(pSndG->Pan(0.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndG->Play() == Handle::Status::SUCCESS);

		// Print snd priority table

		Snd::PrintPriorityTable();
	}

};

#endif

// --- End of File ---
