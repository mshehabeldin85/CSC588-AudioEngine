//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Keyboard.h"
#include "InputProcess.h"
#include "ASndMan.h"
#include "Demo1.h"
#include "Demo2.h"
#include "Demo3.h"
#include "Demo4.h"
#include "Demo5.h"


static bool Key_1_State = false;
static bool Key_2_State = false;
static bool Key_3_State = false;
static bool Key_4_State = false;
static bool Key_5_State = false;

static bool Key_T_State = false;
static bool Key_M_State = false;

void InputProcess()
{
	Keyboard *pKey = Keyboard::GetInstance();
	assert(pKey);

	// Hit the "1" key to start Demo #1
	if ( pKey->GetKeyState(AZUL_KEY::KEY_1) && (Key_1_State == false))
	{
		// avoid a double throw of the key
		Key_1_State = true;
		Demo1();
	}

	// Hit the "2" key to start Demo #2
	if (pKey->GetKeyState(AZUL_KEY::KEY_2) && (Key_2_State == false))
	{
		// avoid a double throw of the key
		Key_2_State = true;
		Demo2();
	}

	// Hit the "3" key to start Demo #3
	if (pKey->GetKeyState(AZUL_KEY::KEY_3) && (Key_3_State == false))
	{
		// avoid a double throw of the key
		Key_3_State = true;
		Demo3();
	}

	// Hit the "4" key to start Demo #4
	if (pKey->GetKeyState(AZUL_KEY::KEY_4) && (Key_4_State == false))
	{
		// avoid a double throw of the key
		Key_4_State = true;
		Demo4();
	}

	// Hit the "5" key to start Demo #5
	if (pKey->GetKeyState(AZUL_KEY::KEY_5) && (Key_5_State == false))
	{
		// avoid a double throw of the key
		Key_5_State = true;
		Demo5();
	}



	// Hit the "T" key to start
	if (pKey->GetKeyState(AZUL_KEY::KEY_T) && (Key_T_State == false))
	{
		// avoid a double throw of the key
		Key_T_State = true;
		Snd::PrintPriorityTable();
	}

	if (!pKey->GetKeyState(AZUL_KEY::KEY_T) && (Key_T_State == true))
	{
		// avoid a double throw of the key
		Key_T_State = false;

	}

	// Hit the "M" key to start
	if (pKey->GetKeyState(AZUL_KEY::KEY_M) && (Key_M_State == false))
	{
		// avoid a double throw of the key
		Key_M_State = true;
		Trace::out("\nASnd Man: ");
		ASndMan::Dump();

		Trace::out("\nSnd Man:");
		SndMan::Dump();
	}

	if (!pKey->GetKeyState(AZUL_KEY::KEY_M))
	{
		// avoid a double throw of the key
		Key_M_State = false;
	}

}


// --- End of File ---
