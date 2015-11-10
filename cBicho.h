#pragma once

#include "cTexture.h"
#include "Globals.h"
#include "Sound.h"

#define FRAME_DELAY		8
#define STEP_LENGTH		2
#define JUMP_HEIGHT		96
#define JUMP_STEP		4

#define STATE_LOOKLEFT		0
#define STATE_LOOKRIGHT		1
#define STATE_WALKLEFT		2
#define STATE_WALKRIGHT		3
#define STATE_WALKUP        4
#define STATE_WALKDOWN      5	
#define STATE_LOOKUP        6 
#define STATE_LOOKDOWN      7
#define STATE_SWORD_DOWN    8
#define STATE_SWORD_UP      9
#define STATE_SWORD_RIGHT   10
#define STATE_SWORD_LEFT    11 
#define STATE_BOW_DOWN    12
#define STATE_BOW_UP      13
#define STATE_BOW_RIGHT   14
#define STATE_BOW_LEFT    15
#define STATE_SLEEP       16
#define STATE_OPEN        17

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

class cRect
{
public:
	int left,top,
		right,bottom;
};

class cBicho
{
public:
	cBicho(void);
	cBicho(int x,int y,int w,int h, int l);
	~cBicho(void);

	void SetPosition(int x,int y);
	void GetPosition(int *x,int *y);
	void SetLife(int l);
	void GetLife(int *l);
	void SetTile(int tx,int ty);
	void GetTile(int *tx,int *ty);
	void SetWidthHeight(int w,int h);
	void GetWidthHeight(int *w,int *h);

	bool Collides(cRect *rc);
	bool CollidesMapWall(vector<int> map, int direction, int width);
	//bool CollidesMapFloor(int *map);
	void GetArea(cRect *rc);
	void DrawRect(int tex_id,float xo,float yo,float xf,float yf);
	void MoveRight(vector<int> map, int width);
	void MoveLeft(vector<int> map, int width);
	void MoveUp(vector<int> map, int width);
	void MoveDown(vector<int> map, int width);
	//void Jump(int *map);
	void Stop();
	void Logic(vector<int> map, int i, int j);

	int  GetState();
	void SetState(int s);

	void NextFrame(int max);
	int  GetFrame();
	boolean active;

private:
	int x,y;
	int w,h;
	int l;
	int state;

	bool jumping;
	int jump_alfa;
	int jump_y;

	int seq,delay;
};
