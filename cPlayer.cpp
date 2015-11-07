#include "cScene.h"
#include "cPlayer.h"

cPlayer::cPlayer() {}
cPlayer::~cPlayer(){}

void cPlayer::Draw(int tex_id)
{
	//if (tex_id == 2) {
		float xo, yo, xf, yf;
		xf = yf = -1;
		//BLOCK_SIZE = 16, FILE_SIZE = 432
		// 16 / 432 = 0.037
		//N = 15, (FILE_SIZE-15*BLOCK_SIZE)/14 = 13.714  =>0.0317
		float bitx = 28.3f / 454.0f;
		//BLOCK_SIZE = 16, FILE_SIZE = 303
		// 16 / 303 = 0.053
		float bity = 28.3f / 340.0f;
		int frame = GetFrame();

		switch (GetState())
		{
			//1
		case STATE_LOOKLEFT:	xo = 0.0f;
			yo = 3.0f*bity;
			break;
			//4
		case STATE_LOOKRIGHT:	xo = 0.0f;
			yo = 2.0f*bity;
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

		case STATE_LOOKUP:      xo = 0.0f;
			yo = 4.0f*bity;
			break;

		case STATE_LOOKDOWN:    xo = 0.0f;
			yo = bity;
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
		if (xf == -1 && yf == -1) {
			xf = xo + bitx;
			yf = yo - bity;
		}

		DrawRect(tex_id, xo, yo, xf, yf, GetState(), frame);
	//}
	//else {
	//	DrawLife(tex_id);
	//}

}

void cPlayer::DrawRect(int tex_id, float xo, float yo, float xf, float yf, int s, int frame)
{
	int screen_x, screen_y;
	int x, y;
	int w, h;
    
	GetPosition(&x, &y);
	GetWidthHeight(&w, &h);
	screen_x = x ;
	screen_y = y ;


	float tmpxo, tmpxf, tmpyo, tmpyf;
	tmpxo = -6.2f;
	tmpxf = 6.2f;
	tmpyo = -3.1f;
	tmpyf = 3.1f;
	switch (s)
	{
	case STATE_SWORD_DOWN:
		tmpyo = -20.30f;
		tmpyf = 20.30f;
		tmpxo = -20.30f;
		tmpxf = 20.30f;

		if (GetFrame() == 6) SetState(STATE_LOOKDOWN);
		break;
	case STATE_SWORD_LEFT:
		tmpyo = -20.30f;
		tmpyf = 20.30f;
		tmpxo = -20.30f;
		tmpxf = 20.30f;
		if (GetFrame() == 6) SetState(STATE_LOOKLEFT);
		break;
	case STATE_SWORD_RIGHT:
		tmpyo = -20.30f;
		tmpyf = 20.30f;
		tmpxo = -20.30f;
		tmpxf = 20.30f;
		if (GetFrame() == 6) SetState(STATE_LOOKRIGHT);
		break;
	case STATE_SWORD_UP:
		tmpyo = -20.30f;
		tmpyf = 20.30f;
		tmpxo = -20.30f;
		tmpxf = 20.30f;
		if (GetFrame() == 5) SetState(STATE_LOOKUP);
		//tmpyf = +14.15f;
		//tmpxf = 28.3f;
		break;
	}

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBegin(GL_QUADS);

	glTexCoord2f(xo, yo);	glVertex2i(screen_x + tmpxo, screen_y+tmpyo);  //Left Down
	glTexCoord2f(xf, yo);	glVertex2i(screen_x + w + tmpxf, screen_y + tmpyo); //right down
	glTexCoord2f(xf, yf);	glVertex2i(screen_x + w + tmpxf, screen_y + h + tmpyf); //right up
	glTexCoord2f(xo, yf);	glVertex2i(screen_x + tmpxo, screen_y + h + tmpyf); //left up
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void cPlayer::DrawLife(int tex_id){ // has to be really imprioved, only to try how to do it!

	float bitx = 57.0f / 170.0f;
	float bity = 1.0f;
	int x, y, l;
	GetPosition(&x, &y);
	int screen_x = x ;
	int screen_y = y ;
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


int cPlayer::getCurrentSceneId() {
	return current_scene_id;
}

void cPlayer::setCurrentSceneId(int scene_id) {
	current_scene_id = scene_id;
}

