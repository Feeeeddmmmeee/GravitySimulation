#include "Planet.h"

#include "SDL_image.h"
#include "SDL.h"

#include <Windows.h>

//const double MOUSE = -1000;

Planet::Planet(double mass, Vector position, Vector velocity, SDL_Renderer* renderer)
{
	this->radius = std::cbrt(4 * mass / DENSITY / PI / 3);
	this->acceleration = Vector();
	this->mass = mass;
	this->position = position;
	this->velocity = velocity;

	SDL_Surface* tempSurface = IMG_Load("planet.png");
	this->texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
}

Planet::Planet(double mass, Vector position, Vector velocity, SDL_Renderer* renderer, const char* fileName)
{
	this->radius = std::cbrt(4 * mass / DENSITY / PI / 3);
	this->acceleration = Vector();
	this->mass = mass;
	this->position = position;
	this->velocity = velocity;

	SDL_Surface* tempSurface = IMG_Load(fileName);
	this->texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
}

void Planet::destroyTexture()
{
	SDL_DestroyTexture(this->texture);
}

void Planet::updateVelocity(std::vector<Planet*>& others)
{
	this->acceleration = Vector();

	for (auto& other : others)
	{
		//cant collide with itself
		if (other == this) continue;

		//collision
		if (sqrt(pow((position.x + radius - other->position.x - other->radius), 2) + pow((position.y + radius - other->position.y - other->radius), 2)) < radius + other->radius)
		{
			if (this->mass > other->mass)
			{
				this->mass += other->mass;
				this->velocity += other->velocity * other->mass / this->mass;
				//this->radius = std::cbrt(4 * mass / DENSITY / PI / 3);

				Planet* p = other;
				p->destroyTexture();
				delete p;
				others.erase(std::remove(others.begin(), others.end(), other), others.end());
				return;
			}
			else
			{
				other->mass += this->mass;
				other->velocity += this->velocity * this->mass / other->mass;
				//other->radius = std::cbrt(4 * mass / DENSITY / PI / 3);

				Planet* p = this;
				p->destroyTexture();
				delete p;
				others.erase(std::remove(others.begin(), others.end(), this), others.end());
				return;
			}
		}//*/

		Vector posV = other->position - this->position;
		double distance = posV.Lenght();
		Vector mag = posV / distance;

		double force = this->mass * other->mass * G / pow(distance, 2);
		this->acceleration += mag * force / this->mass;
		this->radius = std::cbrt(4 * mass / DENSITY / PI / 3);
	}

	//mouse
	/*POINT p;
	HWND handle;
	handle = FindWindowA(NULL, "Gravity Simulation");
	if (GetCursorPos(&p))
	{
		if (ScreenToClient(handle, &p))
		{
			Vector mouse = Vector(p.x, p.y);

			Vector posV = mouse - this->position;
			double distance = posV.Lenght();
			Vector mag = posV / distance;

			double force = this->mass * MOUSE * G / pow(distance, 2);
			this->acceleration += mag * force / this->mass;
		}
	}//*/

	this->velocity += this->acceleration;
}

void Planet::updatePosition()
{
	this->position += this->velocity;
}

void Planet::render(SDL_Renderer* renderer, float zoom)
{
	this->destRect.w = this->destRect.h = this->radius * 2 / zoom;

	this->destRect.x = (this->position.x - this->radius)/zoom;
	this->destRect.y = (this->position.y - this->radius)/zoom;

	SDL_RenderCopy(renderer, this->texture, 0, &destRect);
}
