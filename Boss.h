#pragma once
#include "Enemy.h"
#include "Fireball.h"
class Boss :
	public Enemy
{
public:
	Boss();
	~Boss();
	void Draw();
	void DrawRect(int tex_id, float xo, float yo, float xf, float yf, int s, int frame);
	void Logic(vector<int> map, int width, cBicho* player);
	void FireAttack();
	void hurt(int point);

private:
	int up, down, right, left; //direcciones de fuego
	int mode;
	int delayattack;
	Fireball fireball;
	int maxdistance = 200;
	int CD = 60;
	bool ulti;
};

