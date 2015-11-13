#pragma once

#include "cTexture.h"
#include "Sender.h"
#include "cPlayer.h"
#include "Soldado.h"
#include "Golem.h"
#include "PlantaBomba.h"
#include "Boss.h"
#include "Gear.h"

//#define SCENE_Xo		(2*TILE_SIZE)
//#define SCENE_Yo		TILE_SIZE
//#define SCENE_Xo		0
//#define SCENE_Yo		0

//#define SCENE_WIDTH		36
//#define SCENE_HEIGHT	28

#define FILENAME		"level"
#define FILENAME_EXT	".txt"

#define TILE_SIZE		16
#define BLOCK_SIZE		16

#define SOLDADO 0
#define PLANTABOMBA 1
#define GOLEM 2
#define BOSS 3


class cScene
{
public:
	cScene(void);
	virtual ~cScene(void);
	void initialize(int w, int h);
	bool LoadLevel(int level, float tilewidth, float tileheight);
	void Draw(int tex_id);
	vector<int> GetMap();
	int getWidth();
	int getHeight();
	void setWidth(int w);
	void setHeight(int h);
	int addSender(int x, int y, int scene, int ToX, int ToY, int state, float xo, float xf, float yo, float yf, int w, int h);
	void setSenderCloseImage(int index, float xo, float xf, float yo, float yf);
	void addGear(int x, int y, int sender_id, float xo, float xf, float yo, float yf, int w, int h);

	void logic(cPlayer* player);
	void addEnemy(int enemyType, int x, int y, int tex_id);
	vector<Enemy*> getEnemies();



private:
	vector<int> map;
	vector<Gear> gears;
	vector<Sender> senders;
	vector<Enemy*> enemies;
	//int map[SCENE_WIDTH * SCENE_HEIGHT];	//scene
	int id_DL;								//actual level display list
	int width;
	int height;
};
