#pragma once

#include <SDL_image.h>
#include <functional>

#include "Universe.h"
#include "Vector.h"

class UIElement
{
public:
	UIElement(Vector position, SDL_Renderer* renderer, const char* fileName, std::string identifier);
	bool selected() { return isSelected; }
	std::string getID() { return identifier; }
	void update(Vector mousePos);
	void render(SDL_Renderer* renderer);

private:
	bool isSelected;
	std::string identifier;

	Vector position;
	SDL_Texture* texture;
	SDL_Rect destRect;
};