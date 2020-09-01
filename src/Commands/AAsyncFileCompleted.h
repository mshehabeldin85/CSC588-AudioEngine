//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef A_ASYNC_FILE_COMPLETED_H
#define A_ASYNC_FILE_COMPLETED_H

#include "FCommand.h"
#include "FileUserCallback.h"
#include "Wave.h"

class AAsyncFileCompleted : public FCommand
{
public:
	AAsyncFileCompleted() = delete;
	AAsyncFileCompleted(const AAsyncFileCompleted&) = delete;
	AAsyncFileCompleted& operator = (const AAsyncFileCompleted&) = delete;
	~AAsyncFileCompleted() = default;

	AAsyncFileCompleted(Wave::ID waveID, WAVEFORMATEXTENSIBLE* pWfx, unsigned int rawBuffSize,	RawData* pRawBuff);

	virtual void Execute() override;

private:
	// data
	Wave::ID			waveID;
	WAVEFORMATEXTENSIBLE* pWfx;
	unsigned int rawBuffSize;
	RawData* pRawBuff;
};

#endif

// --- End of File ---