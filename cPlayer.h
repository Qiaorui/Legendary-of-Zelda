#pragma once


#include "Sound.h"
#include "Espada.h"
#include "Flecha.h"
#include "Enemy.h"

#define PLAYER_START_CX		3
#define PLAYER_START_CY		2

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
	//void DrawObject(int tex_id, int cx, int cy);
	void SwordAttack();
	void BowAttack();
	void hurt(int point);
	//void setLifeTexId(int id);
	void setItemTexId(int id);
	void setWeapon(int weapon);
	void changeWeapon();
    void logic(vector<int> map, int width , vector<Enemy*> enemies);
	void attack();

private:
	Espada espada;
	Flecha flecha;

	int usingWeapon;
	//int life_tex_id;
	int item_tex_id;



};
