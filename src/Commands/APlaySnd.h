//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef A_PLAY_SND_H
#define	A_PLAY_SND_H

#include "ACommand.h"
#include "Snd.h"

class APlaySnd : public ACommand
{
public:
	APlaySnd() = delete;
	APlaySnd(const APlaySnd&) = delete;
	APlaySnd& operator = (const APlaySnd&) = delete;
	~APlaySnd() = default;

	APlaySnd(SndID id, Snd* pSnd);

	virtual void Execute() override;
};

#endif

// --- End of File ---
