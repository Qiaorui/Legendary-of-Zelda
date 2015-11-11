#pragma once
#include "Enemy.h"

#define STATE_SLEEP       16
#define STATE_OPEN        17


class Golem :
	public Enemy
{
public:
	Golem();
	~Golem();
	void Draw();
	void DrawRect(int tex_id, float xo, float yo, float xf, float yf, int s, int frame);

	void Logic(vector<int> map, int width, cBicho* player);

private:
	int mode;
	int delayattack;
};

