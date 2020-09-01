//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef WAVE_MAN_H
#define WAVE_MAN_H

#include "Manager.h"
#include "Wave.h"
#include "FileUserCallback.h"

// This class is only there for pretty UML
class WaveMan_MLink : public Manager
{
public:
	Wave_Link* poActive;
	Wave_Link* poReserve;
};

class WaveMan : public WaveMan_MLink
{
	//----------------------------------------------------------------------
	// Big four
	//----------------------------------------------------------------------
private:
	WaveMan(int reserveNum = 3, int reserveGrow = 1);
	WaveMan(const WaveMan&) = delete;
	WaveMan& operator = (const WaveMan&) = delete;
	WaveMan() = delete;
	~WaveMan();

public:

	//----------------------------------------------------------------------
	// Static Methods
	//----------------------------------------------------------------------

	static void Create(int reserveNum = 3, int reserveGrow = 1);
	static void Destroy();

	static Wave* Add(const char* const pWaveName, Wave::ID id, FileUserCallback* pFileUserCB = nullptr);
	static Wave* Find(Wave::ID id);

	static void Remove(Wave* pNode);
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
	static WaveMan* privGetInstance();

	//----------------------------------------------------------------------
	// Data - unique data for this manager 
	//----------------------------------------------------------------------
	static WaveMan* pInstance;
	Wave* poNodeCompare;
};

#endif

// --- End of File ---
