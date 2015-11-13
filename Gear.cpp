#include "Gear.h"



Gear::Gear()
{
	touched = false;
}


Gear::~Gear()
{
}

bool Gear::touch(cRect *rc)
{
	bool collidesX = (x < rc->right) && (x + w > rc->left);
	bool collidesY = (y + h / 2 <= rc->top) && (y + h / 2 >= rc->bottom);
	return collidesX && collidesY;
}

/*
void Gear::logic(cBicho* bicho) {
	cRect body;
	bicho->GetArea(&body);
	if (touch(&body)) {
		if (!touched) {
			Sound::getInstance()->playOpen();
			touched = true;
		}
		
	}
	else if (touched) {
		touched = false;
		Sound::getInstance()->playClose();
	}
}*/

void Gear::logic(vector<cBicho*> bichos) {
	bool b = false;
	cRect body;
	for (int i = 0; i < bichos.size() && !b; i++)
	{
		bichos[i]->GetArea(&body);
		if (touch(&body)) {
			b = true;
		}
	}
	touched = b;
}

void Gear::setSender(int id) {
	sender_id = id;
}
int Gear::getSender() {
	return sender_id;
}
bool Gear::isTouched() {
	return touched;
}