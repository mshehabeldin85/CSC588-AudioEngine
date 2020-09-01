//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "ASndEnd.h"
#include "ASndMan.h"

ASndEnd::ASndEnd(SndID snd_id, Snd* p)
	:ACommand(snd_id, p)
{
}

void ASndEnd::Execute()
{
	assert(this->pSnd);

	// Get the ASnd
	ASnd* pA;
	this->pSnd->proGetASnd(pA);
	assert(pA);

	// Now End the sound
	pA->SndEnd();

}

// --- End of File ---
