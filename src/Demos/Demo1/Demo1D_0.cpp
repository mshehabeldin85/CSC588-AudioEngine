//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Demo1D_0.h"

// Thread stuff
#include "ThreadHelper.h"

// Timer
#include "Timer.h"

// Launch point for thread
void Demo1D_0_Main(Snd *pSnd)
{
	Trace::out("---> Start of thread: Demo1D_0 \n");

	assert(pSnd);

	Handle::Status status;
	Timer timer;	
	int TimeElapsed_ms;
	int TimeElapsed_s;
	bool endThread;
	bool checkOne;
	bool checkTwo;

	// Start the timer
	timer.tic();

	// Get the current time
	TimeElapsed_ms = Time::quotient(timer.toc(), Time(Duration::TIME_ONE_MILLISECOND));
	TimeElapsed_s = Time::quotient(timer.toc(), Time(Duration::TIME_ONE_SECOND));

	// Initialize thread flags
	endThread = false;
	checkOne = false;
	checkTwo = false;

	// Loop until thread is ended
	while ( !endThread )
	{
		// at 35 seconds
		if (TimeElapsed_ms >= 5000 && !checkOne)
		{
			Trace::out("Time of playing 104: %d seconds \n", TimeElapsed_s);
			checkOne = true;
		}

		// at 38 seconds
		if (TimeElapsed_ms >= 8000 && !checkTwo)
		{
			Trace::out("Time of playing 104: %d seconds \n", TimeElapsed_s);
			checkTwo = true;
		}

		// at 60 seconds
		if (TimeElapsed_ms >= 30000)
		{
			Trace::out("Time of playing 104: %d seconds \n", TimeElapsed_s);

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

	Trace::out("---> End of thread: Demo1D_0 \n");
}

// --- End of File ---
