#pragma once

#include "Weapon.h"
class Espada :
	public Weapon
{
public:
	Espada();
	~Espada();
	void Logic(vector<int> map, int width, vector<cBicho*> enemies) ;

private :
	int id;
};

