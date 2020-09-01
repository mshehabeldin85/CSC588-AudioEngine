//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "FAsyncFileLoad.h"
#include "ThreadHelper.h"
#include "SndMan.h"
#include "AAsyncFileCompleted.h"

FAsyncFileLoad::FAsyncFileLoad(const char* const _pWaveName, Wave::ID name)
	: waveID(name),
	pWaveName(_pWaveName)
{
}

void FAsyncFileLoad::Execute()
{
	Trace::out("%s FAsyncFileLoad: \n  waveID:%x,\n  wavename:%s \n", ThreadHelper::GetThreadName(), waveID, pWaveName);

	// Load the wfx
	// Load the RawBuffSize
	// Load the RawBuff

	WAVEFORMATEXTENSIBLE* pWfx;
	pWfx = new WAVEFORMATEXTENSIBLE();
	assert(pWfx);

	unsigned int rawBuffSize;
	rawBuffSize = this->privGetBuffSize(pWaveName);

	RawData* pRawBuff;
	pRawBuff = new RawData[rawBuffSize]();
	assert(pRawBuff);

	this->privLoadBuffer(pWaveName, pWfx, pRawBuff, rawBuffSize);

	// Completed Async load
	CircularData* pOut = SndMan::GetAudioInQueue();
	assert(pOut);

	Command* pCmd = new AAsyncFileCompleted(this->waveID, pWfx, rawBuffSize, pRawBuff);
	assert(pCmd);

	pOut->PushBack(pCmd);
}

unsigned int FAsyncFileLoad::privGetBuffSize(const char* const _pWaveName)
{
	assert(_pWaveName);
	WAVEFORMATEXTENSIBLE Wfx;

	//--------------------------------------------------------
	// zero out wfx and the buffer
	//--------------------------------------------------------

	Wfx = { 0 };    // zeros out the complete structure

	// -------------------------------------------------------
	// Open File
	// -------------------------------------------------------
	File_Slow::Error status;
	File_Slow::Handle fh;

	status = File_Slow::open(fh, _pWaveName, File_Slow::Mode::READ);
	assert(fh != 0);
	assert(status == File_Slow::Error::SUCCESS);

	// -------------------------------------------------------
	// Seek to Beginning of file
	// -------------------------------------------------------

	status = File_Slow::seek(fh, File_Slow::Seek::BEGIN, 0);
	assert(status == File_Slow::Error::SUCCESS);

	// -------------------------------------------------------
	// Find and load specific Chunks
	// -------------------------------------------------------

	DWORD dwChunkSize;
	DWORD dwChunkPosition;
	DWORD filetype;
	ChunkError cStatus;

	// Scan to the RIFF and load file type
	cStatus = FindChunk(fh, fourccRIFF, dwChunkSize, dwChunkPosition);
	assert(cStatus == ChunkError::SUCCESS);
	cStatus = ReadChunkData(fh, &filetype, sizeof(DWORD), dwChunkPosition);
	assert(cStatus == ChunkError::SUCCESS);

	// Make sure its not in the compressed format, WAVE format is uncompressed
	assert(filetype == fourccWAVE);

	// Read the FMT: format
	cStatus = FindChunk(fh, fourccFMT, dwChunkSize, dwChunkPosition);
	assert(cStatus == ChunkError::SUCCESS);
	cStatus = ReadChunkData(fh, &Wfx, dwChunkSize, dwChunkPosition);
	assert(cStatus == ChunkError::SUCCESS);

	// Scan to the DATA chunk, read the size, allocate buffer of that size
	cStatus = FindChunk(fh, fourccDATA, dwChunkSize, dwChunkPosition);
	assert(cStatus == ChunkError::SUCCESS);

	status = File_Slow::close(fh);
	assert(cStatus == ChunkError::SUCCESS);

	return dwChunkSize;
}

void FAsyncFileLoad::privLoadBuffer(const char* const _pWaveName, WAVEFORMATEXTENSIBLE*& pWfx, RawData*& pRawBuff, unsigned int RawBuffSize)
{
	assert(_pWaveName);
	assert(pRawBuff);
	assert(pWfx);

	//--------------------------------------------------------
	// zero out wfx and the buffer
	//--------------------------------------------------------

	*pWfx = { 0 };    // zeros out the complete structure

	// -------------------------------------------------------
	// Open File
	// -------------------------------------------------------

	File_Slow::Error status;
	File_Slow::Handle fh;

	status = File_Slow::open(fh, _pWaveName, File_Slow::Mode::READ);
	assert(fh != 0);
	assert(status == File_Slow::Error::SUCCESS);

	// -------------------------------------------------------
	// Seek to Beginning of file
	// -------------------------------------------------------

	status = File_Slow::seek(fh, File_Slow::Seek::BEGIN, 0);
	assert(status == File_Slow::Error::SUCCESS);

	// -------------------------------------------------------
	// Find and load specific Chunks
	// -------------------------------------------------------

	DWORD dwChunkSize;
	DWORD dwChunkPosition;
	DWORD filetype;
	ChunkError cStatus;

	// Scan to the RIFF and load file type
	cStatus = FindChunk(fh, fourccRIFF, dwChunkSize, dwChunkPosition);
	assert(cStatus == ChunkError::SUCCESS);

	cStatus = ReadChunkData(fh, &filetype, sizeof(DWORD), dwChunkPosition);
	assert(cStatus == ChunkError::SUCCESS);

	// Make sure its not in the compressed format, WAVE format is uncompressed
	assert(filetype == fourccWAVE);

	// Read the FMT: format
	cStatus = FindChunk(fh, fourccFMT, dwChunkSize, dwChunkPosition);
	assert(cStatus == ChunkError::SUCCESS);
	cStatus = ReadChunkData(fh, pWfx, dwChunkSize, dwChunkPosition);
	assert(cStatus == ChunkError::SUCCESS);

	// Scan to the DATA chunk, read the size, allocate buffer of that size
	cStatus = FindChunk(fh, fourccDATA, dwChunkSize, dwChunkPosition);
	assert(cStatus == ChunkError::SUCCESS);
	assert(dwChunkSize == RawBuffSize);
	assert(pRawBuff);

	// Fill the data...
	cStatus = ReadChunkData(fh, pRawBuff, dwChunkSize, dwChunkPosition);
	assert(cStatus == ChunkError::SUCCESS);

	// Close File
	status = File_Slow::close(fh);
	assert(cStatus == ChunkError::SUCCESS);
}


// --- End of File ---