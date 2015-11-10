#include "Flecha.h"



Flecha::Flecha()
{
}


Flecha::~Flecha()
{
}

void Flecha::Logic(vector<int> map, int width, vector<cBicho*> enemies)
{
	int x, y;
	GetPosition(&x, &y);
	switch (GetState()) {

	case STATE_BOW_DOWN:
		--y;
		break;
	case STATE_BOW_UP:
		++y;
		break;
	case STATE_BOW_RIGHT:
		++x;
		break;
	case STATE_BOW_LEFT:
		--y;
		break;
	


	}


}


void Flecha::Draw() { 

	/*    we fix this late....
	float bitx = 16.0f / 608.0f;
	float bity = 16.0f / 152.0f;
	float x0 = bitx;
	float y0 = 0;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBegin(GL_QUADS);
	glTexCoord2f(x0, y0 + bity);	glVertex2i(x - 100, y + 100);  //Left Down
	glTexCoord2f(x0 + bitx, y0 + bity);	glVertex2i(x - 80, y + 100); //right down
	glTexCoord2f(x0 + bitx, y0);	glVertex2i(x - 80, y + 120); //right up
	glTexCoord2f(x0, y0);	glVertex2i(x - 100, y + 120); //left up
	glEnd();
	glDisable(GL_TEXTURE_2D);
	*/
}


