#include "Weapon.h"



Weapon::Weapon()
{
}


Weapon::~Weapon()
{
}


void Weapon::Logic(vector<int> map, int width, vector<cBicho*> enemies) {

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