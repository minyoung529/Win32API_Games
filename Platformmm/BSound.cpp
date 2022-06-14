#include "BSound.h"


BSound::BSound()
{
}


BSound::~BSound()
{
}

void BSound::Init()
{
	System_Create(&m_pFmodSystem);
	if (m_pFmodSystem)
		m_pFmodSystem->init(100, FMOD_INIT_NORMAL, nullptr);

	Load();
}

void BSound::Load()
{
	m_pFmodSystem->createSound("Data/Thinking Out Loud.wav", FMOD_LOOP_NORMAL, nullptr, &m_pSound[eBACKGROUND_SOUND]);
	m_pFmodSystem->createSound("Data/Character_attack.wav", FMOD_DEFAULT, nullptr, &m_pSound[eATTACK_SOUND]);
}

void BSound::Play(int _Type)
{
	if (_Type < 0 || _Type >= eMAX_SOUND)
		return;

	m_pFmodSystem->update();
	m_pFmodSystem->playSound(m_pSound[_Type], 0, false, &m_pChannel[_Type]);

	m_pChannel[_Type]->setVolume(1.0f);
}

void BSound::Stop(int _Type)
{
	if (_Type < 0 || _Type >= eMAX_SOUND)
		return;

	m_pChannel[_Type]->stop();
}

void BSound::Paused(int _Type, bool bPaused)
{
	if (_Type < 0 || _Type >= eMAX_SOUND)
		return;

	m_pChannel[_Type]->setPaused(bPaused);
}

void BSound::Release()
{
	m_pFmodSystem->release();
	m_pFmodSystem->close();
}