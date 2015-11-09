#pragma once
#include "Enemy.h"

class Golem :
	public Enemy
{
public:
	Golem();
	~Golem();
	void Draw(int tex_id);
	void DrawRect(int tex_id, float xo, float yo, float xf, float yf, int s, int frame);
	void Logic(vector<int> map, int width);

private:

};

