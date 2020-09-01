//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef A_QUIT_H
#define	A_QUIT_H

#include "ACommand.h"
#include "Snd.h"

class AQuit : public ACommand
{
public:
	AQuit() = delete;
	AQuit(const AQuit&) = delete;
	AQuit& operator = (const AQuit&) = delete;
	~AQuit() = default;

	AQuit(SndID id, Snd* pSnd);

	virtual void Execute() override;
};

#endif

// --- End of File ---
