#pragma once

#include "Vector.h"
#include <vector>
#include "SDL_image.h"

struct Planet
{
	double radius, mass;
	Vector position, velocity, acceleration;
	
	SDL_Rect srcRect, destRect;
	SDL_Texture* texture;

	Planet(double mass, Vector position, Vector velocity, SDL_Renderer* renderer);

	void updateVelocity(std::vector<Planet*> others);
	void updatePosition();
	
	void render(SDL_Renderer* renderer);
};