//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "XAudio2Wrapper.h"

#include "AudioEngine.h"
#include "Playlist.h"
#include "VoiceMan.h"
#include "Snd.h"
#include "SndMan.h"


Playlist::Playlist()
	: poScript(nullptr),
	 pVoice(nullptr),
	id(SndID::Uninitialized),
	handle()
{
	// nothing dynamic...

	// Pattern:
	//    Manager calls default wave
	//    set(...)  dynamic allocation
	//    privClear(...) release dynamic allocation
	//    destructor release of any owned objects
}

Handle::Status Playlist::Wash()
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

Handle::Status Playlist::Set(SndID snd_id, Voice::ID voice_id, Wave::ID wave_id)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		this->id = snd_id;

		this->pVoice = VoiceMan::Add(voice_id, wave_id);
		assert(this->pVoice);
	}
	return lock;
}

void Playlist::privClear()
{
	this->pVoice = nullptr;

	// Command pattern
	this->poScript = nullptr;

	this->id = SndID::Uninitialized;
}

Handle::Status Playlist::Dump()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		// Dump - Print contents to the debug output window
		Trace::out("   Name: %d (%p) \n", this->id, this);
	}
	return lock;
}


Playlist::~Playlist()
{

	// check "this" and input
	assert(Handle::ValidateHandle(this->handle) == Handle::Status::SUCCESS);
}

Handle::Status Playlist::SetId(SndID snd_id)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		this->id = snd_id;
	}
	return lock;
}

Handle::Status Playlist::GetId(SndID &_id)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		_id = this->id;
	}
	return lock;
}

Handle::Status  Playlist::Play()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		assert(this->id != SndID::Uninitialized);
		assert(this->pVoice);

		this->pVoice->Start();
	}
	return lock;
}

Handle::Status  Playlist::Stop()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		assert(this->id != SndID::Uninitialized);
		assert(this->pVoice);

		this->pVoice->Stop();
	}
	return lock;
}

Handle::Status  Playlist::Vol(float snd_vol)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		assert(this->id != SndID::Uninitialized);
		assert(this->pVoice);

		this->pVoice->Vol(snd_vol);
	}
	return lock;
}

Handle::Status  Playlist::Pan(float snd_pan)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		assert(this->id != SndID::Uninitialized);
		assert(this->pVoice);

		this->pVoice->Pan(snd_pan);
	}
	return lock;
}

Handle::Status Playlist::SndEnd()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		assert(this->id != SndID::Uninitialized);
		assert(this->pVoice);

		// Stop the voice if its not already stopped
		this->pVoice->Stop();

		// Now remove it off the active
		VoiceMan::Remove(this->pVoice);
	}
	return lock;
}

void Playlist::StartStitching()
{
	this->pVoice->StartStitching();
}

void Playlist::StitchSound(SndID sndId)
{
	Snd* pSnd = SndMan::Find(sndId);
	assert(pSnd);
	XAUDIO2_BUFFER_ALIAS* pBuff = pSnd->GetVoiceBuffer();
	this->pVoice->AddBuffer(pBuff);
}

XAUDIO2_BUFFER_ALIAS* Playlist::GetVoiceBuffer()
{
	return this->pVoice->GetBuffer();
}

// --- End of File ---
