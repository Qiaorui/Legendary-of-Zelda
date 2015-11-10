#pragma once
#include "Item.h"
#include "cPlayer.h"
#include "Enemy.h"
class Espada :
	public Item
{
public:
	Espada();
	~Espada();
	void Logic(vector<int> map, cPlayer* player, vector<Enemy*> enemies);
protected:
	int delayespada;
	int id;
};

