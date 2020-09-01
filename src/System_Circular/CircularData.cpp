//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "CircularData.h"
#include "ASndMan.h"

CircularData::CircularData() noexcept
	: front(CIRCULAR_DATA_SIZE),
	back(CIRCULAR_DATA_SIZE),
	empty(true),
	full(false),
	enable(true)
{
	// initialized data
	for (int i = 0; i < CIRCULAR_DATA_SIZE; i++)
	{
		this->data[i] = 0;
	}
}

CircularData::~CircularData()
{
	// Audio thread is calling pop
	// ---> need to stop AudioMain() or FileMain() first

	// If a Quit command is in queue AND another command is following
	// the following command will not get executed, but it will leak
	// so clear the queue and delete it.

	// Any commands to delete
	Command* pCmd = nullptr;
	while(this->PopFront(pCmd) == true)
	{
		assert(pCmd);
		delete pCmd;
	}

}

bool CircularData::PushBack(Command *val)
{	
	bool status = false;
	
	std::lock_guard<std::mutex> lock(this->mtx);

	// Do we have space to add?
	if (this->front != this->back || this->empty)
	{
		// add data
		this->data[this->back.getIndex()] = val;
		this->back++;

		this->empty = false;

		// check if this add made it full
		if (this->front == this->back)
		{
			this->full = true;
		}

		status = true;
	}
	else
	{
		status = false;
	}

	return status;
}

bool CircularData::PopFront(Command*& val)
{
	bool status = false;

	std::lock_guard<std::mutex> lock(this->mtx);

	// Is there data to process?
	if (this->front != this->back || this->full)
	{
		// Grab one
		val = this->data[this->front.getIndex()];
		this->front++;

		this->full = false;

		// check if this Pop made it Empty
		if (this->front == this->back)
		{
			this->empty = true;
		}

		status = true;
	}
	else
	{
		status = false;
	}

	return status;
}

// End of File 
