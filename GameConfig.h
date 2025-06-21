#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>
#include <vector>
#include <random>

static SDL_Window* gWindow = NULL;
static SDL_Renderer* gRenderer = NULL;
static SDL_Event gEvent;

//screen
const int FRAME_PER_SECOND = 60; //fps
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 352;
const int SCREEN_BPP = 32;

//color key
const int COLOR_KEY_R = 167;
const int COLOR_KEY_G = 175;
const int COLOR_KEY_B = 180;

//render color
const int RENDER_DRAW_COLOR = 0xFF;

//tile map
#define TILE_SIZE 32
#define MAX_MAP_X 32*3
#define MAX_MAP_Y 11
#define MAX_TILES 10
#define BLANK_TILE 0

//environment
#define CHANGE_TIME 2000

typedef struct Map {
	int startX;
	int startY;
	int maxX;
	int maxY;
	int tile[MAX_MAP_Y][MAX_MAP_X];
	const char* fileName;
} Map;

//player
#define GRAVITY_SPEED 0.8
#define MAX_FALL_SPEED 14
#define PLAYER_SPEED 6
#define PLAYER_ACCELERATION 0.0015
#define PLAYER_MAX_SPEED 10
#define PLAYER_JUMP 10

//obtacle
#define SPAWN_INTERVAL 1300
#define SPAWN_SPACE 300

//chuyen dong
#define ONE_FRAME 1
#define TWO_FRAME 2
#define SIX_FRAME 6
#define EIGHT_FRAME 8
#define ANIM_DELAY PLAYER_SPEED * 10

typedef struct Input {
	int run;
	int jump;
	int attack;
} Input;

//va cham object
namespace SDLCommonFunc {
	bool checkCollision(const SDL_Rect& a, const SDL_Rect& b);
	int gacha();
}