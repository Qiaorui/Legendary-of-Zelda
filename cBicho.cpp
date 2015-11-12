#include "cBicho.h"
#include "cScene.h"
#include "Globals.h"

cBicho::cBicho(void)
{
	seq=0;
	delay=0;
	speed = 2;
	actionFinished = true;
	//jumping = false;
}
cBicho::~cBicho(void){}

cBicho::cBicho(int posx,int posy,int width,int height, int life)
{
	x = posx;
	y = posy;
	w = width;
	h = height;
	this->life = life;
}
void cBicho::SetPosition(int posx,int posy)
{
	x = posx;
	y = posy;
}
void cBicho::GetPosition(int *posx,int *posy)
{
	*posx = x;
	*posy = y;
}
void cBicho::SetMaxLife(int life)
{
	maxLife = life;
	this->life = life;
	alive = life > 0;
}


int cBicho::getLife()
{
	return life;
	
}
void cBicho::SetTile(int tx,int ty)
{
	x = tx * TILE_SIZE;
	y = ty * TILE_SIZE;
}
void cBicho::GetTile(int *tx,int *ty)
{
	*tx = x / TILE_SIZE;
	*ty = y / TILE_SIZE;
}
void cBicho::SetWidthHeight(int width,int height)
{
	w = width;
	h = height;
}
void cBicho::GetWidthHeight(int *width,int *height)
{
	*width = w;
	*height = h;
}



bool cBicho::Collides(cRect *rc)
{
	bool collidesX = (x < rc->right) && (x + w > rc->left);
	bool collidesY = (y < rc->top) && (y + h > rc->bottom);
	return collidesX && collidesY;
}

void cBicho::GetArea(cRect *rc)
{
	rc->left   = x;
	rc->right  = x+w;
	rc->bottom = y;
	rc->top    = y+h;
}
bool cBicho::CollidesMapWall(vector<int> map, int direction, int width)
{
	int tile_x,tile_y;
	int i,j;
	int width_tiles,height_tiles;

	tile_x = x / TILE_SIZE;
	tile_y = y / TILE_SIZE;
	width_tiles  = w / TILE_SIZE ;
	height_tiles = h / TILE_SIZE ;

	switch (direction) {
	case UP:
		tile_y += height_tiles;
		//tile_x += width_tiles;
		if(x % TILE_SIZE > 0) ++width_tiles;
		break;
	case DOWN:
		//tile_y --;
		//tile_x += width_tiles;
		if (x % TILE_SIZE > 0) ++width_tiles;
		break;
	case LEFT:
		if (y % TILE_SIZE > 0) ++height_tiles;
		break;
	case RIGHT:
		tile_x += width_tiles;
		if (y % TILE_SIZE > 0) ++height_tiles;
		break;
	}


	if (direction == LEFT || direction == RIGHT) {
		for (j = 0; j<height_tiles; j++)
		{
			if (map[tile_x + ((tile_y + j)*width)])	return true;
		}
	}

	if (direction == UP || direction == DOWN) {
		for (j = 0; j<width_tiles; j++)
		{
			if (map[tile_x + j+ (tile_y*width)])	return true;
		}
	}


	return false;
}




void cBicho::DrawRect(int tex_id,float xo,float yo,float xf,float yf)
{
	int screen_x,screen_y;

	screen_x = x;
	screen_y = y;

	glEnable(GL_TEXTURE_2D);
	
	glBindTexture(GL_TEXTURE_2D,tex_id);
	glBegin(GL_QUADS);	
		glTexCoord2f(xo,yo);	glVertex2i(screen_x  ,screen_y);
		glTexCoord2f(xf,yo);	glVertex2i(screen_x+w,screen_y);
		glTexCoord2f(xf,yf);	glVertex2i(screen_x+w,screen_y+h);
		glTexCoord2f(xo,yf);	glVertex2i(screen_x  ,screen_y+h);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}

void cBicho::MoveLeft(vector<int> map, int width)
{
	int xaux;
	
	//Whats next tile?
	if( (x % TILE_SIZE) == 0)
	{
		xaux = x;
		x -= speed;

		if(CollidesMapWall(map,LEFT,width))
		{
			x = xaux;
			state = STATE_LOOKLEFT;
		}
	}
	//Advance, no problem
	else
	{
		x -= speed;
		if(state != STATE_WALKLEFT)
		{
			state = STATE_WALKLEFT;
			seq = 0;
			delay = 0;
		}
	}
}
void cBicho::MoveRight(vector<int> map, int width)
{
	int xaux;

	//Whats next tile?
	if( (x % TILE_SIZE) == 0)
	{
		xaux = x;
		x += speed;

		if(CollidesMapWall(map,RIGHT,width))
		{
			x = xaux;
			state = STATE_LOOKRIGHT;
		}
	}
	//Advance, no problem
	else
	{
		x += speed;
		
		if(state != STATE_WALKRIGHT)
		{
			state = STATE_WALKRIGHT;
			seq = 0;
			delay = 0;
		}
	}
}


