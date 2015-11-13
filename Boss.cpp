#include "Boss.h"



Boss::Boss()
{
	commandDelay = 0;
	ulti = false;
}


Boss::~Boss()
{	
}
void Boss::Draw()
{
	if (alive) {
		float xo, yo, xf, yf;
		xf = yf = -1;
		float  bitx = 32.0f / 233.0f;;

		float bity = 53.0f / 243.0f;
		int frame = GetFrame();

		switch (GetState())
		{

		case STATE_LOOKDOWN:    xo = GetFrame()*(bitx);
			yo = bity;
			NextFrame(4);
			break;
		}

		xf = xo + bitx;
		yf = yo - bity;

		if (fireball.isVisible()) fireball.Draw(7);

		DrawRect(tex_id, xo, yo, xf, yf, GetState(), frame);
	}
	else Enemy::Draw();
		
}

void Boss::DrawRect(int tex_id, float xo, float yo, float xf, float yf, int s, int frame)
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




void Boss::Logic(vector<int> map, int width, cBicho* player) {
	
	Enemy::Logic(map, width, player);
	if (commandDelay %102 > CD && !ulti) {
		FireAttack();
	}
	else if (commandDelay % 32 > 30 && ulti) {
		FireAttack();
	}
	if (commandDelay > 500) {
		ulti = true;
		int x, y;
		GetPosition(&x, &y);
		if (commandDelay < 550) x += 2;
		else if(commandDelay<600) y += 2;
		else if (commandDelay<650) x -= 4;
		else if (commandDelay<700) y -= 2;
		else if (commandDelay<750) x += 2;
		else {
			commandDelay = 0;
			ulti = false;
		}
		SetPosition(x, y);
	}
	
	++commandDelay;
	
	if (fireball.isActive())fireball.Logic(map, width, player);
}

void Boss::FireAttack()
{
	if (!fireball.isActive() && fireball.isActionFinished()) {
		bool correct = true;
		
			fireball.SetWidthHeight(30, 30);
			fireball.SetPosition(x+5 , y+10 );
			fireball.SetState(STATE_BOW_DOWN);
			fireball.setAtk(2);
		
		if (correct) {
			Sound::getInstance()->playFireBall();
			actionFinished = false;
			cleanFrame();
			fireball.attack();
		}
	}
}

void Boss::hurt(int point) {
	cBicho::hurt(point);
	if (!alive) {
		Sound::getInstance()->StopSounds();
		Sound::getInstance()->playVictory();
	}
}