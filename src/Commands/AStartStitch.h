//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef A_START_STITCHING_H
#define	A_START_STITCHING_H

#include "ACommand.h"
#include "Snd.h"

class AStartStitch : public ACommand
{
public:
	AStartStitch() = delete;
	AStartStitch(const AStartStitch &) = delete;
	AStartStitch& operator = (const AStartStitch &) = delete;
	~AStartStitch() = default;

	AStartStitch(SndID id, Snd* pSnd);

	virtual void Execute() override;

	float vol;
};

#endif

// --- End of File ---
