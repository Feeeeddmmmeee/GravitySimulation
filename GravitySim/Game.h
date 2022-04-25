#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include "Universe.h"
#include "UIManager.h"

#include <iostream>

class Game {

public:
	Game(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	~Game();

	void update();
	void render();
	void handleEvents();

	bool running() { return isRunning; };

private:
	bool isRunning, isPaused;

	bool editingV, editingM, skipM;
	bool editingPos;
	Vector previousMousePos;
	float zoom;

	SDL_Window* window;
	SDL_Renderer* renderer;

	Universe universe;

	Planet* tempPlanet = nullptr;
	UIManager ui;
};