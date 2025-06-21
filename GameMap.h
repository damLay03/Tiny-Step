#pragma once

#include "GameConfig.h"
#include "Texture.h"

class TileMat : public Texture
{
public:
	TileMat() { ; }
	~TileMat() { ; }
};

class GameMap
{
public:
	GameMap() { ; }
	~GameMap() { ; }
	void reset();
	bool loadMap(const char* name);
	bool loadTilesNormal(SDL_Renderer* screen);
	bool loadTilesAutumn(SDL_Renderer* screen);
	bool loadTilesWinter(SDL_Renderer* screen);
	void drawMap(SDL_Renderer* screen);
	Map getMap() const { return gMap; }
	void setMap(Map& mapData) { gMap = mapData; }
private:
	Map gMap;
	TileMat gTileMap[MAX_TILES];
};