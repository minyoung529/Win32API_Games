#pragma once
#include "fmod.hpp"

using namespace FMOD;

enum eSOUND
{
	eBACKGROUND_SOUND = 0,
	eATTACK_SOUND,
	eMAX_SOUND
};

class BSound
{
public:
	BSound();
	~BSound();

public:
	void Init();
	void Load();
	void Play(int _Type);
	void Stop(int _Type);
	void Paused(int _Type, bool bPaused);
	void Release();

private:
	System*		m_pFmodSystem;
	Channel*	m_pChannel[eMAX_SOUND];
	Sound*		m_pSound[eMAX_SOUND];

};

