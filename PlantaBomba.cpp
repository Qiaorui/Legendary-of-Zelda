#include "PlantaBomba.h"


PlantaBomba::PlantaBomba(){}
PlantaBomba::~PlantaBomba(){}

void PlantaBomba::Draw(int tex_id)
{

	//if (tex_id == 2) {
	float xo, yo, xf, yf;
	//BLOCK_SIZE = 16, FILE_SIZE = 432
	// 16 / 432 = 0.037
	//N = 15, (FILE_SIZE-15*BLOCK_SIZE)/14 = 13.714  =>0.0317
	float  bitx = 18.0f / 840.0f;
	//BLOCK_SIZE = 16, FILE_SIZE = 303
	// 16 / 303 = 0.053
	float bity = 17.0f / 567.0f;
	int frame = GetFrame();

		if(GetFrame() ==2) xo = 504.0f / 840.0f + (GetFrame()*(bitx)) +1.0f/840.0f;
		else xo = 504.0f / 840.0f + (GetFrame()*(bitx));
		yo = 120.0f / 567.0f;
		NextFrame(3); // con 4 gira la cabeza
		yf = yo - bity;
		xf = xo + bitx;
	DrawRect(tex_id, xo, yo, xf, yf, GetState(), frame);
	
}

void PlantaBomba::DrawRect(int tex_id, float xo, float yo, float xf, float yf, int s, int frame)
{
	int screen_x, screen_y;
	int x, y;
	int w, h;

	GetPosition(&x, &y);
	GetWidthHeight(&w, &h);
	screen_x = x;
	screen_y = y;


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBegin(GL_QUADS);

	glTexCoord2f(xo, yo);	glVertex2i(screen_x, screen_y);  //Left Down
	glTexCoord2f(xf, yo);	glVertex2i(screen_x + w, screen_y); //right down
	glTexCoord2f(xf, yf);	glVertex2i(screen_x + w, screen_y + h); //right up
	glTexCoord2f(xo, yf);	glVertex2i(screen_x, screen_y + h); //left up
	glEnd();

	glDisable(GL_TEXTURE_2D);
}


void PlantaBomba::Logic(vector<int> map, int width) {
	++delaymove;
	if (delaymove >= FRAME_DELAY) {
		int x, y;
		GetPosition(&x, &y);
		switch (rand() % 4) {
		case 0:
			++x;
			SetState(STATE_WALKRIGHT);
			break;
		case 1:
			--x;
			SetState(STATE_WALKLEFT);
			break;
		case 2:
			++y;
			SetState(STATE_WALKUP);
			break;
		case 3:
			--y;
			SetState(STATE_WALKDOWN);
			break;
		}
		SetPosition(x, y);
		delaymove = 0;
	}

}