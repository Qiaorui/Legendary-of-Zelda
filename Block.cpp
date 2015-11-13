#include "Block.h"



Block::Block()
{
	Trigger::Trigger();
	wall = true;
	speed = 1;
}


Block::~Block()
{
}

bool Block::Collides(cRect *rc)
{
	bool collidesX = (x < rc->left+15) && (x + w > rc->left);
	bool collidesY = (y < rc->bottom+15) && (y + h > rc->bottom);
	return collidesX && collidesY;
}


void Block::logic(cBicho* bicho, vector<int> map, int width) {
	if (commandDelay > 0) --commandDelay;
	cRect body;
	bicho->GetArea(&body);
	if (Collides(&body)) {
		switch (bicho->GetState())
		{
		case STATE_WALKDOWN:
			MoveDown(map, width);
			break;
		case STATE_WALKUP:
			MoveUp(map, width);
			break;
		case STATE_WALKLEFT:
			MoveLeft(map, width);
			break;
		case STATE_WALKRIGHT:
			MoveRight(map, width);
			break;
		default:
			break;
		}
		if (commandDelay == 0) {
			commandDelay = 20;
			Sound::getInstance()->playPush();
		}

		if(wall) bicho->stepBack();
	}
}