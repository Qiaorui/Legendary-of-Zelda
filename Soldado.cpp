#include "Soldado.h"



Soldado::Soldado(){
	delaymove = 15;
}

Soldado::~Soldado(){}

void Soldado::Draw()
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
	float bity =  28.0f / 567.0f;
	float  bitx = 0.0f;
	int frame = GetFrame();

	switch (GetState())
	{
		//1
	case STATE_LOOKLEFT:	xo = 183.0f / 840.0f;
		yo = 71.0f / 567.0f;
		break;
		//4
	case STATE_LOOKRIGHT:	xo = 95.0f / 840.0f;
		yo = 71.0f / 567.0f;
		break;
		//1..3
	case STATE_WALKLEFT:	xo = 183.0f / 840.0f + (GetFrame()*(bitxl + 4.0f / 840.0f));
		yo = 71.0f / 567.0f;
		NextFrame(2); // con 4 gira la cabeza
		break;
		//4..6
	case STATE_WALKRIGHT:	xo = 95.0f / 840.0f + (GetFrame()*(bitxl + 2.0f / 840.0f));
		yo = 71.0f / 567.0f;
		NextFrame(2); // con 4 gira la cabeza
		break;

	case STATE_LOOKUP:      xo = 265.0f / 840.0f;
		yo = 71.0f / 567.0f;
		break;

	case STATE_LOOKDOWN:    xo = 16.0f/840.0f;
		yo = 71.0f/567.0f;
		break;

	case STATE_WALKUP:	 xo = 265.0f / 840.0f + (GetFrame()*(bitxp + 4.0f / 840.0f));
		yo = 71.0f / 567.0f;
		NextFrame(2); // con 4 gira la cabeza
		break;

	case STATE_WALKDOWN:    xo = 16.0f / 840.0f + (GetFrame()*(bitxp + 4.0f / 840.0f));
		yo = 71.0f / 567.0f;
		NextFrame(2); // si se pone 4 gira la cabeza
		break;


		//default:			xo = 91.0f/432.0f; yo = bity; break;
	}

	//When we are not atacking 
	if (GetState() == STATE_LOOKDOWN || GetState() == STATE_LOOKUP || GetState() == STATE_WALKUP || GetState() == STATE_WALKDOWN){
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
	
//DrawRect(tex_id, 16.0f / 840.0f, 71.0 / 567.0f, 31.0f / 840.0f, 44.0f / 567.0f, 0, 0);
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


void Soldado::Logic(vector<int> map, cPlayer* player) {
	//comprobar si colisiona con link//////////
	cRect body;
	player->GetArea(&body);
	if (delaymove < 15) {
		int ex, ey, px, py;
		player->GetPosition(&px, &py);
		GetPosition(&ex, &ey);
		if (px < ex) px = px - 1;
		else px = px + 1;
		if (py < ey) py = py - 1;
		else py =py + 1;
		player->SetPosition(px, py);
	}
	else if (Collides(&body)) {
		Sound::getInstance()->playDamage();
		int l;
		player->GetLife(&l);
		player->SetLife(l - 1);
		delaymove = 0;
	}
	++delaymove;
	if (delaymove >= FRAME_DELAY + 15) {
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
		delaymove = 15;
	}
	
}