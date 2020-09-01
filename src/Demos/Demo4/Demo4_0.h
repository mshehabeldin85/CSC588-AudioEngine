//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO4_0_H
#define DEMO4_0_H

#include "Command.h"
#include "SndMan.h"
#include "UserCallBack.h"

class Demo4_0 : public Command
{
public:
	Demo4_0() = default;
	~Demo4_0() = default;
	Demo4_0(const Demo4_0 &) = delete;
	Demo4_0 & operator = (const Demo4_0 &) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo4 part: 0s \n");

		// Play A

		Snd *pSndA = nullptr;
		UserCallback *pCallback_A = new UserCallback();

		pSndA = SndMan::Add(SndID::Dial, pCallback_A );
		assert(pSndA);

		// Vol & Pan
		assert(pSndA->Vol(0.10f) == Handle::Status::SUCCESS);
		assert(pSndA->Pan(-1.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndA->Play() == Handle::Status::SUCCESS);

		// Play B

		Snd *pSndB = nullptr;
		UserCallback *pCallback_B = new UserCallback();

		pSndB = SndMan::Add(SndID::MoonPatrol, pCallback_B);
		assert(pSndB);

		// Vol & Pan
		assert(pSndB->Vol(0.10f) == Handle::Status::SUCCESS);
		assert(pSndB->Pan(1.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndB->Play() == Handle::Status::SUCCESS);

		// Play C

		Snd *pSndC = nullptr;
		UserCallback *pCallback_C = new UserCallback();

		pSndC = SndMan::Add(SndID::Sequence, pCallback_C);
		assert(pSndC);

		// Vol & Pan
		assert(pSndC->Vol(0.10f) == Handle::Status::SUCCESS);
		assert(pSndC->Pan(-1.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndC->Play() == Handle::Status::SUCCESS);



		Snd::PrintPriorityTable();
	}

};

#endif

// --- End of File ---
