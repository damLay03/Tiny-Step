#include "GameConfig.h"
#include "Texture.h"
#include "GameMap.h"
#include "Player.h"
#include "Background.h"
#include "Timer.h"
#include "Obstacle.h"
#include "Text.h"
#include "Audio.h"

Background NBackground;
Background ABackground;
Background WBackground;

GameMap gMap;

Player gPlayer;

ImpTimer fpsTimer;
ImpTimer gameTimer;

TTF_Font* fontTime;
Text gText;

Audio gMusic;
Audio gAudio;

std::vector<Background*> backgroundList;
std::vector<Obstacle*> obstacleList;


bool init() {
	bool success = true;

	//khoi tao video va am thanh
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		success = false;
	}

	//ap dung ti le tuyen tinh
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	//khoi tao window
	gWindow = SDL_CreateWindow("Tiny Step", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (gWindow == nullptr) {
		success = false;
	}

	//khoi tao renderer
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (gRenderer == nullptr) {
		success = false;
	}

	//khoi tao mau cho render
	SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);

	//khoi tao SDL_image
	int imgFlags = IMG_INIT_PNG;
	if (!(IMG_Init(imgFlags) & imgFlags)) {
		success = false;
	}

	//khoi tao van ban
	if (TTF_Init() == -1) {
		success = false;
	}

	// setting am thanh
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		success = false;
	}

	return success;
}

//load hang loat background vao list
void addBackgroundList() {

	//load background normal
	NBackground.loadFromFile("Materials/Textures/Normal/Background.png", gRenderer);

	//load background autumn
	ABackground.loadFromFile("Materials/Textures/Autumn/Background.png", gRenderer);

	//load background winter
	WBackground.loadFromFile("Materials/Textures/Winter/Background.png", gRenderer);

	//them vao list
	backgroundList.push_back(&NBackground);
	backgroundList.push_back(&ABackground);
	backgroundList.push_back(&WBackground);
}

//load hang loat obstacle vao list
void spawnObstacle(std::vector<Obstacle*>& listObstacle, int pickBySeason) {

	Obstacle* newObstacle = nullptr;

	//lua chon ngau nhien de spawn
	int obstacleType = SDLCommonFunc::gacha();

	switch (obstacleType) {
	case 0:
		newObstacle = new Obstacle(STATIC);
		if (pickBySeason == 1) { newObstacle->loadFromFile("Materials/Textures/Normal/Rock_1.png", gRenderer); }
		else if (pickBySeason == 2) { newObstacle->loadFromFile("Materials/Textures/Autumn/Rock_1.png", gRenderer); }
		else if (pickBySeason == 3) { newObstacle->loadFromFile("Materials/Textures/Winter/Rock_1.png", gRenderer); }
		break;
	case 1:
		newObstacle = new Obstacle(STATIC);
		if (pickBySeason == 1) { newObstacle->loadFromFile("Materials/Textures/Normal/Rock_2.png", gRenderer); }
		else if (pickBySeason == 2) { newObstacle->loadFromFile("Materials/Textures/Autumn/Rock_2.png", gRenderer); }
		else if (pickBySeason == 3) { newObstacle->loadFromFile("Materials/Textures/Winter/Rock_2.png", gRenderer); }
		break;
	case 2:
		newObstacle = new Obstacle(STATIC);
		if (pickBySeason == 1) { newObstacle->loadFromFile("Materials/Textures/Normal/Rock_3.png", gRenderer); }
		else if (pickBySeason == 2) { newObstacle->loadFromFile("Materials/Textures/Autumn/Rock_3.png", gRenderer); }
		else if (pickBySeason == 3) { newObstacle->loadFromFile("Materials/Textures/Winter/Rock_3.png", gRenderer); }
		break;
	case 3:
		if (pickBySeason == 1) {
			newObstacle = new Obstacle(LIVING, FROG);
			newObstacle->loadFromFile("Materials/Textures/Normal/Frogger.png", gRenderer);
		}
		else if (pickBySeason == 2) {
			newObstacle = new Obstacle(LIVING, HYENA);
			newObstacle->loadFromFile("Materials/Textures/Autumn/Hyena.png", gRenderer);
		}
		else if (pickBySeason == 3) {
			newObstacle = new Obstacle(LIVING, PENGU);
			newObstacle->loadFromFile("Materials/Textures/Winter/Pengu.png", gRenderer);
		}
		break;
	case 4:
		newObstacle = new Obstacle(LIVING, BAT);
		if (pickBySeason == 1) { newObstacle->loadFromFile("Materials/Textures/Normal/Bat.png", gRenderer); }
		else if (pickBySeason == 2) { newObstacle->loadFromFile("Materials/Textures/Autumn/Bat.png", gRenderer); }
		else if (pickBySeason == 3) { newObstacle->loadFromFile("Materials/Textures/Winter/Bat.png", gRenderer); }
		break;
	case 5:
		newObstacle = new Obstacle(LIVING, DINO);
		if (pickBySeason == 1) { newObstacle->loadFromFile("Materials/Textures/Normal/Dino.png", gRenderer); }
		else if (pickBySeason == 2) { newObstacle->loadFromFile("Materials/Textures/Autumn/Dino.png", gRenderer); }
		else if (pickBySeason == 3) { newObstacle->loadFromFile("Materials/Textures/Winter/Dino.png", gRenderer); }
		break;
	}

	if (newObstacle != nullptr) {
		if (newObstacle->getCreature() == DINO) {
			newObstacle->setXPos(gPlayer.getXPos() - SCREEN_WIDTH);
			newObstacle->setYPos(150);
		}
		else {
			newObstacle->setXPos(gPlayer.getXPos() + SCREEN_WIDTH + rand() % SPAWN_SPACE);
			newObstacle->setYPos(150);
		}
		listObstacle.push_back(newObstacle);
	}
}

