

#include "cPlayer.h"

cPlayer::cPlayer() {
	commandDelay = 0;
	FRAME_DELAY = 4;
	espada.setAtk(2);
	flecha.setAtk(1);

}
cPlayer::~cPlayer(){}

void cPlayer::Draw(int tex_id)
{
	float xo, yo, xf, yf;
	xf = yf = -1;
	float bitx = 28.3f / 454.0f;
	float bity = 28.3f / 340.0f;
	int frame = GetFrame();

	switch (GetState())
	{
	case STATE_LOOKLEFT:	xo = 0.0f;
		yo = 3.0f*bity;
		break;
	case STATE_LOOKRIGHT:	xo = 0.0f;
		yo = 2.0f*bity;
		break;
	case STATE_WALKLEFT:	xo = (GetFrame()*bitx);
		yo = 3.0f*bity;
		NextFrame(8);
		break;
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
	case STATE_SWORD_DOWN:  xo = (GetFrame()*(2 * bitx));
		yo = 12.0f*bity;
		xf = xo + 2.0f*bitx;
		yf = yo - (2.0f*bity);
		NextFrame(7);
		break;

	case STATE_SWORD_LEFT:  xo = (GetFrame()*(2 * bitx));
		yo = 6.0f*bity;
		xf = xo + 2.0f*bitx;
		yf = yo - (2.0f*bity);
		NextFrame(7);
		break;

	case STATE_SWORD_UP:    xo = (GetFrame()*(2 * bitx));
		yo = 10.0f*bity;
		xf = xo + 2.0f*bitx;
		yf = yo - (2.0f*bity);
		NextFrame(6);
		break;

	case STATE_SWORD_RIGHT: xo = (GetFrame()*(2 * bitx));
		yo = 8.0f*bity;
		xf = xo + 2.0f*bitx;
		yf = yo - (2.0f*bity);
		NextFrame(7);
		break;
	}
	if (xf == -1 && yf == -1) {
		xf = xo + bitx;
		yf = yo - bity;
	}

	DrawRect(tex_id, xo, yo, xf, yf, GetState(), frame);
}

void cPlayer::DrawRect(int tex_id, float xo, float yo, float xf, float yf, int s, int frame)
{
	int screen_x, screen_y;
	int x, y;
	int w, h;

	GetPosition(&x, &y);
	GetWidthHeight(&w, &h);
	screen_x = x;
	screen_y = y;


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

	glTexCoord2f(xo, yo);	glVertex2i(screen_x + tmpxo, screen_y + tmpyo);  //Left Down
	glTexCoord2f(xf, yo);	glVertex2i(screen_x + w + tmpxf, screen_y + tmpyo); //right down
	glTexCoord2f(xf, yf);	glVertex2i(screen_x + w + tmpxf, screen_y + h + tmpyf); //right up
	glTexCoord2f(xo, yf);	glVertex2i(screen_x + tmpxo, screen_y + h + tmpyf); //left up
	glEnd();

	glDisable(GL_TEXTURE_2D);

	if (flecha.isVisible()) {
		flecha.Draw(tex_id);
	}
}

void cPlayer::DrawStatus(int cx, int cy) {
	float maxX = 608.0f;
	float maxY = 152.0f;


	//Life Section
	float xo, yo;
	int itemh, itemw;
	float xf, yf;
	itemh = 7;
	itemw = 7;
	int paddingX = 80;
	int paddingY = 110;
	int life = getLife();
	int maxLife = getMaxLife();
	yf = (92.0f - itemh) / maxY;
	yo = 92.0f / maxY;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, item_tex_id);
	glBegin(GL_QUADS);
	for (int i = 0; i < maxLife; i += 2) {
		if (life / 2 > 0) {
			xo = 42.0f;
		}
		else if (life > 0) {
			xo = 50.0f;
		}
		else {
			xo = 58.0f;
		}
		xf = (xo + itemw) / maxX;
		xo = xo / maxX;
		glTexCoord2f(xo, yo);	glVertex2i(cx + paddingX, cy + paddingY); //Left Down
		glTexCoord2f(xf, yo);	glVertex2i(cx + paddingX + itemw + 7, cy + paddingY); //right down
		glTexCoord2f(xf, yf);	glVertex2i(cx + paddingX + itemw + 7, cy + paddingY + itemh + 7); //right up
		glTexCoord2f(xo, yf);	glVertex2i(cx + paddingX, cy + paddingY + itemh + 7); //left up
		paddingX += 15;
		life -= 2;
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);

	//Item Section
	itemw = itemh = 15;
	switch (usingWeapon)
	{
	case SWORD:
		xo = 37.0f;
		yo = 72.0f;
		break;
	case BOW:
		xo = 16.0f;
		yo = 16.0f;
		break;
	default:
		break;
	}
	xf = (xo + itemw) / maxX;
	yf = (yo - itemh) / maxY;
	xo = xo / maxX;
	yo = yo / maxY;
	paddingX = -120;
	paddingY = 100;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, item_tex_id);
	glBegin(GL_QUADS);
	glTexCoord2f(136.0 / maxX, 148.0f / maxY);	glVertex2i(cx + paddingX - 3, cy + paddingY - 3); //Left Down
	glTexCoord2f(214.0 / maxX, 148.0f / maxY);	glVertex2i(cx + paddingX + 3 + itemw + 7, cy + paddingY - 3); //right down
	glTexCoord2f(214.0 / maxX, 78.0 / maxY);	glVertex2i(cx + paddingX + 3 + itemw + 7, cy + paddingY + 3 + itemh + 7); //right up
	glTexCoord2f(136.0 / maxX, 78.0 / maxY);	glVertex2i(cx + paddingX - 3, cy + paddingY + 3 + itemh + 7); //left up

	glTexCoord2f(xo, yo);	glVertex2i(cx + paddingX, cy + paddingY); //Left Down
	glTexCoord2f(xf, yo);	glVertex2i(cx + paddingX + itemw + 7, cy + paddingY); //right down
	glTexCoord2f(xf, yf);	glVertex2i(cx + paddingX + itemw + 7, cy + paddingY + itemh + 7); //right up
	glTexCoord2f(xo, yf);	glVertex2i(cx + paddingX, cy + paddingY + itemh + 7); //left up
	glEnd();
	glDisable(GL_TEXTURE_2D);

}






