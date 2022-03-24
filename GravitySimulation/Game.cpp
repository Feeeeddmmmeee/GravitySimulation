#include "Game.h"

#include <time.h>
#include <Windows.h>

Game::Game() {};
Game::~Game() {};

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialized!" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window Created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			std::cout << "Renderer Created!" << std::endl;
		}

		isRunning = true;
	}

	universe.addPlanet(new Planet(100000, Vector(200, 400), Vector(0, 1), renderer));
	universe.addPlanet(new Planet(100000, Vector(600, 400), Vector(0, -1), renderer));
	universe.addPlanet(new Planet(100000, Vector(400, 200), Vector(-1, 0), renderer));
	universe.addPlanet(new Planet(100000, Vector(400, 600), Vector(1, 0), renderer));
}

void Game::update()
{
	this->universe.update();
}

void Game::render()
{
	SDL_RenderClear(renderer);

	this->universe.render(this->renderer);

	SDL_RenderPresent(renderer);
}

void Game::handleEvents()
{

	SDL_Event event;

	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	}

}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}