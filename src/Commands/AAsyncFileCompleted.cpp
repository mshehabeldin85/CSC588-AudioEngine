//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "ThreadHelper.h"
#include "AAsyncFileCompleted.h"
#include "WaveMan.h"

AAsyncFileCompleted::AAsyncFileCompleted(Wave::ID _waveID, WAVEFORMATEXTENSIBLE* _pWfx, unsigned int _rawBuffSize, RawData* _pRawBuff)
	:	waveID(_waveID), 
	pWfx(_pWfx),
	rawBuffSize(_rawBuffSize), 
	pRawBuff(_pRawBuff)
{
	assert(pWfx);
	assert(rawBuffSize > 0);
	assert(pRawBuff);
}

void AAsyncFileCompleted::Execute()
{
	Trace::out("%s AAsyncFileCompleted: \n  waveID:%x, \n  pWfx:%p, \n  rawBuffSize:0x%x, \n  pRawBuff:%p\n",
		ThreadHelper::GetThreadName(),waveID, pWfx, rawBuffSize, pRawBuff);

	Wave *pWave = WaveMan::Find(waveID);
	assert(pWave);

	pWave->Completed(this->pWfx, this->rawBuffSize, this->pRawBuff);
}

// --- End of File ---
