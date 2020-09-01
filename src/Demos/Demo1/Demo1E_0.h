//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO1E_0_H
#define DEMO1E_0_H

// Command stuff
#include "Command.h"
#include "SndMan.h"

// Thread stuff
#include "ThreadHelper.h"

// Thread that moves the sound
void Demo1E_0_Main(Snd *pSnd);

// Command
class Demo1E_0 : public Command
{
public:
	Demo1E_0() = default;
	~Demo1E_0() = default;
	Demo1E_0(const Demo1E_0 &) = delete;
	Demo1E_0 & operator = (const Demo1E_0 &) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo1 partE: 0 \n");

		//--------------------------------------------------------
		// Create a Snd Call and start it...
		//--------------------------------------------------------

			Snd *pSndA = SndMan::Add(SndID::Bassoon);
			assert(pSndA);

			// Vol
			pSndA->Vol(0.4f);

			// Call the sound
			assert(pSndA->Play() == Handle::Status::SUCCESS);

		//-------------------------------------------------------
		// Move it around in a separate thread
		//-------------------------------------------------------

			std::thread  Demo1E_0_Thread(Demo1E_0_Main, pSndA);
			ThreadHelper::SetThreadName(Demo1E_0_Thread, "DEMO_1E_0");
			Demo1E_0_Thread.detach();
	}
};




#endif

// --- End of File ---
