//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef ASND_MAN_H
#define ASND_MAN_H

#include "Manager.h"
#include "SndID.h"
#include "ASnd.h"

// This class is only there for pretty UML
class ASndMan_MLink : public Manager
{
public:
	ASnd_Link* poActive;
	ASnd_Link* poReserve;
};

class ASndMan : public ASndMan_MLink
{
	//----------------------------------------------------------------------
	// Big four
	//----------------------------------------------------------------------
private:
	ASndMan(int reserveNum = 3, int reserveGrow = 1);
	ASndMan(const ASndMan&) = delete;
	ASndMan& operator = (const ASndMan&) = delete;
	ASndMan() = delete;
	~ASndMan();

public:

	//----------------------------------------------------------------------
	// Static Methods
	//----------------------------------------------------------------------
	static void Create(int reserveNum = 3, int reserveGrow = 1);
	static void Destroy();

	static ASnd* Add(SndID snd_id);
	static ASnd* Find(SndID id);

	static void  SetQuit();
	static bool  IsQuit();

	static void Remove(ASnd* pNode);
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
	static ASndMan* privGetInstance();

	//----------------------------------------------------------------------
	// Data - unique data for this manager 
	//----------------------------------------------------------------------
	static ASndMan* pInstance;
	ASnd* poNodeCompare;

	bool QuitFlag;
};

#endif

// --- End of File ---
