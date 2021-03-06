#pragma once

#include "cTexture.h"
#include "Sender.h"
#include "cPlayer.h"
#include "Soldado.h"
#include "Golem.h"
#include "PlantaBomba.h"
#include "Boss.h"
#include "Gear.h"
#include "Block.h"


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
	void addBlock(int x, int y, float xo, float xf, float yo, float yf, int w, int h);
	void logic(cPlayer* player);
	void addEnemy(int enemyType, int x, int y, int tex_id);
	vector<Enemy*> getEnemies();
	void drawMiniMap(int cx, int cy, int x, int y);


private:
	vector<int> map;
	vector<Gear> gears;
	vector<Block> blocks;
	vector<Sender> senders;
	vector<Enemy*> enemies;
	int id_DL;								//actual level display list
	int width;
	int height;
};
