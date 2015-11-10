#pragma once
#include "cPlayer.h"
#include "Enemy.h"

class Soldado :
	public Enemy
{
public:
	Soldado();
	~Soldado();
	void Draw();
	void DrawRect(int tex_id, float xo, float yo, float xf, float yf, int s, int frame);

	void Logic(vector<int> map, int width, cPlayer* player);


private:


};

