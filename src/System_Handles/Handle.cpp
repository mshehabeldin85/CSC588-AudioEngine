//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "HandleMan.h"
#include "Handle.h"

// --------------------------------------------------
// Handle
// --------------------------------------------------

Handle::Handle()
{
	//Activate
	const Status status = HandleMan::ActivateHandle(this->id, this->index);
	assert(status == Status::SUCCESS);

	//Trace::out("Handle(): new handle(%x):0x%X\n", this->index, this->id);
}

Handle::~Handle()
{
	// Invalidate handle;
	HandleMan::InvalidateHandle(*this);

	//Trace::out("~Handle(): invalidate handle(%x):0x%X\n", this->index, this->id);
}

Handle::ID Handle::GetID() const
{
	return this->id;
}

Handle::Index Handle::GetIndex() const
{
	return this->index;
}

//---------------------------------------------------------------
// Tunneling... I only want handle.h to be used
//---------------------------------------------------------------
Handle::Status Handle::ValidateHandle(const Handle &handle)
{
	return HandleMan::ValidateHandle(handle);
}

Handle::Status Handle::InvalidateHandle(const Handle &handle)
{
	return HandleMan::InvalidateHandle(handle);
}

Handle::Status Handle::AquireResource(const Handle &handle)
{
	return HandleMan::AquireResource(handle);
}

Handle::Status Handle::ReleaseResource(const Handle &handle)
{
	return HandleMan::ReleaseResource(handle);
}


// ---  End of File ---------------
