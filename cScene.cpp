#include "cScene.h"
#include "Globals.h"

cScene::cScene(void)
{
}

cScene::~cScene(void)
{
}

bool cScene::LoadLevel(int level)
{
	bool res;
	FILE *fd;
	char file[16];
	int i,j,px,py;
	char tile = ' ';
	float coordx_tile, coordy_tile;
	int row, column;
	float h = 16.0f / 384.0f;
	float w = 16.0f / 208.0f;
	res=true;
	string buffer = "";
	if(level<10) sprintf(file,"%s0%d%s",(char *)FILENAME,level,(char *)FILENAME_EXT);
	else		 sprintf(file,"%s%d%s",(char *)FILENAME,level,(char *)FILENAME_EXT);

	fd=fopen(file,"r");
	if(fd==NULL) return false;

	id_DL=glGenLists(1);
	glNewList(id_DL,GL_COMPILE);
		glBegin(GL_QUADS);
	
			for(j=SCENE_HEIGHT-1;j>=0;j--)
			{
				px=SCENE_Xo;
				py=SCENE_Yo+(j*TILE_SIZE);

				for(i=0;i<SCENE_WIDTH;i++)
				{
					while (tile != '(') {
						fscanf(fd, "%c", &tile);
					}				
					while (tile != ',') {
						fscanf(fd, "%c", &tile);
						buffer += tile;
					}
					row = stoi(buffer);
					buffer.clear();
					while (tile != ')') {
						fscanf(fd, "%c", &tile);
						buffer += tile;
					}
					column = stoi(buffer);
					buffer.clear();
					/*if(tile==' ')
					{
						//Tiles must be != 0 !!!
						map[(j*SCENE_WIDTH)+i]=0;
					}*/
	
					//Tiles = 1,2,3,...
					if (row == 0 && column == 3) {
						int tmp = rand() % 16;
						switch (tmp)
						{
						case 0:
							column = 3;
							row = 1;
							break;
						case 1:
							column = 3;
							row = 2;
							break;
						/*case 2:
							column = 4;
							row = 2;
							break;
						case 3:
							column = 5;
							row = 2;
							break;*/
						case 4:
							column = 7;
							row = 0;
							break;
						case 5:
							column = 7;
							row = 1;
							break;
						default:
							break;
						}
					}
					

					map[(j*SCENE_WIDTH) + i] = (row*13)+column;

					coordx_tile = column*w;
					coordy_tile = row*h;
					
					glTexCoord2f(coordx_tile, coordy_tile + h);	glVertex2i(px, py);
					glTexCoord2f(coordx_tile + w, coordy_tile + h);	glVertex2i(px + 16, py);
					glTexCoord2f(coordx_tile + w, coordy_tile);	glVertex2i(px + 16, py + 16);
					glTexCoord2f(coordx_tile, coordy_tile);	glVertex2i(px, py + 16);

					/*
					if (map[(j*SCENE_WIDTH) + i] % 2) coordx_tile = 0.0f;
					else						 coordx_tile = 0.5f;
					if (map[(j*SCENE_WIDTH) + i]<3) coordy_tile = 0.0f;
					else						 coordy_tile = 0.5f;

					//BLOCK_SIZE = 24, FILE_SIZE = 64
					// 24 / 64 = 0.375
					glTexCoord2f(coordx_tile, coordy_tile + 0.375f);	glVertex2i(px, py);
					glTexCoord2f(coordx_tile + 0.375f, coordy_tile + 0.375f);	glVertex2i(px + BLOCK_SIZE, py);
					glTexCoord2f(coordx_tile + 0.375f, coordy_tile);	glVertex2i(px + BLOCK_SIZE, py + BLOCK_SIZE);
					glTexCoord2f(coordx_tile, coordy_tile);	glVertex2i(px, py + BLOCK_SIZE);
					*/

					px+=TILE_SIZE;
				}
				fscanf(fd,"%c",&tile); //pass enter
			}

		glEnd();
	glEndList();

	fclose(fd);

	return res;
}

void cScene::Draw(int tex_id)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,tex_id);
	glCallList(id_DL);
	glDisable(GL_TEXTURE_2D);
}
int* cScene::GetMap()
{
	return map;
}