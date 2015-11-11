#include "Flecha.h"



Flecha::Flecha()
{
	attackDelay = 10;
	active = false;
	speed = 4;
	distance = 0;
}


Flecha::~Flecha()
{
	
}

void Flecha::Logic(vector<int> map, int width, vector<cBicho*> enemies)
{
	bool colision = false;
	if (attackDelay >= 10) {
		for (int i = 0; i < enemies.size(); ++i)
		{
			cRect body;
			enemies[i]->GetArea(&body);
			if (Collides(&body)) {
				attackDelay = 0;
				enemies[i]->hurt(attackPower);
				enemy_id = i;
				colision = true;
				visible = false;
				//distance = 0;
			}

		}
	}
	else {
		int ex, ey, ix, iy;
		enemies[enemy_id]->GetPosition(&ex, &ey);
		//player->GetPosition(&ix, &iy);
		ix = x + w / 2;
		iy = y + h / 2;
		if (ex < ix) ex = ex - 1;
		else ex = ex + 1;
		if (ey < iy) ey = ey - 1;
		else ey = ey + 1;
		enemies[enemy_id]->SetPosition(ex, ey);
		++attackDelay;
		if (attackDelay == 10)active = false;
	}
	switch (GetState()) {

	case STATE_BOW_DOWN:
		 if (distance > 200) {
			active = false;
			visible = false;
			distance = 0;
		}
		y -= speed;
		distance += speed;
		break;
	case STATE_BOW_UP:
		if (distance > 200) {
			active = false;
			visible = false;
			distance = 0;
		}
		y += speed;
		distance += speed;
		break;
	case STATE_BOW_RIGHT:
	 if (distance > 200) {
			active = false;
			visible = false;
			distance = 0;
		}
		x += speed;
		distance += speed;
		break;
	case STATE_BOW_LEFT:
		 if (distance > 200) {
			active = false;
			visible = false;
			distance = 0;
		}
		x -= speed;
		distance += speed;
		break;
	}



}


void Flecha::Draw(int tex_id) { 

	 // we fix this late....
	float bitx = 28.3f / 454.0f;
	float bity = 28.3f / 340.0f;
	float xo, yo, xf, yf;
	int x, y, w, h;
	GetPosition(&x, &y);
	GetWidthHeight(&w, &h);
	int state = GetState();
	xo = 12 * bitx;
	switch (state) {

	case STATE_BOW_DOWN:
		yo = bity;
		break;
	case STATE_BOW_UP:
		yo = 4.0f*bity;
		break;
	case STATE_BOW_RIGHT:
		yo = 2.0f*bity;
		break;
	case STATE_BOW_LEFT:
		yo = 3.0f*bity;
		break;
	}
	xf = xo + bitx;
	yf = yo - bity; // has to be fixed because sometimes is no state bow
	w = 28;
	h = 28;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBegin(GL_QUADS);

	glTexCoord2f(xo, yo);	glVertex2i(x -w/2 , y -h/2 );  //Left Down
	glTexCoord2f(xf, yo);	glVertex2i(x + w/2 , y - h/2); //right down
	glTexCoord2f(xf, yf);	glVertex2i(x + w/2 , y + h/2); //right up
	glTexCoord2f(xo, yf);	glVertex2i(x - w/2, y + h/2 ); //left up
	glEnd();

	glDisable(GL_TEXTURE_2D);
	
}


