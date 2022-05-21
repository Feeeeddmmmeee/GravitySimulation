#include "Planet.h"

Planet::Planet(double mass, Vector position, Vector velocity, SDL_Renderer* renderer, SDL_Texture* texture)
{
	this->radius = std::cbrt(4 * mass / DENSITY / PI / 3);
	this->mass = mass;
	this->position = position;
	this->velocity = velocity;

	this->texture = texture;
}

void Planet::destroyTexture()
{
	SDL_DestroyTexture(this->texture);
}

void Planet::updateVelocity(std::vector<Planet*>* vec, std::mutex* m)
{
	auto& others = *vec;
	Vector acceleration;

	for (auto& other : others)
	{
		if (other == this) continue;

		if (sqrt(pow((this->position.x + this->radius - other->position.x - other->radius), 2) + pow((this->position.y + this->radius - other->position.y - other->radius), 2)) < this->radius + other->radius)
		{

			std::lock_guard<std::mutex> lock(*m);
			if (this->mass > other->mass)
			{
				this->mass += other->mass;
				this->velocity += other->velocity * other->mass / this->mass;

				Planet* p = other;
				delete p;

				others.erase(std::remove(others.begin(), others.end(), other), others.end());
				this->radius = std::cbrt(4 * this->mass / DENSITY / PI / 3);

				return;
			}
			else
			{
				other->mass += this->mass;
				other->velocity += this->velocity * this->mass / other->mass;

				Planet* p = this;
				delete p;

				others.erase(std::remove(others.begin(), others.end(), this), others.end());
				other->radius = std::cbrt(4 * other->mass / DENSITY / PI / 3);

				return;
			}
		}

		Vector posV = other->position - this->position;
		double distance = posV.Lenght();
		if (!distance) return;
		Vector mag = posV / distance;

		double force = this->mass * other->mass * G / pow(distance, 2);

		acceleration += mag * force / this->mass;
	}

	std::lock_guard<std::mutex> lock(*m);
	this->velocity += acceleration;
}

void Planet::updatePosition(std::mutex* m)
{
	std::lock_guard<std::mutex> lock(*m);
	this->position += this->velocity;
}

void Planet::render(SDL_Renderer* renderer, float zoom)
{
	this->destRect.w = this->destRect.h = this->radius * 2 / zoom;

	this->destRect.x = (this->position.x - this->radius) / zoom;
	this->destRect.y = (this->position.y - this->radius) / zoom;

	SDL_RenderCopy(renderer, this->texture, 0, &destRect);
}
