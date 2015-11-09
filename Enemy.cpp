#include "Enemy.h"



Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::Draw() {
	exit(0);
}

void Enemy::DrawRect(int tex_id, float xo, float yo, float xf, float yf, int s, int frame) {


}


void Enemy::Logic(vector<int> map, int width) {

}


void Enemy::setImage(int tex_id) {
	this->tex_id = tex_id;
}