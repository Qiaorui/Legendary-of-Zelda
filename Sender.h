#pragma once
#include "cBicho.h"
#include "cPlayer.h"

class Sender :
	public cBicho
{
public:
	Sender(int scene, int x, int y, int state);
	void setImage(float xo, float xf, float yo, float yf, int tex_id);
	void draw();
	void logic(cPlayer* player);
	~Sender();

private:
	int sentToScene;
	int sentToX;
	int sentToY;
	int newDirection;
	float xo;
	float xf;
	float yo;
	float yf;
	int tex_id;
};

