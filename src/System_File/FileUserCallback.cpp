//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "FileUserCallBack.h"
#include "SndMan.h"

void FileUserCallback::Set(SndID _sndID)
{
	this->sndID = _sndID;
}

void FileUserCallback::SetStopSnd(SndID sndId)
{
	this->stopSndID = sndId;
}

void FileUserCallback::Execute()
{
	Trace::out("------------------------------\n");
	Trace::out("  FileUserCallback() \n");
	Trace::out("------------------------------\n");
	Trace::out("     Play(%d)\n",this->sndID);

	Snd *pSndC;
	pSndC = SndMan::Add(this->sndID);
	assert(pSndC);

	// Vol & Pan
	assert(pSndC->Vol(0.50f) == Handle::Status::SUCCESS);
	//assert(pSndC->Pan(0.0f) == Handle::Status::SUCCESS);

	// Call the sound
	assert(pSndC->Play() == Handle::Status::SUCCESS);


	Trace::out("     Stop(%d)\n", this->stopSndID);

	Snd* pSndA = SndMan::Find(this->stopSndID);
	assert(pSndA->End() == Handle::Status::SUCCESS);


	Trace::out("------------------------------\n");
}

// --- End of File ---
