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
		case STATE_BOW_LEFT:	xo = 9 * bitx + GetFrame()*bitx;
			yo = 3.0f*bity;
			NextFrame(3);
			
			break;
			//4..6
		case STATE_BOW_RIGHT:	xo = 9 * bitx + GetFrame()*bitx;
			yo = 2.0f*bity;
			NextFrame(3);
			
			break;
		case STATE_BOW_UP:		xo = 9 * bitx + GetFrame()*bitx;
			yo = 4.0f*bity;
			NextFrame(3);
			
			break;

		case STATE_BOW_DOWN:    xo = 9 * bitx + GetFrame()*bitx;
			yo = bity;
			NextFrame(3);
			
			break;
			//player has atacking movement, so has to add frame

		case STATE_SWORD_DOWN:  xo = (GetFrame()*(2 * bitx));
			yo = 12.0f*bity;
			xf = xo + 2.0f*bitx;
			yf = yo - (2.0f*bity);
			NextFrame(7);
			if (GetFrame() == 1) {
				Sound::getInstance()->play();
				//engine->play2D("resource/LTTP_Sword1.wav", false);
				//engine->play2D("resource/MC_Link_Sword2.wav", false);
			}
			break;

		case STATE_SWORD_LEFT:  xo = (GetFrame()*(2 * bitx));
			yo = 6.0f*bity;
			xf = xo + 2.0f*bitx;
			yf = yo - (2.0f*bity);
			NextFrame(7);
			if (GetFrame() == 1) {
				Sound::getInstance()->play();
				//engine->play2D("resource/LTTP_Sword1.wav", false);
				//engine->play2D("resource/MC_Link_Sword2.wav", false);
			}
			break;

		case STATE_SWORD_UP:    xo = (GetFrame()*(2 * bitx));
			yo = 10.0f*bity;
			xf = xo + 2.0f*bitx;
			yf = yo - (2.0f*bity);
			NextFrame(6);
			if (GetFrame() == 1) {
				Sound::getInstance()->play();
				//engine->play2D("resource/LTTP_Sword1.wav", false);
				//engine->play2D("resource/MC_Link_Sword2.wav", false);
			}
			break;

		case STATE_SWORD_RIGHT: xo = (GetFrame()*(2 * bitx));
			yo = 8.0f*bity;
			xf = xo + 2.0f*bitx;
			yf = yo - (2.0f*bity);
			NextFrame(7);
			if (GetFrame() == 1) {
				Sound::getInstance()->play();
				//engine->play2D("resource/LTTP_Sword1.wav", false);
				//engine->play2D("resource/MC_Link_Sword2.wav", false);
			}
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
	case STATE_BOW_DOWN:
		if (GetFrame() == 2) SetState(STATE_LOOKDOWN);
		break;
	case STATE_BOW_UP:
		if (GetFrame() == 2) SetState(STATE_LOOKUP);
		break;
	case STATE_BOW_RIGHT:
		if (GetFrame() == 2) SetState(STATE_LOOKRIGHT);
		break;
	case STATE_BOW_LEFT:
		if (GetFrame() == 2) SetState(STATE_LOOKLEFT);
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

void cPlayer::DrawLife(int tex_id, int cx, int cy){ // has to be really imprioved, only to try how to do it!

	float bitx = 43.0f / 170.0f;
	float bity = 39.0f/ 57.0f;
	int l;
	
	GetLife(&l);
	float x0 = 7.0f / 170.0f;
	float y0 = 11.0f / 57.0f;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBegin(GL_QUADS);
	for (int i = 0; i < l; ++i) {
		glTexCoord2f(x0, y0 + bity);	glVertex2i(cx + 80, cy + 105);  //Left Down
		glTexCoord2f(x0 + bitx,y0 + bity);	glVertex2i(cx + 65, cy + 105); //right down
		glTexCoord2f(x0 + bitx, y0);	glVertex2i(cx + 65, cy + 120); //right up
		glTexCoord2f(x0, y0);	glVertex2i(cx + 80, cy + 120); //left up
		cx += 20;
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

void cPlayer::SwordAttack()
{
 	int state = GetState();
	int seq = GetFrame();
	if (state == STATE_LOOKDOWN) {
		SetState(STATE_SWORD_DOWN);
		seq = 0;
	}
	else if (state == STATE_LOOKUP) {
		SetState(STATE_SWORD_UP);
		seq = 0;
	}
	else if (state == STATE_LOOKRIGHT) {
		SetState(STATE_SWORD_RIGHT);
		seq = 0;
	}
	else if (state == STATE_LOOKLEFT) {
		SetState(STATE_SWORD_LEFT);
		seq = 0;
	}
}

void cPlayer::BowAttack()
{
	int state = GetState();
	int seq = GetFrame();
	if (state == STATE_LOOKDOWN) {
		SetState(STATE_BOW_DOWN);
		seq = 0;
	}
	else if (state == STATE_LOOKUP) {
		SetState(STATE_BOW_UP);
		seq = 0;
	}
	else if (state == STATE_LOOKRIGHT) {
		SetState(STATE_BOW_RIGHT);
		seq = 0;
	}
	else if (state == STATE_LOOKLEFT) {
		SetState(STATE_BOW_LEFT);
		seq = 0;
	}
}