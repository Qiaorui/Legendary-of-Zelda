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

void Sound::playSword() {
	engine->play2D("resource/LTTP_Sword1.wav", false);
}

void Sound::playBow() {
	engine->play2D("resource/LTTP_Arrow_Shoot.wav", false);
}
void Sound::playDamage() {
	engine->play2D("resource/LTTP_Link_Hurt.wav", false);
}