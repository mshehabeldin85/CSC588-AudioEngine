//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Snd.h"
#include "PlaylistMan.h"
#include "SndMan.h"
#include "TimeEventMan.h"
#include "APlaySnd.h"
#include "AStopSnd.h"
#include "AVolSnd.h"
#include "APanSnd.h"
#include "AStartStitch.h"
#include "AStopSnd.h"
#include "ASndEnd.h"

// Static store
SndPriorityEntry  Snd::sndPriorityTable[Snd::SND_PRIORITY_TABLE_SIZE];
Handle	          Snd::table_handle;

Snd::Snd()
	: id(SndID::Uninitialized),
	pASnd(nullptr),
	vol(0.7f),
	pan(0.0f),
	handle(),
	priority(0),
	sndEnded(false)
{
}

Handle::Status Snd::RemoveFromPriorityTable()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		bool status = false;

		for (unsigned int i = 0; i < Snd::SND_PRIORITY_TABLE_SIZE; i++)
		{
			if (Snd::sndPriorityTable[i].handleID == this->handle.GetID())
			{
				Snd::sndPriorityTable[i].Clear();
				status = true;
				break;
			}
		}
	}
	else
	{
		assert(false);
	}
	return lock;
}

void Snd::PrintPriorityTable()
{

	Trace::out("---------------------------------\n");
	Trace::out(" Snd Priority Table \n");
	Trace::out("---------------------------------\n");
	for (unsigned int i = 0; i < Snd::SND_PRIORITY_TABLE_SIZE; i++)
	{
		if (Snd::sndPriorityTable[i].priority != -1)
		{
			Time delta = (TimeEventMan::GetTimeCurrent()) - sndPriorityTable[i].startTime;

			Trace::out("handle: 0x%x SndID: %d priority:%4d  time: %d ms\n",
				sndPriorityTable[i].handleID,
				sndPriorityTable[i].sndID,
				sndPriorityTable[i].priority,
				Time::quotient(delta, Time(Duration::TIME_ONE_MILLISECOND)));
		}
		else
		{

			Trace::out("handle: 0x-------- SndID: --- priority: ---  time: --- \n");
		}
	}

	Trace::out("---------------------------------\n");
}

void Snd::proSetASnd(ASnd* p)
{
	// OK to set it to nullptr in a end of sound
	this->pASnd = p;
}

void Snd::proGetASnd(ASnd*& p)
{
	p = this->pASnd;
}

void Snd::SetSoundEnded()
{
	this->sndEnded = true;
}

bool Snd::GetSoundEnded()
{
	return this->sndEnded;
}

XAUDIO2_BUFFER_ALIAS* Snd::GetVoiceBuffer()
{
	return this->pASnd->GetVoiceBuffer();
}

Handle::Status Snd::Play()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		Handle::Lock tableLock(this->table_handle);
		if (tableLock)
		{
			if (this->privUseOpenSlotInTable())
			{
				// Easy take a slot

				// Place the Play command in the queue to the Audio thread
				CircularData* pOut = SndMan::GetAudioInQueue();
				assert(pOut);

				Command* pCmd = new APlaySnd(this->id, this);
				assert(pCmd);

				pOut->PushBack(pCmd);
			}
			else
			{
				// No - Slots
				// Can I preempt the sound?
				// To DO
			}
		}
		else
		{
			assert(false);
		}
	}
	else
	{
		assert(false);
	}
	return lock;
}

bool Snd::privUseOpenSlotInTable()
{
	bool status = false;

	// SLOPPY - HACK 

	// Find open slot?
	for (unsigned int i = 0; i < Snd::SND_PRIORITY_TABLE_SIZE; i++)
	{
		if (sndPriorityTable[i].priority == -1)
		{
			sndPriorityTable[i].priority = this->priority;
			sndPriorityTable[i].sndID = this->id;
			sndPriorityTable[i].handleID = this->handle.GetID();
			sndPriorityTable[i].startTime = TimeEventMan::GetTimeCurrent();

			// Found one
			status = true;
			break;
		}
	}

	// if the table is full
	if (status == false)
	{
		int countSamePriority = 0;
		int samePrioritystartIdx = 0;
		int minPrioritystartIdx = 0;

		// Get the first matching priority
		for (unsigned int i = 0; i < Snd::SND_PRIORITY_TABLE_SIZE; i++)
		{
			if (sndPriorityTable[i].priority == this->priority)
			{
				countSamePriority++;
				samePrioritystartIdx = i;
				minPrioritystartIdx = i;
			}
		}

		// Update the minimum time record
		Time minTime = sndPriorityTable[samePrioritystartIdx].startTime;
		if (countSamePriority > 1)			// Multiple priority records
		{
			for (unsigned int i = 0; i < Snd::SND_PRIORITY_TABLE_SIZE; i++)
			{
				if (sndPriorityTable[i].priority == this->priority && sndPriorityTable[i].startTime < minTime)
				{
					minTime = sndPriorityTable[i].startTime;
					minPrioritystartIdx = i;
				}
			}
		}
		else if (countSamePriority == 0)		// No records of the same priority
		{
			for (unsigned int i = 0; i < Snd::SND_PRIORITY_TABLE_SIZE; i++)
			{
				if (sndPriorityTable[i].startTime < minTime)
				{
					minTime = sndPriorityTable[i].startTime;
					minPrioritystartIdx = i;
				}
			}
		}

		// kill the replaced sound
		Snd* killSnd = SndMan::Find(sndPriorityTable[minPrioritystartIdx].sndID);
		assert(killSnd);
		killSnd->End();

		// update the record data with the new sound
		sndPriorityTable[minPrioritystartIdx].priority = this->priority;
		sndPriorityTable[minPrioritystartIdx].sndID = this->id;
		sndPriorityTable[minPrioritystartIdx].handleID = this->handle.GetID();
		sndPriorityTable[minPrioritystartIdx].startTime = TimeEventMan::GetTimeCurrent();

		status = true;
	}

	return status;
}

