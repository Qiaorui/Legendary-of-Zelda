#pragma once

#include "cScene.h"
#include "cPlayer.h"
#include "Soldado.h"
#include "Golem.h"
#include "PlantaBomba.h"
#include "cData.h"

//#define GAME_WIDTH	480
//#define GAME_HEIGHT 480
#define GAME_WIDTH	256
#define GAME_HEIGHT 256
//#define SCREEN_WIDTH 256
//#define SCREEN_HEIGHT 256
#define NUM_SCENE 3

class cGame
{
public:
	cGame(void);
	virtual ~cGame(void);

	bool Init();
	bool Loop();
	void Finalize();

	//When resize windows
	void resize(int width, int height);

	//Input
	void ReadKeyboard(unsigned char key, int x, int y, bool press);
	void ReadMouse(int button, int state, int x, int y);
	//Process
	bool Process();
	//Output
	void Render();

private:
	unsigned char keys[256];
	cScene Scene[NUM_SCENE];
	cPlayer Player;
	Soldado Soldier;
	Golem Ciclope;
	PlantaBomba Plant;
	cData Data;
};

