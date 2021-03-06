#include "cScene.h"
#include "Globals.h"

cScene::cScene(void)
{
}

cScene::~cScene(void)
{
}

void cScene::initialize(int w, int h) {
	width = w;
	height = h;
	map.resize(w*h);
}

bool cScene::LoadLevel(int level, float tilewidth, float tileheight)
{
	bool res;
	FILE *fd;
	char file[16];
	int i, j, px, py;
	char tile = ' ';
	float coordx_tile, coordy_tile;
	int row, column;
	float h = 16.0f / tileheight;
	float w = 16.0f / tilewidth;
	res = true;
	string buffer = "";
	if (level<10) sprintf(file, "%s0%d%s", (char *)FILENAME, level, (char *)FILENAME_EXT);
	else		 sprintf(file, "%s%d%s", (char *)FILENAME, level, (char *)FILENAME_EXT);

	fd = fopen(file, "r");
	if (fd == NULL) return false;

	id_DL = glGenLists(1);
	glNewList(id_DL, GL_COMPILE);
	glBegin(GL_QUADS);

	for (j = height - 1; j >= 0; j--)
	{
		px = 0;
		py = 0 + (j*TILE_SIZE);

		for (i = 0; i<width; i++)
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

			if (row == 0 && column == 3 && level == 1) {
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

			if (level == 1) {
				if (row < 4) map[(j*width) + i] = 0;
				else map[(j*width) + i] = 1;
			}
			else {
				if (row < 7) map[(j*width) + i] = 0;
				else map[(j*width) + i] = 1;
			}

			coordx_tile = column*w;
			coordy_tile = row*h;

			glTexCoord2f(coordx_tile, coordy_tile + h);	glVertex2i(px, py);
			glTexCoord2f(coordx_tile + w, coordy_tile + h);	glVertex2i(px + 16, py);
			glTexCoord2f(coordx_tile + w, coordy_tile);	glVertex2i(px + 16, py + 16);
			glTexCoord2f(coordx_tile, coordy_tile);	glVertex2i(px, py + 16);

			px += TILE_SIZE;
		}
		fscanf(fd, "%c", &tile); //pass enter
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

	for (int i = 0; i < gears.size(); i++)
	{
		if (gears[i].isVisible()) {
			gears[i].draw(tex_id);
		}
	}
	for (int i = 0; i < senders.size(); i++)
	{
		if(senders[i].isVisible()) senders[i].draw(tex_id);
	}
	for (int i = 0; i < blocks.size(); i++)
	{
		if (blocks[i].isVisible()) blocks[i].draw(tex_id);
	}

	for (int i = 0; i < enemies.size(); i++)
	{
		if(enemies[i]->isVisible()) enemies[i]->Draw();
		//if (!enemies[i]->isVisible()) enemies.erase(enemies.begin() + i);
	}


}
vector<int> cScene::GetMap()
{
	return map;
}

int cScene::getWidth(){
	return width;
}

int cScene::getHeight(){
	return height;
}

void cScene::setWidth(int w) {
	width = w;
}

void cScene::setHeight(int h) {
	height = h;
}

int cScene::addSender(int x, int y, int scene, int ToX, int ToY, int state, float xo, float xf, float yo, float yf, int w, int h) {
	Sender sender(scene, ToX, ToY, state);
	sender.SetTile(x, y);
	sender.SetWidthHeight(w, h);
	sender.setImage(xo, xf, yo, yf);
	senders.push_back(sender);
	return senders.size() - 1;
}


void cScene::logic(cPlayer* player) {
	vector<cBicho*> bichos;
	for (int i = 0; i < enemies.size(); ++i) {
		if (enemies[i]->isAlive()) bichos.push_back(enemies[i]);
	}
	for (int i = 0; i < blocks.size(); i++)
	{
		bichos.push_back(&blocks[i]);
	}
	bichos.push_back(player);

	for (int i = 0; i < gears.size(); i++)
	{
		if (gears[i].isActive()) {
			gears[i].logic(bichos);
			int id = gears[i].getSender();
			if (gears[i].isTouched()) {
				if (senders[id].isWall()) {
					Sound::getInstance()->playOpen();
					senders[id].switchState();
				}
			}
			else if (!senders[id].isWall()) {
				Sound::getInstance()->playClose();
				senders[id].switchState();
			}
		}
	}

	for (int i = 0; i < blocks.size(); i++)
	{
		if (blocks[i].isActive()) blocks[i].logic(player, map, width);
	}


	for (int i = 0; i < senders.size(); i++)
	{
		if(senders[i].isActive()) senders[i].logic(player);
	}
	for (int i = 0; i < enemies.size(); i++)
	{
		if(enemies[i]->isActive()) enemies[i]->Logic(map, width, player);
	}
}



void cScene::addEnemy(int enemyType, int x, int y, int tex_id) {
	
	int id = enemies.size();
	
	switch (enemyType)
	{
	case SOLDADO:
			enemies.push_back(new Soldado);
			enemies[id]->SetTile(x,y);
			enemies[id]->SetMaxLife(3);
			enemies[id]->SetWidthHeight(16, 28);
			enemies[id]->SetState(STATE_WALKDOWN);
			enemies[id]->setImage(tex_id);

		break;
	case PLANTABOMBA:
			enemies.push_back(new PlantaBomba);
			enemies[id]->SetTile(x,y);
			enemies[id]->SetMaxLife(3);
			enemies[id]->SetWidthHeight(18,17);
			enemies[id]->SetState(STATE_LOOKDOWN);
			enemies[id]->setImage(tex_id);
		break;
	case GOLEM:
			enemies.push_back(new Golem);
			enemies[id]->SetTile(x,y);
			enemies[id]->SetMaxLife(5);
			enemies[id]->SetWidthHeight(24, 25);
			enemies[id]->SetState(STATE_SLEEP);
			enemies[id]->setImage(tex_id);
		break;
	case BOSS:
		enemies.push_back(new Boss);
		enemies[id]->SetTile(x, y);
		enemies[id]->SetMaxLife(20);
		enemies[id]->SetWidthHeight(32, 53);
		enemies[id]->SetState(STATE_LOOKDOWN);
		enemies[id]->setImage(tex_id);
		break;
	default:
		break;
	}

}


vector<Enemy*> cScene::getEnemies(){
	return enemies;
}

void cScene::setSenderCloseImage(int index, float xo, float xf, float yo, float yf) {
	senders[index].setCloseImage(xo, xf, yo, yf);
	senders[index].switchState();
}

void cScene::addGear(int x, int y, int sender_id, float xo, float xf, float yo, float yf, int w, int h) {
	Gear gear;
	gear.SetTile(x, y);
	gear.setSender(sender_id);
	gear.SetWidthHeight(w, h);
	gear.setImage(xo, xf, yo, yf);
	gears.push_back(gear);
}

void cScene::addBlock(int x, int y, float xo, float xf, float yo, float yf, int w, int h) {
	Block block;
	block.SetTile(x, y);
	block.SetWidthHeight(w, h);
	block.setImage(xo, xf, yo, yf);
	blocks.push_back(block);
}

void cScene::drawMiniMap(int cx, int cy, int x, int y) {
	int blocksize = 4;
	int ini_x = cx - width * 2;
	int ini_y = cy - height * 2;


	glBegin(GL_QUADS);


	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (map[i*width + j]) {
				glColor3f(0, 0, 0);
			}
			else {
				glColor3f(0, 0, 1);
			}
			glVertex2i(ini_x + j*blocksize, ini_y+i*blocksize);
			glVertex2i(ini_x + j * blocksize + blocksize, ini_y + i * blocksize);
			glVertex2i(ini_x + j * blocksize + blocksize, ini_y + i * blocksize + blocksize);
			glVertex2i(ini_x + j * blocksize, ini_y + i * blocksize + blocksize);
		}
	}
	glColor3f(1, 0, 0);
	int ex, ey;
	for (int i = 0; i < enemies.size(); i++) {
		if (enemies[i]->isVisible()) {
			enemies[i]->GetTile(&ex,&ey);
			glVertex2i(ini_x + ex*blocksize, ini_y + ey*blocksize);
			glVertex2i(ini_x + ex * blocksize + blocksize, ini_y + ey * blocksize);
			glVertex2i(ini_x + ex * blocksize + blocksize, ini_y + ey * blocksize + blocksize);
			glVertex2i(ini_x + ex * blocksize, ini_y + ey * blocksize + blocksize);
		}
	}
	glColor3f(0, 1, 0);
	x = x / 16;
	y = y / 16;
	glVertex2i(ini_x + x*blocksize, ini_y + y*blocksize);
	glVertex2i(ini_x + x * blocksize + blocksize, ini_y + y * blocksize);
	glVertex2i(ini_x + x * blocksize + blocksize, ini_y + y * blocksize + blocksize);
	glVertex2i(ini_x + x * blocksize, ini_y + y * blocksize + blocksize);


	glEnd();
	glColor3f(1, 1, 1);


}