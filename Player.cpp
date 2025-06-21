#include "Player.h"

Player::Player()
{
	reset();
}

Player::~Player()
{
	clean();
}

void Player::reset()
{
	xVal = PLAYER_SPEED;
	yVal = 0;
	xPos = 0;
	yPos = 288;
	widthFrame = 0;
	heightFrame = 0;
	frame = 0;
	status = RUN;
	count = 0;
	onGround = false;
	mapX = 0;
	mapY = 0;
	anim_timer.start();
}

bool Player::loadFromFile(std::string path, SDL_Renderer* screen)
{
	bool ret = Texture::loadFromFile(path, screen);
	if (ret) {
		if (status == RUN || status == ATTACK){ widthFrame = rect.w / SIX_FRAME; }
		else if (status == JUMP) { widthFrame = rect.w / TWO_FRAME; }
		heightFrame = rect.h;
	}
	setClips();
	return ret;
}

void Player::setClips()
{
	if (widthFrame > 0 && heightFrame > 0) {
		if (status == RUN || status == ATTACK) {
			for (int i = 0; i < SIX_FRAME; i++)
			{
				frameClip[i].x = i * widthFrame;
				frameClip[i].y = 0;
				frameClip[i].w = widthFrame;
				frameClip[i].h = heightFrame;
			}
		}
		else if (status == JUMP) {
			for (int i = 0; i < TWO_FRAME; i++)
			{
				frameClip[i].x = i * widthFrame;
				frameClip[i].y = 0;
				frameClip[i].w = widthFrame;
				frameClip[i].h = heightFrame;
			}
		}

	}
}

void Player::show(SDL_Renderer* des)
{
	if (status == RUN) {
		loadFromFile("Materials/Textures/Player/Meo_Run.png", des);
		if (anim_timer.get_ticks() >= ANIM_DELAY) {
			frame++;
			if (frame >= SIX_FRAME) {
				frame = 0;
			}
			anim_timer.start();
		}
	}
	else if (status == JUMP) {
		loadFromFile("Materials/Textures/Player/Meo_Jump.png", des);
		frame = yVal < 0 ? 0 : 1;
	}
	else if (status == ATTACK) {
		loadFromFile("Materials/Textures/Player/Meo_Attack.png", des);
		if (anim_timer.get_ticks() >= ANIM_DELAY) {
			frame++;
			if (frame >= SIX_FRAME) {
				frame = SIX_FRAME - 1;
			}
			anim_timer.start();
		}
	}
	rect.x = xPos - mapX;
	rect.y = yPos - mapY;
	SDL_Rect* currentClip = &frameClip[frame];
	SDL_Rect renderQuad = { rect.x, rect.y, widthFrame, heightFrame };
	SDL_RenderCopy(des, mTexture, currentClip, &renderQuad);
}

void Player::handleInputAction(SDL_Event events, SDL_Renderer* screen)
{
	if (events.type == SDL_KEYDOWN) {
		switch (events.key.keysym.sym) {
		case SDLK_SPACE:
			inputType.jump = 1;
			break;
		case SDLK_z:
			inputType.attack = 1;
			break;
		}
	}
	else if (events.type == SDL_KEYUP) {
		switch (events.key.keysym.sym) {
		case SDLK_SPACE:
			inputType.jump = 0;
			break;
		case SDLK_z:
			inputType.attack = 0;
			break;
		}
	}
}

void Player::doPlayer(Map& mapData)
{
	//xu li chay
	xVal += PLAYER_ACCELERATION;
	if (xVal >= PLAYER_MAX_SPEED) {
		xVal = PLAYER_MAX_SPEED;
	}

	//xu li roi
	yVal += GRAVITY_SPEED;
	if (yVal >= MAX_FALL_SPEED) {
		yVal = MAX_FALL_SPEED;
	}

	//xu li nhay
	if (onGround) {
		count = 0;
	}
	if (inputType.jump == 1 && count < 2 ) {
		yVal = -PLAYER_JUMP;
		status = JUMP;
		count++;
		onGround = false;
		inputType.jump = 0;
	}
	else if (status == JUMP && onGround) {
		status = RUN;
	}

	//xu li tan cong
	if (inputType.attack == 1 && onGround) {
		status = ATTACK;
	}
	if (status == ATTACK && frame == SIX_FRAME - 1 && onGround) {
		status = RUN;
	}

	//kiem tra va cham
	checkToMap(mapData);

	//cap nhat toa do camera
	centerMap(mapData);
}

void Player::centerMap(Map& mapData)
{
	//toa do x va
	mapData.startX = xPos - (SCREEN_WIDTH / 5.4);
	if (mapData.startX < 0) {
		mapData.startX = 0;
	}
}

void Player::checkToMap(Map& mapData)
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
	else if (yVal < 0) { //nhan vat dang nhay len
		if (mapData.tile[y1][x1] != BLANK_TILE || mapData.tile[y1][x2] != BLANK_TILE) {
			yPos = (y1 + 1) * TILE_SIZE;
			yVal = 0;
		}
	}

	//nhan vat khong va cham gi ca
	xPos += xVal;
	yPos += yVal;
}