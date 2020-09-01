//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "CircularIndex.h"

CircularIndex::CircularIndex(unsigned int buffSize) noexcept
{
	// need an assert to verify that buffSize is a power of 2
	this->size = buffSize;
	this->mask = buffSize - 1;
	this->index = 0;
}

// postfix
unsigned int CircularIndex::operator++(int)  noexcept
{
	this->index++;

	// Circular 
	this->index = this->index & this->mask;

	return this->index;
}

bool CircularIndex::operator==(const CircularIndex &tmp) noexcept
{
	assert(this->size == tmp.size);
	return (this->index == tmp.index);
}

bool CircularIndex::operator!=(const CircularIndex &tmp) noexcept
{
	assert(this->size == tmp.size);
	return (this->index != tmp.index);
}

unsigned int CircularIndex::getIndex() const noexcept
{
	return this->index;
}

// End of File 
