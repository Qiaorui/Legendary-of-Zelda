#include "Boss.h"



Boss::Boss()
{
}


Boss::~Boss()
{
}
void Boss::Draw()
{
	if (alive) {
		//if (tex_id == 2) {
		float xo, yo, xf, yf;
		xf = yf = -1;
		//BLOCK_SIZE = 16, FILE_SIZE = 432
		// 16 / 432 = 0.037
		//N = 15, (FILE_SIZE-15*BLOCK_SIZE)/14 = 13.714  =>0.0317
		float  bitx = 32.0f / 233.0f;;
		//BLOCK_SIZE = 16, FILE_SIZE = 303
		// 16 / 303 = 0.053
		float bity = 53.0f / 243.0f;
		int frame = GetFrame();

		switch (GetState())
		{

		case STATE_LOOKDOWN:    xo = GetFrame()*(bitx);
			yo = bity;
			NextFrame(4);
			break;


			//default:			xo = 91.0f/432.0f; yo = bity; break;
		}

		//When we are not atacking 
		xf = xo + bitx;
		yf = yo - bity;

		DrawRect(tex_id, xo, yo, xf, yf, GetState(), frame);
	}
	else Enemy::Draw();
	//}
	//else {
	//	DrawLife(tex_id);
	//}

	//DrawRect(tex_id, 16.0f / 840.0f, 71.0 / 567.0f, 31.0f / 840.0f, 44.0f / 567.0f, 0, 0);
}

void Boss::DrawRect(int tex_id, float xo, float yo, float xf, float yf, int s, int frame)
{
	int screen_x, screen_y;
	int x, y;
	int w, h;

	GetPosition(&x, &y);
	GetWidthHeight(&w, &h);
	screen_x = x;
	screen_y = y;


	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, tex_id);
	glBegin(GL_QUADS);

	glTexCoord2f(xo, yo);	glVertex2i(screen_x, screen_y);  //Left Down
	glTexCoord2f(xf, yo);	glVertex2i(screen_x + w, screen_y); //right down
	glTexCoord2f(xf, yf);	glVertex2i(screen_x + w, screen_y + h); //right up
	glTexCoord2f(xo, yf);	glVertex2i(screen_x, screen_y + h); //left up
	glEnd();

	glDisable(GL_TEXTURE_2D);
}




void Boss::Logic(vector<int> map, int width, cBicho* player) {
	
	Enemy::Logic(map, width, player);

}