//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO2A_0_H
#define DEMO2A_0_H

// Command stuff
#include "Command.h"
#include "SndMan.h"

// Thread stuff
#include "ThreadHelper.h"

// Thread that moves the sound
void Demo2A_0_Main(Snd *pSnd);

// Command
class Demo2A_0 : public Command
{
public:
	Demo2A_0() = default;
	~Demo2A_0() = default;
	Demo2A_0(const Demo2A_0 &) = delete;
	Demo2A_0& operator = (const Demo2A_0 &) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo2 partA: 0 \n");

		//--------------------------------------------------------
		// Create a Snd Call and start it...
		//--------------------------------------------------------

			Snd* pSndH = SndMan::Add(SndID::End_mono);
			assert(pSndH);

			Snd* pSndG = SndMan::Add(SndID::CtoA_mono);
			assert(pSndG);

			Snd* pSndF = SndMan::Add(SndID::C_mono);
			assert(pSndF);

			Snd* pSndE = SndMan::Add(SndID::BtoC_mono);
			assert(pSndE);

			Snd* pSndD = SndMan::Add(SndID::B_mono);
			assert(pSndD);

			Snd* pSndC = SndMan::Add(SndID::AtoB_mono);
			assert(pSndC);

			Snd* pSndB = SndMan::Add(SndID::A_mono);
			assert(pSndB);

			Snd *pSndA = SndMan::Add(SndID::Intro_mono);
			assert(pSndA);

			// Vol & Pan
			assert(pSndA->Vol(0.8f) == Handle::Status::SUCCESS);
			assert(pSndA->Pan(0.0f) == Handle::Status::SUCCESS);

			// Start stitching
			assert(pSndA->StartStitching() == Handle::Status::SUCCESS);

			// Call the sound
			assert(pSndA->Play() == Handle::Status::SUCCESS);

		//-------------------------------------------------------
		// Move it around in a separate thread
		//-------------------------------------------------------

			std::thread  Demo2A_0_Thread(Demo2A_0_Main, pSndA);
			ThreadHelper::SetThreadName(Demo2A_0_Thread, "DEMO_2A_0");
			Demo2A_0_Thread.detach();
	}
};




#endif

// --- End of File ---
