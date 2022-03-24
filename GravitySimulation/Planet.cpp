#include "Planet.h"

const double PI = 3.1415;
const double DENSITY = 1;
const double G = 0.01;

Planet::Planet(double mass, Vector position, Vector velocity)
{
	this->radius = std::cbrt(3 * mass / DENSITY / PI / 4);
	this->acceleration = Vector();
	this->mass = mass;
	this->position = position;
	this->velocity = velocity;
}

void Planet::updateVelocity(std::vector<Planet> others)
{
	this->acceleration = Vector();

	for (auto& other : others)
	{
		//cant collide with itself
		if (&other == this) continue;

		/*collision
		if (sqrt(pow((position.x + radius - other.position.x - other.radius), 2) + pow((position.y + radius - other.position.y - other.radius), 2)) < radius + other.radius)
		{

		}*/

		Vector posV = other.position - this->position;
		double distance = posV.Lenght(); 
		Vector mag = posV / distance;

		double force = this->mass * other.mass * G / pow(distance, 2);
		this->acceleration += mag * force / this->mass;
	}

	this->velocity += this->acceleration;
}

void Planet::updatePosition()
{
	this->position += this->velocity;
}

void Planet::draw()
{
}
