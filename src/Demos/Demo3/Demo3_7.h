//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO3_7_H
#define DEMO3_7_H

#include "Command.h"
#include "SndMan.h"

class Demo3_7 : public Command
{
public:
	Demo3_7() = default;
	~Demo3_7() = default;
	Demo3_7(const Demo3_7 &) = delete;
	Demo3_7 & operator = (const Demo3_7 &) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo3 part: 7s \n");

		// Play J

		Snd *pSndJ = nullptr;

		pSndJ = SndMan::Add(SndID::Coma, nullptr, 75);
		assert(pSndJ);

		// Vol & Pan
		assert(pSndJ->Vol(0.10f) == Handle::Status::SUCCESS);
		assert(pSndJ->Pan(0.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndJ->Play() == Handle::Status::SUCCESS);

		// Print snd priority table

		Snd::PrintPriorityTable();
	}

};

#endif

// --- End of File ---
