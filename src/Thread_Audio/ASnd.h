//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef ASND_H
#define ASND_H

#include "DLink.h"
#include "SndID.h"
#include "Handle.h"
#include "Playlist.h"

class UserCallback;
class Snd;

// This class is only there for pretty UML
class ASnd_Link : public DLink
{
};

class ASnd : public ASnd_Link
{
public:
	ASnd();
	ASnd(const ASnd&) = delete;
	ASnd& operator = (const ASnd&) = delete;
	~ASnd();

	Handle::Status SetId(SndID );
	Handle::Status GetId(SndID &);

	Handle::Status Set(SndID snd_id);

	Handle::Status Dump();
	Handle::Status Wash();

	const char* privGetStringName();

	// --- COMMANDS -----------
	Handle::Status Play();
	Handle::Status Stop();
	Handle::Status Vol(float vol);
	Handle::Status Pan(float pan);
	Handle::Status SndEnd();


	void SetSnd(Snd* pSnd);
	Snd* GetSnd();

	// Stitch sound
	void StartStitching();
	void StitchSound(SndID sndId);
	XAUDIO2_BUFFER_ALIAS* GetVoiceBuffer();

private:
	void privClear();

	//-------------------------------------------
	// Data:  public for now
	//-------------------------------------------

public:
	SndID	 id;
	Playlist* pPlaylist;
	Snd* pSnd;
	UserCallback* poUserCallback;

	float	vol;
	float   pan;

	// Protect it with a handle
	Handle	handle;
};

#endif

// --- End of File ---
