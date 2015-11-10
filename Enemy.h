#pragma once


#include "cPlayer.h"
#include "cBicho.h"

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
	virtual void Logic(vector<int> map, int width, cPlayer* player);
	//virtual void Logic(vector<int> map, int width, cPlayer* player);
	void setImage(int tex_id);

private:


};

