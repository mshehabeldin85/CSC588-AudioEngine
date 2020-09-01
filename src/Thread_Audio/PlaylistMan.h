//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef PLAYLIST_MAN_H
#define PLAYLIST_MAN_H

#include "Manager.h"
#include "Voice.h"
#include "Playlist.h"

// This class is only there for pretty UML
class PlaylistMan_MLink : public Manager
{
public:
	Playlist_Link* poActive;
	Playlist_Link* poReserve;
};

class PlaylistMan : public PlaylistMan_MLink
{
	//----------------------------------------------------------------------
	// Big four
	//----------------------------------------------------------------------
private:
	PlaylistMan(int reserveNum = 3, int reserveGrow = 1);
	PlaylistMan(const PlaylistMan&) = delete;
	PlaylistMan& operator = (const PlaylistMan&) = delete;
	PlaylistMan() = delete;
	~PlaylistMan();

public:

	//----------------------------------------------------------------------
	// Static Methods
	//----------------------------------------------------------------------
	static void Create(int reserveNum = 3, int reserveGrow = 1);
	static void Destroy();

	static Playlist* Add(SndID snd_id);
	static Playlist* Find(SndID id);

	static void Remove(Playlist * pNode);
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
	static PlaylistMan* privGetInstance();

	//----------------------------------------------------------------------
	// Data - unique data for this manager 
	//----------------------------------------------------------------------
	static PlaylistMan* pInstance;
	Playlist* poNodeCompare;
};

#endif

// --- End of File ---
