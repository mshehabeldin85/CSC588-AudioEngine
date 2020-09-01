//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef DEMO3_9_H
#define DEMO3_9_H

#include "Command.h"
#include "SndMan.h"
#include "VoiceMan.h"

class Demo3_9 : public Command
{
public:
	Demo3_9() = default;
	~Demo3_9() = default;
	Demo3_9(const Demo3_9 &) = delete;
	Demo3_9 & operator = (const Demo3_9 &) = delete;

	// Behold the demo
	virtual void Execute() override
	{
		Trace::out("Demo3 part: 13s \n");

		// Print snd priority table
		Snd::PrintPriorityTable();

		// Stop sounds
		SndMan::StopAll();
	}

};

#endif

// --- End of File ---
