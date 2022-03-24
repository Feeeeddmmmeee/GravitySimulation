#include "SDL.h"
#include "Game.h"

#include <Windows.h>

Game* game = nullptr;

int main(int argc, char* argv[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->init("Gravity Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, false);

	//ShowWindow(GetConsoleWindow(), SW_HIDE);

	while (game->running())
	{

		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	//ShowWindow(GetConsoleWindow(), SW_RESTORE);
	game->clean();

	return 0;
}