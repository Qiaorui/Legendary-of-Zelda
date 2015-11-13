#include "Golem.h"



Golem::Golem(){
	visible = true;
	delayattack = 15;
	commandDelay = 0;
	speed = 1;
	mode = 0;
}

Golem::~Golem(){}
void Golem::Draw()
{
	if (alive) {
		float xo, yo, xf, yf;
		xf = yf = -1;
		float  bitx = 24.0f / 454.0f;;

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


			
		}


		xf = xo + bitx;
		yf = yo - bity;

		DrawRect(tex_id, xo, yo, xf, yf, GetState(), frame);
	}
	else Enemy::Draw();

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
	int xgolem, ygolem;
	int xp, yp;
	GetPosition(&xgolem, &ygolem);
	player->GetPosition(&xp, &yp);
	if ( ygolem - yp < 128 && abs(xp - xgolem) < 7 && GetState() == STATE_SLEEP) {
		mode = 1;
	}
	else {
		SetState(STATE_SLEEP);
	}
	if (mode == 1) {
		if (commandDelay < 40) {
			SetState(STATE_OPEN);
			++commandDelay;
		}
		else if (commandDelay < 100) {
			/*SetState(STATE_WALKDOWN);
			SetPosition(xgolem, ygolem - 1);*/
			++commandDelay;
			if (xp > xgolem+10) {
				if (CollidesMapWall(map, RIGHT, width)) {
					if (yp > ygolem) {
						MoveUp(map, width);
					}
					else {
						MoveDown(map, width);
					}
				}
				else {
					MoveRight(map, width);
				}
			}
			//left
			else if (xp +10< xgolem) {
				if (CollidesMapWall(map, LEFT, width)) {
					if (yp > ygolem) {
						MoveUp(map, width);
					}
					else {
						MoveDown(map, width);
					}
				}
				else {
					MoveLeft(map, width);
				}

			}
			//up
			else if (yp > ygolem+10) {
				if (CollidesMapWall(map, UP, width)) {
					if (xp > xgolem) {
						MoveRight(map, width);
					}
					else {
						MoveLeft(map, width);
					}
				}
				else {
					MoveUp(map, width);
				}

			}
			//down
			else if (yp +10< ygolem) {
				if (CollidesMapWall(map, DOWN, width)) {
					if (xp > xgolem) {
						MoveRight(map, width);
					}
					else {
						MoveLeft(map, width);
					}
				}
				else {
					MoveDown(map, width);
				}
			}
		}
		else if (commandDelay < 120){
			mode = 2;
			SetState(STATE_SLEEP);
			++commandDelay;
		}
		else {
			commandDelay = 0;
		}
	}
	

	cRect body;
	player->GetArea(&body);
	if (delayattack < 15) {
		int ex, ey, px, py;
		player->GetPosition(&px, &py);
		GetPosition(&ex, &ey);
		if (px < ex) px = px - 1;
		else px = px + 1;
		if (py < ey) py = py - 1;
		else py = py + 1;
		player->SetPosition(px, py);
	}
	else if (Collides(&body)) {
		Sound::getInstance()->playDamage();
		int l;
		player->hurt(1);
		delayattack = 0;
	}
	++delayattack;
	
	Enemy::Logic(map,width, player);

}