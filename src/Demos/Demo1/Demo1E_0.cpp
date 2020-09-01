//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Demo1E_0.h"

// Thread stuff
#include "ThreadHelper.h"

// Timer
#include "Timer.h"

// Launch point for thread
void Demo1E_0_Main(Snd *pSnd)
{
	Trace::out("---> Start of thread: Demo1E_0 \n");

	assert(pSnd);

	Handle::Status status;
	Timer timer;	
	int TimeElapsed_ms;
	bool endThread;
	bool playOnceSndB;
	bool playOnceSndC;
	bool playOnceSndD;

	// Start the timer
	timer.tic();

	// Get the current time
	TimeElapsed_ms = Time::quotient(timer.toc(), Time(Duration::TIME_ONE_MILLISECOND));

	// Sounds
	Snd* pSndB = nullptr;
	Snd* pSndC = nullptr;
	Snd* pSndD = nullptr;

	// Initialize thread flags
	endThread = false;
	playOnceSndB = false;
	playOnceSndC = false;
	playOnceSndD = false;

	// Loop until thread is ended
	while ( !endThread )
	{
		// at 80.5 seconds
		if (TimeElapsed_ms >= 500 && !playOnceSndB)
		{
			pSndB = SndMan::Add(SndID::Bassoon);
			assert(pSndB);

			// Vol
			pSndB->Vol(0.4f);

			// Call the sound
			assert(pSndB->Play() == Handle::Status::SUCCESS);

			playOnceSndB = true;
		}

		// at 81 seconds
		if (TimeElapsed_ms >= 1000 && !playOnceSndC)
		{
			pSndC = SndMan::Add(SndID::Bassoon);
			assert(pSndC);

			// Vol
			pSndC->Vol(0.4f);

			// Call the sound
			assert(pSndC->Play() == Handle::Status::SUCCESS);

			playOnceSndC = true;
		}

		// at 81.5 seconds
		if (TimeElapsed_ms >= 1500 && !playOnceSndD)
		{
			pSndD = SndMan::Add(SndID::Bassoon);
			assert(pSndD);

			// Vol
			pSndD->Vol(0.4f);

			// Call the sound
			assert(pSndD->Play() == Handle::Status::SUCCESS);

			playOnceSndD = true;
		}

		// at 81.5 seconds
		if (TimeElapsed_ms >= 1500)
		{
			// Stop sound A
			status = pSnd->End();
			if (status != Handle::Status::SUCCESS)
			{
				assert(false);
			}

			// Stop sound B
			status = pSndB->End();
			if (status != Handle::Status::SUCCESS)
			{
				assert(false);
			}

			// Stop sound C
			status = pSndC->End();
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
	}

	Trace::out("---> End of thread: Demo1E_0 \n");
}

// --- End of File ---
