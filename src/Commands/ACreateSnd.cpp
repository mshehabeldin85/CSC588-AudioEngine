//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "ACreateSnd.h"
#include "ASndMan.h"
#include "VoiceCallback.h"
#include "UserCallBack.h"

ACreateSnd::ACreateSnd(SndID snd_id, Snd* p, UserCallback* _pUserCallback)
	:ACommand(snd_id, p),
	pUserCallback(_pUserCallback)
{
}

void ACreateSnd::Execute()
{
	assert(this->id != SndID::Uninitialized);

	ASnd* pA = ASndMan::Add(this->id);
	assert(pA);

	// Update the SND call
	// This way its faster to execute commands on the Audio thread side

	assert(this->pSnd);
	pSnd->proSetASnd(pA);
	pA->SetSnd(pSnd);

	// user callback
	pA->poUserCallback = this->pUserCallback;

	// Set the ASnd pointer in the VoiceCallback - HACK
	// Not sure if this is the best place for this...
	Playlist* pPlaylist = pA->pPlaylist;
	assert(pPlaylist);

	Voice* pVoice = pPlaylist->pVoice;
	assert(pVoice);
	pVoice->poCallback;

	// OK to down cast this... might want to change voice.h to use VoiceCallback
	VoiceCallback* pCallback = (VoiceCallback*)pVoice->poCallback;
	assert(pCallback);

	pCallback->SetASnd(pA);

}

// --- End of File ---