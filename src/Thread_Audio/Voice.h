//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef VOICE_H
#define VOICE_H

#include "XAudio2Wrapper.h"
#include "Handle.h"
#include "DLink.h"
#include "Wave.h"

struct XAUDIO2_BUFFER_ALIAS
{
	UINT32 Flags;                       // Either 0 or XAUDIO2_END_OF_STREAM.
	UINT32 AudioBytes;                  // Size of the audio data buffer in bytes.
	RawData *pAudioData;             // Pointer to the audio data buffer.
	UINT32 PlayBegin;                   // First sample in this buffer to be played.
	UINT32 PlayLength;                  // Length of the region to be played in samples,
										//  or 0 to play the whole buffer.
	UINT32 LoopBegin;                   // First sample of the region to be looped.
	UINT32 LoopLength;                  // Length of the desired loop region in samples,
										//  or 0 to loop the entire buffer.
	UINT32 LoopCount;                   // Number of times to repeat the loop region,
										//  or XAUDIO2_LOOP_INFINITE to loop forever.
	void* pContext;                     // Context value to be passed back in callbacks.
};

// This class is only there for pretty UML
class Voice_Link : public DLink
{
};

class Voice : public Voice_Link
{
public:
	enum ID
	{
		Fiddle = 0x88880000,
		Bassoon,
		Calliope,
		Oboe,
		SongA,
		SongB,

		Intro_mono,
		A_mono,
		AtoB_mono,
		B_mono,
		BtoC_mono,
		C_mono,
		CtoA_mono,
		End_mono,

		Coma,

		Dial,
		MoonPatrol,
		Sequence,
		Donkey,

		Electro,
		Alarm,
		Beethoven,

		Uninitialized
	};

public:
	// Big 4
	Voice();
	Voice(const Voice &) = delete;
	Voice & operator = (const Voice &) = delete;
	virtual ~Voice();

	Handle::Status Set(Voice::ID _id, Wave* pWave);

	// Manager methods
	Handle::Status GetId(Voice::ID &);
	Handle::Status SetId(Voice::ID name);

	Handle::Status Wash();
	Handle::Status Dump();

	// Protection with Handles
	Handle::Status Start();
	Handle::Status Stop();
	Handle::Status Vol(float vol);
	Handle::Status Pan(float pan);

	// Stitch sound
	void StartStitching();
	XAUDIO2_BUFFER_ALIAS* GetBuffer();
	void AddBuffer(XAUDIO2_BUFFER_ALIAS* pBuff);

private:
	void privClear();
	const char* privGetStringName();

public:
	//-------------------------------------------
	// Data:  public for now
	//-------------------------------------------
	XAUDIO2_BUFFER_ALIAS *poBuff;
	IXAudio2VoiceCallback *poCallback;
	IXAudio2SourceVoice   *poSourceVoice;
	Wave                  *pWave;
	ID                    id;

	Handle handle;
};

#endif

// --- End of File ---
