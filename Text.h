#pragma once

#include "GameConfig.h"

class Text {
public:
	Text();
	~Text();

	enum TextColor {
		WHITE_TEXT
	};

	bool loadFromRenderText(TTF_Font* font, SDL_Renderer* screen);
	void clean();

	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void setColor(int type);

	void RenderText(SDL_Renderer* screen, 
		int xp, 
		int yp, 
		SDL_Rect* clip = nullptr, 
		double angle = 0.0, 
		SDL_Point* center = nullptr, 
		SDL_RendererFlip flip = SDL_FLIP_NONE);

	int getWidth() const { return width; }
	int getHeight() const { return height; }

	void setText(const std::string& text) { strVal = text; }
	std::string getText() const { return strVal; }

private:
	std::string strVal;
	SDL_Color textColor;
	SDL_Texture* texture;
	int width;
	int height;
};