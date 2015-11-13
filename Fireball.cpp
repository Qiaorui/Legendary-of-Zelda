#include "Fireball.h"



Fireball::Fireball()
{
	attackDelay = 0;
	active = false;
	speed = 4;
	distance = 0;
	visible = false;
}


Fireball::~Fireball()
{
}

void Fireball::Logic(vector<int> map, int width, cBicho* player)
{

	Weapon::Logic(map, width, player);
	if (enemy_id < 0) {
		switch (GetState()) {
		case STATE_BOW_DOWN:
			y -= speed;
			distance += speed;
			break;
		case STATE_BOW_UP:
			y += speed;
			distance += speed;
			break;
		case STATE_BOW_RIGHT:
			x += speed;
			distance += speed;
			break;
		case STATE_BOW_LEFT:
			x -= speed;
			distance += speed;
			break;
		}
	}
	if (distance > 200 || attackDelay >= 10) {
		active = false;
		visible = false;
		actionFinished = true;
	}

}


void Fireball::Draw(int tex_id) {
	int x, y, w, h;
	GetPosition(&x, &y);
	GetWidthHeight(&w, &h);
	float xo, xf, yo, yf, maxX, maxY;
	maxX = 369.0f;
	maxY = 150.0f;
	xo = 120.0f *GetFrame();
	yo = 120.0f;
	int width = w;
	int pos = x ;
	NextFrame(3);
	xf = (xo + 120.0f) / maxX;
	yf = (yo - 120.0f) / maxY;
	xo = xo / maxX;
	yo = yo / maxY;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBegin(GL_QUADS);

	glTexCoord2f(xo, yo);	glVertex2i(x, y);  //Left Down
	glTexCoord2f(xf, yo);	glVertex2i(x + w, y); //right down
	glTexCoord2f(xf, yf);	glVertex2i(x + w, y+h); //right up
	glTexCoord2f(xo, yf);	glVertex2i(x, y+h); //left up
	glEnd();

	glDisable(GL_TEXTURE_2D);

}


void Fireball::attack() {
	Weapon::attack();
	visible = true;
	distance = 0;
}