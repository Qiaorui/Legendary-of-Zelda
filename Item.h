#pragma once
#include "cBicho.h"
#include "cPlayer.h"
#include "Enemy.h"
class Item :
	public cBicho
{
public:
	Item();
	~Item();
	virtual void Logic(vector<int> map, cPlayer* player, vector<Enemy*> enemies);
};

