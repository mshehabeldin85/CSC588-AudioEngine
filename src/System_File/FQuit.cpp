//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "FQuit.h"
#include "FileMan.h"

FQuit::FQuit()
	:FCommand()
{
}

void FQuit::Execute()
{
	FileMan::SetQuit();
}

// --- End of File ---
