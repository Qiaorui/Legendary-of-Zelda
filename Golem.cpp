#include "Golem.h"



Golem::Golem(){
	visible = true;
}

Golem::~Golem(){}
void Golem::Draw()
{

	//if (tex_id == 2) {
	float xo, yo, xf, yf;
	xf = yf = -1;
	//BLOCK_SIZE = 16, FILE_SIZE = 432
	// 16 / 432 = 0.037
	//N = 15, (FILE_SIZE-15*BLOCK_SIZE)/14 = 13.714  =>0.0317
	float  bitx = 24.0f / 454.0f;;
	//BLOCK_SIZE = 16, FILE_SIZE = 303
	// 16 / 303 = 0.053
	float bity = 25.0f / 340.0f;
	int frame = GetFrame();

	switch (GetState())
	{
		//1
	case STATE_LOOKLEFT:	xo = 240.0f / 454.0f;
		yo = 25.0f / 340.0f;
		break;
		//4
	case STATE_LOOKRIGHT:	xo = 48.0f / 454.0f;
		yo = 25.0f / 340.0f;
		break;
		//1..3
	case STATE_WALKLEFT:	xo = 240.0f / 454.0f + (GetFrame()*(bitx));
		yo = 25.0f / 340.0f;
		NextFrame(2); 
		break;
		//4..6
	case STATE_WALKRIGHT:	xo = 48.0f / 454.0f + (GetFrame()*(bitx));
		yo = 25.0f / 340.0f;
		NextFrame(2); 
		break;

	case STATE_LOOKUP:      xo = 192.0f / 454.0f;
		yo = 25.0f / 340.0f;
		break;

	case STATE_LOOKDOWN:    xo = 120.0f / 454.0f;
		yo = 25.0f / 340.0f;
		break;

	case STATE_WALKUP:	 xo = 168.0f / 454.0f + (GetFrame()*(bitx));
		yo = 25.0f / 340.0f;
		NextFrame(2); 
		break;

	case STATE_WALKDOWN:    xo = 96.0f / 454.0f + (GetFrame()*(bitx));
		yo = 25.0f / 340.0f;
		NextFrame(2); 
		break;
	case STATE_SLEEP:    xo = 0;
		yo = 25.0f / 340.0f;
		NextFrame(2); // si se pone 4 gira la cabeza
		break;
	case STATE_OPEN:    xo = 24.0f / 454.0f;
		yo = 25.0f / 340.0f;
		NextFrame(2); // si se pone 4 gira la cabeza
		break;


		//default:			xo = 91.0f/432.0f; yo = bity; break;
	}

	//When we are not atacking 
	xf = xo + bitx;
	yf = yo - bity;
	
	DrawRect(tex_id, xo, yo, xf, yf, GetState(), frame);
	//}
	//else {
	//	DrawLife(tex_id);
	//}

	//DrawRect(tex_id, 16.0f / 840.0f, 71.0 / 567.0f, 31.0f / 840.0f, 44.0f / 567.0f, 0, 0);
}

void Golem::DrawRect(int tex_id, float xo, float yo, float xf, float yf, int s, int frame)
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




void Golem::Logic(vector<int> map, int width, cBicho* player) {
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

	
	Enemy::Logic(map,width, player);

}