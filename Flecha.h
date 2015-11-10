#pragma once
#include "Item.h"
class Flecha :
	public Item
{
public:
	Flecha();
	~Flecha();
	void Logic(vector<int> map, cPlayer* player, vector<Enemy*> enemies);
	void DrawObject(int tex_id, int x, int y);
};

