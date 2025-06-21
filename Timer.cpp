#include "Timer.h"

ImpTimer::ImpTimer()
{
	startTicks = 0;
	pausedTicks = 0;
	paused = false;
	started = false;
}

ImpTimer::~ImpTimer()
{
}

void ImpTimer::start()
{
	started = true;
	paused = false;
	startTicks = SDL_GetTicks();
}

void ImpTimer::stop()
{
	paused = false;
	started = false;
}

void ImpTimer::pause()
{
	if (started == true && paused == false) {
		paused = true;
		pausedTicks = SDL_GetTicks() - startTicks;
	}
}

void ImpTimer::unpause()
{
	if (paused == true) {
		paused = false;
		startTicks = SDL_GetTicks() - pausedTicks;
		pausedTicks = 0;
	}
}

int ImpTimer::get_ticks()
{
	if (started == true) {
		if (paused == true) {
			return pausedTicks;
		}
		else {
			return SDL_GetTicks() - startTicks;
		}
	}
	return 0;
}

bool ImpTimer::is_started()
{
	return started;
}

bool ImpTimer::is_paused()
{
	return paused;
}