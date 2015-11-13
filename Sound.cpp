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
	engine->stopAllSounds();
	switch (id)
	{
	case SOUND_OVERLOAD:
		engine->play2D("resource/04.-overworld.mp3", true);
		break;
	case SOUND_DUNGEON:
		engine->play2D("resource/15.-sanctuary-dungeon.mp3", true);
		break;
	case SOUND_BOSS_ROOM:
		engine->play2D("resource/18.-boss-bgm.mp3", true);
		break;
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
void Sound::playHit() {
	engine->play2D("resource/LTTP_Enemy_Hit.wav", false);
}
void Sound::playItem() {
	engine->play2D("resource/LTTP_Item.wav", false);
}

void Sound::playWeaponChange() {
	engine->play2D("resource/change-weapon.wav", false);
}

void Sound::playDoor() {
	engine->play2D("resource/LTTP_Door.wav",false);
}

void Sound::playLose() {
	engine->stopAllSounds();
	engine->play2D("resource/LTTP_Link_Dying.wav", false);
}
void Sound::playFireBall() {
	engine->play2D("resource/FlameArrow.mp3", false);
}

void Sound::playVictory() {
	engine->play2D("resource/VictoryFanfare.mp3", false);
}

void Sound::StopSounds() {
	engine->stopAllSounds();

}

void Sound::playOpen() {
	engine->play2D("resource/gate-latch.wav", false);
}
void Sound::playClose() {
	engine->play2D("resource/LTTP_Dungeon_Open.wav", false);
}

void Sound::playPush() {
	engine->play2D("resource/LTTP_Link_Push.wav", false);
}