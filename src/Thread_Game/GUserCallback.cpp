//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "GUserCallback.h"
#include "ThreadHelper.h"


GUserCallback::GUserCallback(UserCallback* _pUserCB)
	:pUserCB(_pUserCB)
{
	assert(this->pUserCB);
}


void GUserCallback::Execute()
{
	Trace::out("%s GUserCallback: \n  callback:%p \n", ThreadHelper::GetThreadName(),  this->pUserCB);
	this->pUserCB->Execute();

	delete this->pUserCB;
}


// --- End of File ---
