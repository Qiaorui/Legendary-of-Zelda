#include "Sender.h"



Sender::Sender(int scene, int x, int y, int state)
{
	sentToScene = scene;
	sentToX = x;
	sentToY = y;
	newDirection = state;
}


Sender::~Sender()
{
}

void Sender::draw() {
	DrawRect(tex_id, xo, yo, xf, yf);
}

void Sender::setImage(float xo, float xf, float yo, float yf, int tex_id) {
	this->xo = xo;
	this->xf = xf;
	this->yo = yo;
	this->yf = yf;
	this->tex_id = tex_id;
}

void Sender::logic(cPlayer* player) {
	cRect body;
	player->GetArea(&body);

	if (Collides(&body)) {
		player->setCurrentSceneId(sentToScene);
		player->SetTile(sentToX, sentToY);
		player->SetState(newDirection);
	}
}