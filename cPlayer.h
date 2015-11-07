#pragma once

#include "cBicho.h"
#include "irrKlang.h"
#define PLAYER_START_CX		3
#define PLAYER_START_CY		2

class cPlayer: public cBicho
{
public:
	cPlayer();
	~cPlayer();

	void Draw(int tex_id);
	void DrawRect(int tex_id, float xo, float yo, float xf, float yf, int s, int frame);

	void DrawLife(int tex_id);

	irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();
	void setCurrentSceneId(int scene_id);
	int getCurrentSceneId();

private:
	int current_scene_id;

};
