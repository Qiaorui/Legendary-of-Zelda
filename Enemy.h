#pragma once
#include "cBicho.h"
#include "cPlayer.h"

class Enemy :
	public cBicho
{
protected:
	int delaymove;
	int tex_id;

public:
	Enemy();
	~Enemy();
	virtual void Draw();
	virtual void DrawRect(int tex_id, float xo, float yo, float xf, float yf, int s, int frame);
	virtual void Logic(vector<int> map, cPlayer* player);
	void setImage(int tex_id);

private:


};

