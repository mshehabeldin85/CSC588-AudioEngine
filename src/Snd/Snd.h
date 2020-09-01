//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SND_H
#define SND_H

#include "DLink.h"
#include "SndID.h"
#include "Handle.h"
#include "ASnd.h"
#include "SndPriorityEntry.h"
#include "Timer.h"

typedef int SndPriority;

// This class is only there for pretty UML
class Snd_Link : public DLink
{
};

class Snd : public Snd_Link
{
public:
	// constants
	static const unsigned int SND_PRIORITY_TABLE_SIZE = 6;
	static const int SND_PRIORITY_TABLE_INVALID = -1;

public:
	Snd();
	Snd(const Snd&) = delete;
	Snd & operator = (const Snd&) = delete;
	~Snd();

	Handle::Status SetID(SndID snd_id);
	Handle::Status GetID(SndID &snd_id);

	//Handle::Status Set(SndID snd_id);
	Handle::Status Set(SndID snd_id, SndPriority snd_priority);

	Handle::Status Dump();
	Handle::Status Wash();

	// --- COMMANDS -----------
	Handle::Status Play();
	Handle::Status Stop();
	Handle::Status End();
	Handle::Status Vol(float vol);
	Handle::Status Pan(float pan);
	Handle::Status StartStitching();

	Handle::Status GetVol(float& snd_vol);
	Handle::Status GetPan(float& snd_pan);
	Handle::Status GetTimeInMS(int& timeInMS);

	// Audio thread sets - only accessed in ASnd
	// need to make this "private" so game can never call it
	void proSetASnd(ASnd* p);
	void proGetASnd(ASnd*& p);

	// Sound Table
	Handle::Status RemoveFromPriorityTable();
	static void PrintPriorityTable();

	// Sound Ended flag
	void SetSoundEnded();
	bool GetSoundEnded();

	// Stitch sound
	XAUDIO2_BUFFER_ALIAS* GetVoiceBuffer();

	//------- DEBUG -----------------
	unsigned int GetHandleID()
	{
		return this->handle.GetID();
	}
	unsigned int GetHandleIndex()
	{
		return this->handle.GetIndex();
	}

private:
	void privClear();

	bool privUseOpenSlotInTable();

	//-------------------------------------------
	// Data:  public for now
	//-------------------------------------------

private:
	SndID	 id;
	ASnd* pASnd;

	float	vol;
	float   pan;
	SndPriority priority;

	// Protect it with a handle
	Handle	handle;

	bool sndEnded;

public:
	// ------- STATIC ----------------
	static SndPriorityEntry  sndPriorityTable[SND_PRIORITY_TABLE_SIZE];
	static Handle	         table_handle;
};

#endif


// End of File 
