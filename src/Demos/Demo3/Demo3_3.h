//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO3_3_H
#define DEMO3_3_H

#include "Command.h"
#include "SndMan.h"

class Demo3_3 : public Command
{
public:
	Demo3_3() = default;
	~Demo3_3() = default;
	Demo3_3(const Demo3_3 &) = delete;
	Demo3_3 & operator = (const Demo3_3 &) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo3 part: 3s \n");

		// Play F

		Snd *pSndF = nullptr;

		pSndF = SndMan::Add(SndID::Coma, nullptr, 100);
		assert(pSndF);

		// Vol & Pan
		assert(pSndF->Vol(0.10f) == Handle::Status::SUCCESS);
		assert(pSndF->Pan(0.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndF->Play() == Handle::Status::SUCCESS);

		// Print snd priority table

		Snd::PrintPriorityTable();
	}

};

#endif

// --- End of File ---
