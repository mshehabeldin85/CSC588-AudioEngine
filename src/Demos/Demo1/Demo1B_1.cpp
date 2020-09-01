//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Demo1B_1.h"

// Thread stuff
#include "ThreadHelper.h"

// Timer
#include "Timer.h"

// Launch point for thread
void Demo1B_1_Main(Snd *pSnd)
{
	Trace::out("---> Start of thread: Demo1B_1 \n");

	assert(pSnd);

	Handle::Status status;
	Timer timer;
	float delta;
	float pan;
	int TimeElapsed_ms;

	delta = -(1.0f - (-1.0f)) / 1000.0f;
	pan = 1.0f;

	// Start the timer
	timer.tic();

	// Get the current time
	TimeElapsed_ms = Time::quotient(timer.toc(), Time(Duration::TIME_ONE_MILLISECOND));

	// Loop for 2 seconds
	while (TimeElapsed_ms < 2000)
	{
		// Set panning	
		pan += delta;
		status = pSnd->Pan(pan);

		if (status != Handle::Status::SUCCESS)
		{
			assert(false);
		}

		// update every 1 ms
		std::this_thread::sleep_for(std::chrono::microseconds(1000));
	//	Trace::out("pan:%f\n", pan);

		// Update time
		TimeElapsed_ms = Time::quotient(timer.toc(), Time(Duration::TIME_ONE_MILLISECOND));
	}

	Trace::out("---> End of thread: Demo1B_1 \n");
}

// --- End of File ---
