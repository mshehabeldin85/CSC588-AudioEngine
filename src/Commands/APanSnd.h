//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef A_PAN_SND_H
#define	A_PAN_SND_H

#include "ACommand.h"
#include "Snd.h"

class APanSnd : public ACommand
{
public:
	APanSnd() = delete;
	APanSnd(const APanSnd&) = delete;
	APanSnd& operator = (const APanSnd&) = delete;
	~APanSnd() = default;

	APanSnd(SndID id, Snd* pSnd, float pan);

	virtual void Execute() override;

private:
	float pan;
};

#endif

// --- End of File ---
