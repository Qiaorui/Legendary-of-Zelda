#pragma once

#include "irrKlang.h"
#pragma comment(lib, "irrklang.lib")

#define SOUND_OVERLOAD	0
//#define SOUND_PLAYER	1


class Sound
{
public:
	static Sound* getInstance();
	void playBgm(int id);
	void play();

private:
	static Sound *instance;
	irrklang::ISoundEngine* engine;

	Sound();

};

