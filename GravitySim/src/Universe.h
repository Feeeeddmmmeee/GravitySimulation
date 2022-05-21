#ifndef UNIVERSE_H
#define UNIVERSE_H

#include <future>

#include "Planet.h"

class Universe
{
public:
	void addPlanet(Planet* planet);
	void update();
	void render(SDL_Renderer* renderer, float zoom);
	void restart();
	void move(Vector deltaPos, std::mutex* m);

	size_t size() { return this->planets.size(); }

	Vector getPlanetPosition(int& index);
	std::mutex* getMutexPtr() { return &this->mutex; }

private:
	std::vector<Planet*> planets = {};

	std::vector<std::future<void>> futures;
	std::mutex mutex;

};

#endif