#pragma once
#include "Trigger.h"

class Sender :
	public Trigger
{
public:
	Sender();
	Sender(int scene, int x, int y, int state);
	void setCloseImage(float xo, float xf, float yo, float yf);
	void draw(int tex_id);
	void logic(cBicho* player);
	void switchState();
	bool Collides(cRect *rc);
	~Sender();

private:
	float closexo, closexf, closeyo, closeyf;
	int sentToScene;
	int sentToX;
	int sentToY;
	int newDirection;

};

