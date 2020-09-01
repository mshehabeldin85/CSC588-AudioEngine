//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Demo1C_1.h"

// Thread stuff
#include "ThreadHelper.h"

// Timer
#include "Timer.h"

// Launch point for thread
void Demo1C_1_Main(Snd *pSnd)
{
	Trace::out("---> Start of thread: Demo1C_0 \n");

	assert(pSnd);

	Handle::Status status;
	Timer timer;	
	float delta;
	float vol;
	int TimeElapsed_ms;

	delta = -(1.0f - (-1.0f)) / 1000.0f;
	vol = 1.0f;

	// Start the timer
	timer.tic();

	// Get the current time
	TimeElapsed_ms = Time::quotient(timer.toc(), Time(Duration::TIME_ONE_MILLISECOND));

	// Loop for 2 seconds
	// reduced to 1400 ms to avoid setting the volume after the voice end
	while ( TimeElapsed_ms < 1400 )
	{
		// Set volume	
		vol += delta;
		status = pSnd->Vol(vol);
		
		if (status != Handle::Status::SUCCESS)
		{
			assert(false);
		}

		// update every 1 ms
		std::this_thread::sleep_for(std::chrono::microseconds(1000));

		// Update time
		TimeElapsed_ms = Time::quotient(timer.toc(), Time(Duration::TIME_ONE_MILLISECOND));
	}

	Trace::out("---> End of thread: Demo1C_0 \n");
}

// --- End of File ---
