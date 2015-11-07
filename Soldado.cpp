#include "Soldado.h"



Soldado::Soldado(){}

Soldado::~Soldado(){}

void Soldado::Draw(int tex_id)
{
	//if (tex_id == 2) {
	float xo, yo, xf, yf;
	xf = yf = -1;
	//BLOCK_SIZE = 16, FILE_SIZE = 432
	// 16 / 432 = 0.037
	//N = 15, (FILE_SIZE-15*BLOCK_SIZE)/14 = 13.714  =>0.0317
	float  bitxl = 18.0f / 840.0f;
	float bitxp = 16.0f / 840.0f;
	//BLOCK_SIZE = 16, FILE_SIZE = 303
	// 16 / 303 = 0.053
	float bity =  28.0f / 1200.0f;
	float  bitx = 0.0f;
	int frame = GetFrame();

	switch (GetState())
	{
		//1
	case STATE_LOOKLEFT:	xo = 181.0f;
		yo = 71.0f;
		break;
		//4
	case STATE_LOOKRIGHT:	xo = 95.0f;
		yo = 71.0f;
		break;
		//1..3
	case STATE_WALKLEFT:	xo = (GetFrame()*bitx);
		yo = 3.0f*bity;
		NextFrame(8);
		break;
		//4..6
	case STATE_WALKRIGHT:	xo = (GetFrame()*bitx);
		yo = 2.0f*bity;
		NextFrame(8);
		break;

	case STATE_LOOKUP:      xo = 265.0f;
		yo = 71.0f;
		break;

	case STATE_LOOKDOWN:    xo = 16.0f;
		yo = 71.0f;
		break;

	case STATE_WALKUP:		xo = (GetFrame()*bitx);
		yo = 4.0f*bity;
		NextFrame(8);
		break;

	case STATE_WALKDOWN:    xo = (GetFrame()*bitx);
		yo = bity;
		NextFrame(8);
		break;

		//player has atacking movement, so has to add frame

	case STATE_SWORD_DOWN:  xo = (GetFrame()*(2 * bitx));
		yo = 12.0f*bity;
		xf = xo + 2.0f*bitx;
		yf = yo - (2.0f*bity);
		NextFrame(7);
		//if (GetFrame() == 6) SetState(STATE_LOOKDOWN);
		break;

	case STATE_SWORD_LEFT:  xo = (GetFrame()*(2 * bitx));
		yo = 6.0f*bity;
		xf = xo + 2.0f*bitx;
		yf = yo - (2.0f*bity);
		NextFrame(7);
		//if (GetFrame() == 6) SetState(STATE_LOOKLEFT);
		break;

	case STATE_SWORD_UP:    xo = (GetFrame()*(2 * bitx));
		yo = 10.0f*bity;
		xf = xo + 2.0f*bitx;
		yf = yo - (2.0f*bity);
		NextFrame(6);
		//if (GetFrame() == 5) SetState(STATE_LOOKUP);
		break;

	case STATE_SWORD_RIGHT: xo = (GetFrame()*(2 * bitx));
		yo = 8.0f*bity;
		xf = xo + 2.0f*bitx;
		yf = yo - (2.0f*bity);
		NextFrame(7);
		//if (GetFrame() == 6) SetState(STATE_LOOKRIGHT);
		break;

		//default:			xo = 91.0f/432.0f; yo = bity; break;
	}

	//When we are not atacking 
	if (GetState() == STATE_LOOKDOWN || GetState() == STATE_LOOKUP){
		xf = xo + bitxp;
	}
	else {
		xf = xo + bitxl;
	}
	yf = yo - bity;
	DrawRect(tex_id, xo, yo, xf, yf, GetState(), frame);
	//}
	//else {
	//	DrawLife(tex_id);
	//}

}

void Soldado::DrawRect(int tex_id, float xo, float yo, float xf, float yf, int s, int frame)
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

	glTexCoord2f(xo, yo);	glVertex2i(screen_x , screen_y );  //Left Down
	glTexCoord2f(xf, yo);	glVertex2i(screen_x + w , screen_y); //right down
	glTexCoord2f(xf, yf);	glVertex2i(screen_x + w , screen_y + h ); //right up
	glTexCoord2f(xo, yf);	glVertex2i(screen_x , screen_y + h ); //left up
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void Soldado::DrawLife(int tex_id) { // has to be really imprioved, only to try how to do it!

	float bitx = 57.0f / 170.0f;
	float bity = 1.0f;
	int x, y, l;
	GetPosition(&x, &y);
	int screen_x = x;
	int screen_y = y;
	GetLife(&l);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBegin(GL_QUADS);
	for (int i = 0; i < l; ++i) {
		glTexCoord2f(0.0f, bity);	glVertex2i(screen_x + 80, screen_y + 100);  //Left Down
		glTexCoord2f(bitx, bity);	glVertex2i(screen_x + 60, screen_y + 100); //right down
		glTexCoord2f(bitx, 0.0f);	glVertex2i(screen_x + 60, screen_y + 120); //right up
		glTexCoord2f(0.0f, 0.0f);	glVertex2i(screen_x + 80, screen_y + 120); //left up
		screen_x += 20;
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}


int Soldado::getCurrentSceneId() {
	return current_scene_id;
}

void Soldado::setCurrentSceneId(int scene_id) {
	current_scene_id = scene_id;
}

