#pragma once
#include "cBicho.h"
class Trigger :
	public cBicho
{
public:
	Trigger();
	~Trigger();
	void setImage(float xo, float xf, float yo, float yf);
	virtual void draw(int tex_id);
	void setWall(bool b);
	bool isWall();
	virtual void logic(cBicho* player);
	int getId();

protected:
	int id;
	float xo;
	float xf;
	float yo;
	float yf;
	bool wall;
};

