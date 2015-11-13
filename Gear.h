#pragma once
#include "Trigger.h"
class Gear :
	public Trigger
{
public:
	Gear();
	~Gear();
	//void logic(cBicho* bicho);
	void logic(vector<cBicho*> bichos);
	void setSender(int id);
	int getSender();
	bool isTouched();


private:
	bool touched;
	int sender_id;

	bool touch(cRect* rect);
};



