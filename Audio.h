#pragma once

#include "GameConfig.h"

enum class AudioType { SOUND, MUSIC };

class Audio {
private:
    AudioType type;
    Mix_Chunk* chunk = nullptr;
    Mix_Music* music = nullptr;
    int channel = -1;

public:
    Audio();
    Audio(const std::string& path, AudioType type);
    ~Audio();

    bool load(const std::string& path, AudioType type);
    void play(int loops = 0);
    void stop();
};
