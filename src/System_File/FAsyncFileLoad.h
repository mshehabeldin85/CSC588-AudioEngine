//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef F_FILE_LOAD_H
#define F_FILE_LOAD_H

#include "FCommand.h"
#include "FileUserCallback.h"
#include "Wave.h"

class FAsyncFileLoad : public FCommand
{
public:
	FAsyncFileLoad() = delete;
	FAsyncFileLoad(const FAsyncFileLoad&) = delete;
	FAsyncFileLoad& operator = (const FAsyncFileLoad&) = delete;
	~FAsyncFileLoad() = default;

	FAsyncFileLoad(const char* const pWaveName, Wave::ID name);

	virtual void Execute() override;

private:
	void privLoadBuffer(const char* const pWaveName, WAVEFORMATEXTENSIBLE*& pWfx, RawData*& pRawBuff, unsigned int RawBuffSize);
	unsigned int privGetBuffSize(const char* const pWaveName);


private:
	// data
	Wave::ID			waveID;
	const char* const	pWaveName;
};

#endif

// --- End of File ---
