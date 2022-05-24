#ifndef SOUND_H
#define SOUND_H

#include "fmod.hpp"
using namespace FMOD;

enum SoundType
{
	BackgroundSound = 0,
	AttackSound,
	MaxSound,

};

class BSound
{
public:
	BSound();
	~BSound();

public:
	void	Init();
	void	Load();
	void	Play(int type);
	void	Stop(int type);
	void	Paused(int type, bool paused);
	void	Release();

private:
	System*		FMODSystem;
	Channel*	channel[MaxSound];
	Sound*		pSound[MaxSound];

};
#endif
