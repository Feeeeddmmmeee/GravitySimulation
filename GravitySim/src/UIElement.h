#ifndef UI_ELEMENT_H
#define UI_ELEMENT_H

#include <SDL_image.h>
#include <functional>

#include "Universe.h"
#include "Vector.h"

enum class ID
{
	EXIT,
	PAUSE,
	RESTART,
	PLANET,
	EARTH,
	MARS
};

class UIElement
{
public:
	UIElement(Vector position, SDL_Renderer* renderer, const char* fileName, ID identifier);
	UIElement(Vector position, SDL_Renderer* renderer, SDL_Texture* texture, ID identifier);

	bool selected() { return isSelected; }
	ID getID() { return identifier; }

	void update(Vector mousePos);
	void render(SDL_Renderer* renderer);

	void updateTexture(SDL_Texture* texture);
	SDL_Texture* getTexture() { return this->texture; }

private:
	bool isSelected;
	ID identifier;

	Vector position;
	SDL_Texture* texture;
	SDL_Rect destRect;
};

#endif