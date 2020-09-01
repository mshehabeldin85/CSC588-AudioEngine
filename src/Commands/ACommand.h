//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef A_COMMAND_H
#define	A_COMMAND_H

#include "Command.h"
#include "Snd.h"

class ACommand : public Command
{
public:
	ACommand(SndID id, Snd* pSnd);

protected:
	// Data: ------------------
	SndID id;
	Snd* pSnd;
};

#endif

// --- End of File ---
