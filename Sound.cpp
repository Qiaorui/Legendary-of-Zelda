#include "Sound.h"


Sound* Sound::instance = NULL;

Sound::Sound()
{
	engine = irrklang::createIrrKlangDevice();
}

Sound* Sound::getInstance() {
	if (!instance) {
		instance = new Sound;
	}
	return instance;
}


void Sound::playBgm(int id) {
	switch (id)
	{
	case SOUND_OVERLOAD:
		engine->play2D("resource/04.-overworld.mp3", true);
	default:
		break;
	}
	
}

void Sound::play() {
	engine->play2D("resource/LTTP_Sword1.wav", false);
}