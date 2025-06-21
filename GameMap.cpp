#include "GameMap.h"

void GameMap::reset() {
	gMap.startX = 0;
	gMap.startY = 0;
	gMap.maxX = 0;
	gMap.maxY = 0;

	for (int i = 0; i < MAX_MAP_Y; i++) {
		for (int j = 0; j < MAX_MAP_X; j++) {
			gMap.tile[i][j] = 0;
		}
	}

	loadMap(gMap.fileName);
}


bool GameMap::loadMap(const char* name)
{
	bool success = true;
	FILE* fp = nullptr;
	fopen_s(&fp, name, "rb");
	if (fp == nullptr) {
		success = false;
	}

	//chay vong lap de doc du lieu
	for (int i = 0; i < MAX_MAP_Y; i++) {
		for (int j = 0; j < MAX_MAP_X; j++) {
			fscanf_s(fp, "%d", &gMap.tile[i][j]);
			int val = gMap.tile[i][j];
			if (val > 0) {
				if (j > gMap.maxX) {
					gMap.maxX = j;
				}
				if (i > gMap.maxY) {
					gMap.maxY = i;
				}
			}
		}
	}

	//gan gia tri max x, y
	gMap.maxX = (gMap.maxX + 1) * TILE_SIZE;
	gMap.maxY = (gMap.maxY + 1) * TILE_SIZE;

	//gan gia tri start x, y
	gMap.startX = 0;
	gMap.startY = 0;

	//luu va thoat file
	gMap.fileName = name;
	fclose(fp);
	return success;
}

bool GameMap::loadTilesNormal(SDL_Renderer* screen)
{
	bool success = true;
	char fileImg[35];
	FILE* fp = nullptr;
	for (int i = 0; i < MAX_TILES; i++)
	{
		sprintf_s(fileImg, "Materials/Maps/normal_tiles/%d.png", i);
		fopen_s(&fp, fileImg, "rb");
		if (fp == nullptr) {
			continue;
		}
		fclose(fp);
		gTileMap[i].loadFromFile(fileImg, screen);
	}
	return success;
}

bool GameMap::loadTilesAutumn(SDL_Renderer* screen)
{
	bool success = true;
	char fileImg[35];
	FILE* fp = nullptr;
	for (int i = 0; i < MAX_TILES; i++)
	{
		sprintf_s(fileImg, "Materials/Maps/autumn_tiles/%d.png", i);
		fopen_s(&fp, fileImg, "rb");
		if (fp == nullptr) {
			continue;
		}
		fclose(fp);
		gTileMap[i].loadFromFile(fileImg, screen);
	}
	return success;
}

bool GameMap::loadTilesWinter(SDL_Renderer* screen)
{
	bool success = true;
	char fileImg[35];
	FILE* fp = nullptr;
	for (int i = 0; i < MAX_TILES; i++)
	{
		sprintf_s(fileImg, "Materials/Maps/winter_tiles/%d.png", i);
		fopen_s(&fp, fileImg, "rb");
		if (fp == nullptr) {
			continue;
		}
		fclose(fp);
		gTileMap[i].loadFromFile(fileImg, screen);
	}
	return success;
}

void GameMap::drawMap(SDL_Renderer* screen)
{
	int x1 = 0;
	int x2 = 0;

	int y1 = 0;
	int y2 = 0;

	int mapX = 0;
	int mapY = 0;

	mapX = gMap.startX / TILE_SIZE;
	x1 = (gMap.startX % TILE_SIZE) * -1;
	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

	mapY = gMap.startY / TILE_SIZE;
	y1 = (gMap.startY % TILE_SIZE) * -1;
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);

	for (int i = y1; i < y2; i += TILE_SIZE) {
		mapX = gMap.startX / TILE_SIZE;
		for (int j = x1; j < x2; j += TILE_SIZE) {
			int val = gMap.tile[mapY % MAX_MAP_Y][mapX % MAX_MAP_X];
			if (val > 0) {
				gTileMap[val].SetRect(j, i);
				gTileMap[val].render(screen);
			}
			mapX++;
		}
		mapY++;
	}
}