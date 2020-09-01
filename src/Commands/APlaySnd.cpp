//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "APlaySnd.h"
#include "ASndMan.h"

APlaySnd::APlaySnd(SndID snd_id, Snd* p)
	:ACommand(snd_id, p)
{
}

void APlaySnd::Execute()
{
	assert(this->pSnd);

	// Get the ASnd
	ASnd* pA;

	this->pSnd->proGetASnd(pA);
	assert(pA);

	// Now play it
	pA->Play();
}

// --- End of File ---