//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "GFileUserCallback.h"
#include "ThreadHelper.h"
#include "SndMan.h"

GFileUserCallback::GFileUserCallback(Wave::ID _name, FileUserCallback* _pFileCB)
	:pFileCB(_pFileCB),
	wave_id(_name)
{
	assert(this->pFileCB);
}


void GFileUserCallback::Execute()
{
	Trace::out("%s GFileUserCallback: \n  waveID:%x,\n  callback:%p \n", ThreadHelper::GetThreadName(), this->wave_id, this->pFileCB);
	this->pFileCB->Execute();

	delete this->pFileCB;
}


// --- End of File ---
