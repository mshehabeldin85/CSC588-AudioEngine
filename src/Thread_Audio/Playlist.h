//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "Handle.h"
#include "DLink.h"
#include "Wave.h"
#include "SndID.h"
#include "Voice.h"

class PLScript
{
	// Future
	// Command pattern
};

// This class is only there for pretty UML
class Playlist_Link : public DLink
{
};

class Playlist : public Playlist_Link
{
public:
	// Big 4
	Playlist();
	Playlist(const Playlist&) = delete;
	Playlist& operator = (const Playlist &) = delete;
	virtual ~Playlist();

	Handle::Status Set(SndID snd_id, Voice::ID voice_id, Wave::ID wave_id);

	// Manager methods
	Handle::Status GetId(SndID &);
	Handle::Status SetId(SndID );

	Handle::Status Wash();
	Handle::Status Dump();

	//---- COMMANDS -----

	Handle::Status Play();
	Handle::Status Stop();
	Handle::Status Vol(float vol);
	Handle::Status Pan(float pan);
	Handle::Status SndEnd();

	// Stitch sound
	void StartStitching();
	void StitchSound(SndID sndId);
	XAUDIO2_BUFFER_ALIAS* GetVoiceBuffer();

private:
	void privClear();

public:
	//-------------------------------------------
	// Data:  public for now
	//-------------------------------------------
	PLScript *poScript;
	Voice    *pVoice;
	SndID     id;

	Handle handle;
};

#endif

// --- End of File ---
