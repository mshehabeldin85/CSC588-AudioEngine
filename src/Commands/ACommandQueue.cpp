//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "ACommandQueue.h"
#include "SndMan.h"
#include "ASnd.h"
#include "SndID.h"
#include "ASndEnd.h"
#include "ASndMan.h"

void ACommandQueue::SndEnd(ASnd* pASnd)
{
	// Place the Play command in the queue to the Audio thread
	CircularData* pOut = SndMan::GetAudioInQueue();
	assert(pOut);

	SndID id;
	assert(pASnd);
	Handle::Status status = pASnd->GetId(id);
	assert(status == Handle::Status::SUCCESS);

	Snd* pSnd = pASnd->GetSnd();
	assert(pSnd);

	Command* pCmd = new ASndEnd(id, pSnd);
	assert(pCmd);

	pOut->PushBack(pCmd);

	//Trace::out("ACommandQueue: SndEnd\n");

}

// --- End of File ---
