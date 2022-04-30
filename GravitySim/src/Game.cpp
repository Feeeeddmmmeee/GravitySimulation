#include "Game.h"

#include <time.h>
#include <Windows.h>
#include <string>

Game::Game(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
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

	if (TTF_Init() == 0)
	{
		std::cout << "Font Rendering Initialized!" << std::endl;
	}

	SDL_Surface* tempSurface = IMG_Load("res/gfx/planet.png");
	this->planet = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	tempSurface = IMG_Load("res/gfx/earth.png");
	this->earth = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	tempSurface = IMG_Load("res/gfx/mars.png");
	this->mars = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	// 4 Planets in a circle
	/*universe.addPlanet(new Planet(100000, Vector(200, 400), Vector(0, 1), renderer, this->planet));
	universe.addPlanet(new Planet(100000, Vector(600, 400), Vector(0, -1), renderer, this->planet));
	universe.addPlanet(new Planet(100000, Vector(400, 200), Vector(-1, 0), renderer, this->planet));
	universe.addPlanet(new Planet(100000, Vector(400, 600), Vector(1, 0), renderer, this->planet));//*/

	// Random planets
	srand(time(NULL));
	for (int i = 0; i < 100; i++)
	{
		universe.addPlanet(new Planet(10 + std::rand() % 91, Vector(std::rand() % width, std::rand() % height), Vector((std::rand() % 10 - 5) / 10, (std::rand() % 10 - 5) / 10), renderer, this->planet));
	}//*/

	// Orbiting planets
	/*universe.addPlanet(new Planet(100000, Vector(width/2, height/2), Vector(0, 0), renderer, this->planet));
	universe.addPlanet(new Planet(1000, Vector(width/2, height/2 - height/4), Vector(7, 0), renderer, this->planet));
	universe.addPlanet(new Planet(1000, Vector(width/2, height/2 + height/4), Vector(-7, 0), renderer, this->planet));//*/

	// Buttons
	ui = new UIManager();
	ui->buttons.push_back(new UIElement(Vector(width - 34 - 5, 10), this->renderer, "res/gfx/gui_exit.png", ID::EXIT));
	ui->buttons.push_back(new UIElement(Vector(width - 34 - 5, 10 + 34 + 5), this->renderer, "res/gfx/gui_restart.png", ID::RESTART));
	ui->buttons.push_back(new UIElement(Vector(width - 34 - 5, 10 + 2*34 + 2*5), this->renderer, "res/gfx/gui_planet.png", ID::PLANET));
	ui->buttons.push_back(new UIElement(Vector(width - 34 - 5, 10 + 3*34 + 3*5), this->renderer, "res/gfx/gui_earth.png", ID::EARTH));
	ui->buttons.push_back(new UIElement(Vector(width - 34 - 5, 10 + 4*34 + 4*5), this->renderer, "res/gfx/gui_mars.png", ID::MARS));
	
	isPaused = false;
	zoom = 1;

	TTF_Font* font = TTF_OpenFont("res/font/its_me_sans_undertale.ttf", 24);
	this->ui->textInit(font, { 255, 255, 255 });
}

