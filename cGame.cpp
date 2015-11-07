#include "cGame.h"
#include "Globals.h"
#include "irrKlang.h"
#pragma comment(lib, "irrklang.lib")
cGame::cGame(void)
{
}

cGame::~cGame(void)
{
}



void cGame::resize(int width, int height) {
	int min;
	if (width < height) min = width;
	else min = height;
	glViewport((width - min) / 2, (height - min) / 2, min, min);
}

bool cGame::Init()
{
	bool res=true;


	//Graphics initialization
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 36*16,0, 28*16,0,1);
	glMatrixMode(GL_MODELVIEW);
	
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	//Scene initialization
	res = Data.LoadImage(IMG_OVERLOAD,"LinkToPast-Overworld.png",GL_RGBA);
	if(!res) return false;
	Scene[0].initialize(36,28);
	res = Scene[0].LoadLevel(1);
	if(!res) return false;
	//sound init
	irrklang::ISoundEngine* engine = irrklang::createIrrKlangDevice();
	engine->play2D("resource/04.-overworld.mp3", true);

	//Player initialization
	res = Data.LoadImage(IMG_PLAYER,"linkSprite_basic.png",GL_RGBA);
	res = Data.LoadImage(IMG_LIFE, "corazones_vida.png", GL_RGBA);
	if(!res) return false;
	Player.SetTile(11,16);
	Player.SetLife(3);
	Player.SetWidthHeight(16,25);
	Player.SetState(STATE_LOOKDOWN);
	//Player.SetPosition(11*16, 16*16+8);
	Player.setCurrentSceneId(0);
	//Enemies initialization
	res = Data.LoadImage(IMG_ENEMIES, "Enemies.png", GL_RGBA);
	if (!res) return false;
	Soldier.SetTile(12, 18);
	Soldier.SetLife(3);
	Soldier.SetWidthHeight(16, 28);
	Soldier.SetState(STATE_LOOKRIGHT);
	return res;
}

bool cGame::Loop()
{
	bool res=true;

	res = Process();
	if(res) Render();

	return res;
}

void cGame::Finalize()
{
}

//Input
void cGame::ReadKeyboard(unsigned char key, int x, int y, bool press)
{
	keys[key] = press;
}

void cGame::ReadMouse(int button, int state, int x, int y)
{
}

//Process
bool cGame::Process()
{
	bool res=true;
	
	//Process Input
	if(keys[27])	res=false;
	
	int id = Player.getCurrentSceneId();
	int w, h;
	w = Scene[id].getWidth();
	h = Scene[id].getHeight();

	if(keys[GLUT_KEY_UP])			Player.MoveUp(Scene[id].GetMap(), w );
	else if (keys[GLUT_KEY_DOWN])	Player.MoveDown(Scene[id].GetMap(), w );
	else if(keys[GLUT_KEY_LEFT])	Player.MoveLeft(Scene[id].GetMap(), w );
	else if(keys[GLUT_KEY_RIGHT])	Player.MoveRight(Scene[id].GetMap(), w );
	else Player.Stop();
	if (keys[GLUT_KEY_SPACEBAR])	Player.SwordAttack();

	
	
	//Game Logic
	Player.Logic(Scene[id].GetMap(), w );
	Soldier.Logic(Scene[id].GetMap(), w);
	return res;
}


void setCamera(int x, int y) {
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(x - GAME_WIDTH / 2, x + GAME_WIDTH / 2, y - GAME_HEIGHT / 2, y + GAME_HEIGHT / 2, 0, 1);
	glMatrixMode(GL_MODELVIEW);
}


//Output
void cGame::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	

	int id = Player.getCurrentSceneId();
	int x, y;
	Player.GetPosition(&x, &y);
	int w, h;
	Player.GetWidthHeight(&w, &h);
	//Setting camera
	int cx, cy;
	if ((x+w/2 - GAME_WIDTH / 2) < 0 ) cx = GAME_WIDTH / 2;
	else if ((x+w/2 + GAME_WIDTH / 2) > Scene[id].getWidth() * TILE_SIZE) cx = Scene[id].getWidth() * TILE_SIZE - GAME_WIDTH / 2;
	else cx = x+w/2;
	if ((y +h/2- GAME_HEIGHT/2) < 0 ) cy = GAME_HEIGHT/2;
	else if ( (y+h/2 + GAME_HEIGHT/2)> Scene[id].getHeight() * TILE_SIZE) cy = Scene[id].getHeight() *TILE_SIZE - GAME_HEIGHT/2;
	else cy = y+h/2;
	setCamera(cx,cy);



	glLoadIdentity();
	Scene[0].Draw(Data.GetID(IMG_OVERLOAD));
	Player.Draw(Data.GetID(IMG_PLAYER));
	Player.DrawLife(Data.GetID(IMG_LIFE));
	Soldier.Draw(Data.GetID(IMG_ENEMIES));


	//TODO temporal lines to test
	glBegin(GL_LINES);
	glColor3f(1,0,0);
	glVertex2d(x,y+h);
	glVertex2d(x+w,y+h);
	glVertex2d(x+w,y);
	glVertex2d(x+w,y+h);
	glColor3f(1, 1, 0);
	glVertex2d(x - GAME_WIDTH / 2, y);
	glVertex2d(x + GAME_WIDTH / 2, y);
	glColor3f(0, 1, 0);
	glVertex2d(x, y - GAME_HEIGHT/2);
	glVertex2d(x, y + GAME_HEIGHT/2);
	glEnd();
	glColor3f(1, 1, 1);
	//TODO

	glutSwapBuffers();
}
