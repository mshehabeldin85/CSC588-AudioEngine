//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "ThreadHelper.h"
#include "XAudio2Wrapper.h"
#include "AudioEngine.h"
#include "Wave.h"
#include "FileMan.h"
#include "FAsyncFileLoad.h"
#include "SndMan.h"
#include "GFileUserCallback.h"


Wave::Wave()
	: poWfx(nullptr),
	poRawBuff(nullptr),
	rawBuffSize(0),
	id(Uninitialized),
	strName("uninialized"),
	WaveStatus(Wave::Status::UNINITIALIZED),
	pFileUserCallback(nullptr),
	handle()
{
	// nothing dynamic...
	
	// Pattern:
	//    Manager calls default wave
	//    set(...)  dynamic allocation
	//    privClear(...) release dynamic allocation
	//    destructor release of any owned objects
}

Wave::~Wave()
{
	delete this->poWfx;
	delete[] this->poRawBuff;

	// check "this" and input
	assert(Handle::ValidateHandle(this->handle) == Handle::Status::SUCCESS);
}

Handle::Status Wave::SetId(Wave::ID _id)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		this->id = _id;
	}
	return lock;
}

Handle::Status Wave::GetId(Wave::ID &_id) const
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		_id = this->id;
	}
	return lock;
}

Handle::Status Wave::Set(const char* const pWaveName, Wave::ID wave_id, FileUserCallback* pFileUserCB)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		assert(pWaveName);

		// Filled when async completed
		this->poWfx = nullptr;
		this->rawBuffSize = 0;
		this->poRawBuff = nullptr;

		this->id = wave_id;
		this->WaveStatus = Wave::Status::ASYNC_LOADING;
		this->pFileUserCallback = pFileUserCB;

		this->privSetName(pWaveName);

		// Start Async load
		CircularData* pOut = FileMan::GetFileInQueue();
		assert(pOut);

		Command* pCmd = new FAsyncFileLoad(pWaveName, wave_id);
		assert(pCmd);

		pOut->PushBack(pCmd);
	}
	return lock;
}

Handle::Status Wave::Completed(WAVEFORMATEXTENSIBLE* pWfx, unsigned int _rawBuffSize, RawData* pRawBuff)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		Trace::out("%s Wave::Completed: \n  waveID:%x, \n  pWfx:%p, \n  rawBuffSize:0x%x, \n  pRawBuff:%p\n",
			ThreadHelper::GetThreadName(), this->id, pWfx, _rawBuffSize, pRawBuff);

		assert(pWfx);
		this->poWfx = pWfx;

		assert(_rawBuffSize > 0);
		this->rawBuffSize = _rawBuffSize;

		assert(pRawBuff);
		this->poRawBuff = pRawBuff;

		assert(this->WaveStatus == Wave::Status::ASYNC_LOADING);
		this->WaveStatus = Wave::Status::READY;
		
		// Is there a File Callback?
		if (this->pFileUserCallback)
		{
			// Start Async load
			CircularData* pOut = SndMan::GetGameInQueue();
			assert(pOut);

			Command* pCmd = new GFileUserCallback(this->id, this->pFileUserCallback);
			assert(pCmd);

			pOut->PushBack(pCmd);
		}
	}
	return lock;
}

Handle::Status  Wave::Dump()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		// Dump - Print contents to the debug output window
		Trace::out("   Name: 0x%x (%p) %s\n", this->id, this, this->strName);
	}
	return lock;
}

void Wave::privClear()
{
	// This method... is used in wash to reuse the wave

	// Reset the fmt
	delete this->poWfx;
	this->poWfx = nullptr;

	delete[] this->poRawBuff;
	this->poRawBuff = nullptr;

	// ID
	this->id = Wave::ID::Uninitialized;

	// Status
	this->WaveStatus = Wave::Status::UNINITIALIZED;

	// user callback
	delete this->pFileUserCallback;
	this->pFileUserCallback = nullptr;

	// Name
	char* pWaveName = "	Uninitialized";
	this->privSetName(pWaveName);
}

Handle::Status Wave::Wash()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		// Wash - clear the entire hierarchy
		DLink::Clear();

		// Sub class clear
		this->privClear();
	} 
	return lock;
}

void Wave::privSetName(const char* const pWaveName)
{
	assert(pWaveName);
	memset(this->strName, 0x0, Wave::NAME_SIZE);

	// Quick hack to trim the string before '/
	unsigned int len = strlen(pWaveName);

	const char* pEnd = pWaveName + len;
	const char* pStart = pEnd;

	while (pStart != pWaveName)
	{
		if (*pStart == '/')
		{
			pStart++;
			break;
		}
		pStart--;
	}

	// At this point we have a trimmed name
	strcpy_s(this->strName, Wave::NAME_SIZE, pStart);
}

// --- End of File ---
