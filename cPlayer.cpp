
#include "cPlayer.h"

cPlayer::cPlayer() {}
cPlayer::~cPlayer(){}

void cPlayer::Draw(int tex_id)
{	
	float xo,yo,xf,yf;
	xf = yf = -1;
	//BLOCK_SIZE = 16, FILE_SIZE = 432
	// 16 / 432 = 0.037
	//N = 15, (FILE_SIZE-15*BLOCK_SIZE)/14 = 13.714  =>0.0317
	float bitx = 16.0f/432.0f;
	//BLOCK_SIZE = 16, FILE_SIZE = 303
	// 16 / 303 = 0.053
	float bity = 16.0f/303.0f;

	switch(GetState())
	{
		//1
		case STATE_LOOKLEFT:	xo = 30.0f/432.0f;
								yo = bity;
								break;
		//4
		case STATE_LOOKRIGHT:	xo = 90.0f/432.0f;	
								yo =  45.0f/303.0f;
								break;
		//1..3
		case STATE_WALKLEFT:	xo = 30.0f/432.0f;
								yo =  bity + (GetFrame()*(30.0f/303.0f));
								NextFrame(2);
								break;
		//4..6
		case STATE_WALKRIGHT:	xo =90.0f/432.0f;
								yo =  bity + (GetFrame()*(30.0f/303.0f));
								NextFrame(2);
								break;

    	case STATE_LOOKUP:      xo = 60.0f/ 432.0f;
								yo = bity;
								break;

		case STATE_LOOKDOWN:    xo = 0.0f / 432.0f;
								yo = bity;
								break;

		case STATE_WALKUP:		xo = 60.0f / 432.0f;
								yo = bity + (GetFrame()*(30.0f / 303.0f));
							    NextFrame(2);
								break;

		case STATE_WALKDOWN:    xo = 0.0f / 432.0f;
								yo = bity + (GetFrame()*(30.0f / 303.0f));
								NextFrame(2);
								break;

		//player has atacking movement, so has to add frame

		case STATE_SWORD_DOWN:  xo = 0.0f / 432.0f;	
								yo = 75.0f/303.0f + (GetFrame()*(36.0f / 303.0f));
								xf = xo + bitx;
								yf = yo - bity - (GetFrame()*(11.0f / 303.0f));
								NextFrame(2);
								break;

		case STATE_SWORD_LEFT:  xo = 30.0f / 432.0f - (GetFrame()*(6.0f / 303.0f));
								yo = 75.0f / 303.0f + (GetFrame()*(29.0f / 303.0f));
								xf = xo + bitx + (GetFrame()*(10.0f / 303.0f));
								yf = yo - bity;
								NextFrame(2);
								break;

		case STATE_SWORD_UP:    xo = 60.0f / 432.0f;
								yo = 75.0f / 303.0f + (GetFrame()*(36.0f / 303.0f));
								xf = xo + bitx;
								yf = yo - bity - (GetFrame()*(11.0f / 303.0f));
								NextFrame(2);
								break;

		case STATE_SWORD_RIGHT: xo = 90.0f / 432.0f - (GetFrame()*(6.0f / 303.0f));
								yo = 75.0f / 303.0f + (GetFrame()*(29.0f / 303.0f));
								xf = xo + bitx + (GetFrame()*(10.0f / 303.0f));
								yf = yo - bity;
								NextFrame(2); 
								break;

		//default:			xo = 91.0f/432.0f; yo = bity; break;
	}

	//When we are not atacking 
	if (xf == -1 && yf == -1) {
		xf = xo + bitx;
		yf = yo - bity;
		
	}

	DrawRect(tex_id, xo, yo, xf, yf);

}
