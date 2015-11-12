#include "Sender.h"


Sender::Sender() {

}

Sender::Sender(int scene, int x, int y, int state)
{
	wall = false;
	sentToScene = scene;
	sentToX = x;
	sentToY = y;
	newDirection = state;
	active = true;
	visible = true;
}


Sender::~Sender()
{
}

void Sender::draw(int tex_id) {
	Trigger::draw(tex_id);
}


bool Sender::Collides(cRect *rc)
{
	bool collidesX = (x < rc->right) && (x + w > rc->left);
	bool collidesY = (y+h/2 <= rc->top) && (y + h/2 >= rc->bottom);
	return collidesX && collidesY;
}


void Sender::logic(cBicho* player) {
	cRect body;
	player->GetArea(&body);
	if (Collides(&body)) {
		if (!wall) {
			Sound::getInstance()->playBgm(sentToScene);
			Sound::getInstance()->playDoor();
			player->setCurrentSceneId(sentToScene);
			player->SetTile(sentToX, sentToY);
			player->SetState(newDirection);
		}
		else {
			player->stepBack();
		}
	}
}

void Sender::setCloseImage(float xo, float xf, float yo, float yf) {
	closexo = xo;
	closexf = xf;
	closeyo = yo;
	closeyf = yf;
}

void swap(float& a, float& b) {
	float tmp = a;
	a = b;
	b = tmp;
}

void Sender::switchState() {
	swap(xo, closexo);
	swap(yo, closeyo);
	swap(xf, closexf);
	swap(yf, closeyf);
	wall = !wall;
}