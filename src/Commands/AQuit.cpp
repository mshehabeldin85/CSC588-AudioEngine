//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "AQuit.h"
#include "ASndMan.h"

AQuit::AQuit(SndID snd_id, Snd* p)
	:ACommand(snd_id, p)
{
}

void AQuit::Execute()
{
	ASndMan::SetQuit();
}

// --- End of File ---
