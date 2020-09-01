//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef A_SND_END_H
#define	A_SND_END_H

#include "ACommand.h"
#include "Snd.h"

class ASndEnd : public ACommand
{
public:
	ASndEnd() = delete;
	ASndEnd(const ASndEnd&) = delete;
	ASndEnd& operator = (const ASndEnd&) = delete;
	~ASndEnd() = default;

	ASndEnd(SndID id, Snd* pSnd);

	virtual void Execute() override;
};

#endif

// --- End of File ---
