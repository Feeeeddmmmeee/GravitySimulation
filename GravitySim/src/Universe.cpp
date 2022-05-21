#include "Universe.h"

void Universe::addPlanet(Planet* planet)
{
	this->planets.push_back(planet);
}

void Universe::update()
{
	for (auto& planet : this->planets)
	{
		#if ASYNC
		this->futures.push_back(std::async(std::launch::async, [planet, this]() -> void
			{
				planet->updateVelocity(&this->planets, &this->mutex);
			}
		));

		#else 
		planet->updateVelocity(&this->planets, &this->mutex);

		#endif
	}
	#if ASYNC
	this->futures.clear();

	#endif

	for (auto& planet : this->planets)
	{
		#if ASYNC
		this->futures.push_back(std::async(std::launch::async, [planet, this]() -> void
			{
				planet->updatePosition(&this->mutex);
			}
		));

		#else
		planet->updatePosition(&this->mutex);

		#endif
	}

	#if ASYNC
	this->futures.clear();

	#endif
}

void Universe::render(SDL_Renderer* renderer, float zoom)
{
	for (auto& planet : this->planets)
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

void Universe::move(Vector deltaPos, std::mutex* m)
{
	for (auto& planet : planets)
	{
		#if ASYNC
		this->futures.push_back(std::async(std::launch::async, [planet, deltaPos, m]() -> void
			{
				std::lock_guard<std::mutex> lock(*m);
				planet->position += deltaPos;
			}
		));

		#else
		planet->position += deltaPos;

		#endif
	}

	#if ASYNC
	this->futures.clear();

	#endif
}

Vector Universe::getPlanetPosition(int& index)
{
	if (index < 0) index = this->planets.size() - 1;
	if (index > this->planets.size() - 1) index = 0;

	return this->planets[index]->position;
}