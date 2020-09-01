//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------
#include "AzulCore.h"
#include "Game.h"
#include "GameApp.h"
#include "InputTest.h"

// Sound Manager
#include "SndMan.h"
#include "Snd.h"

// Thread stuff
#include <thread>
#include "ThreadHelper.h"
#include "AudioMain.h"
#include "CircularData.h"
   
// Timer
#include "Timer.h"

// File Slow
#include "File_Slow.h"

// Audio
#include "SndMan.h"
#include "AudioMain.h"
#include "VoiceMan.h"
#include "WaveMan.h"
#include "PlaylistMan.h"
#include "ASndMan.h"

// Game Side
#include "TimeEventMan.h"
#include "InputProcess.h"

// File
#include "FileMan.h"
#include "FileMain.h"


//-----------------------------------------------------------------------------
// Game::Initialize()
//		Allows the engine to perform any initialization it needs to before 
//      starting to run.  This is where it can query for any required services 
//      and load any non-graphic related content. 
//-----------------------------------------------------------------------------
void Game::Initialize()
{ 
	// Game Window Device setup
	this->setWindowName("Audio Engine");
	this->setWidthHeight(400, 300);
	this->SetClearColor(0.74f, 0.74f, 0.86f, 1.0f);
}

//-----------------------------------------------------------------------------
// Game::LoadContent()
//		Allows you to load all content needed for your engine,
//	    such as objects, graphics, etc.
//-----------------------------------------------------------------------------
void Game::LoadContent()
{	
	glDisable(GL_DEBUG_OUTPUT);

	// Load up the demo application
	GameApp::LoadDemo(this->getWidth(), this->getHeight());

	// Name the current main thread
	ThreadHelper::SetCurrentThreadName("--- Game Main ---");
	ThreadHelper::DebugBegin(0);

	// Managers
	SndMan::Create();
	WaveMan::Create();
	VoiceMan::Create();
	PlaylistMan::Create();
	ASndMan::Create();
	TimeEventMan::Create();

	//---------------------------------------------------------------------------------------------------------
	// Launch the Audio Thread 
	//---------------------------------------------------------------------------------------------------------

	std::thread  AudioThread(AudioMain);
	ThreadHelper::SetThreadName(AudioThread, "AUDIO");
	AudioThread.detach();

	//---------------------------------------------------------------------------------------------------------
	// Launch the File Thread 
	//---------------------------------------------------------------------------------------------------------

	std::thread  FileThread(FileMain);
	ThreadHelper::SetThreadName(FileThread, "FILE");
	FileThread.detach();

	// Milestone 2 Initiate in Game Thread
	// Demo #1
	FileMan::Add("../AudioFiles/Bassoon_mono.wav", Wave::ID::Bassoon);
	FileMan::Add("../AudioFiles/Calliope_mono.wav", Wave::ID::Calliope);
	FileMan::Add("../AudioFiles/Fiddle_mono.wav", Wave::ID::Fiddle);
	FileMan::Add("../AudioFiles/Oboe_mono.wav", Wave::ID::Oboe);
	FileMan::Add("../AudioFiles/SongA.wav", Wave::ID::SongA);
	FileMan::Add("../AudioFiles/SongB.wav", Wave::ID::SongB);

	// Demo #2
	FileMan::Add("../AudioFiles/Intro_mono.wav", Wave::ID::Intro_mono);
	FileMan::Add("../AudioFiles/A_mono.wav", Wave::ID::A_mono);
	FileMan::Add("../AudioFiles/AtoB_mono.wav", Wave::ID::AtoB_mono);
	FileMan::Add("../AudioFiles/B_mono.wav", Wave::ID::B_mono);
	FileMan::Add("../AudioFiles/BtoC_mono.wav", Wave::ID::BtoC_mono);
	FileMan::Add("../AudioFiles/C_mono.wav", Wave::ID::C_mono);
	FileMan::Add("../AudioFiles/CtoA_mono.wav", Wave::ID::CtoA_mono);
	FileMan::Add("../AudioFiles/End_mono.wav", Wave::ID::End_mono);

	// Demo #3
	FileMan::Add("../AudioFiles/Coma_mono.wav", Wave::ID::Coma);

	// Demo #4
	FileMan::Add("../AudioFiles/Dial_mono.wav", Wave::ID::Dial);
	FileMan::Add("../AudioFiles/MoonPatrol_mono.wav", Wave::ID::MoonPatrol);
	FileMan::Add("../AudioFiles/Sequence1_mono.wav", Wave::ID::Sequence);
	FileMan::Add("../AudioFiles/Donkey_mono.wav", Wave::ID::Donkey);

	// Demo #5
	FileMan::Add("../AudioFiles/Electro_mono.wav", Wave::ID::Electro);
	FileMan::Add("../AudioFiles/Alert_mono.wav", Wave::ID::Alarm);
}

//-----------------------------------------------------------------------------
// Game::Update()
//      Called once per frame, update data, tranformations, etc
//      Use this function to control process order
//      Input, AI, Physics, Animation, and Graphics
//-----------------------------------------------------------------------------
void Game::Update()
{
	// Update the demo application
	GameApp::UpdateDemo();

	// Process In Queue
	this->ProcessInQueue();

	// TimeEvent Update() - needs to be called once a Game frame
	TimeEventMan::Update();

	// Quit key pressed?
	this->QuitCheck();

	// Keyboard triggers the start of the demo
	InputProcess();
}

//-----------------------------------------------------------------------------
// Game::Draw()
//		This function is called once per frame
//	    Use this for draw graphics to the screen.
//      Only do rendering here
//-----------------------------------------------------------------------------
void Game::Draw()
{
	// Draw the demo application
	GameApp::DrawDemo();

}



//-----------------------------------------------------------------------------
// Game::UnLoadContent()
//       unload content (resources loaded above)
//       unload all content that was loaded before the Engine Loop started
//-----------------------------------------------------------------------------
void Game::UnLoadContent()
{
	VoiceMan::Destroy();
	WaveMan::Destroy();
	SndMan::Destroy();
	ASndMan::Destroy();
	PlaylistMan::Destroy();
	TimeEventMan::Destroy();
	
	ThreadHelper::DebugEnd(0);
}

//-----------------------------------------------------------------------------
// Game::ProcessInQueue()
//-----------------------------------------------------------------------------
void Game::ProcessInQueue()
{
	// Process Queue
	Command* pCmd = nullptr;

	// Any commands to process?
	while (SndMan::GetGameInQueue()->PopFront(pCmd) == true)
	{
		assert(pCmd);
		pCmd->Execute();

		// Commands are instantly killed after execution
		delete pCmd;
	}
}

//-----------------------------------------------------------------------------
// Game::QuitCheck()
//-----------------------------------------------------------------------------
void Game::QuitCheck()
{
	Keyboard* key = Keyboard::GetInstance();
	assert(key);

	// Read Quit Key
	static bool QuitKey = false;
	if (key != nullptr)
	{
		if (key->GetKeyState(AZUL_KEY::KEY_Q) && !QuitKey)
		{
			// Create a Snd Call
			SndMan::Quit(SndID::Quit);
			FileMan::Quit();

			QuitKey = true;
		}
	}
}

// End of File 

