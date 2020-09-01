//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef F_QUIT_H
#define	F_QUIT_H

#include "FCommand.h"

class FQuit : public FCommand
{
public:

	FQuit(const FQuit&) = delete;
	FQuit& operator = (const FQuit&) = delete;
	~FQuit() = default;

	FQuit();

	virtual void Execute() override;
};

#endif

// --- End of File ---
