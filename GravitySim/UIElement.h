#pragma once

#include <SDL_image.h>
#include <functional>

#include "Universe.h"
#include "Vector.h"

enum class ID
{
	EXIT,
	RESTART,
	PLANET,
	EARTH,
	MARS
};

class UIElement
{
public:
	UIElement(Vector position, SDL_Renderer* renderer, const char* fileName, ID identifier);
	bool selected() { return isSelected; }
	ID getID() { return identifier; }
	void update(Vector mousePos);
	void render(SDL_Renderer* renderer);

private:
	bool isSelected;
	ID identifier;

	Vector position;
	SDL_Texture* texture;
	SDL_Rect destRect;
};