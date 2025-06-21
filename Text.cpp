#include "Text.h"

Text::Text()
{
	textColor.r = 255;
	textColor.g = 255;
	textColor.b = 255;
	texture = nullptr;
}

Text::~Text()
{
	clean();
}

bool Text::loadFromRenderText(TTF_Font* font, SDL_Renderer* screen)
{
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, strVal.c_str(), textColor);
	if (textSurface) {
		texture = SDL_CreateTextureFromSurface(screen, textSurface);
		width = textSurface->w;
		height = textSurface->h;
		SDL_FreeSurface(textSurface);
	}
	return textSurface != nullptr;
}

void Text::clean()
{
	if (texture != nullptr) {
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}
}

void Text::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	textColor.r = red;
	textColor.g = green;
	textColor.b = blue;
}

void Text::setColor(int type)
{
	if (type == WHITE_TEXT) {
		SDL_Color color = { 255, 255, 255 };
		textColor = color;
	}
}

void Text::RenderText(SDL_Renderer* screen, 
	int xp, 
	int yp, 
	SDL_Rect* clip, 
	double angle, 
	SDL_Point* center, 
	SDL_RendererFlip flip)
{
	SDL_Rect renderQuad = { xp, yp, width,height };
	if (clip != nullptr) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopyEx(screen, texture, clip, &renderQuad, angle, center, flip);
}
