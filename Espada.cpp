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

		for (int i = 0; i < enemies.size() && enemy_id < 0; ++i)
		{
			cRect body;
			enemies[i]->GetArea(&body);
			if (Collides(&body)) {
				enemies[i]->hurt(attackPower);
				enemy_id = i;
				Sound::getInstance()->playHit();
				colision = true;
			}
		}

	if (enemy_id >= 0 && attackDelay < 11) {
		int ex, ey, ix, iy, ew, eh;
		enemies[enemy_id]->GetPosition(&ex, &ey);
		enemies[enemy_id]->GetWidthHeight(&ew, &eh);
		//player->GetPosition(&ix, &iy);
		ix = x + w / 2;
		iy = y + h / 2;
		if (ex+ ew/2 < ix) ex = ex - 1;
		else ex = ex + 1;
		if (ey +eh/2< iy) ey = ey - 1;
		else ey = ey + 1;
		enemies[enemy_id]->SetPosition(ex, ey);
		++attackDelay;

	}
	if (GetFrame() > 2) {
		actionFinished = true;
		if (enemy_id == -1 || attackDelay > 10)
		{
			active = false;
		}
	}
	NextFrame(4);


}
