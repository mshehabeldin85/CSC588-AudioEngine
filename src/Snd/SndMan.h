//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SND_MAN_H
#define SND_MAN_H

#include "Manager.h"
#include "SndID.h"
#include "Snd.h"
#include "CircularData.h"
#include "UserCallBack.h"

// This class is only there for pretty UML
class SndMan_MLink : public Manager
{
public:
	Snd_Link* poActive;
	Snd_Link* poReserve;
};

class SndMan : public SndMan_MLink
{
	//----------------------------------------------------------------------
	// Big four
	//----------------------------------------------------------------------
private:
	SndMan(int reserveNum = 3, int reserveGrow = 1);
	SndMan(const SndMan&) = delete;
	SndMan& operator = (const SndMan&) = delete;
	SndMan() = delete;
	~SndMan();

public:

	//----------------------------------------------------------------------
	// Static Methods
	//----------------------------------------------------------------------
	static void Create(int reserveNum = 3, int reserveGrow = 1);
	static void Destroy();

	//static Snd* Add(SndID snd_id, SndPriority snd_priority = 0);
	static Snd* Add(SndID snd_id, UserCallback* pCallback = nullptr, SndPriority snd_priority = 0);
	static Snd* Find(SndID snd_id);
	static void Quit(SndID snd_id);

	static void Remove(Snd* pNode);
	static void Dump();
	static void StopAll();

	//----------------------------------------------------------------------
	// Override Abstract methods
	//----------------------------------------------------------------------

	static CircularData* GetAudioInQueue();
	static CircularData* GetGameInQueue();


protected:
	virtual DLink* DerivedCreateNode() override;
	virtual bool DerivedCompare(DLink* pLinkA, DLink* pLinkB) override;
	virtual void DerivedWash(DLink* pLink) override;
	virtual void DerivedDumpNode(DLink* pLink) override;
	virtual void DerivedDestroyNode(DLink* pLink) override;

	//----------------------------------------------------------------------
	// Private methods
	//----------------------------------------------------------------------
private:
	static SndMan* privGetInstance();

	//----------------------------------------------------------------------
	// Data - unique data for this manager 
	//----------------------------------------------------------------------
	static SndMan* poInstance;
	Snd* poNodeCompare;

	CircularData* poAudioInQueue;  // Audio in Queue
	CircularData* poGameInQueue;   // Game in Queue

};

#endif

// --- End of File ---
