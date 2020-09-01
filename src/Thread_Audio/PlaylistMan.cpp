//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "PlaylistMan.h"
#include "VoiceMan.h"
#include "WaveMan.h"

PlaylistMan* PlaylistMan::pInstance = nullptr;

//---------------------------------------------------------------------------------------------------------
// Design Notes:
//
//  Singleton class - use only public static methods for customers
//
//  * One single compare node is owned by this singleton - used for find, prevent extra news
//  * Create one - NULL Object 
//
//---------------------------------------------------------------------------------------------------------

PlaylistMan::PlaylistMan(int reserveNum, int reserveGrow)
//	: Manager() // <--- Kick the can (delegate)
{
	// At this point Man is created, now initialize the reserve
	this->BaseInitialize(reserveNum, reserveGrow);

	// initialize derived data here
	this->poNodeCompare = new Playlist();
	assert(this->poNodeCompare != nullptr);
}

PlaylistMan::~PlaylistMan()
{
	// We created it... so we delete it
	delete this->poNodeCompare;

	//Trace::out("---> ~PlaylistMan()\n");

	// Next stop - base class
}

//----------------------------------------------------------------------
// Static Methods
//----------------------------------------------------------------------
void PlaylistMan::Create(int reserveNum, int reserveGrow)
{
	// make sure values are ressonable 
	assert(reserveNum > 0);
	assert(reserveGrow > 0);

	// initialize the singleton here
	assert(pInstance == nullptr);

	// Do the initialization
	if (pInstance == nullptr)
	{
		pInstance = new PlaylistMan(reserveNum, reserveGrow);
	}

}

void PlaylistMan::Destroy()
{
	//Trace::out("\n");
	//Trace::out("---- Destroy() ----\n");

	// Get the instance
	PlaylistMan* pMan = PlaylistMan::privGetInstance();
	assert(pMan != nullptr);

	// Clean up what it current owns reserve and active
	pMan->BaseDestroy();

	// bye bye singleton
	delete pMan->pInstance;
}

Playlist* PlaylistMan::Add(SndID snd_id)
{
	PlaylistMan* pMan = PlaylistMan::privGetInstance();
	assert(pMan != nullptr);

	Playlist * pNode = (Playlist *)pMan->BaseAdd();
	assert(pNode != nullptr);

	// Create a new one given a wash
	switch (snd_id)
	{
	// Demo #1
	case SndID::Fiddle:
		pNode->Set(snd_id, Voice::ID::Fiddle, Wave::ID::Fiddle);
		break;

	case SndID::Bassoon:
		pNode->Set(snd_id, Voice::ID::Bassoon, Wave::ID::Bassoon);
		break;

	case SndID::Oboe2:
		pNode->Set(snd_id, Voice::ID::Oboe, Wave::ID::Oboe);
		break;

	case SndID::SongA:
		pNode->Set(snd_id, Voice::ID::SongA, Wave::ID::SongA);
		break;

	case SndID::SongB:
		pNode->Set(snd_id, Voice::ID::SongB, Wave::ID::SongB);
		break;

	// Demo #2
	case SndID::Intro_mono:
		pNode->Set(snd_id, Voice::ID::Intro_mono, Wave::ID::Intro_mono);
		break;

	case SndID::A_mono:
		pNode->Set(snd_id, Voice::ID::A_mono, Wave::ID::A_mono);
		break;

	case SndID::AtoB_mono:
		pNode->Set(snd_id, Voice::ID::AtoB_mono, Wave::ID::AtoB_mono);
		break;

	case SndID::B_mono:
		pNode->Set(snd_id, Voice::ID::B_mono, Wave::ID::B_mono);
		break;

	case SndID::BtoC_mono:
		pNode->Set(snd_id, Voice::ID::BtoC_mono, Wave::ID::BtoC_mono);
		break;

	case SndID::C_mono:
		pNode->Set(snd_id, Voice::ID::C_mono, Wave::ID::C_mono);
		break;

	case SndID::CtoA_mono:
		pNode->Set(snd_id, Voice::ID::CtoA_mono, Wave::ID::CtoA_mono);
		break;

	case SndID::End_mono:
		pNode->Set(snd_id, Voice::ID::End_mono, Wave::ID::End_mono);
		break;

	// Demo #3
	case SndID::Coma:
		pNode->Set(snd_id, Voice::ID::Coma, Wave::ID::Coma);
		break;

	case SndID::Quit:
		assert(false);
		break;

	// Demo #4
	case SndID::Dial:
		pNode->Set(snd_id, Voice::ID::Dial, Wave::ID::Dial);
		break;

	case SndID::MoonPatrol:
		pNode->Set(snd_id, Voice::ID::MoonPatrol, Wave::ID::MoonPatrol);
		break;

	case SndID::Sequence:
		pNode->Set(snd_id, Voice::ID::Sequence, Wave::ID::Sequence);
		break;

	case SndID::Donkey:
		pNode->Set(snd_id, Voice::ID::Donkey, Wave::ID::Donkey);
		break;

	// Demo #5
	case SndID::Electro:
		pNode->Set(snd_id, Voice::ID::Electro, Wave::ID::Electro);
		break;

	case SndID::Alarm:
		pNode->Set(snd_id, Voice::ID::Alarm, Wave::ID::Alarm);
		break;

	case SndID::Beethoven:
		pNode->Set(snd_id, Voice::ID::Beethoven, Wave::ID::Beethoven);
		break;

	case SndID::Uninitialized:
		assert(false);
		break;

	}

	return pNode;
}

