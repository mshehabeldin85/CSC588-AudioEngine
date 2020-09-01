//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO5_2_H
#define DEMO5_2_H

#include "Command.h"
#include "SndMan.h"

class Demo5_2 : public Command
{
public:
	Demo5_2() = default;
	~Demo5_2() = default;
	Demo5_2(const Demo5_2&) = delete;
	Demo5_2& operator = (const Demo5_2&) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo5: Stop Beethoven \n");

		// Stop C
		Snd* pSndC = nullptr;

		pSndC = SndMan::Find(SndID::Beethoven);
		assert(pSndC);

		// Call the sound
		assert(pSndC->End() == Handle::Status::SUCCESS);
	}

};

#endif

// --- End of File ---
