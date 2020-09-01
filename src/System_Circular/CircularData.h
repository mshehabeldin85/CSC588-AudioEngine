//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef CIRCULAR_DATA_H
#define CIRCULAR_DATA_H

#include "CircularIndex.h"
#include "Command.h"
#include <mutex>

class CircularData
{
public:
	// needs to be a power of 2
	static const int CIRCULAR_DATA_SIZE = 64;

public:
	CircularData() noexcept;
	
	CircularData(const CircularData &) = delete;
	CircularData &operator = (const CircularData &) = delete;
	CircularData(CircularData&&) = delete;
	CircularData& operator = (CircularData&&) = delete;
	~CircularData();

	bool PushBack(Command* pCmd);
	bool PopFront(Command*& pCmd);
	void Disable();

private:
	
	Command* data[CIRCULAR_DATA_SIZE];

	CircularIndex front;
	CircularIndex back;
	bool empty;
	bool full;
	bool enable;
	std::mutex mtx;

};

#endif

// End of File 
