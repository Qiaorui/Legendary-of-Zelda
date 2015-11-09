#pragma once

#include "Enemy.h"


class PlantaBomba :
	public Enemy
{
public:
	PlantaBomba();
	~PlantaBomba();

	void Draw(int tex_id);
	void DrawRect(int tex_id, float xo, float yo, float xf, float yf, int s, int frame);
	void Logic(vector<int> map, int width);


private:

};