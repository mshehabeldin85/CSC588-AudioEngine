//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef G_FILE_USER_CALLBACK_H
#define G_FILE_USER_CALLBACK_H

#include "GCommand.h"
#include "Wave.h"

class GFileUserCallback : public GCommand
{
public:
	GFileUserCallback() = delete;
	GFileUserCallback(const GFileUserCallback&) = delete;
	GFileUserCallback& operator = (const GFileUserCallback&) = delete;
	~GFileUserCallback() = default;

	GFileUserCallback(Wave::ID name, FileUserCallback* pFileCB);

	virtual void Execute() override;

private:
	// data
	FileUserCallback* pFileCB;
	Wave::ID wave_id;
};

#endif

// --- End of File ---
