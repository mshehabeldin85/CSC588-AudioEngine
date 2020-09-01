//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO3_8_H
#define DEMO3_8_H

#include "Command.h"
#include "SndMan.h"

class Demo3_8 : public Command
{
public:
	Demo3_8() = default;
	~Demo3_8() = default;
	Demo3_8(const Demo3_8 &) = delete;
	Demo3_8 & operator = (const Demo3_8 &) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo3 part: 8s \n");

		// Play K

		Snd *pSndK = nullptr;

		pSndK = SndMan::Add(SndID::Coma, nullptr, 150);
		assert(pSndK);

		// Vol & Pan
		assert(pSndK->Vol(0.10f) == Handle::Status::SUCCESS);
		assert(pSndK->Pan(0.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndK->Play() == Handle::Status::SUCCESS);

		// Print snd priority table

		Snd::PrintPriorityTable();
	}

};

#endif

// --- End of File ---
