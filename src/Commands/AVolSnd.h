//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef A_VOL_SND_H
#define	A_VOL_SND_H

#include "ACommand.h"
#include "Snd.h"

class AVolSnd : public ACommand
{
public:
	AVolSnd() = delete;
	AVolSnd(const AVolSnd&) = delete;
	AVolSnd& operator = (const AVolSnd&) = delete;
	~AVolSnd() = default;

	AVolSnd(SndID id, Snd* pSnd, float vol);

	virtual void Execute() override;

private:
	float vol;
};

#endif

// --- End of File ---
