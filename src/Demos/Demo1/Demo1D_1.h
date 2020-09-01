//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO1D_1_H
#define DEMO1D_1_H

// Command stuff
#include "Command.h"
#include "SndMan.h"

// Thread stuff
#include "ThreadHelper.h"

// Thread that moves the sound
void Demo1D_1_Main(Snd *pSnd);

// Command
class Demo1D_1 : public Command
{
public:
	Demo1D_1() = default;
	~Demo1D_1() = default;
	Demo1D_1(const Demo1D_1 &) = delete;
	Demo1D_1 & operator = (const Demo1D_1 &) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo1 partD: 1 \n");

		//--------------------------------------------------------
		// Create a Snd Call and start it...
		//--------------------------------------------------------

			Snd *pSndA = SndMan::Add(SndID::SongB);
			assert(pSndA);

			// Vol & Pan
			assert(pSndA->Pan(1.0f) == Handle::Status::SUCCESS);

			// Call the sound
			assert(pSndA->Play() == Handle::Status::SUCCESS);

		//-------------------------------------------------------
		// Move it around in a separate thread
		//-------------------------------------------------------

			std::thread  Demo1D_1_Thread(Demo1D_1_Main, pSndA);
			ThreadHelper::SetThreadName(Demo1D_1_Thread, "DEMO_1D_1");
			Demo1D_1_Thread.detach();
	}
};




#endif

// --- End of File ---
