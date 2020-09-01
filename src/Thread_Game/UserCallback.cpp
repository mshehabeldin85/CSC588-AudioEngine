//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "ThreadHelper.h"
#include "UserCallBack.h"
#include "Snd.h"

void UserCallback::Set(Snd* _pSnd, char* waveName, int _TimeInMs)
{
	assert(_pSnd);
	this->pSnd = _pSnd;
	assert(waveName);
	this->pWaveName = waveName;
	this->TimeInMs = _TimeInMs;
}

void UserCallback::Execute()
{
	assert(this->pSnd);
	assert(this->pWaveName);

	Trace::out("------------------------------\n");
	Trace::out("%s  UserCallback() \n", ThreadHelper::GetThreadName());

	SndID id;
	this->pSnd->GetID(id);

	Trace::out("      SndID: 0x%x \n", id);


	Trace::out("       Time: %d ms \n", this->TimeInMs);

	float pan;
	this->pSnd->GetPan(pan);
	Trace::out("        Pan: %f  \n", pan);

	Trace::out("       Wave: %s  \n", this->pWaveName);

	Trace::out("------------------------------\n");

}

// --- End of File ---