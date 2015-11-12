#pragma once

#include "irrKlang.h"
#pragma comment(lib, "irrklang.lib")

#define SOUND_OVERLOAD	0
#define SOUND_DUNGEON   1
#define SOUND_BOSS_ROOM 2
//#define SOUND_PLAYER	1


class Sound
{
public:
	static Sound* getInstance();
	void playBgm(int id);
	void playSword();
	void playBow();
	void playDamage();
	void playHit();
	void playItem();
	void playWeaponChange();
	void playDoor();
	void playVictory();
	void playLose();
	void playFireBall();
	void StopSounds();
	


private:
	static Sound *instance;
	irrklang::ISoundEngine* engine;

	Sound();

};

