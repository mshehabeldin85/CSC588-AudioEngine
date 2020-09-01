//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "ThreadHelper.h"
#include "AFileLoad.h"
#include "WaveMan.h"

AFileLoad::AFileLoad(const char * const _pWaveName, Wave::ID name, FileUserCallback *pFileCB)
	: 	pFileUserCallback(pFileCB),
	waveID(name),
	pWaveName(_pWaveName)
{
}

void AFileLoad::Execute()
{
	Trace::out("%s AFileLoad: \n  callback:%p, \n  waveID:%x, \n  wavename:%s \n", ThreadHelper::GetThreadName(), pFileUserCallback, waveID, pWaveName);

	WaveMan::Add(pWaveName, waveID, pFileUserCallback);

}

// --- End of File ---
