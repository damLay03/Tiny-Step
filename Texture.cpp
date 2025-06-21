#include "Texture.h"

Texture::Texture()
{
	mTexture = nullptr;
	rect.x = 0;
	rect.y = 0;
	rect.w = 0;
	rect.h = 0;
}

Texture::~Texture()
{
	clean();
}

bool Texture::loadFromFile(std::string path, SDL_Renderer* screen)
{
	SDL_Texture* newTexture = nullptr;
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface != nullptr) {
		newTexture = SDL_CreateTextureFromSurface(screen, loadedSurface);
		if (newTexture != nullptr) {
			rect.w = loadedSurface->w;
			rect.h = loadedSurface->h;
		}
		SDL_FreeSurface(loadedSurface);
	}
	mTexture = newTexture;
	return mTexture != nullptr;
}

void Texture::render(SDL_Renderer* des, const SDL_Rect* clip)
{
	SDL_Rect renderQuad;
	renderQuad = { rect.x, rect.y, rect.w, rect.h };
	if (clip != nullptr) {
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}
	SDL_RenderCopy(des, mTexture, clip, &renderQuad);
}

void Texture::clean()
{
	if (mTexture != nullptr) {
		SDL_DestroyTexture(mTexture);
		mTexture = nullptr;
		rect.w = 0;
		rect.h = 0;
	}
}