//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO3_5_H
#define DEMO3_5_H

#include "Command.h"
#include "SndMan.h"

class Demo3_5 : public Command
{
public:
	Demo3_5() = default;
	~Demo3_5() = default;
	Demo3_5(const Demo3_5 &) = delete;
	Demo3_5 & operator = (const Demo3_5 &) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo3 part: 5s \n");

		// Play H

		Snd *pSndH = nullptr;

		pSndH = SndMan::Add(SndID::Coma, nullptr, 75);
		assert(pSndH);

		// Vol & Pan
		assert(pSndH->Vol(0.10f) == Handle::Status::SUCCESS);
		assert(pSndH->Pan(0.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndH->Play() == Handle::Status::SUCCESS);

		// Print snd priority table

		Snd::PrintPriorityTable();
	}

};

#endif

// --- End of File ---
