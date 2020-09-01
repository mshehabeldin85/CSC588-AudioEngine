//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "ThreadHelper.h"

#include "AudioMain.h"

#include "VoiceMan.h"
#include "WaveMan.h"
#include "PlaylistMan.h"
#include "ASndMan.h"
#include "Command.h"
#include "SndMan.h"

//-------------------------------------------------------------
// Audio thread main (loop)
//-------------------------------------------------------------
void AudioMain()
{
	ThreadHelper::DebugBegin(1);

	while ( !ASndMan::IsQuit() )
	{
		Command* pCmd = nullptr;
	
		// Any commands to process?
		if (SndMan::GetAudioInQueue()->PopFront(pCmd) == true)
		{
			assert(pCmd);
			pCmd->Execute();

			// Commands are instantly killed after execution
			delete pCmd;
		}
	}

	ThreadHelper::DebugEnd(1);
}

// --- End of file ---
