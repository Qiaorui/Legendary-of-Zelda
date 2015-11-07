#pragma once

#include "cTexture.h"

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

class cScene
{
public:
	cScene(void);
	virtual ~cScene(void);
	void initialize(int w, int h);
	bool LoadLevel(int level);
	void Draw(int tex_id);
	vector<int> GetMap();
	int getWidth();
	int getHeight();
	void setWidth(int w);
	void setHeight(int h);


private:
	vector<int> map;
	//int map[SCENE_WIDTH * SCENE_HEIGHT];	//scene
	int id_DL;								//actual level display list
	int width;
	int height;
};
