#include "Game.h"

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

		this->window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (this->window)
		{
			std::cout << "Window Created!" << std::endl;
		}

		this->renderer = SDL_CreateRenderer(this->window, -1, 0);
		if (this->renderer)
		{
			SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 255);
			std::cout << "Renderer Created!" << std::endl;
		}

		this->isRunning = true;
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

	tempSurface = IMG_Load("res/gfx/gui_pause_pause.png");
	this->pause = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	tempSurface = IMG_Load("res/gfx/gui_pause_play.png");
	this->play = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	srand(time(NULL));
	for (int i = 0; i < 100; i++)
	{
		this->universe.addPlanet(new Planet(10 + std::rand() % 91, Vector(std::rand() % width, std::rand() % height), Vector((std::rand() % 10 - 5) / 10, (std::rand() % 10 - 5) / 10), this->renderer, this->planet));
	}//*/

	// Orbiting planets
	/*this->universe.addPlanet(new Planet(100000, Vector(width/2, height/2), Vector(0 , 0), this->renderer, this->planet));
	this->universe.addPlanet(new Planet(1000, Vector(width/2, height/2 - height/4), Vector(7 , 0), this->renderer, this->planet));
	this->universe.addPlanet(new Planet(1000, Vector(width/2, height/2 + height/4), Vector(-7 , 0), this->renderer, this->planet));//*/

	this->ui = new UIManager();
	this->ui->buttons.push_back(new UIElement(Vector(width - 34 - 5, 10), this->renderer, "res/gfx/gui_exit.png", ID::EXIT));
	this->ui->buttons.push_back(new UIElement(Vector(width - 34 - 5, 10 + 34 + 5), this->renderer, this->pause, ID::PAUSE));
	this->ui->buttons.push_back(new UIElement(Vector(width - 34 - 5, 10 + 2*34 + 2*5), this->renderer, "res/gfx/gui_restart.png", ID::RESTART));
	this->ui->buttons.push_back(new UIElement(Vector(width - 34 - 5, 10 + 3*34 + 3*5), this->renderer, "res/gfx/gui_planet.png", ID::PLANET));
	this->ui->buttons.push_back(new UIElement(Vector(width - 34 - 5, 10 + 4*34 + 4*5), this->renderer, "res/gfx/gui_earth.png", ID::EARTH));
	this->ui->buttons.push_back(new UIElement(Vector(width - 34 - 5, 10 + 5*34 + 5*5), this->renderer, "res/gfx/gui_mars.png", ID::MARS));
	
	this->isPaused = false;
	this->zoom = 1;

	TTF_Font* font = TTF_OpenFont("res/font/its_me_sans_undertale.ttf", 24);
	this->ui->textInit(font, { 255, 255, 255 });
}

void Game::update()
{
	if (this->editingPos)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		Vector mouseVec = Vector(x, y);

		this->universe.move(mouseVec - this->previousMousePos, this->universe.getMutexPtr());
		this->previousMousePos = mouseVec;
	}

	if(!this->isPaused) this->universe.update();

	UIElement* e = this->ui->getElementByID(ID::PAUSE);
	if (!this->isPaused)
	{
		if (e->getTexture() == this->play)
			e->updateTexture(this->pause);
	}
	else
	{
		if (e->getTexture() == this->pause)
			e->updateTexture(this->play);
	}

	int x, y;
	SDL_GetMouseState(&x, &y);
	Vector mousePos = Vector(x, y);

	this->ui->update(mousePos);

	if (this->tempPlanet)
	{
		if (this->editingM)
		{
			float len = Vector(mousePos - this->tempPlanet->position).Lenght();
			this->tempPlanet->radius = len > 1 ? len : 1;
			this->tempPlanet->mass = pow(this->tempPlanet->radius, 3) * 3 * DENSITY * PI / 4;
		}
		else if(!this->editingV) this->tempPlanet->position = mousePos;
	}
}

