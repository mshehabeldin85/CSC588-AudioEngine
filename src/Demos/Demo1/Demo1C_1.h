//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO1C_1_H
#define DEMO1C_1_H

// Command stuff
#include "Command.h"
#include "SndMan.h"

// Thread stuff
#include "ThreadHelper.h"

// Thread that moves the sound
void Demo1C_1_Main(Snd *pSnd);

// Command
class Demo1C_1 : public Command
{
public:
	Demo1C_1() = default;
	~Demo1C_1() = default;
	Demo1C_1(const Demo1C_1 &) = delete;
	Demo1C_1 & operator = (const Demo1C_1 &) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo1 partC: 1 \n");

		//--------------------------------------------------------
		// Create a Snd Call and start it...
		//--------------------------------------------------------

			Snd *pSndC = SndMan::Add(SndID::Oboe2);
			assert(pSndC);

			// Vol & Pan
			assert(pSndC->Vol(1.0f) == Handle::Status::SUCCESS);
			assert(pSndC->Pan(0.0f) == Handle::Status::SUCCESS);

			// Call the sound
			assert(pSndC->Play() == Handle::Status::SUCCESS);

		//-------------------------------------------------------
		// Move it around in a separate thread
		//-------------------------------------------------------

			std::thread  Demo1C_1_Thread(Demo1C_1_Main, pSndC);
			ThreadHelper::SetThreadName(Demo1C_1_Thread, "DEMO_1C_1");
			Demo1C_1_Thread.detach();
	}
};




#endif

// --- End of File ---
