#pragma once

#include "Planet.h"
#include <vector>

class Universe
{
public:
	void addPlanet(Planet* planet);
	void update();
	void render(SDL_Renderer* renderer);

private:
	std::vector<Planet*> planets;
};