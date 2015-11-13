#pragma once

#include "Enemy.h"
#include "Fireball.h"

class PlantaBomba :
	public Enemy
{
public:
	PlantaBomba();
	~PlantaBomba();

	void Draw();
	void DrawRect(int tex_id, float xo, float yo, float xf, float yf, int s, int frame);

	void Logic(vector<int> map, int width, cBicho* player);
	void FireAttack();

private:
	vector <Fireball*> Fire;
	int CD = 100;
};