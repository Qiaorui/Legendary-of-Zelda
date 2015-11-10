#pragma once

#include "Weapon.h"
//#include "Enemy.h"
class Espada :
	public Weapon
{
public:
	Espada();
	~Espada();
//	void Logic(vector<int> map, int width, vector<Enemy*> enemies) ;

private :
	int id;
};

