//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO1D_0_H
#define DEMO1D_0_H

// Command stuff
#include "Command.h"
#include "SndMan.h"

// Thread stuff
#include "ThreadHelper.h"

// Thread that moves the sound
void Demo1D_0_Main(Snd *pSnd);

// Command
class Demo1D_0 : public Command
{
public:
	Demo1D_0() = default;
	~Demo1D_0() = default;
	Demo1D_0(const Demo1D_0 &) = delete;
	Demo1D_0 & operator = (const Demo1D_0 &) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo1 partD: 0 \n");

		//--------------------------------------------------------
		// Create a Snd Call and start it...
		//--------------------------------------------------------

			Snd *pSndA = SndMan::Add(SndID::SongA);
			assert(pSndA);

			// Vol & Pan
			assert(pSndA->Pan(-1.0f) == Handle::Status::SUCCESS);

			// Call the sound
			assert(pSndA->Play() == Handle::Status::SUCCESS);

		//-------------------------------------------------------
		// Move it around in a separate thread
		//-------------------------------------------------------

			std::thread  Demo1D_0_Thread(Demo1D_0_Main, pSndA);
			ThreadHelper::SetThreadName(Demo1D_0_Thread, "DEMO_1D_0");
			Demo1D_0_Thread.detach();
	}
};




#endif

// --- End of File ---
