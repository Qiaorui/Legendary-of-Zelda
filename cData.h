#pragma once

#include "cTexture.h"
#include "Globals.h"

//Image array size
#define NUM_IMG		8

//Image identifiers
#define IMG_OVERLOAD	0
#define IMG_PLAYER	1
//#define IMG_LIFE	2
#define IMG_ENEMIES	3
#define IMG_EAST_PALACE 4
#define IMG_GOLEM 5
#define IMG_ITEMS 6
#define IMG_BOSS 7
#define IMG_FIRE 8
/*
#define IMG_ENEMY1	2
#define IMG_ENEMY2	3
#define IMG_SHOOT	4
...
*/

class cData
{
public:
	cData(void);
	~cData(void);

	int  GetID(int img);
	void GetSize(int img,int *w,int *h);
	bool LoadImage(int img,char *filename,int type = GL_RGBA);

private:
	cTexture texture[NUM_IMG];
};
