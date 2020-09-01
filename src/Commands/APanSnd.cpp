//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "APanSnd.h"
#include "ASndMan.h"

APanSnd::APanSnd(SndID snd_id, Snd* p, float snd_pan)
	:ACommand(snd_id, p), pan(snd_pan)
{
}

void APanSnd::Execute()
{
	assert(this->pSnd);

	// Get the ASnd
	ASnd* pA;

	this->pSnd->proGetASnd(pA);
	assert(pA);

	// Now pan it
	pA->Pan(this->pan);

}

// --- End of File ---