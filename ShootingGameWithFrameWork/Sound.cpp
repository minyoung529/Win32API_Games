#include "Sound.h"

BSound::BSound()
{
}

BSound::~BSound()
{
}

void BSound::Init()
{
	System_Create(&FMODSystem);

	if (FMODSystem)
		FMODSystem->init(100, FMOD_INIT_NORMAL, nullptr);

	Load();
}

void BSound::Load()
{
	FMODSystem->createSound("Data/Powerup6.wav",
							FMOD_LOOP_NORMAL, 
							nullptr, 
							&pSound[BackgroundSound]);
}

void BSound::Play(int type)
{
	if (type < 0 || type > MaxSound) return;

	// Play
	FMODSystem->update();
	FMODSystem->playSound(pSound[type], 0, false, &channel[type]);

	channel[type]->setVolume(1.0f);
}

void BSound::Stop(int type)
{
	if (type < 0 || type > MaxSound) return;

	channel[type]->stop();
}

void BSound::Paused(int type, bool paused)
{
	channel[type]->setPaused(paused);
}

void BSound::Release()
{
	FMODSystem->release();
	FMODSystem->close();
}