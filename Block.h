#pragma once
#include "Trigger.h"

class Block :
	public Trigger
{
public:
	Block();
	~Block();
	void logic(cBicho* bicho, vector<int> map, int width);
	bool Collides(cRect *rc);
};

