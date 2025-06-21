#pragma once

#include "GameConfig.h"
#include "Texture.h"
#include "Timer.h"
#include "Player.h"

enum ObstacleType {
	STATIC,
	LIVING
};

enum Creature {
	BAT,
	FROG,
	HYENA,
	PENGU,
	DINO
};

class Obstacle : public Texture
{
public:
	Obstacle(ObstacleType t);
	Obstacle(ObstacleType t, Creature c);
	~Obstacle();
	void setXVal(const int& x) { xVal = x; }
	void setYVal(const int& y) { yVal = y; }
	void setXPos(const int& x) { xPos = x; }
	void setYPos(const int& y) { yPos = y; }
	void setMapXY(const int& x, const int& y) { mapX = x; mapY = y; }
	float getXPos() const { return xPos; }
	float getYPos() const { return yPos; }
	int getWidthFrame() const { return widthFrame; }
	int getHeightFrame() const { return heightFrame; }
	int getType() { return type; }
	int getCreature() { return creature; }
	void SetClip();
	bool loadFromFile(std::string path, SDL_Renderer* screen);
	void show(SDL_Renderer* des);
	void doObstacle(Map& gMap, Player playerData);
	void checkToMap(Map& gMap);

private:
	int mapX;
	int mapY;
	float xVal;
	float yVal;
	float xPos;
	float yPos;
	bool onGround;
	int frame;
	int widthFrame;
	int heightFrame;
	ObstacleType type;
	Creature creature;
	SDL_Rect frameClip[EIGHT_FRAME];
	ImpTimer anim_timer;
};