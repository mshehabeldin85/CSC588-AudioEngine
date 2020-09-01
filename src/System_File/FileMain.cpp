//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "FileMain.h"
#include "FileMan.h"
#include "ThreadHelper.h"


//-------------------------------------------------------------
// Audio thread main (loop)
//-------------------------------------------------------------
void FileMain()
{
	ThreadHelper::DebugBegin(1);

	while (!FileMan::IsQuit())
	{
		Command* pCmd = nullptr;

		// Any commands to process?
		if (FileMan::GetFileInQueue()->PopFront(pCmd) == true)
		{
			assert(pCmd);
			pCmd->Execute();

			// Commands are instantly killed after execution
			delete pCmd;
		}
	}

	ThreadHelper::DebugEnd(1);
}

// --- End of File ---