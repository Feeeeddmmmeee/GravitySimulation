#ifndef UNIVERSE_H
#define UNIVERSE_H

#include "Planet.h"

class Universe
{
public:
	void addPlanet(Planet* planet);
	void update();
	void render(SDL_Renderer* renderer, float zoom);
	void restart();
	void move(Vector deltaPos);

	size_t size() { return this->planets.size(); }

	Vector getPlanetPosition(int& index);

private:
	std::vector<Planet*> planets = {};
};

#endif