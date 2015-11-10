#include "Espada.h"



Espada::Espada()
{
	attackDelay = 10;
	active = false;
}


Espada::~Espada()
{

}

void Espada::Logic(vector<int> map, int width, vector<cBicho*> enemies)
{

	bool colision = false;
	if (attackDelay >= 10) {
		for (int i = 0; i < enemies.size(); ++i)
		{
			cRect body;
			enemies[i]->GetArea(&body);
			if (Collides(&body)) {
				attackDelay = 0;
				enemies[i]->hurt(attackPower);
				id = i;
				Sound::getInstance()->playHit();
				colision = true;
			}
		}
		if (!colision) active = false;
	}
	else {
		int ex, ey, ix, iy;
		enemies[id]->GetPosition(&ex, &ey);
		//player->GetPosition(&ix, &iy);
		ix = x + w / 2;
		iy = y + h / 2;
		if (ex < ix) ex = ex - 1;
		else ex = ex + 1;
		if (ey < iy) ey = ey - 1;
		else ey = ey + 1;
		enemies[id]->SetPosition(ex, ey);
		++attackDelay;
		if (attackDelay == 10)active = false;
	}


}
