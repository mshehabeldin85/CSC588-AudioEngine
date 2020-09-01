//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef A_STOP_SND_H
#define	A_STOP_SND_H

#include "ACommand.h"
#include "Snd.h"

class AStopSnd : public ACommand
{
public:
	AStopSnd() = delete;
	AStopSnd(const AStopSnd&) = delete;
	AStopSnd& operator = (const AStopSnd&) = delete;
	~AStopSnd() = default;

	AStopSnd(SndID id, Snd* pSnd);

	virtual void Execute() override;
};

#endif

// --- End of File ---
