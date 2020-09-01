//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "AStartStitch.h"
#include "ASndMan.h"

AStartStitch::AStartStitch(SndID snd_id, Snd* p)
	:ACommand(snd_id, p)
{
}

void AStartStitch::Execute()
{
	// Get the ASnd
	ASnd* pA;

	this->pSnd->proGetASnd(pA);
	assert(pA);

	// Now start stitching
	pA->StartStitching();

}

// --- End of File ---