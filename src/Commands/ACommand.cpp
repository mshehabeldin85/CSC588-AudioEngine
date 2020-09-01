//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "ACommand.h"

ACommand::ACommand(SndID snd_id, Snd* p)
{
	this->id = snd_id;

	assert(p);
	this->pSnd = p;
}

// --- End of File ---
