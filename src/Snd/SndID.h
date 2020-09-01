//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SND_ID_H
#define SND_ID_H

enum class SndID
{
	Fiddle		= 101,
	Bassoon		= 102,
	Oboe2		= 103,
	SongA		= 104,
	SongB		= 105,

	Intro_mono	= 201,
	A_mono		= 202,
	AtoB_mono	= 203,
	B_mono		= 204,
	BtoC_mono	= 205,
	C_mono		= 206,
	CtoA_mono	= 207,
	End_mono	= 208,

	Coma		= 301,

	Dial		= 401,
	MoonPatrol	= 402,
	Sequence	= 403,
	Donkey		= 404,

	Electro		= 501,
	Alarm		= 502,
	Beethoven	= 503,

	Quit,
	Uninitialized = 0x7FFF0000
};

#endif

// --- End of File ---