bool loadMedia() {
	bool success = true;

	//load background
	addBackgroundList();

	//load map
	if (!gMap.loadMap("Materials/Maps/map.txt")) {
		printf("load map");
		success = false;
	}

	//load player
	if (!gPlayer.loadFromFile("Materials/Textures/Player/Meo_Run.png", gRenderer)) {
		printf("load player");
		success = false;
	}

	//load text
	fontTime = TTF_OpenFont("Materials/Fonts/CyberpunkCraftpixPixel.otf", 15);
	if (fontTime == nullptr) {
		success = false;
	}

	//load audio
	gMusic.load("Materials/Audios/Lukrembo - Rose (freetouse.com).mp3", AudioType::MUSIC);

	return success;
}

void close() {
	//giai phong texture
	NBackground.clean();
	ABackground.clean();
	WBackground.clean();
	gPlayer.clean();

	//giai phong cua so
	SDL_DestroyRenderer(gRenderer);
	gRenderer = nullptr;
	SDL_DestroyWindow(gWindow);
	gWindow = nullptr;

	//quit SDL
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* argv[])
{
	if (!init()) {
		printf("Unable to initialize\n");
	}
	if (!loadMedia()) {
		printf("Unable to load media\n");
	}

	bool quit = false;
	while (!quit) {
		//phat nhac
		gMusic.play(-1);

		//tinh thoi gian spawn
		Uint32 lastSpawnTime = 0;
		Uint32 spawnInterval = SPAWN_INTERVAL;
		Uint32 minSpawnInterval = 500;

		//bat dau tinh diem
		Uint32 score = 0;

		//reset
		obstacleList.clear();
		gPlayer.reset();
		gMap.reset();

		//bat dau bo dem game
		gameTimer.start();

		//game over
		bool gameOver = false;

		while (!quit && !gameOver) {
			fpsTimer.start();

			while (SDL_PollEvent(&gEvent) != 0) {
				if (gEvent.type == SDL_QUIT) {
					quit = true;
				}
				gPlayer.handleInputAction(gEvent, gRenderer);
			}

			//clear screen
			SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
			SDL_RenderClear(gRenderer);

			//render background
			int bgIndex = (score / CHANGE_TIME) % backgroundList.size();
			backgroundList[bgIndex]->render(gRenderer, nullptr);
			backgroundList[bgIndex]->scroll(gRenderer, gPlayer);
			if (backgroundList[bgIndex] == &NBackground) {

				//load normal tiles
				gMap.loadTilesNormal(gRenderer);

				//tao obstacle vo han
				if (gameTimer.get_ticks() - lastSpawnTime >= spawnInterval) {
					spawnObstacle(obstacleList, 1);
					lastSpawnTime = gameTimer.get_ticks();
				}
			}
			else if (backgroundList[bgIndex] == &ABackground) {

				//load autumn tiles
				gMap.loadTilesAutumn(gRenderer);

				//tao obstacle vo han
				if (gameTimer.get_ticks() - lastSpawnTime >= spawnInterval) {
					spawnObstacle(obstacleList, 2);
					lastSpawnTime = gameTimer.get_ticks();
				}

				//tao threat vo han
				if (gameTimer.get_ticks() - lastSpawnTime >= spawnInterval) {
					lastSpawnTime = gameTimer.get_ticks();
				}
			}
			else if (backgroundList[bgIndex] == &WBackground) {

				//load winter tiles
				gMap.loadTilesWinter(gRenderer);

				//tao obstacle vo han
				if (gameTimer.get_ticks() - lastSpawnTime >= spawnInterval) {
					spawnObstacle(obstacleList, 3);
					lastSpawnTime = gameTimer.get_ticks();
				}
			}

			//get map data
			Map mapData = gMap.getMap();

			//render player
			gPlayer.setMapXY(mapData.startX, mapData.startY);
			gPlayer.doPlayer(mapData);
			gPlayer.show(gRenderer);

			//render map
			gMap.setMap(mapData);
			gMap.drawMap(gRenderer);

			//chay obstacle
			for (int i = 0; i < obstacleList.size(); i++)
			{
				Obstacle* gObstacle = obstacleList.at(i);
				if (gObstacle != nullptr) {

					//render obstacle
					gObstacle->setMapXY(mapData.startX, mapData.startY);
					gObstacle->doObstacle(mapData, gPlayer);
					gObstacle->show(gRenderer);

					//lay kich thuoc obstacle
					SDL_Rect tRect;
					tRect.x = gObstacle->getRect().x;
					tRect.y = gObstacle->getRect().y;
					tRect.w = gObstacle->getWidthFrame();
					tRect.h = gObstacle->getHeightFrame();

					//lay kich thuoc player
					SDL_Rect pRect;
					pRect.x = gPlayer.getRect().x;
					pRect.y = gPlayer.getRect().y;
					pRect.w = gPlayer.getWidthFrame();
					pRect.h = gPlayer.getHeightFrame();

					//xet va cham
					bool col = SDLCommonFunc::checkCollision(pRect, tRect);

					//khong va cham
					if (gObstacle->getCreature() != DINO) {
						if (gObstacle->getXPos() + gObstacle->getWidthFrame() < 0) {
							gObstacle->clean();
							delete gObstacle;
							obstacleList.erase(obstacleList.begin() + i);
							i--;
						}
					}
					else {
						if (gObstacle->getXPos() + gObstacle->getWidthFrame() > gPlayer.getXPos() + SCREEN_WIDTH) {
							gObstacle->clean();
							delete gObstacle;
							obstacleList.erase(obstacleList.begin() + i);
							i--;
						}
					}

					//va cham
					if (col) {
						gameOver = true;
					}
				}
			}

			//render diem
			score++;
			std::string score_text = std::to_string(score);
			gText.setColor(Text::WHITE_TEXT);
			gText.setText(score_text);
			gText.loadFromRenderText(fontTime, gRenderer);
			gText.RenderText(gRenderer, (SCREEN_WIDTH - score_text.size()) / 2, 15);

			//tang do kho
			if (score % 500 == 0 && spawnInterval > minSpawnInterval) {
				spawnInterval -= 100;
			}

			//update screen
			SDL_RenderPresent(gRenderer);

			//delay
			int realTime = fpsTimer.get_ticks();
			int timePerFrame = 1000 / FRAME_PER_SECOND; //ms
			if (realTime < timePerFrame) {
				SDL_Delay(timePerFrame - realTime);
			}
		}
		//khi thua
		if (!quit) {
			gText.setColor(Text::WHITE_TEXT);
			gText.setText("Game Over! Press SPACE to restart");
			gText.loadFromRenderText(fontTime, gRenderer);
			gText.RenderText(gRenderer, SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2);

			SDL_RenderPresent(gRenderer);

			bool waitRestart = true;
			while (waitRestart) {
				while (SDL_PollEvent(&gEvent)) {
					if (gEvent.type == SDL_QUIT) {
						waitRestart = false;
						quit = true;
					}
					else if (gEvent.type == SDL_KEYDOWN && gEvent.key.keysym.sym == SDLK_SPACE) {
						waitRestart = false;
					}
				}
			}
		}
	}
	//dong chuong trinh
	close();
	return 0;
}