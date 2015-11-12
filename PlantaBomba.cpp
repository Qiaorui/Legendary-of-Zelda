#include "PlantaBomba.h"


PlantaBomba::PlantaBomba(){
	visible = true;
	Fire.push_back(new Fireball);
	Fire.push_back(new Fireball);
	Fire.push_back(new Fireball);
	Fire.push_back(new Fireball);
}
PlantaBomba::~PlantaBomba(){}

void PlantaBomba::Draw()
{
	if (alive) {
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

		if (GetFrame() == 2) xo = 504.0f / 840.0f + (GetFrame()*(bitx)) + 1.0f / 840.0f;
		else xo = 504.0f / 840.0f + (GetFrame()*(bitx));
		yo = 120.0f / 567.0f;
		NextFrame(3); // con 4 gira la cabeza
		yf = yo - bity;
		xf = xo + bitx;
		for (int i = 0; i < Fire.size(); ++i) {
			if (Fire[i]->isVisible()) Fire[i]->Draw(7);
		}
		DrawRect(tex_id, xo, yo, xf, yf, GetState(), frame);
	}
	else Enemy::Draw();
	
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


void PlantaBomba::Logic(vector<int> map, int width, cBicho* player) {
	FireAttack();
	
	
	Enemy::Logic(map,width, player);
	for (int i = 0; i < Fire.size(); ++i) {
		if (Fire[i]->isActive())Fire[i]->Logic(map, width, player);
	}
}

void PlantaBomba::FireAttack()
{
	for (int i = 0; i < Fire.size(); ++i) {
		if (!Fire[i]->isActive() && Fire[i]->isActionFinished()) {
			bool correct = true;

			Fire[i]->SetWidthHeight(10, 10);
			Fire[i]->SetPosition(x + 5, y + 10);
			if (i == 0)Fire[i]->SetState(STATE_BOW_DOWN);
			else if (i == 1)Fire[i]->SetState(STATE_BOW_UP);
			else if (i == 2)Fire[i]->SetState(STATE_BOW_RIGHT);
			else if (i == 3)Fire[i]->SetState(STATE_BOW_LEFT);
			Fire[i]->setAtk(1);

			if (correct) {
				Sound::getInstance()->playBow();
				actionFinished = false;
				cleanFrame();
				Fire[i]->attack();
			}
		}
	}
}