//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO1A_0_H
#define DEMO1A_0_H

#include "Command.h"
#include "SndMan.h"

class Demo1A_0 : public Command
{
public:
	Demo1A_0() = default;
	~Demo1A_0() = default;
	Demo1A_0(const Demo1A_0 &) = delete;
	Demo1A_0 & operator = (const Demo1A_0 &) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo1 partA: 0 \n");

		// Create a Snd Call
		Snd *pSndA = SndMan::Add(SndID::Fiddle);
		assert(pSndA);
		
		// Vol & Pan
		//assert(pSndA->Vol(0.25f) == Handle::Status::SUCCESS);
		assert(pSndA->Pan(0.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndA->Play() == Handle::Status::SUCCESS);
	}

};


#endif

// --- End of File ---
