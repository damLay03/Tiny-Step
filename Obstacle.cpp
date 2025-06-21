#include "Obstacle.h"

Obstacle::Obstacle(ObstacleType t) {
	xVal = 0;
	yVal = 0;
	xPos = 0;
	yPos = 0;
	onGround = 0;
	frame = 0;
	widthFrame = 0;
	heightFrame = 0;
	type = t;
	anim_timer.start();
}

Obstacle::Obstacle(ObstacleType t, Creature c)
{
	xVal = 0;
	yVal = 0;
	xPos = 0;
	yPos = 0;
	onGround = 0;
	frame = 0;
	widthFrame = 0;
	heightFrame = 0;
	type = t;
	creature = c;
	anim_timer.start();
}

Obstacle::~Obstacle() {
	clean();
}

bool Obstacle::loadFromFile(std::string path, SDL_Renderer* screen)
{
	bool ret = Texture::loadFromFile(path, screen);
	if (ret) {
		if (type == STATIC) { widthFrame = rect.w / ONE_FRAME; }
		else if (type == LIVING && (creature != DINO && creature != HYENA)) { widthFrame = rect.w / EIGHT_FRAME; }
		else if (creature == DINO || creature == HYENA) { widthFrame = rect.w / SIX_FRAME; }
		heightFrame = rect.h;
	}
	SetClip();
	return ret;
}

void Obstacle::SetClip()
{
	if (widthFrame > 0 && heightFrame > 0) {
		if (type == STATIC) {
			for (int i = 0; i < ONE_FRAME; i++)
			{
				frameClip[i].x = i * widthFrame;
				frameClip[i].y = 0;
				frameClip[i].w = widthFrame;
				frameClip[i].h = heightFrame;
			}
		}
		else if (type == LIVING && (creature != DINO && creature != HYENA)) {
			for (int i = 0; i < EIGHT_FRAME; i++)
			{
				frameClip[i].x = i * widthFrame;
				frameClip[i].y = 0;
				frameClip[i].w = widthFrame;
				frameClip[i].h = heightFrame;
			}
		}
		else if (creature == DINO || creature == HYENA) {
			for (int i = 0; i < SIX_FRAME; i++)
			{
				frameClip[i].x = i * widthFrame;
				frameClip[i].y = 0;
				frameClip[i].w = widthFrame;
				frameClip[i].h = heightFrame;
			}
		}
	}
}

void Obstacle::show(SDL_Renderer* des)
{
	if (type == STATIC) {
		if (anim_timer.get_ticks() >= ANIM_DELAY) {
			frame++;
			if (frame >= ONE_FRAME) {
				frame = 0;
			}
			anim_timer.start();
		}
	}
	else if (type == LIVING && (creature != DINO && creature != HYENA)) {
		if (anim_timer.get_ticks() >= ANIM_DELAY) {
			frame++;
			if (frame >= EIGHT_FRAME) {
				frame = 0;
			}
			anim_timer.start();
		}
	}
	else if (creature == DINO || creature == HYENA) {
		if (anim_timer.get_ticks() >= ANIM_DELAY) {
			frame++;
			if (frame >= SIX_FRAME) {
				frame = 0;
			}
			anim_timer.start();
		}
	}
	rect.x = xPos - mapX;
	rect.y = yPos - mapY;
	SDL_Rect* currentClip = &frameClip[frame];
	SDL_Rect rendQuad = { rect.x, rect.y, widthFrame, heightFrame };
	SDL_RenderCopy(des, mTexture, currentClip, &rendQuad);
}

void Obstacle::doObstacle(Map& gMap, Player playerData)
{
	if (type == STATIC) {
		xVal = 0;
	}
	else if (creature == HYENA) {
		xVal = playerData.getXVal() / 3;
	}
	else if (creature == BAT) {
		xVal = playerData.getXVal() / 4;
	}
	else if (creature == FROG) {
		xVal = playerData.getXVal() / 5;
	}
	else if (creature == PENGU) {
		xVal = playerData.getXVal() / 6;
	}
	else if (creature == DINO) {
		xVal = playerData.getXVal() * 1.5;
	}

	//tat ca vat the duoi dat
	if (creature != BAT || type == STATIC) {
		yVal += GRAVITY_SPEED;
		if (yVal >= MAX_FALL_SPEED) {
			yVal = MAX_FALL_SPEED;
		}
	}

	checkToMap(gMap);
}

void Obstacle::checkToMap(Map& mapData)
{
	int x1 = 0;
	int x2 = 0;
	int y1 = 0;
	int y2 = 0;

	//kiem tra chieu doc
	int widthMin = widthFrame < TILE_SIZE ? widthFrame : TILE_SIZE;
	x1 = (xPos) / TILE_SIZE;
	x2 = (xPos + widthMin) / TILE_SIZE;

	y1 = (yPos + yVal) / TILE_SIZE;
	y2 = (yPos + yVal + heightFrame - 1) / TILE_SIZE;

	x1 %= MAX_MAP_X; x2 %= MAX_MAP_X;
	y1 %= MAX_MAP_Y; y2 %= MAX_MAP_Y;

	if (yVal > 0) { //nhan vat dang roi tu do
		if (mapData.tile[y2][x1] != BLANK_TILE || mapData.tile[y2][x2] != BLANK_TILE) {
			yPos = y2 * TILE_SIZE;
			yPos -= (heightFrame);
			yVal = 0;
			onGround = true;
		}
	}

	//nhan vat khong va cham gi ca
	if (creature != DINO) {
		xPos -= xVal;
	}
	else {
		xPos += xVal;
	}
	yPos += yVal;
}