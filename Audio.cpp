#include "Audio.h"

Audio::Audio() : type(AudioType::SOUND), chunk(nullptr), music(nullptr), channel(-1) {}

Audio::Audio(const std::string& path, AudioType type) {
    load(path, type);
}

Audio::~Audio() {
    if (chunk) Mix_FreeChunk(chunk);
    if (music) Mix_FreeMusic(music);
}

bool Audio::load(const std::string& path, AudioType t) {
    type = t;

    if (chunk) {
        Mix_FreeChunk(chunk);
        chunk = nullptr;
    }
    if (music) {
        Mix_FreeMusic(music);
        music = nullptr;
    }

    if (type == AudioType::SOUND) {
        chunk = Mix_LoadWAV(path.c_str());
        if (!chunk) {
            SDL_Log("Failed to load sound: %s", Mix_GetError());
            return false;
        }
    }
    else {
        music = Mix_LoadMUS(path.c_str());
        if (!music) {
            SDL_Log("Failed to load music: %s", Mix_GetError());
            return false;
        }
    }
    return true;
}

void Audio::play(int loops) {
    if (type == AudioType::SOUND && chunk) {
        channel = Mix_PlayChannel(-1, chunk, loops);
    }
    else if (type == AudioType::MUSIC && music) {
        Mix_PlayMusic(music, loops);
    }
}

void Audio::stop() {
    if (type == AudioType::SOUND && channel != -1) {
        Mix_HaltChannel(channel);
    }
    else if (type == AudioType::MUSIC) {
        Mix_HaltMusic();
    }
}