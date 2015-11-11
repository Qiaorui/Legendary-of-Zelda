#pragma once
#include "Enemy.h"
class Boss :
	public Enemy
{
public:
	Boss();
	~Boss();
	void Draw();
	void DrawRect(int tex_id, float xo, float yo, float xf, float yf, int s, int frame);

	void Logic(vector<int> map, int width, cBicho* player);

private:
	int mode;
	int delayattack;
};

