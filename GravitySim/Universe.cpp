#include "Universe.h"

void Universe::addPlanet(Planet* planet)
{
	this->planets.push_back(planet);
}

void Universe::update()
{
	for (auto& planet : planets)
	{
		planet->updateVelocity(planets);
	}

	for (auto& planet : planets)
	{
		planet->updatePosition();
	}
}

void Universe::render(SDL_Renderer* renderer, float zoom)
{
	for (auto& planet : planets)
	{
		planet->render(renderer, zoom);
	}
}

void Universe::restart()
{
	for (int i = 0; i < this->planets.size(); i++)
	{
		Planet* p = this->planets[i];
		delete p;
	}
	this->planets.clear();
}

void Universe::move(Vector deltaPos)
{
	for (auto& planet : planets)
	{
		planet->position += deltaPos;
	}
}
