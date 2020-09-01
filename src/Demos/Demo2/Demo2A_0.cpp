//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Demo2A_0.h"

// Thread stuff
#include "ThreadHelper.h"

// Timer
#include "Timer.h"

// Launch point for thread
void Demo2A_0_Main(Snd *pSnd)
{
	Trace::out("---> Start of thread: Demo2A_0 \n");

	assert(pSnd);

	Handle::Status status;
	Timer timer;	
	int TimeElapsed_ms;

	// Temp variables to switch panning
	static int deltaTime = 10000;
	static int actionIndex = 0;

	// Start the timer
	timer.tic();

	// Get the current time
	TimeElapsed_ms = Time::quotient(timer.toc(), Time(Duration::TIME_ONE_MILLISECOND));

	// Loop for 2 seconds
	while ( !pSnd->GetSoundEnded() )
	{
		if (TimeElapsed_ms >= deltaTime)
		{
			// increment the action index
			actionIndex++;

			// Increment the delta time by 10 seconds
			deltaTime += 10000;

			// Index of Pan Right action
			if (actionIndex == 1)
			{
				status = pSnd->Pan(1.0f);

				if (status != Handle::Status::SUCCESS)
				{
					assert(false);
				}
			}

			// Index of Pan Left action
			if (actionIndex == 2)
			{
				status = pSnd->Pan(-1.0f);

				if (status != Handle::Status::SUCCESS)
				{
					assert(false);
				}
			}

			// Index of Pan center action
			if (actionIndex == 3)
			{
				status = pSnd->Pan(0.0f);

				if (status != Handle::Status::SUCCESS)
				{
					assert(false);
				}

				// Since this is the last index, the reset it to start form the beginning
				actionIndex = 0;
			}
		}

		// update every 1 ms
		std::this_thread::sleep_for(std::chrono::microseconds(1000));
	
		// Update time
		TimeElapsed_ms = Time::quotient(timer.toc(), Time(Duration::TIME_ONE_MILLISECOND));
	}

	Trace::out("---> End of thread: Demo2A_0 \n");
}

// --- End of File ---
