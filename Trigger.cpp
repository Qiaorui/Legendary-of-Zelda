#include "Trigger.h"



Trigger::Trigger()
{
	wall = false;
	active = true;
	visible = true;
}


Trigger::~Trigger()
{
}

void Trigger::draw(int tex_id) {
	DrawRect(tex_id, xo, yo, xf, yf);
}

void Trigger::setImage(float xo, float xf, float yo, float yf) {
	this->xo = xo;
	this->xf = xf;
	this->yo = yo;
	this->yf = yf;
}

void Trigger::setWall(bool b) {
	wall = true;
}
bool Trigger::isWall() {
	return wall;
}

void Trigger::logic(cBicho* player) {

}

int Trigger::getId() {
	return id;
}