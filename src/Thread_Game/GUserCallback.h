//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef G_USER_CALLBACK_H
#define G_USER_CALLBACK_H

#include "GCommand.h"
#include "UserCallBack.h"

class GUserCallback : public GCommand
{
public:
	GUserCallback() = delete;
	GUserCallback(const GUserCallback&) = delete;
	GUserCallback& operator = (const GUserCallback&) = delete;
	~GUserCallback() = default;

	GUserCallback(UserCallback* pUserCB);

	virtual void Execute() override;

private:
	UserCallback* pUserCB;

};

#endif

// --- End of File ---
