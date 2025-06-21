#include "Background.h"

Background::~Background() {
	clean();
}

void Background::scroll(SDL_Renderer* screen, Player playerData)
{
	mX -= playerData.getXVal() / 6;
	if (mX <= -SCREEN_WIDTH) {
		mX = 0;
	}
	SDL_Rect rect1 = { mX, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_Rect rect2 = { mX + SCREEN_WIDTH, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_RenderCopy(screen, mTexture, nullptr, &rect1);
	SDL_RenderCopy(screen, mTexture, nullptr, &rect2);
}

void Background::render(SDL_Renderer* des, const SDL_Rect* clip)
{
	SDL_Rect renderQuad = { rect.x, rect.y, SCREEN_WIDTH, SCREEN_HEIGHT };
	SDL_RenderCopy(des, mTexture, clip, &renderQuad);
}

