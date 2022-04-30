#pragma once

#include "Planet.h"
#include "Vector.h"

#include <vector>
#include <Windows.h>

class Universe
{
public:
	void addPlanet(Planet* planet);
	void update();
	void render(SDL_Renderer* renderer, float zoom);
	void restart();
	void move(Vector deltaPos);

	size_t size() { return this->planets.size(); }

private:
	std::vector<Planet*> planets = {};
};