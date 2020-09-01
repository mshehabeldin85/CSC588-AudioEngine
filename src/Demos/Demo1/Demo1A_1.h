//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO1A_1_H
#define DEMO1A_1_H

#include "Command.h"
#include "SndMan.h"

class Demo1A_1 : public Command
{
public:
	Demo1A_1() = default;
	~Demo1A_1() = default;
	Demo1A_1(const Demo1A_1 &) = delete;
	Demo1A_1 & operator = (const Demo1A_1 &) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo1 partA: 1 \n");

		// Create a Snd Call
		Snd *pSndA = SndMan::Add(SndID::Fiddle);
		assert(pSndA);

		// Vol & Pan
		//assert(pSndA->Vol(0.25f) == Handle::Status::SUCCESS);
		assert(pSndA->Pan(-1.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndA->Play() == Handle::Status::SUCCESS);
	}

};


#endif

// --- End of File ---
