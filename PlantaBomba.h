#pragma once
#include "cBicho.h"
class PlantaBomba :
	public cBicho
{
public:
	PlantaBomba();
	~PlantaBomba();

void Draw(int tex_id);
	void DrawRect(int tex_id, float xo, float yo, float xf, float yf, int s, int frame);

	void DrawLife(int tex_id);


	void setCurrentSceneId(int scene_id);
	void Logic(vector<int> map, int width);
	int getCurrentSceneId();

private:
	int current_scene_id;
	int delaymove;
};