#include "Weapon.h"



Weapon::Weapon()
{
}


Weapon::~Weapon()
{
}

/*
void Weapon::Logic(vector<int> map, int width, vector<Enemy*> enemies) {

}
*/

void Weapon::Draw() {

}

void Weapon::setAtk(int atk) {
	attackPower = atk;
}
int Weapon::getAtk() {
	return attackPower;
}