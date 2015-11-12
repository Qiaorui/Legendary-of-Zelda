#pragma once
#include "Weapon.h"

#define STATE_BOW_DOWN    12
#define STATE_BOW_UP      13
#define STATE_BOW_RIGHT   14
#define STATE_BOW_LEFT    15
#define STATE_HIT_DOWN    16
#define STATE_HIT_UP      17
#define STATE_HIT_LEFT    18
#define STATE_HIT_RIGHT   19

class Fireball :
	public Weapon
{
public:
	Fireball();
	~Fireball();

	void Logic(vector<int> map, int width, cBicho* player);
	void Draw(int tex_id);
	void attack();


private:

	int distance;
};