Playlist* PlaylistMan::Find(SndID id)
{
	PlaylistMan* pMan = PlaylistMan::privGetInstance();
	assert(pMan != nullptr);

	// Compare functions only compares two Nodes

	// So:  Use the Compare Node - as a reference
	//      use in the Compare() function
	pMan->poNodeCompare->SetId(id);

	Playlist * pData = (Playlist*)pMan->BaseFind(pMan->poNodeCompare);
	return pData;
}

void PlaylistMan::Remove(Playlist* pNode)
{
	PlaylistMan* pMan = PlaylistMan::privGetInstance();
	assert(pMan != nullptr);

	assert(pNode != nullptr);
	pMan->BaseRemove(pNode);
}

void PlaylistMan::Dump()
{
	PlaylistMan* pMan = PlaylistMan::privGetInstance();
	assert(pMan != nullptr);

	pMan->BaseDump();
}

//----------------------------------------------------------------------
// Override Abstract methods
//----------------------------------------------------------------------
DLink* PlaylistMan::DerivedCreateNode()
{
	DLink* pNode = new Playlist();
	assert(pNode != nullptr);

	return pNode;
}

bool PlaylistMan::DerivedCompare(DLink* pLinkA, DLink* pLinkB)
{
	// This is used in baseFind() 
	assert(pLinkA != nullptr);
	assert(pLinkB != nullptr);

	Playlist* pDataA = (Playlist*)pLinkA;
	Playlist* pDataB = (Playlist*)pLinkB;

	bool status = false;

	SndID A;
	SndID B;

	if (pDataA->GetId(A) != Handle::Status::SUCCESS)
	{
		assert(false);
	}

	if (pDataB->GetId(B) != Handle::Status::SUCCESS)
	{
		assert(false);
	}

	if (A == B)
	{
		status = true;
	}

	return status;
}

void PlaylistMan::DerivedWash(DLink* pLink)
{
	assert(pLink != nullptr);
	Playlist* pNode = (Playlist*)pLink;
	pNode->Wash();
}

void PlaylistMan::DerivedDumpNode(DLink* pLink)
{
	assert(pLink != nullptr);
	Playlist* pData = (Playlist*)pLink;
	pData->Dump();
}

void PlaylistMan::DerivedDestroyNode(DLink* pLink)
{
	assert(pLink);
	Playlist* pData = (Playlist*)pLink;
	delete pData;
}


//----------------------------------------------------------------------
// Private methods
//----------------------------------------------------------------------
PlaylistMan* PlaylistMan::privGetInstance()
{
	// Safety - this forces users to call Create() first before using class
	assert(pInstance != nullptr);

	return pInstance;
}

// --- End of File ---
