#ifndef GAME_H
#define GAME_H

#include <string>

#include "Universe.h"
#include "UIManager.h"

class Game {

public:
	Game(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	~Game();

	void update();
	void render();
	void handleEvents();

	bool running() { return isRunning; };

	int currentFPS;

private:
	int index = 0;
	bool isRunning, isPaused;

	bool editingV, editingM, skipM;
	bool editingPos;
	Vector previousMousePos;
	float zoom;

	SDL_Window* window;
	SDL_Renderer* renderer;

	SDL_Texture* planet, *earth, *mars, *pause, *play;
	Universe universe;

	Planet* tempPlanet = nullptr;
	UIManager* ui;

};

#endif