Handle::Status Snd::Stop()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		// Place the Play command in the queue to the Audio thread
		CircularData* pOut = SndMan::GetAudioInQueue();
		assert(pOut);

		Command* pCmd = new AStopSnd(this->id, this);
		assert(pCmd);

		pOut->PushBack(pCmd);

	}
	else
	{
		assert(false);
	}
	return lock;
}

Handle::Status Snd::End()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		// Place the Play command in the queue to the Audio thread
		CircularData* pOut = SndMan::GetAudioInQueue();
		assert(pOut);

		Command* pCmd = new ASndEnd(this->id, this);
		assert(pCmd);

		pOut->PushBack(pCmd);

	}
	else
	{
		assert(false);
	}
	return lock;
}

Handle::Status Snd::Vol(float snd_vol)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		this->vol = snd_vol;

		// Place the Vol command in the queue to the Audio thread
		CircularData* pOut = SndMan::GetAudioInQueue();
		assert(pOut);

		Command* pCmd = new AVolSnd(this->id, this, this->vol);
		assert(pCmd);

		pOut->PushBack(pCmd);

	}
	return lock;
}

Handle::Status Snd::Pan(float snd_pan)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		this->pan = snd_pan;

		// Place the Play command in the queue to the Audio thread
		CircularData* pOut = SndMan::GetAudioInQueue();
		assert(pOut);

		Command* pCmd = new APanSnd(this->id, this, this->pan);
		assert(pCmd);

		pOut->PushBack(pCmd);
	}
	return lock;
}

Handle::Status Snd::StartStitching()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		// Place the Play command in the queue to the Audio thread
		CircularData* pOut = SndMan::GetAudioInQueue();
		assert(pOut);

		Command* pCmd = new AStartStitch(this->id, this);
		assert(pCmd);

		pOut->PushBack(pCmd);
	}
	return lock;
}

Handle::Status Snd::GetTimeInMS(int& timeInMS)
{
	Handle::Lock lock(this->handle);

	if (lock)
	{
		// table lock
		Handle::Lock tableLock(this->table_handle);

		// Check Priority table
		if (tableLock)
		{
			bool status = false;
			for (unsigned int i = 0; i < Snd::SND_PRIORITY_TABLE_SIZE; i++)
			{
				if (Snd::sndPriorityTable[i].handleID == this->handle.GetID())
				{
					Time delta = (TimeEventMan::GetTimeCurrent()) - sndPriorityTable[i].startTime;

					timeInMS = Time::quotient(delta, Time(Duration::TIME_ONE_MILLISECOND));

					status = true;
					break;
				}
			}

			if (!status)
			{
				assert(false);
			}
		}
		else
		{
			assert(false);
		}
	}

	return lock;
}


Handle::Status Snd::GetVol(float& snd_vol)
{
	Handle::Lock lock(handle);

	if (lock)
	{
		//	Trace::out("Snd::GetVol() lock \n");
		snd_vol = this->vol;

	}
	else
	{
		assert(false);
	}

	//Trace::out("Snd::GetVol() unlock \n");
	return lock;
}

Handle::Status Snd::GetPan(float& snd_pan)
{
	Handle::Lock lock(handle);

	if (lock)
	{
		//	Trace::out("Snd::GetPan() lock \n");
		snd_pan = this->pan;

	}
	else
	{
		assert(false);
	}

	//Trace::out("Snd::GetPan() unlock \n");
	return lock;
}

Handle::Status Snd::SetID(SndID snd_id)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		this->id = snd_id;
	}
	return lock;
}

Handle::Status Snd::GetID(SndID& snd_id)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		snd_id = this->id;
	}
	return lock;
}

Handle::Status Snd::Wash()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		// Wash - clear the entire hierarchy
		DLink::Clear();

		// Sub class clear
		this->privClear();
	}
	return lock;
}

//Handle::Status  Snd::Set(SndID snd_id)
Handle::Status  Snd::Set(SndID snd_id, SndPriority snd_priority)
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		this->id = snd_id;
		this->priority = snd_priority;
	}
	return lock;
}

void Snd::privClear()
{
	this->id = SndID::Uninitialized;

}

Handle::Status Snd::Dump()
{
	Handle::Lock lock(this->handle);
	if (lock)
	{
		SndID _id;
		this->GetID(_id);
		// Dump - Print contents to the debug output window
		//Trace::out("   Name: %d (%p) \n", _id, this);
		Trace::out("   SndName: SndID:%d (%p) priority:%d vol:%f pan:%f \n", _id, this, this->priority, this->vol, this->pan);
	}
	return lock;
}

Snd::~Snd()
{
	// Kill the Handle
	// Gets automagically killed by the ~Handle()

	// check "this" and input
	assert(Handle::ValidateHandle(this->handle) == Handle::Status::SUCCESS);
}

// --- End of File  ---