void Game::render()
{
	SDL_RenderClear(renderer);

	this->universe.render(this->renderer, this->zoom);

	std::string arr[3] = { "FPS: " + std::to_string(this->currentFPS), "Planets: " + std::to_string(this->universe.size()), "Paused: " + std::string(this->isPaused ? "true" : "false") };
	this->ui->render(this->renderer, arr, 3);

	if (this->tempPlanet) this->tempPlanet->render(this->renderer, this->zoom);
	if (this->editingV && this->tempPlanet)
	{
		int x, y;
		SDL_GetMouseState(&x, &y);
		
		SDL_SetRenderDrawColor(this->renderer, 255, 0, 0, 255);
		SDL_RenderDrawLine(this->renderer, this->tempPlanet->position.x, this->tempPlanet->position.y, x, y);
		SDL_SetRenderDrawColor(this->renderer, 0, 0, 0, 0);
		
	}

	SDL_RenderPresent(this->renderer);
}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		this->isRunning = false;
		break;

	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			this->isRunning = false;
			break;

		case SDLK_SPACE:
			this->isPaused = !this->isPaused;
			if (this->tempPlanet)
			{
				this->universe.addPlanet(new Planet(*this->tempPlanet));
				delete this->tempPlanet;
				this->tempPlanet = nullptr;
				this->editingV = false;
				this->editingM = false;
			}
			break;

		case SDLK_RIGHT:
			if (index >= this->universe.size()) index = 0;
			else if (index < 0) index = this->universe.size() - 1;

			this->universe.move(this->universe.getPlanetPosition(this->index) * -1, this->universe.getMutexPtr());
			this->universe.move(Vector(400, 400), this->universe.getMutexPtr());
			this->index++;

			break;

		case SDLK_LEFT:
			if (index < 0) index = this->universe.size() - 1;
			else if (index >= this->universe.size()) index = 0;

			this->universe.move(this->universe.getPlanetPosition(this->index) * -1, this->universe.getMutexPtr());
			this->universe.move(Vector(400, 400), this->universe.getMutexPtr());
			this->index--;

			break;

		}
		break;

	case SDL_MOUSEBUTTONDOWN:
		if (event.button.button == SDL_BUTTON_MIDDLE)
		{
			this->editingPos = true;

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
			}
			break;
		
		case SDL_BUTTON_RIGHT:
			if (this->tempPlanet)
			{
				this->isPaused = !this->isPaused;
				this->universe.addPlanet(new Planet(*this->tempPlanet));
				delete this->tempPlanet;
				this->tempPlanet = nullptr;
				this->editingV = false;
				this->editingM = false;
			}
			break;

		case SDL_BUTTON_LEFT:
			if (this->tempPlanet)
			{
				if (this->editingM)
				{
					this->editingV = true;
					this->editingM = false;
				}
				else if (this->editingV)
				{
					int x, y;
					SDL_GetMouseState(&x, &y);
					this->tempPlanet->velocity = Vector(x, y) - this->tempPlanet->position;
					this->tempPlanet->velocity = this->tempPlanet->velocity / 10;

					this->universe.addPlanet(new Planet(*this->tempPlanet));
					delete tempPlanet;
					this->tempPlanet = nullptr;
					this->isPaused = false;
					this->editingV = false;
				}
				else
				{
					if (this->skipM) this->editingV = true;
					else this->editingM = true;
				}
			}

			const int EARTH_MASS = 10000;
			for (auto& button : this->ui->buttons)
			{
				if (button->selected())
				{
					this->editingV = this->editingM = false;
					this->skipM = true;

					switch (button->getID())
					{
					case ID::EXIT:
						this->isRunning = false;
						break;

					case ID::PAUSE:
						this->isPaused = !this->isPaused;
						break;

					case ID::RESTART:
						this->universe.restart();
						break;

					case ID::PLANET:
						this->isPaused = true;
						int m;

						m = 10000;

						if (this->tempPlanet)
						{
							delete tempPlanet;
						}
						
						this->tempPlanet = new Planet(m, Vector(0, 0), Vector(0, 0), renderer, this->planet);
						this->skipM = false;
						break;

					case ID::EARTH:
						this->isPaused = true;
						if (this->tempPlanet)
						{
							delete tempPlanet;
						}
						this->tempPlanet = new Planet(EARTH_MASS, Vector(0, 0), Vector(0, 0), this->renderer, this->earth);
						break;

					case ID::MARS:
						this->isPaused = true;
						if (this->tempPlanet)
						{
							delete tempPlanet;
						}
						this->tempPlanet = new Planet(EARTH_MASS * 0.714, Vector(0, 0), Vector(0, 0), this->renderer, this->mars);
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
	delete this->tempPlanet;
	delete this->ui;

	SDL_DestroyTexture(this->planet);
	SDL_DestroyTexture(this->earth);
	SDL_DestroyTexture(this->mars);

	SDL_DestroyWindow(this->window);
	SDL_DestroyRenderer(this->renderer);
	SDL_Quit();
	TTF_Quit();
}