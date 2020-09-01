//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef A_CREATE_SND_H
#define	A_CREATE_SND_H

#include "ACommand.h"
#include "Snd.h"

class ACreateSnd : public ACommand
{
public:
	ACreateSnd() = delete;
	ACreateSnd(const ACreateSnd&) = delete;
	ACreateSnd& operator = (const ACreateSnd&) = delete;
	~ACreateSnd() = default;

	ACreateSnd(SndID id, Snd* pSnd, UserCallback* pUserCallback = nullptr);

	virtual void Execute() override;

private:
	// data
	UserCallback* pUserCallback;
};

#endif

// --- End of File ---
