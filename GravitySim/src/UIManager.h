#pragma once

#include <vector>

#include "SDL_ttf.h"

#include "UIElement.h"
#include "Vector.h"

class UIManager
{
public:
	~UIManager();

	void update(Vector mousePos);
	void render(SDL_Renderer* renderer, std::string* texts, int size);

	void textInit(TTF_Font* font, SDL_Color color);

	std::vector<UIElement*> buttons = {};

private:
	TTF_Font* font;
	SDL_Color color;

};