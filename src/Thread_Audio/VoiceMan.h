//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef VOICE_MAN_H
#define VOICE_MAN_H

#include "Manager.h"
#include "Voice.h"

// This class is only there for pretty UML
class VoiceMan_MLink : public Manager
{
public:
	Voice_Link* poActive;
	Voice_Link* poReserve;
};

class VoiceMan : public VoiceMan_MLink
{
	//----------------------------------------------------------------------
	// Big four
	//----------------------------------------------------------------------
private:
	VoiceMan(int reserveNum = 3, int reserveGrow = 1);
	VoiceMan(const VoiceMan&) = delete;
	VoiceMan& operator = (const VoiceMan&) = delete;
	VoiceMan() = delete;
	~VoiceMan();

public:

	//----------------------------------------------------------------------
	// Static Methods
	//----------------------------------------------------------------------
	static void Create(int reserveNum = 3, int reserveGrow = 1);
	static void Destroy();

	static Voice* Add(Voice::ID voice_id, Wave::ID wave_id);
	static Voice* Find(Voice::ID name);

	static void Remove(Voice* pNode);
	static void Dump();

	//----------------------------------------------------------------------
	// Override Abstract methods
	//----------------------------------------------------------------------

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
	static VoiceMan* privGetInstance();

	//----------------------------------------------------------------------
	// Data - unique data for this manager 
	//----------------------------------------------------------------------
	static VoiceMan* pInstance;
	Voice* poNodeCompare;
};

#endif

// --- End of File ---
