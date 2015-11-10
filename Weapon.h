#pragma once

#include "cBicho.h"

class Weapon :
	public cBicho
{
public:
	Weapon();
	~Weapon();
	virtual void Logic(vector<int> map, int width, vector<cBicho*> enemies);
	virtual void Draw();
	void setAtk(int atk);
	int getAtk();

protected:
	int tex_id;
	int attackDelay;
	int attackPower;

};
