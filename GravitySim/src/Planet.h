#pragma once

#include "Vector.h"
#include <vector>
#include "SDL_image.h"

constexpr auto PI = 3.1415;
constexpr auto DENSITY = 1;
constexpr auto G = 0.1; //6.67408e-11;

struct Planet
{
	double radius, mass;
	Vector position, velocity, acceleration;

	SDL_Rect destRect;
	SDL_Texture* texture;

	Planet(double mass, Vector position, Vector velocity, SDL_Renderer* renderer);
	Planet(double mass, Vector position, Vector velocity, SDL_Renderer* renderer, SDL_Texture* texture);
	Planet(double mass, Vector position, Vector velocity, SDL_Renderer* renderer, const char* fileName);

	void destroyTexture();

	void updateVelocity(std::vector<Planet*>& others);
	void updatePosition();

	void render(SDL_Renderer* renderer, float zoom);
};