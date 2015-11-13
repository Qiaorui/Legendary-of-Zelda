#include "Weapon.h"



Weapon::Weapon()
{
}


Weapon::~Weapon()
{
}


void Weapon::Logic(vector<int> map, int width, vector<cBicho*> enemies) {
	for (int i = 0; i < enemies.size() && enemy_id < 0; ++i)
	{
		cRect body;
		enemies[i]->GetArea(&body);
		if (Collides(&body)) {
			enemies[i]->hurt(attackPower);
			enemy_id = i;
			Sound::getInstance()->playHit();
		}
	}

	if (enemy_id >= 0 && attackDelay < 11) {
		int ex, ey, ix, iy, ew, eh;
		enemies[enemy_id]->GetPosition(&ex, &ey);
		enemies[enemy_id]->GetWidthHeight(&ew, &eh);
		//player->GetPosition(&ix, &iy);
		ix = x + w / 2;
		iy = y + h / 2;
		if (ex + ew / 2 < ix) ex = ex - 1;
		else ex = ex + 1;
		if (ey + eh / 2< iy) ey = ey - 1;
		else ey = ey + 1;
		enemies[enemy_id]->SetPosition(ex, ey);
		++attackDelay;

	}
}

void Weapon::Logic(vector<int> map, int width, cBicho* player) {

	cRect body;
	player->GetArea(&body);
	if (Collides(&body) && enemy_id == -1) {
		player->hurt(attackPower);
		enemy_id = 1;
		Sound::getInstance()->playHit();
	}


	if (enemy_id >= 1 && attackDelay < 11) {
		int ex, ey, ix, iy, ew, eh;
		player->GetPosition(&ex, &ey);
		player->GetWidthHeight(&ew, &eh);
		ix = x + w / 2;
		iy = y + h / 2;
		if (ex + ew / 2 < ix) ex = ex - 1;
		else ex = ex + 1;
		if (ey + eh / 2< iy) ey = ey - 1;
		else ey = ey + 1;
		player->SetPosition(ex, ey);
		++attackDelay;
	}

}

void Weapon::Draw() {

}

void Weapon::setAtk(int atk) {
	attackPower = atk;
}
int Weapon::getAtk() {
	return attackPower;
}

void Weapon::attack() {
	active = true;
	actionFinished = false;
	attackDelay = 0;
	cleanFrame();
	enemy_id = -1;
}