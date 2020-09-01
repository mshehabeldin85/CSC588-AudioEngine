//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef USER_CALLBACK_H
#define USER_CALLBACK_H

#include "Snd.h"

class UserCallback
{
public:

	UserCallback() = default;
	UserCallback(const UserCallback&) = delete;
	UserCallback& operator = (const UserCallback&) = delete;
	~UserCallback() = default;


	void Set(Snd* _pSnd, char* waveName, int TimeInMs);
	void Execute();


private:
	Snd* pSnd;
	char* pWaveName;
	int     TimeInMs;
};

#endif

// --- End of File ---