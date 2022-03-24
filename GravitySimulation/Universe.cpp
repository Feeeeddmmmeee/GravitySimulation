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

void Universe::render(SDL_Renderer* renderer)
{
	for (auto& planet : planets)
	{
		planet->render(renderer);
	}
}
