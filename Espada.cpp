#include "Espada.h"



Espada::Espada()
{
	delayespada = 10;
	active = 1;
}


Espada::~Espada()
{
}

void Espada::Logic(vector<int> map, cPlayer* player, vector<Enemy*> enemies)
{
	int  l;
	bool colision = false;
	if (delayespada >= 10) {
		for (int i = 0; i < enemies.size(); ++i)
		{
			cRect body;
			enemies[i]->GetArea(&body);
			if (Collides(&body)) {
				delayespada = 0;
				enemies[i]->GetLife(&l);
				enemies[i]->SetLife(l - 1);
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
		player->GetPosition(&ix, &iy);
		if (ex < ix) ex = ex - 1;
		else ex = ex + 1;
		if (ey < iy) ey = ey - 1;
		else ey = ey + 1;
		enemies[id]->SetPosition(ex, ey);
		++delayespada;
		if (delayespada == 10)active = false;
	}
}