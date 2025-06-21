#pragma once

#include "GameConfig.h"
#include "Texture.h"
#include "Player.h"

class Background : public Texture
{
public:
	Background() { mX = 0; }
	~Background();
	void scroll(SDL_Renderer* screen, Player playerData);
	void render(SDL_Renderer* des, const SDL_Rect* clip);

private:
	int mX;
};