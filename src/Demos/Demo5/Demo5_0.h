//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO5_0_H
#define DEMO5_0_H

#include "Command.h"
#include "FileMan.h"
#include "FileUserCallBack.h"
#include "SndMan.h"

class Demo5_0 : public Command
{
public:
	Demo5_0() = default;
	~Demo5_0() = default;
	Demo5_0(const Demo5_0 &) = delete;
	Demo5_0 & operator = (const Demo5_0 &) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo5 part: 0s \n");

		// Play A
		Snd* pSndA = nullptr;

		pSndA = SndMan::Add(SndID::Electro);
		assert(pSndA);

		// Vol & Pan
		assert(pSndA->Vol(0.3f) == Handle::Status::SUCCESS);
		assert(pSndA->Pan(-1.0f) == Handle::Status::SUCCESS);

		// Call the sound
		assert(pSndA->Play() == Handle::Status::SUCCESS);

		// Initiate Beethoven async loading
		FileUserCallback *pFileCB = new FileUserCallback();
		assert(pFileCB);

		// Set the sound to play once finished loading
		pFileCB->Set(SndID::Beethoven);

		// Set the sound to stop on Beethoven play to SndA
		pFileCB->SetStopSnd(SndID::Electro);

		// Start the load
	
		FileMan::Add("../AudioFiles/Beethoven_stereo.wav", Wave::ID::Beethoven, pFileCB);

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
