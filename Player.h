#pragma once

#include "GameConfig.h"
#include "Texture.h"
#include "Timer.h"

enum status {
	RUN,
	JUMP,
	ATTACK
};

class Player : public Texture
{
public:
	Player();
	~Player();
	void reset();
	bool loadFromFile(std::string path, SDL_Renderer* screen);
	void setClips();
	void show(SDL_Renderer* des);
	void handleInputAction(SDL_Event events, SDL_Renderer* screen);
	void doPlayer(Map& mapData);
	void checkToMap(Map& mapData);
	void setMapXY(const int x, const int y) { mapX = x; mapY = y; }
	void centerMap(Map& mapData);
	void setXVal(float x) { xVal = x; }
	int getWidthFrame() const { return widthFrame; }
	int getHeightFrame() const { return heightFrame; }
	float getXPos() { return xPos; }
	float getYPos() { return yPos; }
	float getXVal() { return xVal; }
	float getYVal() { return yVal; }
	int getStatus() { return status; }

private:

	//toc do cua nhan vat
	float xVal;
	float yVal;

	//toa do cua nhan vat
	float xPos;
	float yPos;

	//kich thuoc cua nhan vat
	int widthFrame;
	int heightFrame;

	//cac frame cua nhan vat
	SDL_Rect frameClip[SIX_FRAME];

	//trang thai cua nhan vat
	status status;

	//hanh dong
	Input inputType;

	//double jump
	int count;

	//kiem tra nhan vat co tren mat dat hay khong
	bool onGround;

	//frame hien tai cua nhan vat
	int frame;

	//toa do cua map
	int mapX;
	int mapY;

	//chuyen dong
	ImpTimer anim_timer;
};