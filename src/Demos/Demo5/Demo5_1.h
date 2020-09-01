//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO5_1_H
#define DEMO5_1_H

#include "Command.h"
#include "SndMan.h"

class Demo5_1 : public Command
{
public:
	Demo5_1() = default;
	~Demo5_1() = default;
	Demo5_1(const Demo5_1&) = delete;
	Demo5_1& operator = (const Demo5_1&) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo5: Play Alarm \n");

		// Play B
		Snd* pSndB = nullptr;

		pSndB = SndMan::Add(SndID::Alarm);
		assert(pSndB);

		// Vol & Pan
		assert(pSndB->Vol(0.3f) == Handle::Status::SUCCESS);
		assert(pSndB->Pan(-1.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndB->Play() == Handle::Status::SUCCESS);
	}

};

#endif

// --- End of File ---
