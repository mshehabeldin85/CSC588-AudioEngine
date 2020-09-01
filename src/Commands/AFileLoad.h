//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef A_FILE_LOAD_H
#define A_FILE_LOAD_H

#include "FCommand.h"
#include "FileUserCallback.h"
#include "Wave.h"

class AFileLoad : public FCommand
{
public:
	AFileLoad() = delete;
	AFileLoad(const AFileLoad &) = delete;
	AFileLoad & operator = (const AFileLoad &) = delete;
	~AFileLoad() = default;

	AFileLoad(const char * const pWaveName, Wave::ID name, FileUserCallback *pFileCB = nullptr);

	virtual void Execute() override;

private:
	// data
	FileUserCallback	*pFileUserCallback;
	Wave::ID			waveID;
	const char * const	pWaveName;
};

#endif

// --- End of File ---
