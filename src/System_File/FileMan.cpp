//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "FileMan.h"
#include "SndMan.h"
#include "AFileLoad.h"
#include "FQuit.h"
#include "WaveMan.h"

FileMan::FileMan()
{
	this->poFileInQueue = new CircularData();
	assert(poFileInQueue);

	this->QuitFlag = false;
}

FileMan::~FileMan()
{
	assert(FileMan::IsQuit() == true);

	// We created it... so we delete it
	delete this->poFileInQueue;


}

//----------------------------------------------------------------------
// Static Methods
//----------------------------------------------------------------------
Wave::Status FileMan::GetStatus(Wave::ID id)
{
	FileMan* pMan = FileMan::privGetInstance();
	assert(pMan != nullptr);

	Wave::Status status = Wave::Status::UNINITIALIZED;

	Wave* pWave = WaveMan::Find(id);
	if (pWave)
	{
		status = pWave->WaveStatus;
	}

	return status;
}

void FileMan::Quit()
{
	FileMan* pMan = FileMan::privGetInstance();
	assert(pMan != nullptr);

	// Place the "Quit" command in the queue 
	CircularData* pOut = FileMan::GetFileInQueue();
	assert(pOut);

	Command* pCmd = new FQuit();
	assert(pCmd);

	pOut->PushBack(pCmd);
}


CircularData* FileMan::GetFileInQueue()
{
	FileMan* pMan = FileMan::privGetInstance();
	return pMan->poFileInQueue;
}

Handle::Status FileMan::Add(const char* const pWaveName, Wave::ID name, FileUserCallback* pFileCallback)
{
	FileMan* pMan = FileMan::privGetInstance();
	assert(pMan != nullptr);

	Handle::Lock lock(pMan->handle);

	if (lock)
	{
		// Now create a the sound call on the Audio thread
		// Place the "Create" command in the queue to the Audio thread
		CircularData* pOut = SndMan::GetAudioInQueue();
		assert(pOut);

		// Doesn't need to know snd_priority its only on game side
		Command* pCmd = new AFileLoad(pWaveName, name, pFileCallback);
		assert(pCmd);

		pOut->PushBack(pCmd);
	}
	else
	{
		assert(false);
	}

	//Trace::out("SndMan::Add() unlock\n");
	return lock;
}

void FileMan::SetQuit()
{
	FileMan* pMan = FileMan::privGetInstance();
	assert(pMan != nullptr);

	pMan->QuitFlag = true;
}

bool  FileMan::IsQuit()
{
	FileMan* pMan = FileMan::privGetInstance();
	assert(pMan != nullptr);

	return pMan->QuitFlag;
}


//----------------------------------------------------------------------
// Private methods
//----------------------------------------------------------------------
FileMan* FileMan::privGetInstance()
{
	static FileMan fileMan;

	return &fileMan;
}


// --- End of File ---