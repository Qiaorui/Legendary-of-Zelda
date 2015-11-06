#include "cGame.h"
#include "Globals.h"


cGame::cGame(void)
{
}

cGame::~cGame(void)
{
}



void cGame::resize(int weight, int height) {
	int min;
	if (weight < height) min = weight;
	else min = height;
	glViewport((weight - min) / 2, (height - min) / 2, min, min);
}

bool cGame::Init()
{
	bool res=true;


	//Graphics initialization
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, GAME_WIDTH,0, GAME_HEIGHT,0,1);
	glMatrixMode(GL_MODELVIEW);
	
	glAlphaFunc(GL_GREATER, 0.05f);
	glEnable(GL_ALPHA_TEST);

	//Scene initialization
	res = Data.LoadImage(IMG_OVERLOAD,"LinkToPast-Overworld.png",GL_RGBA);
	if(!res) return false;
	res = Scene.LoadLevel(1);
	if(!res) return false;

	//Player initialization
	res = Data.LoadImage(IMG_PLAYER,"linkSprite_basic.png",GL_RGBA);
	res = Data.LoadImage(IMG_LIFE, "corazones_vida.png", GL_RGBA);
	if(!res) return false;
	Player.SetTile(4,1);
	Player.SetLife(3);
	Player.SetWidthHeight(32,32);
	Player.SetState(STATE_LOOKDOWN);
	Player.SetPosition(11*16, 16*16+8);

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
	
	if(keys[GLUT_KEY_UP])			Player.MoveUp(Scene.GetMap());
	else if (keys[GLUT_KEY_DOWN])	Player.MoveDown(Scene.GetMap());
	else if(keys[GLUT_KEY_LEFT])	Player.MoveLeft(Scene.GetMap());
	else if(keys[GLUT_KEY_RIGHT])	Player.MoveRight(Scene.GetMap());
	else Player.Stop();
	if (keys[GLUT_KEY_SPACEBAR])	Player.SwordAttack(Scene.GetMap());

	
	
	//Game Logic
	Player.Logic(Scene.GetMap());

	return res;
}


void setCamera(int x, int y) {
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(x - GAME_WIDTH / 2, x + GAME_WIDTH / 2, y - GAME_HEIGHT / 2, y + GAME_HEIGHT / 2, 0, 3);
	glMatrixMode(GL_MODELVIEW);
}


//Output
void cGame::Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	int x, y;
	Player.GetPosition(&x, &y);
	setCamera(x,y);

	glLoadIdentity();

	Scene.Draw(Data.GetID(IMG_OVERLOAD));
	Player.Draw(Data.GetID(IMG_PLAYER));
	Player.Draw(Data.GetID(IMG_LIFE));


	//TODO temporal lines to test
	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex2d(x - GAME_WIDTH / 2, y);
	glVertex2d(x + GAME_WIDTH / 2, y);


	glEnd();
	glColor3f(1, 1, 1);

	glutSwapBuffers();
}
