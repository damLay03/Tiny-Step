#pragma once

#include "GameConfig.h"

class Texture
{
public:
	Texture();
	~Texture();
	void SetRect(const int& x, const int& y) { rect.x = x; rect.y = y; }
	SDL_Rect getRect() const { return rect; }
	SDL_Texture* getObject() const { return mTexture; }
	virtual bool loadFromFile(std::string path, SDL_Renderer* screen);
	void render(SDL_Renderer* des, const SDL_Rect* clip = NULL);
	void clean();
	int getWidth() const { return rect.w; }
	int getHeight() const { return rect.h; }
protected:
	SDL_Texture* mTexture;
	SDL_Rect rect;
};