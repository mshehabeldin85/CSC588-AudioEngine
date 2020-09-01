//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "VoiceCallback.h"
#include "ACommandQueue.h"
#include "ASndMan.h"
#include "SndMan.h"

VoiceCallback::VoiceCallback()
:pASnd(nullptr),
pNextSnd(nullptr)
{
}

VoiceCallback::~VoiceCallback()
{
}

void VoiceCallback::SetASnd(ASnd* _pASnd)
{
	assert(_pASnd);
	this->pASnd = _pASnd;
}

ASnd* VoiceCallback::GetASnd()
{
	assert(this->pASnd);
	return this->pASnd;
}

void VoiceCallback::SetNextSnd()
{
	this->pASnd->Dump();
	this->pNextSnd = (ASnd*)this->pASnd->pNext;
}

void STDMETHODCALLTYPE VoiceCallback::OnStreamEnd() noexcept
{
	if (this->pNextSnd != nullptr)
	{
		// Print current node name
		this->pNextSnd->Dump();

		SndID sndId;
		this->pNextSnd->GetId(sndId);
		this->pASnd->StitchSound(sndId);

		// Move to the next sound
		this->pNextSnd = (ASnd*)this->pNextSnd->pNext;
	}
	else
	{
		Snd* pSnd = this->pASnd->GetSnd();
		assert(pSnd);

		pSnd->SetSoundEnded();

		Trace::out("VoiceCallback: StreamEnd \n");

		// Send a command and leave
		assert(this->pASnd);
		ACommandQueue::SndEnd(this->pASnd);
	}
}

void STDMETHODCALLTYPE VoiceCallback::OnVoiceProcessingPassEnd() noexcept
{
}

void STDMETHODCALLTYPE VoiceCallback::OnVoiceProcessingPassStart(UINT32) noexcept
{
}

void STDMETHODCALLTYPE VoiceCallback::OnBufferEnd(void*) noexcept
{
}

void STDMETHODCALLTYPE VoiceCallback::OnBufferStart(void*) noexcept
{
}

void STDMETHODCALLTYPE VoiceCallback::OnLoopEnd(void*) noexcept
{
}

void STDMETHODCALLTYPE VoiceCallback::OnVoiceError(void*, HRESULT) noexcept
{
}


// --- End of File ---