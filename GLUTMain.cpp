
#include "Globals.h"
#include "cGame.h"

//Delete console
#pragma comment(linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"")

cGame Game;

void AppRender()
{
	Game.Render();
}
void AppKeyboard(unsigned char key, int x, int y)
{
	Game.ReadKeyboard(key,x,y,true);
}
void AppKeyboardUp(unsigned char key, int x, int y)
{
	Game.ReadKeyboard(key,x,y,false);
}
void AppSpecialKeys(int key, int x, int y)
{
	Game.ReadKeyboard(key,x,y,true);
}
void AppSpecialKeysUp(int key, int x, int y)
{
	Game.ReadKeyboard(key,x,y,false);
}
void AppMouse(int button, int state, int x, int y)
{
	Game.ReadMouse(button,state,x,y);
}
void AppIdle()
{
	int t1, t2;
	t1=glutGet(GLUT_ELAPSED_TIME);
	if(!Game.Loop()) exit(0);
	t2 = glutGet(GLUT_ELAPSED_TIME);
	while (t2-t1 < 20) { //1000/20 = 50fps
		t2 =glutGet(GLUT_ELAPSED_TIME);
	}
}

void AppResize(int width, int height) {
	Game.resize(width, height);
}

void main(int argc, char** argv)
{
	int res_x,res_y,pos_x,pos_y;

	//GLUT initialization
	glutInit(&argc, argv);

	//RGBA with double buffer
	glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE);

	//Create centered window
	res_x = glutGet(GLUT_SCREEN_WIDTH);
	res_y = glutGet(GLUT_SCREEN_HEIGHT);
	pos_x = (res_x>>1)-(GAME_WIDTH);
	pos_y = (res_y>>1)-(GAME_HEIGHT);
	
	glutInitWindowPosition(pos_x,pos_y);
	glutInitWindowSize(GAME_WIDTH*2,GAME_HEIGHT*2);
	glutCreateWindow("Legendary of Zelda - Link to the Dark Soul");

	/*glutGameModeString("800x600:32");
	glutEnterGameMode();*/

	//Make the default cursor disappear
	//glutSetCursor(GLUT_CURSOR_NONE);

	//Register callback functions
	glutReshapeFunc(AppResize);
	glutDisplayFunc(AppRender);			
	glutKeyboardFunc(AppKeyboard);		
	glutKeyboardUpFunc(AppKeyboardUp);	
	glutSpecialFunc(AppSpecialKeys);	
	glutSpecialUpFunc(AppSpecialKeysUp);
	glutMouseFunc(AppMouse);
	glutIdleFunc(AppIdle);

	//Game initializations
	Game.Init();

	//Application loop
	glutMainLoop();	
}


//uservj03:yoMeta9n1y