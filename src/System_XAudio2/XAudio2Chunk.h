//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef XAUDIO2_CHUNK_H
#define XAUDIO2_CHUNK_H

#include "File_Slow.h"

enum class ChunkError
{
	SUCCESS = 0x0C000000,
	FAIL = 0x0CFFFFFF

};

ChunkError FindChunk(File_Slow::Handle hFile, DWORD fourcc, DWORD & dwChunkSize, DWORD & dwChunkDataPosition);
ChunkError ReadChunkData(File_Slow::Handle hFile, void * buffer, DWORD buffersize, DWORD bufferoffset);

#endif

// End of File 
 