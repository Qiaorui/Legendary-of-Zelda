#pragma once


#include "Sound.h"
#include "Espada.h"
#include "Flecha.h"
#include "Enemy.h"


#define SWORD 0
#define BOW 1

class cPlayer: public cBicho
{
public:
	cPlayer();
	~cPlayer();

	void Draw(int tex_id);
	void DrawRect(int tex_id, float xo, float yo, float xf, float yf, int s, int frame);

	void DrawStatus(int cx, int cy);
	void SwordAttack();
	void BowAttack();
	void hurt(int point);
	void setItemTexId(int id);
	void setWeapon(int weapon);
	void changeWeapon();
    void logic(vector<int> map, int width , vector<Enemy*> enemies);
	void attack();

private:
	Espada espada;
	Flecha flecha;

	int usingWeapon;
	int item_tex_id;



};
