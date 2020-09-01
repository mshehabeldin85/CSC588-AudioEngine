//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef CIRCULAR_INDEX_H
#define CIRCULAR_INDEX_H

class CircularIndex
{
public:
	CircularIndex(unsigned int buffSize) noexcept;
	CircularIndex() = delete;
	CircularIndex(const CircularIndex &) = delete;
	const CircularIndex &operator = (const CircularIndex &) = delete;
	~CircularIndex() = default;

	// postfix
	unsigned int operator++(int) noexcept;
	bool operator==(const CircularIndex &tmp) noexcept;
	bool operator!=(const CircularIndex &tmp) noexcept;

	unsigned int getIndex() const noexcept;


private:
	unsigned int index;
	unsigned int size;
	unsigned int mask;
};

#endif

// End of File 
