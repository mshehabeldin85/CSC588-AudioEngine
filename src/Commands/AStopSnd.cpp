//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "AStopSnd.h"
#include "ASndMan.h"

AStopSnd::AStopSnd(SndID snd_id, Snd* p)
	:ACommand(snd_id, p)
{
}

void AStopSnd::Execute()
{
	assert(this->pSnd);

	// Get the ASnd
	ASnd* pA;

	this->pSnd->proGetASnd(pA);
	assert(pA);

	// Now Stop it
	pA->Stop();

}

// --- End of File ---
