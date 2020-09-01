//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Demo1D_1.h"

// Thread stuff
#include "ThreadHelper.h"

// Timer
#include "Timer.h"

// Launch point for thread
void Demo1D_1_Main(Snd *pSnd)
{
	Trace::out("---> Start of thread: Demo1D_1 \n");

	assert(pSnd);

	Handle::Status status;
	Timer timer;	
	int TimeElapsed_ms;
	int TimeElapsed_s;
	bool endThread;

	// Start the timer
	timer.tic();

	// Get the current time
	TimeElapsed_ms = Time::quotient(timer.toc(), Time(Duration::TIME_ONE_MILLISECOND));
	TimeElapsed_s = Time::quotient(timer.toc(), Time(Duration::TIME_ONE_SECOND));

	// Initialize thread flags
	endThread = false;

	// Loop until thread is ended
	while ( !endThread )
	{
		// at 72 seconds
		if (TimeElapsed_ms >= 42000)
		{
			Trace::out("Time of playing 105: %d seconds \n", TimeElapsed_s);

			// Stop sound
			status = pSnd->End();

			if (status != Handle::Status::SUCCESS)
			{
				assert(false);
			}

			endThread = true;
		}

		// update every 1 ms
		std::this_thread::sleep_for(std::chrono::microseconds(1000));

		// Update time
		TimeElapsed_ms = Time::quotient(timer.toc(), Time(Duration::TIME_ONE_MILLISECOND));
		TimeElapsed_s = Time::quotient(timer.toc(), Time(Duration::TIME_ONE_SECOND));
	}

	Trace::out("---> End of thread: Demo1D_1 \n");
}

// --- End of File ---
