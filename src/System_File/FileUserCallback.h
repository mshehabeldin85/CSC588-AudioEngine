//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef File_USER_CALLBACK_H
#define File_USER_CALLBACK_H

#include "SndID.h"

class FileUserCallback
{
public:

	FileUserCallback() = default;
	FileUserCallback(const FileUserCallback &) = delete;
	FileUserCallback & operator = (const FileUserCallback &) = delete;
	~FileUserCallback() = default;

	void Set(SndID sndID);
	void SetStopSnd(SndID sndID);
	void Execute();


private:
	SndID sndID;
	SndID stopSndID;
};



#endif

// --- End of File ---
