#include "Game.h"

Game* game = nullptr;

int main(int argc, char* argv[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game("Gravity Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, false);

	//ShowWindow(GetConsoleWindow(), SW_HIDE);

	#if ASYNC
	std::cout << "Async updates enabled!" << std::endl;

	#endif

	while (game->running())
	{

		frameStart = SDL_GetTicks();

		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		game->currentFPS = ((1000.0f / frameTime) > FPS) ? FPS : (1000.0f / frameTime);

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	//ShowWindow(GetConsoleWindow(), SW_RESTORE);
	delete game;

	return 0;
}