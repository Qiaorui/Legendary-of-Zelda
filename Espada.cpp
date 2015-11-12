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


	Weapon::Logic(map, width, enemies);
	if (GetFrame() > 2) {
		actionFinished = true;
		if (enemy_id == -1 || attackDelay > 10)
		{
			active = false;
		}
	}
	NextFrame(4);


}
