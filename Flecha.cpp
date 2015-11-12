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
	
	Weapon::Logic(map, width, enemies);


	switch (GetState()) {

	case STATE_BOW_DOWN:
		if (enemy_id >= 0) {
			SetState(STATE_HIT_DOWN);
			y -= 10;
		}
		else {
			y -= speed;
			distance += speed;
		}
		break;
	case STATE_BOW_UP:
		if (enemy_id >= 0) {
			SetState(STATE_HIT_UP);
			y += 10;
		}
		else {
			y += speed;
			distance += speed;
		}

		break;
	case STATE_BOW_RIGHT:
		if (enemy_id >= 0) {
			SetState(STATE_HIT_RIGHT);
			x += 10;
		}
		else {
			x += speed;
			distance += speed;
		}

		break;
	case STATE_BOW_LEFT:
		if (enemy_id >= 0) {
			SetState(STATE_HIT_LEFT);
			x -= 10;
		}
		else {
			x -= speed;
			distance += speed;
		}

		break;
	}

	if (distance > 200 || CollidesMapWall(map, LEFT, width) || attackDelay >= 10) {
		active = false;
		visible = false;
		actionFinished = true;
	}

}


void Flecha::Draw(int tex_id) { 

	float xo, xf, yo, yf, maxX, maxY;
	maxX = 454.0f;
	maxY = 340.0f;

	switch (GetState()) {

	case STATE_BOW_DOWN:
		xo = 350.0f;
		yo = 21.0f;
		break;
	case STATE_BOW_UP:
		xo = 351.0f;
		yo = 106.0f;
		break;
	case STATE_BOW_RIGHT:
		xo = 346.0f;
		yo = 44.0f;
		break;
	case STATE_BOW_LEFT:
		xo = 346.0f;
		yo = 73.0f;
		break;
	case STATE_HIT_DOWN:
		xo = 359.0f + GetFrame()*7.0f;
		yo = 21.0f;
		NextFrame(3);
		break;
	case STATE_HIT_UP:
		xo = 360.0f + GetFrame()*7.0f;
		yo = 106.0f;
		NextFrame(3);
		break;
	case STATE_HIT_LEFT:
		xo = 364.0f;
		yo = 70.0f + GetFrame()*7.0f;
		NextFrame(3);
		break;

	case STATE_HIT_RIGHT:
		xo = 371.0f;
		yo = 37.0f + GetFrame()*7.0f;
		NextFrame(3);
		break;
	}
	xf = (xo + w) / maxX;
	yf = (yo - h) / maxY;
	xo = xo / maxX;
	yo = yo / maxY;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBegin(GL_QUADS);

	glTexCoord2f(xo, yo);	glVertex2i(x, y - h);  //Left Down
	glTexCoord2f(xf, yo);	glVertex2i(x + w, y - h); //right down
	glTexCoord2f(xf, yf);	glVertex2i(x + w, y); //right up
	glTexCoord2f(xo, yf);	glVertex2i(x, y); //left up
	glEnd();

	glDisable(GL_TEXTURE_2D);

}


void Flecha::attack() {
	Weapon::attack();
	visible = true;
	distance = 0;
}