void Game::update()
{
	if (editingPos)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		Vector mouseVec = Vector(x, y);

		this->universe.move(mouseVec - this->previousMousePos);
		this->previousMousePos = mouseVec;
	}

	if(!isPaused) this->universe.update();

	int x, y;
	SDL_GetMouseState(&x, &y);
	Vector mousePos = Vector(x, y);
	this->ui->update(mousePos);
	if (this->tempPlanet)
	{
		if (editingM)
		{
			tempPlanet->radius = Vector(mousePos - tempPlanet->position).Lenght();
			tempPlanet->mass = pow(tempPlanet->radius, 3) * 3 * DENSITY * PI / 4;
		}
		else if(!editingV) this->tempPlanet->position = mousePos;
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);

	// Planets
	this->universe.render(this->renderer, this->zoom);

	// UI
	std::string arr[2] = { "FPS: " + std::to_string(this->currentFPS), "Planets: " + std::to_string(this->universe.size()) };
	this->ui->render(this->renderer, arr, 2);

	// Temp Planet
	if (this->tempPlanet) this->tempPlanet->render(renderer, this->zoom);
	if (this->editingV && this->tempPlanet)
	{
		// Rendering the velocity vector
		int x, y;
		SDL_GetMouseState(&x, &y);
		
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderDrawLine(this->renderer, tempPlanet->position.x, tempPlanet->position.y, x, y);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		
	}

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

	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			isRunning = false;
			break;

		case SDLK_SPACE:
			isPaused = !isPaused;
			if (this->tempPlanet)
			{
				this->universe.addPlanet(new Planet(*tempPlanet));
				delete tempPlanet;
				tempPlanet = nullptr;
				editingV = false;
				editingM = false;
			}
			break;

		}
		break;

	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_MIDDLE)
		{
			this->editingPos = true;
			//isPaused = true;

			int x, y;
			SDL_GetMouseState(&x, &y);
			this->previousMousePos = Vector(x, y);
		}
		break;

	case SDL_MOUSEBUTTONUP:
		switch(event.button.button)
		{ 
		case SDL_BUTTON_MIDDLE:
			if (this->editingPos)
			{
				this->editingPos = false;
				//isPaused = false;
			}
			break;
		
		case SDL_BUTTON_RIGHT:
			if (this->tempPlanet)
			{
				isPaused = !isPaused;
				this->universe.addPlanet(new Planet(*tempPlanet));
				delete tempPlanet;
				tempPlanet = nullptr;
				editingV = false;
				editingM = false;
			}
			break;

		case SDL_BUTTON_LEFT:
			if (this->tempPlanet)
			{
				if (editingM)
				{
					editingV = true;
					editingM = false;
				}
				else if (editingV)
				{
					// Adding velocity
					int x, y;
					SDL_GetMouseState(&x, &y);
					tempPlanet->velocity = Vector(x, y) - tempPlanet->position;
					tempPlanet->velocity = tempPlanet->velocity / 10;

					// Adding the planet 
					this->universe.addPlanet(new Planet(*tempPlanet));
					delete tempPlanet;
					tempPlanet = nullptr;
					isPaused = false;
					editingV = false;
				}
				else
				{
					if (skipM) editingV = true;
					else editingM = true;
				}
			}

			const int EARTH_MASS = 10000;
			for (auto& button : this->ui->buttons)
			{
				if (button->selected())
				{
					editingV = editingM = false;
					isPaused = skipM = true;

					switch (button->getID())
					{
					case ID::EXIT:
						isRunning = false;
						break;

					case ID::RESTART:
						this->universe.restart();
						break;

					case ID::PLANET:
						int m;

						//std::cin >> m;
						m = 10000;

						if (this->tempPlanet)
						{
							delete tempPlanet;
						}
						//
						this->tempPlanet = new Planet(m, Vector(0, 0), Vector(0, 0), renderer, this->planet);
						skipM = false;
						break;

					case ID::EARTH:
						if (this->tempPlanet)
						{
							delete tempPlanet;
						}
						this->tempPlanet = new Planet(EARTH_MASS, Vector(0, 0), Vector(0, 0), renderer, this->earth);
						break;

					case ID::MARS:
						if (this->tempPlanet)
						{
							delete tempPlanet;
						}
						this->tempPlanet = new Planet(EARTH_MASS * 0.714, Vector(0, 0), Vector(0, 0), renderer, this->mars);
						break;
					}
				}
			}
			break;

		}
	}
}

Game::~Game()
{
	delete tempPlanet;
	delete ui;

	SDL_DestroyTexture(this->planet);
	SDL_DestroyTexture(this->earth);
	SDL_DestroyTexture(this->mars);

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	TTF_Quit();
}