void cPlayer::SwordAttack()
{
	if (!espada.isActive() && espada.isActionFinished()) {
		bool correct = true;
		switch (GetState()) {
		case STATE_LOOKDOWN:
			SetState(STATE_SWORD_DOWN);
			espada.SetPosition(x - 5, y - 11);
			espada.SetWidthHeight(32, 16);
			break;
		case STATE_LOOKUP:
			SetState(STATE_SWORD_UP);
			espada.SetPosition(x - 11, y + 14);
			espada.SetWidthHeight(32, 16);
			break;
		case STATE_LOOKRIGHT:
			SetState(STATE_SWORD_RIGHT);
			espada.SetPosition(x + 14, y - 8);
			espada.SetWidthHeight(16, 32);
			break;
		case STATE_LOOKLEFT:
			SetState(STATE_SWORD_LEFT);
			espada.SetPosition(x - 16, y - 8);
			espada.SetWidthHeight(16, 32);
			break;
		default:
			correct = false;
			break;
		}
		if (correct) {
			actionFinished = false;
			cleanFrame();
			espada.attack();
			Sound::getInstance()->playSword();
		}
	}
}

void cPlayer::BowAttack()
{
	if (!flecha.isActive() && flecha.isActionFinished()) {
		bool correct = true;
		switch (GetState()) {
		case STATE_LOOKDOWN:
			SetState(STATE_BOW_DOWN);
			flecha.SetWidthHeight(7, 15);
			flecha.SetPosition(x + w / 2, y + h);
			flecha.SetState(STATE_BOW_DOWN);
			break;
		case STATE_LOOKUP:
			SetState(STATE_BOW_UP);
			flecha.SetWidthHeight(7, 15);
			flecha.SetPosition(x + w / 2, y);
			flecha.SetState(STATE_BOW_UP);
			break;
		case STATE_LOOKRIGHT:
			SetState(STATE_BOW_RIGHT);
			flecha.SetWidthHeight(15, 7);
			flecha.SetPosition(x + 16, y + h / 2);
			flecha.SetState(STATE_BOW_RIGHT);
			break;
		case STATE_LOOKLEFT:
			SetState(STATE_BOW_LEFT);
			flecha.SetWidthHeight(15, 7);
			flecha.SetPosition(x, y + h / 2);
			flecha.SetState(STATE_BOW_LEFT);
			break;
		default:
			correct = false;
			break;
		}
		if (correct) {
			Sound::getInstance()->playBow();
			actionFinished = false;
			cleanFrame();
			flecha.attack();
		}
	}
}


void cPlayer::setItemTexId(int id) {
	item_tex_id = id;
}

void cPlayer::setWeapon(int weapon) {
	usingWeapon = weapon;
}
void cPlayer::changeWeapon() {
	if (commandDelay == 0) {
		switch (usingWeapon)
		{
		case SWORD:
			usingWeapon = BOW;
			break;
		case BOW:
			usingWeapon = SWORD;
		default:
			break;
		}
		Sound::getInstance()->playWeaponChange();
		commandDelay = 20;
	}
}

void cPlayer::logic(vector<int> map, int width , vector<Enemy*> enemies){
	if (commandDelay > 0) --commandDelay;
	

	vector<cBicho*> bichos;
	for(int i =0; i < enemies.size(); ++i) {
		bichos.push_back(enemies[i]);
	}
	if(espada.isActive()) espada.Logic(map, width, bichos);
	if(flecha.isActive())flecha.Logic(map, width, bichos);
}

void cPlayer::attack() {
	switch (usingWeapon)
	{
	case SWORD:
		SwordAttack();
		break;
	case BOW:
		BowAttack();
		break;
	default:
		break;
	}

}

void cPlayer::hurt(int point) {
	cBicho::hurt(point);
	if (!alive) Sound::getInstance()->playLose();
}