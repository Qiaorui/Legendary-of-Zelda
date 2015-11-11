#include "Enemy.h"



Enemy::Enemy()
{
	smokeDelay = 0;
}


Enemy::~Enemy()
{
}

void Enemy::Draw() {

	float bitx = 15.0f / 840.0f;
	float bity = 15.0f / 567.0f;
	
	float xf, yf, xo, yo;
	int x, y;
	int w, h;

	GetPosition(&x, &y);
	GetWidthHeight(&w, &h);
	int j = smokeDelay / 10;
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 3);
	glBegin(GL_QUADS);
	xo = 657/840.0f + (j*(bitx + 1 / 840.0f));
	yo = 63/567.0f;
	xf = xo + bitx;
	yf = yo - bity;
	glTexCoord2f(xo, yo);	glVertex2i(x, y);  //Left Down
	glTexCoord2f(xf, yo);	glVertex2i(x + w, y); //right down
	glTexCoord2f(xf, yf);	glVertex2i(x + w, y + h); //right up
	glTexCoord2f(xo, yf);	glVertex2i(x, y + h); //left up
	glEnd();

	glDisable(GL_TEXTURE_2D);
	++smokeDelay;
	if (smokeDelay == 22) visible = false;
}

void Enemy::DrawRect(int tex_id, float xo, float yo, float xf, float yf, int s, int frame) {


}


void Enemy::Logic(vector<int> map, int width, cBicho* player) {
	if (!alive) {
		//visible = false;
		active = false;
	}
	

}


void Enemy::setImage(int tex_id) {
	this->tex_id = tex_id;
}