void cBicho::MoveUp(vector<int> map, int width)
{
	int yaux;

	//Whats next tile?
	if ((y % TILE_SIZE) == 0)
	{
		yaux = y;
		y += speed;

		if (CollidesMapWall(map,UP,width))
		{
			y = yaux;
			state = STATE_LOOKUP;
		}
	}
	//Advance, no problem
	else
	{
		y += speed;

		if (state != STATE_WALKUP)
		{
			state = STATE_WALKUP;
			seq = 0;
			delay = 0;
		}
	}
}


void cBicho::MoveDown(vector<int> map, int width)
{
	int yaux;

	//Whats next tile?
	if ((y % TILE_SIZE) == 0)
	{
		yaux = y;
		y -= speed;

		if (CollidesMapWall(map, DOWN, width))
		{
			y = yaux;
			state = STATE_LOOKDOWN;
		}
	}
	//Advance, no problem
	else
	{
		y -= speed;

		if (state != STATE_WALKDOWN)
		{
			state = STATE_WALKDOWN;
			seq = 0;
			delay = 0;
		}
	}
}


void cBicho::Stop()
{
	switch (state)
	{
	case STATE_WALKLEFT:	state = STATE_LOOKLEFT;		break;
	case STATE_WALKRIGHT:	state = STATE_LOOKRIGHT;	break;
	case STATE_WALKUP:	    state = STATE_LOOKUP;		break;
	case STATE_WALKDOWN:	state = STATE_LOOKDOWN;	    break;
	}

	/*if(state == STATE_SWORD_DOWN && seq==6)	state = STATE_LOOKDOWN;	
	else if(state == STATE_SWORD_LEFT && seq ==6)state = STATE_LOOKLEFT;		
	else if (state == STATE_SWORD_RIGHT && seq == 6)	state = STATE_LOOKRIGHT;
	else if (state == STATE_SWORD_UP && seq == 6)	state = STATE_LOOKUP;*/
	
}



void cBicho::Logic(vector<int> map, int width)
{
	/*
	float alfa;

	if(jumping)
	{
		jump_alfa += JUMP_STEP;
		
		if(jump_alfa == 180)
		{
			jumping = false;
			y = jump_y;
		}
		else
		{
			alfa = ((float)jump_alfa) * 0.017453f;
			y = jump_y + (int)( ((float)JUMP_HEIGHT) * sin(alfa) );
		
			if(jump_alfa > 90)
			{
				//Over floor?
				jumping = !CollidesMapFloor(map);
			}
		}
	}
	else
	{
		//Over floor?
		if(!CollidesMapFloor(map))
			y -= (2*STEP_LENGTH);
	}*/
}
void cBicho::NextFrame(int max)
{
	delay++;
	if(delay >= FRAME_DELAY)
	{
		seq++;
		seq%=max;
		delay = 0;
	}
}
int cBicho::GetFrame()
{
	return seq;
}
int cBicho::GetState()
{
	return state;
}
void cBicho::SetState(int s)
{
	state = s;
}

void cBicho::setVisible(bool b) {
	visible = b;
}

bool cBicho::isVisible() {
	return visible;
}


void cBicho::setActive(bool b) {
	active = b;
}

bool cBicho::isActive() {
	return active;
}

void cBicho::setAlive(bool b) {
	alive = b;
}
bool cBicho::isAlive() {
	return alive;
}
void cBicho::hurt(int point) {
	life = life - point;
	if (life <= 0) {
		alive = false;
	}
}

void cBicho::cleanFrame() {
	seq = 0;
}

void cBicho::setActionFinished(bool b) {
	actionFinished = b;
}
bool cBicho::isActionFinished() {
	return actionFinished;
}

int  cBicho::getMaxLife() {
	return maxLife;
}


int cBicho::getCurrentSceneId() {
	return current_scene_id;
}

void cBicho::setCurrentSceneId(int scene_id) {
	current_scene_id = scene_id;
}

void cBicho::stepBack() {
	switch (state)
	{
	case STATE_WALKDOWN:
		y += speed;
		break;
	case STATE_WALKUP:
		y -= speed;
		break;
	case STATE_WALKLEFT:
		x += speed;
	case STATE_WALKRIGHT:
		x -= speed;
	default:
		break;
	}
}