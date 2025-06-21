#include "GameConfig.h"

bool SDLCommonFunc::checkCollision(const SDL_Rect& a, const SDL_Rect& b)
{
	int leftA = a.x;
	int rightA = a.x + a.w;
	int topA = a.y;
	int bottomA = a.y + a.h;

	int leftB = b.x;
	int rightB = b.x + b.w;
	int topB = b.y;
	int bottomB = b.y + b.h;

	//khong va cham
	if (bottomA <= topB) return false;
	if (topA >= bottomB) return false;
	if (rightA <= leftB) return false;
	if (leftA >= rightB) return false;

	//va cham
	return true;
}

int SDLCommonFunc::gacha()
{
	//rand 1-100
	static std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution<> dist(0, 99);
	int r = dist(gen);

	//he thong gacha
	if (r < 25) return 0;
	else if (r < 50) return 1;
	else if (r < 75) return 2;
	else if (r < 85) return 3;
	else if (r < 95) return 4;
	else return 5;
}
